#ifndef STACK
#define STACK

#include <stdio.h>
#include <math.h>

typedef double Elem_t;
const Elem_t Poisoned_cell = nan("57");

typedef unsigned long long Canary_t;
const Canary_t Border = 0XBAAD7004;

typedef struct {
    Canary_t     left_border;
    int         line_of_creation;
    const char* file_of_creation;
    const char* func_of_creation;
    Canary_t     right_border;
} Logs;

typedef struct {
    Canary_t  left_border;
    Elem_t*  data;
    size_t   size;
    size_t   capacity;
    Logs*    logs;
    Canary_t  right_border;
} Stack;

typedef enum {
    NO_ERROR         = 0,
    EMPTY_STACK      = 1,
    MEMORY_EXCEED    = 2,
    SIZE_EXCEED_CAP  = 4,
    INCORRECT_DATA   = 8,
    DATA_PTR_CRASHED = 16,
    LOGS_PTR_CRASHED = 32,
    FILE_INF_CRASHED = 64,
    FUNC_INF_CRASHED = 128,
    R_BORDER_CHANGED = 256,
    L_BORDER_CHANGED = 512,
    OPEN_LOGFILE_ERR = 1024,
} Error;

#define StackCtr(stk, n_elem)                                                 \
        StackCtrWithLogs(stk, n_elem, __LINE__, __PRETTY_FUNCTION__, __FILE__);

Error StackCtrWithLogs(Stack *stk, size_t n_elem, int line, const char* func, const char* file);
Error StackDestr(Stack *stk);
Error StackPush(Stack *stk, Elem_t value);
Error StackPop(Stack *stk);
Error ResizeStack(Stack *stk, size_t capacity);
Error PoisonCells(Stack *stk, size_t n_cells);
int IsPoisoned(double el1);

#endif
