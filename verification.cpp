#include "verification.h"


int StackVerificator(Stack *stk) {
    int errors = NO_ERROR;

    if (stk->capacity < stk->size) {
        errors |= SIZE_EXCEED_CAP;
    }

    if (stk->data == nullptr) {
        errors |= DATA_PTR_CRASHED;
    }

    if (stk->logs == nullptr) {
        errors |= LOGS_PTR_CRASHED;
    }

    #ifdef DEEP_VERIFICATION

    if (!ErrorIsThere(errors, DATA_PTR_CRASHED) && !ErrorIsThere(errors, SIZE_EXCEED_CAP)) {
        for (size_t i = 0; i < stk->size; ++i) {
            if (IsPoisoned(stk->data[i])) {
                errors |= INCORRECT_DATA;
                break;
            }
        }

        if (!ErrorIsThere(errors, INCORRECT_DATA)) {
            for (size_t i = stk->size; i < stk->capacity; ++i) {
                if (!IsPoisoned(stk->data[i])) {
                    errors |= INCORRECT_DATA;
                    break;
                }
            }
        }
    }

    #endif

    #ifdef CANARY_VERIFICATION
    
    if (!ErrorIsThere(errors, DATA_PTR_CRASHED)) {
        Canary_t *l_border_ptr = (Canary_t*) ((char*)stk->data - sizeof(Canary_t*));
        Canary_t *r_border_ptr = (Canary_t*) ((char*)stk->data + sizeof(Elem_t) * stk->capacity);

        if (*l_border_ptr != Border) {
            errors |= L_BORDER_CHANGED;
        }

        if (*r_border_ptr != Border) {
            errors |= R_BORDER_CHANGED;
        }
    }
    
    #endif

    if (!ErrorIsThere(errors, LOGS_PTR_CRASHED)) {
        if (stk->logs->file_of_creation == nullptr) {
            errors |= FILE_INF_CRASHED;
        }
        if (stk->logs->func_of_creation == nullptr) {
            errors |= FUNC_INF_CRASHED;
        }
    }

    return errors;
}

int ErrorIsThere(int errors, Error error) {
    return (errors & error);
}
