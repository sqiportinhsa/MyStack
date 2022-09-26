#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Error StackCtrWithLogs(Stack *stk, size_t n_elem, int line, const char* func, const char* file) {
    stk->logs = (Logs*) calloc(1, sizeof(Logs));

    if (stk->logs == nullptr) {
        return MEMORY_EXCEED;
    }

    stk->logs->file_of_creation = file;
    stk->logs->func_of_creation = func;
    stk->logs->line_of_creation = line;

    stk->logs->left_border  = Border;
    stk->logs->right_border = Border;

    stk->data = (Elem_t*) calloc(n_elem * sizeof(Elem_t) + 2 * sizeof(Canary_t), sizeof(char));

    if (stk->data == nullptr) {
        return MEMORY_EXCEED;
    }

    stk->data = (Elem_t*) ((char*) stk->data + sizeof(Canary_t));

    stk->capacity = n_elem;
    stk->size     = 0;

    stk->left_border  = Border;
    stk->right_border = Border;

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
        return SIZE_EXCEED_CAP;
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

    if (IsPoisoned(stk->data[stk->size - 1]) || !IsPoisoned(stk->data[stk->size])) {
        return INCORRECT_DATA;
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
    Canary_t *l_border_ptr = (Canary_t*) ((char*)stk->data - sizeof(Canary_t*));

    if (stk->capacity < capacity) {
        stk->data = (Elem_t*) realloc(l_border_ptr, capacity * sizeof(Elem_t) 
                                                         + 2 * sizeof(Canary_t));
        if (stk->data == nullptr) {
            return MEMORY_EXCEED;
        }

        stk->data = (Elem_t*) ((char*)stk->data + sizeof(Canary_t));
        stk->capacity = capacity;

        PoisonCells(stk, stk->capacity / 2);
    }

    if (stk->size < capacity / 2) {
        stk->data = (Elem_t*) realloc(l_border_ptr, capacity * sizeof(Elem_t) / 2 
                                                         + 2 * sizeof(Canary_t));
        if (stk->data == nullptr) {
            return MEMORY_EXCEED;
        }

        stk->data = (Elem_t*) ((char*)stk->data + sizeof(Canary_t));
        stk->capacity = capacity / 2;
    }

    if (capacity == 0) {
        stk->data = (Elem_t*) realloc(l_border_ptr, 2 * sizeof(Canary_t));

        if (stk->data == nullptr) {
            return MEMORY_EXCEED;
        }

        stk->capacity = 0;
    }

    Canary_t *r_border_ptr = (Canary_t*) ((char*)stk->data + sizeof(Elem_t) * stk->capacity);
    *r_border_ptr = Border;

    return NO_ERROR;
}

int IsPoisoned(double el1) {
    if (memcmp(&el1, &Poisoned_cell, sizeof(Elem_t)) == 0) {
        return 1;
    }
    return 0;
}
