#
#
#            Nim's Runtime Library
#        (c) Copyright 2012 Andreas Rumpf
#
#    See the file "copying.txt", included in this
#    distribution, for details about the copyright.
#

## Source highlighter for programming or markup languages.
## Currently only few languages are supported, other languages may be added.
## The interface supports one language nested in another.
##
## **Note:** Import ``packages/docutils/highlite`` to use this module
##
## You can use this to build your own syntax highlighting, check this example:
##
## .. code::nim
##   let code = """for x in $int.high: echo x.ord mod 2 == 0"""
##   var toknizr: GeneralTokenizer
##   initGeneralTokenizer(toknizr, code)
##   while true:
##     getNextToken(toknizr, langNim)
##     case toknizr.kind
##     of gtEof: break  # End Of File (or string)
##     of gtWhitespace:
##       echo gtWhitespace # Maybe you want "visible" whitespaces?.
##       echo substr(code, toknizr.start, toknizr.length + toknizr.start - 1)
##     of gtOperator:
##       echo gtOperator # Maybe you want Operators to use a specific color?.
##       echo substr(code, toknizr.start, toknizr.length + toknizr.start - 1)
##     # of gtSomeSymbol: syntaxHighlight("Comic Sans", "bold", "99px", "pink")
##     else:
##       echo toknizr.kind # All the kinds of tokens can be processed here.
##       echo substr(code, toknizr.start, toknizr.length + toknizr.start - 1)
##
## The proc ``getSourceLanguage`` can get the language ``enum`` from a string:
##
## .. code::nim
##   for l in ["C", "c++", "jAvA", "Nim", "c#"]: echo getSourceLanguage(l)
##

import
  strutils
from algorithm import binarySearch

type
  TokenClass* = enum
    gtEof, gtNone, gtWhitespace, gtDecNumber, gtBinNumber, gtHexNumber,
    gtOctNumber, gtFloatNumber, gtIdentifier, gtKeyword, gtStringLit,
    gtLongStringLit, gtCharLit, gtEscapeSequence, # escape sequence like \xff
    gtOperator, gtPunctuation, gtComment, gtLongComment, gtRegularExpression,
    gtTagStart, gtTagEnd, gtKey, gtValue, gtRawData, gtAssembler,
    gtPreprocessor, gtDirective, gtCommand, gtRule, gtHyperlink, gtLabel,
    gtReference, gtOther
  GeneralTokenizer* = object of RootObj
    kind*: TokenClass
    start*, length*: int
    buf: cstring
    pos: int
    state: TokenClass

  SourceLanguage* = enum
    langNone, langNim, langCpp, langCsharp, langC, langJava,
    langYaml

const
  sourceLanguageToStr*: array[SourceLanguage, string] = ["none",
    "Nim", "C++", "C#", "C", "Java", "Yaml"]
  tokenClassToStr*: array[TokenClass, string] = ["Eof", "None", "Whitespace",
    "DecNumber", "BinNumber", "HexNumber", "OctNumber", "FloatNumber",
    "Identifier", "Keyword", "StringLit", "LongStringLit", "CharLit",
    "EscapeSequence", "Operator", "Punctuation", "Comment", "LongComment",
    "RegularExpression", "TagStart", "TagEnd", "Key", "Value", "RawData",
    "Assembler", "Preprocessor", "Directive", "Command", "Rule", "Hyperlink",
    "Label", "Reference", "Other"]

  # The following list comes from doc/keywords.txt, make sure it is
  # synchronized with this array by running the module itself as a test case.
  nimKeywords = ["addr", "and", "as", "asm", "bind", "block",
    "break", "case", "cast", "concept", "const", "continue", "converter",
    "defer", "discard", "distinct", "div", "do",
    "elif", "else", "end", "enum", "except", "export",
    "finally", "for", "from", "func",
    "if", "import", "in", "include",
    "interface", "is", "isnot", "iterator", "let", "macro", "method",
    "mixin", "mod", "nil", "not", "notin", "object", "of", "or", "out", "proc",
    "ptr", "raise", "ref", "return", "shl", "shr", "static",
    "template", "try", "tuple", "type", "using", "var", "when", "while",
    "xor", "yield"]

proc getSourceLanguage*(name: string): SourceLanguage =
  for i in countup(succ(low(SourceLanguage)), high(SourceLanguage)):
    if cmpIgnoreStyle(name, sourceLanguageToStr[i]) == 0:
      return i
  result = langNone

