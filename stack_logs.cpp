#include "stack_logs.h"

#include <stdio.h>
#include <math.h>

void MakeLogs(Stack *stk, const char *file, const char *func, int line, int errors) {
    FILE *logs = fopen("logs.txt", "a");

        fprintf(logs, "Logs called in %s at %s(%d):\n", func, file, line);

    if (ErrorIsThere(errors, LOGS_PTR_CRASHED)) {
        fprintf(logs, "LOGS_PTR_CRASHED: information about creation of stack was lost.\n");
    } else {
        if (ErrorIsThere(errors, FILE_INF_CRASHED)) {
            fprintf(logs, "FILE_INFO_CRASHED: cannot find information about file of creation\n");
            if (ErrorIsThere(errors, FUNC_INF_CRASHED)) {
                fprintf(logs, "FUNC_INFO_CRASHED:");
                fprintf(logs, "cannot find information about function of creation\n");
            } else {
                fprintf(logs, "Stack [%p] created in function %s line %d.\n", &stk, 
                        stk->logs->func_of_creation, stk->logs->line_of_creation);
            }
        } else if (ErrorIsThere(errors, FUNC_INF_CRASHED)) {
            fprintf(logs, "Stack [%p] created in file %s (line: %d).\n", &stk, 
                    stk->logs->file_of_creation, stk->logs->line_of_creation);
            fprintf(logs, "FUNC_INFO_CRASHED:");
            fprintf(logs, "cannot find information about function of creation\n");
        } else {
            fprintf(logs, "Stack [%p] created at %s(%d) in function %s.\n", &stk, 
                    stk->logs->file_of_creation, stk->logs->line_of_creation, 
                    stk->logs->func_of_creation);
        }
    }

    if (ErrorIsThere(errors, SIZE_EXCEED_CAP)) {
        fprintf(logs, "Error: size exceed capacity\n");
    }

    fprintf(logs, "Stack info:\n");

    fprintf(logs, "{\n");
    fprintf(logs, "\t capacity = %lld\n", stk->capacity);
    fprintf(logs, "\t size     = %lld\n", stk->size);
    fprintf(logs, "\t data [%p]\n",       stk->data);

    if (ErrorIsThere(errors, DATA_PTR_CRASHED)) {
        fprintf(logs, "DATA_PTR_CRASHED: cannot print data, information was lost\n");
    } else {
        fprintf(logs, "\t {\n");
        for (size_t i = 0;         i < stk->size;     ++i) {
            fprintf(logs, "\t \t [%lld] = %f (busy)\n",   i, stk->data[i]);
        }
        for (size_t i = stk->size; i < stk->capacity; ++i) {
            fprintf(logs, "\t \t [%lld] = %f (poison)\n", i, stk->data[i]);
        }
        fprintf(logs, "\t }\n");
    }

    fprintf(logs, "}\n\n");

    fclose(logs);
}

int StackVerificator(Stack *stk) {
    int errors = NO_ERROR;

    if (stk->capacity < stk->size) {
        errors += SIZE_EXCEED_CAP;
    }

    if (stk->data == nullptr) {
        errors += DATA_PTR_CRASHED;
    }

    if (stk->logs == nullptr) {
        errors += LOGS_PTR_CRASHED;
    }

    if (!ErrorIsThere(errors, DATA_PTR_CRASHED) && !ErrorIsThere(errors, SIZE_EXCEED_CAP)) {
        for (size_t i = 0; i < stk->size; ++i) {
            if (isnan(stk->data[i])) {
                errors += INCORRECT_DATA;
                break;
            }
        }

        if (!ErrorIsThere(errors, INCORRECT_DATA)) {
            for (size_t i = stk->size; i < stk->capacity; ++i) {
                if (!isnan(stk->data[i])) {
                    errors += INCORRECT_DATA;
                    break;
                }
            }
        }
    }

    if (!ErrorIsThere(errors, LOGS_PTR_CRASHED)) {
        if (stk->logs->file_of_creation == nullptr) {
            errors += FILE_INF_CRASHED;
        }
        if (stk->logs->func_of_creation == nullptr) {
            errors += FUNC_INF_CRASHED;
        }
    }

    return errors;
}

int ErrorIsThere(int errors, Error error) {
    return (errors & error);
}
