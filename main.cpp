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
        DumpLogs(&stk, __FILE__, __PRETTY_FUNCTION__, __LINE__, StackVerificator(&stk));
    }

    for (size_t i = 0; i < 10; ++i) {
        err |= StackPop(&stk);
        DumpLogs(&stk, __FILE__, __PRETTY_FUNCTION__, __LINE__, StackVerificator(&stk));
    }

    if (err == 0) {
        printf("There is no errors\n");
    } else {
        printf("Test failed. Check logs please.\n");
    }

    return 0;
}