proc initGeneralTokenizer*(g: var GeneralTokenizer, buf: cstring) =
  g.buf = buf
  g.kind = low(TokenClass)
  g.start = 0
  g.length = 0
  g.state = low(TokenClass)
  var pos = 0                     # skip initial whitespace:
  while g.buf[pos] in {' ', '\x09'..'\x0D'}: inc(pos)
  g.pos = pos

proc initGeneralTokenizer*(g: var GeneralTokenizer, buf: string) =
  initGeneralTokenizer(g, cstring(buf))

proc deinitGeneralTokenizer*(g: var GeneralTokenizer) =
  discard

proc nimGetKeyword(id: string): TokenClass =
  for k in nimKeywords:
    if cmpIgnoreStyle(id, k) == 0: return gtKeyword
  result = gtIdentifier
  when false:
    var i = getIdent(id)
    if (i.id >= ord(tokKeywordLow) - ord(tkSymbol)) and
        (i.id <= ord(tokKeywordHigh) - ord(tkSymbol)):
      result = gtKeyword
    else:
      result = gtIdentifier

proc nimNumberPostfix(g: var GeneralTokenizer, position: int): int =
  var pos = position
  if g.buf[pos] == '\'':
    inc(pos)
    case g.buf[pos]
    of 'f', 'F':
      g.kind = gtFloatNumber
      inc(pos)
      if g.buf[pos] in {'0'..'9'}: inc(pos)
      if g.buf[pos] in {'0'..'9'}: inc(pos)
    of 'i', 'I':
      inc(pos)
      if g.buf[pos] in {'0'..'9'}: inc(pos)
      if g.buf[pos] in {'0'..'9'}: inc(pos)
    else:
      discard
  result = pos

proc nimNumber(g: var GeneralTokenizer, position: int): int =
  const decChars = {'0'..'9', '_'}
  var pos = position
  g.kind = gtDecNumber
  while g.buf[pos] in decChars: inc(pos)
  if g.buf[pos] == '.':
    g.kind = gtFloatNumber
    inc(pos)
    while g.buf[pos] in decChars: inc(pos)
  if g.buf[pos] in {'e', 'E'}:
    g.kind = gtFloatNumber
    inc(pos)
    if g.buf[pos] in {'+', '-'}: inc(pos)
    while g.buf[pos] in decChars: inc(pos)
  result = nimNumberPostfix(g, pos)

const
  OpChars  = {'+', '-', '*', '/', '\\', '<', '>', '!', '?', '^', '.',
              '|', '=', '%', '&', '$', '@', '~', ':'}

