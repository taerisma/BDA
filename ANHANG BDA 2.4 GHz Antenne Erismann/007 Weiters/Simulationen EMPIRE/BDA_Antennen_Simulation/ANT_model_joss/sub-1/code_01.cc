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
static void output_it1(long nt,int x0,int x1,int n,float *f,float *wgt,float *norm,float *dummy) {
  #undef LONG
  #define LONG int
  LONG *ip  = (LONG *)norm;
  float *wp = wgt;
  float vv=0; int n0=0;
  //printf("OUTPUT it1 ip %ld %ld\n",ip[0],ip[2]);
  for(;n;n--,ip+=2,wp++) if( ip[0] >= x0 && ip[0] < x1 ) {
       //printf("OUTPUT it1 ip[0] %d x0 %d x1 %d\n",ip[0],x0,x1);
       n0++; vv += f[ip[1]]*wp[0];
   }
  
  #undef  NC
  #define NC 11
  static long cnt[NC]; static float val[NC]; static int init=0,prepend=1,add_ts=0; static FILE *fp=0; static char buf[30];
  if( !init ) {init = 1; memset(cnt,0,sizeof(cnt)); memset(val,0,sizeof(val)); }
  
  long nts = nt/53;
  cnt[nts%NC] += n0;
  val[nts%NC] += vv;
  if(cnt[nts%NC] >= 14) {
    cnt[nts%NC] = 0;  float v = val[nts%NC]; val[nts%NC] = 0; 
  if(fp == NULL) { fp = fopen("it1","w"); setvbuf(fp,buf,_IOLBF,30); }
  if (prepend) { prepend = 0; fprintf(fp,"%.17e\n",0.0); }
  fprintf(fp,"%.15e\n",v);
  fflush(fp);
  }}
static void output_it2(long nt,int x0,int x1,int n,float *f,float *wgt,float *norm,float *dummy) {
  #undef LONG
  #define LONG int
  LONG *ip  = (LONG *)norm;
  float *wp = wgt;
  float vv=0; int n0=0;
  //printf("OUTPUT it2 ip %ld %ld\n",ip[0],ip[2]);
  for(;n;n--,ip+=2,wp++) if( ip[0] >= x0 && ip[0] < x1 ) {
       //printf("OUTPUT it2 ip[0] %d x0 %d x1 %d\n",ip[0],x0,x1);
       n0++; vv += f[ip[1]]*wp[0];
   }
  
  #undef  NC
  #define NC 11
  static long cnt[NC]; static float val[NC]; static int init=0,prepend=1,add_ts=0; static FILE *fp=0; static char buf[30];
  if( !init ) {init = 1; memset(cnt,0,sizeof(cnt)); memset(val,0,sizeof(val)); }
  
  long nts = nt/53;
  cnt[nts%NC] += n0;
  val[nts%NC] += vv;
  if(cnt[nts%NC] >= 12) {
    cnt[nts%NC] = 0;  float v = val[nts%NC]; val[nts%NC] = 0; 
  if(fp == NULL) { fp = fopen("it2","w"); setvbuf(fp,buf,_IOLBF,30); }
  if (prepend) { prepend = 0; fprintf(fp,"%.17e\n",0.0); }
  fprintf(fp,"%.15e\n",v);
  fflush(fp);
  }}
  
static void output_ut1(long nt,int x0,int x1,int n,float *f,float *wgt,float *norm,float *dummy) {
  #undef LONG
  #define LONG int
  LONG *ip  = (LONG *)norm;
  float *wp = wgt;
  float vv=0; int n0=0;
  //printf("OUTPUT ut1 ip %ld %ld\n",ip[0],ip[2]);
  for(;n;n--,ip+=2,wp++) if( ip[0] >= x0 && ip[0] < x1 ) {
       //printf("OUTPUT ut1 ip[0] %d x0 %d x1 %d\n",ip[0],x0,x1);
       n0++; vv += f[ip[1]]*wp[0];
   }
  
  #undef  NC
  #define NC 11
  static long cnt[NC]; static float val[NC]; static int init=0,prepend=1,add_ts=0; static FILE *fp=0; static char buf[30];
  if( !init ) {init = 1; memset(cnt,0,sizeof(cnt)); memset(val,0,sizeof(val)); }
  
  long nts = nt/53;
  cnt[nts%NC] += n0;
  val[nts%NC] += vv;
  if(cnt[nts%NC] >= 5) {
    cnt[nts%NC] = 0;  float v = val[nts%NC]; val[nts%NC] = 0; 
  if(fp == NULL) { fp = fopen("ut1","w"); setvbuf(fp,buf,_IOLBF,30); }
  if (prepend) { prepend = 0; fprintf(fp,"%.17e\n",0.0); }
  fprintf(fp,"%.15e\n",v);
  fflush(fp);
  }}
  
static void output_ut2(long nt,int x0,int x1,int n,float *f,float *wgt,float *norm,float *dummy) {
  #undef LONG
  #define LONG int
  LONG *ip  = (LONG *)norm;
  float *wp = wgt;
  float vv=0; int n0=0;
  //printf("OUTPUT ut2 ip %ld %ld\n",ip[0],ip[2]);
  for(;n;n--,ip+=2,wp++) if( ip[0] >= x0 && ip[0] < x1 ) {
       //printf("OUTPUT ut2 ip[0] %d x0 %d x1 %d\n",ip[0],x0,x1);
       n0++; vv += f[ip[1]]*wp[0];
   }
  
  #undef  NC
  #define NC 11
  static long cnt[NC]; static float val[NC]; static int init=0,prepend=1,add_ts=0; static FILE *fp=0; static char buf[30];
  if( !init ) {init = 1; memset(cnt,0,sizeof(cnt)); memset(val,0,sizeof(val)); }
  
  long nts = nt/53;
  cnt[nts%NC] += n0;
  val[nts%NC] += vv;
  if(cnt[nts%NC] >= 4) {
    cnt[nts%NC] = 0;  float v = val[nts%NC]; val[nts%NC] = 0; 
  if(fp == NULL) { fp = fopen("ut2","w"); setvbuf(fp,buf,_IOLBF,30); }
  if (prepend) { prepend = 0; fprintf(fp,"%.17e\n",0.0); }
  fprintf(fp,"%.15e\n",v);
  fflush(fp);
  }}
float              * yee_a0;
int               yee_jobs = 2;
  int               yee_act_strat = 0;
  int               yee_act_multi = 0;
pthread_mutexattr_t yee_mattr;
  pthread_mutex_t yee_lock_00000;
  pthread_mutex_t yee_lock_00001;
  pthread_mutex_t yee_lock_00002;
  pthread_mutex_t yee_lock_00003;
  pthread_mutex_t yee_lock_00004;
  pthread_mutex_t yee_lock_00005;
  pthread_mutex_t yee_lock_00006;
  pthread_mutex_t yee_lock_00007;
unsigned long long  yee_affinity[] = {3ULL,12ULL};
pthread_t         yee_ids[2];
  
