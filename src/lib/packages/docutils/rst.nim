#
#
#            Nim's Runtime Library
#        (c) Copyright 2012 Andreas Rumpf
#
#    See the file "copying.txt", included in this
#    distribution, for details about the copyright.
#

## This module implements a `reStructuredText`:idx: parser. A large
## subset is implemented. Some features of the `markdown`:idx: wiki syntax are
## also supported.
##
## **Note:** Import ``packages/docutils/rst`` to use this module

import
  os, strutils, rstast

type
  RstParseOption* = enum     ## options for the RST parser
    roSkipPounds,             ## skip ``#`` at line beginning (documentation
                              ## embedded in Nim comments)
    roSupportSmilies,         ## make the RST parser support smilies like ``:)``
    roSupportRawDirective,    ## support the ``raw`` directive (don't support
                              ## it for sandboxing)
    roSupportMarkdown         ## support additional features of markdown

  RstParseOptions* = set[RstParseOption]

  MsgClass* = enum
    mcHint = "Hint",
    mcWarning = "Warning",
    mcError = "Error"

  MsgKind* = enum          ## the possible messages
    meCannotOpenFile,
    meExpected,
    meGridTableNotImplemented,
    meNewSectionExpected,
    meGeneralParseError,
    meInvalidDirective,
    mwRedefinitionOfLabel,
    mwUnknownSubstitution,
    mwUnsupportedLanguage,
    mwUnsupportedField

  MsgHandler* = proc (filename: string, line, col: int, msgKind: MsgKind,
                       arg: string) {.closure, gcsafe.} ## what to do in case of an error
  FindFileHandler* = proc (filename: string): string {.closure, gcsafe.}

const
  messages: array[MsgKind, string] = [
    meCannotOpenFile: "cannot open '$1'",
    meExpected: "'$1' expected",
    meGridTableNotImplemented: "grid table is not implemented",
    meNewSectionExpected: "new section expected",
    meGeneralParseError: "general parse error",
    meInvalidDirective: "invalid directive: '$1'",
    mwRedefinitionOfLabel: "redefinition of label '$1'",
    mwUnknownSubstitution: "unknown substitution '$1'",
    mwUnsupportedLanguage: "language '$1' not supported",
    mwUnsupportedField: "field '$1' not supported"
  ]

proc rstnodeToRefname*(n: PRstNode): string
proc addNodes*(n: PRstNode): string
proc getFieldValue*(n: PRstNode, fieldname: string): string
proc getArgument*(n: PRstNode): string

# ----------------------------- scanner part --------------------------------

const
  SymChars: set[char] = {'a'..'z', 'A'..'Z', '0'..'9', '\x80'..'\xFF'}
  SmileyStartChars: set[char] = {':', ';', '8'}
  Smilies = {
    ":D": "icon_e_biggrin",
    ":-D": "icon_e_biggrin",
    ":)": "icon_e_smile",
    ":-)": "icon_e_smile",
    ";)": "icon_e_wink",
    ";-)": "icon_e_wink",
    ":(": "icon_e_sad",
    ":-(": "icon_e_sad",
    ":o": "icon_e_surprised",
    ":-o": "icon_e_surprised",
    ":shock:": "icon_eek",
    ":?": "icon_e_confused",
    ":-?": "icon_e_confused",
    ":-/": "icon_e_confused",

    "8-)": "icon_cool",

    ":lol:": "icon_lol",
    ":x": "icon_mad",
    ":-x": "icon_mad",
    ":P": "icon_razz",
    ":-P": "icon_razz",
    ":oops:": "icon_redface",
    ":cry:": "icon_cry",
    ":evil:": "icon_evil",
    ":twisted:": "icon_twisted",
    ":roll:": "icon_rolleyes",
    ":!:": "icon_exclaim",

    ":?:": "icon_question",
    ":idea:": "icon_idea",
    ":arrow:": "icon_arrow",
    ":|": "icon_neutral",
    ":-|": "icon_neutral",
    ":mrgreen:": "icon_mrgreen",
    ":geek:": "icon_e_geek",
    ":ugeek:": "icon_e_ugeek"
  }

type
  TokType = enum
    tkEof, tkIndent, tkWhite, tkWord, tkAdornment, tkPunct, tkOther
  Token = object              # a RST token
    kind*: TokType            # the type of the token
    ival*: int                # the indentation or parsed integer value
    symbol*: string           # the parsed symbol as string
    line*, col*: int          # line and column of the token

  TokenSeq = seq[Token]
  Lexer = object of RootObj
    buf*: cstring
    bufpos*: int
    line*, col*, baseIndent*: int
    skipPounds*: bool

proc getThing(L: var Lexer, tok: var Token, s: set[char]) =
  tok.kind = tkWord
  tok.line = L.line
  tok.col = L.col
  var pos = L.bufpos
  while true:
    add(tok.symbol, L.buf[pos])
    inc(pos)
    if L.buf[pos] notin s: break
  inc(L.col, pos - L.bufpos)
  L.bufpos = pos

proc getAdornment(L: var Lexer, tok: var Token) =
  tok.kind = tkAdornment
  tok.line = L.line
  tok.col = L.col
  var pos = L.bufpos
  var c = L.buf[pos]
  while true:
    add(tok.symbol, L.buf[pos])
    inc(pos)
    if L.buf[pos] != c: break
  inc(L.col, pos - L.bufpos)
  L.bufpos = pos

proc getBracket(L: var Lexer, tok: var Token) =
  tok.kind = tkPunct
  tok.line = L.line
  tok.col = L.col
  add(tok.symbol, L.buf[L.bufpos])
  inc L.col
  inc L.bufpos

proc getIndentAux(L: var Lexer, start: int): int =
  var pos = start
  # skip the newline (but include it in the token!)
  if L.buf[pos] == '\x0D':
    if L.buf[pos + 1] == '\x0A': inc(pos, 2)
    else: inc(pos)
  elif L.buf[pos] == '\x0A':
    inc(pos)
  if L.skipPounds:
    if L.buf[pos] == '#': inc(pos)
    if L.buf[pos] == '#': inc(pos)
  while true:
    case L.buf[pos]
    of ' ', '\x0B', '\x0C':
      inc(pos)
      inc(result)
    of '\x09':
      inc(pos)
      result = result - (result mod 8) + 8
    else:
      break                   # EndOfFile also leaves the loop
  if L.buf[pos] == '\0':
    result = 0
  elif (L.buf[pos] == '\x0A') or (L.buf[pos] == '\x0D'):
    # look at the next line for proper indentation:
    result = getIndentAux(L, pos)
  L.bufpos = pos              # no need to set back buf

proc getIndent(L: var Lexer, tok: var Token) =
  tok.col = 0
  tok.kind = tkIndent         # skip the newline (but include it in the token!)
  tok.ival = getIndentAux(L, L.bufpos)
  inc L.line
  tok.line = L.line
  L.col = tok.ival
  tok.ival = max(tok.ival - L.baseIndent, 0)
  tok.symbol = "\n" & spaces(tok.ival)

proc rawGetTok(L: var Lexer, tok: var Token) =
  tok.symbol = ""
  tok.ival = 0
  var c = L.buf[L.bufpos]
  case c
  of 'a'..'z', 'A'..'Z', '\x80'..'\xFF', '0'..'9':
    getThing(L, tok, SymChars)
  of ' ', '\x09', '\x0B', '\x0C':
    getThing(L, tok, {' ', '\x09'})
    tok.kind = tkWhite
    if L.buf[L.bufpos] in {'\x0D', '\x0A'}:
      rawGetTok(L, tok)       # ignore spaces before \n
  of '\x0D', '\x0A':
    getIndent(L, tok)
  of '!', '\"', '#', '$', '%', '&', '\'',  '*', '+', ',', '-', '.',
     '/', ':', ';', '<', '=', '>', '?', '@', '\\', '^', '_', '`',
     '|', '~':
    getAdornment(L, tok)
    if len(tok.symbol) <= 3: tok.kind = tkPunct
  of '(', ')', '[', ']', '{', '}':
    getBracket(L, tok)
  else:
    tok.line = L.line
    tok.col = L.col
    if c == '\0':
      tok.kind = tkEof
    else:
      tok.kind = tkOther
      add(tok.symbol, c)
      inc(L.bufpos)
      inc(L.col)
  tok.col = max(tok.col - L.baseIndent, 0)

