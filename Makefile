FLAGS = -lm -W -Wall -Wpointer-arith -Wwrite-strings -Wcast-align -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wno-long-long -Wcast-align -Winline -Werror -pedantic -pedantic-errors -Wmissing-declarations -Wunused -Wuninitialized -fPIC
USEFLAGS = false

main.o: input_output.o solver.o
input_output.o: input_output.h utils.o
solver.o: solver.h utils.o

all: main.o input_output.o solver.o utils.o
	g++ main.o input_output.o solver.o utils.o
%.o: %.cpp
ifeq ($(USEFLAGS), true)
	g++ -c $< $(FLAGS) -O3 -fopenmp -march=native -ffast-math -fopenmp-simd -fno-plt -flto
else
	g++ -c $< -O3 -fopenmp -march=native -ffast-math -fopenmp-simd -fno-plt -flto
endif
 
clean:
	rm -f *.o a.exe a.out
