#
#
#            Nim's Runtime Library
#        (c) Copyright 2017 Nim contributors
#
#    See the file "copying.txt", included in this
#    distribution, for details about the copyright.
#

##[
String `interpolation`:idx: / `format`:idx: inspired by
Python's ``f``-strings.

``fmt`` vs. ``&``
=================

You can use either ``fmt`` or the unary ``&`` operator for formatting. The
difference between them is subtle but important.

The ``fmt"{expr}"`` syntax is more aesthetically pleasing, but it hides a small
gotcha. The string is a
`generalized raw string literal <manual.html#lexical-analysis-generalized-raw-string-literals>`_.
This has some surprising effects:

.. code-block:: nim

    import strformat
    let msg = "hello"
    doAssert fmt"{msg}\n" == "hello\\n"

Because the literal is a raw string literal, the ``\n`` is not interpreted as
an escape sequence.

There are multiple ways to get around this, including the use of the ``&``
operator:

.. code-block:: nim

    import strformat
    let msg = "hello"

    doAssert &"{msg}\n" == "hello\n"

    doAssert fmt"{msg}{'\n'}" == "hello\n"
    doAssert fmt("{msg}\n") == "hello\n"
    doAssert "{msg}\n".fmt == "hello\n"

The choice of style is up to you.

Formatting strings
==================

.. code-block:: nim

    import strformat

    doAssert &"""{"abc":>4}""" == " abc"
    doAssert &"""{"abc":<4}""" == "abc "

Formatting floats
=================

.. code-block:: nim

    import strformat
    doAssert fmt"{-12345:08}" == "-0012345"
    doAssert fmt"{-1:3}" == " -1"
    doAssert fmt"{-1:03}" == "-01"
    doAssert fmt"{16:#X}" == "0x10"

    doAssert fmt"{123.456}" == "123.456"
    doAssert fmt"{123.456:>9.3f}" == "  123.456"
    doAssert fmt"{123.456:9.3f}" == "  123.456"
    doAssert fmt"{123.456:9.4f}" == " 123.4560"
    doAssert fmt"{123.456:>9.0f}" == "     123."
    doAssert fmt"{123.456:<9.4f}" == "123.4560 "

    doAssert fmt"{123.456:e}" == "1.234560e+02"
    doAssert fmt"{123.456:>13e}" == " 1.234560e+02"
    doAssert fmt"{123.456:13e}" == " 1.234560e+02"


Debugging strings
=================

``fmt"{expr=}"`` expands to ``fmt"expr={expr}"`` namely the text of the expression, 
an equal sign and the results of evaluated expression.

.. code-block:: nim

    import strformat
    doAssert fmt"{123.456=}" == "123.456=123.456"
    doAssert fmt"{123.456=:>9.3f}" == "123.456=  123.456"

    let x = "hello"
    doAssert fmt"{x=}" == "x=hello" 
    doAssert fmt"{x =}" == "x =hello"

    let y = 3.1415926
    doAssert fmt"{y=:.2f}" == fmt"y={y:.2f}"
    doAssert fmt"{y=}" == fmt"y={y}"
    doAssert fmt"{y = : <8}" == fmt"y = 3.14159 "

    proc hello(a: string, b: float): int = 12
    let a = "hello"
    let b = 3.1415926
    doAssert fmt"{hello(x, y) = }" == "hello(x, y) = 12"
    doAssert fmt"{x.hello(y) = }" == "x.hello(y) = 12"
    doAssert fmt"{hello x, y = }" == "hello x, y = 12"


Note that it is space sensitive:

.. code-block:: nim

    import strformat
    let x = "12"
    doAssert fmt"{x=}" == "x=12"
    doAssert fmt"{x =:}" == "x =12"
    doAssert fmt"{x =}" == "x =12"
    doAssert fmt"{x= :}" == "x= 12"
    doAssert fmt"{x= }" == "x= 12"
    doAssert fmt"{x = :}" == "x = 12"
    doAssert fmt"{x = }" == "x = 12"
    doAssert fmt"{x   =  :}" == "x   =  12"
    doAssert fmt"{x   =  }" == "x   =  12"


