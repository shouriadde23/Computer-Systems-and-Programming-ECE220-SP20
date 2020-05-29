#include "acc.h"

int main() {
    unsigned long long ret = 0;

    // @TODO insert your code here
    int i = 0;

    for(i= 0; i < NUM_THREADS; i++) {
        ret += acc_file(i);
    }

    FILE *out = fopen("serial_output.txt", "w");
    fprintf(out, "%llu\n", ret);
    fclose(out);

    return 0;
}
