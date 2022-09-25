#include "stack_logs.h"

#include <stdio.h>

void MakeLogs(Stack *stk, const char *file, const char *func, int line) {
    FILE *logs = fopen("logs.txt", "a");
    Logs *stk_logs = stk->logs;

    fprintf(logs, "%s at %s(%d):\n", func, file, line);
    fprintf(logs, "Stack [%p] created at %s(%d) in function %s:\n", &stk, 
            stk_logs->file_of_creation, stk_logs->line_of_creation, stk_logs->func_of_creation);
    fprintf(logs, "{\n");
    fprintf(logs, "\t capacity = %lld\n", stk->capacity);
    fprintf(logs, "\t size     = %lld\n", stk->size);
    fprintf(logs, "\t data [%p]\n",       stk->data);
    fprintf(logs, "\t {\n");
    for (size_t i = 0;         i < stk->size;     ++i) {
        fprintf(logs, "\t \t [%lld] = %f (busy)\n",   i, stk->data[i]);
    }
    for (size_t i = stk->size; i < stk->capacity; ++i) {
        fprintf(logs, "\t \t [%lld] = %f (poison)\n", i, stk->data[i]);
    }
    fprintf(logs, "\t }\n");
    fprintf(logs, "}\n\n");

    fclose(logs);
}