proc getTokens(buffer: string, skipPounds: bool, tokens: var TokenSeq): int =
  var L: Lexer
  var length = len(tokens)
  L.buf = cstring(buffer)
  L.line = 0                  # skip UTF-8 BOM
  if (L.buf[0] == '\xEF') and (L.buf[1] == '\xBB') and (L.buf[2] == '\xBF'):
    inc(L.bufpos, 3)
  L.skipPounds = skipPounds
  if skipPounds:
    if L.buf[L.bufpos] == '#':
      inc(L.bufpos)
      inc(result)
    if L.buf[L.bufpos] == '#':
      inc(L.bufpos)
      inc(result)
    L.baseIndent = 0
    while L.buf[L.bufpos] == ' ':
      inc(L.bufpos)
      inc(L.baseIndent)
      inc(result)
  while true:
    inc(length)
    setLen(tokens, length)
    rawGetTok(L, tokens[length - 1])
    if tokens[length - 1].kind == tkEof: break
  if tokens[0].kind == tkWhite:
    # BUGFIX
    tokens[0].ival = len(tokens[0].symbol)
    tokens[0].kind = tkIndent

type
  LevelMap = array[char, int]
  Substitution = object
    key*: string
    value*: PRstNode

  SharedState = object
    options: RstParseOptions    # parsing options
    uLevel, oLevel: int         # counters for the section levels
    subs: seq[Substitution]     # substitutions
    refs: seq[Substitution]     # references
    underlineToLevel: LevelMap  # Saves for each possible title adornment
                                # character its level in the
                                # current document.
                                # This is for single underline adornments.
    overlineToLevel: LevelMap   # Saves for each possible title adornment
                                # character its level in the current
                                # document.
                                # This is for over-underline adornments.
    msgHandler: MsgHandler      # How to handle errors.
    findFile: FindFileHandler   # How to find files.

  PSharedState = ref SharedState
  RstParser = object of RootObj
    idx*: int
    tok*: TokenSeq
    s*: PSharedState
    indentStack*: seq[int]
    filename*: string
    line*, col*: int
    hasToc*: bool

  EParseError* = object of ValueError

proc whichMsgClass*(k: MsgKind): MsgClass =
  ## returns which message class `k` belongs to.
  case ($k)[1]
  of 'e', 'E': result = mcError
  of 'w', 'W': result = mcWarning
  of 'h', 'H': result = mcHint
  else: assert false, "msgkind does not fit naming scheme"

proc defaultMsgHandler*(filename: string, line, col: int, msgkind: MsgKind,
                        arg: string) =
  let mc = msgkind.whichMsgClass
  let a = messages[msgkind] % arg
  let message = "$1($2, $3) $4: $5" % [filename, $line, $col, $mc, a]
  if mc == mcError: raise newException(EParseError, message)
  else: writeLine(stdout, message)

proc defaultFindFile*(filename: string): string =
  if fileExists(filename): result = filename
  else: result = ""

proc newSharedState(options: RstParseOptions,
                    findFile: FindFileHandler,
                    msgHandler: MsgHandler): PSharedState =
  new(result)
  result.subs = @[]
  result.refs = @[]
  result.options = options
  result.msgHandler = if not isNil(msgHandler): msgHandler else: defaultMsgHandler
  result.findFile = if not isNil(findFile): findFile else: defaultFindFile

proc findRelativeFile(p: RstParser; filename: string): string =
  result = p.filename.splitFile.dir / filename
  if not fileExists(result):
    result = p.s.findFile(filename)

proc rstMessage(p: RstParser, msgKind: MsgKind, arg: string) =
  p.s.msgHandler(p.filename, p.line + p.tok[p.idx].line,
                             p.col + p.tok[p.idx].col, msgKind, arg)

proc rstMessage(p: RstParser, msgKind: MsgKind, arg: string, line, col: int) =
  p.s.msgHandler(p.filename, p.line + line,
                             p.col + col, msgKind, arg)

proc rstMessage(p: RstParser, msgKind: MsgKind) =
  p.s.msgHandler(p.filename, p.line + p.tok[p.idx].line,
                             p.col + p.tok[p.idx].col, msgKind,
                             p.tok[p.idx].symbol)

proc currInd(p: RstParser): int =
  result = p.indentStack[high(p.indentStack)]

proc pushInd(p: var RstParser, ind: int) =
  add(p.indentStack, ind)

proc popInd(p: var RstParser) =
  if len(p.indentStack) > 1: setLen(p.indentStack, len(p.indentStack) - 1)

proc initParser(p: var RstParser, sharedState: PSharedState) =
  p.indentStack = @[0]
  p.tok = @[]
  p.idx = 0
  p.filename = ""
  p.hasToc = false
  p.col = 0
  p.line = 1
  p.s = sharedState

proc addNodesAux(n: PRstNode, result: var string) =
  if n.kind == rnLeaf:
    add(result, n.text)
  else:
    for i in countup(0, len(n) - 1): addNodesAux(n.sons[i], result)

proc addNodes(n: PRstNode): string =
  result = ""
  addNodesAux(n, result)

proc rstnodeToRefnameAux(n: PRstNode, r: var string, b: var bool) =
  template special(s) =
    if b:
      add(r, '-')
      b = false
    add(r, s)

  if n == nil: return
  if n.kind == rnLeaf:
    for i in countup(0, len(n.text) - 1):
      case n.text[i]
      of '0'..'9':
        if b:
          add(r, '-')
          b = false
        if len(r) == 0: add(r, 'Z')
        add(r, n.text[i])
      of 'a'..'z', '\128'..'\255':
        if b:
          add(r, '-')
          b = false
        add(r, n.text[i])
      of 'A'..'Z':
        if b:
          add(r, '-')
          b = false
        add(r, chr(ord(n.text[i]) - ord('A') + ord('a')))
      of '$': special "dollar"
      of '%': special "percent"
      of '&': special "amp"
      of '^': special "roof"
      of '!': special "emark"
      of '?': special "qmark"
      of '*': special "star"
      of '+': special "plus"
      of '-': special "minus"
      of '/': special "slash"
      of '\\': special "backslash"
      of '=': special "eq"
      of '<': special "lt"
      of '>': special "gt"
      of '~': special "tilde"
      of ':': special "colon"
      of '.': special "dot"
      of '@': special "at"
      of '|': special "bar"
      else:
        if len(r) > 0: b = true
  else:
    for i in countup(0, len(n) - 1): rstnodeToRefnameAux(n.sons[i], r, b)

proc rstnodeToRefname(n: PRstNode): string =
  result = ""
  var b = false
  rstnodeToRefnameAux(n, result, b)

proc findSub(p: var RstParser, n: PRstNode): int =
  var key = addNodes(n)
  # the spec says: if no exact match, try one without case distinction:
  for i in countup(0, high(p.s.subs)):
    if key == p.s.subs[i].key:
      return i
  for i in countup(0, high(p.s.subs)):
    if cmpIgnoreStyle(key, p.s.subs[i].key) == 0:
      return i
  result = -1

proc setSub(p: var RstParser, key: string, value: PRstNode) =
  var length = len(p.s.subs)
  for i in countup(0, length - 1):
    if key == p.s.subs[i].key:
      p.s.subs[i].value = value
      return
  setLen(p.s.subs, length + 1)
  p.s.subs[length].key = key
  p.s.subs[length].value = value

proc setRef(p: var RstParser, key: string, value: PRstNode) =
  var length = len(p.s.refs)
  for i in countup(0, length - 1):
    if key == p.s.refs[i].key:
      if p.s.refs[i].value.addNodes != value.addNodes:
        rstMessage(p, mwRedefinitionOfLabel, key)

      p.s.refs[i].value = value
      return
  setLen(p.s.refs, length + 1)
  p.s.refs[length].key = key
  p.s.refs[length].value = value

proc findRef(p: var RstParser, key: string): PRstNode =
  for i in countup(0, high(p.s.refs)):
    if key == p.s.refs[i].key:
      return p.s.refs[i].value

proc newLeaf(p: var RstParser): PRstNode =
  result = newRstNode(rnLeaf, p.tok[p.idx].symbol)

proc getReferenceName(p: var RstParser, endStr: string): PRstNode =
  var res = newRstNode(rnInner)
  while true:
    case p.tok[p.idx].kind
    of tkWord, tkOther, tkWhite:
      add(res, newLeaf(p))
    of tkPunct:
      if p.tok[p.idx].symbol == endStr:
        inc(p.idx)
        break
      else:
        add(res, newLeaf(p))
    else:
      rstMessage(p, meExpected, endStr)
      break
    inc(p.idx)
  result = res

