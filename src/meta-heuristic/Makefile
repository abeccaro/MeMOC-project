CC = g++
CPPFLAGS = -g -Wall -Wno-sign-compare -O2 -std=c++11 -pthread
LDFLAGS =

OBJ = main.o ../tsp_data.o tsp_path_solution.o tsp_population.o

%.o: %.cpp
		$(CC) $(CPPFLAGS) -c $^ -o $@

main: $(OBJ)
		$(CC) $(CPPFLAGS) $(OBJ) -o main

clean:
		rm -rf $(OBJ) main

.PHONY: clean
