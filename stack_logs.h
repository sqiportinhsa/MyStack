#ifndef STACK_LOGS
#define STACK_LOGS

#define LOGS_TO_FILE
//#define LOGS_TO_CONSOLE

#include "stack.h"

void DumpLogs(Stack *stk, const char *file, const char *func, int line, int errors);
void Print(FILE *logs, const char *format, ...);

#endif
