/* Generated by Nim Compiler v1.2.6 */
/*   (c) 2020 Andreas Rumpf */
/* The generated code is subject to the original license. */
#define NIM_INTBITS 64

#include "nimbase.h"
#include <setjmp.h>
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
typedef struct tyObject_PyModuleDesc__gBC8z6Ez5xj3dXoP0ylCRA tyObject_PyModuleDesc__gBC8z6Ez5xj3dXoP0ylCRA;
typedef struct tySequence__E2XyP5e7Jr9aMpJMjdz5Tkg tySequence__E2XyP5e7Jr9aMpJMjdz5Tkg;
typedef struct tySequence__1Ib9a4sxiw4YCYbDTADLEsg tySequence__1Ib9a4sxiw4YCYbDTADLEsg;
typedef struct tySequence__xxWWYOndkW9adiM61bZkvsg tySequence__xxWWYOndkW9adiM61bZkvsg;
typedef struct TNimType TNimType;
typedef struct TNimNode TNimNode;
typedef struct NimStringDesc NimStringDesc;
typedef struct TGenericSeq TGenericSeq;
typedef struct tySequence__sM4lkSb7zS6F7OVMvW9cffQ tySequence__sM4lkSb7zS6F7OVMvW9cffQ;
typedef struct Exception Exception;
typedef struct RootObj RootObj;
typedef struct tySequence__uB9b75OUPRENsBAu4AnoePA tySequence__uB9b75OUPRENsBAu4AnoePA;
typedef struct TSafePoint TSafePoint;
typedef struct tyObject_PyObjectObj__aD5pkFWInXrZXinZ42cDEg tyObject_PyObjectObj__aD5pkFWInXrZXinZ42cDEg;
typedef struct tyObject_PyLibcolonObjectType___bTw708kK89b8Vj9cmSu9a4zig tyObject_PyLibcolonObjectType___bTw708kK89b8Vj9cmSu9a4zig;
typedef struct tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g;
typedef struct tyObject_RawPyBuffer__0qyRdSZKtLACJ1u4qMMP2w tyObject_RawPyBuffer__0qyRdSZKtLACJ1u4qMMP2w;
typedef struct tyObject_Complex__zWadV1X9aMO7qS9bsQFB0JFA tyObject_Complex__zWadV1X9aMO7qS9bsQFB0JFA;
typedef struct tyObject_PyMethodDef__9aWi1PsmvCuTKIYDHHnhfcw tyObject_PyMethodDef__9aWi1PsmvCuTKIYDHHnhfcw;
typedef struct tyObject_InterpretercolonObjectType___P52MELrsYCwBeooqRNfjVA tyObject_InterpretercolonObjectType___P52MELrsYCwBeooqRNfjVA;
typedef struct tyObject_TLLStream__a5oZYQ9aTktYME2449ayEi6g tyObject_TLLStream__a5oZYQ9aTktYME2449ayEi6g;
typedef struct tyObject_PyTypeDesc__BKCcJxogshNojOoN23Qfbg tyObject_PyTypeDesc__BKCcJxogshNojOoN23Qfbg;
typedef struct tySequence__mAI4KvRAgoko9bmrV4QRgaQ tySequence__mAI4KvRAgoko9bmrV4QRgaQ;
typedef struct tyObject_PyIteratorDesc__3Lh9c29bpC2Iomkl9cQO9cGqEw tyObject_PyIteratorDesc__3Lh9c29bpC2Iomkl9cQO9cGqEw;
typedef struct tyObject_StackTraceEntry__oLyohQ7O2XOvGnflOss8EA tyObject_StackTraceEntry__oLyohQ7O2XOvGnflOss8EA;
typedef struct tyObject_PyMemberDef__WC29aEeHi2Pdy9c4AkllcBTg tyObject_PyMemberDef__WC29aEeHi2Pdy9c4AkllcBTg;
struct tyObject_PyModuleDesc__gBC8z6Ez5xj3dXoP0ylCRA {
NCSTRING name;
NCSTRING doc;
tySequence__E2XyP5e7Jr9aMpJMjdz5Tkg* methods;
tySequence__1Ib9a4sxiw4YCYbDTADLEsg* types;
tySequence__xxWWYOndkW9adiM61bZkvsg* iterators;
};
typedef NU8 tyEnum_TNimKind__jIBKr1ejBgsfM33Kxw4j7A;
typedef NU8 tySet_tyEnum_TNimTypeFlag__v8QUszD1sWlSIWZz7mC4bQ;
typedef N_NIMCALL_PTR(void, tyProc__ojoeKfW4VYIm36I9cpDTQIg) (void* p, NI op);
typedef N_NIMCALL_PTR(void*, tyProc__WSm2xU5ARYv9aAR4l0z9c9auQ) (void* p);
struct TNimType {
NI size;
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
typedef N_NIMCALL_PTR(void, tyProc__T4eqaYlFJYZUv9aG9b1TV0bQ) (void);
struct TGenericSeq {
NI len;
NI reserved;
};
struct NimStringDesc {
  TGenericSeq Sup;
NIM_CHAR data[SEQ_DECL_SIZE];
};
typedef N_CDECL_PTR(void*, tyProc__uQWqJp3WAx8fOY1h9aCwjIg) (void* s, void* a, void* k);
typedef N_NIMCALL_PTR(void*, tyProc__iv6n7tcGawU401muvntJ9cA) (void* aX60gensym90390240_, void* kwgX60gensym90390241_);
typedef NCSTRING tyArray__jieoU9cfWs1Krn17l9aYsDyg[2];
struct RootObj {
TNimType* m_type;
};
struct Exception {
  RootObj Sup;
Exception* parent;
NCSTRING name;
NimStringDesc* message;
tySequence__uB9b75OUPRENsBAu4AnoePA* trace;
Exception* up;
};
typedef long tyArray__TcvIiMAJvcwzNLsZkfnFnQ[25];
struct TSafePoint {
TSafePoint* prev;
NI status;
jmp_buf context;
};
struct tyObject_PyObjectObj__aD5pkFWInXrZXinZ42cDEg {
NI ob_refcnt;
void* ob_type;
};
typedef N_CDECL_PTR(void*, tyProc__SsjMo29bx9bP5kwe2xgM3Scg) (NCSTRING f, ...);
typedef N_CDECL_PTR(void*, tyProc__4wJmT85lsn175X0dPNQv7w) (NI sz);
typedef N_CDECL_PTR(NI, tyProc__YRQqZC12s3573tRGP8MV3g) (void* f);
typedef N_CDECL_PTR(void*, tyProc__oPIasAghCTvCKmvkMeB1xQ) (void* f, NI i);
typedef N_CDECL_PTR(int, tyProc__6slETyyIDJuDOSqkO0hUXA) (void* f, NI i, void* v);
typedef N_CDECL_PTR(int, tyProc__tgpXIILGoVcO9bvYnz9azTVQ) (tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g* f);
typedef N_CDECL_PTR(void*, tyProc__eYT4U6bGFqFBUxk9b15mfOA) (tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g* f, void* a, void* b);
typedef N_CDECL_PTR(int, tyProc__T08W9bgbY4bOv2q64h6irpw) (void* m, NCSTRING n, void* o);
typedef N_CDECL_PTR(int, tyProc__fbYpjfe38x3ujjAmVRbI1Q) (void* o);
typedef N_CDECL_PTR(void*, tyProc__YezmFzxOOyM9cb11Eoq1Elg) (void* o, NCSTRING name);
typedef N_CDECL_PTR(void*, tyProc__jvPpjMAkI9bwM1B9apOphnlA) (void* o);
typedef N_CDECL_PTR(void*, tyProc__VQ1ysQk017myXMGb79cPTVw) (void* o, void* k);
typedef N_CDECL_PTR(int, tyProc__7LMjBc4zOHVIsNdulNv7QQ) (void* o, void* k, void* v);
typedef N_CDECL_PTR(int, tyProc__eoRP3F9aLT3mtHj6OkcMSyQ) (void* a, void* b, int op);
typedef N_CDECL_PTR(int, tyProc__8hR9arLDkUs9ag3Pt9bWtjfsg) (void* o, tyObject_RawPyBuffer__0qyRdSZKtLACJ1u4qMMP2w* b, int flags);
typedef N_CDECL_PTR(void, tyProc__vFvpnKOere9bRFN9czzMRlTA) (tyObject_RawPyBuffer__0qyRdSZKtLACJ1u4qMMP2w* b);
typedef N_CDECL_PTR(void*, tyProc__BZ6N5NNdHcK05FTDxQbEWw) (NCSTRING name, void* base, void* dict);
typedef N_CDECL_PTR(NI64, tyProc__mIlNZ9aGaphVJCyIIofK8mg) (void* l);
typedef N_CDECL_PTR(double, tyProc__2su9b9chqHYibM7sMkbSaSkA) (void* l);
typedef N_CDECL_PTR(void*, tyProc__Fc4ZUx59aQs10dLxeMQ50mw) (long v);
typedef N_CDECL_PTR(int, tyProc__i2exZ7Vtp648U9crOFcq9beQ) (tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g* t1, tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g* t2);
struct tyObject_Complex__zWadV1X9aMO7qS9bsQFB0JFA {
NF re;
NF im;
};
typedef N_CDECL_PTR(tyObject_Complex__zWadV1X9aMO7qS9bsQFB0JFA, tyProc__N1A5ZvDSgO9c9aRXmVqfn9bAw) (void* op);
typedef N_CDECL_PTR(int, tyProc__3FKLKFzOaK7FD6dRLWM6Jw) (void* o, NIM_CHAR** s, NI* len);
typedef N_CDECL_PTR(void*, tyProc__YDKrw1adv61oVQkQhbYyaA) (NCSTRING s);
typedef N_CDECL_PTR(int, tyProc__B2MjSeo07a72ynTQRVYFKw) (void* o, NCSTRING s);
typedef N_CDECL_PTR(NCSTRING, tyProc__p1X2BwWx9a3wsChhykvf29aA) (void* o);
typedef N_CDECL_PTR(void*, tyProc__NzboHqZVJcbdtVGYrOosXQ) (void);
typedef N_CDECL_PTR(int, tyProc__MTei9bsKjha0o1cISO9aLMDg) (void* o, void* k);
typedef N_NIMCALL_PTR(void, tyProc__4SVlZZPmetqBimNsH9cHcOA) (void* o);
typedef N_CDECL_PTR(void, tyProc__ln4kdL5W9bbX4a1xl8nnVXQ) (void);
typedef N_CDECL_PTR(void, tyProc__WYY8i0I79agBofnUcEGCfig) (void* o, NCSTRING s);
typedef N_CDECL_PTR(void, tyProc__32w2ZypAyMWuajvi2Jt79cg) (void* o);
typedef N_CDECL_PTR(void*, tyProc__jcEovQ2rZUNUsYxohT50Ug) (void* p, NCSTRING name, tyProc__32w2ZypAyMWuajvi2Jt79cg destr);
typedef N_CDECL_PTR(void*, tyProc__9b2qzlf3LCKK0JvThQT1atg) (tyObject_PyMethodDef__9aWi1PsmvCuTKIYDHHnhfcw* md, void* self, void* module);
typedef N_CDECL_PTR(void, tyProc__U0oVFt576Ze44Q9a3eZc5wg) (void** ptype, void** pvalue, void** ptraceback);
struct tyObject_PyLibcolonObjectType___bTw708kK89b8Vj9cmSu9a4zig {
void* module;
tyProc__SsjMo29bx9bP5kwe2xgM3Scg Py_BuildValue;
tyProc__4wJmT85lsn175X0dPNQv7w PyTuple_New;
tyProc__YRQqZC12s3573tRGP8MV3g PyTuple_Size;
tyProc__oPIasAghCTvCKmvkMeB1xQ PyTuple_GetItem;
tyProc__6slETyyIDJuDOSqkO0hUXA PyTuple_SetItem;
void* Py_None;
tyProc__tgpXIILGoVcO9bvYnz9azTVQ PyType_Ready;
tyProc__eYT4U6bGFqFBUxk9b15mfOA PyType_GenericNew;
tyProc__T08W9bgbY4bOv2q64h6irpw PyModule_AddObject;
tyProc__4wJmT85lsn175X0dPNQv7w PyList_New;
tyProc__YRQqZC12s3573tRGP8MV3g PyList_Size;
tyProc__oPIasAghCTvCKmvkMeB1xQ PyList_GetItem;
tyProc__6slETyyIDJuDOSqkO0hUXA PyList_SetItem;
tyProc__uQWqJp3WAx8fOY1h9aCwjIg PyObject_Call;
tyProc__fbYpjfe38x3ujjAmVRbI1Q PyObject_IsTrue;
tyProc__YezmFzxOOyM9cb11Eoq1Elg PyObject_GetAttrString;
tyProc__T08W9bgbY4bOv2q64h6irpw PyObject_SetAttrString;
tyProc__jvPpjMAkI9bwM1B9apOphnlA PyObject_Dir;
tyProc__jvPpjMAkI9bwM1B9apOphnlA PyObject_Str;
tyProc__jvPpjMAkI9bwM1B9apOphnlA PyObject_GetIter;
tyProc__VQ1ysQk017myXMGb79cPTVw PyObject_GetItem;
tyProc__7LMjBc4zOHVIsNdulNv7QQ PyObject_SetItem;
tyProc__eoRP3F9aLT3mtHj6OkcMSyQ PyObject_RichCompareBool;
tyProc__8hR9arLDkUs9ag3Pt9bWtjfsg PyObject_GetBuffer;
tyProc__vFvpnKOere9bRFN9czzMRlTA PyBuffer_Release;
tyProc__BZ6N5NNdHcK05FTDxQbEWw PyErr_NewException;
tyProc__jvPpjMAkI9bwM1B9apOphnlA PyIter_Next;
tyProc__mIlNZ9aGaphVJCyIIofK8mg PyLong_AsLongLong;
tyProc__2su9b9chqHYibM7sMkbSaSkA PyFloat_AsDouble;
tyProc__Fc4ZUx59aQs10dLxeMQ50mw PyBool_FromLong;
tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g* PyBool_Type;
tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g* PyFloat_Type;
tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g* PyComplex_Type;
tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g* PyCapsule_Type;
tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g* PyTuple_Type;
tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g* PyList_Type;
tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g* PyBytes_Type;
tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g* PyUnicode_Type;
tyProc__i2exZ7Vtp648U9crOFcq9beQ PyType_IsSubtype;
tyProc__N1A5ZvDSgO9c9aRXmVqfn9bAw PyComplex_AsCComplex;
tyProc__2su9b9chqHYibM7sMkbSaSkA PyComplex_RealAsDouble;
tyProc__2su9b9chqHYibM7sMkbSaSkA PyComplex_ImagAsDouble;
tyProc__jvPpjMAkI9bwM1B9apOphnlA PyUnicode_AsUTF8String;
tyProc__3FKLKFzOaK7FD6dRLWM6Jw PyBytes_AsStringAndSize;
tyProc__YDKrw1adv61oVQkQhbYyaA PyUnicode_FromString;
tyProc__B2MjSeo07a72ynTQRVYFKw PyUnicode_CompareWithASCIIString;
tyProc__p1X2BwWx9a3wsChhykvf29aA PyString_AsString;
tyObject_PyTypeObject3Obj__cRsC9bGvH9bX6A9aVx8UB6I5g* PyDict_Type;
tyProc__NzboHqZVJcbdtVGYrOosXQ PyDict_New;
tyProc__YRQqZC12s3573tRGP8MV3g PyDict_Size;
tyProc__YezmFzxOOyM9cb11Eoq1Elg PyDict_GetItemString;
tyProc__T08W9bgbY4bOv2q64h6irpw PyDict_SetItemString;
tyProc__VQ1ysQk017myXMGb79cPTVw PyDict_GetItem;
tyProc__7LMjBc4zOHVIsNdulNv7QQ PyDict_SetItem;
tyProc__jvPpjMAkI9bwM1B9apOphnlA PyDict_Keys;
tyProc__jvPpjMAkI9bwM1B9apOphnlA PyDict_Values;
tyProc__MTei9bsKjha0o1cISO9aLMDg PyDict_Contains;
tyProc__4SVlZZPmetqBimNsH9cHcOA PyDealloc;
tyProc__ln4kdL5W9bbX4a1xl8nnVXQ PyErr_Clear;
tyProc__WYY8i0I79agBofnUcEGCfig PyErr_SetString;
tyProc__NzboHqZVJcbdtVGYrOosXQ PyErr_Occurred;
void* PyExc_TypeError;
tyProc__jcEovQ2rZUNUsYxohT50Ug PyCapsule_New;
tyProc__YezmFzxOOyM9cb11Eoq1Elg PyCapsule_GetPointer;
tyProc__YDKrw1adv61oVQkQhbYyaA PyImport_ImportModule;
tyProc__NzboHqZVJcbdtVGYrOosXQ PyEval_GetBuiltins;
tyProc__NzboHqZVJcbdtVGYrOosXQ PyEval_GetGlobals;
tyProc__NzboHqZVJcbdtVGYrOosXQ PyEval_GetLocals;
tyProc__9b2qzlf3LCKK0JvThQT1atg PyCFunction_NewEx;
NI pythonVersion;
tyProc__U0oVFt576Ze44Q9a3eZc5wg PyErr_Fetch;
tyProc__U0oVFt576Ze44Q9a3eZc5wg PyErr_NormalizeException;
tyProc__MTei9bsKjha0o1cISO9aLMDg PyErr_GivenExceptionMatches;
void* PyExc_BaseException;
void* PyExc_Exception;
void* PyExc_ArithmeticError;
void* PyExc_FloatingPointError;
void* PyExc_OverflowError;
void* PyExc_ZeroDivisionError;
void* PyExc_AssertionError;
void* PyExc_OSError;
void* PyExc_IOError;
void* PyExc_ValueError;
void* PyExc_EOFError;
void* PyExc_MemoryError;
void* PyExc_IndexError;
void* PyExc_KeyError;
void* NimPyException;
};
typedef NU8 tySet_tyEnum_TSandboxFlag__JyPEhkAmDAldmLHNNrLR0A;
struct tyObject_PyMethodDef__9aWi1PsmvCuTKIYDHHnhfcw {
NCSTRING ml_name;
tyProc__uQWqJp3WAx8fOY1h9aCwjIg ml_meth;
int ml_flags;
NCSTRING ml_doc;
};
struct tyObject_PyTypeDesc__BKCcJxogshNojOoN23Qfbg {
tyObject_PyModuleDesc__gBC8z6Ez5xj3dXoP0ylCRA* module;
NCSTRING name;
NCSTRING doc;
NimStringDesc* fullName;
tyProc__eYT4U6bGFqFBUxk9b15mfOA newFunc;
tySequence__E2XyP5e7Jr9aMpJMjdz5Tkg* methods;
tySequence__mAI4KvRAgoko9bmrV4QRgaQ* members;
NI origSize;
};
struct tyObject_PyIteratorDesc__3Lh9c29bpC2Iomkl9cQO9cGqEw {
NCSTRING name;
NCSTRING doc;
tyProc__eYT4U6bGFqFBUxk9b15mfOA newFunc;
};
struct tyObject_StackTraceEntry__oLyohQ7O2XOvGnflOss8EA {
NCSTRING procname;
NI line;
NCSTRING filename;
};
struct tyObject_PyMemberDef__WC29aEeHi2Pdy9c4AkllcBTg {
NCSTRING name;
int typ;
NI offset;
int flags;
NCSTRING doc;
};
struct tySequence__sM4lkSb7zS6F7OVMvW9cffQ {
  TGenericSeq Sup;
  NimStringDesc* data[SEQ_DECL_SIZE];
};
struct tySequence__E2XyP5e7Jr9aMpJMjdz5Tkg {
  TGenericSeq Sup;
  tyObject_PyMethodDef__9aWi1PsmvCuTKIYDHHnhfcw data[SEQ_DECL_SIZE];
};
struct tySequence__1Ib9a4sxiw4YCYbDTADLEsg {
  TGenericSeq Sup;
  tyObject_PyTypeDesc__BKCcJxogshNojOoN23Qfbg data[SEQ_DECL_SIZE];
};
struct tySequence__xxWWYOndkW9adiM61bZkvsg {
  TGenericSeq Sup;
  tyObject_PyIteratorDesc__3Lh9c29bpC2Iomkl9cQO9cGqEw data[SEQ_DECL_SIZE];
};
struct tySequence__uB9b75OUPRENsBAu4AnoePA {
  TGenericSeq Sup;
  tyObject_StackTraceEntry__oLyohQ7O2XOvGnflOss8EA data[SEQ_DECL_SIZE];
};
struct tySequence__mAI4KvRAgoko9bmrV4QRgaQ {
  TGenericSeq Sup;
  tyObject_PyMemberDef__WC29aEeHi2Pdy9c4AkllcBTg data[SEQ_DECL_SIZE];
};
N_LIB_PRIVATE N_NIMCALL(void, nimGCvisit)(void* d, NI op);
static N_NIMCALL(void, TM__bvyyApzoWMsTRz6tx00FGg_2)(void);
N_LIB_PRIVATE N_NIMCALL(void, nimRegisterGlobalMarker)(tyProc__T4eqaYlFJYZUv9aG9b1TV0bQ markerProc);
N_LIB_PRIVATE N_NIMCALL(void, initPythonModuleDesc__0f1AKGy9a6FMRjtYbL5nSQg)(tyObject_PyModuleDesc__gBC8z6Ez5xj3dXoP0ylCRA* m, NCSTRING name, NCSTRING doc);
N_LIB_EXPORT N_CDECL(void, initnim4py)(void);
N_LIB_PRIVATE N_NIMCALL(void, initModule2__QOPr6RYgxP9c8n2lZVbiDwA)(tyObject_PyModuleDesc__gBC8z6Ez5xj3dXoP0ylCRA* m);
N_LIB_EXPORT N_CDECL(void*, PyInit_nim4py)(void);
N_LIB_PRIVATE N_NIMCALL(void*, initModule3__b5gVEAN0cbSksVFIpPmViA)(tyObject_PyModuleDesc__gBC8z6Ez5xj3dXoP0ylCRA* m);
N_LIB_PRIVATE N_NIMCALL(void, registerExportedModule__2aw5dpL5lVZZ9cjH0apWcXA)(NimStringDesc* name, void* initAddr2, void* initAddr3);
N_LIB_PRIVATE N_NIMCALL(void, addMethod__TpUnmhxGlZgxTBTLPiE3nw)(tyObject_PyModuleDesc__gBC8z6Ez5xj3dXoP0ylCRA* m, NCSTRING name, NCSTRING doc, tyProc__uQWqJp3WAx8fOY1h9aCwjIg f);
N_LIB_PRIVATE N_CDECL(void*, nimscriptPy_wrapper__BS9cw0FCpgxUZ8CEP69c7UBg)(void* selfX60gensym90390237_, void* args, void* kwargs);
static N_INLINE(void, updateStackBottom__FRn3WNsRdbdvfuL6O7x1BQnimpy)(void);
N_LIB_PRIVATE N_NOINLINE(void, nimGC_setStackBottom)(void* theStackBottom);
N_LIB_PRIVATE N_NIMCALL(void, setupForeignThreadGc__amVlU9ajqZ06ujoesRBHcDg_2)(void);
N_LIB_PRIVATE N_NIMCALL(void*, noinline__N80vx60ClNyGM4nya6MU8g)(void* args, void* kwargs);
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, verifyArgs__8sVYJT4zfbIXMNXtJ2cTng)(void* argTuple, void* kwargsDict, NI argsLen, NI argsLenReq, NCSTRING* argNames, NI argNamesLen_0, NimStringDesc* funcName);
N_LIB_PRIVATE N_NIMCALL(void, parseArg__icg9aGIbXA4DEIGHwq7rmAA)(void* argTuple, void* kwargsDict, NI argIdx, NCSTRING argName, NimStringDesc** result);
N_LIB_PRIVATE N_NIMCALL(void, parseArg__9b6ttEhK1WRqorza3JVW9cJw)(void* argTuple, void* kwargsDict, NI argIdx, NCSTRING argName, tySequence__sM4lkSb7zS6F7OVMvW9cffQ** result);
static N_INLINE(void, pushSafePoint)(TSafePoint* s);
static N_INLINE(void*, nimValueToPy__6Tvzvi9bEckxJJClCQCOiEAnimpy)(void);
static N_INLINE(void*, newPyNone__6Tvzvi9bEckxJJClCQCOiEA_2nimpy)(void);
static N_INLINE(void, incRef__CnqcscfOCAX2jCHv3dRPDwpy_utils)(void* p);
static N_INLINE(tyObject_PyObjectObj__aD5pkFWInXrZXinZ42cDEg*, to__4gaYCHYBaCTIs6wfSrqsEApy_lib)(void* p);
N_LIB_PRIVATE N_NIMCALL(void, nimscript__qgujufj0gEfJl9a6yUKqB1w)(NimStringDesc* script, tySequence__sM4lkSb7zS6F7OVMvW9cffQ* nim_stdlib_paths);
N_LIB_PRIVATE N_NIMCALL(tyObject_InterpretercolonObjectType___P52MELrsYCwBeooqRNfjVA*, createInterpreter__JxjZwy9bfJI09btLVEDQd2KQ)(NimStringDesc* scriptName, NimStringDesc** searchPaths, NI searchPathsLen_0, tySet_tyEnum_TSandboxFlag__JyPEhkAmDAldmLHNNrLR0A flags);
N_LIB_PRIVATE N_NIMCALL(void, evalScript__4xNUzcz2JvcblqszY4dB2A)(tyObject_InterpretercolonObjectType___P52MELrsYCwBeooqRNfjVA* i, tyObject_TLLStream__a5oZYQ9aTktYME2449ayEi6g* scriptStream);
N_LIB_PRIVATE N_NIMCALL(void, destroyInterpreter__7l8n82kSsf9aZx1TpDojCzQ)(tyObject_InterpretercolonObjectType___P52MELrsYCwBeooqRNfjVA* i);
static N_INLINE(void, popSafePoint)(void);
N_LIB_PRIVATE N_NIMCALL(NIM_BOOL, isObj)(TNimType* obj, TNimType* subclass);
static N_INLINE(Exception*, nimBorrowCurrentException)(void);
static N_INLINE(Exception*, getCurrentException)(void);
N_LIB_PRIVATE N_NIMCALL(void*, pythonException__Zl8uxcjgHaQZB15tcqXlTA)(Exception* e);
static N_INLINE(void, popCurrentException)(void);
N_LIB_PRIVATE N_NIMCALL(void, reraiseException)(void);
static N_INLINE(void, initStackBottomWith)(void* locals);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_ioDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, systemDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, systemInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_timesDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_timesInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_osDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_osInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_ropesDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_tablesDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_lineinfosDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_strtabsDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_setsDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_platformDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_prefixmatchesDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_terminalDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_terminalInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_optionsDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_identsDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_astDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_intsetsDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_incrementalDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_btreesDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_md5DatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_modulegraphsDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_llstreamDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_nimlexbaseDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_lexerDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_parserDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_rendererDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_syntaxesDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_reorderDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_typesDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_streamsDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_lexbaseDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, stdlib_parsejsonDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_vmdefDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_semdataDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_sigmatchDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_guardsDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_transfDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_vmDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_patternsDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_semDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, compiler_nimevalDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, nimpy_py_typesDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, nimpy_py_libDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, nimpy_py_libInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, nimpy_nimpyDatInit000)(void);
N_LIB_PRIVATE N_NIMCALL(void, NimMainModule)(void);
extern TNimType NTI__gBC8z6Ez5xj3dXoP0ylCRA_;
STRING_LITERAL(TM__bvyyApzoWMsTRz6tx00FGg_3, "nim4py", 6);
static NIM_CONST tyArray__jieoU9cfWs1Krn17l9aYsDyg TM__bvyyApzoWMsTRz6tx00FGg_4 = {"script",
"nim_stdlib_paths"}
;
STRING_LITERAL(TM__bvyyApzoWMsTRz6tx00FGg_5, "nimscript", 9);
extern TNimType NTI__XEycrCsme5C8CVWAYEcdBQ_;
N_LIB_PRIVATE tyObject_PyModuleDesc__gBC8z6Ez5xj3dXoP0ylCRA gPythonLocalModuleDesc__U8f9bnkhs9ak9ca9c8BBya7n3w;
extern NIM_THREADVAR NIM_BOOL gcInited__uuy3PWTwb5gov9ao9bXJYBPg;
extern NIM_THREADVAR NIM_BOOL gcInited__uuy3PWTwb5gov9ao9bXJYBPg;
extern NIM_THREADVAR TSafePoint* excHandler__rqLlY5bs9atDw2OXYqJEn5g;
extern NIM_THREADVAR TSafePoint* excHandler__rqLlY5bs9atDw2OXYqJEn5g;
extern NU pyObjectStartOffset__g20dGCi2MffsHqmxIpqX7Q;
extern tyObject_PyLibcolonObjectType___bTw708kK89b8Vj9cmSu9a4zig* pyLib__nxKBiAukGMNwnUq9bpn9adyw;
extern NIM_THREADVAR TSafePoint* excHandler__rqLlY5bs9atDw2OXYqJEn5g;
extern NIM_THREADVAR TSafePoint* excHandler__rqLlY5bs9atDw2OXYqJEn5g;
extern NIM_THREADVAR Exception* currException__9bVPeDJlYTi9bQApZpfH8wjg;
extern NIM_THREADVAR Exception* currException__9bVPeDJlYTi9bQApZpfH8wjg;
extern NIM_THREADVAR Exception* currException__9bVPeDJlYTi9bQApZpfH8wjg;
extern NIM_THREADVAR Exception* currException__9bVPeDJlYTi9bQApZpfH8wjg;
static N_NIMCALL(void, TM__bvyyApzoWMsTRz6tx00FGg_2)(void) {
	nimGCvisit((void*)gPythonLocalModuleDesc__U8f9bnkhs9ak9ca9c8BBya7n3w.methods, 0);
	nimGCvisit((void*)gPythonLocalModuleDesc__U8f9bnkhs9ak9ca9c8BBya7n3w.types, 0);
	nimGCvisit((void*)gPythonLocalModuleDesc__U8f9bnkhs9ak9ca9c8BBya7n3w.iterators, 0);
}
N_LIB_EXPORT N_CDECL(void, initnim4py)(void) {
	initModule2__QOPr6RYgxP9c8n2lZVbiDwA((&gPythonLocalModuleDesc__U8f9bnkhs9ak9ca9c8BBya7n3w));
}
N_LIB_EXPORT N_CDECL(void*, PyInit_nim4py)(void) {
	void* result;
	result = (void*)0;
	result = initModule3__b5gVEAN0cbSksVFIpPmViA((&gPythonLocalModuleDesc__U8f9bnkhs9ak9ca9c8BBya7n3w));
	return result;
}
static N_INLINE(void, updateStackBottom__FRn3WNsRdbdvfuL6O7x1BQnimpy)(void) {
	NI volatile a;
	a = (NI)0;
	nimGC_setStackBottom(((void*) (((NU) (ptrdiff_t) ((&a))))));
	{
		if (!!(gcInited__uuy3PWTwb5gov9ao9bXJYBPg)) goto LA3_;
		gcInited__uuy3PWTwb5gov9ao9bXJYBPg = NIM_TRUE;
		setupForeignThreadGc__amVlU9ajqZ06ujoesRBHcDg_2();
	}
	LA3_: ;
}
static N_INLINE(void, pushSafePoint)(TSafePoint* s) {
	(*s).prev = excHandler__rqLlY5bs9atDw2OXYqJEn5g;
	excHandler__rqLlY5bs9atDw2OXYqJEn5g = s;
}
static N_INLINE(tyObject_PyObjectObj__aD5pkFWInXrZXinZ42cDEg*, to__4gaYCHYBaCTIs6wfSrqsEApy_lib)(void* p) {
	tyObject_PyObjectObj__aD5pkFWInXrZXinZ42cDEg* result;
	result = (tyObject_PyObjectObj__aD5pkFWInXrZXinZ42cDEg*)0;
	result = ((tyObject_PyObjectObj__aD5pkFWInXrZXinZ42cDEg*) ((NU)((NU64)(((NU) (ptrdiff_t) (p))) + (NU64)(pyObjectStartOffset__g20dGCi2MffsHqmxIpqX7Q))));
	return result;
}
static N_INLINE(void, incRef__CnqcscfOCAX2jCHv3dRPDwpy_utils)(void* p) {
	tyObject_PyObjectObj__aD5pkFWInXrZXinZ42cDEg* T1_;
	T1_ = (tyObject_PyObjectObj__aD5pkFWInXrZXinZ42cDEg*)0;
	T1_ = to__4gaYCHYBaCTIs6wfSrqsEApy_lib(p);
	(*T1_).ob_refcnt += ((NI) 1);
}
static N_INLINE(void*, newPyNone__6Tvzvi9bEckxJJClCQCOiEA_2nimpy)(void) {
	void* result;
	result = (void*)0;
	incRef__CnqcscfOCAX2jCHv3dRPDwpy_utils((*pyLib__nxKBiAukGMNwnUq9bpn9adyw).Py_None);
	result = (*pyLib__nxKBiAukGMNwnUq9bpn9adyw).Py_None;
	return result;
}
static N_INLINE(void*, nimValueToPy__6Tvzvi9bEckxJJClCQCOiEAnimpy)(void) {
	void* result;
	result = (void*)0;
	result = newPyNone__6Tvzvi9bEckxJJClCQCOiEA_2nimpy();
	return result;
}
N_LIB_PRIVATE N_NIMCALL(void, nimscript__qgujufj0gEfJl9a6yUKqB1w)(NimStringDesc* script, tySequence__sM4lkSb7zS6F7OVMvW9cffQ* nim_stdlib_paths) {
	tyObject_InterpretercolonObjectType___P52MELrsYCwBeooqRNfjVA* interpreter;
	interpreter = createInterpreter__JxjZwy9bfJI09btLVEDQd2KQ(script, nim_stdlib_paths->data, (nim_stdlib_paths ? nim_stdlib_paths->Sup.len : 0), 0);
	evalScript__4xNUzcz2JvcblqszY4dB2A(interpreter, NIM_NIL);
	destroyInterpreter__7l8n82kSsf9aZx1TpDojCzQ(interpreter);
}
static N_INLINE(void, popSafePoint)(void) {
	excHandler__rqLlY5bs9atDw2OXYqJEn5g = (*excHandler__rqLlY5bs9atDw2OXYqJEn5g).prev;
}
static N_INLINE(Exception*, nimBorrowCurrentException)(void) {
	Exception* result;
	result = (Exception*)0;
	result = currException__9bVPeDJlYTi9bQApZpfH8wjg;
	return result;
}
static N_INLINE(Exception*, getCurrentException)(void) {
	Exception* result;
	result = (Exception*)0;
	result = currException__9bVPeDJlYTi9bQApZpfH8wjg;
	return result;
}
static N_INLINE(void, popCurrentException)(void) {
	currException__9bVPeDJlYTi9bQApZpfH8wjg = (*currException__9bVPeDJlYTi9bQApZpfH8wjg).up;
}
N_LIB_PRIVATE N_NIMCALL(void*, noinline__N80vx60ClNyGM4nya6MU8g)(void* args, void* kwargs) {
	void* result;
	NimStringDesc* arg0script;
	tySequence__sM4lkSb7zS6F7OVMvW9cffQ* arg1nim_stdlib_paths;
	TSafePoint TM__bvyyApzoWMsTRz6tx00FGg_6;
{	result = (void*)0;
	{
		NIM_BOOL T3_;
		T3_ = (NIM_BOOL)0;
		T3_ = verifyArgs__8sVYJT4zfbIXMNXtJ2cTng(args, kwargs, ((NI) 2), ((NI) 2), TM__bvyyApzoWMsTRz6tx00FGg_4, 2, ((NimStringDesc*) &TM__bvyyApzoWMsTRz6tx00FGg_5));
		if (!!(T3_)) goto LA4_;
		result = ((void*) (NIM_NIL));
		goto BeforeRet_;
	}
	LA4_: ;
	arg0script = (NimStringDesc*)0;
	arg1nim_stdlib_paths = (tySequence__sM4lkSb7zS6F7OVMvW9cffQ*)0;
	parseArg__icg9aGIbXA4DEIGHwq7rmAA(args, kwargs, ((NI) 0), "script", (&arg0script));
	parseArg__9b6ttEhK1WRqorza3JVW9cJw(args, kwargs, ((NI) 1), "nim_stdlib_paths", (&arg1nim_stdlib_paths));
	pushSafePoint(&TM__bvyyApzoWMsTRz6tx00FGg_6);
	TM__bvyyApzoWMsTRz6tx00FGg_6.status = setjmp(TM__bvyyApzoWMsTRz6tx00FGg_6.context);
	if (TM__bvyyApzoWMsTRz6tx00FGg_6.status == 0) {
		nimscript__qgujufj0gEfJl9a6yUKqB1w(arg0script, arg1nim_stdlib_paths);
		result = nimValueToPy__6Tvzvi9bEckxJJClCQCOiEAnimpy();
		popSafePoint();
	}
	else {
		popSafePoint();
		if (isObj(nimBorrowCurrentException()->Sup.m_type, (&NTI__XEycrCsme5C8CVWAYEcdBQ_))) {
			Exception* eX60gensym90390238_;
			TM__bvyyApzoWMsTRz6tx00FGg_6.status = 0;
			eX60gensym90390238_ = getCurrentException();
			result = pythonException__Zl8uxcjgHaQZB15tcqXlTA(eX60gensym90390238_);
			popCurrentException();
		}
	}
	if (TM__bvyyApzoWMsTRz6tx00FGg_6.status != 0) reraiseException();
	}BeforeRet_: ;
	return result;
}
N_LIB_PRIVATE N_CDECL(void*, nimscriptPy_wrapper__BS9cw0FCpgxUZ8CEP69c7UBg)(void* selfX60gensym90390237_, void* args, void* kwargs) {
	void* result;
	tyProc__iv6n7tcGawU401muvntJ9cA volatile pX60gensym90390239_;
	result = (void*)0;
	updateStackBottom__FRn3WNsRdbdvfuL6O7x1BQnimpy();
	pX60gensym90390239_ = noinline__N80vx60ClNyGM4nya6MU8g;
	result = pX60gensym90390239_(args, kwargs);
	return result;
}
static N_INLINE(void, initStackBottomWith)(void* locals) {
	nimGC_setStackBottom(locals);
}

