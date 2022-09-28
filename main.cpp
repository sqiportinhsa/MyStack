#include <stdio.h>
#include "stack.h"
#include "stack_logs.h"
#include "verification.h"

int main() {
    int err = 0;

    Stack stk = {};

    err |= StackCtr(&stk, 3);

    for (size_t i = 0; i < 10; ++i) {
        err |= StackPush(&stk, (double) i);
        err |= StackVerificator(&stk);
    }

    stk.data[3] = Poisoned_cell;
    err |= StackVerificator(&stk);

    for (size_t i = 0; i < 5; ++i) {
        err |= StackPop(&stk);
        err |= StackVerificator(&stk);
    }

    stk.data[stk.size] = 14;
    err |= StackVerificator(&stk);

    if (err == 0) {
        printf("There is no errors\n");
    } else {
        printf("Test failed. Error code: %d. Check logs please.\n", err);
    }

    return 0;
}