Implementation details
======================

An expression like ``&"{key} is {value:arg} {{z}}"`` is transformed into:

.. code-block:: nim
  var temp = newStringOfCap(educatedCapGuess)
  temp.formatValue key, ""
  temp.add " is "
  temp.formatValue value, arg
  temp.add " {z}"
  temp

Parts of the string that are enclosed in the curly braces are interpreted
as Nim code, to escape an ``{`` or ``}`` double it.

``&`` delegates most of the work to an open overloaded set
of ``formatValue`` procs. The required signature for a type ``T`` that supports
formatting is usually ``proc formatValue(result: var string; x: T; specifier: string)``.

The subexpression after the colon
(``arg`` in ``&"{key} is {value:arg} {{z}}"``) is optional. It will be passed as
the last argument to ``formatValue``. When the colon with the subexpression it is
left out, an empty string will be taken instead.

For strings and numeric types the optional argument is a so-called
"standard format specifier".


Standard format specifier for strings, integers and floats
==========================================================


The general form of a standard format specifier is::

  [[fill]align][sign][#][0][minimumwidth][.precision][type]

The square brackets ``[]`` indicate an optional element.

The optional align flag can be one of the following:

'<'
    Forces the field to be left-aligned within the available
    space. (This is the default for strings.)

'>'
    Forces the field to be right-aligned within the available space.
    (This is the default for numbers.)

'^'
    Forces the field to be centered within the available space.

Note that unless a minimum field width is defined, the field width
will always be the same size as the data to fill it, so that the alignment
option has no meaning in this case.

The optional 'fill' character defines the character to be used to pad
the field to the minimum width. The fill character, if present, must be
followed by an alignment flag.

The 'sign' option is only valid for numeric types, and can be one of the following:

=================        ====================================================
  Sign                   Meaning
=================        ====================================================
``+``                    Indicates that a sign should be used for both
                         positive as well as negative numbers.
``-``                    Indicates that a sign should be used only for
                         negative numbers (this is the default behavior).
(space)                  Indicates that a leading space should be used on
                         positive numbers.
=================        ====================================================

If the '#' character is present, integers use the 'alternate form' for formatting.
This means that binary, octal, and hexadecimal output will be prefixed
with '0b', '0o', and '0x', respectively.

'width' is a decimal integer defining the minimum field width. If not specified,
then the field width will be determined by the content.

If the width field is preceded by a zero ('0') character, this enables
zero-padding.

The 'precision' is a decimal number indicating how many digits should be displayed
after the decimal point in a floating point conversion. For non-numeric types the
field indicates the maximum field size - in other words, how many characters will
be used from the field content. The precision is ignored for integer conversions.

Finally, the 'type' determines how the data should be presented.

The available integer presentation types are:


=================        ====================================================
  Type                   Result
=================        ====================================================
``b``                    Binary. Outputs the number in base 2.
``d``                    Decimal Integer. Outputs the number in base 10.
``o``                    Octal format. Outputs the number in base 8.
``x``                    Hex format. Outputs the number in base 16, using
                         lower-case letters for the digits above 9.
``X``                    Hex format. Outputs the number in base 16, using
                         uppercase letters for the digits above 9.
(None)                   the same as 'd'
=================        ====================================================


The available floating point presentation types are:

=================        ====================================================
  Type                   Result
=================        ====================================================
``e``                    Exponent notation. Prints the number in scientific
                         notation using the letter 'e' to indicate the
                         exponent.
``E``                    Exponent notation. Same as 'e' except it converts
                         the number to uppercase.
``f``                    Fixed point. Displays the number as a fixed-point
                         number.
``F``                    Fixed point. Same as 'f' except it converts the
                         number to uppercase.
``g``                    General format. This prints the number as a
                         fixed-point number, unless the number is too
                         large, in which case it switches to 'e'
                         exponent notation.
``G``                    General format. Same as 'g' except switches to 'E'
                         if the number gets to large.
(None)                   similar to 'g', except that it prints at least one
                         digit after the decimal point.
=================        ====================================================


Limitations
===========

Because of the well defined order how templates and macros are
expanded, strformat cannot expand template arguments:

.. code-block:: nim
  template myTemplate(arg: untyped): untyped =
    echo "arg is: ", arg
    echo &"--- {arg} ---"

  let x = "abc"
  myTemplate(x)

First the template ``myTemplate`` is expanded, where every identifier
``arg`` is substituted with its argument. The ``arg`` inside the
format string is not seen by this process, because it is part of a
quoted string literal. It is not an identifier yet. Then the strformat
macro creates the ``arg`` identifier from the string literal. An
identifier that cannot be resolved anymore.

The workaround for this is to bind the template argument to a new local variable.

.. code-block:: nim

  template myTemplate(arg: untyped): untyped =
    block:
      let arg1 {.inject.} = arg
      echo "arg is: ", arg1
      echo &"--- {arg1} ---"

The use of ``{.inject.}`` here is necessary again because of template
expansion order and hygienic templates. But since we generally want to
keep the hygienicness of ``myTemplate``, and we do not want ``arg1``
to be injected into the context where ``myTemplate`` is expanded,
everything is wrapped in a ``block``.


Future directions
=================

A curly expression with commas in it like ``{x, argA, argB}`` could be
transformed to ``formatValue(result, x, argA, argB)`` in order to support
formatters that do not need to parse a custom language within a custom
language but instead prefer to use Nim's existing syntax. This also
helps in readability since there is only so much you can cram into
single letter DSLs.

]##