proc untilEol(p: var RstParser): PRstNode =
  result = newRstNode(rnInner)
  while not (p.tok[p.idx].kind in {tkIndent, tkEof}):
    add(result, newLeaf(p))
    inc(p.idx)

proc expect(p: var RstParser, tok: string) =
  if p.tok[p.idx].symbol == tok: inc(p.idx)
  else: rstMessage(p, meExpected, tok)

proc isInlineMarkupEnd(p: RstParser, markup: string): bool =
  result = p.tok[p.idx].symbol == markup
  if not result:
    return                    # Rule 3:
  result = not (p.tok[p.idx - 1].kind in {tkIndent, tkWhite})
  if not result:
    return                    # Rule 4:
  result = (p.tok[p.idx + 1].kind in {tkIndent, tkWhite, tkEof}) or
      (p.tok[p.idx + 1].symbol[0] in
      {'\'', '\"', ')', ']', '}', '>', '-', '/', '\\', ':', '.', ',', ';', '!',
       '?', '_'})
  if not result:
    return                    # Rule 7:
  if p.idx > 0:
    if (markup != "``") and (p.tok[p.idx - 1].symbol == "\\"):
      result = false

proc isInlineMarkupStart(p: RstParser, markup: string): bool =
  var d: char
  result = p.tok[p.idx].symbol == markup
  if not result:
    return                    # Rule 1:
  result = (p.idx == 0) or (p.tok[p.idx - 1].kind in {tkIndent, tkWhite}) or
      (p.tok[p.idx - 1].symbol[0] in
      {'\'', '\"', '(', '[', '{', '<', '-', '/', ':', '_'})
  if not result:
    return                    # Rule 2:
  result = not (p.tok[p.idx + 1].kind in {tkIndent, tkWhite, tkEof})
  if not result:
    return                    # Rule 5 & 7:
  if p.idx > 0:
    if p.tok[p.idx - 1].symbol == "\\":
      result = false
    else:
      var c = p.tok[p.idx - 1].symbol[0]
      case c
      of '\'', '\"': d = c
      of '(': d = ')'
      of '[': d = ']'
      of '{': d = '}'
      of '<': d = '>'
      else: d = '\0'
      if d != '\0': result = p.tok[p.idx + 1].symbol[0] != d

proc match(p: RstParser, start: int, expr: string): bool =
  # regular expressions are:
  # special char     exact match
  # 'w'              tkWord
  # ' '              tkWhite
  # 'a'              tkAdornment
  # 'i'              tkIndent
  # 'p'              tkPunct
  # 'T'              always true
  # 'E'              whitespace, indent or eof
  # 'e'              tkWord or '#' (for enumeration lists)
  var i = 0
  var j = start
  var last = len(expr) - 1
  while i <= last:
    case expr[i]
    of 'w': result = p.tok[j].kind == tkWord
    of ' ': result = p.tok[j].kind == tkWhite
    of 'i': result = p.tok[j].kind == tkIndent
    of 'p': result = p.tok[j].kind == tkPunct
    of 'a': result = p.tok[j].kind == tkAdornment
    of 'o': result = p.tok[j].kind == tkOther
    of 'T': result = true
    of 'E': result = p.tok[j].kind in {tkEof, tkWhite, tkIndent}
    of 'e':
      result = (p.tok[j].kind == tkWord) or (p.tok[j].symbol == "#")
      if result:
        case p.tok[j].symbol[0]
        of 'a'..'z', 'A'..'Z', '#': result = len(p.tok[j].symbol) == 1
        of '0'..'9': result = allCharsInSet(p.tok[j].symbol, {'0'..'9'})
        else: result = false
    else:
      var c = expr[i]
      var length = 0
      while (i <= last) and (expr[i] == c):
        inc(i)
        inc(length)
      dec(i)
      result = (p.tok[j].kind in {tkPunct, tkAdornment}) and
          (len(p.tok[j].symbol) == length) and (p.tok[j].symbol[0] == c)
    if not result: return
    inc(j)
    inc(i)
  result = true

proc fixupEmbeddedRef(n, a, b: PRstNode) =
  var sep = - 1
  for i in countdown(len(n) - 2, 0):
    if n.sons[i].text == "<":
      sep = i
      break
  var incr = if (sep > 0) and (n.sons[sep - 1].text[0] == ' '): 2 else: 1
  for i in countup(0, sep - incr): add(a, n.sons[i])
  for i in countup(sep + 1, len(n) - 2): add(b, n.sons[i])

proc parsePostfix(p: var RstParser, n: PRstNode): PRstNode =
  result = n
  if isInlineMarkupEnd(p, "_") or isInlineMarkupEnd(p, "__"):
    inc(p.idx)
    if p.tok[p.idx-2].symbol == "`" and p.tok[p.idx-3].symbol == ">":
      var a = newRstNode(rnInner)
      var b = newRstNode(rnInner)
      fixupEmbeddedRef(n, a, b)
      if len(a) == 0:
        result = newRstNode(rnStandaloneHyperlink)
        add(result, b)
      else:
        result = newRstNode(rnHyperlink)
        add(result, a)
        add(result, b)
        setRef(p, rstnodeToRefname(a), b)
    elif n.kind == rnInterpretedText:
      n.kind = rnRef
    else:
      result = newRstNode(rnRef)
      add(result, n)
  elif match(p, p.idx, ":w:"):
    # a role:
    if p.tok[p.idx + 1].symbol == "idx":
      n.kind = rnIdx
    elif p.tok[p.idx + 1].symbol == "literal":
      n.kind = rnInlineLiteral
    elif p.tok[p.idx + 1].symbol == "strong":
      n.kind = rnStrongEmphasis
    elif p.tok[p.idx + 1].symbol == "emphasis":
      n.kind = rnEmphasis
    elif (p.tok[p.idx + 1].symbol == "sub") or
        (p.tok[p.idx + 1].symbol == "subscript"):
      n.kind = rnSub
    elif (p.tok[p.idx + 1].symbol == "sup") or
        (p.tok[p.idx + 1].symbol == "supscript"):
      n.kind = rnSup
    else:
      result = newRstNode(rnGeneralRole)
      n.kind = rnInner
      add(result, n)
      add(result, newRstNode(rnLeaf, p.tok[p.idx + 1].symbol))
    inc(p.idx, 3)

proc matchVerbatim(p: RstParser, start: int, expr: string): int =
  result = start
  var j = 0
  while j < expr.len and result < p.tok.len and
        continuesWith(expr, p.tok[result].symbol, j):
    inc j, p.tok[result].symbol.len
    inc result
  if j < expr.len: result = 0

proc parseSmiley(p: var RstParser): PRstNode =
  if p.tok[p.idx].symbol[0] notin SmileyStartChars: return
  for key, val in items(Smilies):
    let m = matchVerbatim(p, p.idx, key)
    if m > 0:
      p.idx = m
      result = newRstNode(rnSmiley)
      result.text = val
      return

when false:
  const
    urlChars = {'A'..'Z', 'a'..'z', '0'..'9', ':', '#', '@', '%', '/', ';',
                 '$', '(', ')', '~', '_', '?', '+', '-', '=', '\\', '.', '&',
                 '\128'..'\255'}

proc isUrl(p: RstParser, i: int): bool =
  result = (p.tok[i+1].symbol == ":") and (p.tok[i+2].symbol == "//") and
    (p.tok[i+3].kind == tkWord) and
    (p.tok[i].symbol in ["http", "https", "ftp", "telnet", "file"])

proc parseUrl(p: var RstParser, father: PRstNode) =
  #if p.tok[p.idx].symbol[strStart] == '<':
  if isUrl(p, p.idx):
    var n = newRstNode(rnStandaloneHyperlink)
    while true:
      case p.tok[p.idx].kind
      of tkWord, tkAdornment, tkOther: discard
      of tkPunct:
        if p.tok[p.idx+1].kind notin {tkWord, tkAdornment, tkOther, tkPunct}:
          break
      else: break
      add(n, newLeaf(p))
      inc(p.idx)
    add(father, n)
  else:
    var n = newLeaf(p)
    inc(p.idx)
    if p.tok[p.idx].symbol == "_": n = parsePostfix(p, n)
    add(father, n)

