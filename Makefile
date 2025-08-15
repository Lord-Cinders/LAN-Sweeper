FLAGS= -std=c++17 -g

WARNINGS=  -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align	\
		   -Wzero-as-null-pointer-constant -Wunused -Woverloaded-virtual -Wpedantic 		  	\
		   -Wconversion  -Wfloat-conversion -Wformat=2 -Werror=vla 		  						\
		   -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op     	\
		   -Wnull-dereference # -Wsign-conversion

INCLUDES=  -I ./includes

LINKS= -L ./lib -lmingw32 -lSDL2main -lSDL2 

OBJECTS= 

all: $(OBJECTS)
	g++ $(FLAGS) $(WARNINGS) $(INCLUDES) ./src/main.cpp $(OBJECTS) $(LINKS) -o ./bin/main 

build: $(OBJECTS)

run: all
	./bin/main

run-main: 
	./bin/main

test: $(OBJECTS)
	g++ $(FLAGS) $(WARNINGS) $(INCLUDES) ./test.cpp $(OBJECTS) $(LINKS) -o ./bin/test
	./bin/test

clean:
	del /s .\build\*