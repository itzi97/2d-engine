# Files
CPPFILES = $(wildcard *.cpp)
OBJFILES = $(CPPFILES:.cpp=.o)

# Output
OUT = main

# Using standard gcc compiler
CC = g++
FLAGS = -lSDL2 \
				-lSDL2_image \
				-lSDL2_ttf \
				-lSDL2_mixer

$(OUT): $(OBJFILES)
	$(CC) -o $@ $^ $(FLAGS)

%.o: %.cpp
	$(CC) -c -o $@ $^

clean:
	rm *.o main

run:
	./main
