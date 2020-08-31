#
#
#            Nim's Runtime Library
#        (c) Copyright 2013 Dominik Picheta, Andreas Rumpf
#
#    See the file "copying.txt", included in this
#    distribution, for details about the copyright.
#

## This module implements an interface to Nim's `runtime type information`:idx:
## (`RTTI`:idx:). See the `marshal <marshal.html>`_ module for an example of
## what this module allows you to do.
##
## Note that even though ``Any`` and its operations hide the nasty low level
## details from its clients, it remains inherently unsafe! Also, Nim's
## runtime type information will evolve and may eventually be deprecated.
## As an alternative approach to programmatically understanding and
## manipulating types, consider using the `macros <macros.html>`_ package to
## work with the types' AST representation at compile time. See, for example,
## the `getTypeImpl proc<macros.html#getTypeImpl,NimNode>`_. As an alternative
## approach to storing arbitrary types at runtime, consider using generics.
##
##

{.push hints: off.}

include "system/inclrtl.nim"
include "system/hti.nim"

{.pop.}

type
  AnyKind* = enum      ## what kind of ``any`` it is
    akNone = 0,         ## invalid any
    akBool = 1,         ## any represents a ``bool``
    akChar = 2,         ## any represents a ``char``
    akEnum = 14,        ## any represents an enum
    akArray = 16,       ## any represents an array
    akObject = 17,      ## any represents an object
    akTuple = 18,       ## any represents a tuple
    akSet = 19,         ## any represents a set
    akRange = 20,       ## any represents a range
    akPtr = 21,         ## any represents a ptr
    akRef = 22,         ## any represents a ref
    akSequence = 24,    ## any represents a sequence
    akProc = 25,        ## any represents a proc
    akPointer = 26,     ## any represents a pointer
    akString = 28,      ## any represents a string
    akCString = 29,     ## any represents a cstring
    akInt = 31,         ## any represents an int
    akInt8 = 32,        ## any represents an int8
    akInt16 = 33,       ## any represents an int16
    akInt32 = 34,       ## any represents an int32
    akInt64 = 35,       ## any represents an int64
    akFloat = 36,       ## any represents a float
    akFloat32 = 37,     ## any represents a float32
    akFloat64 = 38,     ## any represents a float64
    akFloat128 = 39,    ## any represents a float128
    akUInt = 40,        ## any represents an unsigned int
    akUInt8 = 41,       ## any represents an unsigned int8
    akUInt16 = 42,      ## any represents an unsigned in16
    akUInt32 = 43,      ## any represents an unsigned int32
    akUInt64 = 44,      ## any represents an unsigned int64
#    akOpt = 44+18       ## the builtin 'opt' type.

  Any* = object          ## can represent any nim value; NOTE: the wrapped
                          ## value can be modified with its wrapper! This means
                          ## that ``Any`` keeps a non-traced pointer to its
                          ## wrapped value and **must not** live longer than
                          ## its wrapped value.
    value: pointer
    when defined(js):
      rawType: PNimType
    else:
      rawTypePtr: pointer

  ppointer = ptr pointer
  pbyteArray = ptr array[0xffff, int8]

  TGenericSeq {.importc.} = object
    len, space: int
    when defined(gogc):
      elemSize: int
  PGenSeq = ptr TGenericSeq

when not defined(js):
  template rawType(x: Any): PNimType =
    cast[PNimType](x.rawTypePtr)

  template `rawType=`(x: var Any, p: PNimType) =
    x.rawTypePtr = cast[pointer](p)

when defined(gogc):
  const GenericSeqSize = (3 * sizeof(int))
else:
  const GenericSeqSize = (2 * sizeof(int))

proc genericAssign(dest, src: pointer, mt: PNimType) {.importCompilerProc.}
proc genericShallowAssign(dest, src: pointer, mt: PNimType) {.
  importCompilerProc.}