import macros, parseutils, unicode
import strutils except format

proc mkDigit(v: int, typ: char): string {.inline.} =
  assert(v < 26)
  if v < 10:
    result = $chr(ord('0') + v)
  else:
    result = $chr(ord(if typ == 'x': 'a' else: 'A') + v - 10)

proc alignString*(s: string, minimumWidth: int; align = '\0';
    fill = ' '): string =
  ## Aligns ``s`` using ``fill`` char.
  ## This is only of interest if you want to write a custom ``format`` proc that
  ## should support the standard format specifiers.
  if minimumWidth == 0:
    result = s
  else:
    let sRuneLen = if s.validateUtf8 == -1: s.runeLen else: s.len
    let toFill = minimumWidth - sRuneLen
    if toFill <= 0:
      result = s
    elif align == '<' or align == '\0':
      result = s & repeat(fill, toFill)
    elif align == '^':
      let half = toFill div 2
      result = repeat(fill, half) & s & repeat(fill, toFill - half)
    else:
      result = repeat(fill, toFill) & s

type
  StandardFormatSpecifier* = object ## Type that describes "standard format specifiers".
    fill*, align*: char            ## Desired fill and alignment.
    sign*: char                    ## Desired sign.
    alternateForm*: bool           ## Whether to prefix binary, octal and hex numbers
                                   ## with ``0b``, ``0o``, ``0x``.
    padWithZero*: bool             ## Whether to pad with zeros rather than spaces.
    minimumWidth*, precision*: int ## Desired minimum width and precision.
    typ*: char                     ## Type like 'f', 'g' or 'd'.
    endPosition*: int              ## End position in the format specifier after
                                   ## ``parseStandardFormatSpecifier`` returned.

