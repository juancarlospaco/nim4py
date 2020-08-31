#
#
#            Nim's Runtime Library
#        (c) Copyright 2009 Andreas Rumpf
#
#    See the file "copying.txt", included in this
#    distribution, for details about the copyright.
#

## This module implements a simple high performance `CSV`:idx:
## (`comma separated value`:idx:) parser.
##
## Basic usage
## ===========
##
## .. code-block:: nim
##   import parsecsv
##   from os import paramStr
##   from streams import newFileStream
##
##   var s = newFileStream(paramStr(1), fmRead)
##   if s == nil:
##     quit("cannot open the file" & paramStr(1))
##
##   var x: CsvParser
##   open(x, s, paramStr(1))
##   while readRow(x):
##     echo "new row: "
##     for val in items(x.row):
##       echo "##", val, "##"
##   close(x)
##
## For CSV files with a header row, the header can be read and then used as a
## reference for item access with `rowEntry <#rowEntry,CsvParser,string>`_:
##
## .. code-block:: nim
##   import parsecsv
##
##   # Prepare a file
##   let content = """One,Two,Three,Four
##   1,2,3,4
##   10,20,30,40
##   100,200,300,400
##   """
##   writeFile("temp.csv", content)
##
##   var p: CsvParser
##   p.open("temp.csv")
##   p.readHeaderRow()
##   while p.readRow():
##     echo "new row: "
##     for col in items(p.headers):
##       echo "##", col, ":", p.rowEntry(col), "##"
##   p.close()
##
## See also
## ========
##
## * `streams module <streams.html>`_ for using
##   `open proc <#open,CsvParser,Stream,string,char,char,char>`_
##   and other stream processing (like `close proc <streams.html#close,Stream>`_)
## * `parseopt module <parseopt.html>`_ for a command line parser
## * `parsecfg module <parsecfg.html>`_ for a configuration file parser
## * `parsexml module <parsexml.html>`_ for a XML / HTML parser
## * `parsesql module <parsesql.html>`_ for a SQL parser
## * `other parsers <lib.html#pure-libraries-parsers>`_ for other parsers

import
  lexbase, streams

type
  CsvRow* = seq[string] ## A row in a CSV file.
  CsvParser* = object of BaseLexer ## The parser object.
                                   ##
                                   ## It consists of two public fields:
                                   ## * `row` is the current row
                                   ## * `headers` are the columns that are defined in the csv file
                                   ##   (read using `readHeaderRow <#readHeaderRow,CsvParser>`_).
                                   ##   Used with `rowEntry <#rowEntry,CsvParser,string>`_).
    row*: CsvRow
    filename: string
    sep, quote, esc: char
    skipWhite: bool
    currRow: int
    headers*: seq[string]

  CsvError* = object of IOError ## An exception that is raised if
                                ## a parsing error occurs.

proc raiseEInvalidCsv(filename: string, line, col: int,
                      msg: string) {.noreturn.} =
  var e: ref CsvError
  new(e)
  if filename.len == 0:
    e.msg = "Error: " & msg
  else:
    e.msg = filename & "(" & $line & ", " & $col & ") Error: " & msg
  raise e

proc error(my: CsvParser, pos: int, msg: string) =
  raiseEInvalidCsv(my.filename, my.lineNumber, getColNumber(my, pos), msg)

proc open*(my: var CsvParser, input: Stream, filename: string,
           separator = ',', quote = '"', escape = '\0',
           skipInitialSpace = false) =
  ## Initializes the parser with an input stream. `Filename` is only used
  ## for nice error messages. The parser's behaviour can be controlled by
  ## the diverse optional parameters:
  ## - `separator`: character used to separate fields
  ## - `quote`: Used to quote fields containing special characters like
  ##   `separator`, `quote` or new-line characters. '\\0' disables the parsing
  ##   of quotes.
  ## - `escape`: removes any special meaning from the following character;
  ##   '\\0' disables escaping; if escaping is disabled and `quote` is not '\\0',
  ##   two `quote` characters are parsed one literal `quote` character.
  ## - `skipInitialSpace`: If true, whitespace immediately following the
  ##   `separator` is ignored.
  ##
  ## See also:
  ## * `open proc <#open,CsvParser,string,char,char,char>`_ which creates the
  ##   file stream for you
  runnableExamples:
    import streams
    var strm = newStringStream("One,Two,Three\n1,2,3\n10,20,30")
    var parser: CsvParser
    parser.open(strm, "tmp.csv")
    parser.close()
    strm.close()

  lexbase.open(my, input)
  my.filename = filename
  my.sep = separator
  my.quote = quote
  my.esc = escape
  my.skipWhite = skipInitialSpace
  my.row = @[]
  my.currRow = 0