proc incrSeq(seq: PGenSeq, elemSize, elemAlign: int): PGenSeq {.importCompilerProc.}
proc newObj(typ: PNimType, size: int): pointer {.importCompilerProc.}
proc newSeq(typ: PNimType, len: int): pointer {.importCompilerProc.}
proc objectInit(dest: pointer, typ: PNimType) {.importCompilerProc.}

template `+!!`(a, b): untyped = cast[pointer](cast[ByteAddress](a) + b)

proc getDiscriminant(aa: pointer, n: ptr TNimNode): int =
  assert(n.kind == nkCase)
  var d: int
  var a = cast[ByteAddress](aa)
  case n.typ.size
  of 1: d = ze(cast[ptr int8](a +% n.offset)[])
  of 2: d = ze(cast[ptr int16](a +% n.offset)[])
  of 4: d = int(cast[ptr int32](a +% n.offset)[])
  of 8: d = int(cast[ptr int64](a +% n.offset)[])
  else: assert(false)
  return d

proc selectBranch(aa: pointer, n: ptr TNimNode): ptr TNimNode =
  var discr = getDiscriminant(aa, n)
  if discr <% n.len:
    result = n.sons[discr]
    if result == nil: result = n.sons[n.len]
    # n.sons[n.len] contains the ``else`` part (but may be nil)
  else:
    result = n.sons[n.len]

proc newAny(value: pointer, rawType: PNimType): Any {.inline.} =
  result.value = value
  result.rawType = rawType

when declared(system.VarSlot):
  proc toAny*(x: VarSlot): Any {.inline.} =
    ## constructs a ``Any`` object from a variable slot ``x``.
    ## This captures `x`'s address, so `x` can be modified with its
    ## ``Any`` wrapper! The client needs to ensure that the wrapper
    ## **does not** live longer than `x`!
    ## This is provided for easier reflection capabilities of a debugger.
    result.value = x.address
    result.rawType = x.typ

proc toAny*[T](x: var T): Any {.inline.} =
  ## constructs a ``Any`` object from `x`. This captures `x`'s address, so
  ## `x` can be modified with its ``Any`` wrapper! The client needs to ensure
  ## that the wrapper **does not** live longer than `x`!
  newAny(addr(x), cast[PNimType](getTypeInfo(x)))

proc kind*(x: Any): AnyKind {.inline.} =
  ## get the type kind
  result = AnyKind(ord(x.rawType.kind))

proc size*(x: Any): int {.inline.} =
  ## returns the size of `x`'s type.
  result = x.rawType.size

proc baseTypeKind*(x: Any): AnyKind {.inline.} =
  ## get the base type's kind; ``akNone`` is returned if `x` has no base type.
  if x.rawType.base != nil:
    result = AnyKind(ord(x.rawType.base.kind))

proc baseTypeSize*(x: Any): int {.inline.} =
  ## returns the size of `x`'s basetype.
  if x.rawType.base != nil:
    result = x.rawType.base.size

proc invokeNew*(x: Any) =
  ## performs ``new(x)``. `x` needs to represent a ``ref``.
  assert x.rawType.kind == tyRef
  var z = newObj(x.rawType, x.rawType.base.size)
  genericAssign(x.value, addr(z), x.rawType)

proc invokeNewSeq*(x: Any, len: int) =
  ## performs ``newSeq(x, len)``. `x` needs to represent a ``seq``.
  assert x.rawType.kind == tySequence
  var z = newSeq(x.rawType, len)
  genericShallowAssign(x.value, addr(z), x.rawType)

proc extendSeq*(x: Any) =
  ## performs ``setLen(x, x.len+1)``. `x` needs to represent a ``seq``.
  assert x.rawType.kind == tySequence
  var y = cast[ptr PGenSeq](x.value)[]
  var z = incrSeq(y, x.rawType.base.size, x.rawType.base.align)
  # 'incrSeq' already freed the memory for us and copied over the RC!
  # So we simply copy the raw pointer into 'x.value':
  cast[ppointer](x.value)[] = z
  #genericShallowAssign(x.value, addr(z), x.rawType)

