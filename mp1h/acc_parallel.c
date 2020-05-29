#include "acc.h"
#include <pthread.h>

int main() {
    unsigned long long ret = 0;

    int result;
    int i;
    pthread_t threads[NUM_THREADS];
    int mem_thread[NUM_THREADS];

    for(i = 0; i < NUM_THREADS; i++) {
        mem_thread[i] = i;
        pthread_create(&threads[i], NULL, &parallel_acc_wrapper, (void*)&mem_thread[i]);
    }

    for(i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], &result);
        ret = ret + thread_mem[i];

    }

    FILE *out = fopen("parallel_output.txt", "w");
    fprintf(out, "%llu\n", ret);
    fclose(out);
    return 0;
}
