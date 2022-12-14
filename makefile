TARGET = build\main.exe
CPPFLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE -Werror=vla

.PHONY: all
all: $(TARGET)

$(TARGET): bin\main.o bin\stack.o bin\stack_logs.o bin\stack_verification.o
	g++ bin\main.o bin\stack.o bin\stack_logs.o bin\stack_verification.o  -o $(TARGET) $(CPPFLAGS)

bin\main.o: main.cpp stack.h stack_verification.h stack_logs.h
	g++ -c main.cpp -o bin\main.o $(CPPFLAGS)

bin\stack.o: stack.cpp stack.h stack_verification.h stack_logs.h
	g++ -c stack.cpp -o bin\stack.o $(CPPFLAGS)

bin\stack_logs.o: stack_logs.cpp stack_logs.h stack.h stack_verification.h
	g++ -c stack_logs.cpp -o bin\stack_logs.o $(CPPFLAGS)

bin\stack_verification.o: stack_verification.cpp stack_verification.h stack.h
	g++ -c stack_verification.cpp -o bin\stack_verification.o $(CPPFLAGS)