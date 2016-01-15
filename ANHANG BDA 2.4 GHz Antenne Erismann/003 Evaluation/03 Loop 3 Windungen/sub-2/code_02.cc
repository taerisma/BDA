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
  
  r0 = _mm256_load_ps((const float *)(p0+543312LL));   /* OPT */  r27 = r0;
  r1 = _mm256_load_ps((const float *)(p0+543368LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+271656LL));   /* OPT */  r33 = r2;
  r3 = _mm256_load_ps((const float *)(p0+277200LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+814968LL));
  r6 +=  r0;
  *(M *)(p0+814968LL) = r6;   /* OPT */  r40 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r37 = r0;
  r1 = _mm256_load_ps((const float *)(p0+5544LL));
  r0 -=  r1;
  /* OPT */  r2 = r27;
  /* OPT */  r3 = r27;
  r4 = _mm256_load_ps((const float *)(p0+543320LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1086624LL));
  r6 +=  r0;
  *(M *)(p0+1086624LL) = r6;   /* OPT */  r43 = r6;
  /* OPT */  r0 = r33;
  /* OPT */  r1 = r33;
  r4 = _mm256_load_ps((const float *)(p0+271664LL));
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
  r6 = _mm256_load_ps((const float *)(p0+1358280LL));
  r6 +=  r0;
  *(M *)(p0+1358280LL) = r6;   /* OPT */  r36 = r6;
  /* OPT */  r0 = r43;
  /* OPT */  r1 = r43;
  r4 = _mm256_load_ps((const float *)(p0+1086616LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r40;
  r3 = _mm256_load_ps((const float *)(p0+814912LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r27;
  r6 +=  r0;
  *(M *)(p0+543312LL) = r6;
  /* OPT */  r0 = r40;
  r1 = _mm256_load_ps((const float *)(p0+809424LL));
  r0 -=  r1;
  /* OPT */  r2 = r36;
  /* OPT */  r3 = r36;
  r4 = _mm256_load_ps((const float *)(p0+1358272LL));
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
  *(M *)(p0+271656LL) = r6;
  /* OPT */  r0 = r36;
  r1 = _mm256_load_ps((const float *)(p0+1358224LL));
  r0 -=  r1;
  /* OPT */  r2 = r43;
  r3 = _mm256_load_ps((const float *)(p0+1081080LL));
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
  
  r0 = _mm256_load_ps((const float *)(p0+554400LL));   /* OPT */  r36 = r0;
  r1 = _mm256_load_ps((const float *)(p0+554456LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+277200LL));   /* OPT */  r27 = r2;
  r3 = _mm256_load_ps((const float *)(p0+282744LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+831600LL));
  r6 +=  r0;
  *(M *)(p0+831600LL) = r6;   /* OPT */  r30 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r40 = r0;
  r1 = _mm256_load_ps((const float *)(p0+5544LL));
  r0 -=  r1;
  /* OPT */  r2 = r36;
  /* OPT */  r3 = r36;
  r4 = _mm256_load_ps((const float *)(p0+554408LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1108800LL));
  r6 +=  r0;
  *(M *)(p0+1108800LL) = r6;   /* OPT */  r29 = r6;
  /* OPT */  r0 = r27;
  /* OPT */  r1 = r27;
  r4 = _mm256_load_ps((const float *)(p0+277208LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r40;
  r3 = _mm256_load_ps((const float *)(p0+56LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1386000LL));
  r6 +=  r0;
  *(M *)(p0+1386000LL) = r6;   /* OPT */  r39 = r6;
  /* OPT */  r0 = r29;
  /* OPT */  r1 = r29;
  r4 = _mm256_load_ps((const float *)(p0+1108792LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r30;
  r3 = _mm256_load_ps((const float *)(p0+831544LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r36;
  r6 +=  r0;
  *(M *)(p0+554400LL) = r6;
  /* OPT */  r0 = r30;
  r1 = _mm256_load_ps((const float *)(p0+826056LL));
  r0 -=  r1;
  /* OPT */  r2 = r39;
  /* OPT */  r3 = r39;
  r4 = _mm256_load_ps((const float *)(p0+1385992LL));
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
  *(M *)(p0+277200LL) = r6;
  /* OPT */  r0 = r39;
  r1 = _mm256_load_ps((const float *)(p0+1385944LL));
  r0 -=  r1;
  /* OPT */  r2 = r29;
  r3 = _mm256_load_ps((const float *)(p0+1103256LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r40;
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
  
  r0 = _mm256_load_ps((const float *)(p0+548800LL));   /* OPT */  r29 = r0;
  r1 = _mm256_load_ps((const float *)(p0+548856LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+274400LL));   /* OPT */  r34 = r2;
  r3 = _mm256_load_ps((const float *)(p0+280000LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+823200LL));
  r6 +=  r0;
  *(M *)(p0+823200LL) = r6;   /* OPT */  r41 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r37 = r0;
  r1 = _mm256_load_ps((const float *)(p0+5600LL));
  r0 -=  r1;
  /* OPT */  r2 = r29;
  /* OPT */  r3 = r29;
  r4 = _mm256_load_ps((const float *)(p0+548808LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1097600LL));
  r6 +=  r0;
  *(M *)(p0+1097600LL) = r6;   /* OPT */  r31 = r6;
  /* OPT */  r0 = r34;
  /* OPT */  r1 = r34;
  r4 = _mm256_load_ps((const float *)(p0+274408LL));
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
  r6 = _mm256_load_ps((const float *)(p0+1372000LL));
  r6 +=  r0;
  *(M *)(p0+1372000LL) = r6;   /* OPT */  r27 = r6;
  /* OPT */  r0 = r31;
  /* OPT */  r1 = r31;
  r4 = _mm256_load_ps((const float *)(p0+1097592LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r41;
  r3 = _mm256_load_ps((const float *)(p0+823144LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r29;
  r6 +=  r0;
  *(M *)(p0+548800LL) = r6;
  /* OPT */  r0 = r41;
  r1 = _mm256_load_ps((const float *)(p0+817600LL));
  r0 -=  r1;
  /* OPT */  r2 = r27;
  /* OPT */  r3 = r27;
  r4 = _mm256_load_ps((const float *)(p0+1371992LL));
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
  *(M *)(p0+274400LL) = r6;
  /* OPT */  r0 = r27;
  r1 = _mm256_load_ps((const float *)(p0+1371944LL));
  r0 -=  r1;
  /* OPT */  r2 = r31;
  r3 = _mm256_load_ps((const float *)(p0+1092000LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r37;
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
  
  r0 = _mm256_load_ps((const float *)(p0+560000LL));   /* OPT */  r28 = r0;
  r1 = _mm256_load_ps((const float *)(p0+560056LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+280000LL));   /* OPT */  r35 = r2;
  r3 = _mm256_load_ps((const float *)(p0+285600LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+840000LL));
  r6 +=  r0;
  *(M *)(p0+840000LL) = r6;   /* OPT */  r36 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r37 = r0;
  r1 = _mm256_load_ps((const float *)(p0+5600LL));
  r0 -=  r1;
  /* OPT */  r2 = r28;
  /* OPT */  r3 = r28;
  r4 = _mm256_load_ps((const float *)(p0+560008LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1120000LL));
  r6 +=  r0;
  *(M *)(p0+1120000LL) = r6;   /* OPT */  r42 = r6;
  /* OPT */  r0 = r35;
  /* OPT */  r1 = r35;
  r4 = _mm256_load_ps((const float *)(p0+280008LL));
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
  r6 = _mm256_load_ps((const float *)(p0+1400000LL));
  r6 +=  r0;
  *(M *)(p0+1400000LL) = r6;   /* OPT */  r29 = r6;
  /* OPT */  r0 = r42;
  /* OPT */  r1 = r42;
  r4 = _mm256_load_ps((const float *)(p0+1119992LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r36;
  r3 = _mm256_load_ps((const float *)(p0+839944LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r28;
  r6 +=  r0;
  *(M *)(p0+560000LL) = r6;
  /* OPT */  r0 = r36;
  r1 = _mm256_load_ps((const float *)(p0+834400LL));
  r0 -=  r1;
  /* OPT */  r2 = r29;
  /* OPT */  r3 = r29;
  r4 = _mm256_load_ps((const float *)(p0+1399992LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r35;
  r6 +=  r0;
  *(M *)(p0+280000LL) = r6;
  /* OPT */  r0 = r29;
  r1 = _mm256_load_ps((const float *)(p0+1399944LL));
  r0 -=  r1;
  /* OPT */  r2 = r42;
  r3 = _mm256_load_ps((const float *)(p0+1114400LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r37;
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
  
  r0 = _mm256_load_ps((const float *)(p0+620928LL));   /* OPT */  r29 = r0;
  r1 = _mm256_load_ps((const float *)(p0+620992LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+310464LL));   /* OPT */  r36 = r2;
  r3 = _mm256_load_ps((const float *)(p0+316800LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+931392LL));
  r6 +=  r0;
  *(M *)(p0+931392LL) = r6;   /* OPT */  r33 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r37 = r0;
  r1 = _mm256_load_ps((const float *)(p0+6336LL));
  r0 -=  r1;
  /* OPT */  r2 = r29;
  /* OPT */  r3 = r29;
  r4 = _mm256_load_ps((const float *)(p0+620936LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1241856LL));
  r6 +=  r0;
  *(M *)(p0+1241856LL) = r6;   /* OPT */  r43 = r6;
  /* OPT */  r0 = r36;
  /* OPT */  r1 = r36;
  r4 = _mm256_load_ps((const float *)(p0+310472LL));
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
  r6 = _mm256_load_ps((const float *)(p0+1552320LL));
  r6 +=  r0;
  *(M *)(p0+1552320LL) = r6;   /* OPT */  r35 = r6;
  /* OPT */  r0 = r43;
  /* OPT */  r1 = r43;
  r4 = _mm256_load_ps((const float *)(p0+1241848LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r33;
  r3 = _mm256_load_ps((const float *)(p0+931328LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r29;
  r6 +=  r0;
  *(M *)(p0+620928LL) = r6;
  /* OPT */  r0 = r33;
  r1 = _mm256_load_ps((const float *)(p0+925056LL));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  /* OPT */  r3 = r35;
  r4 = _mm256_load_ps((const float *)(p0+1552312LL));
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
  *(M *)(p0+310464LL) = r6;
  /* OPT */  r0 = r35;
  r1 = _mm256_load_ps((const float *)(p0+1552256LL));
  r0 -=  r1;
  /* OPT */  r2 = r43;
  r3 = _mm256_load_ps((const float *)(p0+1235520LL));
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
  
  r0 = _mm256_load_ps((const float *)(p0+633600LL));   /* OPT */  r29 = r0;
  r1 = _mm256_load_ps((const float *)(p0+633664LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+316800LL));   /* OPT */  r41 = r2;
  r3 = _mm256_load_ps((const float *)(p0+323136LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+950400LL));
  r6 +=  r0;
  *(M *)(p0+950400LL) = r6;   /* OPT */  r35 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r37 = r0;
  r1 = _mm256_load_ps((const float *)(p0+6336LL));
  r0 -=  r1;
  /* OPT */  r2 = r29;
  /* OPT */  r3 = r29;
  r4 = _mm256_load_ps((const float *)(p0+633608LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1267200LL));
  r6 +=  r0;
  *(M *)(p0+1267200LL) = r6;   /* OPT */  r28 = r6;
  /* OPT */  r0 = r41;
  /* OPT */  r1 = r41;
  r4 = _mm256_load_ps((const float *)(p0+316808LL));
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
  r6 = _mm256_load_ps((const float *)(p0+1584000LL));
  r6 +=  r0;
  *(M *)(p0+1584000LL) = r6;   /* OPT */  r32 = r6;
  /* OPT */  r0 = r28;
  /* OPT */  r1 = r28;
  r4 = _mm256_load_ps((const float *)(p0+1267192LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  r3 = _mm256_load_ps((const float *)(p0+950336LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r29;
  r6 +=  r0;
  *(M *)(p0+633600LL) = r6;
  /* OPT */  r0 = r35;
  r1 = _mm256_load_ps((const float *)(p0+944064LL));
  r0 -=  r1;
  /* OPT */  r2 = r32;
  /* OPT */  r3 = r32;
  r4 = _mm256_load_ps((const float *)(p0+1583992LL));
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
  *(M *)(p0+316800LL) = r6;
  /* OPT */  r0 = r32;
  r1 = _mm256_load_ps((const float *)(p0+1583936LL));
  r0 -=  r1;
  /* OPT */  r2 = r28;
  r3 = _mm256_load_ps((const float *)(p0+1260864LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r37;
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
  
  r0 = _mm256_load_ps((const float *)(p0+627200LL));   /* OPT */  r36 = r0;
  r1 = _mm256_load_ps((const float *)(p0+627264LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+313600LL));   /* OPT */  r35 = r2;
  r3 = _mm256_load_ps((const float *)(p0+320000LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+940800LL));
  r6 +=  r0;
  *(M *)(p0+940800LL) = r6;   /* OPT */  r43 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r38 = r0;
  r1 = _mm256_load_ps((const float *)(p0+6400LL));
  r0 -=  r1;
  /* OPT */  r2 = r36;
  /* OPT */  r3 = r36;
  r4 = _mm256_load_ps((const float *)(p0+627208LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1254400LL));
  r6 +=  r0;
  *(M *)(p0+1254400LL) = r6;   /* OPT */  r26 = r6;
  /* OPT */  r0 = r35;
  /* OPT */  r1 = r35;
  r4 = _mm256_load_ps((const float *)(p0+313608LL));
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
  r6 = _mm256_load_ps((const float *)(p0+1568000LL));
  r6 +=  r0;
  *(M *)(p0+1568000LL) = r6;   /* OPT */  r41 = r6;
  /* OPT */  r0 = r26;
  /* OPT */  r1 = r26;
  r4 = _mm256_load_ps((const float *)(p0+1254392LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r43;
  r3 = _mm256_load_ps((const float *)(p0+940736LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r36;
  r6 +=  r0;
  *(M *)(p0+627200LL) = r6;
  /* OPT */  r0 = r43;
  r1 = _mm256_load_ps((const float *)(p0+934400LL));
  r0 -=  r1;
  /* OPT */  r2 = r41;
  /* OPT */  r3 = r41;
  r4 = _mm256_load_ps((const float *)(p0+1567992LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r35;
  r6 +=  r0;
  *(M *)(p0+313600LL) = r6;
  /* OPT */  r0 = r41;
  r1 = _mm256_load_ps((const float *)(p0+1567936LL));
  r0 -=  r1;
  /* OPT */  r2 = r26;
  r3 = _mm256_load_ps((const float *)(p0+1248000LL));
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
  
  r0 = _mm256_load_ps((const float *)(p0+640000LL));   /* OPT */  r29 = r0;
  r1 = _mm256_load_ps((const float *)(p0+640064LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+320000LL));   /* OPT */  r28 = r2;
  r3 = _mm256_load_ps((const float *)(p0+326400LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+960000LL));
  r6 +=  r0;
  *(M *)(p0+960000LL) = r6;   /* OPT */  r33 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r35 = r0;
  r1 = _mm256_load_ps((const float *)(p0+6400LL));
  r0 -=  r1;
  /* OPT */  r2 = r29;
  /* OPT */  r3 = r29;
  r4 = _mm256_load_ps((const float *)(p0+640008LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1280000LL));
  r6 +=  r0;
  *(M *)(p0+1280000LL) = r6;   /* OPT */  r27 = r6;
  /* OPT */  r0 = r28;
  /* OPT */  r1 = r28;
  r4 = _mm256_load_ps((const float *)(p0+320008LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  r3 = _mm256_load_ps((const float *)(p0+64LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1600000LL));
  r6 +=  r0;
  *(M *)(p0+1600000LL) = r6;   /* OPT */  r31 = r6;
  /* OPT */  r0 = r27;
  /* OPT */  r1 = r27;
  r4 = _mm256_load_ps((const float *)(p0+1279992LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r33;
  r3 = _mm256_load_ps((const float *)(p0+959936LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r29;
  r6 +=  r0;
  *(M *)(p0+640000LL) = r6;
  /* OPT */  r0 = r33;
  r1 = _mm256_load_ps((const float *)(p0+953600LL));
  r0 -=  r1;
  /* OPT */  r2 = r31;
  /* OPT */  r3 = r31;
  r4 = _mm256_load_ps((const float *)(p0+1599992LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r28;
  r6 +=  r0;
  *(M *)(p0+320000LL) = r6;
  /* OPT */  r0 = r31;
  r1 = _mm256_load_ps((const float *)(p0+1599936LL));
  r0 -=  r1;
  /* OPT */  r2 = r27;
  r3 = _mm256_load_ps((const float *)(p0+1273600LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r35;
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
        