proc formatInt(n: SomeNumber; radix: int;
    spec: StandardFormatSpecifier): string =
  ## Converts ``n`` to string. If ``n`` is `SomeFloat`, it casts to `int64`.
  ## Conversion is done using ``radix``. If result's length is lesser than
  ## ``minimumWidth``, it aligns result to the right or left (depending on ``a``)
  ## with ``fill`` char.
  when n is SomeUnsignedInt:
    var v = n.uint64
    let negative = false
  else:
    var v = n.int64
    let negative = v.int64 < 0
    if negative:
      # FIXME: overflow error for low(int64)
      v = v * -1

  var xx = ""
  if spec.alternateForm:
    case spec.typ
    of 'X': xx = "0x"
    of 'x': xx = "0x"
    of 'b': xx = "0b"
    of 'o': xx = "0o"
    else: discard

  if v == 0:
    result = "0"
  else:
    result = ""
    while v > type(v)(0):
      let d = v mod type(v)(radix)
      v = v div type(v)(radix)
      result.add(mkDigit(d.int, spec.typ))
    for idx in 0..<(result.len div 2):
      swap result[idx], result[result.len - idx - 1]
  if spec.padWithZero:
    let sign = negative or spec.sign != '-'
    let toFill = spec.minimumWidth - result.len - xx.len - ord(sign)
    if toFill > 0:
      result = repeat('0', toFill) & result

  if negative:
    result = "-" & xx & result
  elif spec.sign != '-':
    result = spec.sign & xx & result
  else:
    result = xx & result

  if spec.align == '<':
    for i in result.len..<spec.minimumWidth:
      result.add(spec.fill)
  else:
    let toFill = spec.minimumWidth - result.len
    if spec.align == '^':
      let half = toFill div 2
      result = repeat(spec.fill, half) & result & repeat(spec.fill, toFill - half)
    else:
      if toFill > 0:
        result = repeat(spec.fill, toFill) & result

proc parseStandardFormatSpecifier*(s: string; start = 0;
                                   ignoreUnknownSuffix = false): StandardFormatSpecifier =
  ## An exported helper proc that parses the "standard format specifiers",
  ## as specified by the grammar::
  ##
  ##   [[fill]align][sign][#][0][minimumwidth][.precision][type]
  ##
  ## This is only of interest if you want to write a custom ``format`` proc that
  ## should support the standard format specifiers. If ``ignoreUnknownSuffix`` is true,
  ## an unknown suffix after the ``type`` field is not an error.
  const alignChars = {'<', '>', '^'}
  result.fill = ' '
  result.align = '\0'
  result.sign = '-'
  var i = start
  if i + 1 < s.len and s[i+1] in alignChars:
    result.fill = s[i]
    result.align = s[i+1]
    inc i, 2
  elif i < s.len and s[i] in alignChars:
    result.align = s[i]
    inc i

  if i < s.len and s[i] in {'-', '+', ' '}:
    result.sign = s[i]
    inc i

  if i < s.len and s[i] == '#':
    result.alternateForm = true
    inc i

  if i+1 < s.len and s[i] == '0' and s[i+1] in {'0'..'9'}:
    result.padWithZero = true
    inc i

  let parsedLength = parseSaturatedNatural(s, result.minimumWidth, i)
  inc i, parsedLength
  if i < s.len and s[i] == '.':
    inc i
    let parsedLengthB = parseSaturatedNatural(s, result.precision, i)
    inc i, parsedLengthB
  else:
    result.precision = -1

  if i < s.len and s[i] in {'A'..'Z', 'a'..'z'}:
    result.typ = s[i]
    inc i
  result.endPosition = i
  if i != s.len and not ignoreUnknownSuffix:
    raise newException(ValueError,
      "invalid format string, cannot parse: " & s[i..^1])

proc formatValue*[T: SomeInteger](result: var string; value: T;
    specifier: string) =
  ## Standard format implementation for ``SomeInteger``. It makes little
  ## sense to call this directly, but it is required to exist
  ## by the ``&`` macro.
  if specifier.len == 0:
    result.add $value
    return
  let spec = parseStandardFormatSpecifier(specifier)
  var radix = 10
  case spec.typ
  of 'x', 'X': radix = 16
  of 'd', '\0': discard
  of 'b': radix = 2
  of 'o': radix = 8
  else:
    raise newException(ValueError,
      "invalid type in format string for number, expected one " &
      " of 'x', 'X', 'b', 'd', 'o' but got: " & spec.typ)
  result.add formatInt(value, radix, spec)

