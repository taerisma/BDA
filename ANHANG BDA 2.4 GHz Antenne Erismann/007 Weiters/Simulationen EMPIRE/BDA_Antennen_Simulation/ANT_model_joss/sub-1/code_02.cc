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
  
  r0 = _mm256_load_ps((const float *)(p0+562496LL));   /* OPT */  r36 = r0;
  r1 = _mm256_load_ps((const float *)(p0+562584LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+281248LL));   /* OPT */  r31 = r2;
  r3 = _mm256_load_ps((const float *)(p0+289520LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+843744LL));
  r6 +=  r0;
  *(M *)(p0+843744LL) = r6;   /* OPT */  r35 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r39 = r0;
  r1 = _mm256_load_ps((const float *)(p0+8272LL));
  r0 -=  r1;
  /* OPT */  r2 = r36;
  /* OPT */  r3 = r36;
  r4 = _mm256_load_ps((const float *)(p0+562504LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1124992LL));
  r6 +=  r0;
  *(M *)(p0+1124992LL) = r6;   /* OPT */  r37 = r6;
  /* OPT */  r0 = r31;
  /* OPT */  r1 = r31;
  r4 = _mm256_load_ps((const float *)(p0+281256LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r39;
  r3 = _mm256_load_ps((const float *)(p0+88LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1406240LL));
  r6 +=  r0;
  *(M *)(p0+1406240LL) = r6;   /* OPT */  r43 = r6;
  /* OPT */  r0 = r37;
  /* OPT */  r1 = r37;
  r4 = _mm256_load_ps((const float *)(p0+1124984LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  r3 = _mm256_load_ps((const float *)(p0+843656LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r36;
  r6 +=  r0;
  *(M *)(p0+562496LL) = r6;
  /* OPT */  r0 = r35;
  r1 = _mm256_load_ps((const float *)(p0+835472LL));
  r0 -=  r1;
  /* OPT */  r2 = r43;
  /* OPT */  r3 = r43;
  r4 = _mm256_load_ps((const float *)(p0+1406232LL));
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
  *(M *)(p0+281248LL) = r6;
  /* OPT */  r0 = r43;
  r1 = _mm256_load_ps((const float *)(p0+1406152LL));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  r3 = _mm256_load_ps((const float *)(p0+1116720LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r39;
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
         yee_0_0_0_0(88,0,a0,a1,a1,a1);
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
  
  r0 = _mm256_load_ps((const float *)(p0+579040LL));   /* OPT */  r35 = r0;
  r1 = _mm256_load_ps((const float *)(p0+579128LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+289520LL));   /* OPT */  r29 = r2;
  r3 = _mm256_load_ps((const float *)(p0+297792LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+868560LL));
  r6 +=  r0;
  *(M *)(p0+868560LL) = r6;   /* OPT */  r26 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r37 = r0;
  r1 = _mm256_load_ps((const float *)(p0+8272LL));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  /* OPT */  r3 = r35;
  r4 = _mm256_load_ps((const float *)(p0+579048LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1158080LL));
  r6 +=  r0;
  *(M *)(p0+1158080LL) = r6;   /* OPT */  r34 = r6;
  /* OPT */  r0 = r29;
  /* OPT */  r1 = r29;
  r4 = _mm256_load_ps((const float *)(p0+289528LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  r3 = _mm256_load_ps((const float *)(p0+88LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1447600LL));
  r6 +=  r0;
  *(M *)(p0+1447600LL) = r6;   /* OPT */  r42 = r6;
  /* OPT */  r0 = r34;
  /* OPT */  r1 = r34;
  r4 = _mm256_load_ps((const float *)(p0+1158072LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r26;
  r3 = _mm256_load_ps((const float *)(p0+868472LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r35;
  r6 +=  r0;
  *(M *)(p0+579040LL) = r6;
  /* OPT */  r0 = r26;
  r1 = _mm256_load_ps((const float *)(p0+860288LL));
  r0 -=  r1;
  /* OPT */  r2 = r42;
  /* OPT */  r3 = r42;
  r4 = _mm256_load_ps((const float *)(p0+1447592LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r29;
  r6 +=  r0;
  *(M *)(p0+289520LL) = r6;
  /* OPT */  r0 = r42;
  r1 = _mm256_load_ps((const float *)(p0+1447512LL));
  r0 -=  r1;
  /* OPT */  r2 = r34;
  r3 = _mm256_load_ps((const float *)(p0+1149808LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r37;
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
         yee_0_0_1_1(88,0,a0,a1,a1,a1);
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
  
  r0 = _mm256_load_ps((const float *)(p0+568480LL));   /* OPT */  r35 = r0;
  r1 = _mm256_load_ps((const float *)(p0+568568LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+284240LL));   /* OPT */  r26 = r2;
  r3 = _mm256_load_ps((const float *)(p0+292600LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+852720LL));
  r6 +=  r0;
  *(M *)(p0+852720LL) = r6;   /* OPT */  r29 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r30 = r0;
  r1 = _mm256_load_ps((const float *)(p0+8360LL));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  /* OPT */  r3 = r35;
  r4 = _mm256_load_ps((const float *)(p0+568488LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1136960LL));
  r6 +=  r0;
  *(M *)(p0+1136960LL) = r6;   /* OPT */  r38 = r6;
  /* OPT */  r0 = r26;
  /* OPT */  r1 = r26;
  r4 = _mm256_load_ps((const float *)(p0+284248LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r30;
  r3 = _mm256_load_ps((const float *)(p0+88LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1421200LL));
  r6 +=  r0;
  *(M *)(p0+1421200LL) = r6;   /* OPT */  r34 = r6;
  /* OPT */  r0 = r38;
  /* OPT */  r1 = r38;
  r4 = _mm256_load_ps((const float *)(p0+1136952LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r29;
  r3 = _mm256_load_ps((const float *)(p0+852632LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r35;
  r6 +=  r0;
  *(M *)(p0+568480LL) = r6;
  /* OPT */  r0 = r29;
  r1 = _mm256_load_ps((const float *)(p0+844360LL));
  r0 -=  r1;
  /* OPT */  r2 = r34;
  /* OPT */  r3 = r34;
  r4 = _mm256_load_ps((const float *)(p0+1421192LL));
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
  *(M *)(p0+284240LL) = r6;
  /* OPT */  r0 = r34;
  r1 = _mm256_load_ps((const float *)(p0+1421112LL));
  r0 -=  r1;
  /* OPT */  r2 = r38;
  r3 = _mm256_load_ps((const float *)(p0+1128600LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r30;
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
         yee_0_1_0_2(88,0,a0,a1,a1,a1);
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
  
  r0 = _mm256_load_ps((const float *)(p0+585200LL));   /* OPT */  r26 = r0;
  r1 = _mm256_load_ps((const float *)(p0+585288LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+292600LL));   /* OPT */  r40 = r2;
  r3 = _mm256_load_ps((const float *)(p0+300960LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+877800LL));
  r6 +=  r0;
  *(M *)(p0+877800LL) = r6;   /* OPT */  r30 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r28 = r0;
  r1 = _mm256_load_ps((const float *)(p0+8360LL));
  r0 -=  r1;
  /* OPT */  r2 = r26;
  /* OPT */  r3 = r26;
  r4 = _mm256_load_ps((const float *)(p0+585208LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1170400LL));
  r6 +=  r0;
  *(M *)(p0+1170400LL) = r6;   /* OPT */  r31 = r6;
  /* OPT */  r0 = r40;
  /* OPT */  r1 = r40;
  r4 = _mm256_load_ps((const float *)(p0+292608LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r28;
  r3 = _mm256_load_ps((const float *)(p0+88LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1463000LL));
  r6 +=  r0;
  *(M *)(p0+1463000LL) = r6;   /* OPT */  r32 = r6;
  /* OPT */  r0 = r31;
  /* OPT */  r1 = r31;
  r4 = _mm256_load_ps((const float *)(p0+1170392LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r30;
  r3 = _mm256_load_ps((const float *)(p0+877712LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r26;
  r6 +=  r0;
  *(M *)(p0+585200LL) = r6;
  /* OPT */  r0 = r30;
  r1 = _mm256_load_ps((const float *)(p0+869440LL));
  r0 -=  r1;
  /* OPT */  r2 = r32;
  /* OPT */  r3 = r32;
  r4 = _mm256_load_ps((const float *)(p0+1462992LL));
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
  *(M *)(p0+292600LL) = r6;
  /* OPT */  r0 = r32;
  r1 = _mm256_load_ps((const float *)(p0+1462912LL));
  r0 -=  r1;
  /* OPT */  r2 = r31;
  r3 = _mm256_load_ps((const float *)(p0+1162040LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r28;
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
         yee_0_1_1_3(88,0,a0,a1,a1,a1);
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
  
  r0 = _mm256_load_ps((const float *)(p0+613632LL));   /* OPT */  r29 = r0;
  r1 = _mm256_load_ps((const float *)(p0+613728LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+306816LL));   /* OPT */  r34 = r2;
  r3 = _mm256_load_ps((const float *)(p0+315840LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+920448LL));
  r6 +=  r0;
  *(M *)(p0+920448LL) = r6;   /* OPT */  r31 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r37 = r0;
  r1 = _mm256_load_ps((const float *)(p0+9024LL));
  r0 -=  r1;
  /* OPT */  r2 = r29;
  /* OPT */  r3 = r29;
  r4 = _mm256_load_ps((const float *)(p0+613640LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1227264LL));
  r6 +=  r0;
  *(M *)(p0+1227264LL) = r6;   /* OPT */  r28 = r6;
  /* OPT */  r0 = r34;
  /* OPT */  r1 = r34;
  r4 = _mm256_load_ps((const float *)(p0+306824LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  r3 = _mm256_load_ps((const float *)(p0+96LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1534080LL));
  r6 +=  r0;
  *(M *)(p0+1534080LL) = r6;   /* OPT */  r26 = r6;
  /* OPT */  r0 = r28;
  /* OPT */  r1 = r28;
  r4 = _mm256_load_ps((const float *)(p0+1227256LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r31;
  r3 = _mm256_load_ps((const float *)(p0+920352LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r29;
  r6 +=  r0;
  *(M *)(p0+613632LL) = r6;
  /* OPT */  r0 = r31;
  r1 = _mm256_load_ps((const float *)(p0+911424LL));
  r0 -=  r1;
  /* OPT */  r2 = r26;
  /* OPT */  r3 = r26;
  r4 = _mm256_load_ps((const float *)(p0+1534072LL));
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
  *(M *)(p0+306816LL) = r6;
  /* OPT */  r0 = r26;
  r1 = _mm256_load_ps((const float *)(p0+1533984LL));
  r0 -=  r1;
  /* OPT */  r2 = r28;
  r3 = _mm256_load_ps((const float *)(p0+1218240LL));
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
         yee_8_0_0_4(88,0,a0,a1,a1,a1);
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
  
  r0 = _mm256_load_ps((const float *)(p0+631680LL));   /* OPT */  r30 = r0;
  r1 = _mm256_load_ps((const float *)(p0+631776LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+315840LL));   /* OPT */  r37 = r2;
  r3 = _mm256_load_ps((const float *)(p0+324864LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+947520LL));
  r6 +=  r0;
  *(M *)(p0+947520LL) = r6;   /* OPT */  r39 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r40 = r0;
  r1 = _mm256_load_ps((const float *)(p0+9024LL));
  r0 -=  r1;
  /* OPT */  r2 = r30;
  /* OPT */  r3 = r30;
  r4 = _mm256_load_ps((const float *)(p0+631688LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1263360LL));
  r6 +=  r0;
  *(M *)(p0+1263360LL) = r6;   /* OPT */  r43 = r6;
  /* OPT */  r0 = r37;
  /* OPT */  r1 = r37;
  r4 = _mm256_load_ps((const float *)(p0+315848LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r40;
  r3 = _mm256_load_ps((const float *)(p0+96LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1579200LL));
  r6 +=  r0;
  *(M *)(p0+1579200LL) = r6;   /* OPT */  r31 = r6;
  /* OPT */  r0 = r43;
  /* OPT */  r1 = r43;
  r4 = _mm256_load_ps((const float *)(p0+1263352LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r39;
  r3 = _mm256_load_ps((const float *)(p0+947424LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r30;
  r6 +=  r0;
  *(M *)(p0+631680LL) = r6;
  /* OPT */  r0 = r39;
  r1 = _mm256_load_ps((const float *)(p0+938496LL));
  r0 -=  r1;
  /* OPT */  r2 = r31;
  /* OPT */  r3 = r31;
  r4 = _mm256_load_ps((const float *)(p0+1579192LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r37;
  r6 +=  r0;
  *(M *)(p0+315840LL) = r6;
  /* OPT */  r0 = r31;
  r1 = _mm256_load_ps((const float *)(p0+1579104LL));
  r0 -=  r1;
  /* OPT */  r2 = r43;
  r3 = _mm256_load_ps((const float *)(p0+1254336LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r40;
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
         yee_8_0_1_5(88,0,a0,a1,a1,a1);
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
  
  r0 = _mm256_load_ps((const float *)(p0+620160LL));   /* OPT */  r29 = r0;
  r1 = _mm256_load_ps((const float *)(p0+620256LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+310080LL));   /* OPT */  r27 = r2;
  r3 = _mm256_load_ps((const float *)(p0+319200LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+930240LL));
  r6 +=  r0;
  *(M *)(p0+930240LL) = r6;   /* OPT */  r36 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r39 = r0;
  r1 = _mm256_load_ps((const float *)(p0+9120LL));
  r0 -=  r1;
  /* OPT */  r2 = r29;
  /* OPT */  r3 = r29;
  r4 = _mm256_load_ps((const float *)(p0+620168LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1240320LL));
  r6 +=  r0;
  *(M *)(p0+1240320LL) = r6;   /* OPT */  r34 = r6;
  /* OPT */  r0 = r27;
  /* OPT */  r1 = r27;
  r4 = _mm256_load_ps((const float *)(p0+310088LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r39;
  r3 = _mm256_load_ps((const float *)(p0+96LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1550400LL));
  r6 +=  r0;
  *(M *)(p0+1550400LL) = r6;   /* OPT */  r42 = r6;
  /* OPT */  r0 = r34;
  /* OPT */  r1 = r34;
  r4 = _mm256_load_ps((const float *)(p0+1240312LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r36;
  r3 = _mm256_load_ps((const float *)(p0+930144LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r29;
  r6 +=  r0;
  *(M *)(p0+620160LL) = r6;
  /* OPT */  r0 = r36;
  r1 = _mm256_load_ps((const float *)(p0+921120LL));
  r0 -=  r1;
  /* OPT */  r2 = r42;
  /* OPT */  r3 = r42;
  r4 = _mm256_load_ps((const float *)(p0+1550392LL));
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
  *(M *)(p0+310080LL) = r6;
  /* OPT */  r0 = r42;
  r1 = _mm256_load_ps((const float *)(p0+1550304LL));
  r0 -=  r1;
  /* OPT */  r2 = r34;
  r3 = _mm256_load_ps((const float *)(p0+1231200LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r39;
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
         yee_8_1_0_6(88,0,a0,a1,a1,a1);
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
  
  r0 = _mm256_load_ps((const float *)(p0+638400LL));   /* OPT */  r30 = r0;
  r1 = _mm256_load_ps((const float *)(p0+638496LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+319200LL));   /* OPT */  r38 = r2;
  r3 = _mm256_load_ps((const float *)(p0+328320LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+957600LL));
  r6 +=  r0;
  *(M *)(p0+957600LL) = r6;   /* OPT */  r35 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r39 = r0;
  r1 = _mm256_load_ps((const float *)(p0+9120LL));
  r0 -=  r1;
  /* OPT */  r2 = r30;
  /* OPT */  r3 = r30;
  r4 = _mm256_load_ps((const float *)(p0+638408LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r24;
  r6 = _mm256_load_ps((const float *)(p0+1276800LL));
  r6 +=  r0;
  *(M *)(p0+1276800LL) = r6;   /* OPT */  r32 = r6;
  /* OPT */  r0 = r38;
  /* OPT */  r1 = r38;
  r4 = _mm256_load_ps((const float *)(p0+319208LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r39;
  r3 = _mm256_load_ps((const float *)(p0+96LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r25;
  r6 = _mm256_load_ps((const float *)(p0+1596000LL));
  r6 +=  r0;
  *(M *)(p0+1596000LL) = r6;   /* OPT */  r37 = r6;
  /* OPT */  r0 = r32;
  /* OPT */  r1 = r32;
  r4 = _mm256_load_ps((const float *)(p0+1276792LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  r3 = _mm256_load_ps((const float *)(p0+957504LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r30;
  r6 +=  r0;
  *(M *)(p0+638400LL) = r6;
  /* OPT */  r0 = r35;
  r1 = _mm256_load_ps((const float *)(p0+948480LL));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  /* OPT */  r3 = r37;
  r4 = _mm256_load_ps((const float *)(p0+1595992LL));
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
  *(M *)(p0+319200LL) = r6;
  /* OPT */  r0 = r37;
  r1 = _mm256_load_ps((const float *)(p0+1595904LL));
  r0 -=  r1;
  /* OPT */  r2 = r32;
  r3 = _mm256_load_ps((const float *)(p0+1267680LL));
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
         yee_8_1_1_7(88,0,a0,a1,a1,a1);
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
        