proc open*(my: var CsvParser, filename: string,
           separator = ',', quote = '"', escape = '\0',
           skipInitialSpace = false) =
  ## Similar to the `other open proc<#open,CsvParser,Stream,string,char,char,char>`_,
  ## but creates the file stream for you.
  runnableExamples:
    from os import removeFile
    writeFile("tmp.csv", "One,Two,Three\n1,2,3\n10,20,300")
    var parser: CsvParser
    parser.open("tmp.csv")
    parser.close()
    removeFile("tmp.csv")

  var s = newFileStream(filename, fmRead)
  if s == nil: my.error(0, "cannot open: " & filename)
  open(my, s, filename, separator,
       quote, escape, skipInitialSpace)

proc parseField(my: var CsvParser, a: var string) =
  var pos = my.bufpos
  if my.skipWhite:
    while my.buf[pos] in {' ', '\t'}: inc(pos)
  setLen(a, 0) # reuse memory
  if my.buf[pos] == my.quote and my.quote != '\0':
    inc(pos)
    while true:
      let c = my.buf[pos]
      if c == '\0':
        my.bufpos = pos # can continue after exception?
        error(my, pos, my.quote & " expected")
        break
      elif c == my.quote:
        if my.esc == '\0' and my.buf[pos+1] == my.quote:
          add(a, my.quote)
          inc(pos, 2)
        else:
          inc(pos)
          break
      elif c == my.esc:
        add(a, my.buf[pos+1])
        inc(pos, 2)
      else:
        case c
        of '\c':
          pos = handleCR(my, pos)
          add(a, "\n")
        of '\l':
          pos = handleLF(my, pos)
          add(a, "\n")
        else:
          add(a, c)
          inc(pos)
  else:
    while true:
      let c = my.buf[pos]
      if c == my.sep: break
      if c in {'\c', '\l', '\0'}: break
      add(a, c)
      inc(pos)
  my.bufpos = pos

proc processedRows*(my: var CsvParser): int =
  ## Returns number of the processed rows.
  ##
  ## But even if `readRow <#readRow,CsvParser,int>`_ arrived at EOF then
  ## processed rows counter is incremented.
  runnableExamples:
    import streams

    var strm = newStringStream("One,Two,Three\n1,2,3")
    var parser: CsvParser
    parser.open(strm, "tmp.csv")
    doAssert parser.readRow()
    doAssert parser.processedRows() == 1
    doAssert parser.readRow()
    doAssert parser.processedRows() == 2
    ## Even if `readRow` arrived at EOF then `processedRows` is incremented.
    doAssert parser.readRow() == false
    doAssert parser.processedRows() == 3
    doAssert parser.readRow() == false
    doAssert parser.processedRows() == 4
    parser.close()
    strm.close()

  return my.currRow

proc readRow*(my: var CsvParser, columns = 0): bool =
  ## Reads the next row; if `columns` > 0, it expects the row to have
  ## exactly this many columns. Returns false if the end of the file
  ## has been encountered else true.
  ##
  ## Blank lines are skipped.
  runnableExamples:
    import streams
    var strm = newStringStream("One,Two,Three\n1,2,3\n\n10,20,30")
    var parser: CsvParser
    parser.open(strm, "tmp.csv")
    doAssert parser.readRow()
    doAssert parser.row == @["One", "Two", "Three"]
    doAssert parser.readRow()
    doAssert parser.row == @["1", "2", "3"]
    ## Blank lines are skipped.
    doAssert parser.readRow()
    doAssert parser.row == @["10", "20", "30"]

    var emptySeq: seq[string]
    doAssert parser.readRow() == false
    doAssert parser.row == emptySeq
    doAssert parser.readRow() == false
    doAssert parser.row == emptySeq

    parser.close()
    strm.close()

  var col = 0 # current column
  let oldpos = my.bufpos
  # skip initial empty lines #8365
  while true:
    case my.buf[my.bufpos]
    of '\c': my.bufpos = handleCR(my, my.bufpos)
    of '\l': my.bufpos = handleLF(my, my.bufpos)
    else: break
  while my.buf[my.bufpos] != '\0':
    let oldlen = my.row.len
    if oldlen < col+1:
      setLen(my.row, col+1)
      my.row[col] = ""
    parseField(my, my.row[col])
    inc(col)
    if my.buf[my.bufpos] == my.sep:
      inc(my.bufpos)
    else:
      case my.buf[my.bufpos]
      of '\c', '\l':
        # skip empty lines:
        while true:
          case my.buf[my.bufpos]
          of '\c': my.bufpos = handleCR(my, my.bufpos)
          of '\l': my.bufpos = handleLF(my, my.bufpos)
          else: break
      of '\0': discard
      else: error(my, my.bufpos, my.sep & " expected")
      break

  setLen(my.row, col)
  result = col > 0
  if result and col != columns and columns > 0:
    error(my, oldpos+1, $columns & " columns expected, but found " &
          $col & " columns")
  inc(my.currRow)