static long long multi_scells[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	multi_n[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	multi_cells[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  static int  multies[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20},nmulties= 20,nstrat=4;
  static int  *startup_finished = (int *)0x000000001BBCA200LL;
  
  typedef struct {int idx,multi,strat; } MULTI;
  
  #define DBG_MULTI 1
   #define MULTI_INFO(idx,x) { int * mi = (int *)0x00000000022F5A00LL;  mi[idx] = x; }
   #define XZSIZE 78336
   #define CACHE_BY_CORE 2097152
   #define THREADS 2
   #define STRAT1_OK 0
   #define EXT_STRAT -1
    int strat1_ok = STRAT1_OK;
                       void calc_multi( MULTI * m )
                        {
#ifdef FORCE_STRAT
                            m->multi = FORCE_MULTI;
                            m->strat = FORCE_STRAT;
                            m->idx   = 0;
                            do_cpuclock       = 0;
#else


                            static int pass = 0,idx=-1,debug=DBG_MULTI;  static long long bst; 
                            extern int yee_jobs;  extern int strat1_ok;

                            if (nmulties*nstrat == 1)
                              {
                                  idx  = 0;
                                  pass = 1;
                              }
                            else 
                                   if (pass == 0 && ++idx == nmulties*nstrat) 
                                     {
                                        bst            = 0;
                                        pass           = 1;


                                        for(int i=0;i<nmulties*nstrat;i++)
                                         {
                                           int strat = i/nmulties;
                                           int mul   = i%nmulties;
                                           float bonus    = 1.;

                                           if (!strat1_ok && strat==1)
                                                continue;

                                           if ( EXT_STRAT != -1 && strat != EXT_STRAT )
                                                continue;

                                           if ( strat ==3 ) bonus = 0.95;


                                           double mcx = multi_cells[i];

                                           if (mcx*bonus > bst )
                                             {
                                                bst = (long long)(mcx*bonus);
                                                idx = i;
                                             }
                                         }

                                        *startup_finished = 1;
                                        do_cpuclock       = 0;

                                        if (debug) printf("\n"); 
                                        for(int i=0;debug && i<nmulties*nstrat;i++)
                                           {
                                                   if(i%nmulties==0) printf("\n");
                                                   int strat = i/nmulties,multi;
                                                   multi = multies [i%nmulties];
                                                   if (multi && multi_cells[i])
                                                       printf("  Strategy %2d multi %2d: %10ld MCells/s\n",strat,multi,(long)multi_cells[i]); 
                                           }

                                        int mlt;
                                        mlt = multies[idx%nmulties];
                                        if (debug) { printf("\nMultiple Timestep optimized to strategy %d ,multi %d\n",idx/nmulties,mlt);  fflush(stdout); }
                                     }

                              m-> idx   = idx;
                              m-> strat = idx/nmulties;
                              m-> multi = multies [idx%nmulties];


                              int skip_rest = 0;

                              if(  !strat1_ok && m->strat == 1)
                                 { calc_multi(m); return; }

                              if ( EXT_STRAT != -1 && m->strat != EXT_STRAT )
                                 { calc_multi(m); return; }


                              if (  m->multi > 5  )
                                {
                                   if (multi_cells[idx-1] < multi_cells[idx-2]*1.01 )
                                      skip_rest = 1;
                                }

                              if (idx%nmulties>1 && m->multi > 4 )
                                {
                                   for(int id1 = idx-1 ; id1%nmulties ; id1--)
                                      if( multi_cells[idx-1]*1.1 < multi_cells[id1-1])     
                                        { skip_rest = 1;  break; }
                                }

                              if (m->strat  >  0 && m->multi >= 5)  
                                  if(multi_cells[idx-1]*1.1 < multi_cells[(idx-1)%nmulties])
                                       skip_rest = 1;

                              if (m->strat  == 0 && m->multi <= 5)  skip_rest = 0;
                              if (m->strat  == 1 && m->multi <= 8)  skip_rest = 0;

                              if  (m->strat == 0 ) {
                                  int xz_in_cache = CACHE_BY_CORE / XZSIZE;

                                  if (xz_in_cache < 5 || xz_in_cache < m->multi+2)
                                        skip_rest = 1;
                              }

                              if  (m->strat == 1 ) {
                                  int xz_in_cache = (THREADS*CACHE_BY_CORE) / XZSIZE;

                                  if (xz_in_cache < 10 || xz_in_cache < m->multi + 2) skip_rest = 1;
                                  if (m->multi == 1 )  { calc_multi(m); return; }
                              }

                             if  (m->strat > 1 && EXT_STRAT==-1 )  {
                                  int nzmin = m->multi * m->strat + m->multi * yee_jobs + 1;  extern int yee_NZ;

                                  if( yee_NZ < nzmin ) skip_rest = 1;
                              }

                              if (pass != 0                      )  skip_rest = 0;
                              if (skip_rest)
                                        {
                                             idx -= idx%nmulties;
                                             idx += nmulties-1;
                                             calc_multi(m);
                                        }

                              if (!m->multi)
                                   { calc_multi(m); return; }

                              yee_act_strat = m->strat;
                              yee_act_multi = m->multi;


                              //printf("MUL %d STRAT %d\n",m->multi,m->strat);

                              MULTI_INFO(0,m->strat);
                              MULTI_INFO(1,m->multi);
#endif
                        }
                
  
void multi_statistics(MULTI *m)                   
{                                                                   
     float *timing =  (float *)0x0000000013E8A340LL;
     double *acct  =  (double *)0x0000000013E31EC0LL;
     int multi = m->idx;
     float cs = 0,tg =0,cg = 0;
        for(int i=0;i<2;i++) {
            cg += timing[2*i]; tg += timing[2*i+1]; timing[2*i] = timing[2*i+1] = 0; 
            tg += acct[8*i]; acct[8*i]=0;
   }
     cs = cg/tg*2;                                           
     multi_n[multi]     += 1;                                 
     multi_scells[multi]+= (long long)(cs/1e6+0.5);                   
     multi_cells[multi]  = multi_scells[multi] / multi_n[multi]; 
}
  
  
  
  typedef union { char dummy[64];  struct { pthread_spinlock_t l;  volatile unsigned long t; } U; } ELOCK;
  #define YZ(y,z)  ((34LL*(y) + z))
  #define NYZ      (3230LL)
typedef void YEEFUN (int n,int n0,float *f,float *c,float *spc,float *norms);
int               yee_NZ = 34;
ELOCK *yee_YZ_lock;
volatile int      yee_i0;
int               yee_NY = 95;
int               yee_imax;
int               yee_running;
int               yee_booted;
MULTI             yee_multi;
pthread_mutex_t   yee_data_lock;
pthread_mutex_t   yee_msg_lock;
pthread_mutex_t   yee_boot_lock;
pthread_cond_t    yee_start_stepping;
pthread_cond_t    yee_stepping_finished;
pthread_mutex_t   yee_Y_lock[95][2][2];
int               yee_Y_wait[2][2];
  pthread_mutex_t   yee_job_lock[3];
  pthread_mutex_t   yee_strat1_lock[3];
  int yee_nzs[] = {16,18};
  int yee_zint[2][2];
  void balance_jobs(int steps) {
                          float rel[2],sum=0;   static int max_chg = 5;   int nchg = 0;   static int imx_l=-1,imi_l=-1;  static float wait_l=0;  float wait;

                          for(int i=0;i<yee_jobs;i++)
                             {
                                rel[i] = yee_Y_wait[i][0] + yee_Y_wait[i][1];
                                sum   += rel[i];
                             }

                          if (!sum) return;

                          wait = sum/steps;

                          for(int i=0;i<yee_jobs;i++)
                                rel[i] /= sum;

                          int things_done = 1;

                          if (max_chg > 1 ) 
                                max_chg--;

                          while( things_done ) 
                            {
                              things_done = 0;
                              float mx=-1e10,mi=1e10; int imx=-1,imi=-1;
                              for(int i=0;i<yee_jobs;i++)
                                 {
                                    if(!rel[i]) continue;
                                    if(rel[i] > mx ) { mx = rel[i]; imx = i; }
                                    if(rel[i] < mi ) { mi = rel[i]; imi = i; }
                                 }

                              // printf("balance sum %e mi %f mx %f imi %d imx %d\n",wait,mi,mx,imi,imx);

                              if ((mi==0.0 || mx/mi > 2.0) && imi != -1 && imx != -1 && yee_nzs[imi] > 1)
                                 {
                                    if( imx_l == imi && imi_l == imx && wait < wait_l)
                                       continue;
                                    yee_nzs[imi]--;
                                    yee_nzs[imx]++;
                                    rel[imi] = 0;
                                    rel[imx] = 0;

                                    if( ++nchg  < max_chg )
                                        things_done = 1;
                                    //printf("BALANCE up %d down %d\n",imx,imi);
                                    imx_l  = imx;
                                    imi_l  = imi;
                                    wait_l = wait;
                                 }

                            }
                              //for(int i=0;i<yee_jobs;i++)
                        //          printf("BALANCE %d %d\n",i,yee_nzs[i]);
                         //     printf("\n");
                    }
  
                      void calc_zint(void) {
                        int z=0;
                        strat1_ok = STRAT1_OK;
                        for(int i=0;i<yee_jobs;i++)
                           {
                                //printf("calc_zint %d %d\n",i,yee_nzs[i]);
                                yee_zint[i][0] = z;
                                z += yee_nzs[i];
                                if (yee_nzs[i]<1) strat1_ok = 0;
                                yee_zint[i][1] = z;
                           }
                    }
  #define ACCT_D(_j,_i) (((double *)0x0000000013E31EC0LL)[(_j)*8+(_i)])
  #define ACCT(i) { long long  t1; CPUCLOCK(t1); if( t1> t0 ) { ACCT_D(jobid,i) += (t1-t0)*3.855050115651504e-10; } t0=t1; }
  #define IS_P4 0
void * yee_thread( void *data )                            
   {  
  _mm_setcsr(0x9fc0);
    long jobid = (long) (long long) data; 
  SetThreadAffinityMask(GetCurrentThread(),(DWORD_PTR)yee_affinity[jobid]); int take_right_job=1;
                
                     long long t0,t1;
                     pthread_mutex_lock(&yee_msg_lock);
                     yee_booted += 1;
                     if (yee_booted == yee_jobs )
                         pthread_mutex_unlock(&yee_boot_lock);


                     while(1)  
                       {          // Condition Loop
                          CPUCLOCK(t0);

                          pthread_cond_wait(&yee_start_stepping,&yee_msg_lock);
                          pthread_mutex_unlock(&yee_msg_lock);

                          if (yee_multi.strat == 1)   // Strat    1
                           {
                                    if (jobid == 0)                         // Job 0 inhibits others
                                       {
                                         for(int i=1;i<yee_jobs;i++)
                                            for(int y=0;y<yee_NY;y++)
                                               pthread_mutex_trylock(&yee_Y_lock[y][i][0]);

                                         for(int i=1;i<yee_jobs;i++)
                                               pthread_mutex_unlock(yee_job_lock+i);
                                       }
                                    else
                                         pthread_mutex_lock(yee_job_lock+jobid);
                           }
                          else
                           {
                                    if (jobid == 0)                         // Avoid Deadlock
                                       pthread_mutex_unlock(yee_job_lock);
                           }

                          int multi = yee_multi.multi;
                          int imax  = yee_imax;
                          int strat = yee_multi.strat;


                          if (strat == 1)
                             while(1)
                              {    // Strat 1 Loop
                                    if (jobid != 0 )
                                        pthread_mutex_lock(yee_strat1_lock+jobid);

                                    pthread_mutex_lock(&yee_data_lock); 
                                    int i0    = yee_i0;
                                    pthread_mutex_unlock(yee_strat1_lock+((jobid+1)%yee_jobs));

                                    if (i0==imax) {                            
                                        pthread_mutex_unlock(&yee_data_lock);
                                        pthread_mutex_lock(&yee_msg_lock);
                                        if( --yee_running == 0)
                                            pthread_cond_broadcast(&yee_stepping_finished);
                                        break;
                                    }

                                    if (i0+multi > imax)
                                        multi  = imax-i0;

                                    pthread_mutex_unlock(&yee_data_lock); 

                                    extern void yee_h2e(int,int,int,int,int);

                                    
                                    ACCT(0);
                                    yee_h2e(i0,i0+multi,multi,yee_multi.strat,jobid);
                                    ACCT(1);

                                    if ( jobid == 0 )
                                        {
                                           pthread_mutex_lock(yee_strat1_lock);
                                           pthread_mutex_lock(&yee_data_lock); 
                                           yee_i0       = i0+multi;
                                           pthread_mutex_unlock(&yee_data_lock); 
                                        }
                            }    // Strat 1 Loop
                         else
                           while(1)
                            {    // Strat != 1 Loop
                                    CPUCLOCK(t0);
                                    pthread_mutex_lock(yee_job_lock+jobid);
                                    ACCT(0);
                                    pthread_mutex_lock(&yee_data_lock);

                                    int mymult = multi;

                                    if (yee_jobs == 8 && ! IS_P4 && strat == 0 && multi >= 4 )
                                       {
                                          mymult -= 2;
                                          if( jobid == 1 )  mymult += 1;
                                          if( jobid == 3 )  mymult += 2;
                                          if( jobid == 5 )  mymult += 2;
                                          if( jobid == 7 )  mymult += 1;
                                       }

                                    #ifdef MULTI_0
                                    if (jobid == 0)  mymult = MULTI_0;
                                    #endif


                                    int i0    = yee_i0;

                                    if (i0==imax) {
                                        pthread_mutex_unlock(&yee_data_lock);
                                        pthread_mutex_unlock(yee_job_lock+(1+jobid)%yee_jobs);
                                        pthread_mutex_lock(&yee_msg_lock);
                                        if( --yee_running == 0)
                                            pthread_cond_broadcast(&yee_stepping_finished);
                                        break;
                                    }
                                    if (i0+mymult > imax)
                                        mymult  = imax-i0;

                                    yee_i0 = i0+mymult;
                                    pthread_mutex_unlock(&yee_data_lock);

                                    extern void yee_h2e(int,int,int,int,int);
                                    CPUCLOCK(t0);
                                    yee_h2e(i0,i0+mymult,mymult,yee_multi.strat,jobid);
                                    ACCT(1);
                            }    // Strat != 1 Loop
                      }  // Condition Loop

                        return 0;
                    }
  
static inline void chksum(long nt,int x0,int x1,int n,float *f,float *wgt,float *space,float *dummy)
  {
      int   *ntmax   = (int   *)0x00000000022F5F00LL;
      float *storage = (float *)0x000000001BB100C0LL;
      int   pos      = ((nt/53)%11);
      float *act     = storage + 2*8*pos;
      size_t o0      = *(size_t *)wgt;
      if (*ntmax  < nt)  memset((char *)act,0,2*8*sizeof(float));
      if(nt > *ntmax) *ntmax = nt;
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r0 = _mm256_load_ps((const float *)(act+0LL));
  r1 = _mm256_load_ps((const float *)(act+8LL));
  {

  float * p0 = f + o0 + x0 + 0/8*8;
  
  for(long64 i=x1-x0;i>0;i-=8,p0 += 8) {
  
  r2 = _mm256_load_ps((const float *)(p0+0LL));
  r2 *=  r2;
  r0 +=  r2;
  r2 = _mm256_load_ps((const float *)(p0+930240LL));
  r2 *=  r2;
  r1 +=  r2;
  r2 = _mm256_load_ps((const float *)(p0+310080LL));
  r2 *=  r2;
  r0 +=  r2;
  r2 = _mm256_load_ps((const float *)(p0+1240320LL));
  r2 *=  r2;
  r1 +=  r2;
  r2 = _mm256_load_ps((const float *)(p0+620160LL));
  r2 *=  r2;
  r0 +=  r2;
  r2 = _mm256_load_ps((const float *)(p0+1550400LL));
  r2 *=  r2;
  r1 +=  r2;
  
  }}

  *(M *)(act+0LL) = r0;
  *(M *)(act+8LL) = r1;
  }
  #undef LONG
  #define LONG int
  
static inline void excite_1(long nt,int x0,int x1,int n,float *f,float *wgt,float *norm,float *dummy)
 {
  #undef NC
  #define NC  90
  static int tmax=0;  static float cache[NC];  float val=0;  LONG * ip = (LONG *)norm; static FILE *fp=0;
  for (;nt >= tmax;tmax++) {
     int tsteps     = tmax-1;
  
     val      = expf(-3.857683256965041e+19f*(tsteps*3.459290688102856e-13f-5.462979407413064e-10f)*(tsteps*3.459290688102856e-13f-5.462979407413064e-10f));
  
     cache[tmax%NC] = val;
    if( tmax % 53 == 0) {
          if(fp == NULL) fp = fopen("et","w");
          fprintf(fp,"%.15e\n",val);
          fflush(fp);
     }
   }
   if( tmax - 1 - nt < NC ) {
    val = cache[ nt % NC ];
   } else {
      int tsteps     = nt-1;
  
      val  = expf(-3.857683256965041e+19f*(tsteps*3.459290688102856e-13f-5.462979407413064e-10f)*(tsteps*3.459290688102856e-13f-5.462979407413064e-10f));
  
  }
   for(;n--;wgt++,ip+=2) 
        if( ip[0] >= x0 && ip[0] < x1 ) { 
     f[ip[1]] += wgt[0]*val; 
   }
 }
  
static void dumpbox_1(long nt,int x0,int x1,int n,float *f,float *c,float *dummy_spc,float *dummy_norm) {
  float *p0 = (float *)0x000000001BE1A000LL;
  static int tmax=-1; int pos=0,needs_write=0;
  #undef  NC
  #define NC 90
  #undef  NF
  #define NF 1
  #undef  MN
  #define MN 8
  #undef  NS
  #define NS 53
  #undef  DP2
  #define DP2 88
  #undef CHK_AVG
  #define CHK_AVG 22
  #undef NCHK
  #define NCHK 8272LL
  #undef LOGFN
  #define LOGFN "emplane_1_chksum.log"
  double *conv_error =  (double *)0x0000000015A3C300LL;
  static pthread_mutex_t chk_lock[NC];
  static long64 nchk[NC];
  static float  chk[2][NC][MN] __attribute__((aligned(64)));
  static float  zero[MN] __attribute__((aligned(64)));
  static float  chk_mavg[3][CHK_AVG];
  static float  chk_avg[3];
  static int    started = 0;
  static int    chk_init = 0,chk_navg=0;
  if(!chk_init) {
  while(pthread_mutex_trylock(&yee_lock_00000));
  if (!chk_init) {  memset(nchk,0,sizeof(nchk)); memset(chk,0,sizeof(chk)); memset(zero,0,sizeof(zero)); memset(chk_mavg,0,sizeof(chk_mavg)); memset(chk_avg,0,sizeof(chk_avg)); for(int i=0;i<NC;i++) pthread_mutex_init(chk_lock+i,0); chk_init = 1; }
  pthread_mutex_unlock(&yee_lock_00000);
  }
  int chk_pos = (nt/NS)%NC;
  
  long64 *ip = (long64 *)c;
  volatile long64 *ts = (volatile long64 *)(ip+3);
  int      x00        = ip[2];
  int xA   = x00;      if(xA < x0) xA = x0;
  int xB   = x00+DP2;  if(xB > x1) xB = x1;
  int      n0 = xB - xA;
  if( n0 <= 0 ) return;
  int      xoff = xA - x00;
  float *coh,*sih,*coe,*sie;
  if( nt <= tmax &&  tmax - nt < NC ) { pos = MN*NF*(nt % NC); 
  coh = pos+(float *)0x000000001576F040LL;
  sih = pos+(float *)0x00000000022FE180LL;
  coe = pos+(float *)0x00000000022FD5C0LL;
  sie = pos+(float *)0x0000000015A27140LL;
  } else {
  while(pthread_mutex_trylock(&yee_lock_00000));
  *ts = nt;
  int new_tmax = tmax;
  if( nt > tmax            ) { pos = MN*NF*(nt % NC); needs_write = 1; new_tmax = nt; }
  else if ( tmax - nt < NC ) { pos = MN*NF*(nt % NC); needs_write = 0; }
  else                       { pos = MN*NF*(NC + 1);  needs_write = 1; }
  coh = pos+(float *)0x000000001576F040LL;
  sih = pos+(float *)0x00000000022FE180LL;
  coe = pos+(float *)0x00000000022FD5C0LL;
  sie = pos+(float *)0x0000000015A27140LL;
  if( needs_write) {
  
  float ch,ce,sh,se;
  ch = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.0)) ; sh = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.0));
  ce = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.5)) ; se = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.5));
  coh[0] = ch; sih[0] = sh; coe[0] = ce; sie[0] = se;
  coh[1] = ch; sih[1] = sh; coe[1] = ce; sie[1] = se;
  coh[2] = ch; sih[2] = sh; coe[2] = ce; sie[2] = se;
  coh[3] = ch; sih[3] = sh; coe[3] = ce; sie[3] = se;
  coh[4] = ch; sih[4] = sh; coe[4] = ce; sie[4] = se;
  coh[5] = ch; sih[5] = sh; coe[5] = ce; sie[5] = se;
  coh[6] = ch; sih[6] = sh; coe[6] = ce; sie[6] = se;
  coh[7] = ch; sih[7] = sh; coe[7] = ce; sie[7] = se;
  
  tmax = new_tmax;
  }
  pthread_mutex_unlock(&yee_lock_00000);
  }
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  float *pr,*pi,*pf;
  r5 = _mm256_load_ps((const float *)(zero+0LL));
  
  // fk = 0
  
  pr = p0+ip[1]+0LL+xoff; pi=pr+88;
  pf = f +ip[0]+0LL+xoff;
     for(int n=n0;n;pf+=8,pr+=8,pi+=8,n-=8) {
  r0 = _mm256_load_ps((const float *)(pf+0LL));
  r1 = _mm256_load_ps((const float *)(((float *)coe)+0LL));
  r2 = _mm256_load_ps((const float *)(((float *)sie)+0LL));
  r3 = _mm256_load_ps((const float *)(pr+0LL));
  r4 = _mm256_load_ps((const float *)(pi+0LL));
  r1 *=  r0;
  r2 *=  r0;
  r3 +=  r1;
  r4 +=  r2;
  *(M *)(pr+0LL) = r3;
  *(M *)(pi+0LL) = r4;
  r3 *=  r3;
  r4 *=  r4;
  r5 +=  r4;
  r5 +=  r3;
   }
  
  // fk = 1
  
  pr = p0+ip[1]+16544LL+xoff; pi=pr+88;
  pf = f +ip[0]+310080LL+xoff;
     for(int n=n0;n;pf+=8,pr+=8,pi+=8,n-=8) {
  r0 = _mm256_load_ps((const float *)(pf+0LL));
  r1 = _mm256_load_ps((const float *)(((float *)coe)+0LL));
  r2 = _mm256_load_ps((const float *)(((float *)sie)+0LL));
  r3 = _mm256_load_ps((const float *)(pr+0LL));
  r4 = _mm256_load_ps((const float *)(pi+0LL));
  r1 *=  r0;
  r2 *=  r0;
  r3 +=  r1;
  r4 +=  r2;
  *(M *)(pr+0LL) = r3;
  *(M *)(pi+0LL) = r4;
  r3 *=  r3;
  r4 *=  r4;
  r5 +=  r4;
  r5 +=  r3;
   }
  
  // fk = 2
  
  pr = p0+ip[1]+33088LL+xoff; pi=pr+88;
  pf = f +ip[0]+620160LL+xoff;
     for(int n=n0;n;pf+=8,pr+=8,pi+=8,n-=8) {
  r0 = _mm256_load_ps((const float *)(pf+0LL));
  r1 = _mm256_load_ps((const float *)(((float *)coe)+0LL));
  r2 = _mm256_load_ps((const float *)(((float *)sie)+0LL));
  r3 = _mm256_load_ps((const float *)(pr+0LL));
  r4 = _mm256_load_ps((const float *)(pi+0LL));
  r1 *=  r0;
  r2 *=  r0;
  r3 +=  r1;
  r4 +=  r2;
  *(M *)(pr+0LL) = r3;
  *(M *)(pi+0LL) = r4;
  r3 *=  r3;
  r4 *=  r4;
  r5 +=  r4;
  r5 +=  r3;
   }
  r6 = _mm256_load_ps((const float *)(zero+0LL));
  
  // fk = 3
  
  pr = p0+ip[1]+49632LL+xoff; pi=pr+88;
  pf = f +ip[0]+930240LL+xoff;
     for(int n=n0;n;pf+=8,pr+=8,pi+=8,n-=8) {
  r0 = _mm256_load_ps((const float *)(pf+0LL));
  r1 = _mm256_load_ps((const float *)(((float *)coh)+0LL));
  r2 = _mm256_load_ps((const float *)(((float *)sih)+0LL));
  r3 = _mm256_load_ps((const float *)(pr+0LL));
  r4 = _mm256_load_ps((const float *)(pi+0LL));
  r1 *=  r0;
  r2 *=  r0;
  r3 +=  r1;
  r4 +=  r2;
  *(M *)(pr+0LL) = r3;
  *(M *)(pi+0LL) = r4;
  r3 *=  r3;
  r4 *=  r4;
  r6 +=  r4;
  r6 +=  r3;
   }
  
  // fk = 4
  
  pr = p0+ip[1]+66176LL+xoff; pi=pr+88;
  pf = f +ip[0]+1240320LL+xoff;
     for(int n=n0;n;pf+=8,pr+=8,pi+=8,n-=8) {
  r0 = _mm256_load_ps((const float *)(pf+0LL));
  r1 = _mm256_load_ps((const float *)(((float *)coh)+0LL));
  r2 = _mm256_load_ps((const float *)(((float *)sih)+0LL));
  r3 = _mm256_load_ps((const float *)(pr+0LL));
  r4 = _mm256_load_ps((const float *)(pi+0LL));
  r1 *=  r0;
  r2 *=  r0;
  r3 +=  r1;
  r4 +=  r2;
  *(M *)(pr+0LL) = r3;
  *(M *)(pi+0LL) = r4;
  r3 *=  r3;
  r4 *=  r4;
  r6 +=  r4;
  r6 +=  r3;
   }
  
  // fk = 5
  
  pr = p0+ip[1]+82720LL+xoff; pi=pr+88;
  pf = f +ip[0]+1550400LL+xoff;
     for(int n=n0;n;pf+=8,pr+=8,pi+=8,n-=8) {
  r0 = _mm256_load_ps((const float *)(pf+0LL));
  r1 = _mm256_load_ps((const float *)(((float *)coh)+0LL));
  r2 = _mm256_load_ps((const float *)(((float *)sih)+0LL));
  r3 = _mm256_load_ps((const float *)(pr+0LL));
  r4 = _mm256_load_ps((const float *)(pi+0LL));
  r1 *=  r0;
  r2 *=  r0;
  r3 +=  r1;
  r4 +=  r2;
  *(M *)(pr+0LL) = r3;
  *(M *)(pi+0LL) = r4;
  r3 *=  r3;
  r4 *=  r4;
  r6 +=  r4;
  r6 +=  r3;
   }
  while(pthread_mutex_trylock(chk_lock + chk_pos));
  r7 = _mm256_load_ps((const float *)(chk[0][chk_pos]+0LL));
  r5 +=  r7;
  *(M *)(chk[0][chk_pos]+0LL) = r5;
  r8 = _mm256_load_ps((const float *)(chk[1][chk_pos]+0LL));
  r6 +=  r8;
  *(M *)(chk[1][chk_pos]+0LL) = r6;
  nchk[chk_pos] += n0;
  if (nchk[chk_pos] >= NCHK ) {
              nchk[chk_pos] = 0;
              float chks[2] = {0,0};

              for(int j=0;j<2;j++)
              for(int i=0;i<MN;i++)
                 { 
                    chks[j]            += chk[j][chk_pos][i];
                    chk[j][chk_pos][i] = 0;
                 }

              int avg = (chk_navg++)%CHK_AVG;

              chk_avg[0] -= chk_mavg[0][avg];
              chk_avg[0] += chk_mavg[0][avg] = chks[0];

              chk_avg[1] -= chk_mavg[1][avg];
              chk_avg[1] += chk_mavg[1][avg] = chks[1];

              float e_avg = chk_avg[0] / CHK_AVG;
              float h_avg = chk_avg[1] / CHK_AVG;

              float err_e = (chks[0] - e_avg) / (e_avg ? e_avg : 1.0);
              float err_h = (chks[1] - h_avg) / (h_avg ? h_avg : 1.0);

              if (err_e < 0) err_e = -err_e;
              if (err_h < 0) err_h = -err_h;

              float emax = err_e > err_h ? err_e : err_h;

              chk_avg[2] -= chk_mavg[2][avg];
              chk_avg[2] += chk_mavg[2][avg] = emax;

              float error = chk_avg[2] / CHK_AVG;

              if (error > 0.1)
                started = 1;

              if (!started ) 
                 error = 1;

              *conv_error = error;
              static const char *mode = "w";
              FILE *fp = fopen(LOGFN,mode);
              fprintf(fp,"%d %.15e\n",(int)nt,error);
              fclose(fp);

              mode = "a";
            }
            
  pthread_mutex_unlock(chk_lock + chk_pos);
  }
