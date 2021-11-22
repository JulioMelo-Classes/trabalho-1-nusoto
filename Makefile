GCC = g++
GCC_FLAGS = -I include -std=c++11 -Wall -Werror -fsanitize=address -g
EXEC_NAME = forca
BUILD_DIR = build

all: exec
exec: main.o Palavra.o Forca.o Score.o 
	$(GCC) $(GCC_FLAGS) -o ${EXEC_NAME} *.o
main.o: src/main.cpp include/Forca.hpp
	$(GCC) $(GCC_FLAGS) -c src/main.cpp
Palavra.o: src/Palavra.cpp include/Palavra.hpp
	$(GCC) $(GCC_FLAGS) -c src/Palavra.cpp
Forca.o: src/Forca.cpp include/Forca.hpp
	$(GCC) $(GCC_FLAGS) -c src/Forca.cpp
Score.o: src/Score.cpp include/Score.hpp
	$(GCC) $(GCC_FLAGS) -c src/Score.cpp
funcs.o: src/funcs.cpp include/funcs.hpp
	$(GCC) $(GCC_FLAGS) -c src/Score.cpp
clean:
	rm *.o