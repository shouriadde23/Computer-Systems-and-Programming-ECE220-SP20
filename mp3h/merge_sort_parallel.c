#include "merge_sort.h"
#include <pthread.h>

#define THRESHOLD 125000
int threadNum = 0;

void* merge_sort_thread_wrapper(void *arg){
    Node* head = (Node*)arg;
    int length = 0;
    Node* new_head = split_ll(head, &length);

    // if number of nodes less than threshold, use sequential version
    if (length < THRESHOLD) {
        head = merge_sort(head);
        new_head = merge_sort(new_head);
        head = merge_ordered_ll(head, new_head);
        pthread_exit((void*)head);
    }

    // @TODO insert your code here

    // create first thread
    pthread_t thread1;
    threadNum++;
    pthread_create(&thread1, NULL, merge_sort_thread_wrapper, (void*) head);

    // create second thread
    pthread_t thread2;
    threadNum++;
    pthread_create(&thread2, NULL, merge_sort_thread_wrapper, (void*) new_head);

    // join the two threads
    Node *newHead1;
    Node *newHead2;
    pthread_join(thread1, (void**)&newHead1);
    pthread_join(thread2, (void**)&newHead2);

    // merge the two heads that were generated from the threads
    head = merge_ordered_ll(newHead1, newHead2);

    // stop generating threads
    pthread_exit((void*) head);
    return NULL;

}



int main() {
    Node* head = make_ll_from_file("input.txt");

    // @TODO insert your code here
    pthread_t thread;
    pthread_create(&thread, NULL, merge_sort_thread_wrapper, (void*) head);
    pthread_join(thread, (void**)&head);

    print_list(head,"parallel_output.txt");
    free_list(head);
    return 0;
}
