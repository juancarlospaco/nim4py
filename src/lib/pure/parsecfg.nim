#
#
#            Nim's Runtime Library
#        (c) Copyright 2010 Andreas Rumpf
#
#    See the file "copying.txt", included in this
#    distribution, for details about the copyright.
#

## The ``parsecfg`` module implements a high performance configuration file
## parser. The configuration file's syntax is similar to the Windows ``.ini``
## format, but much more powerful, as it is not a line based parser. String
## literals, raw string literals and triple quoted string literals are supported
## as in the Nim programming language.
##
## Example of how a configuration file may look like:
##
## .. include:: ../../doc/mytest.cfg
##     :literal:
##
## Here is an example of how to use the configuration file parser:
##
## .. code-block:: nim
##
##    import os, parsecfg, strutils, streams
##
##    var f = newFileStream(paramStr(1), fmRead)
##    if f != nil:
##      var p: CfgParser
##      open(p, f, paramStr(1))
##      while true:
##        var e = next(p)
##        case e.kind
##        of cfgEof: break
##        of cfgSectionStart:   ## a ``[section]`` has been parsed
##          echo("new section: " & e.section)
##        of cfgKeyValuePair:
##          echo("key-value-pair: " & e.key & ": " & e.value)
##        of cfgOption:
##          echo("command: " & e.key & ": " & e.value)
##        of cfgError:
##          echo(e.msg)
##      close(p)
##    else:
##      echo("cannot open: " & paramStr(1))
##
##
## Examples
## ========
##
## Configuration file example
## --------------------------
##
## .. code-block:: nim
##
##     charset = "utf-8"
##     [Package]
##     name = "hello"
##     --threads:on
##     [Author]
##     name = "lihf8515"
##     qq = "10214028"
##     email = "lihaifeng@wxm.com"
##
## Creating a configuration file
## -----------------------------
## .. code-block:: nim
##
##     import parsecfg
##     var dict=newConfig()
##     dict.setSectionKey("","charset","utf-8")
##     dict.setSectionKey("Package","name","hello")
##     dict.setSectionKey("Package","--threads","on")
##     dict.setSectionKey("Author","name","lihf8515")
##     dict.setSectionKey("Author","qq","10214028")
##     dict.setSectionKey("Author","email","lihaifeng@wxm.com")
##     dict.writeConfig("config.ini")
##
## Reading a configuration file
## ----------------------------
## .. code-block:: nim
##
##     import parsecfg
##     var dict = loadConfig("config.ini")
##     var charset = dict.getSectionValue("","charset")
##     var threads = dict.getSectionValue("Package","--threads")
##     var pname = dict.getSectionValue("Package","name")
##     var name = dict.getSectionValue("Author","name")
##     var qq = dict.getSectionValue("Author","qq")
##     var email = dict.getSectionValue("Author","email")
##     echo pname & "\n" & name & "\n" & qq & "\n" & email
##
## Modifying a configuration file
## ------------------------------
## .. code-block:: nim
##
##     import parsecfg
##     var dict = loadConfig("config.ini")
##     dict.setSectionKey("Author","name","lhf")
##     dict.writeConfig("config.ini")
##
## Deleting a section key in a configuration file
## ----------------------------------------------
## .. code-block:: nim
##
##     import parsecfg
##     var dict = loadConfig("config.ini")
##     dict.delSectionKey("Author","email")
##     dict.writeConfig("config.ini")

import
  strutils, lexbase, streams, tables

include "system/inclrtl"