proc formatValue*(result: var string; value: SomeFloat; specifier: string) =
  ## Standard format implementation for ``SomeFloat``. It makes little
  ## sense to call this directly, but it is required to exist
  ## by the ``&`` macro.
  if specifier.len == 0:
    result.add $value
    return
  let spec = parseStandardFormatSpecifier(specifier)

  var fmode = ffDefault
  case spec.typ
  of 'e', 'E':
    fmode = ffScientific
  of 'f', 'F':
    fmode = ffDecimal
  of 'g', 'G':
    fmode = ffDefault
  of '\0': discard
  else:
    raise newException(ValueError,
      "invalid type in format string for number, expected one " &
      " of 'e', 'E', 'f', 'F', 'g', 'G' but got: " & spec.typ)

  var f = formatBiggestFloat(value, fmode, spec.precision)
  var sign = false
  if value >= 0.0:
    if spec.sign != '-':
      sign = true
      if value == 0.0:
        if 1.0 / value == Inf:
          # only insert the sign if value != negZero
          f.insert($spec.sign, 0)
      else:
        f.insert($spec.sign, 0)
  else:
    sign = true

  if spec.padWithZero:
    var signStr = ""
    if sign:
      signStr = $f[0]
      f = f[1..^1]

    let toFill = spec.minimumWidth - f.len - ord(sign)
    if toFill > 0:
      f = repeat('0', toFill) & f
    if sign:
      f = signStr & f

  # the default for numbers is right-alignment:
  let align = if spec.align == '\0': '>' else: spec.align
  let res = alignString(f, spec.minimumWidth, align, spec.fill)
  if spec.typ in {'A'..'Z'}:
    result.add toUpperAscii(res)
  else:
    result.add res

proc formatValue*(result: var string; value: string; specifier: string) =
  ## Standard format implementation for ``string``. It makes little
  ## sense to call this directly, but it is required to exist
  ## by the ``&`` macro.
  let spec = parseStandardFormatSpecifier(specifier)
  var value = value
  case spec.typ
  of 's', '\0': discard
  else:
    raise newException(ValueError,
      "invalid type in format string for string, expected 's', but got " &
      spec.typ)
  if spec.precision != -1:
    if spec.precision < runeLen(value):
      setLen(value, runeOffset(value, spec.precision))
  result.add alignString(value, spec.minimumWidth, spec.align, spec.fill)

proc formatValue[T: not SomeInteger](result: var string; value: T;
    specifier: string) =
  mixin `$`
  formatValue(result, $value, specifier)

template formatValue(result: var string; value: char; specifier: string) =
  result.add value

template formatValue(result: var string; value: cstring; specifier: string) =
  result.add value

