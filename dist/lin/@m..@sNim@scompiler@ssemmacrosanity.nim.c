/* Generated by Nim Compiler v1.3.5 */
/*   (c) 2020 Andreas Rumpf */
/* The generated code is subject to the original license. */
#define NIM_INTBITS 64

/* section: NIM_merge_HEADERS */

#include "nimbase.h"
#include <string.h>
#undef LANGUAGE_C
#undef MIPSEB
#undef MIPSEL
#undef PPC
#undef R3000
#undef R4000
#undef i386
#undef linux
#undef mips
#undef near
#undef far
#undef powerpc
#undef unix

/* section: NIM_merge_FRAME_DEFINES */
#define nimfr_(x, y)
#define nimln_(x, y)

/* section: NIM_merge_FORWARD_TYPES */
typedef struct tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw;
typedef struct tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ;
typedef struct tyObject_ConfigRefcolonObjectType___LaK09ayL9alwKUad7rts0rTw tyObject_ConfigRefcolonObjectType___LaK09ayL9alwKUad7rts0rTw;
typedef struct tyObject_TLineInfo__WGx4rAexNXnczy1Avn646Q tyObject_TLineInfo__WGx4rAexNXnczy1Avn646Q;
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
typedef struct tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w;
typedef struct tyObject_TIdent__GufRQq9c0miSybX3zBD4tyA tyObject_TIdent__GufRQq9c0miSybX3zBD4tyA;
typedef struct tySequence__ehmV9bTklH2Gt9cXHV9c0HLeQ tySequence__ehmV9bTklH2Gt9cXHV9c0HLeQ;
typedef struct tyObject_TIdObj__iIXPrEsiKHiioLj0HSkQhA tyObject_TIdObj__iIXPrEsiKHiioLj0HSkQhA;
typedef struct RootObj RootObj;
typedef struct TNimType TNimType;
typedef struct TNimNode TNimNode;
typedef struct tySequence__Ef05srmQTDulnBdXR4Ja6Q tySequence__Ef05srmQTDulnBdXR4Ja6Q;
typedef struct tySequence__MvZmat48bhe9b6x9aUD58D5Q tySequence__MvZmat48bhe9b6x9aUD58D5Q;
typedef struct tyObject_TLoc__EtHNvCB0bgfu9bFjzx9cb6aA tyObject_TLoc__EtHNvCB0bgfu9bFjzx9cb6aA;
typedef struct tyObject_RopeObj__OFzf0kSiPTcNreUIeJgWVA tyObject_RopeObj__OFzf0kSiPTcNreUIeJgWVA;
typedef struct tySequence__DXS6mEo7PVUFJkirsQ9bNQA tySequence__DXS6mEo7PVUFJkirsQ9bNQA;
typedef struct tyObject_TStrTable__f07aOS3dr28kGa5wcE29aFA tyObject_TStrTable__f07aOS3dr28kGa5wcE29aFA;
typedef struct tySequence__DfgJFJEYoj4YBAHLZPl5lQ tySequence__DfgJFJEYoj4YBAHLZPl5lQ;
typedef struct tyObject_TLib__NBMxlJ6g3utqUlplqTTHkA tyObject_TLib__NBMxlJ6g3utqUlplqTTHkA;
typedef struct tyTuple__kN8up2W6YKc5YA9avn5mV5w tyTuple__kN8up2W6YKc5YA9avn5mV5w;
typedef struct tyTuple__zwpS6d6iewrdlBSTNFoyVA tyTuple__zwpS6d6iewrdlBSTNFoyVA;
typedef struct tyObject_TInstantiation__5LqgVn6Tq9ainQRK7TQAQxA tyObject_TInstantiation__5LqgVn6Tq9ainQRK7TQAQxA;