type
  CfgEventKind* = enum ## enumeration of all events that may occur when parsing
    cfgEof,            ## end of file reached
    cfgSectionStart,   ## a ``[section]`` has been parsed
    cfgKeyValuePair,   ## a ``key=value`` pair has been detected
    cfgOption,         ## a ``--key=value`` command line option
    cfgError           ## an error occurred during parsing

  CfgEvent* = object of RootObj ## describes a parsing event
    case kind*: CfgEventKind    ## the kind of the event
    of cfgEof: nil
    of cfgSectionStart:
      section*: string          ## `section` contains the name of the
                                ## parsed section start (syntax: ``[section]``)
    of cfgKeyValuePair, cfgOption:
      key*, value*: string      ## contains the (key, value) pair if an option
                                ## of the form ``--key: value`` or an ordinary
                                ## ``key= value`` pair has been parsed.
                                ## ``value==""`` if it was not specified in the
                                ## configuration file.
    of cfgError:                ## the parser encountered an error: `msg`
      msg*: string              ## contains the error message. No exceptions
                                ## are thrown if a parse error occurs.

  TokKind = enum
    tkInvalid, tkEof,
    tkSymbol, tkEquals, tkColon, tkBracketLe, tkBracketRi, tkDashDash
  Token = object    # a token
    kind: TokKind   # the type of the token
    literal: string # the parsed (string) literal

  CfgParser* = object of BaseLexer ## the parser object.
    tok: Token
    filename: string

# implementation

const
  SymChars = {'a'..'z', 'A'..'Z', '0'..'9', '_', '\x80'..'\xFF', '.', '/', '\\', '-'}

proc rawGetTok(c: var CfgParser, tok: var Token) {.gcsafe.}

proc open*(c: var CfgParser, input: Stream, filename: string,
           lineOffset = 0) {.rtl, extern: "npc$1".} =
  ## initializes the parser with an input stream. `Filename` is only used
  ## for nice error messages. `lineOffset` can be used to influence the line
  ## number information in the generated error messages.
  lexbase.open(c, input)
  c.filename = filename
  c.tok.kind = tkInvalid
  c.tok.literal = ""
  inc(c.lineNumber, lineOffset)
  rawGetTok(c, c.tok)

proc close*(c: var CfgParser) {.rtl, extern: "npc$1".} =
  ## closes the parser `c` and its associated input stream.
  lexbase.close(c)

proc getColumn*(c: CfgParser): int {.rtl, extern: "npc$1".} =
  ## get the current column the parser has arrived at.
  result = getColNumber(c, c.bufpos)

proc getLine*(c: CfgParser): int {.rtl, extern: "npc$1".} =
  ## get the current line the parser has arrived at.
  result = c.lineNumber

proc getFilename*(c: CfgParser): string {.rtl, extern: "npc$1".} =
  ## get the filename of the file that the parser processes.
  result = c.filename

proc handleHexChar(c: var CfgParser, xi: var int) =
  case c.buf[c.bufpos]
  of '0'..'9':
    xi = (xi shl 4) or (ord(c.buf[c.bufpos]) - ord('0'))
    inc(c.bufpos)
  of 'a'..'f':
    xi = (xi shl 4) or (ord(c.buf[c.bufpos]) - ord('a') + 10)
    inc(c.bufpos)
  of 'A'..'F':
    xi = (xi shl 4) or (ord(c.buf[c.bufpos]) - ord('A') + 10)
    inc(c.bufpos)
  else:
    discard

proc handleDecChars(c: var CfgParser, xi: var int) =
  while c.buf[c.bufpos] in {'0'..'9'}:
    xi = (xi * 10) + (ord(c.buf[c.bufpos]) - ord('0'))
    inc(c.bufpos)

proc getEscapedChar(c: var CfgParser, tok: var Token) =
  inc(c.bufpos) # skip '\'
  case c.buf[c.bufpos]
  of 'n', 'N':
    add(tok.literal, "\n")
    inc(c.bufpos)
  of 'r', 'R', 'c', 'C':
    add(tok.literal, '\c')
    inc(c.bufpos)
  of 'l', 'L':
    add(tok.literal, '\L')
    inc(c.bufpos)
  of 'f', 'F':
    add(tok.literal, '\f')
    inc(c.bufpos)
  of 'e', 'E':
    add(tok.literal, '\e')
    inc(c.bufpos)
  of 'a', 'A':
    add(tok.literal, '\a')
    inc(c.bufpos)
  of 'b', 'B':
    add(tok.literal, '\b')
    inc(c.bufpos)
  of 'v', 'V':
    add(tok.literal, '\v')
    inc(c.bufpos)
  of 't', 'T':
    add(tok.literal, '\t')
    inc(c.bufpos)
  of '\'', '"':
    add(tok.literal, c.buf[c.bufpos])
    inc(c.bufpos)
  of '\\':
    add(tok.literal, '\\')
    inc(c.bufpos)
  of 'x', 'X':
    inc(c.bufpos)
    var xi = 0
    handleHexChar(c, xi)
    handleHexChar(c, xi)
    add(tok.literal, chr(xi))
  of '0'..'9':
    var xi = 0
    handleDecChars(c, xi)
    if (xi <= 255): add(tok.literal, chr(xi))
    else: tok.kind = tkInvalid
  else: tok.kind = tkInvalid