proc setObjectRuntimeType*(x: Any) =
  ## this needs to be called to set `x`'s runtime object type field.
  assert x.rawType.kind == tyObject
  objectInit(x.value, x.rawType)

proc skipRange(x: PNimType): PNimType {.inline.} =
  result = x
  if result.kind == tyRange: result = result.base

proc align(address, alignment: int): int =
  result = (address + (alignment - 1)) and not (alignment - 1)

proc `[]`*(x: Any, i: int): Any =
  ## accessor for an any `x` that represents an array or a sequence.
  case x.rawType.kind
  of tyArray:
    var bs = x.rawType.base.size
    if i >=% x.rawType.size div bs:
      raise newException(IndexDefect, formatErrorIndexBound(i, x.rawType.size div bs))
    return newAny(x.value +!! i*bs, x.rawType.base)
  of tySequence:
    var s = cast[ppointer](x.value)[]
    if s == nil: raise newException(ValueError, "sequence is nil")
    var bs = x.rawType.base.size
    if i >=% cast[PGenSeq](s).len:
      raise newException(IndexDefect, formatErrorIndexBound(i, cast[PGenSeq](s).len-1))
    return newAny(s +!! (align(GenericSeqSize, x.rawType.base.align)+i*bs), x.rawType.base)
  else: assert false

proc `[]=`*(x: Any, i: int, y: Any) =
  ## accessor for an any `x` that represents an array or a sequence.
  case x.rawType.kind
  of tyArray:
    var bs = x.rawType.base.size
    if i >=% x.rawType.size div bs:
      raise newException(IndexDefect, formatErrorIndexBound(i, x.rawType.size div bs))
    assert y.rawType == x.rawType.base
    genericAssign(x.value +!! i*bs, y.value, y.rawType)
  of tySequence:
    var s = cast[ppointer](x.value)[]
    if s == nil: raise newException(ValueError, "sequence is nil")
    var bs = x.rawType.base.size
    if i >=% cast[PGenSeq](s).len:
      raise newException(IndexDefect, formatErrorIndexBound(i, cast[PGenSeq](s).len-1))
    assert y.rawType == x.rawType.base
    genericAssign(s +!! (align(GenericSeqSize, x.rawType.base.align)+i*bs), y.value, y.rawType)
  else: assert false

proc len*(x: Any): int =
  ## len for an any `x` that represents an array or a sequence.
  case x.rawType.kind
  of tyArray:
    result = x.rawType.size div x.rawType.base.size
  of tySequence:
    let pgenSeq = cast[PGenSeq](cast[ppointer](x.value)[])
    if isNil(pgenSeq):
      result = 0
    else:
      result = pgenSeq.len
  else: assert false


proc base*(x: Any): Any =
  ## returns base Any (useful for inherited object types).
  result.rawType = x.rawType.base
  result.value = x.value


proc isNil*(x: Any): bool =
  ## `isNil` for an any `x` that represents a cstring, proc or
  ## some pointer type.
  assert x.rawType.kind in {tyCString, tyRef, tyPtr, tyPointer, tyProc}
  result = isNil(cast[ppointer](x.value)[])

proc getPointer*(x: Any): pointer =
  ## retrieve the pointer value out of `x`. ``x`` needs to be of kind
  ## ``akString``, ``akCString``, ``akProc``, ``akRef``, ``akPtr``,
  ## ``akPointer``, ``akSequence``.
  assert x.rawType.kind in {tyString, tyCString, tyRef, tyPtr, tyPointer,
                            tySequence, tyProc}
  result = cast[ppointer](x.value)[]

proc setPointer*(x: Any, y: pointer) =
  ## sets the pointer value of `x`. ``x`` needs to be of kind
  ## ``akString``, ``akCString``, ``akProc``, ``akRef``, ``akPtr``,
  ## ``akPointer``, ``akSequence``.
  assert x.rawType.kind in {tyString, tyCString, tyRef, tyPtr, tyPointer,
                            tySequence, tyProc}
  cast[ppointer](x.value)[] = y

