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
typedef struct TNimType TNimType;
typedef struct TNimNode TNimNode;
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
typedef struct tyObject_MD5Context__oMciKUdSdCaIeMtcxbiPOw tyObject_MD5Context__oMciKUdSdCaIeMtcxbiPOw;

/* section: NIM_merge_TYPES */
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
typedef NU8 tyEnum_TNimNodeKind__unfNsxrcATrufDZmpBq4HQ;
struct TNimNode {
tyEnum_TNimNodeKind__unfNsxrcATrufDZmpBq4HQ kind;
NI offset;
TNimType* typ;
NCSTRING name;
NI len;
TNimNode** sons;
};
typedef NU8 tyArray__qtqsWM5aXmcpMIVmvq3kAA[16];
struct TGenericSeq {
NI len;
NI reserved;
};
struct NimStringDesc {
  TGenericSeq Sup;
NIM_CHAR data[SEQ_DECL_SIZE];
};
typedef NU32 tyArray__FleBT9cC2nxhgiXmSYYnEKA[4];
typedef NU32 tyArray__JlnxiR65D9cjJpwi6uBZRtA[2];
typedef NU8 tyArray__w5VB8h5K8DB3oWrO5U2wqg[64];
struct tyObject_MD5Context__oMciKUdSdCaIeMtcxbiPOw {
tyArray__FleBT9cC2nxhgiXmSYYnEKA state;
tyArray__JlnxiR65D9cjJpwi6uBZRtA count;
tyArray__w5VB8h5K8DB3oWrO5U2wqg buffer;
};
typedef NU32 tyArray__U0SiHM0pVagA9c71oWelQMA[16];
typedef NU8 tyArray__cdsir9aPB24hAk6k77P9b9bCA[8];

/* section: NIM_merge_PROC_HEADERS */
static N_INLINE(void, nimZeroMem)(void* p, NI size);
static N_INLINE(void, nimSetMem__zxfKBYntu9cBapkhrCOk1fgmemory)(void* a, int v, NI size);
static N_INLINE(NIM_BOOL*, nimErrorFlag)(void);
N_LIB_PRIVATE N_NIMCALL(void, md5Init__aFJbJ6Fb5boL1UBjNazO4A)(tyObject_MD5Context__oMciKUdSdCaIeMtcxbiPOw* c);
static N_INLINE(void, zeroMem__FsvhfMqbswETmyMWtamDewsystem)(void* p, NI size);
N_LIB_PRIVATE N_NIMCALL(void, md5Update__3dyWcdKqKqoei9csU09cRuCA)(tyObject_MD5Context__oMciKUdSdCaIeMtcxbiPOw* c, NCSTRING input, NI len);
static N_INLINE(void, copyMem__i80o3k0SgEI5gTRCzYdyWAsystem)(void* dest, void* source, NI size);
static N_INLINE(void, nimCopyMem)(void* dest, void* source, NI size);
N_LIB_PRIVATE N_NIMCALL(void, transform__FpyLDebN7eBB2pkKKmjXJg)(void* buffer, NU32* state);
N_LIB_PRIVATE N_NIMCALL(void, encode__3XCrKZ0CpOjKYafeeVPnyw)(NU32* dest, NCSTRING src);
N_LIB_PRIVATE N_NIMCALL(void, FF__ShdGhVqwUZX4yDCc7A6Q6Q)(NU32* a, NU32 b, NU32 c, NU32 d, NU32 x, NU8 s, NU32 ac);
static N_INLINE(NU32, F__junZWnvhBQX0olNRUg769cgmd5)(NU32 x, NU32 y, NU32 z);
static N_INLINE(void, rot__E0YQh9cqfeV9b80YVg57S1mAmd5)(NU32* x, NU8 n);
N_LIB_PRIVATE N_NIMCALL(void, GG__ShdGhVqwUZX4yDCc7A6Q6Q_2)(NU32* a, NU32 b, NU32 c, NU32 d, NU32 x, NU8 s, NU32 ac);
static N_INLINE(NU32, G__junZWnvhBQX0olNRUg769cg_2md5)(NU32 x, NU32 y, NU32 z);
N_LIB_PRIVATE N_NIMCALL(void, HH__ShdGhVqwUZX4yDCc7A6Q6Q_3)(NU32* a, NU32 b, NU32 c, NU32 d, NU32 x, NU8 s, NU32 ac);
static N_INLINE(NU32, H__junZWnvhBQX0olNRUg769cg_3md5)(NU32 x, NU32 y, NU32 z);
N_LIB_PRIVATE N_NIMCALL(void, II__ShdGhVqwUZX4yDCc7A6Q6Q_4)(NU32* a, NU32 b, NU32 c, NU32 d, NU32 x, NU8 s, NU32 ac);
static N_INLINE(NU32, I__junZWnvhBQX0olNRUg769cg_4md5)(NU32 x, NU32 y, NU32 z);
static N_INLINE(NCSTRING, nimToCStringConv)(NimStringDesc* s);
N_LIB_PRIVATE N_NIMCALL(void, md5Final__CQoglTaDBxWEuKEO9ah9bXuQ)(tyObject_MD5Context__oMciKUdSdCaIeMtcxbiPOw* c, NU8* digest);
N_LIB_PRIVATE N_NIMCALL(void, decode__qtGCMfOlZdT3LJ4HIRsaNA)(NU8* dest, NI destLen_0, NU32* src, NI srcLen_0);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar___bUodBpefvLgLc2LbngPSqw)(tyArray__qtqsWM5aXmcpMIVmvq3kAA d);
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, addChar)(NimStringDesc* s, NIM_CHAR c);

