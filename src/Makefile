GC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror 
OB=s21_decimal
# LIB=s21_string
GCOV=--coverage
SANI=-fsanitize=address -g

all : f out

clean :
	rm -rf *.o
	rm -rf *.a
	rm -rf *.g*
	rm -rf report
	rm -rf test.info
	rm -rf gcov
	rm -rf f
	rm -rf test
	# rm -rf ../tests/*.o


# мой мейник
f : clean $(OB).o # $(LIB).a 
	$(GC) $(CFLAGS) $(OB).o  -o f

out: f	
	./f > 1.txt

$(OB).o : $(OB).c
	$(GC) $(CFLAGS) -c $(OB).c


