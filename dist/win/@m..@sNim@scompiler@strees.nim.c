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
typedef struct tySequence__DXS6mEo7PVUFJkirsQ9bNQA tySequence__DXS6mEo7PVUFJkirsQ9bNQA;
typedef struct tyObject_TStrTable__f07aOS3dr28kGa5wcE29aFA tyObject_TStrTable__f07aOS3dr28kGa5wcE29aFA;
typedef struct tySequence__DfgJFJEYoj4YBAHLZPl5lQ tySequence__DfgJFJEYoj4YBAHLZPl5lQ;
typedef struct tyObject_TLoc__EtHNvCB0bgfu9bFjzx9cb6aA tyObject_TLoc__EtHNvCB0bgfu9bFjzx9cb6aA;
typedef struct tyObject_RopeObj__OFzf0kSiPTcNreUIeJgWVA tyObject_RopeObj__OFzf0kSiPTcNreUIeJgWVA;
typedef struct tyObject_TLib__NBMxlJ6g3utqUlplqTTHkA tyObject_TLib__NBMxlJ6g3utqUlplqTTHkA;
typedef struct tySequence__MvZmat48bhe9b6x9aUD58D5Q tySequence__MvZmat48bhe9b6x9aUD58D5Q;
typedef struct tyObject_TInstantiation__5LqgVn6Tq9ainQRK7TQAQxA tyObject_TInstantiation__5LqgVn6Tq9ainQRK7TQAQxA;
typedef struct tyTuple__zwpS6d6iewrdlBSTNFoyVA tyTuple__zwpS6d6iewrdlBSTNFoyVA;

/* section: NIM_merge_TYPES */
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
typedef NU8 tyEnum_TSymKind__cNCW9acsSznmEccl1fgQwkw;
struct tyObject_TStrTable__f07aOS3dr28kGa5wcE29aFA {
NI counter;
tySequence__DfgJFJEYoj4YBAHLZPl5lQ* data;
};
typedef NU16 tyEnum_TMagic__shZhZOdbVC5nnFvcXQAImg;
typedef NU64 tySet_tyEnum_TSymFlag__K9ay6LWMat9bUiT9bIbMxpDHw;
typedef NU32 tySet_tyEnum_TOption__WspMeQySXNP2XoTWR5MTgg;
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
struct tyObject_TIdent__GufRQq9c0miSybX3zBD4tyA {
  tyObject_TIdObj__iIXPrEsiKHiioLj0HSkQhA Sup;
NimStringDesc* s;
tyObject_TIdent__GufRQq9c0miSybX3zBD4tyA* next;
NI h;
};
typedef NU16 tyEnum_TSpecialWord__ycbpMCRV6Cd2eBh3X9biEiw;
typedef NU8 tyEnum_TNodeFlag__jyh9acXHkhZANSSvPIY7ZLg;
typedef NU8 tyEnum_TNimNodeKind__unfNsxrcATrufDZmpBq4HQ;
struct TNimNode {
tyEnum_TNimNodeKind__unfNsxrcATrufDZmpBq4HQ kind;
NI offset;
TNimType* typ;
NCSTRING name;
NI len;
TNimNode** sons;
};
typedef NU64 tySet_tyEnum_TTypeKind__9a3YiReNVD0IJHWFKgXRe9ag;
typedef NU8 tyEnum_TTypeKind__9a3YiReNVD0IJHWFKgXRe9ag;
typedef NU8 tyEnum_TCallingConvention__yjAJ8w0h1PBaSwSGJ3P7IA;
typedef NU64 tySet_tyEnum_TTypeFlag__x2m5g1NpbmDig4wLT3Ylhw;
typedef tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w* tyArray__PsPyPA45AAjHu4uDGHNjTg[6];
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
typedef NU8 tyEnum_TTypeFlag__x2m5g1NpbmDig4wLT3Ylhw;
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
struct tySequence__DXS6mEo7PVUFJkirsQ9bNQA {
  TGenericSeq Sup;
  tyObject_TInstantiation__5LqgVn6Tq9ainQRK7TQAQxA* data[SEQ_DECL_SIZE];
};
struct tySequence__DfgJFJEYoj4YBAHLZPl5lQ {
  TGenericSeq Sup;
  tyObject_TSym__JpsEh5i1AcKChGYbg7aV4w* data[SEQ_DECL_SIZE];
};
struct tySequence__MvZmat48bhe9b6x9aUD58D5Q {
  TGenericSeq Sup;
  tyTuple__zwpS6d6iewrdlBSTNFoyVA data[SEQ_DECL_SIZE];
};

