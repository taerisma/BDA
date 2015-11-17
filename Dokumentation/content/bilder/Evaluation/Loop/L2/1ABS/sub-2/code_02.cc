#include <Python.h>
#include <time.h>
#include <pthread.h>

#if 0
#ifndef __extern_always_inline 
#define __extern_always_inline inline
#endif
#endif

#ifndef __GETTIMEOFDAY_C
#define __GETTIMEOFDAY_C


#if defined(_MSC_VER) || defined(_WINDOWS_)
   #include <time.h>
   #if !defined(_WINSOCK2API_) && !defined(_WINSOCKAPI_)
         struct timeval 
         {
            long tv_sec;
            long tv_usec;
         };
   #endif 
#else
   #include <sys/time.h>
#endif 
#if defined(_MSC_VER) || defined(_WINDOWS_)
   int gettimeofday(struct timeval* tv,void *dummy) 
   {
      union {
         long long ns100;
         FILETIME ft;
      } now;
     
      GetSystemTimeAsFileTime (&now.ft);
      tv->tv_usec = (long) ((now.ns100 / 10LL) % 1000000LL);
      tv->tv_sec = (long) ((now.ns100 - 116444736000000000LL) / 10000000LL);
     return (0);
   }
#endif
#endif /* __GETTIMEOFDAY_C */
#include <list>
PyThreadState *pythread=0;
int allow_threads=1;
int do_cpuclock=1;
pthread_mutex_t py_mutex;
#define Py_MY_BEGIN_ALLOW_THREADS { if(allow_threads && !pythread) pythread= PyEval_SaveThread();  }
#define Py_MY_END_ALLOW_THREADS { if(allow_threads && pythread) { PyEval_RestoreThread(pythread);}  pythread = 0; }
#define Py_MY_BEGIN_ALLOW_THREADS_LOCKED { if(allow_threads && !pythread) { pythread= PyEval_SaveThread(); }  pthread_mutex_unlock(&py_mutex); }
#define Py_MY_END_ALLOW_THREADS_LOCKED { pthread_mutex_lock(&py_mutex); if(allow_threads && pythread) { PyEval_RestoreThread(pythread);}  pythread = 0; }
#define rdtsc(low,high) __asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high))
#define CPUCLOCK(x) { if( do_cpuclock) { unsigned int h=0,l=0; rdtsc(l,h); x = (long long)l + (((long long)h)<<32); } else x=0;   }
#ifdef MS_WIN32
static PyObject *__dict,*__none,*__se,*__ie;
static _typeobject *__int;

#define PyRun(_s) PyRun_String(_s,Py_eval_input,__dict,__dict)

#undef Py_None
#undef PyCObject_Check

#define PyCObject_Check(a)  (1)
#define Py_None             __none
#define PyInt_Type          (*(__int))
#define PyExc_StandardError __se
#define PyExc_IndexError    __ie

static void init_dict(void) {
 PyObject *m;
 m      = PyImport_AddModule("__main__");
 __dict = PyModule_GetDict(m);
 __none =   PyRun("None");
 __int  =    PyRun("1") -> ob_type ;
 __se   = PyRun("StandardError");
 __ie   = PyRun("IndexError");
}
#endif
#include <Numeric/arrayobject.h>

#ifndef MS_WIN64
#undef long64
#define long64 long
#endif
  #include <immintrin.h>
  typedef float M  __attribute__ ((__vector_size__ (32)));
  #include <Windows.h>
  
