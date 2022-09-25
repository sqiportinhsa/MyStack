#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Error StackCtrWithLogs(Stack *stk, size_t n_elem, int line, const char *func, const char *file) {
    stk->logs = (Logs*) calloc(1, sizeof(Logs));

    stk->logs->file_of_creation = (char*) calloc(sizeof(file), sizeof(char));
    stk->logs->func_of_creation = (char*) calloc(sizeof(func), sizeof(char));

    strcpy(stk->logs->file_of_creation, file);
    strcpy(stk->logs->func_of_creation, func);
    
    stk->logs->line_of_creation = line;

    stk->data = (Elem_t*) calloc(n_elem, sizeof(Elem_t));
    stk->capacity = n_elem;
    stk->size     = 0;

    if (stk->data == nullptr) {
        return MEMORY_EXC;
    }

    return PoisonCells(stk, n_elem);
}

Error StackDestr(Stack *stk) {
    stk->size = 0;
    PoisonCells(stk, stk->capacity);
    ResizeStack(stk, 0);
    stk->data = nullptr;
    return NO_ERROR;
}

Error PoisonCells(Stack *stk, size_t n_cells) {
    if (stk->size + n_cells > stk->capacity + 1) {
        return SIZE_EXC_CAP;
    }

    for (size_t i = 0; i < n_cells; ++i) {
        (stk->data)[stk->size + i] = Poisoned_cell;
    }

    return NO_ERROR;
}

Error StackPush(Stack *stk, Elem_t value) {
    if (stk->size >= stk->capacity) {
        ResizeStack(stk, stk->capacity * 2);
    }

    if (isnan(stk->data[stk->size - 1]) || !isnan(stk->data[stk->size])) {
        return SIZE_CRASHED;
    }
    stk->data[stk->size] = value;
    ++(stk->size);
    
    return NO_ERROR;
}

Error StackPop(Stack *stk) {
    if (stk->size == 0) {
        return EMPTY_STACK;
    }

    Error err = NO_ERROR;

    --(stk->size);
    
    err = PoisonCells(stk, 1);
    err = ResizeStack(stk, stk->capacity);

    return err;
}

Error ResizeStack(Stack *stk, size_t capacity) {
    if (stk->capacity < capacity) {
        stk->data = (Elem_t*) realloc(stk->data, capacity * sizeof(Elem_t));
        stk->capacity = capacity;
        PoisonCells(stk, stk->capacity / 2);
    }

    if (stk->size < capacity / 2) {
        stk->data = (Elem_t*) realloc(stk->data, capacity * sizeof(Elem_t) / 2);
        stk->capacity = capacity / 2;
    }

    if (capacity == 0) {
        stk->data = (Elem_t*) realloc(stk->data, 0);
        stk->capacity = 0;
    }

    if (stk->data == nullptr) {
        return MEMORY_EXC;
    }

    return NO_ERROR;
}