proc parseBackslash(p: var RstParser, father: PRstNode) =
  assert(p.tok[p.idx].kind == tkPunct)
  if p.tok[p.idx].symbol == "\\\\":
    add(father, newRstNode(rnLeaf, "\\"))
    inc(p.idx)
  elif p.tok[p.idx].symbol == "\\":
    # XXX: Unicode?
    inc(p.idx)
    if p.tok[p.idx].kind != tkWhite: add(father, newLeaf(p))
    if p.tok[p.idx].kind != tkEof: inc(p.idx)
  else:
    add(father, newLeaf(p))
    inc(p.idx)

when false:
  proc parseAdhoc(p: var RstParser, father: PRstNode, verbatim: bool) =
    if not verbatim and isURL(p, p.idx):
      var n = newRstNode(rnStandaloneHyperlink)
      while true:
        case p.tok[p.idx].kind
        of tkWord, tkAdornment, tkOther: nil
        of tkPunct:
          if p.tok[p.idx+1].kind notin {tkWord, tkAdornment, tkOther, tkPunct}:
            break
        else: break
        add(n, newLeaf(p))
        inc(p.idx)
      add(father, n)
    elif not verbatim and roSupportSmilies in p.sharedState.options:
      let n = parseSmiley(p)
      if s != nil:
        add(father, n)
    else:
      var n = newLeaf(p)
      inc(p.idx)
      if p.tok[p.idx].symbol == "_": n = parsePostfix(p, n)
      add(father, n)

proc parseUntil(p: var RstParser, father: PRstNode, postfix: string,
                interpretBackslash: bool) =
  let
    line = p.tok[p.idx].line
    col = p.tok[p.idx].col
  inc p.idx
  while true:
    case p.tok[p.idx].kind
    of tkPunct:
      if isInlineMarkupEnd(p, postfix):
        inc(p.idx)
        break
      elif interpretBackslash:
        parseBackslash(p, father)
      else:
        add(father, newLeaf(p))
        inc(p.idx)
    of tkAdornment, tkWord, tkOther:
      add(father, newLeaf(p))
      inc(p.idx)
    of tkIndent:
      add(father, newRstNode(rnLeaf, " "))
      inc(p.idx)
      if p.tok[p.idx].kind == tkIndent:
        rstMessage(p, meExpected, postfix, line, col)
        break
    of tkWhite:
      add(father, newRstNode(rnLeaf, " "))
      inc(p.idx)
    else: rstMessage(p, meExpected, postfix, line, col)

proc parseMarkdownCodeblock(p: var RstParser): PRstNode =
  var args = newRstNode(rnDirArg)
  if p.tok[p.idx].kind == tkWord:
    add(args, newLeaf(p))
    inc(p.idx)
  else:
    args = nil
  var n = newRstNode(rnLeaf, "")
  while true:
    case p.tok[p.idx].kind
    of tkEof:
      rstMessage(p, meExpected, "```")
      break
    of tkPunct:
      if p.tok[p.idx].symbol == "```":
        inc(p.idx)
        break
      else:
        add(n.text, p.tok[p.idx].symbol)
        inc(p.idx)
    else:
      add(n.text, p.tok[p.idx].symbol)
      inc(p.idx)
  var lb = newRstNode(rnLiteralBlock)
  add(lb, n)
  result = newRstNode(rnCodeBlock)
  add(result, args)
  add(result, PRstNode(nil))
  add(result, lb)

proc parseMarkdownLink(p: var RstParser; father: PRstNode): bool =
  result = true
  var desc, link = ""
  var i = p.idx

  template parse(endToken, dest) =
    inc i # skip begin token
    while true:
      if p.tok[i].kind in {tkEof, tkIndent}: return false
      if p.tok[i].symbol == endToken: break
      dest.add p.tok[i].symbol
      inc i
    inc i # skip end token

  parse("]", desc)
  if p.tok[i].symbol != "(": return false
  parse(")", link)
  let child = newRstNode(rnHyperlink)
  child.add desc
  child.add link
  # only commit if we detected no syntax error:
  father.add child
  p.idx = i
  result = true

proc parseInline(p: var RstParser, father: PRstNode) =
  case p.tok[p.idx].kind
  of tkPunct:
    if isInlineMarkupStart(p, "***"):
      var n = newRstNode(rnTripleEmphasis)
      parseUntil(p, n, "***", true)
      add(father, n)
    elif isInlineMarkupStart(p, "**"):
      var n = newRstNode(rnStrongEmphasis)
      parseUntil(p, n, "**", true)
      add(father, n)
    elif isInlineMarkupStart(p, "*"):
      var n = newRstNode(rnEmphasis)
      parseUntil(p, n, "*", true)
      add(father, n)
    elif roSupportMarkdown in p.s.options and p.tok[p.idx].symbol == "```":
      inc(p.idx)
      add(father, parseMarkdownCodeblock(p))
    elif isInlineMarkupStart(p, "``"):
      var n = newRstNode(rnInlineLiteral)
      parseUntil(p, n, "``", false)
      add(father, n)
    elif isInlineMarkupStart(p, "`"):
      var n = newRstNode(rnInterpretedText)
      parseUntil(p, n, "`", true)
      n = parsePostfix(p, n)
      add(father, n)
    elif isInlineMarkupStart(p, "|"):
      var n = newRstNode(rnSubstitutionReferences)
      parseUntil(p, n, "|", false)
      add(father, n)
    elif roSupportMarkdown in p.s.options and
        p.tok[p.idx].symbol == "[" and p.tok[p.idx+1].symbol != "[" and
        parseMarkdownLink(p, father):
      discard "parseMarkdownLink already processed it"
    else:
      if roSupportSmilies in p.s.options:
        let n = parseSmiley(p)
        if n != nil:
          add(father, n)
          return
      parseBackslash(p, father)
  of tkWord:
    if roSupportSmilies in p.s.options:
      let n = parseSmiley(p)
      if n != nil:
        add(father, n)
        return
    parseUrl(p, father)
  of tkAdornment, tkOther, tkWhite:
    if roSupportSmilies in p.s.options:
      let n = parseSmiley(p)
      if n != nil:
        add(father, n)
        return
    add(father, newLeaf(p))
    inc(p.idx)
  else: discard

proc getDirective(p: var RstParser): string =
  if p.tok[p.idx].kind == tkWhite and p.tok[p.idx+1].kind == tkWord:
    var j = p.idx
    inc(p.idx)
    result = p.tok[p.idx].symbol
    inc(p.idx)
    while p.tok[p.idx].kind in {tkWord, tkPunct, tkAdornment, tkOther}:
      if p.tok[p.idx].symbol == "::": break
      add(result, p.tok[p.idx].symbol)
      inc(p.idx)
    if p.tok[p.idx].kind == tkWhite: inc(p.idx)
    if p.tok[p.idx].symbol == "::":
      inc(p.idx)
      if (p.tok[p.idx].kind == tkWhite): inc(p.idx)
    else:
      p.idx = j               # set back
      result = ""             # error
  else:
    result = ""

proc parseComment(p: var RstParser): PRstNode =
  case p.tok[p.idx].kind
  of tkIndent, tkEof:
    if p.tok[p.idx].kind != tkEof and p.tok[p.idx + 1].kind == tkIndent:
      inc(p.idx)              # empty comment
    else:
      var indent = p.tok[p.idx].ival
      while true:
        case p.tok[p.idx].kind
        of tkEof:
          break
        of tkIndent:
          if (p.tok[p.idx].ival < indent): break
        else:
          discard
        inc(p.idx)
  else:
    while p.tok[p.idx].kind notin {tkIndent, tkEof}: inc(p.idx)
  result = nil

type
  DirKind = enum             # must be ordered alphabetically!
    dkNone, dkAuthor, dkAuthors, dkCode, dkCodeBlock, dkContainer, dkContents,
    dkFigure, dkImage, dkInclude, dkIndex, dkRaw, dkTitle

const
  DirIds: array[0..12, string] = ["", "author", "authors", "code",
    "code-block", "container", "contents", "figure", "image", "include",
    "index", "raw", "title"]

proc getDirKind(s: string): DirKind =
  let i = find(DirIds, s)
  if i >= 0: result = DirKind(i)
  else: result = dkNone

proc parseLine(p: var RstParser, father: PRstNode) =
  while true:
    case p.tok[p.idx].kind
    of tkWhite, tkWord, tkOther, tkPunct: parseInline(p, father)
    else: break

proc parseUntilNewline(p: var RstParser, father: PRstNode) =
  while true:
    case p.tok[p.idx].kind
    of tkWhite, tkWord, tkAdornment, tkOther, tkPunct: parseInline(p, father)
    of tkEof, tkIndent: break