proc fieldsAux(p: pointer, n: ptr TNimNode,
               ret: var seq[tuple[name: cstring, any: Any]]) =
  case n.kind
  of nkNone: assert(false)
  of nkSlot:
    ret.add((n.name, newAny(p +!! n.offset, n.typ)))
    assert ret[ret.len()-1][0] != nil
  of nkList:
    for i in 0..n.len-1: fieldsAux(p, n.sons[i], ret)
  of nkCase:
    var m = selectBranch(p, n)
    ret.add((n.name, newAny(p +!! n.offset, n.typ)))
    if m != nil: fieldsAux(p, m, ret)

iterator fields*(x: Any): tuple[name: string, any: Any] =
  ## iterates over every active field of the any `x` that represents an object
  ## or a tuple.
  assert x.rawType.kind in {tyTuple, tyObject}
  var p = x.value
  var t = x.rawType
  # XXX BUG: does not work yet, however is questionable anyway
  when false:
    if x.rawType.kind == tyObject: t = cast[ptr PNimType](x.value)[]
  var ret: seq[tuple[name: cstring, any: Any]] = @[]
  if t.kind == tyObject:
    while true:
      fieldsAux(p, t.node, ret)
      t = t.base
      if t.isNil: break
  else:
    fieldsAux(p, t.node, ret)
  for name, any in items(ret):
    yield ($name, any)

proc cmpIgnoreStyle(a, b: cstring): int {.noSideEffect.} =
  proc toLower(c: char): char {.inline.} =
    if c in {'A'..'Z'}: result = chr(ord(c) + (ord('a') - ord('A')))
    else: result = c
  var i = 0
  var j = 0
  while true:
    while a[i] == '_': inc(i)
    while b[j] == '_': inc(j) # BUGFIX: typo
    var aa = toLower(a[i])
    var bb = toLower(b[j])
    result = ord(aa) - ord(bb)
    if result != 0 or aa == '\0': break
    inc(i)
    inc(j)

proc getFieldNode(p: pointer, n: ptr TNimNode,
                  name: cstring): ptr TNimNode =
  case n.kind
  of nkNone: assert(false)
  of nkSlot:
    if cmpIgnoreStyle(n.name, name) == 0:
      result = n
  of nkList:
    for i in 0..n.len-1:
      result = getFieldNode(p, n.sons[i], name)
      if result != nil: break
  of nkCase:
    if cmpIgnoreStyle(n.name, name) == 0:
      result = n
    else:
      var m = selectBranch(p, n)
      if m != nil: result = getFieldNode(p, m, name)

proc `[]=`*(x: Any, fieldName: string, value: Any) =
  ## sets a field of `x`; `x` represents an object or a tuple.
  var t = x.rawType
  # XXX BUG: does not work yet, however is questionable anyway
  when false:
    if x.rawType.kind == tyObject: t = cast[ptr PNimType](x.value)[]
  assert x.rawType.kind in {tyTuple, tyObject}
  var n = getFieldNode(x.value, t.node, fieldName)
  if n != nil:
    assert n.typ == value.rawType
    genericAssign(x.value +!! n.offset, value.value, value.rawType)
  else:
    raise newException(ValueError, "invalid field name: " & fieldName)

proc `[]`*(x: Any, fieldName: string): Any =
  ## gets a field of `x`; `x` represents an object or a tuple.
  var t = x.rawType
  # XXX BUG: does not work yet, however is questionable anyway
  when false:
    if x.rawType.kind == tyObject: t = cast[ptr PNimType](x.value)[]
  assert x.rawType.kind in {tyTuple, tyObject}
  var n = getFieldNode(x.value, t.node, fieldName)
  if n != nil:
    result.value = x.value +!! n.offset
    result.rawType = n.typ
  elif x.rawType.kind == tyObject and x.rawType.base != nil:
    return `[]`(newAny(x.value, x.rawType.base), fieldName)
  else:
    raise newException(ValueError, "invalid field name: " & fieldName)

