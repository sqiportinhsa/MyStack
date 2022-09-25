#include <stdio.h>
#include <math.h>

#ifndef STACK
#define STACK

typedef double Elem_t;
const Elem_t Poisoned_cell = NAN;

typedef struct {
    int   line_of_creation;
    char* file_of_creation;
    char* func_of_creation;
} Logs;

typedef struct {
    Elem_t*  data;
    size_t   size;
    size_t   capacity;
    Logs*    logs;
} Stack;

typedef enum {
    NO_ERROR     = 0,
    MEMORY_EXC   = 1,
    EMPTY_STACK  = 2,
    SIZE_EXC_CAP = 4,
    SIZE_CRASHED = 8,
} Error;

#define StackCtr(stk, n_elem)                                                              \
        StackCtrWithLogs(stk, n_elem, __LINE__, __PRETTY_FUNCTION__, __FILE__);

Error StackCtrWithLogs(Stack *stk, size_t n_elem, int line, const char *func, const char *file);
Error StackDestr(Stack *stk);
Error StackPush(Stack *stk, Elem_t value);
Error StackPop(Stack *stk);
Error ResizeStack(Stack *stk, size_t capacity);
Error PoisonCells(Stack *stk, size_t n_cells);

#endif
