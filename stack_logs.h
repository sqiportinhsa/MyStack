#ifndef STACK_LOGS
#define STACK_LOGS

#include "stack.h"

void MakeLogs(Stack *stk, const char *file, const char *func, int line, int errors);
int StackVerificator(Stack *stk);
int ErrorIsThere(int errors, Error error);

#endif