static void yee_0_0_0_0(int n,int n0,float *f,float *c,float *dummy,float *norm)               {
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r20 = _mm256_load_ps((const float *)(norm+0LL));
  r0 = _mm256_load_ps((const float *)(c+0LL));
  r20 *=  r0;
  r21 = _mm256_load_ps((const float *)(norm+8LL));
  r0 = _mm256_load_ps((const float *)(c+8LL));
  r21 *=  r0;
  r22 = _mm256_load_ps((const float *)(norm+16LL));
  r0 = _mm256_load_ps((const float *)(c+16LL));
  r22 *=  r0;
  r23 = _mm256_load_ps((const float *)(norm+24LL));
  r0 = _mm256_load_ps((const float *)(c+24LL));
  r23 *=  r0;
  r24 = _mm256_load_ps((const float *)(norm+32LL));
  r0 = _mm256_load_ps((const float *)(c+32LL));
  r24 *=  r0;
  r25 = _mm256_load_ps((const float *)(norm+40LL));
  r0 = _mm256_load_ps((const float *)(c+40LL));
  r25 *=  r0;
  {

  float * p0 = f + 0/8*8,* p1 = c + 0/8*0;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 0) {
  
  r0 = _mm256_load_ps((const float *)(p0+588336LL));   /* OPT */  r27 = r0;
  r1 = _mm256_load_ps((const float *)(p0+588392LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+294168LL));   /* OPT */  r41 = r2;
  r3 = _mm256_load_ps((const float *)(p0+299936LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+882504LL));
  r6 +=  r0;
  *(M *)(p0+882504LL) = r6;   /* OPT */  r31 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r37 = r0;
  r1 = _mm256_load_ps((const float *)(p0+5768LL));
  r0 -=  r1;
  /* OPT */  r2 = r27;
  /* OPT */  r3 = r27;
  r4 = _mm256_load_ps((const float *)(p0+588344LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1176672LL));
  r6 +=  r0;
  *(M *)(p0+1176672LL) = r6;   /* OPT */  r34 = r6;
  /* OPT */  r0 = r41;
  /* OPT */  r1 = r41;
  r4 = _mm256_load_ps((const float *)(p0+294176LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  r3 = _mm256_load_ps((const float *)(p0+56LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1470840LL));
  r6 +=  r0;
  *(M *)(p0+1470840LL) = r6;   /* OPT */  r30 = r6;
  /* OPT */  r0 = r34;
  /* OPT */  r1 = r34;
  r4 = _mm256_load_ps((const float *)(p0+1176664LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r31;
  r3 = _mm256_load_ps((const float *)(p0+882448LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r27;
  r6 +=  r0;
  *(M *)(p0+588336LL) = r6;
  /* OPT */  r0 = r31;
  r1 = _mm256_load_ps((const float *)(p0+876736LL));
  r0 -=  r1;
  /* OPT */  r2 = r30;
  /* OPT */  r3 = r30;
  r4 = _mm256_load_ps((const float *)(p0+1470832LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r41;
  r6 +=  r0;
  *(M *)(p0+294168LL) = r6;
  /* OPT */  r0 = r30;
  r1 = _mm256_load_ps((const float *)(p0+1470784LL));
  r0 -=  r1;
  /* OPT */  r2 = r34;
  r3 = _mm256_load_ps((const float *)(p0+1170904LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r37;
  r6 +=  r0;
  *(M *)(p0+0LL) = r6;
  
  }}

}

static PyObject * m_0000(PyObject *self, PyObject *args) {
  volatile double        retval=0;
  long           i0,i1;
  PyArrayObject *pa0,*pa1;
  float         *a0,*a1;

  if (!PyArg_ParseTuple(args, "llOO",&i0,&i1,&pa0,&pa1))
     return NULL;

  a0 = (float *)(pa0->data);
  a1 = (float *)(pa1->data);

  long long clmin = 1000000,cl0,cl1;
  for(int i=0;i<i0;i++)
     { 
     CPUCLOCK(cl0);  
     for(int j=0;j<i1;j++)
       { 
         yee_0_0_0_0(56,0,a0,a1,a1,a1);
       } 
     CPUCLOCK(cl1); cl1 -= cl0;  if(cl1 > 0 && cl1 < clmin ) clmin = cl1; 
     } 
  retval = clmin;

  return PyFloat_FromDouble(retval);
}
  
static void yee_0_0_1_1(int n,int n0,float *f,float *c,float *dummy,float *norm)               {
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r20 = _mm256_load_ps((const float *)(norm+0LL));
  r0 = _mm256_load_ps((const float *)(c+0LL));
  r20 *=  r0;
  r21 = _mm256_load_ps((const float *)(norm+8LL));
  r0 = _mm256_load_ps((const float *)(c+8LL));
  r21 *=  r0;
  r22 = _mm256_load_ps((const float *)(norm+16LL));
  r0 = _mm256_load_ps((const float *)(c+16LL));
  r22 *=  r0;
  r23 = _mm256_load_ps((const float *)(norm+24LL));
  r0 = _mm256_load_ps((const float *)(c+24LL));
  r23 *=  r0;
  r24 = _mm256_load_ps((const float *)(norm+32LL));
  r0 = _mm256_load_ps((const float *)(c+32LL));
  r24 *=  r0;
  r25 = _mm256_load_ps((const float *)(norm+40LL));
  r0 = _mm256_load_ps((const float *)(c+40LL));
  r25 *=  r0;
  {

  float * p0 = f + 0/8*8,* p1 = c + 0/8*0;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 0) {
  
  r0 = _mm256_load_ps((const float *)(p0+599872LL));   /* OPT */  r36 = r0;
  r1 = _mm256_load_ps((const float *)(p0+599928LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+299936LL));   /* OPT */  r34 = r2;
  r3 = _mm256_load_ps((const float *)(p0+305704LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+899808LL));
  r6 +=  r0;
  *(M *)(p0+899808LL) = r6;   /* OPT */  r39 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r30 = r0;
  r1 = _mm256_load_ps((const float *)(p0+5768LL));
  r0 -=  r1;
  /* OPT */  r2 = r36;
  /* OPT */  r3 = r36;
  r4 = _mm256_load_ps((const float *)(p0+599880LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1199744LL));
  r6 +=  r0;
  *(M *)(p0+1199744LL) = r6;   /* OPT */  r37 = r6;
  /* OPT */  r0 = r34;
  /* OPT */  r1 = r34;
  r4 = _mm256_load_ps((const float *)(p0+299944LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r30;
  r3 = _mm256_load_ps((const float *)(p0+56LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1499680LL));
  r6 +=  r0;
  *(M *)(p0+1499680LL) = r6;   /* OPT */  r27 = r6;
  /* OPT */  r0 = r37;
  /* OPT */  r1 = r37;
  r4 = _mm256_load_ps((const float *)(p0+1199736LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r39;
  r3 = _mm256_load_ps((const float *)(p0+899752LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r36;
  r6 +=  r0;
  *(M *)(p0+599872LL) = r6;
  /* OPT */  r0 = r39;
  r1 = _mm256_load_ps((const float *)(p0+894040LL));
  r0 -=  r1;
  /* OPT */  r2 = r27;
  /* OPT */  r3 = r27;
  r4 = _mm256_load_ps((const float *)(p0+1499672LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r34;
  r6 +=  r0;
  *(M *)(p0+299936LL) = r6;
  /* OPT */  r0 = r27;
  r1 = _mm256_load_ps((const float *)(p0+1499624LL));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  r3 = _mm256_load_ps((const float *)(p0+1193976LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r30;
  r6 +=  r0;
  *(M *)(p0+0LL) = r6;
  
  }}

}

static PyObject * m_0001(PyObject *self, PyObject *args) {
  volatile double        retval=0;
  long           i0,i1;
  PyArrayObject *pa0,*pa1;
  float         *a0,*a1;

  if (!PyArg_ParseTuple(args, "llOO",&i0,&i1,&pa0,&pa1))
     return NULL;

  a0 = (float *)(pa0->data);
  a1 = (float *)(pa1->data);

  long long clmin = 1000000,cl0,cl1;
  for(int i=0;i<i0;i++)
     { 
     CPUCLOCK(cl0);  
     for(int j=0;j<i1;j++)
       { 
         yee_0_0_1_1(56,0,a0,a1,a1,a1);
       } 
     CPUCLOCK(cl1); cl1 -= cl0;  if(cl1 > 0 && cl1 < clmin ) clmin = cl1; 
     } 
  retval = clmin;

  return PyFloat_FromDouble(retval);
}
  
static void yee_0_1_0_2(int n,int n0,float *f,float *c,float *dummy,float *norm)               {
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r20 = _mm256_load_ps((const float *)(norm+0LL));
  r0 = _mm256_load_ps((const float *)(c+0LL));
  r20 *=  r0;
  r21 = _mm256_load_ps((const float *)(norm+8LL));
  r0 = _mm256_load_ps((const float *)(c+8LL));
  r21 *=  r0;
  r22 = _mm256_load_ps((const float *)(norm+16LL));
  r0 = _mm256_load_ps((const float *)(c+16LL));
  r22 *=  r0;
  r23 = _mm256_load_ps((const float *)(norm+24LL));
  r0 = _mm256_load_ps((const float *)(c+24LL));
  r23 *=  r0;
  r24 = _mm256_load_ps((const float *)(norm+32LL));
  r0 = _mm256_load_ps((const float *)(c+32LL));
  r24 *=  r0;
  r25 = _mm256_load_ps((const float *)(norm+40LL));
  r0 = _mm256_load_ps((const float *)(c+40LL));
  r25 *=  r0;
  {

  float * p0 = f + 0/8*8,* p1 = c + 0/8*0;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 0) {
  
  r0 = _mm256_load_ps((const float *)(p0+594048LL));   /* OPT */  r28 = r0;
  r1 = _mm256_load_ps((const float *)(p0+594104LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+297024LL));   /* OPT */  r42 = r2;
  r3 = _mm256_load_ps((const float *)(p0+302848LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+891072LL));
  r6 +=  r0;
  *(M *)(p0+891072LL) = r6;   /* OPT */  r35 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r38 = r0;
  r1 = _mm256_load_ps((const float *)(p0+5824LL));
  r0 -=  r1;
  /* OPT */  r2 = r28;
  /* OPT */  r3 = r28;
  r4 = _mm256_load_ps((const float *)(p0+594056LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1188096LL));
  r6 +=  r0;
  *(M *)(p0+1188096LL) = r6;   /* OPT */  r33 = r6;
  /* OPT */  r0 = r42;
  /* OPT */  r1 = r42;
  r4 = _mm256_load_ps((const float *)(p0+297032LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r38;
  r3 = _mm256_load_ps((const float *)(p0+56LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1485120LL));
  r6 +=  r0;
  *(M *)(p0+1485120LL) = r6;   /* OPT */  r37 = r6;
  /* OPT */  r0 = r33;
  /* OPT */  r1 = r33;
  r4 = _mm256_load_ps((const float *)(p0+1188088LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  r3 = _mm256_load_ps((const float *)(p0+891016LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r28;
  r6 +=  r0;
  *(M *)(p0+594048LL) = r6;
  /* OPT */  r0 = r35;
  r1 = _mm256_load_ps((const float *)(p0+885248LL));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  /* OPT */  r3 = r37;
  r4 = _mm256_load_ps((const float *)(p0+1485112LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r42;
  r6 +=  r0;
  *(M *)(p0+297024LL) = r6;
  /* OPT */  r0 = r37;
  r1 = _mm256_load_ps((const float *)(p0+1485064LL));
  r0 -=  r1;
  /* OPT */  r2 = r33;
  r3 = _mm256_load_ps((const float *)(p0+1182272LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r38;
  r6 +=  r0;
  *(M *)(p0+0LL) = r6;
  
  }}

}

static PyObject * m_0002(PyObject *self, PyObject *args) {
  volatile double        retval=0;
  long           i0,i1;
  PyArrayObject *pa0,*pa1;
  float         *a0,*a1;

  if (!PyArg_ParseTuple(args, "llOO",&i0,&i1,&pa0,&pa1))
     return NULL;

  a0 = (float *)(pa0->data);
  a1 = (float *)(pa1->data);

  long long clmin = 1000000,cl0,cl1;
  for(int i=0;i<i0;i++)
     { 
     CPUCLOCK(cl0);  
     for(int j=0;j<i1;j++)
       { 
         yee_0_1_0_2(56,0,a0,a1,a1,a1);
       } 
     CPUCLOCK(cl1); cl1 -= cl0;  if(cl1 > 0 && cl1 < clmin ) clmin = cl1; 
     } 
  retval = clmin;

  return PyFloat_FromDouble(retval);
}
  
static void yee_0_1_1_3(int n,int n0,float *f,float *c,float *dummy,float *norm)               {
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r20 = _mm256_load_ps((const float *)(norm+0LL));
  r0 = _mm256_load_ps((const float *)(c+0LL));
  r20 *=  r0;
  r21 = _mm256_load_ps((const float *)(norm+8LL));
  r0 = _mm256_load_ps((const float *)(c+8LL));
  r21 *=  r0;
  r22 = _mm256_load_ps((const float *)(norm+16LL));
  r0 = _mm256_load_ps((const float *)(c+16LL));
  r22 *=  r0;
  r23 = _mm256_load_ps((const float *)(norm+24LL));
  r0 = _mm256_load_ps((const float *)(c+24LL));
  r23 *=  r0;
  r24 = _mm256_load_ps((const float *)(norm+32LL));
  r0 = _mm256_load_ps((const float *)(c+32LL));
  r24 *=  r0;
  r25 = _mm256_load_ps((const float *)(norm+40LL));
  r0 = _mm256_load_ps((const float *)(c+40LL));
  r25 *=  r0;
  {

  float * p0 = f + 0/8*8,* p1 = c + 0/8*0;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 0) {
  
  r0 = _mm256_load_ps((const float *)(p0+605696LL));   /* OPT */  r29 = r0;
  r1 = _mm256_load_ps((const float *)(p0+605752LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+302848LL));   /* OPT */  r43 = r2;
  r3 = _mm256_load_ps((const float *)(p0+308672LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+908544LL));
  r6 +=  r0;
  *(M *)(p0+908544LL) = r6;   /* OPT */  r34 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r38 = r0;
  r1 = _mm256_load_ps((const float *)(p0+5824LL));
  r0 -=  r1;
  /* OPT */  r2 = r29;
  /* OPT */  r3 = r29;
  r4 = _mm256_load_ps((const float *)(p0+605704LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1211392LL));
  r6 +=  r0;
  *(M *)(p0+1211392LL) = r6;   /* OPT */  r42 = r6;
  /* OPT */  r0 = r43;
  /* OPT */  r1 = r43;
  r4 = _mm256_load_ps((const float *)(p0+302856LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r38;
  r3 = _mm256_load_ps((const float *)(p0+56LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1514240LL));
  r6 +=  r0;
  *(M *)(p0+1514240LL) = r6;   /* OPT */  r28 = r6;
  /* OPT */  r0 = r42;
  /* OPT */  r1 = r42;
  r4 = _mm256_load_ps((const float *)(p0+1211384LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r34;
  r3 = _mm256_load_ps((const float *)(p0+908488LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r29;
  r6 +=  r0;
  *(M *)(p0+605696LL) = r6;
  /* OPT */  r0 = r34;
  r1 = _mm256_load_ps((const float *)(p0+902720LL));
  r0 -=  r1;
  /* OPT */  r2 = r28;
  /* OPT */  r3 = r28;
  r4 = _mm256_load_ps((const float *)(p0+1514232LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r43;
  r6 +=  r0;
  *(M *)(p0+302848LL) = r6;
  /* OPT */  r0 = r28;
  r1 = _mm256_load_ps((const float *)(p0+1514184LL));
  r0 -=  r1;
  /* OPT */  r2 = r42;
  r3 = _mm256_load_ps((const float *)(p0+1205568LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r38;
  r6 +=  r0;
  *(M *)(p0+0LL) = r6;
  
  }}

}

static PyObject * m_0003(PyObject *self, PyObject *args) {
  volatile double        retval=0;
  long           i0,i1;
  PyArrayObject *pa0,*pa1;
  float         *a0,*a1;

  if (!PyArg_ParseTuple(args, "llOO",&i0,&i1,&pa0,&pa1))
     return NULL;

  a0 = (float *)(pa0->data);
  a1 = (float *)(pa1->data);

  long long clmin = 1000000,cl0,cl1;
  for(int i=0;i<i0;i++)
     { 
     CPUCLOCK(cl0);  
     for(int j=0;j<i1;j++)
       { 
         yee_0_1_1_3(56,0,a0,a1,a1,a1);
       } 
     CPUCLOCK(cl1); cl1 -= cl0;  if(cl1 > 0 && cl1 < clmin ) clmin = cl1; 
     } 
  retval = clmin;

  return PyFloat_FromDouble(retval);
}
  
static void yee_8_0_0_4(int n,int n0,float *f,float *c,float *dummy,float *norm)               {
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r20 = _mm256_load_ps((const float *)(norm+0LL));
  r0 = _mm256_load_ps((const float *)(c+0LL));
  r20 *=  r0;
  r21 = _mm256_load_ps((const float *)(norm+8LL));
  r0 = _mm256_load_ps((const float *)(c+8LL));
  r21 *=  r0;
  r22 = _mm256_load_ps((const float *)(norm+16LL));
  r0 = _mm256_load_ps((const float *)(c+16LL));
  r22 *=  r0;
  r23 = _mm256_load_ps((const float *)(norm+24LL));
  r0 = _mm256_load_ps((const float *)(c+24LL));
  r23 *=  r0;
  r24 = _mm256_load_ps((const float *)(norm+32LL));
  r0 = _mm256_load_ps((const float *)(c+32LL));
  r24 *=  r0;
  r25 = _mm256_load_ps((const float *)(norm+40LL));
  r0 = _mm256_load_ps((const float *)(c+40LL));
  r25 *=  r0;
  {

  float * p0 = f + 0/8*8,* p1 = c + 0/8*0;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 0) {
  
  r0 = _mm256_load_ps((const float *)(p0+672384LL));   /* OPT */  r29 = r0;
  r1 = _mm256_load_ps((const float *)(p0+672448LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+336192LL));   /* OPT */  r36 = r2;
  r3 = _mm256_load_ps((const float *)(p0+342784LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+1008576LL));
  r6 +=  r0;
  *(M *)(p0+1008576LL) = r6;   /* OPT */  r35 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r37 = r0;
  r1 = _mm256_load_ps((const float *)(p0+6592LL));
  r0 -=  r1;
  /* OPT */  r2 = r29;
  /* OPT */  r3 = r29;
  r4 = _mm256_load_ps((const float *)(p0+672392LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1344768LL));
  r6 +=  r0;
  *(M *)(p0+1344768LL) = r6;   /* OPT */  r33 = r6;
  /* OPT */  r0 = r36;
  /* OPT */  r1 = r36;
  r4 = _mm256_load_ps((const float *)(p0+336200LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  r3 = _mm256_load_ps((const float *)(p0+64LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1680960LL));
  r6 +=  r0;
  *(M *)(p0+1680960LL) = r6;   /* OPT */  r32 = r6;
  /* OPT */  r0 = r33;
  /* OPT */  r1 = r33;
  r4 = _mm256_load_ps((const float *)(p0+1344760LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  r3 = _mm256_load_ps((const float *)(p0+1008512LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r29;
  r6 +=  r0;
  *(M *)(p0+672384LL) = r6;
  /* OPT */  r0 = r35;
  r1 = _mm256_load_ps((const float *)(p0+1001984LL));
  r0 -=  r1;
  /* OPT */  r2 = r32;
  /* OPT */  r3 = r32;
  r4 = _mm256_load_ps((const float *)(p0+1680952LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r36;
  r6 +=  r0;
  *(M *)(p0+336192LL) = r6;
  /* OPT */  r0 = r32;
  r1 = _mm256_load_ps((const float *)(p0+1680896LL));
  r0 -=  r1;
  /* OPT */  r2 = r33;
  r3 = _mm256_load_ps((const float *)(p0+1338176LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r37;
  r6 +=  r0;
  *(M *)(p0+0LL) = r6;
  
  }}

}

static PyObject * m_0004(PyObject *self, PyObject *args) {
  volatile double        retval=0;
  long           i0,i1;
  PyArrayObject *pa0,*pa1;
  float         *a0,*a1;

  if (!PyArg_ParseTuple(args, "llOO",&i0,&i1,&pa0,&pa1))
     return NULL;

  a0 = (float *)(pa0->data);
  a1 = (float *)(pa1->data);

  long long clmin = 1000000,cl0,cl1;
  for(int i=0;i<i0;i++)
     { 
     CPUCLOCK(cl0);  
     for(int j=0;j<i1;j++)
       { 
         yee_8_0_0_4(56,0,a0,a1,a1,a1);
       } 
     CPUCLOCK(cl1); cl1 -= cl0;  if(cl1 > 0 && cl1 < clmin ) clmin = cl1; 
     } 
  retval = clmin;

  return PyFloat_FromDouble(retval);
}
  
static void yee_8_0_1_5(int n,int n0,float *f,float *c,float *dummy,float *norm)               {
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r20 = _mm256_load_ps((const float *)(norm+0LL));
  r0 = _mm256_load_ps((const float *)(c+0LL));
  r20 *=  r0;
  r21 = _mm256_load_ps((const float *)(norm+8LL));
  r0 = _mm256_load_ps((const float *)(c+8LL));
  r21 *=  r0;
  r22 = _mm256_load_ps((const float *)(norm+16LL));
  r0 = _mm256_load_ps((const float *)(c+16LL));
  r22 *=  r0;
  r23 = _mm256_load_ps((const float *)(norm+24LL));
  r0 = _mm256_load_ps((const float *)(c+24LL));
  r23 *=  r0;
  r24 = _mm256_load_ps((const float *)(norm+32LL));
  r0 = _mm256_load_ps((const float *)(c+32LL));
  r24 *=  r0;
  r25 = _mm256_load_ps((const float *)(norm+40LL));
  r0 = _mm256_load_ps((const float *)(c+40LL));
  r25 *=  r0;
  {

  float * p0 = f + 0/8*8,* p1 = c + 0/8*0;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 0) {
  
  r0 = _mm256_load_ps((const float *)(p0+685568LL));   /* OPT */  r30 = r0;
  r1 = _mm256_load_ps((const float *)(p0+685632LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+342784LL));   /* OPT */  r43 = r2;
  r3 = _mm256_load_ps((const float *)(p0+349376LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+1028352LL));
  r6 +=  r0;
  *(M *)(p0+1028352LL) = r6;   /* OPT */  r34 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r38 = r0;
  r1 = _mm256_load_ps((const float *)(p0+6592LL));
  r0 -=  r1;
  /* OPT */  r2 = r30;
  /* OPT */  r3 = r30;
  r4 = _mm256_load_ps((const float *)(p0+685576LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1371136LL));
  r6 +=  r0;
  *(M *)(p0+1371136LL) = r6;   /* OPT */  r31 = r6;
  /* OPT */  r0 = r43;
  /* OPT */  r1 = r43;
  r4 = _mm256_load_ps((const float *)(p0+342792LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r38;
  r3 = _mm256_load_ps((const float *)(p0+64LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1713920LL));
  r6 +=  r0;
  *(M *)(p0+1713920LL) = r6;   /* OPT */  r35 = r6;
  /* OPT */  r0 = r31;
  /* OPT */  r1 = r31;
  r4 = _mm256_load_ps((const float *)(p0+1371128LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r34;
  r3 = _mm256_load_ps((const float *)(p0+1028288LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r30;
  r6 +=  r0;
  *(M *)(p0+685568LL) = r6;
  /* OPT */  r0 = r34;
  r1 = _mm256_load_ps((const float *)(p0+1021760LL));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  /* OPT */  r3 = r35;
  r4 = _mm256_load_ps((const float *)(p0+1713912LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r43;
  r6 +=  r0;
  *(M *)(p0+342784LL) = r6;
  /* OPT */  r0 = r35;
  r1 = _mm256_load_ps((const float *)(p0+1713856LL));
  r0 -=  r1;
  /* OPT */  r2 = r31;
  r3 = _mm256_load_ps((const float *)(p0+1364544LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r38;
  r6 +=  r0;
  *(M *)(p0+0LL) = r6;
  
  }}

}

static PyObject * m_0005(PyObject *self, PyObject *args) {
  volatile double        retval=0;
  long           i0,i1;
  PyArrayObject *pa0,*pa1;
  float         *a0,*a1;

  if (!PyArg_ParseTuple(args, "llOO",&i0,&i1,&pa0,&pa1))
     return NULL;

  a0 = (float *)(pa0->data);
  a1 = (float *)(pa1->data);

  long long clmin = 1000000,cl0,cl1;
  for(int i=0;i<i0;i++)
     { 
     CPUCLOCK(cl0);  
     for(int j=0;j<i1;j++)
       { 
         yee_8_0_1_5(56,0,a0,a1,a1,a1);
       } 
     CPUCLOCK(cl1); cl1 -= cl0;  if(cl1 > 0 && cl1 < clmin ) clmin = cl1; 
     } 
  retval = clmin;

  return PyFloat_FromDouble(retval);
}
  
static void yee_8_1_0_6(int n,int n0,float *f,float *c,float *dummy,float *norm)               {
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r20 = _mm256_load_ps((const float *)(norm+0LL));
  r0 = _mm256_load_ps((const float *)(c+0LL));
  r20 *=  r0;
  r21 = _mm256_load_ps((const float *)(norm+8LL));
  r0 = _mm256_load_ps((const float *)(c+8LL));
  r21 *=  r0;
  r22 = _mm256_load_ps((const float *)(norm+16LL));
  r0 = _mm256_load_ps((const float *)(c+16LL));
  r22 *=  r0;
  r23 = _mm256_load_ps((const float *)(norm+24LL));
  r0 = _mm256_load_ps((const float *)(c+24LL));
  r23 *=  r0;
  r24 = _mm256_load_ps((const float *)(norm+32LL));
  r0 = _mm256_load_ps((const float *)(c+32LL));
  r24 *=  r0;
  r25 = _mm256_load_ps((const float *)(norm+40LL));
  r0 = _mm256_load_ps((const float *)(c+40LL));
  r25 *=  r0;
  {

  float * p0 = f + 0/8*8,* p1 = c + 0/8*0;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 0) {
  
  r0 = _mm256_load_ps((const float *)(p0+678912LL));   /* OPT */  r35 = r0;
  r1 = _mm256_load_ps((const float *)(p0+678976LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+339456LL));   /* OPT */  r40 = r2;
  r3 = _mm256_load_ps((const float *)(p0+346112LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+1018368LL));
  r6 +=  r0;
  *(M *)(p0+1018368LL) = r6;   /* OPT */  r30 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r37 = r0;
  r1 = _mm256_load_ps((const float *)(p0+6656LL));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  /* OPT */  r3 = r35;
  r4 = _mm256_load_ps((const float *)(p0+678920LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1357824LL));
  r6 +=  r0;
  *(M *)(p0+1357824LL) = r6;   /* OPT */  r33 = r6;
  /* OPT */  r0 = r40;
  /* OPT */  r1 = r40;
  r4 = _mm256_load_ps((const float *)(p0+339464LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  r3 = _mm256_load_ps((const float *)(p0+64LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1697280LL));
  r6 +=  r0;
  *(M *)(p0+1697280LL) = r6;   /* OPT */  r34 = r6;
  /* OPT */  r0 = r33;
  /* OPT */  r1 = r33;
  r4 = _mm256_load_ps((const float *)(p0+1357816LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r30;
  r3 = _mm256_load_ps((const float *)(p0+1018304LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r35;
  r6 +=  r0;
  *(M *)(p0+678912LL) = r6;
  /* OPT */  r0 = r30;
  r1 = _mm256_load_ps((const float *)(p0+1011712LL));
  r0 -=  r1;
  /* OPT */  r2 = r34;
  /* OPT */  r3 = r34;
  r4 = _mm256_load_ps((const float *)(p0+1697272LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r40;
  r6 +=  r0;
  *(M *)(p0+339456LL) = r6;
  /* OPT */  r0 = r34;
  r1 = _mm256_load_ps((const float *)(p0+1697216LL));
  r0 -=  r1;
  /* OPT */  r2 = r33;
  r3 = _mm256_load_ps((const float *)(p0+1351168LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r37;
  r6 +=  r0;
  *(M *)(p0+0LL) = r6;
  
  }}

}

static PyObject * m_0006(PyObject *self, PyObject *args) {
  volatile double        retval=0;
  long           i0,i1;
  PyArrayObject *pa0,*pa1;
  float         *a0,*a1;

  if (!PyArg_ParseTuple(args, "llOO",&i0,&i1,&pa0,&pa1))
     return NULL;

  a0 = (float *)(pa0->data);
  a1 = (float *)(pa1->data);

  long long clmin = 1000000,cl0,cl1;
  for(int i=0;i<i0;i++)
     { 
     CPUCLOCK(cl0);  
     for(int j=0;j<i1;j++)
       { 
         yee_8_1_0_6(56,0,a0,a1,a1,a1);
       } 
     CPUCLOCK(cl1); cl1 -= cl0;  if(cl1 > 0 && cl1 < clmin ) clmin = cl1; 
     } 
  retval = clmin;

  return PyFloat_FromDouble(retval);
}
  
static void yee_8_1_1_7(int n,int n0,float *f,float *c,float *dummy,float *norm)               {
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r20 = _mm256_load_ps((const float *)(norm+0LL));
  r0 = _mm256_load_ps((const float *)(c+0LL));
  r20 *=  r0;
  r21 = _mm256_load_ps((const float *)(norm+8LL));
  r0 = _mm256_load_ps((const float *)(c+8LL));
  r21 *=  r0;
  r22 = _mm256_load_ps((const float *)(norm+16LL));
  r0 = _mm256_load_ps((const float *)(c+16LL));
  r22 *=  r0;
  r23 = _mm256_load_ps((const float *)(norm+24LL));
  r0 = _mm256_load_ps((const float *)(c+24LL));
  r23 *=  r0;
  r24 = _mm256_load_ps((const float *)(norm+32LL));
  r0 = _mm256_load_ps((const float *)(c+32LL));
  r24 *=  r0;
  r25 = _mm256_load_ps((const float *)(norm+40LL));
  r0 = _mm256_load_ps((const float *)(c+40LL));
  r25 *=  r0;
  {

  float * p0 = f + 0/8*8,* p1 = c + 0/8*0;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 0) {
  
  r0 = _mm256_load_ps((const float *)(p0+692224LL));   /* OPT */  r37 = r0;
  r1 = _mm256_load_ps((const float *)(p0+692288LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+346112LL));   /* OPT */  r38 = r2;
  r3 = _mm256_load_ps((const float *)(p0+352768LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+1038336LL));
  r6 +=  r0;
  *(M *)(p0+1038336LL) = r6;   /* OPT */  r41 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r39 = r0;
  r1 = _mm256_load_ps((const float *)(p0+6656LL));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  /* OPT */  r3 = r37;
  r4 = _mm256_load_ps((const float *)(p0+692232LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1384448LL));
  r6 +=  r0;
  *(M *)(p0+1384448LL) = r6;   /* OPT */  r26 = r6;
  /* OPT */  r0 = r38;
  /* OPT */  r1 = r38;
  r4 = _mm256_load_ps((const float *)(p0+346120LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r39;
  r3 = _mm256_load_ps((const float *)(p0+64LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1730560LL));
  r6 +=  r0;
  *(M *)(p0+1730560LL) = r6;   /* OPT */  r33 = r6;
  /* OPT */  r0 = r26;
  /* OPT */  r1 = r26;
  r4 = _mm256_load_ps((const float *)(p0+1384440LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r41;
  r3 = _mm256_load_ps((const float *)(p0+1038272LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r37;
  r6 +=  r0;
  *(M *)(p0+692224LL) = r6;
  /* OPT */  r0 = r41;
  r1 = _mm256_load_ps((const float *)(p0+1031680LL));
  r0 -=  r1;
  /* OPT */  r2 = r33;
  /* OPT */  r3 = r33;
  r4 = _mm256_load_ps((const float *)(p0+1730552LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r38;
  r6 +=  r0;
  *(M *)(p0+346112LL) = r6;
  /* OPT */  r0 = r33;
  r1 = _mm256_load_ps((const float *)(p0+1730496LL));
  r0 -=  r1;
  /* OPT */  r2 = r26;
  r3 = _mm256_load_ps((const float *)(p0+1377792LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r39;
  r6 +=  r0;
  *(M *)(p0+0LL) = r6;
  
  }}

}

static PyObject * m_0007(PyObject *self, PyObject *args) {
  volatile double        retval=0;
  long           i0,i1;
  PyArrayObject *pa0,*pa1;
  float         *a0,*a1;

  if (!PyArg_ParseTuple(args, "llOO",&i0,&i1,&pa0,&pa1))
     return NULL;

  a0 = (float *)(pa0->data);
  a1 = (float *)(pa1->data);

  long long clmin = 1000000,cl0,cl1;
  for(int i=0;i<i0;i++)
     { 
     CPUCLOCK(cl0);  
     for(int j=0;j<i1;j++)
       { 
         yee_8_1_1_7(56,0,a0,a1,a1,a1);
       } 
     CPUCLOCK(cl1); cl1 -= cl0;  if(cl1 > 0 && cl1 < clmin ) clmin = cl1; 
     } 
  retval = clmin;

  return PyFloat_FromDouble(retval);
}


static PyMethodDef moduleMethods[] = {
{"m_0000",m_0000,METH_VARARGS,0},
{"m_0001",m_0001,METH_VARARGS,0},
{"m_0002",m_0002,METH_VARARGS,0},
{"m_0003",m_0003,METH_VARARGS,0},
{"m_0004",m_0004,METH_VARARGS,0},
{"m_0005",m_0005,METH_VARARGS,0},
{"m_0006",m_0006,METH_VARARGS,0},
{"m_0007",m_0007,METH_VARARGS,0},
{0}
};

extern "C" DL_EXPORT(void) initcode_02(void) {
   PyObject *m;
   m = Py_InitModule("code_02",moduleMethods);
   import_array();
#ifdef MS_WIN32
   init_dict();
#endif
}
        
