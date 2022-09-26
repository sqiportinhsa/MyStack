#include "stack_logs.h"

#include <stdio.h>
#include <math.h>
#include <stdarg.h>

#define LOGS_TO_FILE
//#define LOGS_TO_CONSOLE

void DumpLogs(Stack *stk, const char *file, const char *func, int line, int errors) {
    FILE *logs = nullptr;

    #ifdef LOGS_TO_FILE

    logs = fopen("logs.txt", "a");

    if (logs == nullptr) {
        return;
    }

    #endif

    #ifndef LOGS_TO_FILE
    #ifdef LOGS_TO_CONSOLE
    logs = stdout;
    #endif
    #endif

    Print(logs, "Logs called in %s at %s(%d):\n", func, file, line);

    if (ErrorIsThere(errors, LOGS_PTR_CRASHED)) {
        Print(logs, "LOGS_PTR_CRASHED: information about creation of stack was lost.\n");

    } else {
        if (ErrorIsThere(errors, FILE_INF_CRASHED)) {
            Print(logs, "FILE_INFO_CRASHED: cannot find information about file of creation\n");

            if (ErrorIsThere(errors, FUNC_INF_CRASHED)) {
                Print(logs, "FUNC_INFO_CRASHED:");
                Print(logs, "cannot find information about function of creation\n");
            } else {
                Print(logs, "Stack [%p] created in function %s line %d.\n", &stk, 
                        stk->logs->func_of_creation, stk->logs->line_of_creation);
            }

        } else if (ErrorIsThere(errors, FUNC_INF_CRASHED)) {
            Print(logs, "Stack [%p] created in file %s (line: %d).\n", &stk, 
                    stk->logs->file_of_creation, stk->logs->line_of_creation);
            Print(logs, "FUNC_INFO_CRASHED:");
            Print(logs, "cannot find information about function of creation\n");
            
        } else {
            Print(logs, "Stack [%p] created at %s(%d) in function %s.\n", &stk, 
                    stk->logs->file_of_creation, stk->logs->line_of_creation, 
                    stk->logs->func_of_creation);
        }
    }

    if (ErrorIsThere(errors, SIZE_EXCEED_CAP)) {
        Print(logs, "Error: size exceed capacity\n");
    }

    Print(logs, "Stack info:\n");

    Print(logs, "{\n");
    Print(logs, "\t capacity = %lld\n", stk->capacity);
    Print(logs, "\t size     = %lld\n", stk->size);
    Print(logs, "\t data [%p]\n",       stk->data);

    if (ErrorIsThere(errors, DATA_PTR_CRASHED)) {
        Print(logs, "DATA_PTR_CRASHED: cannot print data, information was lost\n");
    } else {
        Print(logs, "\t {\n");

        #ifdef CANARY_VERIFICATION
        if (ErrorIsThere(errors, L_BORDER_CHANGED)) {
            Print(logs, "\t \t Left  Border = %lld (expected %lld)\n", stk->left_border, Border);
        } else {
            Print(logs, "\t \t Left  Border = %lld (OK)\n", stk->left_border);
        }
        #endif

        for (size_t i = 0;         i < stk->size;     ++i) {
            Print(logs, "\t \t [%lld] = %f (busy)\n",   i, stk->data[i]);
        }
        for (size_t i = stk->size; i < stk->capacity; ++i) {
            Print(logs, "\t \t [%lld] = %f (poison)\n", i, stk->data[i]);
        }

        #ifdef CANARY_VERIFICATION
        if (ErrorIsThere(errors, R_BORDER_CHANGED)) {
            Print(logs, "\t \t Right Border = %lld (expected %lld)\n", stk->right_border, Border);
        } else {
            Print(logs, "\t \t Right Border = %lld (OK)\n", stk->right_border);
        }
        #endif

        Print(logs, "\t }\n");
    }

    Print(logs, "}\n\n");

    #ifdef LOGS_TO_FILE
    fclose(logs);
    #endif
}

void Print(FILE *output, const char *format, ...) {
    va_list ptr = {};
    va_start(ptr, format);

    if (output == nullptr) {
        return;
    }

    #ifdef LOGS_TO_FILE

    vfprintf(output, format, ptr);

    #endif

    #ifdef LOGS_TO_CONSOLE
    #ifdef LOGS_TO_FILE

    vfprintf(stdout, format, ptr);

    #endif
    #ifndef LOGS_TO_FILE

    vfprintf(output, format, ptr);

    #endif
    #endif

    va_end(ptr);
}