proc strformatImpl(pattern: NimNode; openChar, closeChar: char): NimNode =
  if pattern.kind notin {nnkStrLit..nnkTripleStrLit}:
    error "string formatting (fmt(), &) only works with string literals", pattern
  if openChar == ':' or closeChar == ':':
    error "openChar and closeChar must not be ':'"
  let f = pattern.strVal
  var i = 0
  let res = genSym(nskVar, "fmtRes")
  result = newNimNode(nnkStmtListExpr, lineInfoFrom = pattern)
  # XXX: https://github.com/nim-lang/Nim/issues/8405
  # When compiling with -d:useNimRtl, certain procs such as `count` from the strutils
  # module are not accessible at compile-time:
  let expectedGrowth = when defined(useNimRtl): 0 else: count(f, '{') * 10
  result.add newVarStmt(res, newCall(bindSym"newStringOfCap",
                                     newLit(f.len + expectedGrowth)))
  var strlit = ""
  while i < f.len:
    if f[i] == openChar:
      inc i
      if f[i] == openChar:
        inc i
        strlit.add openChar
      else:
        if strlit.len > 0:
          result.add newCall(bindSym"add", res, newLit(strlit))
          strlit = ""

        var subexpr = ""
        while i < f.len and f[i] != closeChar and f[i] != ':':
          if f[i] == '=':
            let start = i
            inc i
            i += f.skipWhitespace(i)
            if f[i] == closeChar or f[i] == ':':
              result.add newCall(bindSym"add", res, newLit(subexpr & f[start ..< i]))
            else:
              subexpr.add f[start ..< i]
          else:
            subexpr.add f[i]
            inc i

        var x: NimNode
        try:
          x = parseExpr(subexpr)
        except ValueError:
          when declared(getCurrentExceptionMsg):
            let msg = getCurrentExceptionMsg()
            error("could not parse `" & subexpr & "`.\n" & msg, pattern)
          else:
            error("could not parse `" & subexpr & "`.\n", pattern)
        let formatSym = bindSym("formatValue", brOpen)
        var options = ""
        if f[i] == ':':
          inc i
          while i < f.len and f[i] != closeChar:
            options.add f[i]
            inc i
        if f[i] == closeChar:
          inc i
        else:
          doAssert false, "invalid format string: missing '}'"
        result.add newCall(formatSym, res, x, newLit(options))
    elif f[i] == closeChar:
      if f[i+1] == closeChar:
        strlit.add closeChar
        inc i, 2
      else:
        doAssert false, "invalid format string: '}' instead of '}}'"
        inc i
    else:
      strlit.add f[i]
      inc i
  if strlit.len > 0:
    result.add newCall(bindSym"add", res, newLit(strlit))
  result.add res
  when defined(debugFmtDsl):
    echo repr result

macro `&`*(pattern: string): untyped = strformatImpl(pattern, '{', '}')
  ## For a specification of the ``&`` macro, see the module level documentation.

macro fmt*(pattern: string): untyped = strformatImpl(pattern, '{', '}')
  ## An alias for ``&``.

macro fmt*(pattern: string; openChar, closeChar: char): untyped =
  ## Use ``openChar`` instead of '{' and ``closeChar`` instead of '}'
  runnableExamples:
    let testInt = 123
    doAssert "<testInt>".fmt('<', '>') == "123"
    doAssert """(()"foo" & "bar"())""".fmt(')', '(') == "(foobar)"
    doAssert """ ""{"123+123"}"" """.fmt('"', '"') == " \"{246}\" "
  strformatImpl(pattern, openChar.intVal.char, closeChar.intVal.char)

