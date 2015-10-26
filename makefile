CC=g++
FLAGS=-std=c++14 -O3
EXEC=make_ecs
all: $(EXEC)

make_ecs:main.o entity.o world.o
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) -o $@ -c $< $(FLAGS)