proc nimNextToken(g: var GeneralTokenizer) =
  const
    hexChars = {'0'..'9', 'A'..'F', 'a'..'f', '_'}
    octChars = {'0'..'7', '_'}
    binChars = {'0'..'1', '_'}
    SymChars = {'a'..'z', 'A'..'Z', '0'..'9', '\x80'..'\xFF'}
  var pos = g.pos
  g.start = g.pos
  if g.state == gtStringLit:
    g.kind = gtStringLit
    while true:
      case g.buf[pos]
      of '\\':
        g.kind = gtEscapeSequence
        inc(pos)
        case g.buf[pos]
        of 'x', 'X':
          inc(pos)
          if g.buf[pos] in hexChars: inc(pos)
          if g.buf[pos] in hexChars: inc(pos)
        of '0'..'9':
          while g.buf[pos] in {'0'..'9'}: inc(pos)
        of '\0':
          g.state = gtNone
        else: inc(pos)
        break
      of '\0', '\x0D', '\x0A':
        g.state = gtNone
        break
      of '\"':
        inc(pos)
        g.state = gtNone
        break
      else: inc(pos)
  else:
    case g.buf[pos]
    of ' ', '\x09'..'\x0D':
      g.kind = gtWhitespace
      while g.buf[pos] in {' ', '\x09'..'\x0D'}: inc(pos)
    of '#':
      g.kind = gtComment
      inc(pos)
      var isDoc = false
      if g.buf[pos] == '#':
        inc(pos)
        isDoc = true
      if g.buf[pos] == '[':
        g.kind = gtLongComment
        var nesting = 0
        while true:
          case g.buf[pos]
          of '\0': break
          of '#':
            if isDoc:
              if g.buf[pos+1] == '#' and g.buf[pos+2] == '[':
                inc nesting
            elif g.buf[pos+1] == '[':
              inc nesting
            inc pos
          of ']':
            if isDoc:
              if g.buf[pos+1] == '#' and g.buf[pos+2] == '#':
                if nesting == 0:
                  inc(pos, 3)
                  break
                dec nesting
            elif g.buf[pos+1] == '#':
              if nesting == 0:
                inc(pos, 2)
                break
              dec nesting
            inc pos
          else:
            inc pos
      else:
        while g.buf[pos] notin {'\0', '\x0A', '\x0D'}: inc(pos)
    of 'a'..'z', 'A'..'Z', '_', '\x80'..'\xFF':
      var id = ""
      while g.buf[pos] in SymChars + {'_'}:
        add(id, g.buf[pos])
        inc(pos)
      if (g.buf[pos] == '\"'):
        if (g.buf[pos + 1] == '\"') and (g.buf[pos + 2] == '\"'):
          inc(pos, 3)
          g.kind = gtLongStringLit
          while true:
            case g.buf[pos]
            of '\0':
              break
            of '\"':
              inc(pos)
              if g.buf[pos] == '\"' and g.buf[pos+1] == '\"' and
                  g.buf[pos+2] != '\"':
                inc(pos, 2)
                break
            else: inc(pos)
        else:
          g.kind = gtRawData
          inc(pos)
          while not (g.buf[pos] in {'\0', '\x0A', '\x0D'}):
            if g.buf[pos] == '"' and g.buf[pos+1] != '"': break
            inc(pos)
          if g.buf[pos] == '\"': inc(pos)
      else:
        g.kind = nimGetKeyword(id)
    of '0':
      inc(pos)
      case g.buf[pos]
      of 'b', 'B':
        g.kind = gtBinNumber
        inc(pos)
        while g.buf[pos] in binChars: inc(pos)
        pos = nimNumberPostfix(g, pos)
      of 'x', 'X':
        g.kind = gtHexNumber
        inc(pos)
        while g.buf[pos] in hexChars: inc(pos)
        pos = nimNumberPostfix(g, pos)
      of 'o', 'O':
        g.kind = gtOctNumber
        inc(pos)
        while g.buf[pos] in octChars: inc(pos)
        pos = nimNumberPostfix(g, pos)
      else: pos = nimNumber(g, pos)
    of '1'..'9':
      pos = nimNumber(g, pos)
    of '\'':
      inc(pos)
      g.kind = gtCharLit
      while true:
        case g.buf[pos]
        of '\0', '\x0D', '\x0A':
          break
        of '\'':
          inc(pos)
          break
        of '\\':
          inc(pos, 2)
        else: inc(pos)
    of '\"':
      inc(pos)
      if (g.buf[pos] == '\"') and (g.buf[pos + 1] == '\"'):
        inc(pos, 2)
        g.kind = gtLongStringLit
        while true:
          case g.buf[pos]
          of '\0':
            break
          of '\"':
            inc(pos)
            if g.buf[pos] == '\"' and g.buf[pos+1] == '\"' and
                g.buf[pos+2] != '\"':
              inc(pos, 2)
              break
          else: inc(pos)
      else:
        g.kind = gtStringLit
        while true:
          case g.buf[pos]
          of '\0', '\x0D', '\x0A':
            break
          of '\"':
            inc(pos)
            break
          of '\\':
            g.state = g.kind
            break
          else: inc(pos)
    of '(', ')', '[', ']', '{', '}', '`', ':', ',', ';':
      inc(pos)
      g.kind = gtPunctuation
    of '\0':
      g.kind = gtEof
    else:
      if g.buf[pos] in OpChars:
        g.kind = gtOperator
        while g.buf[pos] in OpChars: inc(pos)
      else:
        inc(pos)
        g.kind = gtNone
  g.length = pos - g.pos
  if g.kind != gtEof and g.state != gtNone and g.length <= 0:
    assert false, "nimNextToken: produced an empty token"
  g.pos = pos

proc generalNumber(g: var GeneralTokenizer, position: int): int =
  const decChars = {'0'..'9'}
  var pos = position
  g.kind = gtDecNumber
  while g.buf[pos] in decChars: inc(pos)
  if g.buf[pos] == '.':
    g.kind = gtFloatNumber
    inc(pos)
    while g.buf[pos] in decChars: inc(pos)
  if g.buf[pos] in {'e', 'E'}:
    g.kind = gtFloatNumber
    inc(pos)
    if g.buf[pos] in {'+', '-'}: inc(pos)
    while g.buf[pos] in decChars: inc(pos)
  result = pos

