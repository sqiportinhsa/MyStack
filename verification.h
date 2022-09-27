#ifndef VERIFICATION
#define VERIFICATION

#include "stack.h"

#define DEEP_VERIFICATION
//#define CANARY_VERIFICATION
//#define HASH_VERIFICATION

int StackVerificator(Stack *stk);
int ErrorIsThere(int errors, Error error);
size_t StackHash(Stack *stk);

#endif