proc parseSection(p: var RstParser, result: PRstNode) {.gcsafe.}
proc parseField(p: var RstParser): PRstNode =
  ## Returns a parsed rnField node.
  ##
  ## rnField nodes have two children nodes, a rnFieldName and a rnFieldBody.
  result = newRstNode(rnField)
  var col = p.tok[p.idx].col
  var fieldname = newRstNode(rnFieldName)
  parseUntil(p, fieldname, ":", false)
  var fieldbody = newRstNode(rnFieldBody)
  if p.tok[p.idx].kind != tkIndent: parseLine(p, fieldbody)
  if p.tok[p.idx].kind == tkIndent:
    var indent = p.tok[p.idx].ival
    if indent > col:
      pushInd(p, indent)
      parseSection(p, fieldbody)
      popInd(p)
  add(result, fieldname)
  add(result, fieldbody)

proc parseFields(p: var RstParser): PRstNode =
  ## Parses fields for a section or directive block.
  ##
  ## This proc may return nil if the parsing doesn't find anything of value,
  ## otherwise it will return a node of rnFieldList type with children.
  result = nil
  var atStart = p.idx == 0 and p.tok[0].symbol == ":"
  if (p.tok[p.idx].kind == tkIndent) and (p.tok[p.idx + 1].symbol == ":") or
      atStart:
    var col = if atStart: p.tok[p.idx].col else: p.tok[p.idx].ival
    result = newRstNode(rnFieldList)
    if not atStart: inc(p.idx)
    while true:
      add(result, parseField(p))
      if (p.tok[p.idx].kind == tkIndent) and (p.tok[p.idx].ival == col) and
          (p.tok[p.idx + 1].symbol == ":"):
        inc(p.idx)
      else:
        break

proc getFieldValue*(n: PRstNode): string =
  ## Returns the value of a specific ``rnField`` node.
  ##
  ## This proc will assert if the node is not of the expected type. The empty
  ## string will be returned as a minimum. Any value in the rst will be
  ## stripped form leading/trailing whitespace.
  assert n.kind == rnField
  assert n.len == 2
  assert n.sons[0].kind == rnFieldName
  assert n.sons[1].kind == rnFieldBody
  result = addNodes(n.sons[1]).strip

proc getFieldValue(n: PRstNode, fieldname: string): string =
  result = ""
  if n.sons[1] == nil: return
  if (n.sons[1].kind != rnFieldList):
    #InternalError("getFieldValue (2): " & $n.sons[1].kind)
    # We don't like internal errors here anymore as that would break the forum!
    return
  for i in countup(0, len(n.sons[1]) - 1):
    var f = n.sons[1].sons[i]
    if cmpIgnoreStyle(addNodes(f.sons[0]), fieldname) == 0:
      result = addNodes(f.sons[1])
      if result == "": result = "\x01\x01" # indicates that the field exists
      return

proc getArgument(n: PRstNode): string =
  if n.sons[0] == nil: result = ""
  else: result = addNodes(n.sons[0])

proc parseDotDot(p: var RstParser): PRstNode {.gcsafe.}
proc parseLiteralBlock(p: var RstParser): PRstNode =
  result = newRstNode(rnLiteralBlock)
  var n = newRstNode(rnLeaf, "")
  if p.tok[p.idx].kind == tkIndent:
    var indent = p.tok[p.idx].ival
    inc(p.idx)
    while true:
      case p.tok[p.idx].kind
      of tkEof:
        break
      of tkIndent:
        if (p.tok[p.idx].ival < indent):
          break
        else:
          add(n.text, "\n")
          add(n.text, spaces(p.tok[p.idx].ival - indent))
          inc(p.idx)
      else:
        add(n.text, p.tok[p.idx].symbol)
        inc(p.idx)
  else:
    while not (p.tok[p.idx].kind in {tkIndent, tkEof}):
      add(n.text, p.tok[p.idx].symbol)
      inc(p.idx)
  add(result, n)

proc getLevel(map: var LevelMap, lvl: var int, c: char): int =
  if map[c] == 0:
    inc(lvl)
    map[c] = lvl
  result = map[c]

proc tokenAfterNewline(p: RstParser): int =
  result = p.idx
  while true:
    case p.tok[result].kind
    of tkEof:
      break
    of tkIndent:
      inc(result)
      break
    else: inc(result)

proc isLineBlock(p: RstParser): bool =
  var j = tokenAfterNewline(p)
  result = (p.tok[p.idx].col == p.tok[j].col) and (p.tok[j].symbol == "|") or
      (p.tok[j].col > p.tok[p.idx].col)

proc predNL(p: RstParser): bool =
  result = true
  if p.idx > 0:
    result = p.tok[p.idx-1].kind == tkIndent and
        p.tok[p.idx-1].ival == currInd(p)

proc isDefList(p: RstParser): bool =
  var j = tokenAfterNewline(p)
  result = (p.tok[p.idx].col < p.tok[j].col) and
      (p.tok[j].kind in {tkWord, tkOther, tkPunct}) and
      (p.tok[j - 2].symbol != "::")

proc isOptionList(p: RstParser): bool =
  result = match(p, p.idx, "-w") or match(p, p.idx, "--w") or
           match(p, p.idx, "/w") or match(p, p.idx, "//w")

proc isMarkdownHeadlinePattern(s: string): bool =
  if s.len >= 1 and s.len <= 6:
    for c in s:
      if c != '#': return false
    result = true

proc isMarkdownHeadline(p: RstParser): bool =
  if roSupportMarkdown in p.s.options:
    if isMarkdownHeadlinePattern(p.tok[p.idx].symbol) and p.tok[p.idx+1].kind == tkWhite:
      if p.tok[p.idx+2].kind in {tkWord, tkOther, tkPunct}:
        result = true

proc whichSection(p: RstParser): RstNodeKind =
  case p.tok[p.idx].kind
  of tkAdornment:
    if match(p, p.idx + 1, "ii"): result = rnTransition
    elif match(p, p.idx + 1, " a"): result = rnTable
    elif match(p, p.idx + 1, "i"): result = rnOverline
    elif isMarkdownHeadline(p):
      result = rnHeadline
    else:
      result = rnLeaf
  of tkPunct:
    if isMarkdownHeadline(p):
      result = rnHeadline
    elif match(p, tokenAfterNewline(p), "ai"):
      result = rnHeadline
    elif p.tok[p.idx].symbol == "::":
      result = rnLiteralBlock
    elif predNL(p) and
        ((p.tok[p.idx].symbol == "+") or (p.tok[p.idx].symbol == "*") or
        (p.tok[p.idx].symbol == "-")) and (p.tok[p.idx + 1].kind == tkWhite):
      result = rnBulletList
    elif (p.tok[p.idx].symbol == "|") and isLineBlock(p):
      result = rnLineBlock
    elif (p.tok[p.idx].symbol == "..") and predNL(p):
      result = rnDirective
    elif match(p, p.idx, ":w:") and predNL(p):
      # (p.tok[p.idx].symbol == ":")
      result = rnFieldList
    elif match(p, p.idx, "(e) ") or match(p, p.idx, "e. "):
      result = rnEnumList
    elif match(p, p.idx, "+a+"):
      result = rnGridTable
      rstMessage(p, meGridTableNotImplemented)
    elif isDefList(p):
      result = rnDefList
    elif isOptionList(p):
      result = rnOptionList
    else:
      result = rnParagraph
  of tkWord, tkOther, tkWhite:
    if match(p, tokenAfterNewline(p), "ai"): result = rnHeadline
    elif match(p, p.idx, "e) ") or match(p, p.idx, "e. "): result = rnEnumList
    elif isDefList(p): result = rnDefList
    else: result = rnParagraph
  else: result = rnLeaf

proc parseLineBlock(p: var RstParser): PRstNode =
  result = nil
  if p.tok[p.idx + 1].kind == tkWhite:
    var col = p.tok[p.idx].col
    result = newRstNode(rnLineBlock)
    pushInd(p, p.tok[p.idx + 2].col)
    inc(p.idx, 2)
    while true:
      var item = newRstNode(rnLineBlockItem)
      parseSection(p, item)
      add(result, item)
      if (p.tok[p.idx].kind == tkIndent) and (p.tok[p.idx].ival == col) and
          (p.tok[p.idx + 1].symbol == "|") and
          (p.tok[p.idx + 2].kind == tkWhite):
        inc(p.idx, 3)
      else:
        break
    popInd(p)