/* section: NIM_merge_PROC_HEADERS */
static N_INLINE(NIM_BOOL, sameFloatIgnoreNan__ZHjXPPi0kcAio2Zeegfpmgtrees)(NF a, NF b);
static N_INLINE(NIM_BOOL, eqStrings)(NimStringDesc* a, NimStringDesc* b);
static N_INLINE(NIM_BOOL, equalMem__9bGgqEk7RXXl6eqM9c1HdELAsystem)(void* a, void* b, NI size);
static N_INLINE(int, nimCmpMem)(void* a, void* b, NI size);
static N_INLINE(NI, len__P89cqdlERShb9alU3iC0yj8wast)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n);
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, exprStructuralEquivalent__E1mnSzj2NONtG7h9cR3AuFA)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* a, tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* b, NIM_BOOL strictSymEquality);
static N_INLINE(NIM_BOOL*, nimErrorFlag)(void);
N_LIB_PRIVATE N_NIMCALL(tyEnum_TSpecialWord__ycbpMCRV6Cd2eBh3X9biEiw, whichKeyword__sZUQNPhNGEM8MllfcWvRiw)(tyObject_TIdent__GufRQq9c0miSybX3zBD4tyA* id);
static N_INLINE(NI, safeLen__P89cqdlERShb9alU3iC0yj8w_2ast)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n);
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, isCaseObj__9cP6JNeOKqczaXCI4Zo4SBQ)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n);
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, cyclicTreeAux__E5C0jygoyjxqsSt8fsH2EQ)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n, tySequence__ehmV9bTklH2Gt9cXHV9c0HLeQ** visited);
N_LIB_PRIVATE N_NIMCALL(TGenericSeq*, incrSeqV3)(TGenericSeq* s, TNimType* typ);
static N_INLINE(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*, pop__jgHhw9bd9a38Xqyz0a3Aayngsystem)(tySequence__ehmV9bTklH2Gt9cXHV9c0HLeQ** s);
N_LIB_PRIVATE N_NIMCALL(TGenericSeq*, setLengthSeqV2)(TGenericSeq* s, TNimType* typ, NI newLen);
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*, newNodeI__vokyXY9cZDshCSxFKChhG9bg)(tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw kind, tyObject_TLineInfo__WGx4rAexNXnczy1Avn646Q info);
N_LIB_PRIVATE N_NIMCALL(void, unnestStmts__JHcnC5MLPZM8o9bbjyuNYSg)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n, tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* result);
N_LIB_PRIVATE N_NIMCALL(void, add__P8dDSotTW25BkfbyspojGg)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* father, tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* son);
N_LIB_PRIVATE N_NIMCALL(tyEnum_TSpecialWord__ycbpMCRV6Cd2eBh3X9biEiw, whichPragma__Pjztiiq9bHmTTxDuLd39cNRw)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n);
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*, newNodeI__UY1ElYk2XqXDzuz9cGLG1Kw)(tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw kind, tyObject_TLineInfo__WGx4rAexNXnczy1Avn646Q info, NI children);
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, isDeepConstExpr__sjm2oD6Aq9cG39aPE7CTvtmA)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n, NIM_BOOL preventInheritance);
N_LIB_PRIVATE N_NIMCALL(tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ*, skipTypes__zsqmUNR5OZrTUna0Y9bdu9bg)(tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* t, tySet_tyEnum_TTypeKind__9a3YiReNVD0IJHWFKgXRe9ag kinds);

/* section: NIM_merge_DATA */
extern TNimType NTI__ehmV9bTklH2Gt9cXHV9c0HLeQ_;

/* section: NIM_merge_VARS */
extern NIM_BOOL nimInErrorMode__759bT87luu8XGcbkw13FUjA;