static void dumpbox_2(long nt,int x0,int x1,int n,float *f,float *c,float *dummy_spc,float *dummy_norm) {
  float *p0 = (float *)0x0000000014F70080LL;
  static int tmax=-1; int pos=0,needs_write=0;
  #undef  NC
  #define NC 90
  #undef  NF
  #define NF 1
  #undef  MN
  #define MN 8
  #undef  NS
  #define NS 53
  #undef  DP2
  #define DP2 56
  #undef CHK_AVG
  #define CHK_AVG 22
  #undef NCHK
  #define NCHK 86184LL
  #undef LOGFN
  #define LOGFN "emvolume_2_chksum.log"
  double *conv_error =  (double *)0x0000000015A3C480LL;
  static pthread_mutex_t chk_lock[NC];
  static long64 nchk[NC];
  static float  chk[2][NC][MN] __attribute__((aligned(64)));
  static float  zero[MN] __attribute__((aligned(64)));
  static float  chk_mavg[3][CHK_AVG];
  static float  chk_avg[3];
  static int    started = 0;
  static int    chk_init = 0,chk_navg=0;
  if(!chk_init) {
  while(pthread_mutex_trylock(&yee_lock_00001));
  if (!chk_init) {  memset(nchk,0,sizeof(nchk)); memset(chk,0,sizeof(chk)); memset(zero,0,sizeof(zero)); memset(chk_mavg,0,sizeof(chk_mavg)); memset(chk_avg,0,sizeof(chk_avg)); for(int i=0;i<NC;i++) pthread_mutex_init(chk_lock+i,0); chk_init = 1; }
  pthread_mutex_unlock(&yee_lock_00001);
  }
  int chk_pos = (nt/NS)%NC;
  
  long64 *ip = (long64 *)c;
  volatile long64 *ts = (volatile long64 *)(ip+3);
  int      x00        = ip[2];
  int xA   = x00;      if(xA < x0) xA = x0;
  int xB   = x00+DP2;  if(xB > x1) xB = x1;
  int      n0 = xB - xA;
  if( n0 <= 0 ) return;
  int      xoff = xA - x00;
  float *coh,*sih,*coe,*sie;
  if( nt <= tmax &&  tmax - nt < NC ) { pos = MN*NF*(nt % NC); 
  coh = pos+(float *)0x0000000015A28D00LL;
  sih = pos+(float *)0x0000000015A6B980LL;
  coe = pos+(float *)0x0000000015A6ADC0LL;
  sie = pos+(float *)0x0000000015A6C540LL;
  } else {
  while(pthread_mutex_trylock(&yee_lock_00001));
  *ts = nt;
  int new_tmax = tmax;
  if( nt > tmax            ) { pos = MN*NF*(nt % NC); needs_write = 1; new_tmax = nt; }
  else if ( tmax - nt < NC ) { pos = MN*NF*(nt % NC); needs_write = 0; }
  else                       { pos = MN*NF*(NC + 1);  needs_write = 1; }
  coh = pos+(float *)0x0000000015A28D00LL;
  sih = pos+(float *)0x0000000015A6B980LL;
  coe = pos+(float *)0x0000000015A6ADC0LL;
  sie = pos+(float *)0x0000000015A6C540LL;
  if( needs_write) {
  
  float ch,ce,sh,se;
  ch = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.0)) ; sh = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.0));
  ce = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.5)) ; se = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.5));
  coh[0] = ch; sih[0] = sh; coe[0] = ce; sie[0] = se;
  coh[1] = ch; sih[1] = sh; coe[1] = ce; sie[1] = se;
  coh[2] = ch; sih[2] = sh; coe[2] = ce; sie[2] = se;
  coh[3] = ch; sih[3] = sh; coe[3] = ce; sie[3] = se;
  coh[4] = ch; sih[4] = sh; coe[4] = ce; sie[4] = se;
  coh[5] = ch; sih[5] = sh; coe[5] = ce; sie[5] = se;
  coh[6] = ch; sih[6] = sh; coe[6] = ce; sie[6] = se;
  coh[7] = ch; sih[7] = sh; coe[7] = ce; sie[7] = se;
  
  tmax = new_tmax;
  }
  pthread_mutex_unlock(&yee_lock_00001);
  }
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  float *pr,*pi,*pf;
  r5 = _mm256_load_ps((const float *)(zero+0LL));
  
  // fk = 0
  
  pr = p0+ip[1]+0LL+xoff; pi=pr+56;
  pf = f +ip[0]+0LL+xoff;
     for(int n=n0;n;pf+=8,pr+=8,pi+=8,n-=8) {
  r0 = _mm256_load_ps((const float *)(pf+0LL));
  r1 = _mm256_load_ps((const float *)(((float *)coe)+0LL));
  r2 = _mm256_load_ps((const float *)(((float *)sie)+0LL));
  r3 = _mm256_load_ps((const float *)(pr+0LL));
  r4 = _mm256_load_ps((const float *)(pi+0LL));
  r1 *=  r0;
  r2 *=  r0;
  r3 +=  r1;
  r4 +=  r2;
  *(M *)(pr+0LL) = r3;
  *(M *)(pi+0LL) = r4;
  r3 *=  r3;
  r4 *=  r4;
  r5 +=  r4;
  r5 +=  r3;
   }
  
  // fk = 1
  
  pr = p0+ip[1]+172368LL+xoff; pi=pr+56;
  pf = f +ip[0]+310080LL+xoff;
     for(int n=n0;n;pf+=8,pr+=8,pi+=8,n-=8) {
  r0 = _mm256_load_ps((const float *)(pf+0LL));
  r1 = _mm256_load_ps((const float *)(((float *)coe)+0LL));
  r2 = _mm256_load_ps((const float *)(((float *)sie)+0LL));
  r3 = _mm256_load_ps((const float *)(pr+0LL));
  r4 = _mm256_load_ps((const float *)(pi+0LL));
  r1 *=  r0;
  r2 *=  r0;
  r3 +=  r1;
  r4 +=  r2;
  *(M *)(pr+0LL) = r3;
  *(M *)(pi+0LL) = r4;
  r3 *=  r3;
  r4 *=  r4;
  r5 +=  r4;
  r5 +=  r3;
   }
  
  // fk = 2
  
  pr = p0+ip[1]+344736LL+xoff; pi=pr+56;
  pf = f +ip[0]+620160LL+xoff;
     for(int n=n0;n;pf+=8,pr+=8,pi+=8,n-=8) {
  r0 = _mm256_load_ps((const float *)(pf+0LL));
  r1 = _mm256_load_ps((const float *)(((float *)coe)+0LL));
  r2 = _mm256_load_ps((const float *)(((float *)sie)+0LL));
  r3 = _mm256_load_ps((const float *)(pr+0LL));
  r4 = _mm256_load_ps((const float *)(pi+0LL));
  r1 *=  r0;
  r2 *=  r0;
  r3 +=  r1;
  r4 +=  r2;
  *(M *)(pr+0LL) = r3;
  *(M *)(pi+0LL) = r4;
  r3 *=  r3;
  r4 *=  r4;
  r5 +=  r4;
  r5 +=  r3;
   }
  r6 = _mm256_load_ps((const float *)(zero+0LL));
  
  // fk = 3
  
  pr = p0+ip[1]+517104LL+xoff; pi=pr+56;
  pf = f +ip[0]+930240LL+xoff;
     for(int n=n0;n;pf+=8,pr+=8,pi+=8,n-=8) {
  r0 = _mm256_load_ps((const float *)(pf+0LL));
  r1 = _mm256_load_ps((const float *)(((float *)coh)+0LL));
  r2 = _mm256_load_ps((const float *)(((float *)sih)+0LL));
  r3 = _mm256_load_ps((const float *)(pr+0LL));
  r4 = _mm256_load_ps((const float *)(pi+0LL));
  r1 *=  r0;
  r2 *=  r0;
  r3 +=  r1;
  r4 +=  r2;
  *(M *)(pr+0LL) = r3;
  *(M *)(pi+0LL) = r4;
  r3 *=  r3;
  r4 *=  r4;
  r6 +=  r4;
  r6 +=  r3;
   }
  
  // fk = 4
  
  pr = p0+ip[1]+689472LL+xoff; pi=pr+56;
  pf = f +ip[0]+1240320LL+xoff;
     for(int n=n0;n;pf+=8,pr+=8,pi+=8,n-=8) {
  r0 = _mm256_load_ps((const float *)(pf+0LL));
  r1 = _mm256_load_ps((const float *)(((float *)coh)+0LL));
  r2 = _mm256_load_ps((const float *)(((float *)sih)+0LL));
  r3 = _mm256_load_ps((const float *)(pr+0LL));
  r4 = _mm256_load_ps((const float *)(pi+0LL));
  r1 *=  r0;
  r2 *=  r0;
  r3 +=  r1;
  r4 +=  r2;
  *(M *)(pr+0LL) = r3;
  *(M *)(pi+0LL) = r4;
  r3 *=  r3;
  r4 *=  r4;
  r6 +=  r4;
  r6 +=  r3;
   }
  
  // fk = 5
  
  pr = p0+ip[1]+861840LL+xoff; pi=pr+56;
  pf = f +ip[0]+1550400LL+xoff;
     for(int n=n0;n;pf+=8,pr+=8,pi+=8,n-=8) {
  r0 = _mm256_load_ps((const float *)(pf+0LL));
  r1 = _mm256_load_ps((const float *)(((float *)coh)+0LL));
  r2 = _mm256_load_ps((const float *)(((float *)sih)+0LL));
  r3 = _mm256_load_ps((const float *)(pr+0LL));
  r4 = _mm256_load_ps((const float *)(pi+0LL));
  r1 *=  r0;
  r2 *=  r0;
  r3 +=  r1;
  r4 +=  r2;
  *(M *)(pr+0LL) = r3;
  *(M *)(pi+0LL) = r4;
  r3 *=  r3;
  r4 *=  r4;
  r6 +=  r4;
  r6 +=  r3;
   }
  while(pthread_mutex_trylock(chk_lock + chk_pos));
  r7 = _mm256_load_ps((const float *)(chk[0][chk_pos]+0LL));
  r5 +=  r7;
  *(M *)(chk[0][chk_pos]+0LL) = r5;
  r8 = _mm256_load_ps((const float *)(chk[1][chk_pos]+0LL));
  r6 +=  r8;
  *(M *)(chk[1][chk_pos]+0LL) = r6;
  nchk[chk_pos] += n0;
  if (nchk[chk_pos] >= NCHK ) {
              nchk[chk_pos] = 0;
              float chks[2] = {0,0};

              for(int j=0;j<2;j++)
              for(int i=0;i<MN;i++)
                 { 
                    chks[j]            += chk[j][chk_pos][i];
                    chk[j][chk_pos][i] = 0;
                 }

              int avg = (chk_navg++)%CHK_AVG;

              chk_avg[0] -= chk_mavg[0][avg];
              chk_avg[0] += chk_mavg[0][avg] = chks[0];

              chk_avg[1] -= chk_mavg[1][avg];
              chk_avg[1] += chk_mavg[1][avg] = chks[1];

              float e_avg = chk_avg[0] / CHK_AVG;
              float h_avg = chk_avg[1] / CHK_AVG;

              float err_e = (chks[0] - e_avg) / (e_avg ? e_avg : 1.0);
              float err_h = (chks[1] - h_avg) / (h_avg ? h_avg : 1.0);

              if (err_e < 0) err_e = -err_e;
              if (err_h < 0) err_h = -err_h;

              float emax = err_e > err_h ? err_e : err_h;

              chk_avg[2] -= chk_mavg[2][avg];
              chk_avg[2] += chk_mavg[2][avg] = emax;

              float error = chk_avg[2] / CHK_AVG;

              if (error > 0.1)
                started = 1;

              if (!started ) 
                 error = 1;

              *conv_error = error;
              static const char *mode = "w";
              FILE *fp = fopen(LOGFN,mode);
              fprintf(fp,"%d %.15e\n",(int)nt,error);
              fclose(fp);

              mode = "a";
            }
            
  pthread_mutex_unlock(chk_lock + chk_pos);
  }
static void ff_1_xmin(long nt,int x0,int x1,int n,float *f,float *c,float *dummy_spc,float *dumm_normy) {
  static int tmax=-1; int pos=0,needs_write=0;
  #undef  NC
  #define NC 90
  #undef  NF
  #define NF 1
  
  long64 *ip = (long64 *)c;
  int x00  = ip[3];
  int xA   = x00;      if(xA < x0) xA = x0;
  int xB   = x00+n;    if(xB > x1) xB = x1;
  int      n0 = xB - xA;
  if( n0 <= 0 ) return;
  int      xoff = xA - x00;
  float *p = (float *)0x0000000015A45B00LL,*pf,*pg;
  static float _coh[91],_sih[91],_coe[91],_sie[91];
  
  float *coh,*sih,*coe,*sie;
  if( nt <= tmax &&  tmax - nt < NC ) { 
                     pos = NF*(nt % NC); 
                     coh = pos+_coh;
                     sih = pos+_sih;
                     coe = pos+_coe;
                     sie = pos+_sie;
         } else {
  while(pthread_mutex_trylock(&yee_lock_00002));
  int new_tmax = tmax;
  if( nt > tmax            ) { pos = NF*(nt % NC); needs_write = 1;  new_tmax = nt; }
  else if ( tmax - nt < NC ) { pos = NF*(nt % NC); needs_write = 0; }
  else                       { pos = NF*NC;        needs_write = 1; }
  coh = pos+_coh;
  sih = pos+_sih;
  coe = pos+_coe;
  sie = pos+_sie;
  if( needs_write) {
  
  float ch,ce,sh,se;
  ch = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.0)) ; sh = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.0));
  ce = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.5)) ; se = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.5));
  coh[0] = ch; sih[0] = sh; coe[0] = ce; sie[0] = se;
  
  tmax = new_tmax;
  }
  pthread_mutex_unlock(&yee_lock_00002);
  }
  pf = f + ip[0] + 310080LL +xoff;      
  pg = p + ip[1] + 0LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.50*(pf[0]);
            pg[0] += coe[0]  * w;    pg[1] += sie[0] * w;
  }
  pf = f + ip[0] + 620160LL +xoff;      
  pg = p + ip[1] + 4128LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.50*(pf[0]);
            pg[0] += coe[0]  * w;    pg[1] += sie[0] * w;
  }
  pf = f + ip[0] + 1240320LL +xoff;      
  pg = p + ip[1] + 8256LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.25*(pf[0]+pf[-1]);
            pg[0] += coh[0]  * w;    pg[1] += sih[0] * w;
  }
  pf = f + ip[0] + 1550400LL +xoff;      
  pg = p + ip[1] + 12384LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.25*(pf[0]+pf[-1]);
            pg[0] += coh[0]  * w;    pg[1] += sih[0] * w;
  }
  }
  