proc parseParagraph(p: var RstParser, result: PRstNode) =
  while true:
    case p.tok[p.idx].kind
    of tkIndent:
      if p.tok[p.idx + 1].kind == tkIndent:
        inc(p.idx)
        break
      elif (p.tok[p.idx].ival == currInd(p)):
        inc(p.idx)
        case whichSection(p)
        of rnParagraph, rnLeaf, rnHeadline, rnOverline, rnDirective:
          add(result, newRstNode(rnLeaf, " "))
        of rnLineBlock:
          addIfNotNil(result, parseLineBlock(p))
        else: break
      else:
        break
    of tkPunct:
      if (p.tok[p.idx].symbol == "::") and
          (p.tok[p.idx + 1].kind == tkIndent) and
          (currInd(p) < p.tok[p.idx + 1].ival):
        add(result, newRstNode(rnLeaf, ":"))
        inc(p.idx)            # skip '::'
        add(result, parseLiteralBlock(p))
        break
      else:
        parseInline(p, result)
    of tkWhite, tkWord, tkAdornment, tkOther:
      parseInline(p, result)
    else: break

proc parseHeadline(p: var RstParser): PRstNode =
  result = newRstNode(rnHeadline)
  if isMarkdownHeadline(p):
    result.level = p.tok[p.idx].symbol.len
    assert(p.tok[p.idx+1].kind == tkWhite)
    inc p.idx, 2
    parseUntilNewline(p, result)
  else:
    parseUntilNewline(p, result)
    assert(p.tok[p.idx].kind == tkIndent)
    assert(p.tok[p.idx + 1].kind == tkAdornment)
    var c = p.tok[p.idx + 1].symbol[0]
    inc(p.idx, 2)
    result.level = getLevel(p.s.underlineToLevel, p.s.uLevel, c)

type
  IntSeq = seq[int]

proc tokEnd(p: RstParser): int =
  result = p.tok[p.idx].col + len(p.tok[p.idx].symbol) - 1

proc getColumns(p: var RstParser, cols: var IntSeq) =
  var L = 0
  while true:
    inc(L)
    setLen(cols, L)
    cols[L - 1] = tokEnd(p)
    assert(p.tok[p.idx].kind == tkAdornment)
    inc(p.idx)
    if p.tok[p.idx].kind != tkWhite: break
    inc(p.idx)
    if p.tok[p.idx].kind != tkAdornment: break
  if p.tok[p.idx].kind == tkIndent: inc(p.idx)
  # last column has no limit:
  cols[L - 1] = 32000

proc parseDoc(p: var RstParser): PRstNode {.gcsafe.}

proc parseSimpleTable(p: var RstParser): PRstNode =
  var
    cols: IntSeq
    row: seq[string]
    i, last, line: int
    c: char
    q: RstParser
    a, b: PRstNode
  result = newRstNode(rnTable)
  cols = @[]
  row = @[]
  a = nil
  c = p.tok[p.idx].symbol[0]
  while true:
    if p.tok[p.idx].kind == tkAdornment:
      last = tokenAfterNewline(p)
      if p.tok[last].kind in {tkEof, tkIndent}:
        # skip last adornment line:
        p.idx = last
        break
      getColumns(p, cols)
      setLen(row, len(cols))
      if a != nil:
        for j in 0..len(a)-1: a.sons[j].kind = rnTableHeaderCell
    if p.tok[p.idx].kind == tkEof: break
    for j in countup(0, high(row)): row[j] = ""
    # the following while loop iterates over the lines a single cell may span:
    line = p.tok[p.idx].line
    while true:
      i = 0
      while not (p.tok[p.idx].kind in {tkIndent, tkEof}):
        if (tokEnd(p) <= cols[i]):
          add(row[i], p.tok[p.idx].symbol)
          inc(p.idx)
        else:
          if p.tok[p.idx].kind == tkWhite: inc(p.idx)
          inc(i)
      if p.tok[p.idx].kind == tkIndent: inc(p.idx)
      if tokEnd(p) <= cols[0]: break
      if p.tok[p.idx].kind in {tkEof, tkAdornment}: break
      for j in countup(1, high(row)): add(row[j], '\x0A')
    a = newRstNode(rnTableRow)
    for j in countup(0, high(row)):
      initParser(q, p.s)
      q.col = cols[j]
      q.line = line - 1
      q.filename = p.filename
      q.col += getTokens(row[j], false, q.tok)
      b = newRstNode(rnTableDataCell)
      add(b, parseDoc(q))
      add(a, b)
    add(result, a)

proc parseTransition(p: var RstParser): PRstNode =
  result = newRstNode(rnTransition)
  inc(p.idx)
  if p.tok[p.idx].kind == tkIndent: inc(p.idx)
  if p.tok[p.idx].kind == tkIndent: inc(p.idx)

proc parseOverline(p: var RstParser): PRstNode =
  var c = p.tok[p.idx].symbol[0]
  inc(p.idx, 2)
  result = newRstNode(rnOverline)
  while true:
    parseUntilNewline(p, result)
    if p.tok[p.idx].kind == tkIndent:
      inc(p.idx)
      if p.tok[p.idx - 1].ival > currInd(p):
        add(result, newRstNode(rnLeaf, " "))
      else:
        break
    else:
      break
  result.level = getLevel(p.s.overlineToLevel, p.s.oLevel, c)
  if p.tok[p.idx].kind == tkAdornment:
    inc(p.idx)                # XXX: check?
    if p.tok[p.idx].kind == tkIndent: inc(p.idx)

proc parseBulletList(p: var RstParser): PRstNode =
  result = nil
  if p.tok[p.idx + 1].kind == tkWhite:
    var bullet = p.tok[p.idx].symbol
    var col = p.tok[p.idx].col
    result = newRstNode(rnBulletList)
    pushInd(p, p.tok[p.idx + 2].col)
    inc(p.idx, 2)
    while true:
      var item = newRstNode(rnBulletItem)
      parseSection(p, item)
      add(result, item)
      if (p.tok[p.idx].kind == tkIndent) and (p.tok[p.idx].ival == col) and
          (p.tok[p.idx + 1].symbol == bullet) and
          (p.tok[p.idx + 2].kind == tkWhite):
        inc(p.idx, 3)
      else:
        break
    popInd(p)

proc parseOptionList(p: var RstParser): PRstNode =
  result = newRstNode(rnOptionList)
  while true:
    if isOptionList(p):
      var a = newRstNode(rnOptionGroup)
      var b = newRstNode(rnDescription)
      var c = newRstNode(rnOptionListItem)
      if match(p, p.idx, "//w"): inc(p.idx)
      while not (p.tok[p.idx].kind in {tkIndent, tkEof}):
        if (p.tok[p.idx].kind == tkWhite) and (len(p.tok[p.idx].symbol) > 1):
          inc(p.idx)
          break
        add(a, newLeaf(p))
        inc(p.idx)
      var j = tokenAfterNewline(p)
      if (j > 0) and (p.tok[j - 1].kind == tkIndent) and
          (p.tok[j - 1].ival > currInd(p)):
        pushInd(p, p.tok[j - 1].ival)
        parseSection(p, b)
        popInd(p)
      else:
        parseLine(p, b)
      if (p.tok[p.idx].kind == tkIndent): inc(p.idx)
      add(c, a)
      add(c, b)
      add(result, c)
    else:
      break

proc parseDefinitionList(p: var RstParser): PRstNode =
  result = nil
  var j = tokenAfterNewline(p) - 1
  if (j >= 1) and (p.tok[j].kind == tkIndent) and
      (p.tok[j].ival > currInd(p)) and (p.tok[j - 1].symbol != "::"):
    var col = p.tok[p.idx].col
    result = newRstNode(rnDefList)
    while true:
      j = p.idx
      var a = newRstNode(rnDefName)
      parseLine(p, a)
      if (p.tok[p.idx].kind == tkIndent) and
          (p.tok[p.idx].ival > currInd(p)) and
          (p.tok[p.idx + 1].symbol != "::") and
          not (p.tok[p.idx + 1].kind in {tkIndent, tkEof}):
        pushInd(p, p.tok[p.idx].ival)
        var b = newRstNode(rnDefBody)
        parseSection(p, b)
        var c = newRstNode(rnDefItem)
        add(c, a)
        add(c, b)
        add(result, c)
        popInd(p)
      else:
        p.idx = j
        break
      if (p.tok[p.idx].kind == tkIndent) and (p.tok[p.idx].ival == col):
        inc(p.idx)
        j = tokenAfterNewline(p) - 1
        if j >= 1 and p.tok[j].kind == tkIndent and p.tok[j].ival > col and
            p.tok[j-1].symbol != "::" and p.tok[j+1].kind != tkIndent:
          discard
        else:
          break
    if len(result) == 0: result = nil

