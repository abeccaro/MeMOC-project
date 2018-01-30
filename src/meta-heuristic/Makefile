CC = g++
CPPFLAGS = -g -Wall -Wsign-compare -O2
LDFLAGS =

OBJ = main.o ../TSPData.o tsp_solution.o tsp_population.o

%.o: %.cpp
		$(CC) $(CPPFLAGS) -c $^ -o $@

main: $(OBJ)
		$(CC) $(CPPFLAGS) $(OBJ) -o main

clean:
		rm -rf $(OBJ) main

.PHONY: clean