/* section: NIM_merge_TYPES */
typedef NU64 tySet_tyEnum_TTypeKind__9a3YiReNVD0IJHWFKgXRe9ag;
struct tyObject_TLineInfo__WGx4rAexNXnczy1Avn646Q {
NU16 line;
NI16 col;
NI32 fileIndex;
};
typedef NU32 tySet_tyEnum_TNodeFlag__jyh9acXHkhZANSSvPIY7ZLg;
typedef NU8 tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw;
struct TGenericSeq {
NI len;
NI reserved;
};
struct NimStringDesc {
  TGenericSeq Sup;
NIM_CHAR data[SEQ_DECL_SIZE];
};
struct tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw {
tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* typ;
tyObject_TLineInfo__WGx4rAexNXnczy1Avn646Q info;
tySet_tyEnum_TNodeFlag__jyh9acXHkhZANSSvPIY7ZLg flags;
tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw kind;
union{
struct {NI64 intVal;
} _kind_1;
struct {NF floatVal;
} _kind_2;
struct {NimStringDesc* strVal;
} _kind_3;
struct {tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w* sym;
} _kind_4;
struct {tyObject_TIdent__GufRQq9c0miSybX3zBD4tyA* ident;
} _kind_5;
struct {tySequence__ehmV9bTklH2Gt9cXHV9c0HLeQ* sons;
} _kind_6;
};
NimStringDesc* comment;
};
typedef NU8 tyEnum_TNimKind__jIBKr1ejBgsfM33Kxw4j7A;
typedef NU8 tySet_tyEnum_TNimTypeFlag__v8QUszD1sWlSIWZz7mC4bQ;
typedef N_NIMCALL_PTR(void, tyProc__ojoeKfW4VYIm36I9cpDTQIg) (void* p, NI op);
typedef N_NIMCALL_PTR(void*, tyProc__WSm2xU5ARYv9aAR4l0z9c9auQ) (void* p);
struct TNimType {
NI size;
NI align;
tyEnum_TNimKind__jIBKr1ejBgsfM33Kxw4j7A kind;
tySet_tyEnum_TNimTypeFlag__v8QUszD1sWlSIWZz7mC4bQ flags;
TNimType* base;
TNimNode* node;
void* finalizer;
tyProc__ojoeKfW4VYIm36I9cpDTQIg marker;
tyProc__WSm2xU5ARYv9aAR4l0z9c9auQ deepcopy;
};
struct RootObj {
TNimType* m_type;
};
struct tyObject_TIdObj__iIXPrEsiKHiioLj0HSkQhA {
  RootObj Sup;
NI id;
};
typedef NU8 tyEnum_TTypeKind__9a3YiReNVD0IJHWFKgXRe9ag;
typedef NU8 tyEnum_TCallingConvention__yjAJ8w0h1PBaSwSGJ3P7IA;
typedef NU64 tySet_tyEnum_TTypeFlag__x2m5g1NpbmDig4wLT3Ylhw;
typedef tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w* tyArray__PsPyPA45AAjHu4uDGHNjTg[6];
typedef NU8 tyEnum_TLocKind__O7PRFZKuiBBWbku09cayVBg;
typedef NU8 tyEnum_TStorageLoc__JK9cKMX3XnqHaUky9b6gkGEw;
typedef NU16 tySet_tyEnum_TLocFlag__o2bqJgR4ceIupnUSpxiudA;
struct tyObject_TLoc__EtHNvCB0bgfu9bFjzx9cb6aA {
tyEnum_TLocKind__O7PRFZKuiBBWbku09cayVBg k;
tyEnum_TStorageLoc__JK9cKMX3XnqHaUky9b6gkGEw storage;
tySet_tyEnum_TLocFlag__o2bqJgR4ceIupnUSpxiudA flags;
tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* lode;
tyObject_RopeObj__OFzf0kSiPTcNreUIeJgWVA* r;
};
struct tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ {
  tyObject_TIdObj__iIXPrEsiKHiioLj0HSkQhA Sup;
tyEnum_TTypeKind__9a3YiReNVD0IJHWFKgXRe9ag kind;
tyEnum_TCallingConvention__yjAJ8w0h1PBaSwSGJ3P7IA callConv;
tySet_tyEnum_TTypeFlag__x2m5g1NpbmDig4wLT3Ylhw flags;
tySequence__Ef05srmQTDulnBdXR4Ja6Q* sons;
tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n;
tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w* owner;
tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w* sym;
tyArray__PsPyPA45AAjHu4uDGHNjTg attachedOps;
tySequence__MvZmat48bhe9b6x9aUD58D5Q* methods;
NI64 size;
NI16 align;
NI16 paddingAtEnd;
NI16 lockLevel;
tyObject_TLoc__EtHNvCB0bgfu9bFjzx9cb6aA loc;
tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* typeInst;
NI uniqueId;
};
typedef NU8 tyEnum_TSymKind__cNCW9acsSznmEccl1fgQwkw;
struct tyObject_TStrTable__f07aOS3dr28kGa5wcE29aFA {
NI counter;
tySequence__DfgJFJEYoj4YBAHLZPl5lQ* data;
};
typedef NU16 tyEnum_TMagic__shZhZOdbVC5nnFvcXQAImg;
typedef NU64 tySet_tyEnum_TSymFlag__K9ay6LWMat9bUiT9bIbMxpDHw;
typedef NU32 tySet_tyEnum_TOption__WspMeQySXNP2XoTWR5MTgg;
struct tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w {
  tyObject_TIdObj__iIXPrEsiKHiioLj0HSkQhA Sup;
tyEnum_TSymKind__cNCW9acsSznmEccl1fgQwkw kind;
union{
struct {tySequence__Ef05srmQTDulnBdXR4Ja6Q* typeInstCache;
} _kind_1;
struct {tySequence__DXS6mEo7PVUFJkirsQ9bNQA* procInstCache;
tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w* gcUnsafetyReason;
tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* transformedBody;
} _kind_2;
struct {tySequence__DXS6mEo7PVUFJkirsQ9bNQA* usedGenerics;
tyObject_TStrTable__f07aOS3dr28kGa5wcE29aFA tab;
} _kind_3;
struct {tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w* guard;
NI bitsize;
NI alignment;
} _kind_4;
};
tyEnum_TMagic__shZhZOdbVC5nnFvcXQAImg magic;
tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* typ;
tyObject_TIdent__GufRQq9c0miSybX3zBD4tyA* name;
tyObject_TLineInfo__WGx4rAexNXnczy1Avn646Q info;
tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w* owner;
tySet_tyEnum_TSymFlag__K9ay6LWMat9bUiT9bIbMxpDHw flags;
tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* ast;
tySet_tyEnum_TOption__WspMeQySXNP2XoTWR5MTgg options;
NI position;
NI offset;
tyObject_TLoc__EtHNvCB0bgfu9bFjzx9cb6aA loc;
tyObject_TLib__NBMxlJ6g3utqUlplqTTHkA* annex;
tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* constraint;
};
typedef NU8 tyEnum_TMsgKind__29cbg2fC1z5iM1PAI28kR5w;
typedef NU8 tyEnum_TErrorHandling__q4fXoCN3Xdcm6SS9cUkWkWw;
struct tyTuple__kN8up2W6YKc5YA9avn5mV5w {
NimStringDesc* Field0;
NI Field1;
NI Field2;
};
struct tyTuple__zwpS6d6iewrdlBSTNFoyVA {
NI Field0;
tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w* Field1;
};