proc generalStrLit(g: var GeneralTokenizer, position: int): int =
  const
    decChars = {'0'..'9'}
    hexChars = {'0'..'9', 'A'..'F', 'a'..'f'}
  var pos = position
  g.kind = gtStringLit
  var c = g.buf[pos]
  inc(pos)                    # skip " or '
  while true:
    case g.buf[pos]
    of '\0':
      break
    of '\\':
      inc(pos)
      case g.buf[pos]
      of '\0':
        break
      of '0'..'9':
        while g.buf[pos] in decChars: inc(pos)
      of 'x', 'X':
        inc(pos)
        if g.buf[pos] in hexChars: inc(pos)
        if g.buf[pos] in hexChars: inc(pos)
      else: inc(pos, 2)
    else:
      if g.buf[pos] == c:
        inc(pos)
        break
      else:
        inc(pos)
  result = pos

proc isKeyword(x: openArray[string], y: string): int =
  binarySearch(x, y)

proc isKeywordIgnoreCase(x: openArray[string], y: string): int =
  binarySearch(x, y, cmpIgnoreCase)

type
  TokenizerFlag = enum
    hasPreprocessor, hasNestedComments
  TokenizerFlags = set[TokenizerFlag]

proc clikeNextToken(g: var GeneralTokenizer, keywords: openArray[string],
                    flags: TokenizerFlags) =
  const
    hexChars = {'0'..'9', 'A'..'F', 'a'..'f'}
    octChars = {'0'..'7'}
    binChars = {'0'..'1'}
    symChars = {'A'..'Z', 'a'..'z', '0'..'9', '_', '\x80'..'\xFF'}
  var pos = g.pos
  g.start = g.pos
  if g.state == gtStringLit:
    g.kind = gtStringLit
    while true:
      case g.buf[pos]
      of '\\':
        g.kind = gtEscapeSequence
        inc(pos)
        case g.buf[pos]
        of 'x', 'X':
          inc(pos)
          if g.buf[pos] in hexChars: inc(pos)
          if g.buf[pos] in hexChars: inc(pos)
        of '0'..'9':
          while g.buf[pos] in {'0'..'9'}: inc(pos)
        of '\0':
          g.state = gtNone
        else: inc(pos)
        break
      of '\0', '\x0D', '\x0A':
        g.state = gtNone
        break
      of '\"':
        inc(pos)
        g.state = gtNone
        break
      else: inc(pos)
  else:
    case g.buf[pos]
    of ' ', '\x09'..'\x0D':
      g.kind = gtWhitespace
      while g.buf[pos] in {' ', '\x09'..'\x0D'}: inc(pos)
    of '/':
      inc(pos)
      if g.buf[pos] == '/':
        g.kind = gtComment
        while not (g.buf[pos] in {'\0', '\x0A', '\x0D'}): inc(pos)
      elif g.buf[pos] == '*':
        g.kind = gtLongComment
        var nested = 0
        inc(pos)
        while true:
          case g.buf[pos]
          of '*':
            inc(pos)
            if g.buf[pos] == '/':
              inc(pos)
              if nested == 0: break
          of '/':
            inc(pos)
            if g.buf[pos] == '*':
              inc(pos)
              if hasNestedComments in flags: inc(nested)
          of '\0':
            break
          else: inc(pos)
    of '#':
      inc(pos)
      if hasPreprocessor in flags:
        g.kind = gtPreprocessor
        while g.buf[pos] in {' ', '\t'}: inc(pos)
        while g.buf[pos] in symChars: inc(pos)
      else:
        g.kind = gtOperator
    of 'a'..'z', 'A'..'Z', '_', '\x80'..'\xFF':
      var id = ""
      while g.buf[pos] in symChars:
        add(id, g.buf[pos])
        inc(pos)
      if isKeyword(keywords, id) >= 0: g.kind = gtKeyword
      else: g.kind = gtIdentifier
    of '0':
      inc(pos)
      case g.buf[pos]
      of 'b', 'B':
        inc(pos)
        while g.buf[pos] in binChars: inc(pos)
        if g.buf[pos] in {'A'..'Z', 'a'..'z'}: inc(pos)
      of 'x', 'X':
        inc(pos)
        while g.buf[pos] in hexChars: inc(pos)
        if g.buf[pos] in {'A'..'Z', 'a'..'z'}: inc(pos)
      of '0'..'7':
        inc(pos)
        while g.buf[pos] in octChars: inc(pos)
        if g.buf[pos] in {'A'..'Z', 'a'..'z'}: inc(pos)
      else:
        pos = generalNumber(g, pos)
        if g.buf[pos] in {'A'..'Z', 'a'..'z'}: inc(pos)
    of '1'..'9':
      pos = generalNumber(g, pos)
      if g.buf[pos] in {'A'..'Z', 'a'..'z'}: inc(pos)
    of '\'':
      pos = generalStrLit(g, pos)
      g.kind = gtCharLit
    of '\"':
      inc(pos)
      g.kind = gtStringLit
      while true:
        case g.buf[pos]
        of '\0':
          break
        of '\"':
          inc(pos)
          break
        of '\\':
          g.state = g.kind
          break
        else: inc(pos)
    of '(', ')', '[', ']', '{', '}', ':', ',', ';', '.':
      inc(pos)
      g.kind = gtPunctuation
    of '\0':
      g.kind = gtEof
    else:
      if g.buf[pos] in OpChars:
        g.kind = gtOperator
        while g.buf[pos] in OpChars: inc(pos)
      else:
        inc(pos)
        g.kind = gtNone
  g.length = pos - g.pos
  if g.kind != gtEof and g.length <= 0:
    assert false, "clikeNextToken: produced an empty token"
  g.pos = pos