when isMainModule:
  template check(actual, expected: string) =
    doAssert actual == expected

  from strutils import toUpperAscii, repeat

  # Basic tests
  let s = "string"
  check &"{0} {s}", "0 string"
  check &"{s[0..2].toUpperAscii}", "STR"
  check &"{-10:04}", "-010"
  check &"{-10:<04}", "-010"
  check &"{-10:>04}", "-010"
  check &"0x{10:02X}", "0x0A"

  check &"{10:#04X}", "0x0A"

  check &"""{"test":#>5}""", "#test"
  check &"""{"test":>5}""", " test"

  check &"""{"test":#^7}""", "#test##"

  check &"""{"test": <5}""", "test "
  check &"""{"test":<5}""", "test "
  check &"{1f:.3f}", "1.000"
  check &"Hello, {s}!", "Hello, string!"

  # Tests for identifiers without parenthesis
  check &"{s} works{s}", "string worksstring"
  check &"{s:>7}", " string"
  doAssert(not compiles(&"{s_works}")) # parsed as identifier `s_works`

  # Misc general tests
  check &"{{}}", "{}"
  check &"{0}%", "0%"
  check &"{0}%asdf", "0%asdf"
  check &("\n{\"\\n\"}\n"), "\n\n\n"
  check &"""{"abc"}s""", "abcs"

  # String tests
  check &"""{"abc"}""", "abc"
  check &"""{"abc":>4}""", " abc"
  check &"""{"abc":<4}""", "abc "
  check &"""{"":>4}""", "    "
  check &"""{"":<4}""", "    "

  # Int tests
  check &"{12345}", "12345"
  check &"{ - 12345}", "-12345"
  check &"{12345:6}", " 12345"
  check &"{12345:>6}", " 12345"
  check &"{12345:4}", "12345"
  check &"{12345:08}", "00012345"
  check &"{-12345:08}", "-0012345"
  check &"{0:0}", "0"
  check &"{0:02}", "00"
  check &"{-1:3}", " -1"
  check &"{-1:03}", "-01"
  check &"{10}", "10"
  check &"{16:#X}", "0x10"
  check &"{16:^#7X}", " 0x10  "
  check &"{16:^+#7X}", " +0x10 "

  # Hex tests
  check &"{0:x}", "0"
  check &"{-0:x}", "0"
  check &"{255:x}", "ff"
  check &"{255:X}", "FF"
  check &"{-255:x}", "-ff"
  check &"{-255:X}", "-FF"
  check &"{255:x} uNaffeCteD CaSe", "ff uNaffeCteD CaSe"
  check &"{255:X} uNaffeCteD CaSe", "FF uNaffeCteD CaSe"
  check &"{255:4x}", "  ff"
  check &"{255:04x}", "00ff"
  check &"{-255:4x}", " -ff"
  check &"{-255:04x}", "-0ff"

  # Float tests
  check &"{123.456}", "123.456"
  check &"{-123.456}", "-123.456"
  check &"{123.456:.3f}", "123.456"
  check &"{123.456:+.3f}", "+123.456"
  check &"{-123.456:+.3f}", "-123.456"
  check &"{-123.456:.3f}", "-123.456"
  check &"{123.456:1g}", "123.456"
  check &"{123.456:.1f}", "123.5"
  check &"{123.456:.0f}", "123."
  check &"{123.456:>9.3f}", "  123.456"
  check &"{123.456:9.3f}", "  123.456"
  check &"{123.456:>9.4f}", " 123.4560"
  check &"{123.456:>9.0f}", "     123."
  check &"{123.456:<9.4f}", "123.4560 "

  # Float (scientific) tests
  check &"{123.456:e}", "1.234560e+02"
  check &"{123.456:>13e}", " 1.234560e+02"
  check &"{123.456:<13e}", "1.234560e+02 "
  check &"{123.456:.1e}", "1.2e+02"
  check &"{123.456:.2e}", "1.23e+02"
  check &"{123.456:.3e}", "1.235e+02"

  # Note: times.format adheres to the format protocol. Test that this
  # works:
  import times

  var dt = initDateTime(01, mJan, 2000, 00, 00, 00)
  check &"{dt:yyyy-MM-dd}", "2000-01-01"

  var tm = fromUnix(0)
  discard &"{tm}"

  var noww = now()
  check &"{noww}", $noww

  # Unicode string tests
  check &"""{"αβγ"}""", "αβγ"
  check &"""{"αβγ":>5}""", "  αβγ"
  check &"""{"αβγ":<5}""", "αβγ  "
  check &"""a{"a"}α{"α"}€{"€"}𐍈{"𐍈"}""", "aaαα€€𐍈𐍈"
  check &"""a{"a":2}α{"α":2}€{"€":2}𐍈{"𐍈":2}""", "aa αα €€ 𐍈𐍈 "
  # Invalid unicode sequences should be handled as plain strings.
  # Invalid examples taken from: https://stackoverflow.com/a/3886015/1804173
  let invalidUtf8 = [
    "\xc3\x28", "\xa0\xa1",
    "\xe2\x28\xa1", "\xe2\x82\x28",
    "\xf0\x28\x8c\xbc", "\xf0\x90\x28\xbc", "\xf0\x28\x8c\x28"
  ]
  for s in invalidUtf8:
    check &"{s:>5}", repeat(" ", 5-s.len) & s

  # bug #11089
  let flfoo: float = 1.0
  check &"{flfoo}", "1.0"

  # bug #11092
  check &"{high(int64)}", "9223372036854775807"
  check &"{low(int64)}", "-9223372036854775808"

  doAssert fmt"{'a'} {'b'}" == "a b"

  echo("All tests ok")