/* section: NIM_merge_SEQ_TYPES */
struct tySequence__ehmV9bTklH2Gt9cXHV9c0HLeQ {
  TGenericSeq Sup;
  tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* data[SEQ_DECL_SIZE];
};
struct tySequence__Ef05srmQTDulnBdXR4Ja6Q {
  TGenericSeq Sup;
  tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* data[SEQ_DECL_SIZE];
};
struct tySequence__MvZmat48bhe9b6x9aUD58D5Q {
  TGenericSeq Sup;
  tyTuple__zwpS6d6iewrdlBSTNFoyVA data[SEQ_DECL_SIZE];
};
struct tySequence__DXS6mEo7PVUFJkirsQ9bNQA {
  TGenericSeq Sup;
  tyObject_TInstantiation__5LqgVn6Tq9ainQRK7TQAQxA* data[SEQ_DECL_SIZE];
};
struct tySequence__DfgJFJEYoj4YBAHLZPl5lQ {
  TGenericSeq Sup;
  tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w* data[SEQ_DECL_SIZE];
};

/* section: NIM_merge_PROC_HEADERS */
N_LIB_PRIVATE N_NIMCALL(tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ*, skipTypes__zsqmUNR5OZrTUna0Y9bdu9bg)(tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* t, tySet_tyEnum_TTypeKind__9a3YiReNVD0IJHWFKgXRe9ag kinds);
static N_INLINE(NI, len__P89cqdlERShb9alU3iC0yj8wast)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n);
N_LIB_PRIVATE N_NIMCALL(tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w*, ithField__X0EX2ekTNwCWixXKa9ch4uQ)(tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* t, NI* field);
N_LIB_PRIVATE N_NIMCALL(tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w*, ithField__kaFOQERzou3n2mQIpXn4Bw)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n, NI* field);
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*, lastSon__UPSW0jLTX5qJL51YMUAHgw)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n);
static N_INLINE(NIM_BOOL*, nimErrorFlag)(void);
N_LIB_PRIVATE N_NOINLINE(void, liMessage__Q6JNH4uRwLyZrj0dJakHew)(tyObject_ConfigRefcolonObjectType___LaK09ayL9alwKUad7rts0rTw* conf, tyObject_TLineInfo__WGx4rAexNXnczy1Avn646Q info, tyEnum_TMsgKind__29cbg2fC1z5iM1PAI28kR5w msg, NimStringDesc* arg, tyEnum_TErrorHandling__q4fXoCN3Xdcm6SS9cUkWkWw eh, tyTuple__kN8up2W6YKc5YA9avn5mV5w info2, NIM_BOOL isRaw);
static N_INLINE(void, appendString)(NimStringDesc* dest, NimStringDesc* src);
static N_INLINE(void, copyMem__i80o3k0SgEI5gTRCzYdyWAsystem)(void* dest, void* source, NI size);
static N_INLINE(void, nimCopyMem)(void* dest, void* source, NI size);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, nimIntToStr)(NI x);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, rawNewString)(NI space);
static N_INLINE(NimStringDesc*, toFileLineCol__fTQr4TRmeNwYlKvcPy3kYAmsgs)(tyTuple__kN8up2W6YKc5YA9avn5mV5w info);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, resizeString)(NimStringDesc* dest, NI addlen);
N_LIB_PRIVATE N_NIMCALL(void, addInt__mftMOxbyu0h4yByfs3sqjA)(NimStringDesc** result, NI64 x);
N_LIB_PRIVATE N_NIMCALL(void, internalErrorImpl__PTSwZ6HM9bGBf7vF9cnDmwVw)(tyObject_ConfigRefcolonObjectType___LaK09ayL9alwKUad7rts0rTw* conf, tyObject_TLineInfo__WGx4rAexNXnczy1Avn646Q info, NimStringDesc* errMsg, tyTuple__kN8up2W6YKc5YA9avn5mV5w info2);
N_LIB_PRIVATE N_NIMCALL(void, annotateType__zBoL79cc9cORdBkTIEpbntbg)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n, tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* t, tyObject_ConfigRefcolonObjectType___LaK09ayL9alwKUad7rts0rTw* conf);
static N_INLINE(NI, len__5mJADrRYkP3r9auuiuDZN9cQast)(tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* n);
static N_INLINE(NI, safeLen__P89cqdlERShb9alU3iC0yj8w_2ast)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n);
N_LIB_PRIVATE N_NIMCALL(tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ*, elemType__PfgI9ap7WOnsRfFV4znQ27w_2)(tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* t);