proc parseEnumList(p: var RstParser): PRstNode =
  const
    wildcards: array[0..2, string] = ["(e) ", "e) ", "e. "]
    wildpos: array[0..2, int] = [1, 0, 0]
  result = nil
  var w = 0
  while w <= 2:
    if match(p, p.idx, wildcards[w]): break
    inc(w)
  if w <= 2:
    var col = p.tok[p.idx].col
    result = newRstNode(rnEnumList)
    inc(p.idx, wildpos[w] + 3)
    var j = tokenAfterNewline(p)
    if (p.tok[j].col == p.tok[p.idx].col) or match(p, j, wildcards[w]):
      pushInd(p, p.tok[p.idx].col)
      while true:
        var item = newRstNode(rnEnumItem)
        parseSection(p, item)
        add(result, item)
        if (p.tok[p.idx].kind == tkIndent) and (p.tok[p.idx].ival == col) and
            match(p, p.idx + 1, wildcards[w]):
          inc(p.idx, wildpos[w] + 4)
        else:
          break
      popInd(p)
    else:
      dec(p.idx, wildpos[w] + 3)
      result = nil

proc sonKind(father: PRstNode, i: int): RstNodeKind =
  result = rnLeaf
  if i < len(father): result = father.sons[i].kind

proc parseSection(p: var RstParser, result: PRstNode) =
  while true:
    var leave = false
    assert(p.idx >= 0)
    while p.tok[p.idx].kind == tkIndent:
      if currInd(p) == p.tok[p.idx].ival:
        inc(p.idx)
      elif p.tok[p.idx].ival > currInd(p):
        pushInd(p, p.tok[p.idx].ival)
        var a = newRstNode(rnBlockQuote)
        parseSection(p, a)
        add(result, a)
        popInd(p)
      else:
        leave = true
        break
    if leave or p.tok[p.idx].kind == tkEof: break
    var a: PRstNode = nil
    var k = whichSection(p)
    case k
    of rnLiteralBlock:
      inc(p.idx)              # skip '::'
      a = parseLiteralBlock(p)
    of rnBulletList: a = parseBulletList(p)
    of rnLineBlock: a = parseLineBlock(p)
    of rnDirective: a = parseDotDot(p)
    of rnEnumList: a = parseEnumList(p)
    of rnLeaf: rstMessage(p, meNewSectionExpected)
    of rnParagraph: discard
    of rnDefList: a = parseDefinitionList(p)
    of rnFieldList:
      if p.idx > 0: dec(p.idx)
      a = parseFields(p)
    of rnTransition: a = parseTransition(p)
    of rnHeadline: a = parseHeadline(p)
    of rnOverline: a = parseOverline(p)
    of rnTable: a = parseSimpleTable(p)
    of rnOptionList: a = parseOptionList(p)
    else:
      #InternalError("rst.parseSection()")
      discard
    if a == nil and k != rnDirective:
      a = newRstNode(rnParagraph)
      parseParagraph(p, a)
    addIfNotNil(result, a)
  if sonKind(result, 0) == rnParagraph and sonKind(result, 1) != rnParagraph:
    result.sons[0].kind = rnInner

proc parseSectionWrapper(p: var RstParser): PRstNode =
  result = newRstNode(rnInner)
  parseSection(p, result)
  while (result.kind == rnInner) and (len(result) == 1):
    result = result.sons[0]

proc `$`(t: Token): string =
  result = $t.kind & ' ' & t.symbol

proc parseDoc(p: var RstParser): PRstNode =
  result = parseSectionWrapper(p)
  if p.tok[p.idx].kind != tkEof:
    when false:
      assert isAllocatedPtr(cast[pointer](p.tok))
      for i in 0 .. high(p.tok):
        assert isNil(p.tok[i].symbol) or
               isAllocatedPtr(cast[pointer](p.tok[i].symbol))
      echo "index: ", p.idx, " length: ", high(p.tok), "##",
          p.tok[p.idx-1], p.tok[p.idx], p.tok[p.idx+1]
    #assert isAllocatedPtr(cast[pointer](p.indentStack))
    rstMessage(p, meGeneralParseError)

type
  DirFlag = enum
    hasArg, hasOptions, argIsFile, argIsWord
  DirFlags = set[DirFlag]
  SectionParser = proc (p: var RstParser): PRstNode {.nimcall.}

proc parseDirective(p: var RstParser, flags: DirFlags): PRstNode =
  ## Parses arguments and options for a directive block.
  ##
  ## A directive block will always have three sons: the arguments for the
  ## directive (rnDirArg), the options (rnFieldList) and the block
  ## (rnLineBlock). This proc parses the two first nodes, the block is left to
  ## the outer `parseDirective` call.
  ##
  ## Both rnDirArg and rnFieldList children nodes might be nil, so you need to
  ## check them before accessing.
  result = newRstNode(rnDirective)
  var args: PRstNode = nil
  var options: PRstNode = nil
  if hasArg in flags:
    args = newRstNode(rnDirArg)
    if argIsFile in flags:
      while true:
        case p.tok[p.idx].kind
        of tkWord, tkOther, tkPunct, tkAdornment:
          add(args, newLeaf(p))
          inc(p.idx)
        else: break
    elif argIsWord in flags:
      while p.tok[p.idx].kind == tkWhite: inc(p.idx)
      if p.tok[p.idx].kind == tkWord:
        add(args, newLeaf(p))
        inc(p.idx)
      else:
        args = nil
    else:
      parseLine(p, args)
  add(result, args)
  if hasOptions in flags:
    if (p.tok[p.idx].kind == tkIndent) and (p.tok[p.idx].ival >= 3) and
        (p.tok[p.idx + 1].symbol == ":"):
      options = parseFields(p)
  add(result, options)

proc indFollows(p: RstParser): bool =
  result = p.tok[p.idx].kind == tkIndent and p.tok[p.idx].ival > currInd(p)

proc parseDirective(p: var RstParser, flags: DirFlags,
                    contentParser: SectionParser): PRstNode =
  ## Returns a generic rnDirective tree.
  ##
  ## The children are rnDirArg, rnFieldList and rnLineBlock. Any might be nil.
  result = parseDirective(p, flags)
  if not isNil(contentParser) and indFollows(p):
    pushInd(p, p.tok[p.idx].ival)
    var content = contentParser(p)
    popInd(p)
    add(result, content)
  else:
    add(result, PRstNode(nil))

proc parseDirBody(p: var RstParser, contentParser: SectionParser): PRstNode =
  if indFollows(p):
    pushInd(p, p.tok[p.idx].ival)
    result = contentParser(p)
    popInd(p)

proc dirInclude(p: var RstParser): PRstNode =
  ##
  ## The following options are recognized:
  ##
  ## :start-after: text to find in the external data file
  ##
  ##     Only the content after the first occurrence of the specified
  ##     text will be included. If text is not found inclusion will
  ##     start from beginning of the file
  ##
  ## :end-before: text to find in the external data file
  ##
  ##     Only the content before the first occurrence of the specified
  ##     text (but after any after text) will be included. If text is
  ##     not found inclusion will happen until the end of the file.
  #literal : flag (empty)
  #    The entire included text is inserted into the document as a single
  #    literal block (useful for program listings).
  #encoding : name of text encoding
  #    The text encoding of the external data file. Defaults to the document's
  #    encoding (if specified).
  #
  result = nil
  var n = parseDirective(p, {hasArg, argIsFile, hasOptions}, nil)
  var filename = strip(addNodes(n.sons[0]))
  var path = p.findRelativeFile(filename)
  if path == "":
    rstMessage(p, meCannotOpenFile, filename)
  else:
    # XXX: error handling; recursive file inclusion!
    if getFieldValue(n, "literal") != "":
      result = newRstNode(rnLiteralBlock)
      add(result, newRstNode(rnLeaf, readFile(path)))
    else:
      let inputString = readFile(path).string()
      let startPosition =
        block:
          let searchFor = n.getFieldValue("start-after").strip()
          if searchFor != "":
            let pos = inputString.find(searchFor)
            if pos != -1: pos + searchFor.len()
            else: 0
          else:
            0

      let endPosition =
        block:
          let searchFor = n.getFieldValue("end-before").strip()
          if searchFor != "":
            let pos = inputString.find(searchFor, start = startPosition)
            if pos != -1: pos - 1
            else: 0
          else:
            inputString.len - 1

      var q: RstParser
      initParser(q, p.s)
      q.filename = path
      q.col += getTokens(
        inputString[startPosition..endPosition].strip(),
        false,
        q.tok)
      # workaround a GCC bug; more like the interior pointer bug?
      #if find(q.tok[high(q.tok)].symbol, "\0\x01\x02") > 0:
      #  InternalError("Too many binary zeros in include file")
      result = parseDoc(q)

