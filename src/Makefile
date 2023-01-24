GC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror 
TEST=s21_test
LIB=s21_decimal
GCOV=--coverage
SANI=-fsanitize=address -g

all : out

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

test : clean $(LIB).a $(TEST).o
	$(GC) $(CFLAGS) $(TEST).o -l check -L. $(LIB).a -o test 
	./test

$(TEST).o : $(TEST).c
	$(GC) $(CFLAGS) -c $(TEST).c


# библиотека для теста
$(LIB).a : $(LIB).c
	$(GC) -c $(LIB).c
	ar rc  $(LIB).a $(LIB).o
	ranlib $(LIB).a

# проверки lcov и brew
lcov:
ifeq ("", "$(wildcard ~/goinfre/homebrew/bin/lcov)")
	$(error Need to install lcov: make lcov_install)
endif

lcov_install :  brew
	brew install lcov 

brew:
ifeq ("", "$(wildcard ~/goinfre/homebrew)")
	git clone https://github.com/Homebrew/brew ~/goinfre/homebrew
	~/goinfre/homebrew/bin/brew shellenv
endif

out: f	
	./f > 1.txt

# мой мейник
f : clean f.o $(LIB).a 
	$(GC) $(CFLAGS) f.o  -L. $(LIB).a -o f

f.o : f.c
	$(GC) $(CFLAGS) -c f.c