/* section: NIM_merge_DATA */
STRING_LITERAL(TM__gkmEeaIyT0wHpJzs9ciIEJg_2, "invalid field at index ", 23);
STRING_LITERAL(TM__gkmEeaIyT0wHpJzs9ciIEJg_4, "/home/runner/work/nim4py/nim4py/Nim/compiler/semmacrosanity.nim", 63);
static NIM_CONST tyTuple__kN8up2W6YKc5YA9avn5mV5w TM__gkmEeaIyT0wHpJzs9ciIEJg_3 = {((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_4),
((NI) 58),
((NI) 20)}
;
STRING_LITERAL(TM__gkmEeaIyT0wHpJzs9ciIEJg_5, "(", 1);
STRING_LITERAL(TM__gkmEeaIyT0wHpJzs9ciIEJg_6, ", ", 2);
STRING_LITERAL(TM__gkmEeaIyT0wHpJzs9ciIEJg_7, ")", 1);
static NIM_CONST tyTuple__kN8up2W6YKc5YA9avn5mV5w TM__gkmEeaIyT0wHpJzs9ciIEJg_8 = {((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_4),
((NI) 60),
((NI) 22)}
;
static NIM_CONST tyObject_TLineInfo__WGx4rAexNXnczy1Avn646Q TM__gkmEeaIyT0wHpJzs9ciIEJg_9 = {((NU16) 0), ((NI16) -1), ((NI32) -1)}
;
static NIM_CONST tyTuple__kN8up2W6YKc5YA9avn5mV5w TM__gkmEeaIyT0wHpJzs9ciIEJg_10 = {((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_4),
((NI) 66),
((NI) 35)}
;
STRING_LITERAL(TM__gkmEeaIyT0wHpJzs9ciIEJg_11, "() must have a tuple type", 25);
static NIM_CONST tyTuple__kN8up2W6YKc5YA9avn5mV5w TM__gkmEeaIyT0wHpJzs9ciIEJg_12 = {((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_4),
((NI) 71),
((NI) 17)}
;
STRING_LITERAL(TM__gkmEeaIyT0wHpJzs9ciIEJg_13, "[] must have some form of array type", 36);
static NIM_CONST tyTuple__kN8up2W6YKc5YA9avn5mV5w TM__gkmEeaIyT0wHpJzs9ciIEJg_14 = {((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_4),
((NI) 77),
((NI) 17)}
;
STRING_LITERAL(TM__gkmEeaIyT0wHpJzs9ciIEJg_15, "{} must have the set type", 25);
static NIM_CONST tyTuple__kN8up2W6YKc5YA9avn5mV5w TM__gkmEeaIyT0wHpJzs9ciIEJg_16 = {((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_4),
((NI) 83),
((NI) 17)}
;
STRING_LITERAL(TM__gkmEeaIyT0wHpJzs9ciIEJg_17, "float literal must have some float type", 39);
static NIM_CONST tyTuple__kN8up2W6YKc5YA9avn5mV5w TM__gkmEeaIyT0wHpJzs9ciIEJg_18 = {((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_4),
((NI) 88),
((NI) 17)}
;
STRING_LITERAL(TM__gkmEeaIyT0wHpJzs9ciIEJg_19, "integer literal must have some int type", 39);
static NIM_CONST tyTuple__kN8up2W6YKc5YA9avn5mV5w TM__gkmEeaIyT0wHpJzs9ciIEJg_20 = {((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_4),
((NI) 93),
((NI) 17)}
;
STRING_LITERAL(TM__gkmEeaIyT0wHpJzs9ciIEJg_21, "string literal must be of some string type", 42);
static NIM_CONST tyTuple__kN8up2W6YKc5YA9avn5mV5w TM__gkmEeaIyT0wHpJzs9ciIEJg_22 = {((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_4),
((NI) 98),
((NI) 17)}
;
STRING_LITERAL(TM__gkmEeaIyT0wHpJzs9ciIEJg_23, "nil literal must be of some pointer type", 40);
static NIM_CONST tyTuple__kN8up2W6YKc5YA9avn5mV5w TM__gkmEeaIyT0wHpJzs9ciIEJg_24 = {((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_4),
((NI) 103),
((NI) 17)}
;

/* section: NIM_merge_VARS */
extern NIM_BOOL nimInErrorMode__759bT87luu8XGcbkw13FUjA;

/* section: NIM_merge_PROCS */
static N_INLINE(NI, len__P89cqdlERShb9alU3iC0yj8wast)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n) {
	NI result;
	NI T1_;
	result = (NI)0;
	T1_ = ((*n)._kind_6.sons ? (*n)._kind_6.sons->Sup.len : 0);
	result = T1_;
	return result;
}
static N_INLINE(NIM_BOOL*, nimErrorFlag)(void) {
	NIM_BOOL* result;
	result = (NIM_BOOL*)0;
	result = (&nimInErrorMode__759bT87luu8XGcbkw13FUjA);
	return result;
}
N_LIB_PRIVATE N_NIMCALL(tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w*, ithField__kaFOQERzou3n2mQIpXn4Bw)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n, NI* field) {
	tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w* result;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	result = (tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w*)0;
	result = NIM_NIL;
	switch ((*n).kind) {
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 138):
	{
		{
			NI i;
			NI colontmp_;
			NI i_2;
			i = (NI)0;
			colontmp_ = (NI)0;
			colontmp_ = len__P89cqdlERShb9alU3iC0yj8wast(n);
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
			i_2 = ((NI) 0);
			{
				while (1) {
					if (!(i_2 < colontmp_)) goto LA4;
					i = i_2;
					result = ithField__kaFOQERzou3n2mQIpXn4Bw((*n)._kind_6.sons->data[i], field);
					if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
					{
						if (!!((result == NIM_NIL))) goto LA7_;
						goto BeforeRet_;
					}
					LA7_: ;
					i_2 += ((NI) 1);
				} LA4: ;
			}
		}
	}
	break;
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 139):
	{
		{
			if (!!(((*(*n)._kind_6.sons->data[((NI) 0)]).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 3)))) goto LA12_;
			goto BeforeRet_;
		}
		LA12_: ;
		result = ithField__kaFOQERzou3n2mQIpXn4Bw((*n)._kind_6.sons->data[((NI) 0)], field);
		if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
		{
			if (!!((result == NIM_NIL))) goto LA16_;
			goto BeforeRet_;
		}
		LA16_: ;
		{
			NI i_3;
			NI colontmp__2;
			NI i_4;
			i_3 = (NI)0;
			colontmp__2 = (NI)0;
			colontmp__2 = len__P89cqdlERShb9alU3iC0yj8wast(n);
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
			i_4 = ((NI) 1);
			{
				while (1) {
					if (!(i_4 < colontmp__2)) goto LA20;
					i_3 = i_4;
					switch ((*(*n)._kind_6.sons->data[i_3]).kind) {
					case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 85):
					case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 88):
					{
						tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* T22_;
						T22_ = (tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*)0;
						T22_ = lastSon__UPSW0jLTX5qJL51YMUAHgw((*n)._kind_6.sons->data[i_3]);
						if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
						result = ithField__kaFOQERzou3n2mQIpXn4Bw(T22_, field);
						if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
						{
							if (!!((result == NIM_NIL))) goto LA25_;
							goto BeforeRet_;
						}
						LA25_: ;
					}
					break;
					default:
					{
					}
					break;
					}
					i_4 += ((NI) 1);
				} LA20: ;
			}
		}
	}
	break;
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 3):
	{
		{
			if (!((*field) == ((NI) 0))) goto LA31_;
			result = (*n)._kind_4.sym;
		}
		goto LA29_;
		LA31_: ;
		{
			(*field) -= ((NI) 1);
		}
		LA29_: ;
	}
	break;
	default:
	{
	}
	break;
	}
	}BeforeRet_: ;
	return result;
}
N_LIB_PRIVATE N_NIMCALL(tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w*, ithField__X0EX2ekTNwCWixXKa9ch4uQ)(tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* t, NI* field) {
	tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w* result;
	tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* base;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	result = (tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w*)0;
	base = (*t).sons->data[((NI) 0)];
	{
		while (1) {
			tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* b;
			if (!!((base == NIM_NIL))) goto LA2;
			b = skipTypes__zsqmUNR5OZrTUna0Y9bdu9bg(base, IL64(36275087638268176));
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
			result = ithField__kaFOQERzou3n2mQIpXn4Bw((*b).n, field);
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
			{
				if (!!((result == NIM_NIL))) goto LA5_;
				goto BeforeRet_;
			}
			LA5_: ;
			base = (*b).sons->data[((NI) 0)];
		} LA2: ;
	}
	result = ithField__kaFOQERzou3n2mQIpXn4Bw((*t).n, field);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	}BeforeRet_: ;
	return result;
}
static N_INLINE(void, nimCopyMem)(void* dest, void* source, NI size) {
	void* T1_;
	T1_ = (void*)0;
	T1_ = memcpy(dest, source, ((size_t) (size)));
}
static N_INLINE(void, copyMem__i80o3k0SgEI5gTRCzYdyWAsystem)(void* dest, void* source, NI size) {
	nimCopyMem(dest, source, size);
}
static N_INLINE(void, appendString)(NimStringDesc* dest, NimStringDesc* src) {
	{
		void* T5_;
		void* T6_;
		if (!!((src == NIM_NIL))) goto LA3_;
		T5_ = (void*)0;
		T5_ = ((void*) ((&(*dest).data[(*dest).Sup.len])));
		T6_ = (void*)0;
		T6_ = ((void*) ((*src).data));
		copyMem__i80o3k0SgEI5gTRCzYdyWAsystem(T5_, T6_, ((NI) ((NI)((*src).Sup.len + ((NI) 1)))));
		(*dest).Sup.len += (*src).Sup.len;
	}
	LA3_: ;
}
static N_INLINE(NimStringDesc*, toFileLineCol__fTQr4TRmeNwYlKvcPy3kYAmsgs)(tyTuple__kN8up2W6YKc5YA9avn5mV5w info) {
	NimStringDesc* result;
	result = (NimStringDesc*)0;
	result = resizeString(result, (info.Field0 ? info.Field0->Sup.len : 0) + 0);
appendString(result, info.Field0);
	{
		if (!(((NI) 0) < info.Field1)) goto LA3_;
		result = resizeString(result, 1);
appendString(result, ((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_5));
		addInt__mftMOxbyu0h4yByfs3sqjA((&result), ((NI64) (info.Field1)));
		{
			if (!(((NI) 0) < (NI)(info.Field2 + ((NI) 1)))) goto LA7_;
			result = resizeString(result, 2);
appendString(result, ((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_6));
			addInt__mftMOxbyu0h4yByfs3sqjA((&result), ((NI64) ((NI)(info.Field2 + ((NI) 1)))));
		}
		LA7_: ;
		result = resizeString(result, 1);
appendString(result, ((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_7));
	}
	LA3_: ;
	return result;
}
static N_INLINE(NI, len__5mJADrRYkP3r9auuiuDZN9cQast)(tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* n) {
	NI result;
	NI T1_;
	result = (NI)0;
	T1_ = ((*n).sons ? (*n).sons->Sup.len : 0);
	result = T1_;
	return result;
}
static N_INLINE(NI, safeLen__P89cqdlERShb9alU3iC0yj8w_2ast)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n) {
	NI result;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	result = (NI)0;
	{
		if (!((*n).kind >= ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 0) && (*n).kind <= ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 23))) goto LA3_;
		result = ((NI) 0);
	}
	goto LA1_;
	LA3_: ;
	{
		result = len__P89cqdlERShb9alU3iC0yj8wast(n);
		if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	}
	LA1_: ;
	}BeforeRet_: ;
	return result;
}
N_LIB_PRIVATE N_NIMCALL(void, annotateType__zBoL79cc9cORdBkTIEpbntbg)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n, tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* t, tyObject_ConfigRefcolonObjectType___LaK09ayL9alwKUad7rts0rTw* conf) {
	tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* x;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	x = skipTypes__zsqmUNR5OZrTUna0Y9bdu9bg(t, IL64(36134350136322320));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	switch ((*n).kind) {
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 38):
	{
		tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* x_2;
		x_2 = skipTypes__zsqmUNR5OZrTUna0Y9bdu9bg(t, IL64(36275087638309136));
		if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
		(*n).typ = t;
		{
			NI i;
			NI colontmp_;
			NI i_2;
			i = (NI)0;
			colontmp_ = (NI)0;
			colontmp_ = len__P89cqdlERShb9alU3iC0yj8wast(n);
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
			i_2 = ((NI) 1);
			{
				while (1) {
					NI j;
					tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w* field;
					if (!(i_2 < colontmp_)) goto LA4;
					i = i_2;
					j = (NI)(i - ((NI) 1));
					field = ithField__X0EX2ekTNwCWixXKa9ch4uQ(x_2, (&j));
					if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
					{
						NimStringDesc* T9_;
						NimStringDesc* T10_;
						if (!(field == 0)) goto LA7_;
						T9_ = (NimStringDesc*)0;
						T10_ = (NimStringDesc*)0;
						T10_ = nimIntToStr(i);
						T9_ = rawNewString((T10_ ? T10_->Sup.len : 0) + 23);
appendString(T9_, ((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_2));
appendString(T9_, T10_);
						liMessage__Q6JNH4uRwLyZrj0dJakHew(conf, (*n).info, ((tyEnum_TMsgKind__29cbg2fC1z5iM1PAI28kR5w) 10), T9_, ((tyEnum_TErrorHandling__q4fXoCN3Xdcm6SS9cUkWkWw) 2), TM__gkmEeaIyT0wHpJzs9ciIEJg_3, NIM_FALSE);
						if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
					}
					goto LA5_;
					LA7_: ;
					{
						{
							NimStringDesc* argX60gensym16_;
							if (!!(((*(*n)._kind_6.sons->data[i]).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 34)))) goto LA14_;
							argX60gensym16_ = toFileLineCol__fTQr4TRmeNwYlKvcPy3kYAmsgs(TM__gkmEeaIyT0wHpJzs9ciIEJg_8);
							if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
							internalErrorImpl__PTSwZ6HM9bGBf7vF9cnDmwVw(conf, TM__gkmEeaIyT0wHpJzs9ciIEJg_9, argX60gensym16_, TM__gkmEeaIyT0wHpJzs9ciIEJg_8);
							if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
						}
						LA14_: ;
						annotateType__zBoL79cc9cORdBkTIEpbntbg((*(*n)._kind_6.sons->data[i])._kind_6.sons->data[((NI) 1)], (*field).typ, conf);
						if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
					}
					LA5_: ;
					i_2 += ((NI) 1);
				} LA4: ;
			}
		}
	}
	break;
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 37):
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 160):
	{
		{
			if (!((*x).kind == ((tyEnum_TTypeKind__9a3YiReNVD0IJHWFKgXRe9ag) 18))) goto LA19_;
			(*n).typ = t;
			{
				NI i_3;
				NI colontmp__2;
				NI i_4;
				i_3 = (NI)0;
				colontmp__2 = (NI)0;
				colontmp__2 = len__P89cqdlERShb9alU3iC0yj8wast(n);
				if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
				i_4 = ((NI) 0);
				{
					while (1) {
						if (!(i_4 < colontmp__2)) goto LA23;
						i_3 = i_4;
						{
							NI T26_;
							NimStringDesc* T29_;
							NimStringDesc* T30_;
							T26_ = (NI)0;
							T26_ = len__5mJADrRYkP3r9auuiuDZN9cQast(x);
							if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
							if (!(T26_ <= i_3)) goto LA27_;
							T29_ = (NimStringDesc*)0;
							T30_ = (NimStringDesc*)0;
							T30_ = nimIntToStr(i_3);
							T29_ = rawNewString((T30_ ? T30_->Sup.len : 0) + 23);
appendString(T29_, ((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_2));
appendString(T29_, T30_);
							liMessage__Q6JNH4uRwLyZrj0dJakHew(conf, (*n).info, ((tyEnum_TMsgKind__29cbg2fC1z5iM1PAI28kR5w) 10), T29_, ((tyEnum_TErrorHandling__q4fXoCN3Xdcm6SS9cUkWkWw) 2), TM__gkmEeaIyT0wHpJzs9ciIEJg_10, NIM_FALSE);
							if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
						}
						goto LA24_;
						LA27_: ;
						{
							annotateType__zBoL79cc9cORdBkTIEpbntbg((*n)._kind_6.sons->data[i_3], (*x).sons->data[i_3], conf);
							if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
						}
						LA24_: ;
						i_4 += ((NI) 1);
					} LA23: ;
				}
			}
		}
		goto LA17_;
		LA19_: ;
		{
			NIM_BOOL T33_;
			T33_ = (NIM_BOOL)0;
			T33_ = ((*x).kind == ((tyEnum_TTypeKind__9a3YiReNVD0IJHWFKgXRe9ag) 25));
			if (!(T33_)) goto LA34_;
			T33_ = ((*x).callConv == ((tyEnum_TCallingConvention__yjAJ8w0h1PBaSwSGJ3P7IA) 9));
			LA34_: ;
			if (!T33_) goto LA35_;
			(*n).typ = t;
		}
		goto LA17_;
		LA35_: ;
		{
			liMessage__Q6JNH4uRwLyZrj0dJakHew(conf, (*n).info, ((tyEnum_TMsgKind__29cbg2fC1z5iM1PAI28kR5w) 10), ((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_11), ((tyEnum_TErrorHandling__q4fXoCN3Xdcm6SS9cUkWkWw) 2), TM__gkmEeaIyT0wHpJzs9ciIEJg_12, NIM_FALSE);
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
		}
		LA17_: ;
	}
	break;
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 41):
	{
		{
			if (!((151060480 &((NU64)1<<((NU)((*x).kind)&63U)))!=0)) goto LA41_;
			(*n).typ = t;
			{
				tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* m;
				m = (tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*)0;
				{
					NI i_5;
					NI colontmp__3;
					NI i_6;
					i_5 = (NI)0;
					colontmp__3 = (NI)0;
					colontmp__3 = safeLen__P89cqdlERShb9alU3iC0yj8w_2ast(n);
					if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
					i_6 = ((NI) 0);
					{
						while (1) {
							tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* T47_;
							if (!(i_6 < colontmp__3)) goto LA46;
							i_5 = i_6;
							m = (*n)._kind_6.sons->data[i_5];
							T47_ = (tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ*)0;
							T47_ = elemType__PfgI9ap7WOnsRfFV4znQ27w_2(x);
							if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
							annotateType__zBoL79cc9cORdBkTIEpbntbg(m, T47_, conf);
							if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
							i_6 += ((NI) 1);
						} LA46: ;
					}
				}
			}
		}
		goto LA39_;
		LA41_: ;
		{
			liMessage__Q6JNH4uRwLyZrj0dJakHew(conf, (*n).info, ((tyEnum_TMsgKind__29cbg2fC1z5iM1PAI28kR5w) 10), ((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_13), ((tyEnum_TErrorHandling__q4fXoCN3Xdcm6SS9cUkWkWw) 2), TM__gkmEeaIyT0wHpJzs9ciIEJg_14, NIM_FALSE);
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
		}
		LA39_: ;
	}
	break;
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 39):
	{
		{
			if (!((524288 &((NU64)1<<((NU)((*x).kind)&63U)))!=0)) goto LA52_;
			(*n).typ = t;
			{
				tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* m_2;
				m_2 = (tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*)0;
				{
					NI i_7;
					NI colontmp__4;
					NI i_8;
					i_7 = (NI)0;
					colontmp__4 = (NI)0;
					colontmp__4 = safeLen__P89cqdlERShb9alU3iC0yj8w_2ast(n);
					if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
					i_8 = ((NI) 0);
					{
						while (1) {
							tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* T58_;
							if (!(i_8 < colontmp__4)) goto LA57;
							i_7 = i_8;
							m_2 = (*n)._kind_6.sons->data[i_7];
							T58_ = (tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ*)0;
							T58_ = elemType__PfgI9ap7WOnsRfFV4znQ27w_2(x);
							if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
							annotateType__zBoL79cc9cORdBkTIEpbntbg(m_2, T58_, conf);
							if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
							i_8 += ((NI) 1);
						} LA57: ;
					}
				}
			}
		}
		goto LA50_;
		LA52_: ;
		{
			liMessage__Q6JNH4uRwLyZrj0dJakHew(conf, (*n).info, ((tyEnum_TMsgKind__29cbg2fC1z5iM1PAI28kR5w) 10), ((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_15), ((tyEnum_TErrorHandling__q4fXoCN3Xdcm6SS9cUkWkWw) 2), TM__gkmEeaIyT0wHpJzs9ciIEJg_16, NIM_FALSE);
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
		}
		LA50_: ;
	}
	break;
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 16) ... ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 19):
	{
		{
			if (!((IL64(1030792151040) &((NU64)1<<((NU)((*x).kind)&63U)))!=0)) goto LA63_;
			(*n).typ = t;
		}
		goto LA61_;
		LA63_: ;
		{
			liMessage__Q6JNH4uRwLyZrj0dJakHew(conf, (*n).info, ((tyEnum_TMsgKind__29cbg2fC1z5iM1PAI28kR5w) 10), ((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_17), ((tyEnum_TErrorHandling__q4fXoCN3Xdcm6SS9cUkWkWw) 2), TM__gkmEeaIyT0wHpJzs9ciIEJg_18, NIM_FALSE);
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
		}
		LA61_: ;
	}
	break;
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 5) ... ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 15):
	{
		{
			if (!((IL64(35182224621574) &((NU64)1<<((NU)((*x).kind)&63U)))!=0)) goto LA69_;
			(*n).typ = t;
		}
		goto LA67_;
		LA69_: ;
		{
			liMessage__Q6JNH4uRwLyZrj0dJakHew(conf, (*n).info, ((tyEnum_TMsgKind__29cbg2fC1z5iM1PAI28kR5w) 10), ((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_19), ((tyEnum_TErrorHandling__q4fXoCN3Xdcm6SS9cUkWkWw) 2), TM__gkmEeaIyT0wHpJzs9ciIEJg_20, NIM_FALSE);
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
		}
		LA67_: ;
	}
	break;
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 20) ... ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 22):
	{
		{
			if (!((805306368 &((NU64)1<<((NU)((*x).kind)&63U)))!=0)) goto LA75_;
			(*n).typ = t;
		}
		goto LA73_;
		LA75_: ;
		{
			liMessage__Q6JNH4uRwLyZrj0dJakHew(conf, (*n).info, ((tyEnum_TMsgKind__29cbg2fC1z5iM1PAI28kR5w) 10), ((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_21), ((tyEnum_TErrorHandling__q4fXoCN3Xdcm6SS9cUkWkWw) 2), TM__gkmEeaIyT0wHpJzs9ciIEJg_22, NIM_FALSE);
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
		}
		LA73_: ;
	}
	break;
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 23):
	{
		{
			if (!((IL64(1125900835880960) &((NU64)1<<((NU)((*x).kind)&63U)))!=0)) goto LA81_;
			(*n).typ = t;
		}
		goto LA79_;
		LA81_: ;
		{
			liMessage__Q6JNH4uRwLyZrj0dJakHew(conf, (*n).info, ((tyEnum_TMsgKind__29cbg2fC1z5iM1PAI28kR5w) 10), ((NimStringDesc*) &TM__gkmEeaIyT0wHpJzs9ciIEJg_23), ((tyEnum_TErrorHandling__q4fXoCN3Xdcm6SS9cUkWkWw) 2), TM__gkmEeaIyT0wHpJzs9ciIEJg_24, NIM_FALSE);
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
		}
		LA79_: ;
	}
	break;
	default:
	{
	}
	break;
	}
	}BeforeRet_: ;
}
