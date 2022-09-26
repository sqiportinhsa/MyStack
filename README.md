# MyStack
Realization of stack in C/C++ with some useful functions.

## How to start using

* Download files "stack.cpp" and "stack.h" and add them to your project folder. 
* Include "stack.h" to start work with stacks.
* Do not forget to add "stack.cpp" to your makefile to compile it with your code. You can also make an object file from "stack.cpp" and use it directly

## Debug features

If you need some information about stack to debug your code, the "stack_logs" is for you.

* Download "stack_logs.cpp" and "stack_logs.h" and add them to your project folder.
* Include "stack_logs.h" everywhere you need.
* Compile "stack_logs.cpp" to the object file and add to all your object files at the moment of compilation.

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

## Testing and examples of using

I made some tests of StackPush and StackPop in "main.cpp". It is also an example of working with MyStack. You can download and edit it to run your own tests and learn
how to use functions. Use makefile to compile all files from repository together to play with them.

[Useful link](https://www.youtube.com/watch?v=dQw4w9WgXcQ)