proc handleCRLF(c: var CfgParser, pos: int): int =
  case c.buf[pos]
  of '\c': result = lexbase.handleCR(c, pos)
  of '\L': result = lexbase.handleLF(c, pos)
  else: result = pos

proc getString(c: var CfgParser, tok: var Token, rawMode: bool) =
  var pos = c.bufpos + 1 # skip "
  tok.kind = tkSymbol
  if (c.buf[pos] == '"') and (c.buf[pos + 1] == '"'):
    # long string literal:
    inc(pos, 2) # skip ""
                              # skip leading newline:
    pos = handleCRLF(c, pos)
    while true:
      case c.buf[pos]
      of '"':
        if (c.buf[pos + 1] == '"') and (c.buf[pos + 2] == '"'): break
        add(tok.literal, '"')
        inc(pos)
      of '\c', '\L':
        pos = handleCRLF(c, pos)
        add(tok.literal, "\n")
      of lexbase.EndOfFile:
        tok.kind = tkInvalid
        break
      else:
        add(tok.literal, c.buf[pos])
        inc(pos)
    c.bufpos = pos + 3 # skip the three """
  else:
    # ordinary string literal
    while true:
      var ch = c.buf[pos]
      if ch == '"':
        inc(pos) # skip '"'
        break
      if ch in {'\c', '\L', lexbase.EndOfFile}:
        tok.kind = tkInvalid
        break
      if (ch == '\\') and not rawMode:
        c.bufpos = pos
        getEscapedChar(c, tok)
        pos = c.bufpos
      else:
        add(tok.literal, ch)
        inc(pos)
    c.bufpos = pos

proc getSymbol(c: var CfgParser, tok: var Token) =
  var pos = c.bufpos
  while true:
    add(tok.literal, c.buf[pos])
    inc(pos)
    if not (c.buf[pos] in SymChars): break
  c.bufpos = pos
  tok.kind = tkSymbol

proc skip(c: var CfgParser) =
  var pos = c.bufpos
  while true:
    case c.buf[pos]
    of ' ', '\t':
      inc(pos)
    of '#', ';':
      while not (c.buf[pos] in {'\c', '\L', lexbase.EndOfFile}): inc(pos)
    of '\c', '\L':
      pos = handleCRLF(c, pos)
    else:
      break # EndOfFile also leaves the loop
  c.bufpos = pos

proc rawGetTok(c: var CfgParser, tok: var Token) =
  tok.kind = tkInvalid
  setLen(tok.literal, 0)
  skip(c)
  case c.buf[c.bufpos]
  of '=':
    tok.kind = tkEquals
    inc(c.bufpos)
    tok.literal = "="
  of '-':
    inc(c.bufpos)
    if c.buf[c.bufpos] == '-':
      inc(c.bufpos)
      tok.kind = tkDashDash
      tok.literal = "--"
    else:
      dec(c.bufpos)
      getSymbol(c, tok)
  of ':':
    tok.kind = tkColon
    inc(c.bufpos)
    tok.literal = ":"
  of 'r', 'R':
    if c.buf[c.bufpos + 1] == '\"':
      inc(c.bufpos)
      getString(c, tok, true)
    else:
      getSymbol(c, tok)
  of '[':
    tok.kind = tkBracketLe
    inc(c.bufpos)
    tok.literal = "["
  of ']':
    tok.kind = tkBracketRi
    inc(c.bufpos)
    tok.literal = "]"
  of '"':
    getString(c, tok, false)
  of lexbase.EndOfFile:
    tok.kind = tkEof
    tok.literal = "[EOF]"
  else: getSymbol(c, tok)

