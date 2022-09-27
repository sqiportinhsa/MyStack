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
        DumpLogs(&stk, __FILE__, __PRETTY_FUNCTION__, __LINE__, err);
    }

    for (size_t i = 0; i < 10; ++i) {
        err |= StackPop(&stk);
        err |= StackVerificator(&stk);
        DumpLogs(&stk, __FILE__, __PRETTY_FUNCTION__, __LINE__, err);
    }

    if (err == 0) {
        printf("There is no errors\n");
    } else {
        printf("Test failed. Error code: %d. Check logs please.\n", err);
    }

    return 0;
}