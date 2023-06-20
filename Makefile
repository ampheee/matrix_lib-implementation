CC=gcc
CFLAGS=-Wall	-Wextra	-Werror	-std=c11

ifeq ($(shell uname), Linux)
	LINUX_LIBS=-lsubunit -lrt -lpthread -lm
endif

all: clean lib_matrix.a

lib_matrix.a: lib_matrix.o
	ar r lib_matrix.a lib_matrix.o
	ranlib lib_matrix.a

lib_matrix.o:
	$(CC)	$(CFLAGS) -c lib_matrix.c

test: lib_matrix.a
	$(CC)	matrix_test.c lib_matrix.a -o check.out -lcheck $(LINUX_LIBS)
	./check.out


gcov_report: matrix_test.c lib_matrix.c
	clear
	gcc matrix_test.c	lib_matrix.c -o coverage.o -lcheck $(LINUX_LIBS) -fprofile-arcs -ftest-coverage  
	./coverage.o
	lcov -c -d . -o coverage.info
	genhtml coverage.info -o coverage

clean:
	rm -rf *.o *.out *.a
	rm -rf *.gcda *.gcno
	rm -rf coverage coverage.info 

leaks: test
	gcc -g matrix_test.c lib_matrix.o -o check.out -lcheck $(LINUX_LIBS)
	valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes ./check.out


leaks2: test
	CK_FORK=no leaks --atExit -- ./check.out

lint:
	cp ./../materials/linters/.clang-format .
	clang-format -n *.c *.h
	clang-format -i *.c *.h
	clang-format -i *.c *.h
	rm .clang-format