static void ff_2_xmax(long nt,int x0,int x1,int n,float *f,float *c,float *dummy_spc,float *dumm_normy) {
  static int tmax=-1; int pos=0,needs_write=0;
  #undef  NC
  #define NC 90
  #undef  NF
  #define NF 1
  
  long64 *ip = (long64 *)c;
  int x00  = ip[3];
  int xA   = x00;      if(xA < x0) xA = x0;
  int xB   = x00+n;    if(xB > x1) xB = x1;
  int      n0 = xB - xA;
  if( n0 <= 0 ) return;
  int      xoff = xA - x00;
  float *p = (float *)0x000000001BB94D00LL,*pf,*pg;
  static float _coh[91],_sih[91],_coe[91],_sie[91];
  
  float *coh,*sih,*coe,*sie;
  if( nt <= tmax &&  tmax - nt < NC ) { 
                     pos = NF*(nt % NC); 
                     coh = pos+_coh;
                     sih = pos+_sih;
                     coe = pos+_coe;
                     sie = pos+_sie;
         } else {
  while(pthread_mutex_trylock(&yee_lock_00003));
  int new_tmax = tmax;
  if( nt > tmax            ) { pos = NF*(nt % NC); needs_write = 1;  new_tmax = nt; }
  else if ( tmax - nt < NC ) { pos = NF*(nt % NC); needs_write = 0; }
  else                       { pos = NF*NC;        needs_write = 1; }
  coh = pos+_coh;
  sih = pos+_sih;
  coe = pos+_coe;
  sie = pos+_sie;
  if( needs_write) {
  
  float ch,ce,sh,se;
  ch = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.0)) ; sh = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.0));
  ce = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.5)) ; se = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.5));
  coh[0] = ch; sih[0] = sh; coe[0] = ce; sie[0] = se;
  
  tmax = new_tmax;
  }
  pthread_mutex_unlock(&yee_lock_00003);
  }
  pf = f + ip[0] + 310080LL +xoff;      
  pg = p + ip[1] + 0LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.50*(pf[0]);
            pg[0] += coe[0]  * w;    pg[1] += sie[0] * w;
  }
  pf = f + ip[0] + 620160LL +xoff;      
  pg = p + ip[1] + 4128LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.50*(pf[0]);
            pg[0] += coe[0]  * w;    pg[1] += sie[0] * w;
  }
  pf = f + ip[0] + 1240320LL +xoff;      
  pg = p + ip[1] + 8256LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.25*(pf[0]+pf[-1]);
            pg[0] += coh[0]  * w;    pg[1] += sih[0] * w;
  }
  pf = f + ip[0] + 1550400LL +xoff;      
  pg = p + ip[1] + 12384LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.25*(pf[0]+pf[-1]);
            pg[0] += coh[0]  * w;    pg[1] += sih[0] * w;
  }
  }
  
static void ff_3_ymin(long nt,int x0,int x1,int n,float *f,float *c,float *dummy_spc,float *dumm_normy) {
  static int tmax=-1; int pos=0,needs_write=0;
  #undef  NC
  #define NC 90
  #undef  NF
  #define NF 1
  
  long64 *ip = (long64 *)c;
  int x00  = ip[3];
  int xA   = x00;      if(xA < x0) xA = x0;
  int xB   = x00+n;    if(xB > x1) xB = x1;
  int      n0 = xB - xA;
  if( n0 <= 0 ) return;
  int      xoff = xA - x00;
  float *p = (float *)0x0000000015A08D80LL,*pf,*pg;
  static float _coh[91],_sih[91],_coe[91],_sie[91];
  
  float *coh,*sih,*coe,*sie;
  if( nt <= tmax &&  tmax - nt < NC ) { 
                     pos = NF*(nt % NC); 
                     coh = pos+_coh;
                     sih = pos+_sih;
                     coe = pos+_coe;
                     sie = pos+_sie;
         } else {
  while(pthread_mutex_trylock(&yee_lock_00004));
  int new_tmax = tmax;
  if( nt > tmax            ) { pos = NF*(nt % NC); needs_write = 1;  new_tmax = nt; }
  else if ( tmax - nt < NC ) { pos = NF*(nt % NC); needs_write = 0; }
  else                       { pos = NF*NC;        needs_write = 1; }
  coh = pos+_coh;
  sih = pos+_sih;
  coe = pos+_coe;
  sie = pos+_sie;
  if( needs_write) {
  
  float ch,ce,sh,se;
  ch = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.0)) ; sh = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.0));
  ce = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.5)) ; se = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.5));
  coh[0] = ch; sih[0] = sh; coe[0] = ce; sie[0] = se;
  
  tmax = new_tmax;
  }
  pthread_mutex_unlock(&yee_lock_00004);
  }
  pf = f + ip[0] + 620160LL +xoff;      
  pg = p + ip[1] + 0LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.50*(pf[0]);
            pg[0] += coe[0]  * w;    pg[1] += sie[0] * w;
  }
  pf = f + ip[0] + 0LL +xoff;      
  pg = p + ip[1] + 3120LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.50*(pf[0]);
            pg[0] += coe[0]  * w;    pg[1] += sie[0] * w;
  }
  pf = f + ip[0] + 1550400LL +xoff;      
  pg = p + ip[1] + 6240LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.25*(pf[0]+pf[-96]);
            pg[0] += coh[0]  * w;    pg[1] += sih[0] * w;
  }
  pf = f + ip[0] + 930240LL +xoff;      
  pg = p + ip[1] + 9360LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.25*(pf[0]+pf[-96]);
            pg[0] += coh[0]  * w;    pg[1] += sih[0] * w;
  }
  }
  
static void ff_4_ymax(long nt,int x0,int x1,int n,float *f,float *c,float *dummy_spc,float *dumm_normy) {
  static int tmax=-1; int pos=0,needs_write=0;
  #undef  NC
  #define NC 90
  #undef  NF
  #define NF 1
  
  long64 *ip = (long64 *)c;
  int x00  = ip[3];
  int xA   = x00;      if(xA < x0) xA = x0;
  int xB   = x00+n;    if(xB > x1) xB = x1;
  int      n0 = xB - xA;
  if( n0 <= 0 ) return;
  int      xoff = xA - x00;
  float *p = (float *)0x0000000015A150C0LL,*pf,*pg;
  static float _coh[91],_sih[91],_coe[91],_sie[91];
  
  float *coh,*sih,*coe,*sie;
  if( nt <= tmax &&  tmax - nt < NC ) { 
                     pos = NF*(nt % NC); 
                     coh = pos+_coh;
                     sih = pos+_sih;
                     coe = pos+_coe;
                     sie = pos+_sie;
         } else {
  while(pthread_mutex_trylock(&yee_lock_00005));
  int new_tmax = tmax;
  if( nt > tmax            ) { pos = NF*(nt % NC); needs_write = 1;  new_tmax = nt; }
  else if ( tmax - nt < NC ) { pos = NF*(nt % NC); needs_write = 0; }
  else                       { pos = NF*NC;        needs_write = 1; }
  coh = pos+_coh;
  sih = pos+_sih;
  coe = pos+_coe;
  sie = pos+_sie;
  if( needs_write) {
  
  float ch,ce,sh,se;
  ch = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.0)) ; sh = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.0));
  ce = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.5)) ; se = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.5));
  coh[0] = ch; sih[0] = sh; coe[0] = ce; sie[0] = se;
  
  tmax = new_tmax;
  }
  pthread_mutex_unlock(&yee_lock_00005);
  }
  pf = f + ip[0] + 620160LL +xoff;      
  pg = p + ip[1] + 0LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.50*(pf[0]);
            pg[0] += coe[0]  * w;    pg[1] += sie[0] * w;
  }
  pf = f + ip[0] + 0LL +xoff;      
  pg = p + ip[1] + 3120LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.50*(pf[0]);
            pg[0] += coe[0]  * w;    pg[1] += sie[0] * w;
  }
  pf = f + ip[0] + 1550400LL +xoff;      
  pg = p + ip[1] + 6240LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.25*(pf[0]+pf[-96]);
            pg[0] += coh[0]  * w;    pg[1] += sih[0] * w;
  }
  pf = f + ip[0] + 930240LL +xoff;      
  pg = p + ip[1] + 9360LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.25*(pf[0]+pf[-96]);
            pg[0] += coh[0]  * w;    pg[1] += sih[0] * w;
  }
  }
  
static void ff_5_zmin(long nt,int x0,int x1,int n,float *f,float *c,float *dummy_spc,float *dumm_normy) {
  static int tmax=-1; int pos=0,needs_write=0;
  #undef  NC
  #define NC 90
  #undef  NF
  #define NF 1
  
  long64 *ip = (long64 *)c;
  int x00  = ip[3];
  int xA   = x00;      if(xA < x0) xA = x0;
  int xB   = x00+n;    if(xB > x1) xB = x1;
  int      n0 = xB - xA;
  if( n0 <= 0 ) return;
  int      xoff = xA - x00;
  float *p = (float *)0x000000001BC14F80LL,*pf,*pg;
  static float _coh[91],_sih[91],_coe[91],_sie[91];
  
  float *coh,*sih,*coe,*sie;
  if( nt <= tmax &&  tmax - nt < NC ) { 
                     pos = NF*(nt % NC); 
                     coh = pos+_coh;
                     sih = pos+_sih;
                     coe = pos+_coe;
                     sie = pos+_sie;
         } else {
  while(pthread_mutex_trylock(&yee_lock_00006));
  int new_tmax = tmax;
  if( nt > tmax            ) { pos = NF*(nt % NC); needs_write = 1;  new_tmax = nt; }
  else if ( tmax - nt < NC ) { pos = NF*(nt % NC); needs_write = 0; }
  else                       { pos = NF*NC;        needs_write = 1; }
  coh = pos+_coh;
  sih = pos+_sih;
  coe = pos+_coe;
  sie = pos+_sie;
  if( needs_write) {
  
  float ch,ce,sh,se;
  ch = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.0)) ; sh = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.0));
  ce = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.5)) ; se = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.5));
  coh[0] = ch; sih[0] = sh; coe[0] = ce; sie[0] = se;
  
  tmax = new_tmax;
  }
  pthread_mutex_unlock(&yee_lock_00006);
  }
  pf = f + ip[0] + 0LL +xoff;      
  pg = p + ip[1] + 0LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.50*(pf[0]);
            pg[0] += coe[0]  * w;    pg[1] += sie[0] * w;
  }
  pf = f + ip[0] + 310080LL +xoff;      
  pg = p + ip[1] + 11180LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.50*(pf[0]);
            pg[0] += coe[0]  * w;    pg[1] += sie[0] * w;
  }
  pf = f + ip[0] + 930240LL +xoff;      
  pg = p + ip[1] + 22360LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.25*(pf[0]+pf[-9120]);
            pg[0] += coh[0]  * w;    pg[1] += sih[0] * w;
  }
  pf = f + ip[0] + 1240320LL +xoff;      
  pg = p + ip[1] + 33540LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.25*(pf[0]+pf[-9120]);
            pg[0] += coh[0]  * w;    pg[1] += sih[0] * w;
  }
  }
  
static void ff_6_zmax(long nt,int x0,int x1,int n,float *f,float *c,float *dummy_spc,float *dumm_normy) {
  static int tmax=-1; int pos=0,needs_write=0;
  #undef  NC
  #define NC 90
  #undef  NF
  #define NF 1
  
  long64 *ip = (long64 *)c;
  int x00  = ip[3];
  int xA   = x00;      if(xA < x0) xA = x0;
  int xB   = x00+n;    if(xB > x1) xB = x1;
  int      n0 = xB - xA;
  if( n0 <= 0 ) return;
  int      xoff = xA - x00;
  float *p = (float *)0x000000001BBCB1C0LL,*pf,*pg;
  static float _coh[91],_sih[91],_coe[91],_sie[91];
  
  float *coh,*sih,*coe,*sie;
  if( nt <= tmax &&  tmax - nt < NC ) { 
                     pos = NF*(nt % NC); 
                     coh = pos+_coh;
                     sih = pos+_sih;
                     coe = pos+_coe;
                     sie = pos+_sie;
         } else {
  while(pthread_mutex_trylock(&yee_lock_00007));
  int new_tmax = tmax;
  if( nt > tmax            ) { pos = NF*(nt % NC); needs_write = 1;  new_tmax = nt; }
  else if ( tmax - nt < NC ) { pos = NF*(nt % NC); needs_write = 0; }
  else                       { pos = NF*NC;        needs_write = 1; }
  coh = pos+_coh;
  sih = pos+_sih;
  coe = pos+_coe;
  sie = pos+_sie;
  if( needs_write) {
  
  float ch,ce,sh,se;
  ch = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.0)) ; sh = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.0));
  ce = 1.833424064694514e-11*cos(-5.325164284064002e-03*(nt+0.5)) ; se = 1.833424064694514e-11*sin(-5.325164284064002e-03*(nt+0.5));
  coh[0] = ch; sih[0] = sh; coe[0] = ce; sie[0] = se;
  
  tmax = new_tmax;
  }
  pthread_mutex_unlock(&yee_lock_00007);
  }
  pf = f + ip[0] + 0LL +xoff;      
  pg = p + ip[1] + 0LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.50*(pf[0]);
            pg[0] += coe[0]  * w;    pg[1] += sie[0] * w;
  }
  pf = f + ip[0] + 310080LL +xoff;      
  pg = p + ip[1] + 11180LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.50*(pf[0]);
            pg[0] += coe[0]  * w;    pg[1] += sie[0] * w;
  }
  pf = f + ip[0] + 930240LL +xoff;      
  pg = p + ip[1] + 22360LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.25*(pf[0]+pf[-9120]);
            pg[0] += coh[0]  * w;    pg[1] += sih[0] * w;
  }
  pf = f + ip[0] + 1240320LL +xoff;      
  pg = p + ip[1] + 33540LL +xoff*ip[2];
  for(int nn=n0;nn--;pf++,pg+=ip[2])  {
  float w  = 0.25*(pf[0]+pf[-9120]);
            pg[0] += coh[0]  * w;    pg[1] += sih[0] * w;
  }
  }
  

static PyObject * m_0000(PyObject *self, PyObject *args) {


  return Py_None;
}

static PyObject * m_0001(PyObject *self, PyObject *args) {

  timeBeginPeriod(1);
  _mm_setcsr(0x9fc0);
  pthread_mutexattr_init(&yee_mattr);
  extern void init_locks(void);
  init_locks();
  pthread_mutex_init(&py_mutex,&yee_mattr);
  yee_YZ_lock = (ELOCK *)malloc( NYZ * sizeof( ELOCK ) );
  memset((void *)yee_YZ_lock,0,NYZ * sizeof( ELOCK) );
   pthread_win32_process_attach_np();
  pthread_mutexattr_settype(&yee_mattr,PTHREAD_MUTEX_FAST_NP);
  pthread_mutex_init(&yee_data_lock,&yee_mattr);
  pthread_mutex_init(&yee_msg_lock,&yee_mattr);
  pthread_mutex_init(&yee_boot_lock,&yee_mattr);
  pthread_cond_init(&yee_start_stepping,0);
  pthread_cond_init(&yee_stepping_finished,0);
  for(int i=0;i<95;i++) for(int j=0;j<34;j++)
   { pthread_spin_init(&yee_YZ_lock[YZ(i,j)].U.l,0); }
  for(int i=0;i<95;i++) for(int j=0;j<2;j++)
   { pthread_mutex_init(&yee_Y_lock[i][j][0],&yee_mattr); pthread_mutex_init(&yee_Y_lock[i][j][1],&yee_mattr); }
  yee_booted = 0;
  pthread_mutex_lock(&yee_boot_lock);
  pthread_mutex_init(yee_job_lock+0,&yee_mattr);
  pthread_mutex_init(yee_job_lock+1,&yee_mattr);
  pthread_mutex_init(yee_job_lock+2,&yee_mattr);
  pthread_mutex_init(yee_strat1_lock+0,&yee_mattr);
  pthread_mutex_init(yee_strat1_lock+1,&yee_mattr);
  pthread_mutex_init(yee_strat1_lock+2,&yee_mattr);
  pthread_mutex_lock(yee_job_lock+0);
  pthread_mutex_lock(yee_strat1_lock+0);
  pthread_mutex_lock(yee_job_lock+1);
  pthread_mutex_lock(yee_strat1_lock+1);
  extern void * yee_thread( void *data );
  pthread_create(yee_ids+0,0,yee_thread,(void *)0L);
  pthread_create(yee_ids+1,0,yee_thread,(void *)1L);

  return Py_None;
}