proc `[]`*(x: Any): Any =
  ## dereference operation for the any `x` that represents a ptr or a ref.
  assert x.rawType.kind in {tyRef, tyPtr}
  result.value = cast[ppointer](x.value)[]
  result.rawType = x.rawType.base

proc `[]=`*(x, y: Any) =
  ## dereference operation for the any `x` that represents a ptr or a ref.
  assert x.rawType.kind in {tyRef, tyPtr}
  assert y.rawType == x.rawType.base
  genericAssign(cast[ppointer](x.value)[], y.value, y.rawType)

proc getInt*(x: Any): int =
  ## retrieve the int value out of `x`. `x` needs to represent an int.
  assert skipRange(x.rawType).kind == tyInt
  result = cast[ptr int](x.value)[]

proc getInt8*(x: Any): int8 =
  ## retrieve the int8 value out of `x`. `x` needs to represent an int8.
  assert skipRange(x.rawType).kind == tyInt8
  result = cast[ptr int8](x.value)[]

proc getInt16*(x: Any): int16 =
  ## retrieve the int16 value out of `x`. `x` needs to represent an int16.
  assert skipRange(x.rawType).kind == tyInt16
  result = cast[ptr int16](x.value)[]

proc getInt32*(x: Any): int32 =
  ## retrieve the int32 value out of `x`. `x` needs to represent an int32.
  assert skipRange(x.rawType).kind == tyInt32
  result = cast[ptr int32](x.value)[]

proc getInt64*(x: Any): int64 =
  ## retrieve the int64 value out of `x`. `x` needs to represent an int64.
  assert skipRange(x.rawType).kind == tyInt64
  result = cast[ptr int64](x.value)[]

proc getBiggestInt*(x: Any): BiggestInt =
  ## retrieve the integer value out of `x`. `x` needs to represent
  ## some integer, a bool, a char, an enum or a small enough bit set.
  ## The value might be sign-extended to ``BiggestInt``.
  var t = skipRange(x.rawType)
  case t.kind
  of tyInt: result = BiggestInt(cast[ptr int](x.value)[])
  of tyInt8: result = BiggestInt(cast[ptr int8](x.value)[])
  of tyInt16: result = BiggestInt(cast[ptr int16](x.value)[])
  of tyInt32: result = BiggestInt(cast[ptr int32](x.value)[])
  of tyInt64, tyUInt64: result = BiggestInt(cast[ptr int64](x.value)[])
  of tyBool: result = BiggestInt(cast[ptr bool](x.value)[])
  of tyChar: result = BiggestInt(cast[ptr char](x.value)[])
  of tyEnum, tySet:
    case t.size
    of 1: result = ze64(cast[ptr int8](x.value)[])
    of 2: result = ze64(cast[ptr int16](x.value)[])
    of 4: result = BiggestInt(cast[ptr int32](x.value)[])
    of 8: result = BiggestInt(cast[ptr int64](x.value)[])
    else: assert false
  of tyUInt: result = BiggestInt(cast[ptr uint](x.value)[])
  of tyUInt8: result = BiggestInt(cast[ptr uint8](x.value)[])
  of tyUInt16: result = BiggestInt(cast[ptr uint16](x.value)[])
  of tyUInt32: result = BiggestInt(cast[ptr uint32](x.value)[])
  else: assert false