proc cNextToken(g: var GeneralTokenizer) =
  const
    keywords: array[0..36, string] = ["_Bool", "_Complex", "_Imaginary", "auto",
      "break", "case", "char", "const", "continue", "default", "do", "double",
      "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int",
      "long", "register", "restrict", "return", "short", "signed", "sizeof",
      "static", "struct", "switch", "typedef", "union", "unsigned", "void",
      "volatile", "while"]
  clikeNextToken(g, keywords, {hasPreprocessor})

proc cppNextToken(g: var GeneralTokenizer) =
  const
    keywords: array[0..47, string] = ["asm", "auto", "break", "case", "catch",
      "char", "class", "const", "continue", "default", "delete", "do", "double",
      "else", "enum", "extern", "float", "for", "friend", "goto", "if",
      "inline", "int", "long", "new", "operator", "private", "protected",
      "public", "register", "return", "short", "signed", "sizeof", "static",
      "struct", "switch", "template", "this", "throw", "try", "typedef",
      "union", "unsigned", "virtual", "void", "volatile", "while"]
  clikeNextToken(g, keywords, {hasPreprocessor})

proc csharpNextToken(g: var GeneralTokenizer) =
  const
    keywords: array[0..76, string] = ["abstract", "as", "base", "bool", "break",
      "byte", "case", "catch", "char", "checked", "class", "const", "continue",
      "decimal", "default", "delegate", "do", "double", "else", "enum", "event",
      "explicit", "extern", "false", "finally", "fixed", "float", "for",
      "foreach", "goto", "if", "implicit", "in", "int", "interface", "internal",
      "is", "lock", "long", "namespace", "new", "null", "object", "operator",
      "out", "override", "params", "private", "protected", "public", "readonly",
      "ref", "return", "sbyte", "sealed", "short", "sizeof", "stackalloc",
      "static", "string", "struct", "switch", "this", "throw", "true", "try",
      "typeof", "uint", "ulong", "unchecked", "unsafe", "ushort", "using",
      "virtual", "void", "volatile", "while"]
  clikeNextToken(g, keywords, {hasPreprocessor})

proc javaNextToken(g: var GeneralTokenizer) =
  const
    keywords: array[0..52, string] = ["abstract", "assert", "boolean", "break",
      "byte", "case", "catch", "char", "class", "const", "continue", "default",
      "do", "double", "else", "enum", "extends", "false", "final", "finally",
      "float", "for", "goto", "if", "implements", "import", "instanceof", "int",
      "interface", "long", "native", "new", "null", "package", "private",
      "protected", "public", "return", "short", "static", "strictfp", "super",
      "switch", "synchronized", "this", "throw", "throws", "transient", "true",
      "try", "void", "volatile", "while"]
  clikeNextToken(g, keywords, {})

proc yamlPlainStrLit(g: var GeneralTokenizer, pos: var int) =
  g.kind = gtStringLit
  while g.buf[pos] notin {'\0', '\x09'..'\x0D', ',', ']', '}'}:
    if g.buf[pos] == ':' and
        g.buf[pos + 1] in {'\0', '\x09'..'\x0D', ' '}:
      break
    inc(pos)