static PyObject * m_0002(PyObject *self, PyObject *args) {
  volatile double        retval=0;
  long           i0,i1,i2;
  PyArrayObject *pa0;
  float         *a0;

  if (!PyArg_ParseTuple(args, "lllO",&i0,&i1,&i2,&pa0))
     return NULL;

  a0 = (float *)(pa0->data);

  int do_source=i2;
  Py_MY_BEGIN_ALLOW_THREADS
  
/***** Callstage first ********/
  
  
/***** Callstage e2h ********/
  
  yee_a0=a0;
  
/***** Callstage h2e ********/
  
  yee_a0=a0;
  pthread_mutex_lock(&yee_data_lock);
  static int minit=0;
  yee_i0    = 0;
  yee_running = 2;
  yee_imax  = i1;
  calc_zint();
  if(!minit ) { minit=1; calc_multi(&yee_multi); }
  pthread_mutex_unlock(&yee_data_lock);
  pthread_mutex_lock(&yee_boot_lock);
  pthread_mutex_unlock(&yee_boot_lock);
  pthread_mutex_trylock(yee_job_lock+0);
  pthread_mutex_trylock(yee_job_lock+1);
  yee_Y_wait[0][0] = yee_Y_wait[0][1] = 0;
  yee_Y_wait[1][0] = yee_Y_wait[1][1] = 0;
  pthread_mutex_unlock(yee_job_lock);
  pthread_mutex_lock(&yee_msg_lock);
  pthread_cond_broadcast(&yee_start_stepping);
  pthread_cond_wait(&yee_stepping_finished,&yee_msg_lock);
  pthread_mutex_unlock(&yee_msg_lock);
  if (!startup_finished[0]) { multi_statistics(&yee_multi); calc_multi(&yee_multi); }
  balance_jobs(yee_imax);
  
  Py_MY_END_ALLOW_THREADS

  return PyFloat_FromDouble(retval);
}
  float *yee_norms = (float *) 0x00000000164EB6C0LL;
  