proc setBiggestInt*(x: Any, y: BiggestInt) =
  ## sets the integer value of `x`. `x` needs to represent
  ## some integer, a bool, a char, an enum or a small enough bit set.
  var t = skipRange(x.rawType)
  case t.kind
  of tyInt: cast[ptr int](x.value)[] = int(y)
  of tyInt8: cast[ptr int8](x.value)[] = int8(y)
  of tyInt16: cast[ptr int16](x.value)[] = int16(y)
  of tyInt32: cast[ptr int32](x.value)[] = int32(y)
  of tyInt64, tyUInt64: cast[ptr int64](x.value)[] = int64(y)
  of tyBool: cast[ptr bool](x.value)[] = y != 0
  of tyChar: cast[ptr char](x.value)[] = chr(y.int)
  of tyEnum, tySet:
    case t.size
    of 1: cast[ptr int8](x.value)[] = toU8(y.int)
    of 2: cast[ptr int16](x.value)[] = toU16(y.int)
    of 4: cast[ptr int32](x.value)[] = int32(y)
    of 8: cast[ptr int64](x.value)[] = y
    else: assert false
  of tyUInt: cast[ptr uint](x.value)[] = uint(y)
  of tyUInt8: cast[ptr uint8](x.value)[] = uint8(y)
  of tyUInt16: cast[ptr uint16](x.value)[] = uint16(y)
  of tyUInt32: cast[ptr uint32](x.value)[] = uint32(y)
  else: assert false

proc getUInt*(x: Any): uint =
  ## retrieve the uint value out of `x`, `x` needs to represent an uint.
  assert skipRange(x.rawType).kind == tyUInt
  result = cast[ptr uint](x.value)[]

proc getUInt8*(x: Any): uint8 =
  ## retrieve the uint8 value out of `x`, `x` needs to represent an
  ## uint8.
  assert skipRange(x.rawType).kind == tyUInt8
  result = cast[ptr uint8](x.value)[]

proc getUInt16*(x: Any): uint16 =
  ## retrieve the uint16 value out of `x`, `x` needs to represent an
  ## uint16.
  assert skipRange(x.rawType).kind == tyUInt16
  result = cast[ptr uint16](x.value)[]

proc getUInt32*(x: Any): uint32 =
  ## retrieve the uint32 value out of `x`, `x` needs to represent an
  ## uint32.
  assert skipRange(x.rawType).kind == tyUInt32
  result = cast[ptr uint32](x.value)[]

proc getUInt64*(x: Any): uint64 =
  ## retrieve the uint64 value out of `x`, `x` needs to represent an
  ## uint64.
  assert skipRange(x.rawType).kind == tyUInt64
  result = cast[ptr uint64](x.value)[]

proc getBiggestUint*(x: Any): uint64 =
  ## retrieve the unsigned integer value out of `x`. `x` needs to
  ## represent an unsigned integer.
  var t = skipRange(x.rawType)
  case t.kind
  of tyUInt: result = uint64(cast[ptr uint](x.value)[])
  of tyUInt8: result = uint64(cast[ptr uint8](x.value)[])
  of tyUInt16: result = uint64(cast[ptr uint16](x.value)[])
  of tyUInt32: result = uint64(cast[ptr uint32](x.value)[])
  of tyUInt64: result = uint64(cast[ptr uint64](x.value)[])
  else: assert false

proc setBiggestUint*(x: Any; y: uint64) =
  ## sets the unsigned integer value of `c`. `c` needs to represent an
  ## unsigned integer.
  var t = skipRange(x.rawType)
  case t.kind:
  of tyUInt: cast[ptr uint](x.value)[] = uint(y)
  of tyUInt8: cast[ptr uint8](x.value)[] = uint8(y)
  of tyUInt16: cast[ptr uint16](x.value)[] = uint16(y)
  of tyUInt32: cast[ptr uint32](x.value)[] = uint32(y)
  of tyUInt64: cast[ptr uint64](x.value)[] = uint64(y)
  else: assert false

proc getChar*(x: Any): char =
  ## retrieve the char value out of `x`. `x` needs to represent a char.
  var t = skipRange(x.rawType)
  assert t.kind == tyChar
  result = cast[ptr char](x.value)[]

