/* Generated by Nim Compiler v1.2.6 */
/*   (c) 2020 Andreas Rumpf */
/* The generated code is subject to the original license. */
#define NIM_INTBITS 64

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
#define nimfr_(x, y)
#define nimln_(x, y)
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
struct TGenericSeq {
NI len;
NI reserved;
};
struct NimStringDesc {
  TGenericSeq Sup;
NIM_CHAR data[SEQ_DECL_SIZE];
};
N_NIMCALL(NimStringDesc*, rawNewString)(NI cap);
N_LIB_PRIVATE N_NIMCALL(void, escapeJson__YID1CO5Pb6vZOjpjrUt6Lw)(NimStringDesc* s, NimStringDesc** result);
static N_INLINE(void, appendString)(NimStringDesc* dest, NimStringDesc* src);
static N_INLINE(void, copyMem__i80o3k0SgEI5gTRCzYdyWAsystem)(void* dest, void* source, NI size);
static N_INLINE(void, nimCopyMem)(void* dest, void* source, NI size);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, resizeString)(NimStringDesc* dest, NI addlen);
N_LIB_PRIVATE N_NIMCALL(void, escapeJsonUnquoted__YID1CO5Pb6vZOjpjrUt6Lw_2)(NimStringDesc* s, NimStringDesc** result);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, nimIntToStr)(NI x);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, nsuToHex)(NI64 x, NI len);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, addChar)(NimStringDesc* s, NIM_CHAR c);
STRING_LITERAL(TM__9b9bytt1stv9cZ8uqII7HFgew_2, "\"", 1);
STRING_LITERAL(TM__9b9bytt1stv9cZ8uqII7HFgew_3, "\\n", 2);
STRING_LITERAL(TM__9b9bytt1stv9cZ8uqII7HFgew_4, "\\b", 2);
STRING_LITERAL(TM__9b9bytt1stv9cZ8uqII7HFgew_5, "\\f", 2);
STRING_LITERAL(TM__9b9bytt1stv9cZ8uqII7HFgew_6, "\\t", 2);
STRING_LITERAL(TM__9b9bytt1stv9cZ8uqII7HFgew_7, "\\u000b", 6);
STRING_LITERAL(TM__9b9bytt1stv9cZ8uqII7HFgew_8, "\\r", 2);
STRING_LITERAL(TM__9b9bytt1stv9cZ8uqII7HFgew_9, "\\\"", 2);
STRING_LITERAL(TM__9b9bytt1stv9cZ8uqII7HFgew_10, "\\u000", 5);
STRING_LITERAL(TM__9b9bytt1stv9cZ8uqII7HFgew_11, "\\u00", 4);
STRING_LITERAL(TM__9b9bytt1stv9cZ8uqII7HFgew_12, "\\\\", 2);
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
		if (!!((src == NIM_NIL))) goto LA3_;
		copyMem__i80o3k0SgEI5gTRCzYdyWAsystem(((void*) ((&(*dest).data[(*dest).Sup.len]))), ((void*) ((*src).data)), ((NI) ((NI)((*src).Sup.len + ((NI) 1)))));
		(*dest).Sup.len += (*src).Sup.len;
	}
	LA3_: ;
}
N_LIB_PRIVATE N_NIMCALL(void, escapeJsonUnquoted__YID1CO5Pb6vZOjpjrUt6Lw_2)(NimStringDesc* s, NimStringDesc** result) {
	{
		NIM_CHAR c;
		NI i;
		NI L;
		c = (NIM_CHAR)0;
		i = ((NI) 0);
		L = (s ? s->Sup.len : 0);
		{
			while (1) {
				if (!(i < L)) goto LA3;
				c = s->data[i];
				switch (((NU8)(c))) {
				case 10:
				{
					(*result) = resizeString((*result), 2);
appendString((*result), ((NimStringDesc*) &TM__9b9bytt1stv9cZ8uqII7HFgew_3));
				}
				break;
				case 8:
				{
					(*result) = resizeString((*result), 2);
appendString((*result), ((NimStringDesc*) &TM__9b9bytt1stv9cZ8uqII7HFgew_4));
				}
				break;
				case 12:
				{
					(*result) = resizeString((*result), 2);
appendString((*result), ((NimStringDesc*) &TM__9b9bytt1stv9cZ8uqII7HFgew_5));
				}
				break;
				case 9:
				{
					(*result) = resizeString((*result), 2);
appendString((*result), ((NimStringDesc*) &TM__9b9bytt1stv9cZ8uqII7HFgew_6));
				}
				break;
				case 11:
				{
					(*result) = resizeString((*result), 6);
appendString((*result), ((NimStringDesc*) &TM__9b9bytt1stv9cZ8uqII7HFgew_7));
				}
				break;
				case 13:
				{
					(*result) = resizeString((*result), 2);
appendString((*result), ((NimStringDesc*) &TM__9b9bytt1stv9cZ8uqII7HFgew_8));
				}
				break;
				case 34:
				{
					(*result) = resizeString((*result), 2);
appendString((*result), ((NimStringDesc*) &TM__9b9bytt1stv9cZ8uqII7HFgew_9));
				}
				break;
				case 0 ... 7:
				{
					NimStringDesc* T12_;
					NimStringDesc* T13_;
					T12_ = (NimStringDesc*)0;
					T13_ = (NimStringDesc*)0;
					T13_ = nimIntToStr(((NU8)(c)));
					T12_ = rawNewString((T13_ ? T13_->Sup.len : 0) + 5);
appendString(T12_, ((NimStringDesc*) &TM__9b9bytt1stv9cZ8uqII7HFgew_10));
appendString(T12_, T13_);
					(*result) = resizeString((*result), (T12_ ? T12_->Sup.len : 0) + 0);
appendString((*result), T12_);
				}
				break;
				case 14 ... 31:
				{
					NimStringDesc* T15_;
					NimStringDesc* T16_;
					T15_ = (NimStringDesc*)0;
					T16_ = (NimStringDesc*)0;
					T16_ = nsuToHex(((NI64) (((NU8)(c)))), ((NI) 2));
					T15_ = rawNewString((T16_ ? T16_->Sup.len : 0) + 4);
appendString(T15_, ((NimStringDesc*) &TM__9b9bytt1stv9cZ8uqII7HFgew_11));
appendString(T15_, T16_);
					(*result) = resizeString((*result), (T15_ ? T15_->Sup.len : 0) + 0);
appendString((*result), T15_);
				}
				break;
				case 92:
				{
					(*result) = resizeString((*result), 2);
appendString((*result), ((NimStringDesc*) &TM__9b9bytt1stv9cZ8uqII7HFgew_12));
				}
				break;
				default:
				{
					(*result) = addChar((*result), c);
				}
				break;
				}
				i += ((NI) 1);
			} LA3: ;
		}
	}
}
N_LIB_PRIVATE N_NIMCALL(void, escapeJson__YID1CO5Pb6vZOjpjrUt6Lw)(NimStringDesc* s, NimStringDesc** result) {
	(*result) = resizeString((*result), 1);
appendString((*result), ((NimStringDesc*) &TM__9b9bytt1stv9cZ8uqII7HFgew_2));
	escapeJsonUnquoted__YID1CO5Pb6vZOjpjrUt6Lw_2(s, result);
	(*result) = resizeString((*result), 1);
appendString((*result), ((NimStringDesc*) &TM__9b9bytt1stv9cZ8uqII7HFgew_2));
}
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, escapeJson__NGTWHwdUy0ADNv9alK3ECRA)(NimStringDesc* s) {
	NimStringDesc* result;
	result = (NimStringDesc*)0;
	result = rawNewString(((NI) ((NI)((s ? s->Sup.len : 0) + (NI)((NI64)((s ? s->Sup.len : 0)) >> (NU64)(((NI) 3)))))));
	escapeJson__YID1CO5Pb6vZOjpjrUt6Lw(s, (&result));
	return result;
}