proc yamlPossibleNumber(g: var GeneralTokenizer, pos: var int) =
  g.kind = gtNone
  if g.buf[pos] == '-': inc(pos)
  if g.buf[pos] == '0': inc(pos)
  elif g.buf[pos] in '1'..'9':
    inc(pos)
    while g.buf[pos] in {'0'..'9'}: inc(pos)
  else: yamlPlainStrLit(g, pos)
  if g.kind == gtNone:
    if g.buf[pos] in {'\0', '\x09'..'\x0D', ' ', ',', ']', '}'}:
      g.kind = gtDecNumber
    elif g.buf[pos] == '.':
      inc(pos)
      if g.buf[pos] notin {'0'..'9'}: yamlPlainStrLit(g, pos)
      else:
        while g.buf[pos] in {'0'..'9'}: inc(pos)
        if g.buf[pos] in {'\0', '\x09'..'\x0D', ' ', ',', ']', '}'}:
          g.kind = gtFloatNumber
    if g.kind == gtNone:
      if g.buf[pos] in {'e', 'E'}:
        inc(pos)
        if g.buf[pos] in {'-', '+'}: inc(pos)
        if g.buf[pos] notin {'0'..'9'}: yamlPlainStrLit(g, pos)
        else:
          while g.buf[pos] in {'0'..'9'}: inc(pos)
          if g.buf[pos] in {'\0', '\x09'..'\x0D', ' ', ',', ']', '}'}:
            g.kind = gtFloatNumber
          else: yamlPlainStrLit(g, pos)
      else: yamlPlainStrLit(g, pos)
  while g.buf[pos] notin {'\0', ',', ']', '}', '\x0A', '\x0D'}:
    inc(pos)
    if g.buf[pos] notin {'\x09'..'\x0D', ' ', ',', ']', '}'}:
      yamlPlainStrLit(g, pos)
      break
  # theoretically, we would need to parse indentation (like with block scalars)
  # because of possible multiline flow scalars that start with number-like
  # content, but that is far too troublesome. I think it is fine that the
  # highlighter is sloppy here.