/* section: NIM_merge_PROCS */
static N_INLINE(NIM_BOOL, sameFloatIgnoreNan__ZHjXPPi0kcAio2Zeegfpmgtrees)(NF a, NF b) {
	NIM_BOOL result;
	NIM_BOOL T1_;
	union { NF source; NU64 dest; } LOC2;
	union { NF source; NU64 dest; } LOC3;
	result = (NIM_BOOL)0;
	T1_ = (NIM_BOOL)0;
	LOC2.source = a;
	LOC3.source = b;
	T1_ = (LOC2.dest == LOC3.dest);
	if (T1_) goto LA4_;
	T1_ = (a == b);
	LA4_: ;
	result = T1_;
	return result;
}
static N_INLINE(int, nimCmpMem)(void* a, void* b, NI size) {
	int result;
	result = (int)0;
	result = memcmp(a, b, ((size_t) (size)));
	return result;
}
static N_INLINE(NIM_BOOL, equalMem__9bGgqEk7RXXl6eqM9c1HdELAsystem)(void* a, void* b, NI size) {
	NIM_BOOL result;
	int T1_;
	result = (NIM_BOOL)0;
	T1_ = (int)0;
	T1_ = nimCmpMem(a, b, size);
	result = (T1_ == ((NI32) 0));
	return result;
}
static N_INLINE(NIM_BOOL, eqStrings)(NimStringDesc* a, NimStringDesc* b) {
	NIM_BOOL result;
	NI alen;
	NI blen;
{	result = (NIM_BOOL)0;
	alen = (a ? a->Sup.len : 0);
	blen = (b ? b->Sup.len : 0);
	{
		if (!(alen == blen)) goto LA3_;
		{
			if (!(alen == ((NI) 0))) goto LA7_;
			result = NIM_TRUE;
			goto BeforeRet_;
		}
		LA7_: ;
		result = equalMem__9bGgqEk7RXXl6eqM9c1HdELAsystem(((void*) ((&a->data[((NI) 0)]))), ((void*) ((&b->data[((NI) 0)]))), ((NI) (alen)));
		goto BeforeRet_;
	}
	LA3_: ;
	}BeforeRet_: ;
	return result;
}
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
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, exprStructuralEquivalent__E1mnSzj2NONtG7h9cR3AuFA)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* a, tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* b, NIM_BOOL strictSymEquality) {
	NIM_BOOL result;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	result = (NIM_BOOL)0;
	{
		if (!(a == b)) goto LA3_;
		result = NIM_TRUE;
	}
	goto LA1_;
	LA3_: ;
	{
		NIM_BOOL T6_;
		NIM_BOOL T7_;
		T6_ = (NIM_BOOL)0;
		T7_ = (NIM_BOOL)0;
		T7_ = !((a == NIM_NIL));
		if (!(T7_)) goto LA8_;
		T7_ = !((b == NIM_NIL));
		LA8_: ;
		T6_ = T7_;
		if (!(T6_)) goto LA9_;
		T6_ = ((*a).kind == (*b).kind);
		LA9_: ;
		if (!T6_) goto LA10_;
		switch ((*a).kind) {
		case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 3):
		{
			{
				if (!strictSymEquality) goto LA15_;
				result = ((*a)._kind_4.sym == (*b)._kind_4.sym);
			}
			goto LA13_;
			LA15_: ;
			{
				result = ((*(*(*a)._kind_4.sym).name).Sup.id == (*(*(*b)._kind_4.sym).name).Sup.id);
			}
			LA13_: ;
		}
		break;
		case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 2):
		{
			result = ((*(*a)._kind_5.ident).Sup.id == (*(*b)._kind_5.ident).Sup.id);
		}
		break;
		case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 5) ... ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 15):
		{
			result = ((*a)._kind_1.intVal == (*b)._kind_1.intVal);
		}
		break;
		case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 16) ... ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 18):
		{
			NF T21_;
			T21_ = (NF)0;
			T21_ = (*a)._kind_2.floatVal;
			result = sameFloatIgnoreNan__ZHjXPPi0kcAio2Zeegfpmgtrees(T21_, (*b)._kind_2.floatVal);
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
		}
		break;
		case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 20) ... ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 22):
		{
			result = eqStrings((*a)._kind_3.strVal, (*b)._kind_3.strVal);
		}
		break;
		case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 125):
		{
			result = eqStrings((*a).comment, (*b).comment);
		}
		break;
		case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 1):
		case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 23):
		case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 4):
		{
			result = NIM_TRUE;
		}
		break;
		default:
		{
			{
				NI T28_;
				NI T29_;
				T28_ = (NI)0;
				T28_ = len__P89cqdlERShb9alU3iC0yj8wast(a);
				if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
				T29_ = (NI)0;
				T29_ = len__P89cqdlERShb9alU3iC0yj8wast(b);
				if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
				if (!(T28_ == T29_)) goto LA30_;
				{
					NI i;
					NI colontmp_;
					NI i_2;
					i = (NI)0;
					colontmp_ = (NI)0;
					colontmp_ = len__P89cqdlERShb9alU3iC0yj8wast(a);
					if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
					i_2 = ((NI) 0);
					{
						while (1) {
							if (!(i_2 < colontmp_)) goto LA34;
							i = i_2;
							{
								tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* T37_;
								NIM_BOOL T38_;
								T37_ = (tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*)0;
								T37_ = (*a)._kind_6.sons->data[i];
								T38_ = (NIM_BOOL)0;
								T38_ = exprStructuralEquivalent__E1mnSzj2NONtG7h9cR3AuFA(T37_, (*b)._kind_6.sons->data[i], strictSymEquality);
								if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
								if (!!(T38_)) goto LA39_;
								goto BeforeRet_;
							}
							LA39_: ;
							i_2 += ((NI) 1);
						} LA34: ;
					}
				}
				result = NIM_TRUE;
			}
			LA30_: ;
		}
		break;
		}
	}
	goto LA1_;
	LA10_: ;
	LA1_: ;
	}BeforeRet_: ;
	return result;
}
N_LIB_PRIVATE N_NIMCALL(tyEnum_TMagic__shZhZOdbVC5nnFvcXQAImg, getMagic__4W1ZJaFiusqlhViRx9cbM9bw)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* op) {
	tyEnum_TMagic__shZhZOdbVC5nnFvcXQAImg result;
{	result = (tyEnum_TMagic__shZhZOdbVC5nnFvcXQAImg)0;
	{
		if (!(op == NIM_NIL)) goto LA3_;
		result = ((tyEnum_TMagic__shZhZOdbVC5nnFvcXQAImg) 0);
		goto BeforeRet_;
	}
	LA3_: ;
	switch ((*op).kind) {
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 26) ... ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 32):
	{
		switch ((*(*op)._kind_6.sons->data[((NI) 0)]).kind) {
		case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 3):
		{
			result = (*(*(*op)._kind_6.sons->data[((NI) 0)])._kind_4.sym).magic;
		}
		break;
		default:
		{
			result = ((tyEnum_TMagic__shZhZOdbVC5nnFvcXQAImg) 0);
		}
		break;
		}
	}
	break;
	default:
	{
		result = ((tyEnum_TMagic__shZhZOdbVC5nnFvcXQAImg) 0);
	}
	break;
	}
	}BeforeRet_: ;
	return result;
}
N_LIB_PRIVATE N_NIMCALL(tyEnum_TSpecialWord__ycbpMCRV6Cd2eBh3X9biEiw, whichPragma__Pjztiiq9bHmTTxDuLd39cNRw)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n) {
	tyEnum_TSpecialWord__ycbpMCRV6Cd2eBh3X9biEiw result;
	tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* key;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	result = (tyEnum_TSpecialWord__ycbpMCRV6Cd2eBh3X9biEiw)0;
	{
		NIM_BOOL T3_;
		NI T5_;
		T3_ = (NIM_BOOL)0;
		T3_ = ((*n).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 34) || (*n).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 27) || (*n).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 28));
		if (!(T3_)) goto LA4_;
		T5_ = (NI)0;
		T5_ = len__P89cqdlERShb9alU3iC0yj8wast(n);
		if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
		T3_ = (((NI) 0) < T5_);
		LA4_: ;
		if (!T3_) goto LA6_;
		key = (*n)._kind_6.sons->data[((NI) 0)];
	}
	goto LA1_;
	LA6_: ;
	{
		key = n;
	}
	LA1_: ;
	{
		if (!((*key).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 2))) goto LA11_;
		result = whichKeyword__sZUQNPhNGEM8MllfcWvRiw((*key)._kind_5.ident);
		if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	}
	LA11_: ;
	}BeforeRet_: ;
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
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, isCaseObj__9cP6JNeOKqczaXCI4Zo4SBQ)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n) {
	NIM_BOOL result;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	result = (NIM_BOOL)0;
	{
		if (!((*n).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 139))) goto LA3_;
		result = NIM_TRUE;
		goto BeforeRet_;
	}
	LA3_: ;
	{
		NI i;
		NI colontmp_;
		NI i_2;
		i = (NI)0;
		colontmp_ = (NI)0;
		colontmp_ = safeLen__P89cqdlERShb9alU3iC0yj8w_2ast(n);
		if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
		i_2 = ((NI) 0);
		{
			while (1) {
				if (!(i_2 < colontmp_)) goto LA7;
				i = i_2;
				{
					NIM_BOOL T10_;
					T10_ = (NIM_BOOL)0;
					T10_ = isCaseObj__9cP6JNeOKqczaXCI4Zo4SBQ((*n)._kind_6.sons->data[i]);
					if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
					if (!T10_) goto LA11_;
					result = NIM_TRUE;
					goto BeforeRet_;
				}
				LA11_: ;
				i_2 += ((NI) 1);
			} LA7: ;
		}
	}
	}BeforeRet_: ;
	return result;
}
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, isConstExpr__9cP6JNeOKqczaXCI4Zo4SBQ_2)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n) {
	NIM_BOOL result;
	NIM_BOOL T1_;
	result = (NIM_BOOL)0;
	T1_ = (NIM_BOOL)0;
	T1_ = ((*n).kind >= ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 5) && (*n).kind <= ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 23));
	if (T1_) goto LA2_;
	T1_ = (((*n).flags &(1U<<((NU)(((tyEnum_TNodeFlag__jyh9acXHkhZANSSvPIY7ZLg) 4))&31U)))!=0);
	LA2_: ;
	result = T1_;
	return result;
}
static N_INLINE(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*, pop__jgHhw9bd9a38Xqyz0a3Aayngsystem)(tySequence__ehmV9bTklH2Gt9cXHV9c0HLeQ** s) {
	tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* result;
	NI L;
	NI T1_;
	result = (tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*)0;
	T1_ = ((*s) ? (*s)->Sup.len : 0);
	L = (NI)(T1_ - ((NI) 1));
	result = (*s)->data[L];
	(*s) = (tySequence__ehmV9bTklH2Gt9cXHV9c0HLeQ*) setLengthSeqV2(&((*s))->Sup, (&NTI__ehmV9bTklH2Gt9cXHV9c0HLeQ_), ((NI) (L)));
	return result;
}
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, cyclicTreeAux__E5C0jygoyjxqsSt8fsH2EQ)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n, tySequence__ehmV9bTklH2Gt9cXHV9c0HLeQ** visited) {
	NIM_BOOL result;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	result = (NIM_BOOL)0;
	{
		if (!(n == NIM_NIL)) goto LA3_;
		goto BeforeRet_;
	}
	LA3_: ;
	{
		tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw** v;
		NI i;
		NI L;
		NI T6_;
		v = (tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw**)0;
		i = ((NI) 0);
		T6_ = ((*visited) ? (*visited)->Sup.len : 0);
		L = T6_;
		{
			while (1) {
				if (!(i < L)) goto LA8;
				v = &(*visited)->data[i];
				{
					if (!((*v) == n)) goto LA11_;
					result = NIM_TRUE;
					goto BeforeRet_;
				}
				LA11_: ;
				i += ((NI) 1);
			} LA8: ;
		}
	}
	{
		NI T17_;
		tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* T27_;
		if (!!(((*n).kind >= ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 1) && (*n).kind <= ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 23)))) goto LA15_;
		(*visited) = (tySequence__ehmV9bTklH2Gt9cXHV9c0HLeQ*) incrSeqV3((TGenericSeq*)((*visited)), (&NTI__ehmV9bTklH2Gt9cXHV9c0HLeQ_));
		T17_ = (*visited)->Sup.len++;
		(*visited)->data[T17_] = n;
		{
			tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw** nSon;
			tySequence__ehmV9bTklH2Gt9cXHV9c0HLeQ* colontmp_;
			NI i_2;
			NI L_2;
			NI T19_;
			nSon = (tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw**)0;
			colontmp_ = (tySequence__ehmV9bTklH2Gt9cXHV9c0HLeQ*)0;
			colontmp_ = (*n)._kind_6.sons;
			i_2 = ((NI) 0);
			T19_ = (colontmp_ ? colontmp_->Sup.len : 0);
			L_2 = T19_;
			{
				while (1) {
					if (!(i_2 < L_2)) goto LA21;
					nSon = &colontmp_->data[i_2];
					{
						NIM_BOOL T24_;
						T24_ = (NIM_BOOL)0;
						T24_ = cyclicTreeAux__E5C0jygoyjxqsSt8fsH2EQ((*nSon), visited);
						if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
						if (!T24_) goto LA25_;
						result = NIM_TRUE;
						goto BeforeRet_;
					}
					LA25_: ;
					i_2 += ((NI) 1);
				} LA21: ;
			}
		}
		T27_ = (tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*)0;
		T27_ = pop__jgHhw9bd9a38Xqyz0a3Aayngsystem(visited);
		(void)(T27_);
	}
	LA15_: ;
	}BeforeRet_: ;
	return result;
}
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, cyclicTree__9cP6JNeOKqczaXCI4Zo4SBQ_3)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n) {
	NIM_BOOL result;
	tySequence__ehmV9bTklH2Gt9cXHV9c0HLeQ* visited;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	result = (NIM_BOOL)0;
	visited = NIM_NIL;
	result = cyclicTreeAux__E5C0jygoyjxqsSt8fsH2EQ(n, (&visited));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	}BeforeRet_: ;
	return result;
}
N_LIB_PRIVATE N_NIMCALL(void, unnestStmts__JHcnC5MLPZM8o9bbjyuNYSg)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n, tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* result) {
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	{
		if (!((*n).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 115))) goto LA3_;
		{
			tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* x;
			x = (tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*)0;
			{
				NI i;
				NI colontmp_;
				NI i_2;
				i = (NI)0;
				colontmp_ = (NI)0;
				colontmp_ = safeLen__P89cqdlERShb9alU3iC0yj8w_2ast(n);
				if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
				i_2 = ((NI) 0);
				{
					while (1) {
						if (!(i_2 < colontmp_)) goto LA8;
						i = i_2;
						x = (*n)._kind_6.sons->data[i];
						unnestStmts__JHcnC5MLPZM8o9bbjyuNYSg(x, result);
						if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
						i_2 += ((NI) 1);
					} LA8: ;
				}
			}
		}
	}
	goto LA1_;
	LA3_: ;
	{
		if (!!(((*n).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 125) || (*n).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 23)))) goto LA10_;
		add__P8dDSotTW25BkfbyspojGg(result, n);
		if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	}
	goto LA1_;
	LA10_: ;
	LA1_: ;
	}BeforeRet_: ;
}
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*, flattenStmts__qsyX8NJX39ctdwAi4rC8W1g)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n) {
	tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* result;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	result = (tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*)0;
	result = newNodeI__vokyXY9cZDshCSxFKChhG9bg(((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 115), (*n).info);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	unnestStmts__JHcnC5MLPZM8o9bbjyuNYSg(n, result);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	{
		NI T3_;
		T3_ = (NI)0;
		T3_ = len__P89cqdlERShb9alU3iC0yj8wast(result);
		if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
		if (!(T3_ == ((NI) 1))) goto LA4_;
		result = (*result)._kind_6.sons->data[((NI) 0)];
	}
	LA4_: ;
	}BeforeRet_: ;
	return result;
}
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*, effectSpec__bT2fsf3zXYRpjYdeea19aAA)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n, tyEnum_TSpecialWord__ycbpMCRV6Cd2eBh3X9biEiw effectType) {
	tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* result;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	result = (tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*)0;
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
				tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* it;
				if (!(i_2 < colontmp_)) goto LA3;
				i = i_2;
				it = (*n)._kind_6.sons->data[i];
				{
					NIM_BOOL T6_;
					tyEnum_TSpecialWord__ycbpMCRV6Cd2eBh3X9biEiw T8_;
					T6_ = (NIM_BOOL)0;
					T6_ = ((*it).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 34));
					if (!(T6_)) goto LA7_;
					T8_ = (tyEnum_TSpecialWord__ycbpMCRV6Cd2eBh3X9biEiw)0;
					T8_ = whichPragma__Pjztiiq9bHmTTxDuLd39cNRw(it);
					if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
					T6_ = (T8_ == effectType);
					LA7_: ;
					if (!T6_) goto LA9_;
					result = (*it)._kind_6.sons->data[((NI) 1)];
					{
						if (!!(((*result).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 39) || (*result).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 41)))) goto LA13_;
						result = newNodeI__vokyXY9cZDshCSxFKChhG9bg(((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 39), (*result).info);
						if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
						add__P8dDSotTW25BkfbyspojGg(result, (*it)._kind_6.sons->data[((NI) 1)]);
						if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
					}
					LA13_: ;
					goto BeforeRet_;
				}
				LA9_: ;
				i_2 += ((NI) 1);
			} LA3: ;
		}
	}
	}BeforeRet_: ;
	return result;
}
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*, extractRange__O5NwuGwzV0TTJrU6OP82MA)(tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw k, tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n, NI a, NI b) {
	tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* result;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	result = (tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*)0;
	result = newNodeI__UY1ElYk2XqXDzuz9cGLG1Kw(k, (*n).info, (NI)((NI)(b - a) + ((NI) 1)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	{
		NI i;
		NI colontmp_;
		NI res;
		i = (NI)0;
		colontmp_ = (NI)0;
		colontmp_ = (NI)(b - a);
		res = ((NI) 0);
		{
			while (1) {
				if (!(res <= colontmp_)) goto LA3;
				i = res;
				(*result)._kind_6.sons->data[i] = (*n)._kind_6.sons->data[(NI)(i + a)];
				res += ((NI) 1);
			} LA3: ;
		}
	}
	}BeforeRet_: ;
	return result;
}
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, isDeepConstExpr__sjm2oD6Aq9cG39aPE7CTvtmA)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n, NIM_BOOL preventInheritance) {
	NIM_BOOL result;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	result = (NIM_BOOL)0;
	switch ((*n).kind) {
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 5) ... ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 23):
	{
		result = NIM_TRUE;
	}
	break;
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 33):
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 34):
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 58):
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 59):
	{
		result = isDeepConstExpr__sjm2oD6Aq9cG39aPE7CTvtmA((*n)._kind_6.sons->data[((NI) 1)], preventInheritance);
		if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	}
	break;
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 39):
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 41):
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 37):
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 160):
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 38):
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 155):
	case ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 44):
	{
		{
			NI i;
			NI colontmp_;
			NI colontmp__2;
			NI i_2;
			i = (NI)0;
			colontmp_ = (NI)0;
			colontmp__2 = (NI)0;
			colontmp_ = ((*n).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 38));
			colontmp__2 = len__P89cqdlERShb9alU3iC0yj8wast(n);
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
			i_2 = colontmp_;
			{
				while (1) {
					if (!(i_2 < colontmp__2)) goto LA6;
					i = i_2;
					{
						NIM_BOOL T9_;
						T9_ = (NIM_BOOL)0;
						T9_ = isDeepConstExpr__sjm2oD6Aq9cG39aPE7CTvtmA((*n)._kind_6.sons->data[i], preventInheritance);
						if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
						if (!!(T9_)) goto LA10_;
						result = NIM_FALSE;
						goto BeforeRet_;
					}
					LA10_: ;
					i_2 += ((NI) 1);
				} LA6: ;
			}
		}
		{
			if (!((*n).typ == 0)) goto LA14_;
			result = NIM_TRUE;
		}
		goto LA12_;
		LA14_: ;
		{
			tyObject_TType__v9ae2Dpu13OW2ZJ2U9bNMd9cQ* t;
			t = skipTypes__zsqmUNR5OZrTUna0Y9bdu9bg((*n).typ, IL64(105553116276752));
			if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
			{
				NIM_BOOL T19_;
				T19_ = (NIM_BOOL)0;
				T19_ = ((6291456 &((NU64)1<<((NU)((*t).kind)&63U)))!=0);
				if (T19_) goto LA20_;
				T19_ = (((*t).flags &((NU64)1<<((NU)(((tyEnum_TTypeFlag__x2m5g1NpbmDig4wLT3Ylhw) 1))&63U)))!=0);
				LA20_: ;
				if (!T19_) goto LA21_;
				result = NIM_FALSE;
				goto BeforeRet_;
			}
			LA21_: ;
			{
				if (!((*t).kind == ((tyEnum_TTypeKind__9a3YiReNVD0IJHWFKgXRe9ag) 17))) goto LA25_;
				{
					NIM_BOOL T29_;
					T29_ = (NIM_BOOL)0;
					T29_ = preventInheritance;
					if (!(T29_)) goto LA30_;
					T29_ = !(((*t).sons->data[((NI) 0)] == NIM_NIL));
					LA30_: ;
					if (!T29_) goto LA31_;
					result = NIM_FALSE;
				}
				goto LA27_;
				LA31_: ;
				{
					NIM_BOOL T34_;
					T34_ = (NIM_BOOL)0;
					T34_ = isCaseObj__9cP6JNeOKqczaXCI4Zo4SBQ((*t).n);
					if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
					if (!T34_) goto LA35_;
					result = NIM_FALSE;
				}
				goto LA27_;
				LA35_: ;
				{
					result = NIM_TRUE;
				}
				LA27_: ;
			}
			goto LA23_;
			LA25_: ;
			{
				result = NIM_TRUE;
			}
			LA23_: ;
		}
		LA12_: ;
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
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, isTrue__9cP6JNeOKqczaXCI4Zo4SBQ_4)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n) {
	NIM_BOOL result;
	NIM_BOOL T1_;
	NIM_BOOL T2_;
	NIM_BOOL T3_;
	NIM_BOOL T7_;
	result = (NIM_BOOL)0;
	T1_ = (NIM_BOOL)0;
	T2_ = (NIM_BOOL)0;
	T3_ = (NIM_BOOL)0;
	T3_ = ((*n).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 3));
	if (!(T3_)) goto LA4_;
	T3_ = ((*(*n)._kind_4.sym).kind == ((tyEnum_TSymKind__cNCW9acsSznmEccl1fgQwkw) 20));
	LA4_: ;
	T2_ = T3_;
	if (!(T2_)) goto LA5_;
	T2_ = !(((*(*n)._kind_4.sym).position == ((NI) 0)));
	LA5_: ;
	T1_ = T2_;
	if (T1_) goto LA6_;
	T7_ = (NIM_BOOL)0;
	T7_ = ((*n).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 6));
	if (!(T7_)) goto LA8_;
	T7_ = !(((*n)._kind_1.intVal == IL64(0)));
	LA8_: ;
	T1_ = T7_;
	LA6_: ;
	result = T1_;
	return result;
}
N_LIB_PRIVATE N_NIMCALL(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*, propSpec__bT2fsf3zXYRpjYdeea19aAA_2)(tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* n, tyEnum_TSpecialWord__ycbpMCRV6Cd2eBh3X9biEiw effectType) {
	tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* result;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	result = (tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw*)0;
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
				tyObject_TNode__bROa11lyF5vxEN9aYNbHmhw* it;
				if (!(i_2 < colontmp_)) goto LA3;
				i = i_2;
				it = (*n)._kind_6.sons->data[i];
				{
					NIM_BOOL T6_;
					tyEnum_TSpecialWord__ycbpMCRV6Cd2eBh3X9biEiw T8_;
					T6_ = (NIM_BOOL)0;
					T6_ = ((*it).kind == ((tyEnum_TNodeKind__G4E4Gxe7oI2Cm03rkiOzQw) 34));
					if (!(T6_)) goto LA7_;
					T8_ = (tyEnum_TSpecialWord__ycbpMCRV6Cd2eBh3X9biEiw)0;
					T8_ = whichPragma__Pjztiiq9bHmTTxDuLd39cNRw(it);
					if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
					T6_ = (T8_ == effectType);
					LA7_: ;
					if (!T6_) goto LA9_;
					result = (*it)._kind_6.sons->data[((NI) 1)];
					goto BeforeRet_;
				}
				LA9_: ;
				i_2 += ((NI) 1);
			} LA3: ;
		}
	}
	}BeforeRet_: ;
	return result;
}