proc errorStr*(c: CfgParser, msg: string): string {.rtl, extern: "npc$1".} =
  ## returns a properly formatted error message containing current line and
  ## column information.
  result = `%`("$1($2, $3) Error: $4",
                [c.filename, $getLine(c), $getColumn(c), msg])

proc warningStr*(c: CfgParser, msg: string): string {.rtl, extern: "npc$1".} =
  ## returns a properly formatted warning message containing current line and
  ## column information.
  result = `%`("$1($2, $3) Warning: $4",
                [c.filename, $getLine(c), $getColumn(c), msg])

proc ignoreMsg*(c: CfgParser, e: CfgEvent): string {.rtl, extern: "npc$1".} =
  ## returns a properly formatted warning message containing that
  ## an entry is ignored.
  case e.kind
  of cfgSectionStart: result = c.warningStr("section ignored: " & e.section)
  of cfgKeyValuePair: result = c.warningStr("key ignored: " & e.key)
  of cfgOption:
    result = c.warningStr("command ignored: " & e.key & ": " & e.value)
  of cfgError: result = e.msg
  of cfgEof: result = ""

proc getKeyValPair(c: var CfgParser, kind: CfgEventKind): CfgEvent =
  if c.tok.kind == tkSymbol:
    case kind
    of cfgOption, cfgKeyValuePair:
      result = CfgEvent(kind: kind, key: c.tok.literal, value: "")
    else: discard
    rawGetTok(c, c.tok)
    if c.tok.kind in {tkEquals, tkColon}:
      rawGetTok(c, c.tok)
      if c.tok.kind == tkSymbol:
        result.value = c.tok.literal
      else:
        result = CfgEvent(kind: cfgError,
          msg: errorStr(c, "symbol expected, but found: " & c.tok.literal))
      rawGetTok(c, c.tok)
  else:
    result = CfgEvent(kind: cfgError,
      msg: errorStr(c, "symbol expected, but found: " & c.tok.literal))
    rawGetTok(c, c.tok)

proc next*(c: var CfgParser): CfgEvent {.rtl, extern: "npc$1".} =
  ## retrieves the first/next event. This controls the parser.
  case c.tok.kind
  of tkEof:
    result = CfgEvent(kind: cfgEof)
  of tkDashDash:
    rawGetTok(c, c.tok)
    result = getKeyValPair(c, cfgOption)
  of tkSymbol:
    result = getKeyValPair(c, cfgKeyValuePair)
  of tkBracketLe:
    rawGetTok(c, c.tok)
    if c.tok.kind == tkSymbol:
      result = CfgEvent(kind: cfgSectionStart, section: c.tok.literal)
    else:
      result = CfgEvent(kind: cfgError,
        msg: errorStr(c, "symbol expected, but found: " & c.tok.literal))
    rawGetTok(c, c.tok)
    if c.tok.kind == tkBracketRi:
      rawGetTok(c, c.tok)
    else:
      result = CfgEvent(kind: cfgError,
        msg: errorStr(c, "']' expected, but found: " & c.tok.literal))
  of tkInvalid, tkEquals, tkColon, tkBracketRi:
    result = CfgEvent(kind: cfgError,
      msg: errorStr(c, "invalid token: " & c.tok.literal))
    rawGetTok(c, c.tok)

