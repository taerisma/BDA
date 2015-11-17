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
  
  r0 = _mm256_load_ps((const float *)(p0+565264LL));   /* OPT */  r26 = r0;
  r1 = _mm256_load_ps((const float *)(p0+565320LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+282632LL));   /* OPT */  r30 = r2;
  r3 = _mm256_load_ps((const float *)(p0+288400LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+847896LL));
  r6 +=  r0;
  *(M *)(p0+847896LL) = r6;   /* OPT */  r39 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r35 = r0;
  r1 = _mm256_load_ps((const float *)(p0+5768LL));
  r0 -=  r1;
  /* OPT */  r2 = r26;
  /* OPT */  r3 = r26;
  r4 = _mm256_load_ps((const float *)(p0+565272LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1130528LL));
  r6 +=  r0;
  *(M *)(p0+1130528LL) = r6;   /* OPT */  r36 = r6;
  /* OPT */  r0 = r30;
  /* OPT */  r1 = r30;
  r4 = _mm256_load_ps((const float *)(p0+282640LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  r3 = _mm256_load_ps((const float *)(p0+56LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1413160LL));
  r6 +=  r0;
  *(M *)(p0+1413160LL) = r6;   /* OPT */  r41 = r6;
  /* OPT */  r0 = r36;
  /* OPT */  r1 = r36;
  r4 = _mm256_load_ps((const float *)(p0+1130520LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r39;
  r3 = _mm256_load_ps((const float *)(p0+847840LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r26;
  r6 +=  r0;
  *(M *)(p0+565264LL) = r6;
  /* OPT */  r0 = r39;
  r1 = _mm256_load_ps((const float *)(p0+842128LL));
  r0 -=  r1;
  /* OPT */  r2 = r41;
  /* OPT */  r3 = r41;
  r4 = _mm256_load_ps((const float *)(p0+1413152LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r30;
  r6 +=  r0;
  *(M *)(p0+282632LL) = r6;
  /* OPT */  r0 = r41;
  r1 = _mm256_load_ps((const float *)(p0+1413104LL));
  r0 -=  r1;
  /* OPT */  r2 = r36;
  r3 = _mm256_load_ps((const float *)(p0+1124760LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r35;
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
  
  r0 = _mm256_load_ps((const float *)(p0+576800LL));   /* OPT */  r34 = r0;
  r1 = _mm256_load_ps((const float *)(p0+576856LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+288400LL));   /* OPT */  r26 = r2;
  r3 = _mm256_load_ps((const float *)(p0+294168LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+865200LL));
  r6 +=  r0;
  *(M *)(p0+865200LL) = r6;   /* OPT */  r37 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r28 = r0;
  r1 = _mm256_load_ps((const float *)(p0+5768LL));
  r0 -=  r1;
  /* OPT */  r2 = r34;
  /* OPT */  r3 = r34;
  r4 = _mm256_load_ps((const float *)(p0+576808LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1153600LL));
  r6 +=  r0;
  *(M *)(p0+1153600LL) = r6;   /* OPT */  r31 = r6;
  /* OPT */  r0 = r26;
  /* OPT */  r1 = r26;
  r4 = _mm256_load_ps((const float *)(p0+288408LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r28;
  r3 = _mm256_load_ps((const float *)(p0+56LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1442000LL));
  r6 +=  r0;
  *(M *)(p0+1442000LL) = r6;   /* OPT */  r27 = r6;
  /* OPT */  r0 = r31;
  /* OPT */  r1 = r31;
  r4 = _mm256_load_ps((const float *)(p0+1153592LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  r3 = _mm256_load_ps((const float *)(p0+865144LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r34;
  r6 +=  r0;
  *(M *)(p0+576800LL) = r6;
  /* OPT */  r0 = r37;
  r1 = _mm256_load_ps((const float *)(p0+859432LL));
  r0 -=  r1;
  /* OPT */  r2 = r27;
  /* OPT */  r3 = r27;
  r4 = _mm256_load_ps((const float *)(p0+1441992LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r26;
  r6 +=  r0;
  *(M *)(p0+288400LL) = r6;
  /* OPT */  r0 = r27;
  r1 = _mm256_load_ps((const float *)(p0+1441944LL));
  r0 -=  r1;
  /* OPT */  r2 = r31;
  r3 = _mm256_load_ps((const float *)(p0+1147832LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r28;
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
  
  r0 = _mm256_load_ps((const float *)(p0+570752LL));   /* OPT */  r28 = r0;
  r1 = _mm256_load_ps((const float *)(p0+570808LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+285376LL));   /* OPT */  r33 = r2;
  r3 = _mm256_load_ps((const float *)(p0+291200LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+856128LL));
  r6 +=  r0;
  *(M *)(p0+856128LL) = r6;   /* OPT */  r41 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r36 = r0;
  r1 = _mm256_load_ps((const float *)(p0+5824LL));
  r0 -=  r1;
  /* OPT */  r2 = r28;
  /* OPT */  r3 = r28;
  r4 = _mm256_load_ps((const float *)(p0+570760LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1141504LL));
  r6 +=  r0;
  *(M *)(p0+1141504LL) = r6;   /* OPT */  r42 = r6;
  /* OPT */  r0 = r33;
  /* OPT */  r1 = r33;
  r4 = _mm256_load_ps((const float *)(p0+285384LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r36;
  r3 = _mm256_load_ps((const float *)(p0+56LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1426880LL));
  r6 +=  r0;
  *(M *)(p0+1426880LL) = r6;   /* OPT */  r26 = r6;
  /* OPT */  r0 = r42;
  /* OPT */  r1 = r42;
  r4 = _mm256_load_ps((const float *)(p0+1141496LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r41;
  r3 = _mm256_load_ps((const float *)(p0+856072LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r28;
  r6 +=  r0;
  *(M *)(p0+570752LL) = r6;
  /* OPT */  r0 = r41;
  r1 = _mm256_load_ps((const float *)(p0+850304LL));
  r0 -=  r1;
  /* OPT */  r2 = r26;
  /* OPT */  r3 = r26;
  r4 = _mm256_load_ps((const float *)(p0+1426872LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r33;
  r6 +=  r0;
  *(M *)(p0+285376LL) = r6;
  /* OPT */  r0 = r26;
  r1 = _mm256_load_ps((const float *)(p0+1426824LL));
  r0 -=  r1;
  /* OPT */  r2 = r42;
  r3 = _mm256_load_ps((const float *)(p0+1135680LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r36;
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
  
  r0 = _mm256_load_ps((const float *)(p0+582400LL));   /* OPT */  r37 = r0;
  r1 = _mm256_load_ps((const float *)(p0+582456LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+291200LL));   /* OPT */  r31 = r2;
  r3 = _mm256_load_ps((const float *)(p0+297024LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+873600LL));
  r6 +=  r0;
  *(M *)(p0+873600LL) = r6;   /* OPT */  r27 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r39 = r0;
  r1 = _mm256_load_ps((const float *)(p0+5824LL));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  /* OPT */  r3 = r37;
  r4 = _mm256_load_ps((const float *)(p0+582408LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1164800LL));
  r6 +=  r0;
  *(M *)(p0+1164800LL) = r6;   /* OPT */  r30 = r6;
  /* OPT */  r0 = r31;
  /* OPT */  r1 = r31;
  r4 = _mm256_load_ps((const float *)(p0+291208LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r39;
  r3 = _mm256_load_ps((const float *)(p0+56LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1456000LL));
  r6 +=  r0;
  *(M *)(p0+1456000LL) = r6;   /* OPT */  r35 = r6;
  /* OPT */  r0 = r30;
  /* OPT */  r1 = r30;
  r4 = _mm256_load_ps((const float *)(p0+1164792LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r27;
  r3 = _mm256_load_ps((const float *)(p0+873544LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r37;
  r6 +=  r0;
  *(M *)(p0+582400LL) = r6;
  /* OPT */  r0 = r27;
  r1 = _mm256_load_ps((const float *)(p0+867776LL));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  /* OPT */  r3 = r35;
  r4 = _mm256_load_ps((const float *)(p0+1455992LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r31;
  r6 +=  r0;
  *(M *)(p0+291200LL) = r6;
  /* OPT */  r0 = r35;
  r1 = _mm256_load_ps((const float *)(p0+1455944LL));
  r0 -=  r1;
  /* OPT */  r2 = r30;
  r3 = _mm256_load_ps((const float *)(p0+1158976LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r39;
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
  
  r0 = _mm256_load_ps((const float *)(p0+646016LL));   /* OPT */  r28 = r0;
  r1 = _mm256_load_ps((const float *)(p0+646080LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+323008LL));   /* OPT */  r34 = r2;
  r3 = _mm256_load_ps((const float *)(p0+329600LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+969024LL));
  r6 +=  r0;
  *(M *)(p0+969024LL) = r6;   /* OPT */  r36 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r37 = r0;
  r1 = _mm256_load_ps((const float *)(p0+6592LL));
  r0 -=  r1;
  /* OPT */  r2 = r28;
  /* OPT */  r3 = r28;
  r4 = _mm256_load_ps((const float *)(p0+646024LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1292032LL));
  r6 +=  r0;
  *(M *)(p0+1292032LL) = r6;   /* OPT */  r42 = r6;
  /* OPT */  r0 = r34;
  /* OPT */  r1 = r34;
  r4 = _mm256_load_ps((const float *)(p0+323016LL));
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
  r6 = _mm256_load_ps((const float *)(p0+1615040LL));
  r6 +=  r0;
  *(M *)(p0+1615040LL) = r6;   /* OPT */  r29 = r6;
  /* OPT */  r0 = r42;
  /* OPT */  r1 = r42;
  r4 = _mm256_load_ps((const float *)(p0+1292024LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r36;
  r3 = _mm256_load_ps((const float *)(p0+968960LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r28;
  r6 +=  r0;
  *(M *)(p0+646016LL) = r6;
  /* OPT */  r0 = r36;
  r1 = _mm256_load_ps((const float *)(p0+962432LL));
  r0 -=  r1;
  /* OPT */  r2 = r29;
  /* OPT */  r3 = r29;
  r4 = _mm256_load_ps((const float *)(p0+1615032LL));
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
  *(M *)(p0+323008LL) = r6;
  /* OPT */  r0 = r29;
  r1 = _mm256_load_ps((const float *)(p0+1614976LL));
  r0 -=  r1;
  /* OPT */  r2 = r42;
  r3 = _mm256_load_ps((const float *)(p0+1285440LL));
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
  
  r0 = _mm256_load_ps((const float *)(p0+659200LL));   /* OPT */  r30 = r0;
  r1 = _mm256_load_ps((const float *)(p0+659264LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+329600LL));   /* OPT */  r33 = r2;
  r3 = _mm256_load_ps((const float *)(p0+336192LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+988800LL));
  r6 +=  r0;
  *(M *)(p0+988800LL) = r6;   /* OPT */  r36 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r39 = r0;
  r1 = _mm256_load_ps((const float *)(p0+6592LL));
  r0 -=  r1;
  /* OPT */  r2 = r30;
  /* OPT */  r3 = r30;
  r4 = _mm256_load_ps((const float *)(p0+659208LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1318400LL));
  r6 +=  r0;
  *(M *)(p0+1318400LL) = r6;   /* OPT */  r29 = r6;
  /* OPT */  r0 = r33;
  /* OPT */  r1 = r33;
  r4 = _mm256_load_ps((const float *)(p0+329608LL));
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
  r6 = _mm256_load_ps((const float *)(p0+1648000LL));
  r6 +=  r0;
  *(M *)(p0+1648000LL) = r6;   /* OPT */  r42 = r6;
  /* OPT */  r0 = r29;
  /* OPT */  r1 = r29;
  r4 = _mm256_load_ps((const float *)(p0+1318392LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r36;
  r3 = _mm256_load_ps((const float *)(p0+988736LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r30;
  r6 +=  r0;
  *(M *)(p0+659200LL) = r6;
  /* OPT */  r0 = r36;
  r1 = _mm256_load_ps((const float *)(p0+982208LL));
  r0 -=  r1;
  /* OPT */  r2 = r42;
  /* OPT */  r3 = r42;
  r4 = _mm256_load_ps((const float *)(p0+1647992LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r33;
  r6 +=  r0;
  *(M *)(p0+329600LL) = r6;
  /* OPT */  r0 = r42;
  r1 = _mm256_load_ps((const float *)(p0+1647936LL));
  r0 -=  r1;
  /* OPT */  r2 = r29;
  r3 = _mm256_load_ps((const float *)(p0+1311808LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r39;
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
  
  r0 = _mm256_load_ps((const float *)(p0+652288LL));   /* OPT */  r34 = r0;
  r1 = _mm256_load_ps((const float *)(p0+652352LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+326144LL));   /* OPT */  r27 = r2;
  r3 = _mm256_load_ps((const float *)(p0+332800LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+978432LL));
  r6 +=  r0;
  *(M *)(p0+978432LL) = r6;   /* OPT */  r29 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r38 = r0;
  r1 = _mm256_load_ps((const float *)(p0+6656LL));
  r0 -=  r1;
  /* OPT */  r2 = r34;
  /* OPT */  r3 = r34;
  r4 = _mm256_load_ps((const float *)(p0+652296LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1304576LL));
  r6 +=  r0;
  *(M *)(p0+1304576LL) = r6;   /* OPT */  r33 = r6;
  /* OPT */  r0 = r27;
  /* OPT */  r1 = r27;
  r4 = _mm256_load_ps((const float *)(p0+326152LL));
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
  r6 = _mm256_load_ps((const float *)(p0+1630720LL));
  r6 +=  r0;
  *(M *)(p0+1630720LL) = r6;   /* OPT */  r36 = r6;
  /* OPT */  r0 = r33;
  /* OPT */  r1 = r33;
  r4 = _mm256_load_ps((const float *)(p0+1304568LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r29;
  r3 = _mm256_load_ps((const float *)(p0+978368LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r34;
  r6 +=  r0;
  *(M *)(p0+652288LL) = r6;
  /* OPT */  r0 = r29;
  r1 = _mm256_load_ps((const float *)(p0+971776LL));
  r0 -=  r1;
  /* OPT */  r2 = r36;
  /* OPT */  r3 = r36;
  r4 = _mm256_load_ps((const float *)(p0+1630712LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r27;
  r6 +=  r0;
  *(M *)(p0+326144LL) = r6;
  /* OPT */  r0 = r36;
  r1 = _mm256_load_ps((const float *)(p0+1630656LL));
  r0 -=  r1;
  /* OPT */  r2 = r33;
  r3 = _mm256_load_ps((const float *)(p0+1297920LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r38;
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
  
  r0 = _mm256_load_ps((const float *)(p0+665600LL));   /* OPT */  r35 = r0;
  r1 = _mm256_load_ps((const float *)(p0+665664LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+332800LL));   /* OPT */  r40 = r2;
  r3 = _mm256_load_ps((const float *)(p0+339456LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+998400LL));
  r6 +=  r0;
  *(M *)(p0+998400LL) = r6;   /* OPT */  r37 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r31 = r0;
  r1 = _mm256_load_ps((const float *)(p0+6656LL));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  /* OPT */  r3 = r35;
  r4 = _mm256_load_ps((const float *)(p0+665608LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1331200LL));
  r6 +=  r0;
  *(M *)(p0+1331200LL) = r6;   /* OPT */  r32 = r6;
  /* OPT */  r0 = r40;
  /* OPT */  r1 = r40;
  r4 = _mm256_load_ps((const float *)(p0+332808LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r31;
  r3 = _mm256_load_ps((const float *)(p0+64LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1664000LL));
  r6 +=  r0;
  *(M *)(p0+1664000LL) = r6;   /* OPT */  r33 = r6;
  /* OPT */  r0 = r32;
  /* OPT */  r1 = r32;
  r4 = _mm256_load_ps((const float *)(p0+1331192LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  r3 = _mm256_load_ps((const float *)(p0+998336LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r35;
  r6 +=  r0;
  *(M *)(p0+665600LL) = r6;
  /* OPT */  r0 = r37;
  r1 = _mm256_load_ps((const float *)(p0+991744LL));
  r0 -=  r1;
  /* OPT */  r2 = r33;
  /* OPT */  r3 = r33;
  r4 = _mm256_load_ps((const float *)(p0+1663992LL));
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
  *(M *)(p0+332800LL) = r6;
  /* OPT */  r0 = r33;
  r1 = _mm256_load_ps((const float *)(p0+1663936LL));
  r0 -=  r1;
  /* OPT */  r2 = r32;
  r3 = _mm256_load_ps((const float *)(p0+1324544LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r31;
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
        