N_LIB_PRIVATE void PreMainInner(void) {
	stdlib_timesInit000();
	stdlib_osInit000();
	stdlib_terminalInit000();
	nimpy_py_libInit000();
}

N_LIB_PRIVATE int cmdCount;
N_LIB_PRIVATE char** cmdLine;
N_LIB_PRIVATE char** gEnv;
N_LIB_PRIVATE void PreMain(void) {
	void (*volatile inner)(void);
	inner = PreMainInner;
	stdlib_ioDatInit000();
	systemDatInit000();
	initStackBottomWith((void *)&inner);
	systemInit000();
	stdlib_timesDatInit000();
	stdlib_osDatInit000();
	compiler_ropesDatInit000();
	stdlib_tablesDatInit000();
	compiler_lineinfosDatInit000();
	stdlib_strtabsDatInit000();
	stdlib_setsDatInit000();
	compiler_platformDatInit000();
	compiler_prefixmatchesDatInit000();
	stdlib_terminalDatInit000();
	compiler_optionsDatInit000();
	compiler_identsDatInit000();
	compiler_astDatInit000();
	stdlib_intsetsDatInit000();
	compiler_incrementalDatInit000();
	compiler_btreesDatInit000();
	stdlib_md5DatInit000();
	compiler_modulegraphsDatInit000();
	compiler_llstreamDatInit000();
	compiler_nimlexbaseDatInit000();
	compiler_lexerDatInit000();
	compiler_parserDatInit000();
	compiler_rendererDatInit000();
	compiler_syntaxesDatInit000();
	compiler_reorderDatInit000();
	compiler_typesDatInit000();
	stdlib_streamsDatInit000();
	stdlib_lexbaseDatInit000();
	stdlib_parsejsonDatInit000();
	compiler_vmdefDatInit000();
	compiler_semdataDatInit000();
	compiler_sigmatchDatInit000();
	compiler_guardsDatInit000();
	compiler_transfDatInit000();
	compiler_vmDatInit000();
	compiler_patternsDatInit000();
	compiler_semDatInit000();
	compiler_nimevalDatInit000();
	nimpy_py_typesDatInit000();
	nimpy_py_libDatInit000();
	nimpy_nimpyDatInit000();
	(*inner)();
}