proc getBool*(x: Any): bool =
  ## retrieve the bool value out of `x`. `x` needs to represent a bool.
  var t = skipRange(x.rawType)
  assert t.kind == tyBool
  result = cast[ptr bool](x.value)[]

proc skipRange*(x: Any): Any =
  ## skips the range information of `x`.
  assert x.rawType.kind == tyRange
  result.rawType = x.rawType.base
  result.value = x.value

proc getEnumOrdinal*(x: Any, name: string): int =
  ## gets the enum field ordinal from `name`. `x` needs to represent an enum
  ## but is only used to access the type information. In case of an error
  ## ``low(int)`` is returned.
  var typ = skipRange(x.rawType)
  assert typ.kind == tyEnum
  var n = typ.node
  var s = n.sons
  for i in 0 .. n.len-1:
    if cmpIgnoreStyle($s[i].name, name) == 0:
      if ntfEnumHole notin typ.flags:
        return i
      else:
        return s[i].offset
  result = low(int)

proc getEnumField*(x: Any, ordinalValue: int): string =
  ## gets the enum field name as a string. `x` needs to represent an enum
  ## but is only used to access the type information. The field name of
  ## `ordinalValue` is returned.
  var typ = skipRange(x.rawType)
  assert typ.kind == tyEnum
  var e = ordinalValue
  if ntfEnumHole notin typ.flags:
    if e <% typ.node.len:
      return $typ.node.sons[e].name
  else:
    # ugh we need a slow linear search:
    var n = typ.node
    var s = n.sons
    for i in 0 .. n.len-1:
      if s[i].offset == e: return $s[i].name
  result = $e

proc getEnumField*(x: Any): string =
  ## gets the enum field name as a string. `x` needs to represent an enum.
  result = getEnumField(x, getBiggestInt(x).int)

proc getFloat*(x: Any): float =
  ## retrieve the float value out of `x`. `x` needs to represent an float.
  assert skipRange(x.rawType).kind == tyFloat
  result = cast[ptr float](x.value)[]

proc getFloat32*(x: Any): float32 =
  ## retrieve the float32 value out of `x`. `x` needs to represent an float32.
  assert skipRange(x.rawType).kind == tyFloat32
  result = cast[ptr float32](x.value)[]

proc getFloat64*(x: Any): float64 =
  ## retrieve the float64 value out of `x`. `x` needs to represent an float64.
  assert skipRange(x.rawType).kind == tyFloat64
  result = cast[ptr float64](x.value)[]

proc getBiggestFloat*(x: Any): BiggestFloat =
  ## retrieve the float value out of `x`. `x` needs to represent
  ## some float. The value is extended to ``BiggestFloat``.
  case skipRange(x.rawType).kind
  of tyFloat: result = BiggestFloat(cast[ptr float](x.value)[])
  of tyFloat32: result = BiggestFloat(cast[ptr float32](x.value)[])
  of tyFloat64: result = BiggestFloat(cast[ptr float64](x.value)[])
  else: assert false

proc setBiggestFloat*(x: Any, y: BiggestFloat) =
  ## sets the float value of `x`. `x` needs to represent
  ## some float.
  case skipRange(x.rawType).kind
  of tyFloat: cast[ptr float](x.value)[] = y
  of tyFloat32: cast[ptr float32](x.value)[] = y.float32
  of tyFloat64: cast[ptr float64](x.value)[] = y
  else: assert false

proc getString*(x: Any): string =
  ## retrieve the string value out of `x`. `x` needs to represent a string.
  assert x.rawType.kind == tyString
  if not isNil(cast[ptr pointer](x.value)[]):
    result = cast[ptr string](x.value)[]

proc setString*(x: Any, y: string) =
  ## sets the string value of `x`. `x` needs to represent a string.
  assert x.rawType.kind == tyString
  cast[ptr string](x.value)[] = y

proc getCString*(x: Any): cstring =
  ## retrieve the cstring value out of `x`. `x` needs to represent a cstring.
  assert x.rawType.kind == tyCString
  result = cast[ptr cstring](x.value)[]