/* section: NIM_merge_DATA */
extern TNimType NTI__k3HXouOuhqAKq0dx450lXQ_;
N_LIB_PRIVATE TNimType NTI__qtqsWM5aXmcpMIVmvq3kAA_;
STRING_LITERAL(TM__evv4Z8qaB9aehA3eX73W1Cw_2, "0123456789abcdef", 16);

/* section: NIM_merge_VARS */
extern NIM_BOOL nimInErrorMode__759bT87luu8XGcbkw13FUjA;

/* section: NIM_merge_PROCS */
static N_INLINE(void, nimSetMem__zxfKBYntu9cBapkhrCOk1fgmemory)(void* a, int v, NI size) {
	void* T1_;
	T1_ = (void*)0;
	T1_ = memset(a, v, ((size_t) (size)));
}
static N_INLINE(NIM_BOOL*, nimErrorFlag)(void) {
	NIM_BOOL* result;
	result = (NIM_BOOL*)0;
	result = (&nimInErrorMode__759bT87luu8XGcbkw13FUjA);
	return result;
}
static N_INLINE(void, nimZeroMem)(void* p, NI size) {
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	nimSetMem__zxfKBYntu9cBapkhrCOk1fgmemory(p, ((int) 0), size);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	}BeforeRet_: ;
}
static N_INLINE(void, zeroMem__FsvhfMqbswETmyMWtamDewsystem)(void* p, NI size) {
	nimZeroMem(p, size);
}
N_LIB_PRIVATE N_NIMCALL(void, md5Init__aFJbJ6Fb5boL1UBjNazO4A)(tyObject_MD5Context__oMciKUdSdCaIeMtcxbiPOw* c) {
	(*c).state[(((NI) 0))- 0] = ((NU32) 1732584193);
	(*c).state[(((NI) 1))- 0] = ((NU32) IL64(4023233417));
	(*c).state[(((NI) 2))- 0] = ((NU32) IL64(2562383102));
	(*c).state[(((NI) 3))- 0] = ((NU32) 271733878);
	(*c).count[(((NI) 0))- 0] = ((NU32) 0);
	(*c).count[(((NI) 1))- 0] = ((NU32) 0);
	zeroMem__FsvhfMqbswETmyMWtamDewsystem(((void*) ((*c).buffer)), ((NI) 64));
}
static N_INLINE(void, nimCopyMem)(void* dest, void* source, NI size) {
	void* T1_;
	T1_ = (void*)0;
	T1_ = memcpy(dest, source, ((size_t) (size)));
}
static N_INLINE(void, copyMem__i80o3k0SgEI5gTRCzYdyWAsystem)(void* dest, void* source, NI size) {
	nimCopyMem(dest, source, size);
}
N_LIB_PRIVATE N_NIMCALL(void, encode__3XCrKZ0CpOjKYafeeVPnyw)(NU32* dest, NCSTRING src) {
	NI j;
	j = ((NI) 0);
	{
		NI i;
		NI res;
		i = (NI)0;
		res = ((NI) 0);
		{
			while (1) {
				if (!(res <= ((NI) 15))) goto LA3;
				i = res;
				dest[(i)- 0] = (NU32)((NU32)((NU32)(((NU32) (((NU8)(src[j])))) | (NU32)((NU64)(((NU32) (((NU8)(src[(NI)(j + ((NI) 1))]))))) << (NU64)(((NI) 8)))) | (NU32)((NU64)(((NU32) (((NU8)(src[(NI)(j + ((NI) 2))]))))) << (NU64)(((NI) 16)))) | (NU32)((NU64)(((NU32) (((NU8)(src[(NI)(j + ((NI) 3))]))))) << (NU64)(((NI) 24))));
				j += ((NI) 4);
				res += ((NI) 1);
			} LA3: ;
		}
	}
}
static N_INLINE(NU32, F__junZWnvhBQX0olNRUg769cgmd5)(NU32 x, NU32 y, NU32 z) {
	NU32 result;
	result = (NU32)0;
	result = (NU32)((NU32)(x & y) | (NU32)((NU32)((NU32) ~(x)) & z));
	return result;
}
static N_INLINE(void, rot__E0YQh9cqfeV9b80YVg57S1mAmd5)(NU32* x, NU8 n) {
	(*x) = (NU32)((NU32)((NU32)((*x)) << (NU32)(n)) | (NU32)((NU32)((*x)) >> (NU32)((NU32)((NU32)(((NU32) 32)) - (NU32)(((NU32) (n)))))));
}
N_LIB_PRIVATE N_NIMCALL(void, FF__ShdGhVqwUZX4yDCc7A6Q6Q)(NU32* a, NU32 b, NU32 c, NU32 d, NU32 x, NU8 s, NU32 ac) {
	NU32 T1_;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	T1_ = (NU32)0;
	T1_ = F__junZWnvhBQX0olNRUg769cgmd5(b, c, d);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	(*a) = (NU32)((NU32)((NU32)((NU32)((NU32)((NU32)((*a)) + (NU32)(T1_))) + (NU32)(x))) + (NU32)(ac));
	rot__E0YQh9cqfeV9b80YVg57S1mAmd5(a, s);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	(*a) = (NU32)((NU32)((*a)) + (NU32)(b));
	}BeforeRet_: ;
}
static N_INLINE(NU32, G__junZWnvhBQX0olNRUg769cg_2md5)(NU32 x, NU32 y, NU32 z) {
	NU32 result;
	result = (NU32)0;
	result = (NU32)((NU32)(x & z) | (NU32)(y & (NU32)((NU32) ~(z))));
	return result;
}
N_LIB_PRIVATE N_NIMCALL(void, GG__ShdGhVqwUZX4yDCc7A6Q6Q_2)(NU32* a, NU32 b, NU32 c, NU32 d, NU32 x, NU8 s, NU32 ac) {
	NU32 T1_;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	T1_ = (NU32)0;
	T1_ = G__junZWnvhBQX0olNRUg769cg_2md5(b, c, d);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	(*a) = (NU32)((NU32)((NU32)((NU32)((NU32)((NU32)((*a)) + (NU32)(T1_))) + (NU32)(x))) + (NU32)(ac));
	rot__E0YQh9cqfeV9b80YVg57S1mAmd5(a, s);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	(*a) = (NU32)((NU32)((*a)) + (NU32)(b));
	}BeforeRet_: ;
}
static N_INLINE(NU32, H__junZWnvhBQX0olNRUg769cg_3md5)(NU32 x, NU32 y, NU32 z) {
	NU32 result;
	result = (NU32)0;
	result = (NU32)((NU32)(x ^ y) ^ z);
	return result;
}
N_LIB_PRIVATE N_NIMCALL(void, HH__ShdGhVqwUZX4yDCc7A6Q6Q_3)(NU32* a, NU32 b, NU32 c, NU32 d, NU32 x, NU8 s, NU32 ac) {
	NU32 T1_;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	T1_ = (NU32)0;
	T1_ = H__junZWnvhBQX0olNRUg769cg_3md5(b, c, d);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	(*a) = (NU32)((NU32)((NU32)((NU32)((NU32)((NU32)((*a)) + (NU32)(T1_))) + (NU32)(x))) + (NU32)(ac));
	rot__E0YQh9cqfeV9b80YVg57S1mAmd5(a, s);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	(*a) = (NU32)((NU32)((*a)) + (NU32)(b));
	}BeforeRet_: ;
}
static N_INLINE(NU32, I__junZWnvhBQX0olNRUg769cg_4md5)(NU32 x, NU32 y, NU32 z) {
	NU32 result;
	result = (NU32)0;
	result = (NU32)(y ^ (NU32)(x | (NU32)((NU32) ~(z))));
	return result;
}
N_LIB_PRIVATE N_NIMCALL(void, II__ShdGhVqwUZX4yDCc7A6Q6Q_4)(NU32* a, NU32 b, NU32 c, NU32 d, NU32 x, NU8 s, NU32 ac) {
	NU32 T1_;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	T1_ = (NU32)0;
	T1_ = I__junZWnvhBQX0olNRUg769cg_4md5(b, c, d);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	(*a) = (NU32)((NU32)((NU32)((NU32)((NU32)((NU32)((*a)) + (NU32)(T1_))) + (NU32)(x))) + (NU32)(ac));
	rot__E0YQh9cqfeV9b80YVg57S1mAmd5(a, s);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	(*a) = (NU32)((NU32)((*a)) + (NU32)(b));
	}BeforeRet_: ;
}
N_LIB_PRIVATE N_NIMCALL(void, transform__FpyLDebN7eBB2pkKKmjXJg)(void* buffer, NU32* state) {
	tyArray__U0SiHM0pVagA9c71oWelQMA myBlock;
	NU32 a;
	NU32 b;
	NU32 c;
	NU32 d;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	nimZeroMem((void*)myBlock, sizeof(tyArray__U0SiHM0pVagA9c71oWelQMA));
	encode__3XCrKZ0CpOjKYafeeVPnyw(myBlock, ((NCSTRING) (buffer)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	a = state[(((NI) 0))- 0];
	b = state[(((NI) 1))- 0];
	c = state[(((NI) 2))- 0];
	d = state[(((NI) 3))- 0];
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&a), b, c, d, myBlock[(((NI) 0))- 0], ((NU8) 7), ((NU32) IL64(3614090360)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&d), a, b, c, myBlock[(((NI) 1))- 0], ((NU8) 12), ((NU32) IL64(3905402710)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&c), d, a, b, myBlock[(((NI) 2))- 0], ((NU8) 17), ((NU32) 606105819));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&b), c, d, a, myBlock[(((NI) 3))- 0], ((NU8) 22), ((NU32) IL64(3250441966)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&a), b, c, d, myBlock[(((NI) 4))- 0], ((NU8) 7), ((NU32) IL64(4118548399)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&d), a, b, c, myBlock[(((NI) 5))- 0], ((NU8) 12), ((NU32) 1200080426));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&c), d, a, b, myBlock[(((NI) 6))- 0], ((NU8) 17), ((NU32) IL64(2821735955)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&b), c, d, a, myBlock[(((NI) 7))- 0], ((NU8) 22), ((NU32) IL64(4249261313)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&a), b, c, d, myBlock[(((NI) 8))- 0], ((NU8) 7), ((NU32) 1770035416));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&d), a, b, c, myBlock[(((NI) 9))- 0], ((NU8) 12), ((NU32) IL64(2336552879)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&c), d, a, b, myBlock[(((NI) 10))- 0], ((NU8) 17), ((NU32) IL64(4294925233)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&b), c, d, a, myBlock[(((NI) 11))- 0], ((NU8) 22), ((NU32) IL64(2304563134)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&a), b, c, d, myBlock[(((NI) 12))- 0], ((NU8) 7), ((NU32) 1804603682));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&d), a, b, c, myBlock[(((NI) 13))- 0], ((NU8) 12), ((NU32) IL64(4254626195)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&c), d, a, b, myBlock[(((NI) 14))- 0], ((NU8) 17), ((NU32) IL64(2792965006)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	FF__ShdGhVqwUZX4yDCc7A6Q6Q((&b), c, d, a, myBlock[(((NI) 15))- 0], ((NU8) 22), ((NU32) 1236535329));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&a), b, c, d, myBlock[(((NI) 1))- 0], ((NU8) 5), ((NU32) IL64(4129170786)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&d), a, b, c, myBlock[(((NI) 6))- 0], ((NU8) 9), ((NU32) IL64(3225465664)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&c), d, a, b, myBlock[(((NI) 11))- 0], ((NU8) 14), ((NU32) 643717713));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&b), c, d, a, myBlock[(((NI) 0))- 0], ((NU8) 20), ((NU32) IL64(3921069994)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&a), b, c, d, myBlock[(((NI) 5))- 0], ((NU8) 5), ((NU32) IL64(3593408605)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&d), a, b, c, myBlock[(((NI) 10))- 0], ((NU8) 9), ((NU32) 38016083));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&c), d, a, b, myBlock[(((NI) 15))- 0], ((NU8) 14), ((NU32) IL64(3634488961)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&b), c, d, a, myBlock[(((NI) 4))- 0], ((NU8) 20), ((NU32) IL64(3889429448)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&a), b, c, d, myBlock[(((NI) 9))- 0], ((NU8) 5), ((NU32) 568446438));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&d), a, b, c, myBlock[(((NI) 14))- 0], ((NU8) 9), ((NU32) IL64(3275163606)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&c), d, a, b, myBlock[(((NI) 3))- 0], ((NU8) 14), ((NU32) IL64(4107603335)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&b), c, d, a, myBlock[(((NI) 8))- 0], ((NU8) 20), ((NU32) 1163531501));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&a), b, c, d, myBlock[(((NI) 13))- 0], ((NU8) 5), ((NU32) IL64(2850285829)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&d), a, b, c, myBlock[(((NI) 2))- 0], ((NU8) 9), ((NU32) IL64(4243563512)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&c), d, a, b, myBlock[(((NI) 7))- 0], ((NU8) 14), ((NU32) 1735328473));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	GG__ShdGhVqwUZX4yDCc7A6Q6Q_2((&b), c, d, a, myBlock[(((NI) 12))- 0], ((NU8) 20), ((NU32) IL64(2368359562)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&a), b, c, d, myBlock[(((NI) 5))- 0], ((NU8) 4), ((NU32) IL64(4294588738)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&d), a, b, c, myBlock[(((NI) 8))- 0], ((NU8) 11), ((NU32) IL64(2272392833)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&c), d, a, b, myBlock[(((NI) 11))- 0], ((NU8) 16), ((NU32) 1839030562));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&b), c, d, a, myBlock[(((NI) 14))- 0], ((NU8) 23), ((NU32) IL64(4259657740)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&a), b, c, d, myBlock[(((NI) 1))- 0], ((NU8) 4), ((NU32) IL64(2763975236)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&d), a, b, c, myBlock[(((NI) 4))- 0], ((NU8) 11), ((NU32) 1272893353));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&c), d, a, b, myBlock[(((NI) 7))- 0], ((NU8) 16), ((NU32) IL64(4139469664)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&b), c, d, a, myBlock[(((NI) 10))- 0], ((NU8) 23), ((NU32) IL64(3200236656)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&a), b, c, d, myBlock[(((NI) 13))- 0], ((NU8) 4), ((NU32) 681279174));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&d), a, b, c, myBlock[(((NI) 0))- 0], ((NU8) 11), ((NU32) IL64(3936430074)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&c), d, a, b, myBlock[(((NI) 3))- 0], ((NU8) 16), ((NU32) IL64(3572445317)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&b), c, d, a, myBlock[(((NI) 6))- 0], ((NU8) 23), ((NU32) 76029189));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&a), b, c, d, myBlock[(((NI) 9))- 0], ((NU8) 4), ((NU32) IL64(3654602809)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&d), a, b, c, myBlock[(((NI) 12))- 0], ((NU8) 11), ((NU32) IL64(3873151461)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&c), d, a, b, myBlock[(((NI) 15))- 0], ((NU8) 16), ((NU32) 530742520));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	HH__ShdGhVqwUZX4yDCc7A6Q6Q_3((&b), c, d, a, myBlock[(((NI) 2))- 0], ((NU8) 23), ((NU32) IL64(3299628645)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&a), b, c, d, myBlock[(((NI) 0))- 0], ((NU8) 6), ((NU32) IL64(4096336452)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&d), a, b, c, myBlock[(((NI) 7))- 0], ((NU8) 10), ((NU32) 1126891415));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&c), d, a, b, myBlock[(((NI) 14))- 0], ((NU8) 15), ((NU32) IL64(2878612391)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&b), c, d, a, myBlock[(((NI) 5))- 0], ((NU8) 21), ((NU32) IL64(4237533241)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&a), b, c, d, myBlock[(((NI) 12))- 0], ((NU8) 6), ((NU32) 1700485571));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&d), a, b, c, myBlock[(((NI) 3))- 0], ((NU8) 10), ((NU32) IL64(2399980690)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&c), d, a, b, myBlock[(((NI) 10))- 0], ((NU8) 15), ((NU32) IL64(4293915773)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&b), c, d, a, myBlock[(((NI) 1))- 0], ((NU8) 21), ((NU32) IL64(2240044497)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&a), b, c, d, myBlock[(((NI) 8))- 0], ((NU8) 6), ((NU32) 1873313359));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&d), a, b, c, myBlock[(((NI) 15))- 0], ((NU8) 10), ((NU32) IL64(4264355552)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&c), d, a, b, myBlock[(((NI) 6))- 0], ((NU8) 15), ((NU32) IL64(2734768916)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&b), c, d, a, myBlock[(((NI) 13))- 0], ((NU8) 21), ((NU32) 1309151649));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&a), b, c, d, myBlock[(((NI) 4))- 0], ((NU8) 6), ((NU32) IL64(4149444226)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&d), a, b, c, myBlock[(((NI) 11))- 0], ((NU8) 10), ((NU32) IL64(3174756917)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&c), d, a, b, myBlock[(((NI) 2))- 0], ((NU8) 15), ((NU32) 718787259));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	II__ShdGhVqwUZX4yDCc7A6Q6Q_4((&b), c, d, a, myBlock[(((NI) 9))- 0], ((NU8) 21), ((NU32) IL64(3951481745)));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	state[(((NI) 0))- 0] = (NU32)((NU32)(state[(((NI) 0))- 0]) + (NU32)(a));
	state[(((NI) 1))- 0] = (NU32)((NU32)(state[(((NI) 1))- 0]) + (NU32)(b));
	state[(((NI) 2))- 0] = (NU32)((NU32)(state[(((NI) 2))- 0]) + (NU32)(c));
	state[(((NI) 3))- 0] = (NU32)((NU32)(state[(((NI) 3))- 0]) + (NU32)(d));
	}BeforeRet_: ;
}
N_LIB_PRIVATE N_NIMCALL(void, md5Update__3dyWcdKqKqoei9csU09cRuCA)(tyObject_MD5Context__oMciKUdSdCaIeMtcxbiPOw* c, NCSTRING input, NI len) {
	NCSTRING input_2;
	NI Index;
	NI PartLen;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	input_2 = input;
	Index = ((NI) ((NU32)((NU32)((NU32)((*c).count[(((NI) 0))- 0]) >> (NU64)(((NI) 3))) & ((NU32) 63))));
	(*c).count[(((NI) 0))- 0] = (NU32)((NU32)((*c).count[(((NI) 0))- 0]) + (NU32)((NU32)((NU64)(((NU32) (len))) << (NU64)(((NI) 3)))));
	{
		if (!((NU32)((*c).count[(((NI) 0))- 0]) < (NU32)((NU32)((NU64)(((NU32) (len))) << (NU64)(((NI) 3)))))) goto LA3_;
		(*c).count[(((NI) 1))- 0] = (NU32)((NU32)((*c).count[(((NI) 1))- 0]) + (NU32)(((NU32) 1)));
	}
	LA3_: ;
	(*c).count[(((NI) 1))- 0] = (NU32)((NU32)((*c).count[(((NI) 1))- 0]) + (NU32)((NU32)((NU32)(((NU32) (len))) >> (NU64)(((NI) 29)))));
	PartLen = (NI)(((NI) 64) - Index);
	{
		void* T9_;
		NI i;
		void* T12_;
		if (!(PartLen <= len)) goto LA7_;
		copyMem__i80o3k0SgEI5gTRCzYdyWAsystem(((void*) ((&(*c).buffer[(Index)- 0]))), ((void*) (input_2)), ((NI) (PartLen)));
		T9_ = (void*)0;
		T9_ = ((void*) ((*c).buffer));
		transform__FpyLDebN7eBB2pkKKmjXJg(T9_, (*c).state);
		if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
		i = PartLen;
		{
			while (1) {
				if (!((NI)(i + ((NI) 63)) < len)) goto LA11;
				transform__FpyLDebN7eBB2pkKKmjXJg(((void*) ((&input_2[i]))), (*c).state);
				if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
				i += ((NI) 64);
			} LA11: ;
		}
		T12_ = (void*)0;
		T12_ = ((void*) ((&input_2[i])));
		copyMem__i80o3k0SgEI5gTRCzYdyWAsystem(((void*) ((&(*c).buffer[(((NI) 0))- 0]))), T12_, ((NI) ((NI)(len - i))));
	}
	goto LA5_;
	LA7_: ;
	{
		copyMem__i80o3k0SgEI5gTRCzYdyWAsystem(((void*) ((&(*c).buffer[(Index)- 0]))), ((void*) ((&input_2[((NI) 0)]))), ((NI) (len)));
	}
	LA5_: ;
	}BeforeRet_: ;
}
static N_INLINE(NCSTRING, nimToCStringConv)(NimStringDesc* s) {
	NCSTRING result;
	result = (NCSTRING)0;
	{
		NIM_BOOL T3_;
		T3_ = (NIM_BOOL)0;
		T3_ = (s == NIM_NIL);
		if (T3_) goto LA4_;
		T3_ = ((*s).Sup.len == ((NI) 0));
		LA4_: ;
		if (!T3_) goto LA5_;
		result = "";
	}
	goto LA1_;
	LA5_: ;
	{
		result = ((NCSTRING) ((*s).data));
	}
	LA1_: ;
	return result;
}
N_LIB_PRIVATE N_NIMCALL(void, decode__qtGCMfOlZdT3LJ4HIRsaNA)(NU8* dest, NI destLen_0, NU32* src, NI srcLen_0) {
	NI i;
	i = ((NI) 0);
	{
		NI j;
		NI colontmp_;
		NI res;
		j = (NI)0;
		colontmp_ = (NI)0;
		colontmp_ = (srcLen_0-1);
		res = ((NI) 0);
		{
			while (1) {
				if (!(res <= colontmp_)) goto LA3;
				j = res;
				dest[i] = ((NU8) ((NU32)(src[j] & ((NU32) 255))));
				dest[(NI)(i + ((NI) 1))] = ((NU8) ((NU32)((NU32)((NU32)(src[j]) >> (NU64)(((NI) 8))) & ((NU32) 255))));
				dest[(NI)(i + ((NI) 2))] = ((NU8) ((NU32)((NU32)((NU32)(src[j]) >> (NU64)(((NI) 16))) & ((NU32) 255))));
				dest[(NI)(i + ((NI) 3))] = ((NU8) ((NU32)((NU32)((NU32)(src[j]) >> (NU64)(((NI) 24))) & ((NU32) 255))));
				i += ((NI) 4);
				res += ((NI) 1);
			} LA3: ;
		}
	}
}
N_LIB_PRIVATE N_NIMCALL(void, md5Final__CQoglTaDBxWEuKEO9ah9bXuQ)(tyObject_MD5Context__oMciKUdSdCaIeMtcxbiPOw* c, NU8* digest) {
	tyArray__cdsir9aPB24hAk6k77P9b9bCA Bits;
	NI PadLen;
	NI Index;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	nimZeroMem((void*)Bits, sizeof(tyArray__cdsir9aPB24hAk6k77P9b9bCA));
	PadLen = (NI)0;
	decode__qtGCMfOlZdT3LJ4HIRsaNA(Bits, 8, (*c).count, 2);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	Index = ((NI) ((NU32)((NU32)((NU32)((*c).count[(((NI) 0))- 0]) >> (NU64)(((NI) 3))) & ((NU32) 63))));
	{
		if (!(Index < ((NI) 56))) goto LA3_;
		PadLen = (NI)(((NI) 56) - Index);
	}
	goto LA1_;
	LA3_: ;
	{
		PadLen = (NI)(((NI) 120) - Index);
	}
	LA1_: ;
	md5Update__3dyWcdKqKqoei9csU09cRuCA(c, "\200\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
"\000", PadLen);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	md5Update__3dyWcdKqKqoei9csU09cRuCA(c, ((NCSTRING) (Bits)), ((NI) 8));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	decode__qtGCMfOlZdT3LJ4HIRsaNA(digest, 16, (*c).state, 4);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	zeroMem__FsvhfMqbswETmyMWtamDewsystem(((void*) (c)), ((NI) 88));
	}BeforeRet_: ;
}
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, dollar___bUodBpefvLgLc2LbngPSqw)(tyArray__qtqsWM5aXmcpMIVmvq3kAA d) {
	NimStringDesc* result;
	result = (NimStringDesc*)0;
	result = ((NimStringDesc*) NIM_NIL);
	{
		NI i;
		NI res;
		i = (NI)0;
		res = ((NI) 0);
		{
			while (1) {
				if (!(res <= ((NI) 15))) goto LA3;
				i = res;
				result = addChar(result, ((NimStringDesc*) &TM__evv4Z8qaB9aehA3eX73W1Cw_2)->data[(NI)((NI)((NI64)(((NI) (d[(i)- 0]))) >> (NU64)(((NI) 4))) & ((NI) 15))]);
				result = addChar(result, ((NimStringDesc*) &TM__evv4Z8qaB9aehA3eX73W1Cw_2)->data[(NI)(((NI) (d[(i)- 0])) & ((NI) 15))]);
				res += ((NI) 1);
			} LA3: ;
		}
	}
	return result;
}
N_LIB_PRIVATE N_NIMCALL(NimStringDesc*, getMD5__kEzF9cC2zt4kZNszZVUnKEA)(NimStringDesc* s) {
	NimStringDesc* result;
	tyObject_MD5Context__oMciKUdSdCaIeMtcxbiPOw c;
	tyArray__qtqsWM5aXmcpMIVmvq3kAA d;
	NimStringDesc* T1_;
NIM_BOOL* nimErr_;
{nimErr_ = nimErrorFlag();
	result = (NimStringDesc*)0;
	nimZeroMem((void*)(&c), sizeof(tyObject_MD5Context__oMciKUdSdCaIeMtcxbiPOw));
	nimZeroMem((void*)d, sizeof(tyArray__qtqsWM5aXmcpMIVmvq3kAA));
	md5Init__aFJbJ6Fb5boL1UBjNazO4A((&c));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	T1_ = (NimStringDesc*)0;
	T1_ = s;
	md5Update__3dyWcdKqKqoei9csU09cRuCA((&c), nimToCStringConv(T1_), (s ? s->Sup.len : 0));
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	md5Final__CQoglTaDBxWEuKEO9ah9bXuQ((&c), d);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	result = dollar___bUodBpefvLgLc2LbngPSqw(d);
	if (NIM_UNLIKELY(*nimErr_)) goto BeforeRet_;
	}BeforeRet_: ;
	return result;
}
N_LIB_PRIVATE N_NIMCALL(void, stdlib_md5DatInit000)(void) {

/* section: NIM_merge_TYPE_INIT3 */
NTI__qtqsWM5aXmcpMIVmvq3kAA_.size = sizeof(tyArray__qtqsWM5aXmcpMIVmvq3kAA);
NTI__qtqsWM5aXmcpMIVmvq3kAA_.align = NIM_ALIGNOF(tyArray__qtqsWM5aXmcpMIVmvq3kAA);
NTI__qtqsWM5aXmcpMIVmvq3kAA_.kind = 16;
NTI__qtqsWM5aXmcpMIVmvq3kAA_.base = (&NTI__k3HXouOuhqAKq0dx450lXQ_);
NTI__qtqsWM5aXmcpMIVmvq3kAA_.flags = 3;
}

