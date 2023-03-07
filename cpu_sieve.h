
// cpu_sieve.h

typedef struct {

	uint64_t pmin = 0, pmax = 0;
	uint32_t kmin = 0, kmax = 0;	// note k is 32 bit!
	uint32_t nmin = 0, nmax = 0;
	uint32_t nstep;
	uint32_t mont_nstep;
	int32_t bbits;
	uint64_t r0;
	int32_t bbits1;
	uint64_t r1;
	uint64_t lastN;
	bool cw = false;
	bool test = false;
	bool avx512 = false;
	uint64_t checksum = 0;
	uint32_t threads = 1;
	uint64_t primecount = 0;
	uint64_t factorcount = 0;
	double wu_range;

	uint64_t workunit;
	uint64_t p;	// current p
	bool write_state_a_next = true;

//	tpsieve option -M2, change K's modulus to 2
	uint32_t kstep = 2;
	uint32_t koffset = 1;
//	default for twin prime search
//	uint32_t kstep = 6;
//	uint32_t koffset = 3;


}searchData;


// buffer for factors found
const uint32_t numresults = 1000000u;

// 1 if a number mod 15 is not divisible by 2 or 3.
//                      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
const int prime15[] = { 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1 };


/* shared data between threads */
//-------------------------------
extern uint64_t g_primecount;
extern uint64_t g_checksum;
extern pthread_mutex_t lock1;
//-------------------------------
extern uint64_t g_complete;
extern pthread_mutex_t lock2;
//-------------------------------


typedef struct _thread_data_t {
	int id;
	searchData sd;
	uint64_t pmin,pmax;
} thread_data_t;


extern FILE *my_fopen(const char * filename, const char * mode);

extern void gatherfactors( searchData & sd );

extern int read_state_thread( searchData sd, uint64_t & current_p, int thread_id, bool & state_a, uint64_t & primecount, uint64_t & checksum);

extern void checkpoint_thread( searchData sd, uint64_t my_P, int thread_id, bool & state_a, uint64_t primecount, uint64_t checksum  );

extern void clear_factors_file( int thread_id );

extern void report_solution_temp( char * results, int thread_id );

extern void ckerr(int err);

extern bool goodfactor_cw(uint32_t uk, uint32_t n, int c);

extern bool goodfactor(uint32_t uk, uint32_t n, int c);

extern void *thr_func_cw_avx512(void *arg);

extern void *thr_func_avx512(void *arg);

extern void *thr_func_cw(void *arg);

extern void *thr_func(void *arg);

extern void cpu_sieve( searchData & sd );

extern void run_test( searchData & sd );