N_LIB_PRIVATE N_CDECL(void, NimMainInner)(void) {
	NimMainModule();
}

N_LIB_EXPORT N_CDECL(void, NimMain)(void) {
	void (*volatile inner)(void);
	PreMain();
	inner = NimMainInner;
	initStackBottomWith((void *)&inner);
	(*inner)();
}

N_LIB_PRIVATE void NIM_POSIX_INIT NimMainInit(void) {
	NimMain();
}

N_LIB_PRIVATE N_NIMCALL(void, NimMainModule)(void) {
{

	nimRegisterGlobalMarker(TM__bvyyApzoWMsTRz6tx00FGg_2);

	initPythonModuleDesc__0f1AKGy9a6FMRjtYbL5nSQg((&gPythonLocalModuleDesc__U8f9bnkhs9ak9ca9c8BBya7n3w), "nim4py", "");
	registerExportedModule__2aw5dpL5lVZZ9cjH0apWcXA(((NimStringDesc*) &TM__bvyyApzoWMsTRz6tx00FGg_3), ((void*) (initnim4py)), ((void*) (PyInit_nim4py)));
	addMethod__TpUnmhxGlZgxTBTLPiE3nw((&gPythonLocalModuleDesc__U8f9bnkhs9ak9ca9c8BBya7n3w), "nimscript", "NimScript Interpreter for Python, see https://nim-lang.github.i"
"o/Nim/nims.html\012* ``func nimscript(script: string; nim_stdlib_pa"
"ths: seq[string])``", nimscriptPy_wrapper__BS9cw0FCpgxUZ8CEP69c7UBg);
}
}

