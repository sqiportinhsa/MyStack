# MyStack
Realization of stack in C/C++ with some useful functions.

## How to start using

* Download files "stack.cpp" and "stack.h" and add them to your project folder. 
* Include "stack.h" to start work with stacks.
* Do not forget to add "stack.cpp" to your makefile to compile it with your code. You can also make an object file from "stack.cpp" and use it directly

## Debug features

If you need some information about stack to debug your code, the "stack_logs" and "verification" are for you.

* Download "stack_logs.cpp", "verification.cpp", "stack_logs.h" and "verification.h" and add them to your project folder.
* Include "stack_logs.h" and "verification.h" everywhere you need.
* Compile "stack_logs.cpp" and "verification.cpp" to the object file and add to all your object files at the moment of compilation.

### Verification modes
There are some different ways to verificate your stack:

* Basic verification will be completed automatically when you call verification function. It checks stack for crashed pointers (to data, logs info) and matching of size and capacity. 
* Deep verification. Checks if stack data is correct by checkup for unexpected poison in cells with data and for unexpected non-poison data in cells that should be poisoned. You need to turn on this mode in the "verification.h" by using define (already defined in the last versions here):
```c++
#define DEEP_VERIFICATION
```

* Canary protection. Protect your stack from unexpected loosing of data caused by ascessiion from near-stored structures. It is represented by two border elements around the stack data and borders around the stack and logs info. This checkup will notify you if borders will be suddenly changed. You need to turn on this mode in the "verification.h" by using define (already defined in the last versions here):
```c++
#define CANARY_VERIFICATION
```
* Hash verification. Turn on this checkup to be warned if the data will be changed not by using functions from "stack". Verification based on GNU hash. To turn on this mode you need to define it in the "verification.h" (already defined in the last versions here):
```c++
#define HASH_VERIFICATION
```

### Logs output

Use DumpLogs to dump logs to logfile or to your console. If you want to dump logs to file print
```c++
#define LOGS_TO_FILE
```
in "stack_logs.h" (was defined by default). It creates or opens an existing "logs.txt" file for adding information and dump logs there.

If you want to dump logs to console print
```c++
#define LOGS_TO_CONSOLE
```
in "stack_logs.h".

You can use both of this defines at same time, only one or none of them.

### Safemode
This define turns on logs output to logfile everytime your verification returned errors, you don't need to do it by yourself anymore. Turn on by defining in "verification.h" (already defined in the last versions):
```c++
#define SAFEMODE
```

## Functions using
* Constructor
```c++
StackCrtr(&stk);
```
* Destructor
```c++
StackDtrs(&stk);
```
* Push
```c++
StackPush(&stk, Elem_t value);
```
* Pop

Returns the last element from Stack. It can change the error value using pointer to it. Also has default mode without returning error using default pointer value.
```c++
Elem_t popped = StackPop(&stk, int* error);
```
* Safe and unsafe Verificator

Verify your Stack using verificators from your settings. Safe version dumps logs automatically if errors != 0.
```c++
int errors1 = SafeStackVerificator(&stk);
int errors2 = StackVerificator(&stk);
```
* Dump logs
```
DumpLogs(&stk);
```

## Examples of using
You can look at "main.cpp" as example of working with MyStack. It shows how to construct stack, push and pop elements and do verification. Run it to see how safemode verification catch editing stack info and dump logs. 

Windows: To compile download all files and use "make" command from your terminal. You store all files in one folder and have folders bin and build for object files and executable file in it. 

Linux: you need to create your own makefile because of difference in operation systems.

[Useful link](https://www.youtube.com/watch?v=dQw4w9WgXcQ)
