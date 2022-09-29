#ifndef VERIFICATION
#define VERIFICATION

#include "stack.h"

#define DEEP_VERIFICATION
#define CANARY_VERIFICATION
#define HASH_VERIFICATION
#define SAFEMODE

#define StackVerificator(stk) SafeStackVerificator(stk, __FILE__, __PRETTY_FUNCTION__, __LINE__)

int SafeStackVerificator(Stack *stk, const char *file, const char *func, int line);
int ErrorIsThere(int errors, Error error);
size_t StackHash(Stack *stk);

#endif