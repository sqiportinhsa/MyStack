#include <stdio.h>
#include "stack.h"
#include "stack_logs.h"
#include "verification.h"

int main() {
    int err = 0;

    Stack stk = {};

    err |= StackCtr(&stk, 0);

    DumpLogs(&stk);

    for (size_t i = 0; i < 10; ++i) {
        err |= StackPush(&stk, (double) i);
        DumpLogs(&stk);
    }

    for (size_t i = 0; i < 5; ++i) {
        int c = (int) StackPop(&stk, &err);
        if (c != 9 - (int) i) {
            printf("popped %d, expected %d\n", c, 10 - (int) i);
            DumpLogs(&stk);
        }
        DumpLogs(&stk);
    }

    stk.data[5] = 14;

    err |= SafeStackVerificator(&stk);

    if (err == 0) {
        printf("There is no errors\n");
    } else {
        printf("Test failed. Error code: %d. Check logs please.\n", err);
    }

    DumpLogs(nullptr);

    StackDestr(&stk);
    DumpLogs(&stk);

    return 0;
}