proc yamlNextToken(g: var GeneralTokenizer) =
  const
    hexChars = {'0'..'9', 'A'..'F', 'a'..'f'}
  var pos = g.pos
  g.start = g.pos
  if g.state == gtStringLit:
    g.kind = gtStringLit
    while true:
      case g.buf[pos]
      of '\\':
        if pos != g.pos: break
        g.kind = gtEscapeSequence
        inc(pos)
        case g.buf[pos]
        of 'x':
          inc(pos)
          for i in 1..2:
            {.unroll.}
            if g.buf[pos] in hexChars: inc(pos)
          break
        of 'u':
          inc(pos)
          for i in 1..4:
            {.unroll.}
            if g.buf[pos] in hexChars: inc(pos)
          break
        of 'U':
          inc(pos)
          for i in 1..8:
            {.unroll.}
            if g.buf[pos] in hexChars: inc(pos)
          break
        else: inc(pos)
        break
      of '\0':
        g.state = gtOther
        break
      of '\"':
        inc(pos)
        g.state = gtOther
        break
      else: inc(pos)
  elif g.state == gtCharLit:
    # abusing gtCharLit as single-quoted string lit
    g.kind = gtStringLit
    inc(pos) # skip the starting '
    while true:
      case g.buf[pos]
      of '\'':
        inc(pos)
        if g.buf[pos] == '\'':
          inc(pos)
          g.kind = gtEscapeSequence
        else: g.state = gtOther
        break
      else: inc(pos)
  elif g.state == gtCommand:
    # gtCommand means 'block scalar header'
    case g.buf[pos]
    of ' ', '\t':
      g.kind = gtWhitespace
      while g.buf[pos] in {' ', '\t'}: inc(pos)
    of '#':
      g.kind = gtComment
      while g.buf[pos] notin {'\0', '\x0A', '\x0D'}: inc(pos)
    of '\x0A', '\x0D': discard
    else:
      # illegal here. just don't parse a block scalar
      g.kind = gtNone
      g.state = gtOther
    if g.buf[pos] in {'\x0A', '\x0D'} and g.state == gtCommand:
      g.state = gtLongStringLit
  elif g.state == gtLongStringLit:
    # beware, this is the only token where we actually have to parse
    # indentation.

    g.kind = gtLongStringLit
    # first, we have to find the parent indentation of the block scalar, so that
    # we know when to stop
    assert g.buf[pos] in {'\x0A', '\x0D'}
    var lookbehind = pos - 1
    var headerStart = -1
    while lookbehind >= 0 and g.buf[lookbehind] notin {'\x0A', '\x0D'}:
      if headerStart == -1 and g.buf[lookbehind] in {'|', '>'}:
        headerStart = lookbehind
      dec(lookbehind)
    assert headerStart != -1
    var indentation = 1
    while g.buf[lookbehind + indentation] == ' ': inc(indentation)
    if g.buf[lookbehind + indentation] in {'|', '>'}:
      # when the header is alone in a line, this line does not show the parent's
      # indentation, so we must go further. search the first previous line with
      # non-whitespace content.
      while lookbehind >= 0 and g.buf[lookbehind] in {'\x0A', '\x0D'}:
        dec(lookbehind)
        while lookbehind >= 0 and
            g.buf[lookbehind] in {' ', '\t'}: dec(lookbehind)
      # now, find the beginning of the line...
      while lookbehind >= 0 and g.buf[lookbehind] notin {'\x0A', '\x0D'}:
        dec(lookbehind)
      # ... and its indentation
      indentation = 1
      while g.buf[lookbehind + indentation] == ' ': inc(indentation)
    if lookbehind == -1: indentation = 0 # top level
    elif g.buf[lookbehind + 1] == '-' and g.buf[lookbehind + 2] == '-' and
        g.buf[lookbehind + 3] == '-' and
        g.buf[lookbehind + 4] in {'\x09'..'\x0D', ' '}:
      # this is a document start, therefore, we are at top level
      indentation = 0
    # because lookbehind was at newline char when calculating indentation, we're
    # off by one. fix that. top level's parent will have indentation of -1.
    let parentIndentation = indentation - 1

    # find first content
    while g.buf[pos] in {' ', '\x0A', '\x0D'}:
      if g.buf[pos] == ' ': inc(indentation)
      else: indentation = 0
      inc(pos)
    var minIndentation = indentation

    # for stupid edge cases, we must check whether an explicit indentation depth
    # is given at the header.
    while g.buf[headerStart] in {'>', '|', '+', '-'}: inc(headerStart)
    if g.buf[headerStart] in {'0'..'9'}:
      minIndentation = min(minIndentation, ord(g.buf[headerStart]) - ord('0'))

    # process content lines
    while indentation > parentIndentation and g.buf[pos] != '\0':
      if (indentation < minIndentation and g.buf[pos] == '#') or
          (indentation == 0 and g.buf[pos] == '.' and g.buf[pos + 1] == '.' and
          g.buf[pos + 2] == '.' and
          g.buf[pos + 3] in {'\0', '\x09'..'\x0D', ' '}):
        # comment after end of block scalar, or end of document
        break
      minIndentation = min(indentation, minIndentation)
      while g.buf[pos] notin {'\0', '\x0A', '\x0D'}: inc(pos)
      while g.buf[pos] in {' ', '\x0A', '\x0D'}:
        if g.buf[pos] == ' ': inc(indentation)
        else: indentation = 0
        inc(pos)

    g.state = gtOther
  elif g.state == gtOther:
    # gtOther means 'inside YAML document'
    case g.buf[pos]
    of ' ', '\x09'..'\x0D':
      g.kind = gtWhitespace
      while g.buf[pos] in {' ', '\x09'..'\x0D'}: inc(pos)
    of '#':
      g.kind = gtComment
      inc(pos)
      while g.buf[pos] notin {'\0', '\x0A', '\x0D'}: inc(pos)
    of '-':
      inc(pos)
      if g.buf[pos] in {'\0', ' ', '\x09'..'\x0D'}:
        g.kind = gtPunctuation
      elif g.buf[pos] == '-' and
          (pos == 1 or g.buf[pos - 2] in {'\x0A', '\x0D'}): # start of line
        inc(pos)
        if g.buf[pos] == '-' and g.buf[pos + 1] in {'\0', '\x09'..'\x0D', ' '}:
          inc(pos)
          g.kind = gtKeyword
        else: yamlPossibleNumber(g, pos)
      else: yamlPossibleNumber(g, pos)
    of '.':
      if pos == 0 or g.buf[pos - 1] in {'\x0A', '\x0D'}:
        inc(pos)
        for i in 1..2:
          {.unroll.}
          if g.buf[pos] != '.': break
          inc(pos)
        if pos == g.start + 3:
          g.kind = gtKeyword
          g.state = gtNone
        else: yamlPlainStrLit(g, pos)
      else: yamlPlainStrLit(g, pos)
    of '?':
      inc(pos)
      if g.buf[pos] in {'\0', ' ', '\x09'..'\x0D'}:
        g.kind = gtPunctuation
      else: yamlPlainStrLit(g, pos)
    of ':':
      inc(pos)
      if g.buf[pos] in {'\0', '\x09'..'\x0D', ' ', '\'', '\"'} or
          (pos > 0 and g.buf[pos - 2] in {'}', ']', '\"', '\''}):
        g.kind = gtPunctuation
      else: yamlPlainStrLit(g, pos)
    of '[', ']', '{', '}', ',':
      inc(pos)
      g.kind = gtPunctuation
    of '\"':
      inc(pos)
      g.state = gtStringLit
      g.kind = gtStringLit
    of '\'':
      g.state = gtCharLit
      g.kind = gtNone
    of '!':
      g.kind = gtTagStart
      inc(pos)
      if g.buf[pos] == '<':
        # literal tag (e.g. `!<tag:yaml.org,2002:str>`)
        while g.buf[pos] notin {'\0', '>', '\x09'..'\x0D', ' '}: inc(pos)
        if g.buf[pos] == '>': inc(pos)
      else:
        while g.buf[pos] in {'A'..'Z', 'a'..'z', '0'..'9', '-'}: inc(pos)
        case g.buf[pos]
        of '!':
          # prefixed tag (e.g. `!!str`)
          inc(pos)
          while g.buf[pos] notin
              {'\0', '\x09'..'\x0D', ' ', ',', '[', ']', '{', '}'}: inc(pos)
        of '\0', '\x09'..'\x0D', ' ': discard
        else:
          # local tag (e.g. `!nim:system:int`)
          while g.buf[pos] notin {'\0', '\x09'..'\x0D', ' '}: inc(pos)
    of '&':
      g.kind = gtLabel
      while g.buf[pos] notin {'\0', '\x09'..'\x0D', ' '}: inc(pos)
    of '*':
      g.kind = gtReference
      while g.buf[pos] notin {'\0', '\x09'..'\x0D', ' '}: inc(pos)
    of '|', '>':
      # this can lead to incorrect tokenization when | or > appear inside flow
      # content. checking whether we're inside flow content is not
      # chomsky type-3, so we won't do that here.
      g.kind = gtCommand
      g.state = gtCommand
      inc(pos)
      while g.buf[pos] in {'0'..'9', '+', '-'}: inc(pos)
    of '0'..'9': yamlPossibleNumber(g, pos)
    of '\0': g.kind = gtEof
    else: yamlPlainStrLit(g, pos)
  else:
    # outside document
    case g.buf[pos]
    of '%':
      if pos == 0 or g.buf[pos - 1] in {'\x0A', '\x0D'}:
        g.kind = gtDirective
        while g.buf[pos] notin {'\0', '\x0A', '\x0D'}: inc(pos)
      else:
        g.state = gtOther
        yamlPlainStrLit(g, pos)
    of ' ', '\x09'..'\x0D':
      g.kind = gtWhitespace
      while g.buf[pos] in {' ', '\x09'..'\x0D'}: inc(pos)
    of '#':
      g.kind = gtComment
      while g.buf[pos] notin {'\0', '\x0A', '\x0D'}: inc(pos)
    of '\0': g.kind = gtEof
    else:
      g.kind = gtNone
      g.state = gtOther
  g.length = pos - g.pos
  g.pos = pos

proc getNextToken*(g: var GeneralTokenizer, lang: SourceLanguage) =
  case lang
  of langNone: assert false
  of langNim: nimNextToken(g)
  of langCpp: cppNextToken(g)
  of langCsharp: csharpNextToken(g)
  of langC: cNextToken(g)
  of langJava: javaNextToken(g)
  of langYaml: yamlNextToken(g)

when isMainModule:
  var keywords: seq[string]
  # Try to work running in both the subdir or at the root.
  for filename in ["doc/keywords.txt", "../../../doc/keywords.txt"]:
    try:
      let input = string(readFile(filename))
      keywords = input.splitWhitespace()
      break
    except:
      echo filename, " not found"
  doAssert(keywords.len > 0, "Couldn't read any keywords.txt file!")
  for i in 0..min(keywords.len, nimKeywords.len)-1:
    doAssert keywords[i] == nimKeywords[i], "Unexpected keyword"
  doAssert keywords.len == nimKeywords.len, "No matching lengths"
