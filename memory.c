#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>
#include <timer.h>

#define NTHREADS 20
#define TIME_BETWEEN_THREADS_IN_SECONDS 3

#define MEMORY_MAX_FRAMES 64
#define PROCESS_MAX_PAGES 50

#define WORKING_SET_LIMIT 4

typedef int bool;
#define FALSE 0
#define TRUE 1

typedef struct
{
	
	int allocated_pages = 0; 
	page pages[PROCESS_MAX_PAGES];
	

	// For FIFO process scheduling
	double time_last_page_added;

}page_table;

typedef struct
{
	bool is_empty;
	int frame;
}page;

void * process(void * arg){
	int* p;
	int pid;

	p = (int *) arg;
	pid = *p;
	printf("Starting process %d\n", pid);



	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	int i;
	int * pid;
	// Vetor de threads
	pthread_t threads[NTHREADS];

    /* Cria as threads */
	for ( i = 0; i < NTHREADS; ++i)
	{
		pid = (int *) malloc(sizeof(int));
        *pid = i;
		pthread_create(&threads[i], NULL, process, pid);
		sleep(TIME_BETWEEN_THREADS_IN_SECONDS);
	}

	/* Espera todas as threads completarem */
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }


	return 0;
}
