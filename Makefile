BUILD_DIR = build
BIN_DIR = bin
$(shell mkdir -p $(BIN_DIR))
$(shell mkdir -p $(BUILD_DIR))
ASSETS_DIR = assets

FLAGS= -std=c++17 -g

WARNINGS=  -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align	\
		   -Wzero-as-null-pointer-constant -Wunused -Woverloaded-virtual -Wpedantic 		  	\
		   -Wconversion  -Wfloat-conversion -Wformat=2 -Werror=vla 		  						\
		   -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op     	\
		   -Wnull-dereference # -Wsign-conversion

INCLUDES=  -I ./includes 

LINKS= -L ./lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

OBJECTS= ./build/Board.o ./build/Title.o

build: $(OBJECTS)

copy_assets:
	xcopy $(ASSETS_DIR) $(BIN_DIR)\assets /E /I /Y
	
all: copy_assets $(OBJECTS)
	g++ $(FLAGS) $(WARNINGS) $(INCLUDES) ./src/main.cpp $(OBJECTS) $(LINKS) -o ./bin/main 

./build/Board.o: ./src/Board.cpp
	g++ $(FLAGS) $(WARNINGS) $(INCLUDES) ./src/Board.cpp -c -o ./$(BUILD_DIR)/Board.o

./build/Title.o: ./src/Title.cpp
	g++ $(FLAGS) $(WARNINGS) $(INCLUDES) ./src/Title.cpp -c -o ./$(BUILD_DIR)/Title.o
	
run: all
	./bin/main

run-main: 
	./bin/main

test: $(OBJECTS)
	g++ $(FLAGS) $(WARNINGS) $(INCLUDES) ./test.cpp $(OBJECTS) $(LINKS) -o ./bin/test
	./bin/test

clean:
	del /s .\build\*