proc close*(my: var CsvParser) {.inline.} =
  ## Closes the parser `my` and its associated input stream.
  lexbase.close(my)

proc readHeaderRow*(my: var CsvParser) =
  ## Reads the first row and creates a look-up table for column numbers
  ## See also:
  ## * `rowEntry proc <#rowEntry,CsvParser,string>`_
  runnableExamples:
    import streams

    var strm = newStringStream("One,Two,Three\n1,2,3")
    var parser: CsvParser
    parser.open(strm, "tmp.csv")

    parser.readHeaderRow()
    doAssert parser.headers == @["One", "Two", "Three"]
    doAssert parser.row == @["One", "Two", "Three"]

    doAssert parser.readRow()
    doAssert parser.headers == @["One", "Two", "Three"]
    doAssert parser.row == @["1", "2", "3"]

    parser.close()
    strm.close()

  let present = my.readRow()
  if present:
    my.headers = my.row

proc rowEntry*(my: var CsvParser, entry: string): var string =
  ## Accesses a specified `entry` from the current row.
  ##
  ## Assumes that `readHeaderRow <#readHeaderRow,CsvParser>`_ has already been
  ## called.
  runnableExamples:
    import streams
    var strm = newStringStream("One,Two,Three\n1,2,3\n\n10,20,30")
    var parser: CsvParser
    parser.open(strm, "tmp.csv")
    ## Need calling `readHeaderRow`.
    parser.readHeaderRow()
    doAssert parser.readRow()
    doAssert parser.rowEntry("One") == "1"
    doAssert parser.rowEntry("Two") == "2"
    doAssert parser.rowEntry("Three") == "3"
    ## `parser.rowEntry("NotExistEntry")` causes SIGSEGV fault.
    parser.close()
    strm.close()

  let index = my.headers.find(entry)
  if index >= 0:
    result = my.row[index]

when not defined(testing) and isMainModule:
  import os
  var s = newFileStream(paramStr(1), fmRead)
  if s == nil: quit("cannot open the file" & paramStr(1))
  var x: CsvParser
  open(x, s, paramStr(1))
  while readRow(x):
    echo "new row: "
    for val in items(x.row):
      echo "##", val, "##"
  close(x)

when isMainModule:
  import os
  import strutils
  block: # Tests for reading the header row
    let content = "\nOne,Two,Three,Four\n1,2,3,4\n10,20,30,40,\n100,200,300,400\n"
    writeFile("temp.csv", content)

    var p: CsvParser
    p.open("temp.csv")
    p.readHeaderRow()
    while p.readRow():
      let zeros = repeat('0', p.currRow-2)
      doAssert p.rowEntry("One") == "1" & zeros
      doAssert p.rowEntry("Two") == "2" & zeros
      doAssert p.rowEntry("Three") == "3" & zeros
      doAssert p.rowEntry("Four") == "4" & zeros
    p.close()

    when not defined(testing):
      var parser: CsvParser
      parser.open("temp.csv")
      parser.readHeaderRow()
      while parser.readRow():
        echo "new row: "
        for col in items(parser.headers):
          echo "##", col, ":", parser.rowEntry(col), "##"
      parser.close()
      removeFile("temp.csv")

    # Tidy up
    removeFile("temp.csv")