static void yh111e111(int n,int n0,float *f,float *c,float *dummy,float *norm)               {
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
  
static void yh111E111(int n,int n0,float *f,float *c,float *dummy,float *norm)               {
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
  
  r0 = _mm256_load_ps((const float *)(p0+620160LL));   /* OPT */  r30 = r0;
  r1 = _mm256_load_ps((const float *)(p0+620256LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+310080LL));   /* OPT */  r28 = r2;
  r3 = _mm256_load_ps((const float *)(p0+319200LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r23;
  r6 = _mm256_load_ps((const float *)(p0+930240LL));
  r6 +=  r0;
  *(M *)(p0+930240LL) = r6;   /* OPT */  r37 = r6;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r40 = r0;
  r1 = _mm256_load_ps((const float *)(p0+9120LL));
  r0 -=  r1;
  /* OPT */  r2 = r30;
  /* OPT */  r3 = r30;
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
  *(M *)(p0+1240320LL) = r6;   /* OPT */  r35 = r6;
  /* OPT */  r0 = r28;
  /* OPT */  r1 = r28;
  r4 = _mm256_load_ps((const float *)(p0+310088LL));
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
  r6 = _mm256_load_ps((const float *)(p0+1550400LL));
  r6 +=  r0;
  *(M *)(p0+1550400LL) = r6;   /* OPT */  r45 = r6;
  /* OPT */  r0 = r35;
  /* OPT */  r1 = r35;
  r4 = _mm256_load_ps((const float *)(p0+1240312LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  r3 = _mm256_load_ps((const float *)(p0+930144LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r22;
  /* OPT */  r6 = r30;
  r2 = _mm256_load_ps((const float *)(p1+64LL));
  r6 *=  r2;
  r6 +=  r0;
  *(M *)(p0+620160LL) = r6;
  /* OPT */  r0 = r37;
  r1 = _mm256_load_ps((const float *)(p0+921120LL));
  r0 -=  r1;
  /* OPT */  r2 = r45;
  /* OPT */  r3 = r45;
  r4 = _mm256_load_ps((const float *)(p0+1550392LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r21;
  /* OPT */  r6 = r28;
  r2 = _mm256_load_ps((const float *)(p1+56LL));
  r6 *=  r2;
  r6 +=  r0;
  *(M *)(p0+310080LL) = r6;
  /* OPT */  r0 = r45;
  r1 = _mm256_load_ps((const float *)(p0+1550304LL));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  r3 = _mm256_load_ps((const float *)(p0+1231200LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r20;
  /* OPT */  r6 = r40;
  r2 = _mm256_load_ps((const float *)(p1+48LL));
  r6 *=  r2;
  r6 +=  r0;
  *(M *)(p0+0LL) = r6;
  
  }}

}
  
static void Yh111e000(int n,int n0,float *f,float *c,float *dummy,float *norm)               {
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r20 = _mm256_load_ps((const float *)(norm+0LL));
  r21 = _mm256_load_ps((const float *)(norm+8LL));
  r22 = _mm256_load_ps((const float *)(norm+16LL));
  r23 = _mm256_load_ps((const float *)(norm+24LL));
  r24 = _mm256_load_ps((const float *)(norm+32LL));
  r25 = _mm256_load_ps((const float *)(norm+40LL));
  {

  float * p0 = f + 0/8*8,* p1 = c + 0/8*48;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 48) {
  
  r5 = _mm256_load_ps((const float *)(p1+24LL));
  r5 *=  r23;
  r0 = _mm256_load_ps((const float *)(p0+620160LL));   /* OPT */  r34 = r0;
  r1 = _mm256_load_ps((const float *)(p0+620256LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+310080LL));   /* OPT */  r27 = r2;
  r3 = _mm256_load_ps((const float *)(p0+319200LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  r6 = _mm256_load_ps((const float *)(p0+930240LL));
  r6 +=  r0;
  *(M *)(p0+930240LL) = r6;
  r5 = _mm256_load_ps((const float *)(p1+32LL));
  r5 *=  r24;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r30 = r0;
  r1 = _mm256_load_ps((const float *)(p0+9120LL));
  r0 -=  r1;
  /* OPT */  r2 = r34;
  /* OPT */  r3 = r34;
  r4 = _mm256_load_ps((const float *)(p0+620168LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  r6 = _mm256_load_ps((const float *)(p0+1240320LL));
  r6 +=  r0;
  *(M *)(p0+1240320LL) = r6;
  r5 = _mm256_load_ps((const float *)(p1+40LL));
  r5 *=  r25;
  /* OPT */  r0 = r27;
  /* OPT */  r1 = r27;
  r4 = _mm256_load_ps((const float *)(p0+310088LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r30;
  r3 = _mm256_load_ps((const float *)(p0+96LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  r6 = _mm256_load_ps((const float *)(p0+1550400LL));
  r6 +=  r0;
  *(M *)(p0+1550400LL) = r6;
  
  }}

}
  
static void Yh111e111(int n,int n0,float *f,float *c,float *dummy,float *norm)               {
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r20 = _mm256_load_ps((const float *)(norm+0LL));
  r21 = _mm256_load_ps((const float *)(norm+8LL));
  r22 = _mm256_load_ps((const float *)(norm+16LL));
  r23 = _mm256_load_ps((const float *)(norm+24LL));
  r24 = _mm256_load_ps((const float *)(norm+32LL));
  r25 = _mm256_load_ps((const float *)(norm+40LL));
  {

  float * p0 = f + 0/8*8,* p1 = c + 0/8*48;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 48) {
  
  r5 = _mm256_load_ps((const float *)(p1+24LL));
  r5 *=  r23;
  r0 = _mm256_load_ps((const float *)(p0+620160LL));   /* OPT */  r35 = r0;
  r1 = _mm256_load_ps((const float *)(p0+620256LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+310080LL));   /* OPT */  r28 = r2;
  r3 = _mm256_load_ps((const float *)(p0+319200LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  r6 = _mm256_load_ps((const float *)(p0+930240LL));
  r6 +=  r0;
  *(M *)(p0+930240LL) = r6;   /* OPT */  r43 = r6;
  r5 = _mm256_load_ps((const float *)(p1+32LL));
  r5 *=  r24;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r39 = r0;
  r1 = _mm256_load_ps((const float *)(p0+9120LL));
  r0 -=  r1;
  /* OPT */  r2 = r35;
  /* OPT */  r3 = r35;
  r4 = _mm256_load_ps((const float *)(p0+620168LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  r6 = _mm256_load_ps((const float *)(p0+1240320LL));
  r6 +=  r0;
  *(M *)(p0+1240320LL) = r6;   /* OPT */  r37 = r6;
  r5 = _mm256_load_ps((const float *)(p1+40LL));
  r5 *=  r25;
  /* OPT */  r0 = r28;
  /* OPT */  r1 = r28;
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
  r0 *=  r5;
  r6 = _mm256_load_ps((const float *)(p0+1550400LL));
  r6 +=  r0;
  *(M *)(p0+1550400LL) = r6;   /* OPT */  r42 = r6;
  r5 = _mm256_load_ps((const float *)(p1+16LL));
  r5 *=  r22;
  /* OPT */  r0 = r37;
  /* OPT */  r1 = r37;
  r4 = _mm256_load_ps((const float *)(p0+1240312LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r43;
  r3 = _mm256_load_ps((const float *)(p0+930144LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  /* OPT */  r6 = r35;
  r6 +=  r0;
  *(M *)(p0+620160LL) = r6;
  r5 = _mm256_load_ps((const float *)(p1+8LL));
  r5 *=  r21;
  /* OPT */  r0 = r43;
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
  r0 *=  r5;
  /* OPT */  r6 = r28;
  r6 +=  r0;
  *(M *)(p0+310080LL) = r6;
  r5 = _mm256_load_ps((const float *)(p1+0LL));
  r5 *=  r20;
  /* OPT */  r0 = r42;
  r1 = _mm256_load_ps((const float *)(p0+1550304LL));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  r3 = _mm256_load_ps((const float *)(p0+1231200LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  /* OPT */  r6 = r39;
  r6 +=  r0;
  *(M *)(p0+0LL) = r6;
  
  }}

}
  
static void Yh111E000(int n,int n0,float *f,float *c,float *dummy,float *norm)               {
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r20 = _mm256_load_ps((const float *)(norm+0LL));
  r21 = _mm256_load_ps((const float *)(norm+8LL));
  r22 = _mm256_load_ps((const float *)(norm+16LL));
  r23 = _mm256_load_ps((const float *)(norm+24LL));
  r24 = _mm256_load_ps((const float *)(norm+32LL));
  r25 = _mm256_load_ps((const float *)(norm+40LL));
  {

  float * p0 = f + 0/8*8,* p1 = c + 0/8*72;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 72) {
  
  r5 = _mm256_load_ps((const float *)(p1+24LL));
  r5 *=  r23;
  r0 = _mm256_load_ps((const float *)(p0+620160LL));   /* OPT */  r34 = r0;
  r1 = _mm256_load_ps((const float *)(p0+620256LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+310080LL));   /* OPT */  r27 = r2;
  r3 = _mm256_load_ps((const float *)(p0+319200LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  r6 = _mm256_load_ps((const float *)(p0+930240LL));
  r6 +=  r0;
  *(M *)(p0+930240LL) = r6;
  r5 = _mm256_load_ps((const float *)(p1+32LL));
  r5 *=  r24;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r30 = r0;
  r1 = _mm256_load_ps((const float *)(p0+9120LL));
  r0 -=  r1;
  /* OPT */  r2 = r34;
  /* OPT */  r3 = r34;
  r4 = _mm256_load_ps((const float *)(p0+620168LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  r6 = _mm256_load_ps((const float *)(p0+1240320LL));
  r6 +=  r0;
  *(M *)(p0+1240320LL) = r6;
  r5 = _mm256_load_ps((const float *)(p1+40LL));
  r5 *=  r25;
  /* OPT */  r0 = r27;
  /* OPT */  r1 = r27;
  r4 = _mm256_load_ps((const float *)(p0+310088LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r30;
  r3 = _mm256_load_ps((const float *)(p0+96LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  r6 = _mm256_load_ps((const float *)(p0+1550400LL));
  r6 +=  r0;
  *(M *)(p0+1550400LL) = r6;
  
  }}

}
  
static void Yh111E111(int n,int n0,float *f,float *c,float *dummy,float *norm)               {
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r20 = _mm256_load_ps((const float *)(norm+0LL));
  r21 = _mm256_load_ps((const float *)(norm+8LL));
  r22 = _mm256_load_ps((const float *)(norm+16LL));
  r23 = _mm256_load_ps((const float *)(norm+24LL));
  r24 = _mm256_load_ps((const float *)(norm+32LL));
  r25 = _mm256_load_ps((const float *)(norm+40LL));
  {

  float * p0 = f + 0/8*8,* p1 = c + 0/8*72;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 72) {
  
  r5 = _mm256_load_ps((const float *)(p1+24LL));
  r5 *=  r23;
  r0 = _mm256_load_ps((const float *)(p0+620160LL));   /* OPT */  r37 = r0;
  r1 = _mm256_load_ps((const float *)(p0+620256LL));
  r0 -=  r1;
  r2 = _mm256_load_ps((const float *)(p0+310080LL));   /* OPT */  r28 = r2;
  r3 = _mm256_load_ps((const float *)(p0+319200LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  r6 = _mm256_load_ps((const float *)(p0+930240LL));
  r6 +=  r0;
  *(M *)(p0+930240LL) = r6;   /* OPT */  r46 = r6;
  r5 = _mm256_load_ps((const float *)(p1+32LL));
  r5 *=  r24;
  r0 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r42 = r0;
  r1 = _mm256_load_ps((const float *)(p0+9120LL));
  r0 -=  r1;
  /* OPT */  r2 = r37;
  /* OPT */  r3 = r37;
  r4 = _mm256_load_ps((const float *)(p0+620168LL));
  r4 = _mm256_blend_ps(r4,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r3 = _mm256_blend_ps(r3,r4,(1<<3)+(1<<7));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  r6 = _mm256_load_ps((const float *)(p0+1240320LL));
  r6 +=  r0;
  *(M *)(p0+1240320LL) = r6;   /* OPT */  r40 = r6;
  r5 = _mm256_load_ps((const float *)(p1+40LL));
  r5 *=  r25;
  /* OPT */  r0 = r28;
  /* OPT */  r1 = r28;
  r4 = _mm256_load_ps((const float *)(p0+310088LL));
  r4 = _mm256_blend_ps(r4,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r4 = _mm256_permute_ps(r4,3);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r1 = _mm256_blend_ps(r1,r4,(1<<3)+(1<<7));
  r0 -=  r1;
  /* OPT */  r2 = r42;
  r3 = _mm256_load_ps((const float *)(p0+96LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  r6 = _mm256_load_ps((const float *)(p0+1550400LL));
  r6 +=  r0;
  *(M *)(p0+1550400LL) = r6;   /* OPT */  r45 = r6;
  r5 = _mm256_load_ps((const float *)(p1+16LL));
  r5 *=  r22;
  /* OPT */  r0 = r40;
  /* OPT */  r1 = r40;
  r4 = _mm256_load_ps((const float *)(p0+1240312LL));
  r4 = _mm256_blend_ps(r4,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r1 = _mm256_blend_ps(r1,r4,1+(1<<4));
  r0 -=  r1;
  /* OPT */  r2 = r46;
  r3 = _mm256_load_ps((const float *)(p0+930144LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  /* OPT */  r6 = r37;
  r2 = _mm256_load_ps((const float *)(p1+64LL));
  r6 *=  r2;
  r6 +=  r0;
  *(M *)(p0+620160LL) = r6;
  r5 = _mm256_load_ps((const float *)(p1+8LL));
  r5 *=  r21;
  /* OPT */  r0 = r46;
  r1 = _mm256_load_ps((const float *)(p0+921120LL));
  r0 -=  r1;
  /* OPT */  r2 = r45;
  /* OPT */  r3 = r45;
  r4 = _mm256_load_ps((const float *)(p0+1550392LL));
  r4 = _mm256_blend_ps(r4,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r4 = _mm256_permute2f128_ps(r4,r4,1);
  r4 = _mm256_permute_ps(r4,3);
  r3 = _mm256_blend_ps(r3,r4,1+(1<<4));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  /* OPT */  r6 = r28;
  r2 = _mm256_load_ps((const float *)(p1+56LL));
  r6 *=  r2;
  r6 +=  r0;
  *(M *)(p0+310080LL) = r6;
  r5 = _mm256_load_ps((const float *)(p1+0LL));
  r5 *=  r20;
  /* OPT */  r0 = r45;
  r1 = _mm256_load_ps((const float *)(p0+1550304LL));
  r0 -=  r1;
  /* OPT */  r2 = r40;
  r3 = _mm256_load_ps((const float *)(p0+1231200LL));
  r3 -=  r2;
  r0 +=  r3;
  r0 *=  r5;
  /* OPT */  r6 = r42;
  r2 = _mm256_load_ps((const float *)(p1+48LL));
  r6 *=  r2;
  r6 +=  r0;
  *(M *)(p0+0LL) = r6;
  
  }}

}
  
static void pC111L011(int n,int n0,float *f,float *cc,float *ff,float *norm) {
   static float half[] __attribute__ ((__aligned__(32))) = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r5 = _mm256_load_ps((const float *)(half+0LL));
  {

  float * p0 = f + n0/8*8,* p1 = ff + n0/8*32,* p2 = cc + n0/8*0;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 32,p2 += 0) {
  
  // fk 3 yee
  r1 = _mm256_load_ps((const float *)(p0+620160LL));   /* OPT */  r21 = r1;
  r0 = _mm256_load_ps((const float *)(p0+620256LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p0+310080LL));   /* OPT */  r40 = r0;
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p0+319200LL));
  r1 +=  r0;
  r0 = _mm256_load_ps((const float *)(p2+48LL));
  r2 = _mm256_load_ps((const float *)(norm+24LL));
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p0+930240LL));
  r0 +=  r1;
  *(M *)(p0+930240LL) = r0;   /* OPT */  r10 = r0;
  // fk 4 lossy-split
  r0 = _mm256_load_ps((const float *)(p0+1240320LL));
  r1 = _mm256_load_ps((const float *)(p1+0LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  r1 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r31 = r1;
  r0 = _mm256_load_ps((const float *)(p0+9120LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+64LL));
  r2 = _mm256_load_ps((const float *)(norm+32LL));   /* OPT */  r39 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+160LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r21;
  /* OPT */  r1 = r21;
  r2 = _mm256_load_ps((const float *)(p0+620168LL));
  r2 = _mm256_blend_ps(r2,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r2 = _mm256_permute_ps(r2,3);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r1 = _mm256_blend_ps(r1,r2,(1<<3)+(1<<7));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+72LL));
  /* OPT */  r2 = r39;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+168LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+1240320LL) = r0;   /* OPT */  r29 = r0;
  r3 -=  r4;
  *(M *)(p1+0LL) = r3;
  // fk 5 lossy-split
  r0 = _mm256_load_ps((const float *)(p0+1550400LL));
  r1 = _mm256_load_ps((const float *)(p1+8LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r40;
  /* OPT */  r0 = r40;
  r2 = _mm256_load_ps((const float *)(p0+310088LL));
  r2 = _mm256_blend_ps(r2,r0,1<<4);
  r0 = _mm256_permute_ps(r0,249);
  r2 = _mm256_permute_ps(r2,3);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r0 = _mm256_blend_ps(r0,r2,(1<<3)+(1<<7));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+80LL));
  r2 = _mm256_load_ps((const float *)(norm+40LL));   /* OPT */  r28 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+176LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r31;
  r1 = _mm256_load_ps((const float *)(p0+96LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+88LL));
  /* OPT */  r2 = r28;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+184LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+1550400LL) = r0;   /* OPT */  r35 = r0;
  r3 -=  r4;
  *(M *)(p1+8LL) = r3;
  // fk 0 yee
  /* OPT */  r1 = r35;
  r0 = _mm256_load_ps((const float *)(p0+1550304LL));
  r1 -=  r0;
  /* OPT */  r0 = r29;
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p0+1231200LL));
  r1 +=  r0;
  r0 = _mm256_load_ps((const float *)(p2+0LL));
  r2 = _mm256_load_ps((const float *)(norm+0LL));
  r0 *=  r2;
  r1 *=  r0;
  /* OPT */  r0 = r31;
  r0 +=  r1;
  *(M *)(p0+0LL) = r0;
  // fk 1 lossy-split
  /* OPT */  r0 = r40;
  r1 = _mm256_load_ps((const float *)(p1+16LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r10;
  r0 = _mm256_load_ps((const float *)(p0+921120LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+16LL));
  r2 = _mm256_load_ps((const float *)(norm+8LL));   /* OPT */  r18 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+112LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r35;
  /* OPT */  r1 = r35;
  r2 = _mm256_load_ps((const float *)(p0+1550392LL));
  r2 = _mm256_blend_ps(r2,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r2 = _mm256_permute_ps(r2,3);
  r1 = _mm256_blend_ps(r1,r2,1+(1<<4));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+24LL));
  /* OPT */  r2 = r18;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+120LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+310080LL) = r0;
  r3 -=  r4;
  *(M *)(p1+16LL) = r3;
  // fk 2 lossy-split
  /* OPT */  r0 = r21;
  r1 = _mm256_load_ps((const float *)(p1+24LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r29;
  /* OPT */  r0 = r29;
  r2 = _mm256_load_ps((const float *)(p0+1240312LL));
  r2 = _mm256_blend_ps(r2,r0,1<<3);
  r0 = _mm256_permute_ps(r0,144);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r2 = _mm256_permute_ps(r2,3);
  r0 = _mm256_blend_ps(r0,r2,1+(1<<4));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+32LL));
  r2 = _mm256_load_ps((const float *)(norm+16LL));   /* OPT */  r47 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+128LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r10;
  r1 = _mm256_load_ps((const float *)(p0+930144LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+40LL));
  /* OPT */  r2 = r47;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+136LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+620160LL) = r0;
  r3 -=  r4;
  *(M *)(p1+24LL) = r3;
  
  }}

}
  
static void pC111L111(int n,int n0,float *f,float *cc,float *ff,float *norm) {
   static float half[] __attribute__ ((__aligned__(32))) = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r5 = _mm256_load_ps((const float *)(half+0LL));
  {

  float * p0 = f + n0/8*8,* p1 = ff + n0/8*48,* p2 = cc + n0/8*0;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 48,p2 += 0) {
  
  // fk 3 lossy-split
  r0 = _mm256_load_ps((const float *)(p0+930240LL));
  r1 = _mm256_load_ps((const float *)(p1+0LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  r1 = _mm256_load_ps((const float *)(p0+620160LL));   /* OPT */  r27 = r1;
  r0 = _mm256_load_ps((const float *)(p0+620256LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+48LL));
  r2 = _mm256_load_ps((const float *)(norm+24LL));   /* OPT */  r44 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+144LL));
  r3 *=  r0;
  r3 +=  r1;
  r0 = _mm256_load_ps((const float *)(p0+310080LL));   /* OPT */  r13 = r0;
  r1 = _mm256_load_ps((const float *)(p0+319200LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+56LL));
  /* OPT */  r2 = r44;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+152LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+930240LL) = r0;   /* OPT */  r48 = r0;
  r3 -=  r4;
  *(M *)(p1+0LL) = r3;
  // fk 4 lossy-split
  r0 = _mm256_load_ps((const float *)(p0+1240320LL));
  r1 = _mm256_load_ps((const float *)(p1+8LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  r1 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r39 = r1;
  r0 = _mm256_load_ps((const float *)(p0+9120LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+64LL));
  r2 = _mm256_load_ps((const float *)(norm+32LL));   /* OPT */  r47 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+160LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r27;
  /* OPT */  r1 = r27;
  r2 = _mm256_load_ps((const float *)(p0+620168LL));
  r2 = _mm256_blend_ps(r2,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r2 = _mm256_permute_ps(r2,3);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r1 = _mm256_blend_ps(r1,r2,(1<<3)+(1<<7));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+72LL));
  /* OPT */  r2 = r47;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+168LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+1240320LL) = r0;   /* OPT */  r37 = r0;
  r3 -=  r4;
  *(M *)(p1+8LL) = r3;
  // fk 5 lossy-split
  r0 = _mm256_load_ps((const float *)(p0+1550400LL));
  r1 = _mm256_load_ps((const float *)(p1+16LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r13;
  /* OPT */  r0 = r13;
  r2 = _mm256_load_ps((const float *)(p0+310088LL));
  r2 = _mm256_blend_ps(r2,r0,1<<4);
  r0 = _mm256_permute_ps(r0,249);
  r2 = _mm256_permute_ps(r2,3);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r0 = _mm256_blend_ps(r0,r2,(1<<3)+(1<<7));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+80LL));
  r2 = _mm256_load_ps((const float *)(norm+40LL));   /* OPT */  r34 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+176LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r39;
  r1 = _mm256_load_ps((const float *)(p0+96LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+88LL));
  /* OPT */  r2 = r34;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+184LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+1550400LL) = r0;   /* OPT */  r43 = r0;
  r3 -=  r4;
  *(M *)(p1+16LL) = r3;
  // fk 0 lossy-split
  /* OPT */  r0 = r39;
  r1 = _mm256_load_ps((const float *)(p1+24LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r43;
  r0 = _mm256_load_ps((const float *)(p0+1550304LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+0LL));
  r2 = _mm256_load_ps((const float *)(norm+0LL));   /* OPT */  r32 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+96LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r37;
  r1 = _mm256_load_ps((const float *)(p0+1231200LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+8LL));
  /* OPT */  r2 = r32;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+104LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+0LL) = r0;
  r3 -=  r4;
  *(M *)(p1+24LL) = r3;
  // fk 1 lossy-split
  /* OPT */  r0 = r13;
  r1 = _mm256_load_ps((const float *)(p1+32LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r48;
  r0 = _mm256_load_ps((const float *)(p0+921120LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+16LL));
  r2 = _mm256_load_ps((const float *)(norm+8LL));   /* OPT */  r24 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+112LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r43;
  /* OPT */  r1 = r43;
  r2 = _mm256_load_ps((const float *)(p0+1550392LL));
  r2 = _mm256_blend_ps(r2,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r2 = _mm256_permute_ps(r2,3);
  r1 = _mm256_blend_ps(r1,r2,1+(1<<4));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+24LL));
  /* OPT */  r2 = r24;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+120LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+310080LL) = r0;
  r3 -=  r4;
  *(M *)(p1+32LL) = r3;
  // fk 2 lossy-split
  /* OPT */  r0 = r27;
  r1 = _mm256_load_ps((const float *)(p1+40LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r37;
  /* OPT */  r0 = r37;
  r2 = _mm256_load_ps((const float *)(p0+1240312LL));
  r2 = _mm256_blend_ps(r2,r0,1<<3);
  r0 = _mm256_permute_ps(r0,144);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r2 = _mm256_permute_ps(r2,3);
  r0 = _mm256_blend_ps(r0,r2,1+(1<<4));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+32LL));
  r2 = _mm256_load_ps((const float *)(norm+16LL));   /* OPT */  r56 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+128LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r48;
  r1 = _mm256_load_ps((const float *)(p0+930144LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+40LL));
  /* OPT */  r2 = r56;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+136LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+620160LL) = r0;
  r3 -=  r4;
  *(M *)(p1+40LL) = r3;
  
  }}

}
  
static void PC111L110(int n,int n0,float *f,float *cc,float *ff,float *norm) {
   static float half[] __attribute__ ((__aligned__(32))) = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r5 = _mm256_load_ps((const float *)(half+0LL));
  {

  float * p0 = f + n0/8*8,* p1 = ff + n0/8*32,* p2 = cc + n0/8*192;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 32,p2 += 192) {
  
  // fk 3 lossy-split
  r0 = _mm256_load_ps((const float *)(p0+930240LL));
  r1 = _mm256_load_ps((const float *)(p1+0LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  r1 = _mm256_load_ps((const float *)(p0+620160LL));   /* OPT */  r22 = r1;
  r0 = _mm256_load_ps((const float *)(p0+620256LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+48LL));
  r2 = _mm256_load_ps((const float *)(norm+24LL));   /* OPT */  r37 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+144LL));
  r3 *=  r0;
  r3 +=  r1;
  r0 = _mm256_load_ps((const float *)(p0+310080LL));   /* OPT */  r10 = r0;
  r1 = _mm256_load_ps((const float *)(p0+319200LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+56LL));
  /* OPT */  r2 = r37;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+152LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+930240LL) = r0;   /* OPT */  r41 = r0;
  r3 -=  r4;
  *(M *)(p1+0LL) = r3;
  // fk 4 lossy-split
  r0 = _mm256_load_ps((const float *)(p0+1240320LL));
  r1 = _mm256_load_ps((const float *)(p1+8LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  r1 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r32 = r1;
  r0 = _mm256_load_ps((const float *)(p0+9120LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+64LL));
  r2 = _mm256_load_ps((const float *)(norm+32LL));   /* OPT */  r40 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+160LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r22;
  /* OPT */  r1 = r22;
  r2 = _mm256_load_ps((const float *)(p0+620168LL));
  r2 = _mm256_blend_ps(r2,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r2 = _mm256_permute_ps(r2,3);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r1 = _mm256_blend_ps(r1,r2,(1<<3)+(1<<7));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+72LL));
  /* OPT */  r2 = r40;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+168LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+1240320LL) = r0;   /* OPT */  r30 = r0;
  r3 -=  r4;
  *(M *)(p1+8LL) = r3;
  // fk 5 yee
  /* OPT */  r1 = r10;
  /* OPT */  r0 = r10;
  r2 = _mm256_load_ps((const float *)(p0+310088LL));
  r2 = _mm256_blend_ps(r2,r0,1<<4);
  r0 = _mm256_permute_ps(r0,249);
  r2 = _mm256_permute_ps(r2,3);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r0 = _mm256_blend_ps(r0,r2,(1<<3)+(1<<7));
  r1 -=  r0;
  /* OPT */  r0 = r32;
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p0+96LL));
  r1 +=  r0;
  r0 = _mm256_load_ps((const float *)(p2+80LL));
  r2 = _mm256_load_ps((const float *)(norm+40LL));
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p0+1550400LL));
  r0 +=  r1;
  *(M *)(p0+1550400LL) = r0;   /* OPT */  r36 = r0;
  // fk 0 lossy-split
  /* OPT */  r0 = r32;
  r1 = _mm256_load_ps((const float *)(p1+16LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r36;
  r0 = _mm256_load_ps((const float *)(p0+1550304LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+0LL));
  r2 = _mm256_load_ps((const float *)(norm+0LL));   /* OPT */  r26 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+96LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r30;
  r1 = _mm256_load_ps((const float *)(p0+1231200LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+8LL));
  /* OPT */  r2 = r26;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+104LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+0LL) = r0;
  r3 -=  r4;
  *(M *)(p1+16LL) = r3;
  // fk 1 lossy-split
  /* OPT */  r0 = r10;
  r1 = _mm256_load_ps((const float *)(p1+24LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r41;
  r0 = _mm256_load_ps((const float *)(p0+921120LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+16LL));
  r2 = _mm256_load_ps((const float *)(norm+8LL));   /* OPT */  r19 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+112LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r36;
  /* OPT */  r1 = r36;
  r2 = _mm256_load_ps((const float *)(p0+1550392LL));
  r2 = _mm256_blend_ps(r2,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r2 = _mm256_permute_ps(r2,3);
  r1 = _mm256_blend_ps(r1,r2,1+(1<<4));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+24LL));
  /* OPT */  r2 = r19;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+120LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+310080LL) = r0;
  r3 -=  r4;
  *(M *)(p1+24LL) = r3;
  // fk 2 yee
  /* OPT */  r1 = r30;
  /* OPT */  r0 = r30;
  r2 = _mm256_load_ps((const float *)(p0+1240312LL));
  r2 = _mm256_blend_ps(r2,r0,1<<3);
  r0 = _mm256_permute_ps(r0,144);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r2 = _mm256_permute_ps(r2,3);
  r0 = _mm256_blend_ps(r0,r2,1+(1<<4));
  r1 -=  r0;
  /* OPT */  r0 = r41;
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p0+930144LL));
  r1 +=  r0;
  r0 = _mm256_load_ps((const float *)(p2+32LL));
  r2 = _mm256_load_ps((const float *)(norm+16LL));
  r0 *=  r2;
  r1 *=  r0;
  /* OPT */  r0 = r22;
  r0 +=  r1;
  *(M *)(p0+620160LL) = r0;
  
  }}

}
  
static void PC111L101(int n,int n0,float *f,float *cc,float *ff,float *norm) {
   static float half[] __attribute__ ((__aligned__(32))) = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r5 = _mm256_load_ps((const float *)(half+0LL));
  {

  float * p0 = f + n0/8*8,* p1 = ff + n0/8*32,* p2 = cc + n0/8*192;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 32,p2 += 192) {
  
  // fk 3 lossy-split
  r0 = _mm256_load_ps((const float *)(p0+930240LL));
  r1 = _mm256_load_ps((const float *)(p1+0LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  r1 = _mm256_load_ps((const float *)(p0+620160LL));   /* OPT */  r25 = r1;
  r0 = _mm256_load_ps((const float *)(p0+620256LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+48LL));
  r2 = _mm256_load_ps((const float *)(norm+24LL));   /* OPT */  r40 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+144LL));
  r3 *=  r0;
  r3 +=  r1;
  r0 = _mm256_load_ps((const float *)(p0+310080LL));   /* OPT */  r11 = r0;
  r1 = _mm256_load_ps((const float *)(p0+319200LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+56LL));
  /* OPT */  r2 = r40;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+152LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+930240LL) = r0;   /* OPT */  r44 = r0;
  r3 -=  r4;
  *(M *)(p1+0LL) = r3;
  // fk 4 yee
  r1 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r36 = r1;
  r0 = _mm256_load_ps((const float *)(p0+9120LL));
  r1 -=  r0;
  /* OPT */  r0 = r25;
  r1 -=  r0;
  /* OPT */  r0 = r25;
  r2 = _mm256_load_ps((const float *)(p0+620168LL));
  r2 = _mm256_blend_ps(r2,r0,1<<4);
  r0 = _mm256_permute_ps(r0,249);
  r2 = _mm256_permute_ps(r2,3);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r0 = _mm256_blend_ps(r0,r2,(1<<3)+(1<<7));
  r1 +=  r0;
  r0 = _mm256_load_ps((const float *)(p2+64LL));
  r2 = _mm256_load_ps((const float *)(norm+32LL));
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p0+1240320LL));
  r0 +=  r1;
  *(M *)(p0+1240320LL) = r0;   /* OPT */  r34 = r0;
  // fk 5 lossy-split
  r0 = _mm256_load_ps((const float *)(p0+1550400LL));
  r1 = _mm256_load_ps((const float *)(p1+8LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r11;
  /* OPT */  r0 = r11;
  r2 = _mm256_load_ps((const float *)(p0+310088LL));
  r2 = _mm256_blend_ps(r2,r0,1<<4);
  r0 = _mm256_permute_ps(r0,249);
  r2 = _mm256_permute_ps(r2,3);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r0 = _mm256_blend_ps(r0,r2,(1<<3)+(1<<7));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+80LL));
  r2 = _mm256_load_ps((const float *)(norm+40LL));   /* OPT */  r31 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+176LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r36;
  r1 = _mm256_load_ps((const float *)(p0+96LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+88LL));
  /* OPT */  r2 = r31;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+184LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+1550400LL) = r0;   /* OPT */  r39 = r0;
  r3 -=  r4;
  *(M *)(p1+8LL) = r3;
  // fk 0 lossy-split
  /* OPT */  r0 = r36;
  r1 = _mm256_load_ps((const float *)(p1+16LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r39;
  r0 = _mm256_load_ps((const float *)(p0+1550304LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+0LL));
  r2 = _mm256_load_ps((const float *)(norm+0LL));   /* OPT */  r29 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+96LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r34;
  r1 = _mm256_load_ps((const float *)(p0+1231200LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+8LL));
  /* OPT */  r2 = r29;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+104LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+0LL) = r0;
  r3 -=  r4;
  *(M *)(p1+16LL) = r3;
  // fk 1 yee
  /* OPT */  r1 = r44;
  r0 = _mm256_load_ps((const float *)(p0+921120LL));
  r1 -=  r0;
  /* OPT */  r0 = r39;
  r1 -=  r0;
  /* OPT */  r0 = r39;
  r2 = _mm256_load_ps((const float *)(p0+1550392LL));
  r2 = _mm256_blend_ps(r2,r0,1<<3);
  r0 = _mm256_permute_ps(r0,144);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r2 = _mm256_permute_ps(r2,3);
  r0 = _mm256_blend_ps(r0,r2,1+(1<<4));
  r1 +=  r0;
  r0 = _mm256_load_ps((const float *)(p2+16LL));
  r2 = _mm256_load_ps((const float *)(norm+8LL));
  r0 *=  r2;
  r1 *=  r0;
  /* OPT */  r0 = r11;
  r0 +=  r1;
  *(M *)(p0+310080LL) = r0;
  // fk 2 lossy-split
  /* OPT */  r0 = r25;
  r1 = _mm256_load_ps((const float *)(p1+24LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r34;
  /* OPT */  r0 = r34;
  r2 = _mm256_load_ps((const float *)(p0+1240312LL));
  r2 = _mm256_blend_ps(r2,r0,1<<3);
  r0 = _mm256_permute_ps(r0,144);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r2 = _mm256_permute_ps(r2,3);
  r0 = _mm256_blend_ps(r0,r2,1+(1<<4));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+32LL));
  r2 = _mm256_load_ps((const float *)(norm+16LL));   /* OPT */  r50 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+128LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r44;
  r1 = _mm256_load_ps((const float *)(p0+930144LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+40LL));
  /* OPT */  r2 = r50;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+136LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+620160LL) = r0;
  r3 -=  r4;
  *(M *)(p1+24LL) = r3;
  
  }}

}
  
static void PC111L111(int n,int n0,float *f,float *cc,float *ff,float *norm) {
   static float half[] __attribute__ ((__aligned__(32))) = {0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5};
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  r5 = _mm256_load_ps((const float *)(half+0LL));
  {

  float * p0 = f + n0/8*8,* p1 = ff + n0/8*48,* p2 = cc + n0/8*192;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 48,p2 += 192) {
  
  // fk 3 lossy-split
  r0 = _mm256_load_ps((const float *)(p0+930240LL));
  r1 = _mm256_load_ps((const float *)(p1+0LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  r1 = _mm256_load_ps((const float *)(p0+620160LL));   /* OPT */  r27 = r1;
  r0 = _mm256_load_ps((const float *)(p0+620256LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+48LL));
  r2 = _mm256_load_ps((const float *)(norm+24LL));   /* OPT */  r44 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+144LL));
  r3 *=  r0;
  r3 +=  r1;
  r0 = _mm256_load_ps((const float *)(p0+310080LL));   /* OPT */  r13 = r0;
  r1 = _mm256_load_ps((const float *)(p0+319200LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+56LL));
  /* OPT */  r2 = r44;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+152LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+930240LL) = r0;   /* OPT */  r48 = r0;
  r3 -=  r4;
  *(M *)(p1+0LL) = r3;
  // fk 4 lossy-split
  r0 = _mm256_load_ps((const float *)(p0+1240320LL));
  r1 = _mm256_load_ps((const float *)(p1+8LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  r1 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r39 = r1;
  r0 = _mm256_load_ps((const float *)(p0+9120LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+64LL));
  r2 = _mm256_load_ps((const float *)(norm+32LL));   /* OPT */  r47 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+160LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r27;
  /* OPT */  r1 = r27;
  r2 = _mm256_load_ps((const float *)(p0+620168LL));
  r2 = _mm256_blend_ps(r2,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r2 = _mm256_permute_ps(r2,3);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r1 = _mm256_blend_ps(r1,r2,(1<<3)+(1<<7));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+72LL));
  /* OPT */  r2 = r47;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+168LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+1240320LL) = r0;   /* OPT */  r37 = r0;
  r3 -=  r4;
  *(M *)(p1+8LL) = r3;
  // fk 5 lossy-split
  r0 = _mm256_load_ps((const float *)(p0+1550400LL));
  r1 = _mm256_load_ps((const float *)(p1+16LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r13;
  /* OPT */  r0 = r13;
  r2 = _mm256_load_ps((const float *)(p0+310088LL));
  r2 = _mm256_blend_ps(r2,r0,1<<4);
  r0 = _mm256_permute_ps(r0,249);
  r2 = _mm256_permute_ps(r2,3);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r0 = _mm256_blend_ps(r0,r2,(1<<3)+(1<<7));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+80LL));
  r2 = _mm256_load_ps((const float *)(norm+40LL));   /* OPT */  r34 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+176LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r39;
  r1 = _mm256_load_ps((const float *)(p0+96LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+88LL));
  /* OPT */  r2 = r34;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+184LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+1550400LL) = r0;   /* OPT */  r43 = r0;
  r3 -=  r4;
  *(M *)(p1+16LL) = r3;
  // fk 0 lossy-split
  /* OPT */  r0 = r39;
  r1 = _mm256_load_ps((const float *)(p1+24LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r43;
  r0 = _mm256_load_ps((const float *)(p0+1550304LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+0LL));
  r2 = _mm256_load_ps((const float *)(norm+0LL));   /* OPT */  r32 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+96LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r37;
  r1 = _mm256_load_ps((const float *)(p0+1231200LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+8LL));
  /* OPT */  r2 = r32;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+104LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+0LL) = r0;
  r3 -=  r4;
  *(M *)(p1+24LL) = r3;
  // fk 1 lossy-split
  /* OPT */  r0 = r13;
  r1 = _mm256_load_ps((const float *)(p1+32LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r48;
  r0 = _mm256_load_ps((const float *)(p0+921120LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+16LL));
  r2 = _mm256_load_ps((const float *)(norm+8LL));   /* OPT */  r24 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+112LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r43;
  /* OPT */  r1 = r43;
  r2 = _mm256_load_ps((const float *)(p0+1550392LL));
  r2 = _mm256_blend_ps(r2,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r2 = _mm256_permute_ps(r2,3);
  r1 = _mm256_blend_ps(r1,r2,1+(1<<4));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+24LL));
  /* OPT */  r2 = r24;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+120LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+310080LL) = r0;
  r3 -=  r4;
  *(M *)(p1+32LL) = r3;
  // fk 2 lossy-split
  /* OPT */  r0 = r27;
  r1 = _mm256_load_ps((const float *)(p1+40LL));
  r3 = r0;
  r3 +=  r1;
  r3 *=  r5;
  r4 = r0;
  r4 -=  r1;
  r4 *=  r5;
  /* OPT */  r1 = r37;
  /* OPT */  r0 = r37;
  r2 = _mm256_load_ps((const float *)(p0+1240312LL));
  r2 = _mm256_blend_ps(r2,r0,1<<3);
  r0 = _mm256_permute_ps(r0,144);
  r2 = _mm256_permute2f128_ps(r2,r2,1);
  r2 = _mm256_permute_ps(r2,3);
  r0 = _mm256_blend_ps(r0,r2,1+(1<<4));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+32LL));
  r2 = _mm256_load_ps((const float *)(norm+16LL));   /* OPT */  r56 = r2;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+128LL));
  r3 *=  r0;
  r3 +=  r1;
  /* OPT */  r0 = r48;
  r1 = _mm256_load_ps((const float *)(p0+930144LL));
  r1 -=  r0;
  r0 = _mm256_load_ps((const float *)(p2+40LL));
  /* OPT */  r2 = r56;
  r0 *=  r2;
  r1 *=  r0;
  r0 = _mm256_load_ps((const float *)(p2+136LL));
  r4 *=  r0;
  r4 +=  r1;
  r0 = r3;
  r0 +=  r4;
  *(M *)(p0+620160LL) = r0;
  r3 -=  r4;
  *(M *)(p1+40LL) = r3;
  
  }}

}
  
void LH111E111(int n,int n0,float *f,float *c,float * spc,float *norm)               {
  register M r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20,r21,r22,r23,r24,r25,r26,r27,r28,r29,r30,r31,r32,r33,r34,r35,r36,r37,r38,r39,r40,r41,r42,r43,r44,r45,r46,r47,r48,r49,r50,r51,r52,r53,r54,r55,r56,r57,r58,r59,r60,r61,r62,r63; volatile M add;
  
  {

  float * p0 = f + n0/8*8,* p1 = c + n0/8*144,* p2 = spc + n0/8*24;
  
  for(long64 i=n;i>0;i-=8,p0 += 8,p1 += 144,p2 += 24) {
  
  r4 = _mm256_load_ps((const float *)(p0+930240LL));
  r0 = _mm256_load_ps((const float *)(p0+310080LL));   /* OPT */  r10 = r0;
  r1 = _mm256_load_ps((const float *)(p0+319200LL));
  r1 -=  r0;
  r2 = _mm256_load_ps((const float *)(p0+620160LL));   /* OPT */  r39 = r2;
  r3 = _mm256_load_ps((const float *)(p0+620256LL));
  r2 -=  r3;
  r1 +=  r2;
  r3 = _mm256_load_ps((const float *)(p1+24LL));
  r0 = _mm256_load_ps((const float *)(norm+24LL));
  r3 *=  r0;
  r1 *=  r3;
  r1 +=  r4;
  *(M *)(p0+930240LL) = r1;   /* OPT */  r23 = r1;
  r4 = _mm256_load_ps((const float *)(p0+1240320LL));
  /* OPT */  r0 = r39;
  /* OPT */  r1 = r39;
  r3 = _mm256_load_ps((const float *)(p0+620168LL));
  r3 = _mm256_blend_ps(r3,r1,1<<4);
  r1 = _mm256_permute_ps(r1,249);
  r3 = _mm256_permute_ps(r3,3);
  r3 = _mm256_permute2f128_ps(r3,r3,1);
  r1 = _mm256_blend_ps(r1,r3,(1<<3)+(1<<7));
  r1 -=  r0;
  r2 = _mm256_load_ps((const float *)(p0+0LL));   /* OPT */  r30 = r2;
  r3 = _mm256_load_ps((const float *)(p0+9120LL));
  r2 -=  r3;
  r1 +=  r2;
  r3 = _mm256_load_ps((const float *)(p1+32LL));
  r0 = _mm256_load_ps((const float *)(norm+32LL));
  r3 *=  r0;
  r1 *=  r3;
  r1 +=  r4;
  *(M *)(p0+1240320LL) = r1;   /* OPT */  r28 = r1;
  r4 = _mm256_load_ps((const float *)(p0+1550400LL));
  /* OPT */  r0 = r30;
  r1 = _mm256_load_ps((const float *)(p0+96LL));
  r1 -=  r0;
  /* OPT */  r2 = r10;
  /* OPT */  r3 = r10;
  r0 = _mm256_load_ps((const float *)(p0+310088LL));
  r0 = _mm256_blend_ps(r0,r3,1<<4);
  r3 = _mm256_permute_ps(r3,249);
  r0 = _mm256_permute_ps(r0,3);
  r0 = _mm256_permute2f128_ps(r0,r0,1);
  r3 = _mm256_blend_ps(r3,r0,(1<<3)+(1<<7));
  r2 -=  r3;
  r1 +=  r2;
  r3 = _mm256_load_ps((const float *)(p1+40LL));
  r0 = _mm256_load_ps((const float *)(norm+40LL));
  r3 *=  r0;
  r1 *=  r3;
  r1 +=  r4;
  *(M *)(p0+1550400LL) = r1;   /* OPT */  r34 = r1;
  /* OPT */  r4 = r30;
  /* LR ik=0 */
  r5 = _mm256_load_ps((const float *)(p2+0LL));
  r1 = _mm256_load_ps((const float *)(p1+120LL));
  r2 = _mm256_load_ps((const float *)(p1+48LL));
  r2 *=  r4;
  r5 *=  r1;
  r5 +=  r2;
  *(M *)(p2+0LL) = r5;
  /* OPT */  r0 = r28;
  r1 = _mm256_load_ps((const float *)(p0+1231200LL));
  r1 -=  r0;
  /* OPT */  r2 = r34;
  r3 = _mm256_load_ps((const float *)(p0+1550304LL));
  r2 -=  r3;
  r1 +=  r2;
  r3 = _mm256_load_ps((const float *)(p1+0LL));
  r0 = _mm256_load_ps((const float *)(norm+0LL));
  r3 *=  r0;
  r1 *=  r3;
  r2 = _mm256_load_ps((const float *)(p1+72LL));
  r4 *=  r2;
  r1 +=  r4;
  r1 -=  r5;
  *(M *)(p0+0LL) = r1;
  /* OPT */  r4 = r10;
  /* LR ik=0 */
  r5 = _mm256_load_ps((const float *)(p2+8LL));
  r1 = _mm256_load_ps((const float *)(p1+128LL));
  r2 = _mm256_load_ps((const float *)(p1+56LL));
  r2 *=  r4;
  r5 *=  r1;
  r5 +=  r2;
  *(M *)(p2+8LL) = r5;
  /* OPT */  r0 = r34;
  /* OPT */  r1 = r34;
  r3 = _mm256_load_ps((const float *)(p0+1550392LL));
  r3 = _mm256_blend_ps(r3,r1,1<<3);
  r1 = _mm256_permute_ps(r1,144);
  r3 = _mm256_permute2f128_ps(r3,r3,1);
  r3 = _mm256_permute_ps(r3,3);
  r1 = _mm256_blend_ps(r1,r3,1+(1<<4));
  r1 -=  r0;
  /* OPT */  r2 = r23;
  r3 = _mm256_load_ps((const float *)(p0+921120LL));
  r2 -=  r3;
  r1 +=  r2;
  r3 = _mm256_load_ps((const float *)(p1+8LL));
  r0 = _mm256_load_ps((const float *)(norm+8LL));
  r3 *=  r0;
  r1 *=  r3;
  r2 = _mm256_load_ps((const float *)(p1+80LL));
  r4 *=  r2;
  r1 +=  r4;
  r1 -=  r5;
  *(M *)(p0+310080LL) = r1;
  /* OPT */  r4 = r39;
  /* LR ik=0 */
  r5 = _mm256_load_ps((const float *)(p2+16LL));
  r1 = _mm256_load_ps((const float *)(p1+136LL));
  r2 = _mm256_load_ps((const float *)(p1+64LL));
  r2 *=  r4;
  r5 *=  r1;
  r5 +=  r2;
  *(M *)(p2+16LL) = r5;
  /* OPT */  r0 = r23;
  r1 = _mm256_load_ps((const float *)(p0+930144LL));
  r1 -=  r0;
  /* OPT */  r2 = r28;
  /* OPT */  r3 = r28;
  r0 = _mm256_load_ps((const float *)(p0+1240312LL));
  r0 = _mm256_blend_ps(r0,r3,1<<3);
  r3 = _mm256_permute_ps(r3,144);
  r0 = _mm256_permute2f128_ps(r0,r0,1);
  r0 = _mm256_permute_ps(r0,3);
  r3 = _mm256_blend_ps(r3,r0,1+(1<<4));
  r2 -=  r3;
  r1 +=  r2;
  r3 = _mm256_load_ps((const float *)(p1+16LL));
  r0 = _mm256_load_ps((const float *)(norm+16LL));
  r3 *=  r0;
  r1 *=  r3;
  r2 = _mm256_load_ps((const float *)(p1+88LL));
  r4 *=  r2;
  r1 +=  r4;
  r1 -=  r5;
  *(M *)(p0+620160LL) = r1;
  
  }}

}
  pthread_mutex_t   lck_013;
  pthread_mutex_t   lck_023;
  pthread_mutex_t   lck_024;
  pthread_mutex_t   lck_025;
  pthread_mutex_t   lck_026;
                 static void interpreter_h2e(int myt,int yy,int zz,long long &ncells,long long &Time)
                 { /* Linecode */
                    if (yy < 93 && zz < 33 ) ncells += 96;
                    const int NY = 95,NZ = 34,NY0 = 95,NZ0 = 34,NXB = 1,NX = 96;
                    float *base  = (float *)0x1bd94880ULL;
                    float *a0    = yee_a0;
                    float *coeff = 0;
  
  static struct YEEh2e {int nf,x0,c0,s0; } *yh2e = (YEEh2e *)0x0000000013F2A340LL;
  static int *LINESh2e = (int *)0x000000001BBA4F40LL;
  /* LENGTH calls 64867 */
  /*  is_32bit 1 */
                    float *a00   = yee_a0    + yy*96LL + zz*9120LL;
                           const int x0=0,x1=NX;
                           int *line = LINESh2e + 2*((zz+yy*NZ)  );
                    int stop = 0;
                    struct YEEh2e *py = (struct YEEh2e *)((int *)yh2e + line[0]);
                    float *norms = yee_norms + yy*1632     + zz*48;
  _mm_prefetch((char *)(norms+0LL),_MM_HINT_T0);
  _mm_prefetch((char *)(norms+16LL),_MM_HINT_T0);
  _mm_prefetch((char *)(norms+32LL),_MM_HINT_T0);
                    float *pos = 0,*spc=0; 
                    for(int n=line[1];n>0 && !stop;) { /* For n */
  _mm_prefetch((char *)((char *)py+64+0LL),_MM_HINT_T0);
                       int  arg = py->x0;
                       int nn  = py->nf&0xffff;
                       int n0  = nn>>1;
                       int cde = py->nf>>16;
                       if(nn&1) {
                              coeff = base +arg;
                              n-=2;   py = (struct YEEh2e *)((int *)py + 2); 
                                }
                       else     {
                                pos   = a00   +arg; coeff = base+py->c0; spc = base+py->s0;
                                n-=4; py ++; }
  
                       switch(cde) { /* Switch */
                                           case 1: {
                       yh111e111(n0,0,pos,coeff,spc,norms);
                                           break; }
                                           case 2: {
                       yh111E111(n0,0,pos,coeff,spc,norms);
                                           break; }
                                           case 3: {
                       Yh111e000(n0,0,pos,coeff,spc,norms);
                                           break; }
                                           case 4: {
                       Yh111e111(n0,0,pos,coeff,spc,norms);
                                           break; }
                                           case 5: {
                       Yh111E000(n0,0,pos,coeff,spc,norms);
                                           break; }
                                           case 6: {
                       Yh111E111(n0,0,pos,coeff,spc,norms);
                                           break; }
                                           case 7: {
                       pC111L011(n0,0,pos,coeff,spc,norms);
                                               spc += n0*4;
                                           break; }
                                           case 8: {
                       pC111L111(n0,0,pos,coeff,spc,norms);
                                               spc += n0*6;
                                           break; }
                                           case 9: {
                       PC111L110(n0,0,pos,coeff,spc,norms);
                                               spc += n0*4;
                                           break; }
                                           case 10: {
                       PC111L101(n0,0,pos,coeff,spc,norms);
                                               spc += n0*4;
                                           break; }
                                           case 11: {
                       PC111L111(n0,0,pos,coeff,spc,norms);
                                               spc += n0*6;
                                           break; }
                                           case 12: {
                       LH111E111(n0,0,pos,coeff,spc,norms);
                                               spc += n0*3;
                                           break; }
                                           case 13: {
      if( myt % 1007 != 0) { stop =1; break; }  else    {  
      long long cl0,cl1; CPUCLOCK(cl0); 
      pthread_mutex_lock(&lck_013); chksum(myt,x0,x1,n0,a0,coeff,spc,norms); pthread_mutex_unlock(&lck_013); 
       CPUCLOCK(cl1);  if(cl1 > cl0) Time += cl1-cl0;
   } 
                                           break; }
                                           case 14: {
      if( myt % 53 != 0) { stop =1; break; }  else    {  
      long long cl0,cl1; CPUCLOCK(cl0); 
       dumpbox_1(myt,x0,x1,n0,a0,coeff,spc,norms);  
       CPUCLOCK(cl1);  if(cl1 > cl0) Time += cl1-cl0;
   } 
                                           break; }
                                           case 15: {
      if( myt % 53 != 0) { stop =1; break; }  else    {  
      long long cl0,cl1; CPUCLOCK(cl0); 
       dumpbox_2(myt,x0,x1,n0,a0,coeff,spc,norms);  
       CPUCLOCK(cl1);  if(cl1 > cl0) Time += cl1-cl0;
   } 
                                           break; }
                                           case 16: {
                                             {;  excite_1(myt,x0,x1,n0,a0,coeff,spc,norms); ;}
                                           break; }
                                           case 17: {
      if( myt % 53 != 0) { stop =1; break; }  else    {  
      long long cl0,cl1; CPUCLOCK(cl0); 
       ff_1_xmin(myt,x0,x1,n0,a0,coeff,spc,norms);  
       CPUCLOCK(cl1);  if(cl1 > cl0) Time += cl1-cl0;
   } 
                                           break; }
                                           case 18: {
      if( myt % 53 != 0) { stop =1; break; }  else    {  
      long long cl0,cl1; CPUCLOCK(cl0); 
       ff_2_xmax(myt,x0,x1,n0,a0,coeff,spc,norms);  
       CPUCLOCK(cl1);  if(cl1 > cl0) Time += cl1-cl0;
   } 
                                           break; }
                                           case 19: {
      if( myt % 53 != 0) { stop =1; break; }  else    {  
      long long cl0,cl1; CPUCLOCK(cl0); 
       ff_3_ymin(myt,x0,x1,n0,a0,coeff,spc,norms);  
       CPUCLOCK(cl1);  if(cl1 > cl0) Time += cl1-cl0;
   } 
                                           break; }
                                           case 20: {
      if( myt % 53 != 0) { stop =1; break; }  else    {  
      long long cl0,cl1; CPUCLOCK(cl0); 
       ff_4_ymax(myt,x0,x1,n0,a0,coeff,spc,norms);  
       CPUCLOCK(cl1);  if(cl1 > cl0) Time += cl1-cl0;
   } 
                                           break; }
                                           case 21: {
      if( myt % 53 != 0) { stop =1; break; }  else    {  
      long long cl0,cl1; CPUCLOCK(cl0); 
       ff_5_zmin(myt,x0,x1,n0,a0,coeff,spc,norms);  
       CPUCLOCK(cl1);  if(cl1 > cl0) Time += cl1-cl0;
   } 
                                           break; }
                                           case 22: {
      if( myt % 53 != 0) { stop =1; break; }  else    {  
      long long cl0,cl1; CPUCLOCK(cl0); 
       ff_6_zmax(myt,x0,x1,n0,a0,coeff,spc,norms);  
       CPUCLOCK(cl1);  if(cl1 > cl0) Time += cl1-cl0;
   } 
                                           break; }
                                           case 23: {
      if( myt % 53 != 0) { stop =1; break; }  else    {  
      long long cl0,cl1; CPUCLOCK(cl0); 
      pthread_mutex_lock(&lck_023); output_it1(myt,x0,x1,n0,a0,coeff,spc,norms); pthread_mutex_unlock(&lck_023); 
       CPUCLOCK(cl1);  if(cl1 > cl0) Time += cl1-cl0;
   } 
                                           break; }
                                           case 24: {
      if( myt % 53 != 0) { stop =1; break; }  else    {  
      long long cl0,cl1; CPUCLOCK(cl0); 
      pthread_mutex_lock(&lck_024); output_it2(myt,x0,x1,n0,a0,coeff,spc,norms); pthread_mutex_unlock(&lck_024); 
       CPUCLOCK(cl1);  if(cl1 > cl0) Time += cl1-cl0;
   } 
                                           break; }
                                           case 25: {
      if( myt % 53 != 0) { stop =1; break; }  else    {  
      long long cl0,cl1; CPUCLOCK(cl0); 
      pthread_mutex_lock(&lck_025); output_ut1(myt,x0,x1,n0,a0,coeff,spc,norms); pthread_mutex_unlock(&lck_025); 
       CPUCLOCK(cl1);  if(cl1 > cl0) Time += cl1-cl0;
   } 
                                           break; }
                                           case 26: {
      if( myt % 53 != 0) { stop =1; break; }  else    {  
      long long cl0,cl1; CPUCLOCK(cl0); 
      pthread_mutex_lock(&lck_026); output_ut2(myt,x0,x1,n0,a0,coeff,spc,norms); pthread_mutex_unlock(&lck_026); 
       CPUCLOCK(cl1);  if(cl1 > cl0) Time += cl1-cl0;
   } 
                                           break; }
                                   default: break;
                                          } /* Switch */
                       pos += n0;
                    } /* For n */
          } /* Linecode */
  
void yee_h2e(int i0,int imax,int multi,int strat,int jobid)
{ /* yee */
     int clck; int unlocked_next=0;
     float *timing =  (float *)0x0000000013E8A340LL;
                    long long  time = 0, ncells = 0,cl0,cl1;  
  strat += 0;
  #undef NTT
  #define NTT(_y,_z) yee_YZ_lock[YZ(_y,_z)].U.t
  int sizefct = (imax-i0) / multi;
  
  for(int i=i0;i<imax;i+=multi) { /* Multi-loop */
   if (strat == 1) { /* new-classic-if */ 
   const int NY = 95,NZ = 34,NY0 = 95,NZ0 = 34; int dy,yy,zz;
   int z0 = yee_zint[jobid][0],z1=yee_zint[jobid][1]; 
   if (z1 > NZ0 ) z1 = NZ0;             
    if    (i+multi>imax)             multi = imax-i;
  
  
       for(int y=0;y<NY0+multi;y++)
       {
         for(dy=0,yy=y;dy<multi;dy++,yy--)
          if( yy >= 0 && yy < NY0 )
          for(zz=z0;zz<z1;zz++)
           { /* zz-loop */ 
              unsigned long tt = NTT(yy,zz);
              CPUCLOCK(cl0);
              if( zz==z0   &&  jobid != 0 && NTT(yy,zz-1) != tt+1  )
                       { long cnt = 0; while(NTT(yy,zz-1) != tt+1) cnt++;  yee_Y_wait[jobid][0]+=cnt; }
              if( zz==z1-1 &&  jobid != yee_jobs-1 && NTT(yy,zz+1) != tt ) 
                       { long cnt = 0; while(NTT(yy,zz+1) != tt) cnt++;   yee_Y_wait[jobid][1]+=cnt; }
              long long notime=0;
              interpreter_h2e(tt+1,yy,zz,ncells,notime);
              NTT(yy,zz) = tt+1;
              CPUCLOCK(cl1); if(cl1 > cl0) time += cl1-cl0 - notime;
           } /* zz-loop */ 
       } /*y-loop*/
   } else  { /* new-classic-if */
   int zshift = strat ? multi*jobid:0;
   int yshift = strat ? multi*jobid:0;
   const int NY = 95,NZ = 34,NY0 = 95,NZ0 = 34;
   int zmulti=0,dzmin,dzmax; 
   int ymulti=0,dymin,dymax; 
   int step,yy,zz,dy,dz,DY; 
   int y,z,delta,pos;
   static volatile int pos_last_job=0;
    if    (i+multi>imax)             multi = imax-i;
  
  
     if(strat) { zmulti = strat*multi;     dzmin = -zmulti ; dzmax = zmulti; }  
     else      { zmulti = NZ0;             dzmin = 0;        dzmax = NZ0;     } 
  
                 ymulti = NY0;             dymin = 0;        dymax = NY0;
  
     for(int z=-zshift;z<NZ0+zmulti;z+=zmulti)
       {  /* dy-loop */                        
   for(y=-yshift;y<NY0+ymulti;y+=ymulti)
    {  
       for(dy=dymin;dy<dymax;dy++)
         {
         for(dz=dzmin,zz=z+dzmin;dz<dzmax;dz++,zz++)
          if(zz>=0 && zz < NZ0)
            for(step=0,DY=dy,yy=y+dy;step<multi;step++,yy--,DY--)
              if( yy >= 0 && yy < NY0 )
               { /* zz-loop */ 
                 long long cl0,cl1,notime=0;
                 CPUCLOCK(cl0); 
                 int ok = 0;
                 if( dz >= 0 )
                   { 
                      int refstep = zmulti-dz-1;                                            
                      ok          = step <= refstep;                                          
                   } 
                 else 
                   { 
                      int refstep = -dz-1;                                                  
                      ok          = step >  refstep;                                          
                   } 
  
               if( strat==0 || ok) {  /* strat == 0 or ok */ 
              int myt; 
  int DDY=1;
  int DDZ=1;
                      if(step == 0 && (yy+DDY)<NY0 && (zz+DDZ)<NZ0) {                        
                             pthread_spin_lock(  & yee_YZ_lock[YZ(yy+DDY,zz+DDZ)].U.l);      
                             if(         !unlocked_next) { unlocked_next = 1; pthread_mutex_unlock( yee_job_lock+(jobid+1)%2 ); } 
                      }
  { myt = NTT(yy,zz) + 1; 
              interpreter_h2e(myt,yy,zz,ncells,notime);
  NTT(yy,zz) = myt; } 
                 if(step == multi-1)  {
                       pthread_spin_unlock(  & yee_YZ_lock[YZ(yy,zz) ].U.l);
                 }
                 } /* strat == 0 or ok */ 
                 CPUCLOCK(cl1);  if(cl1 > cl0) time += cl1-cl0-notime;
                } /* zz-loop */ 
               }  /* dy-loop */
              }  /* y-loop */
            }  /* z-loop */
        if( jobid == yee_jobs - 1 )   pos_last_job = -1; 
        } /* new - classic */
       } /* multi-loop */   
  timing[2*jobid]   += (float)ncells;
  timing[2*jobid+1] += (float)time*3.855050115651504e-10;
}/* yee */
  
  void init_locks(void) {
     pthread_mutex_init(&lck_013,&yee_mattr);
     pthread_mutex_init(&lck_023,&yee_mattr);
     pthread_mutex_init(&lck_024,&yee_mattr);
     pthread_mutex_init(&lck_025,&yee_mattr);
     pthread_mutex_init(&lck_026,&yee_mattr);
     pthread_mutex_init(&yee_lock_00000,&yee_mattr);
     pthread_mutex_init(&yee_lock_00001,&yee_mattr);
     pthread_mutex_init(&yee_lock_00002,&yee_mattr);
     pthread_mutex_init(&yee_lock_00003,&yee_mattr);
     pthread_mutex_init(&yee_lock_00004,&yee_mattr);
     pthread_mutex_init(&yee_lock_00005,&yee_mattr);
     pthread_mutex_init(&yee_lock_00006,&yee_mattr);
     pthread_mutex_init(&yee_lock_00007,&yee_mattr);
  }
  
/*******************************
   **** Yee Statistics
  *******************************
  
  Para
   N   = (96, 95, 34) = 7.44192 MBytes
   ev  = [1, 96, 9120]
   efk = 310080
  
  rlestat
  
  le          :        0.253 Mbytes ratio   7.11 % reuse  88.22 %
  lecap0      :        0.156 Mbytes ratio   4.38 % reuse  99.57 %
  lh          :        0.211 Mbytes ratio   5.93 % reuse  89.59 %
  me          :        0.166 Mbytes ratio   4.66 % reuse  99.42 %
  mecap0      :        0.153 Mbytes ratio   4.32 % reuse  99.67 %
  mh          :        0.149 Mbytes ratio   4.19 % reuse  99.87 %
  
    SUM      1.087 MBytes
  
  yle         :        0.176 Mbytes ratio   4.95 % reuse  94.37 %
  ylecap0     :        0.149 Mbytes ratio   4.20 % reuse  99.71 %
  ylh         :        0.148 Mbytes ratio   4.17 % reuse  99.97 %
  yme         :        0.392 Mbytes ratio  11.04 % reuse  92.17 %
  ymecap0     :        0.154 Mbytes ratio   4.35 % reuse  99.73 %
  ymh         :        0.155 Mbytes ratio   4.36 % reuse  99.75 %
  
    SUM      1.174 MBytes
  
  
  ystat
   nalloc         =      3.019 MBytes
   nspace         =      2.332 MBytes
   hits           = 3164016L
   misses         = 669456L = 17.463 %
   chunks         = 44L
   bigs           = 0L
   cachelines     = 0L
   cachesize      = 20000L
  
  Overview
    Brutto       1860.480 k components
    Netto        1473.120 k components
    Calc            0.000 k components
    Calls          19.682 k =      0.247 MBytes, 64.81 % big calls
  
    FillFactor       0.00 percent
  
  
*******************************/
  


static PyMethodDef moduleMethods[] = {
{"m_0000",m_0000,METH_VARARGS,0},
{"m_0001",m_0001,METH_VARARGS,0},
{"m_0002",m_0002,METH_VARARGS,0},
{0}
};

extern "C" DL_EXPORT(void) initcode_01(void) {
   PyObject *m;
   m = Py_InitModule("code_01",moduleMethods);
   import_array();
#ifdef MS_WIN32
   init_dict();
#endif
}
        