# ---------------- Configuration file related operations ----------------
type
  Config* = OrderedTableRef[string, <//>OrderedTableRef[string, string]]

proc newConfig*(): Config =
  ## Create a new configuration table.
  ## Useful when wanting to create a configuration file.
  result = newOrderedTable[string, <//>OrderedTableRef[string, string]]()

proc loadConfig*(stream: Stream, filename: string = "[stream]"): <//>Config =
  ## Load the specified configuration from stream into a new Config instance.
  ## `filename` parameter is only used for nicer error messages.
  var dict = newOrderedTable[string, <//>OrderedTableRef[string, string]]()
  var curSection = "" ## Current section,
                      ## the default value of the current section is "",
                      ## which means that the current section is a common
  var p: CfgParser
  open(p, stream, filename)
  while true:
    var e = next(p)
    case e.kind
    of cfgEof:
      break
    of cfgSectionStart: # Only look for the first time the Section
      curSection = e.section
    of cfgKeyValuePair:
      var t = newOrderedTable[string, string]()
      if dict.hasKey(curSection):
        t = dict[curSection]
      t[e.key] = e.value
      dict[curSection] = t
    of cfgOption:
      var c = newOrderedTable[string, string]()
      if dict.hasKey(curSection):
        c = dict[curSection]
      c["--" & e.key] = e.value
      dict[curSection] = c
    of cfgError:
      break
  close(p)
  result = dict

proc loadConfig*(filename: string): <//>Config =
  ## Load the specified configuration file into a new Config instance.
  let file = open(filename, fmRead)
  let fileStream = newFileStream(file)
  defer: fileStream.close()
  result = fileStream.loadConfig(filename)

proc replace(s: string): string =
  var d = ""
  var i = 0
  while i < s.len():
    if s[i] == '\\':
      d.add(r"\\")
    elif s[i] == '\c' and s[i+1] == '\l':
      d.add(r"\c\l")
      inc(i)
    elif s[i] == '\c':
      d.add(r"\n")
    elif s[i] == '\l':
      d.add(r"\n")
    else:
      d.add(s[i])
    inc(i)
  result = d

proc writeConfig*(dict: Config, stream: Stream) =
  ## Writes the contents of the table to the specified stream
  ##
  ## **Note:** Comment statement will be ignored.
  for section, sectionData in dict.pairs():
    if section != "": ## Not general section
      if not allCharsInSet(section, SymChars): ## Non system character
        stream.writeLine("[\"" & section & "\"]")
      else:
        stream.writeLine("[" & section & "]")
    for key, value in sectionData.pairs():
      var kv, segmentChar: string
      if key.len > 1 and key[0] == '-' and key[1] == '-': ## If it is a command key
        segmentChar = ":"
        if not allCharsInSet(key[2..key.len()-1], SymChars):
          kv.add("--\"")
          kv.add(key[2..key.len()-1])
          kv.add("\"")
        else:
          kv = key
      else:
        segmentChar = "="
        kv = key
      if value != "": ## If the key is not empty
        if not allCharsInSet(value, SymChars):
          if find(value, '"') == -1:
            kv.add(segmentChar)
            kv.add("\"")
            kv.add(replace(value))
            kv.add("\"")
          else:
            kv.add(segmentChar)
            kv.add("\"\"\"")
            kv.add(replace(value))
            kv.add("\"\"\"")
        else:
          kv.add(segmentChar)
          kv.add(value)
      stream.writeLine(kv)

proc `$`*(dict: Config): string =
  ## Writes the contents of the table to string.
  ## Note: Comment statement will be ignored.
  let stream = newStringStream()
  defer: stream.close()
  dict.writeConfig(stream)
  result = stream.data

proc writeConfig*(dict: Config, filename: string) =
  ## Writes the contents of the table to the specified configuration file.
  ## Note: Comment statement will be ignored.
  let file = open(filename, fmWrite)
  defer: file.close()
  let fileStream = newFileStream(file)
  dict.writeConfig(fileStream)

proc getSectionValue*(dict: Config, section, key: string): string =
  ## Gets the Key value of the specified Section, returns an empty string if the key does not exist.
  if dict.hasKey(section):
    if dict[section].hasKey(key):
      result = dict[section][key]
    else:
      result = ""
  else:
    result = ""

proc setSectionKey*(dict: var Config, section, key, value: string) =
  ## Sets the Key value of the specified Section.
  var t = newOrderedTable[string, string]()
  if dict.hasKey(section):
    t = dict[section]
  t[key] = value
  dict[section] = t

proc delSection*(dict: var Config, section: string) =
  ## Deletes the specified section and all of its sub keys.
  dict.del(section)

proc delSectionKey*(dict: var Config, section, key: string) =
  ## Delete the key of the specified section.
  if dict.hasKey(section):
    if dict[section].hasKey(key):
      if dict[section].len == 1:
        dict.del(section)
      else:
        dict[section].del(key)