proc dirCodeBlock(p: var RstParser, nimExtension = false): PRstNode =
  ## Parses a code block.
  ##
  ## Code blocks are rnDirective trees with a `kind` of rnCodeBlock. See the
  ## description of ``parseDirective`` for further structure information.
  ##
  ## Code blocks can come in two forms, the standard `code directive
  ## <http://docutils.sourceforge.net/docs/ref/rst/directives.html#code>`_ and
  ## the nim extension ``.. code-block::``. If the block is an extension, we
  ## want the default language syntax highlighting to be Nim, so we create a
  ## fake internal field to communicate with the generator. The field is named
  ## ``default-language``, which is unlikely to collide with a field specified
  ## by any random rst input file.
  ##
  ## As an extension this proc will process the ``file`` extension field and if
  ## present will replace the code block with the contents of the referenced
  ## file.
  result = parseDirective(p, {hasArg, hasOptions}, parseLiteralBlock)
  var filename = strip(getFieldValue(result, "file"))
  if filename != "":
    var path = p.findRelativeFile(filename)
    if path == "": rstMessage(p, meCannotOpenFile, filename)
    var n = newRstNode(rnLiteralBlock)
    add(n, newRstNode(rnLeaf, readFile(path)))
    result.sons[2] = n

  # Extend the field block if we are using our custom extension.
  if nimExtension:
    # Create a field block if the input block didn't have any.
    if result.sons[1].isNil: result.sons[1] = newRstNode(rnFieldList)
    assert result.sons[1].kind == rnFieldList
    # Hook the extra field and specify the Nim language as value.
    var extraNode = newRstNode(rnField)
    extraNode.add(newRstNode(rnFieldName))
    extraNode.add(newRstNode(rnFieldBody))
    extraNode.sons[0].add(newRstNode(rnLeaf, "default-language"))
    extraNode.sons[1].add(newRstNode(rnLeaf, "Nim"))
    result.sons[1].add(extraNode)

  result.kind = rnCodeBlock

proc dirContainer(p: var RstParser): PRstNode =
  result = parseDirective(p, {hasArg}, parseSectionWrapper)
  assert(result.kind == rnDirective)
  assert(len(result) == 3)
  result.kind = rnContainer

proc dirImage(p: var RstParser): PRstNode =
  result = parseDirective(p, {hasOptions, hasArg, argIsFile}, nil)
  result.kind = rnImage

proc dirFigure(p: var RstParser): PRstNode =
  result = parseDirective(p, {hasOptions, hasArg, argIsFile},
                          parseSectionWrapper)
  result.kind = rnFigure

proc dirTitle(p: var RstParser): PRstNode =
  result = parseDirective(p, {hasArg}, nil)
  result.kind = rnTitle

proc dirContents(p: var RstParser): PRstNode =
  result = parseDirective(p, {hasArg}, nil)
  result.kind = rnContents

proc dirIndex(p: var RstParser): PRstNode =
  result = parseDirective(p, {}, parseSectionWrapper)
  result.kind = rnIndex

proc dirRawAux(p: var RstParser, result: var PRstNode, kind: RstNodeKind,
               contentParser: SectionParser) =
  var filename = getFieldValue(result, "file")
  if filename.len > 0:
    var path = p.findRelativeFile(filename)
    if path.len == 0:
      rstMessage(p, meCannotOpenFile, filename)
    else:
      var f = readFile(path)
      result = newRstNode(kind)
      add(result, newRstNode(rnLeaf, f))
  else:
    result.kind = kind
    add(result, parseDirBody(p, contentParser))

proc dirRaw(p: var RstParser): PRstNode =
  #
  #The following options are recognized:
  #
  #file : string (newlines removed)
  #    The local filesystem path of a raw data file to be included.
  #
  # html
  # latex
  result = parseDirective(p, {hasOptions, hasArg, argIsWord})
  if result.sons[0] != nil:
    if cmpIgnoreCase(result.sons[0].sons[0].text, "html") == 0:
      dirRawAux(p, result, rnRawHtml, parseLiteralBlock)
    elif cmpIgnoreCase(result.sons[0].sons[0].text, "latex") == 0:
      dirRawAux(p, result, rnRawLatex, parseLiteralBlock)
    else:
      rstMessage(p, meInvalidDirective, result.sons[0].sons[0].text)
  else:
    dirRawAux(p, result, rnRaw, parseSectionWrapper)

proc parseDotDot(p: var RstParser): PRstNode =
  result = nil
  var col = p.tok[p.idx].col
  inc(p.idx)
  var d = getDirective(p)
  if d != "":
    pushInd(p, col)
    case getDirKind(d)
    of dkInclude: result = dirInclude(p)
    of dkImage: result = dirImage(p)
    of dkFigure: result = dirFigure(p)
    of dkTitle: result = dirTitle(p)
    of dkContainer: result = dirContainer(p)
    of dkContents: result = dirContents(p)
    of dkRaw:
      if roSupportRawDirective in p.s.options:
        result = dirRaw(p)
      else:
        rstMessage(p, meInvalidDirective, d)
    of dkCode: result = dirCodeBlock(p)
    of dkCodeBlock: result = dirCodeBlock(p, nimExtension = true)
    of dkIndex: result = dirIndex(p)
    else: rstMessage(p, meInvalidDirective, d)
    popInd(p)
  elif match(p, p.idx, " _"):
    # hyperlink target:
    inc(p.idx, 2)
    var a = getReferenceName(p, ":")
    if p.tok[p.idx].kind == tkWhite: inc(p.idx)
    var b = untilEol(p)
    setRef(p, rstnodeToRefname(a), b)
  elif match(p, p.idx, " |"):
    # substitution definitions:
    inc(p.idx, 2)
    var a = getReferenceName(p, "|")
    var b: PRstNode
    if p.tok[p.idx].kind == tkWhite: inc(p.idx)
    if cmpIgnoreStyle(p.tok[p.idx].symbol, "replace") == 0:
      inc(p.idx)
      expect(p, "::")
      b = untilEol(p)
    elif cmpIgnoreStyle(p.tok[p.idx].symbol, "image") == 0:
      inc(p.idx)
      b = dirImage(p)
    else:
      rstMessage(p, meInvalidDirective, p.tok[p.idx].symbol)
    setSub(p, addNodes(a), b)
  elif match(p, p.idx, " ["):
    # footnotes, citations
    inc(p.idx, 2)
    var a = getReferenceName(p, "]")
    if p.tok[p.idx].kind == tkWhite: inc(p.idx)
    var b = untilEol(p)
    setRef(p, rstnodeToRefname(a), b)
  else:
    result = parseComment(p)

proc resolveSubs(p: var RstParser, n: PRstNode): PRstNode =
  result = n
  if n == nil: return
  case n.kind
  of rnSubstitutionReferences:
    var x = findSub(p, n)
    if x >= 0:
      result = p.s.subs[x].value
    else:
      var key = addNodes(n)
      var e = getEnv(key)
      if e != "": result = newRstNode(rnLeaf, e)
      else: rstMessage(p, mwUnknownSubstitution, key)
  of rnRef:
    var y = findRef(p, rstnodeToRefname(n))
    if y != nil:
      result = newRstNode(rnHyperlink)
      n.kind = rnInner
      add(result, n)
      add(result, y)
  of rnLeaf:
    discard
  of rnContents:
    p.hasToc = true
  else:
    for i in countup(0, len(n) - 1): n.sons[i] = resolveSubs(p, n.sons[i])

proc rstParse*(text, filename: string,
               line, column: int, hasToc: var bool,
               options: RstParseOptions,
               findFile: FindFileHandler = nil,
               msgHandler: MsgHandler = nil): PRstNode =
  var p: RstParser
  initParser(p, newSharedState(options, findFile, msgHandler))
  p.filename = filename
  p.line = line
  p.col = column + getTokens(text, roSkipPounds in options, p.tok)
  result = resolveSubs(p, parseDoc(p))
  hasToc = p.hasToc
