#ifndef STACK
#define STACK

#include <stdio.h>
#include <math.h>

typedef double Elem_t;
const Elem_t Poisoned_cell = nan("57");

typedef unsigned long long Canary_t;
const Canary_t Border = 0XBAAD7004;

const size_t Hash_base_const = 5381;
const size_t Hash_mult_const = 33;

typedef struct {
    Canary_t     left_border;
    int          line_of_creation;
    const char*  file_of_creation;
    const char*  func_of_creation;
    Canary_t     right_border;
} Logs;

typedef struct {
    Canary_t  left_border;
    Elem_t*   data;
    size_t    size;
    size_t    capacity;
    size_t    hash;
    Logs*     logs;
    Canary_t  right_border;
} Stack;

typedef enum {
    NO_ERROR         = 0,
    HASH_CALC_ERR    = 1,
    HASH_DISMATCH    = 2,
    EMPTY_STACK      = 4,
    MEMORY_EXCEED    = 8,
    UNEXPECTED_PSN   = 16,
    UNEXPECTED_ELM   = 32,
    SIZE_EXCEED_CAP  = 64,
    STCK_PTR_CRASHED = 128,
    DATA_PTR_CRASHED = 256,
    LOGS_PTR_CRASHED = 512,
    FILE_INF_CRASHED = 1024,
    FUNC_INF_CRASHED = 2048,
    R_BORDER_CHANGED = 4096,
    L_BORDER_CHANGED = 8192,
    OPEN_LOGFILE_ERR = 16384,
    STK_BRDR_CHANGED = 32768,
    LGS_BRDR_CHANGED = 65536,
} Error;

#define StackCtr(stk, n_elem)                                                 \
        StackCtrWithLogs(stk, n_elem, __LINE__, __PRETTY_FUNCTION__, __FILE__)


Error StackCtrWithLogs(Stack *stk, size_t n_elem, int line, const char* func, const char* file);
int StackDestr(Stack *stk);
int StackPush(Stack *stk, Elem_t value);
Elem_t StackPop(Stack *stk, int *err);
Error ResizeStack(Stack *stk, size_t capacity);
Error PoisonCells(Stack *stk, size_t n_cells);
int IsPoisoned(double el1);

#endif