proc assign*(x, y: Any) =
  ## copies the value of `y` to `x`. The assignment operator for ``Any``
  ## does NOT do this; it performs a shallow copy instead!
  assert y.rawType == x.rawType
  genericAssign(x.value, y.value, y.rawType)

iterator elements*(x: Any): int =
  ## iterates over every element of `x` that represents a Nim bitset.
  assert x.rawType.kind == tySet
  var typ = x.rawType
  var p = x.value
  # "typ.slots.len" field is for sets the "first" field
  var u: int64
  case typ.size
  of 1: u = ze64(cast[ptr int8](p)[])
  of 2: u = ze64(cast[ptr int16](p)[])
  of 4: u = ze64(cast[ptr int32](p)[])
  of 8: u = cast[ptr int64](p)[]
  else:
    var a = cast[pbyteArray](p)
    for i in 0 .. typ.size*8-1:
      if (ze(a[i div 8]) and (1 shl (i mod 8))) != 0:
        yield i+typ.node.len
  if typ.size <= 8:
    for i in 0..sizeof(int64)*8-1:
      if (u and (1'i64 shl int64(i))) != 0'i64:
        yield i+typ.node.len

proc inclSetElement*(x: Any, elem: int) =
  ## includes an element `elem` in `x`. `x` needs to represent a Nim bitset.
  assert x.rawType.kind == tySet
  var typ = x.rawType
  var p = x.value
  # "typ.slots.len" field is for sets the "first" field
  var e = elem - typ.node.len
  case typ.size
  of 1:
    var a = cast[ptr int8](p)
    a[] = a[] or (1'i8 shl int8(e))
  of 2:
    var a = cast[ptr int16](p)
    a[] = a[] or (1'i16 shl int16(e))
  of 4:
    var a = cast[ptr int32](p)
    a[] = a[] or (1'i32 shl int32(e))
  of 8:
    var a = cast[ptr int64](p)
    a[] = a[] or (1'i64 shl e)
  else:
    var a = cast[pbyteArray](p)
    a[e shr 3] = toU8(a[e shr 3] or (1 shl (e and 7)))

when isMainModule:
  type
    TE = enum
      blah, blah2

    TestObj = object
      test, asd: int
      case test2: TE
      of blah:
        help: string
      else:
        nil

  var test = @[0,1,2,3,4]
  var x = toAny(test)
  var y = 78
  x[4] = toAny(y)
  assert cast[ptr int](x[2].value)[] == 2

  var test2: tuple[name: string, s: int] = ("test", 56)
  var x2 = toAny(test2)
  var i = 0
  for n, a in fields(x2):
    case i
    of 0: assert n == "name" and $a.kind == "akString"
    of 1: assert n == "s" and $a.kind == "akInt"
    else: assert false
    inc i

  var test3: TestObj
  test3.test = 42
  test3 = TestObj(test2: blah2)
  var x3 = toAny(test3)
  i = 0
  for n, a in fields(x3):
    case i
    of 0: assert n == "test" and $a.kind == "akInt"
    of 1: assert n == "asd" and $a.kind == "akInt"
    of 2: assert n == "test2" and $a.kind == "akEnum"
    else: assert false
    inc i

  var test4: ref string
  new(test4)
  test4[] = "test"
  var x4 = toAny(test4)
  assert($x4[].kind() == "akString")

  block:
    # gimme a new scope dammit
    var myarr: array[0..4, array[0..4, string]] = [
      ["test", "1", "2", "3", "4"], ["test", "1", "2", "3", "4"],
      ["test", "1", "2", "3", "4"], ["test", "1", "2", "3", "4"],
      ["test", "1", "2", "3", "4"]]
    var m = toAny(myArr)
    for i in 0 .. m.len-1:
      for j in 0 .. m[i].len-1:
        echo getString(m[i][j])
