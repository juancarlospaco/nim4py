#
#
#            Nim's Runtime Library
#        (c) Copyright 2019 Andreas Rumpf
#
#    See the file "copying.txt", included in this
#    distribution, for details about the copyright.
#

# ------------------- cell seq handling ---------------------------------------

type
  PCellArray = ptr UncheckedArray[PCell]
  CellSeq {.final, pure.} = object
    len, cap: int
    d: PCellArray

proc contains(s: CellSeq, c: PCell): bool {.inline.} =
  for i in 0 .. s.len-1:
    if s.d[i] == c: return true
  return false

proc add(s: var CellSeq, c: PCell) {.inline.} =
  if s.len >= s.cap:
    s.cap = s.cap * 3 div 2
    var d = cast[PCellArray](alloc(s.cap * sizeof(PCell)))
    copyMem(d, s.d, s.len * sizeof(PCell))
    dealloc(s.d)
    s.d = d
    # XXX: realloc?
  s.d[s.len] = c
  inc(s.len)

proc init(s: var CellSeq, cap: int = 1024) =
  s.len = 0
  s.cap = cap
  s.d = cast[PCellArray](alloc0(cap * sizeof(PCell)))

proc deinit(s: var CellSeq) =
  dealloc(s.d)
  s.d = nil
  s.len = 0
  s.cap = 0
