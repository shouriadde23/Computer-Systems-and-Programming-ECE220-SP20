#include "thread_info.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef NUM_THREADS
    #define NUM_THREADS 13 // [1, 99]
#endif

#define FILE_NAME_LEN 23

const char* FILE_NAME_PREFIX = "input/acc_input.part";
unsigned long long result; // each thread accumulates the result in this variable
pthread_mutex_t lock_for_result; // lock for shared result


/*
    Read and compute the sum of all numbers within the file "input/acc_input.partxx"

    ARGS:
        int i -> the file index
    RET:
        the sum of all numbers with in the file
*/
unsigned long long acc_file(int i) {
    unsigned long long result = 0;

    char str[FILE_NAME_LEN];
    FILE *fPoint;

    sprintf(str, "input/acc_input.part%02d", i);
    fPoint = fopen(str, "r");
    while(!feof(fPoint)) {
        int val = 0;
        fscanf(fPoint, "%u", &val);
        result += val;
    }

    return result;
}

/*
    A pthread compatible wrapper that calls acc_file
    This is the entry point of each thread when calling pthread_create

    The input to this funtion should specify the index of the input file for the thread
    This function should call acc_file and accumulate the sub-total into the variable result
    ARGS:
        void* arg -> a pointer to the memory location where the argument is placed
    RET:
        NULL
*/
void *parallel_acc_wrapper(void *arg) {
    int index = *((int *)arg);

    unsigned long long tot = acc_file(index);
    pthread_mutex_lock(&lock_for_result);
    result += tot;
    pthread_mutex_unlock(&lock_for_result);
    return NULL;
}
