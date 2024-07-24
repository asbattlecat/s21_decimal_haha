FLAGS = -Wall -Werror -Wextra -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CLANGFLAGS = --style=Google --verbose
LIBCHECK = $(shell pkg-config --libs check)
CFILES = helpers.c others.c comprasion.c conversion.c arithmetic.c  main.c s21_decimal.c
ifeq ($(shell uname -r | grep WSL -o), WSL)
	HTML_OPEN = @echo HTML report is in $(shell pwd)/report/index.html
else ifeq ($(shell uname -s), Linux)
	HTML_OPEN = @xdg-open ./report/index.html
else
	HTML_OPEN = @open ./report/index.html
endif

all: test

check: 
ifeq ("", "$(shell which pkg-config)")
	$(error "Please install pkg-config")
else ifeq ("", "$(LIBCHECK)")
	$(error "Please install check")
else ifeq ("", "$(shell which lcov)")
	$(error "Please install lcov")
endif
de:
	@gcc $(FLAGS) helpers.c others.c comprasion.c conversion.c arithmetic.c  main.c s21_decimal.c -o s21_decimal.out
	@./s21_decimal.out
test: s21_decimal.a
	clang-format -n $(CLANGFLAGS) $(CFILES)
	gcc $(FLAGS) s21_decimal_test.c s21_decimal.a $(LIBCHECK) -o test.out
	./test.out
gcov_report: check
	@rm -rf report
	clang-format -n $(CLANGFLAGS) $(CFILES)
	gcc $(FLAGS) $(GCOV_FLAGS) $(CFILES) -o gcov_report.out $(LIBCHECK)
	./gcov_report.out
	lcov -t "s21_decimal" -o s21_decimal.info -c -d . -q
	genhtml -o report s21_decimal.info -q
	@rm -f s21_decimal.info *.gcda *gcno gcov_report.out
	$(HTML_OPEN)
s21_decimal.a: check
	gcc $(FLAGS) -c -o helpers.o helpers.c
	gcc $(FLAGS) -c -o others.o others.c
	gcc $(FLAGS) -c -o comprasion.o comprasion.c
	gcc $(FLAGS) -c -o arithmetic.o arithmetic.c
	gcc $(FLAGS) -c -o conversion.o conversion.c
	gcc $(FLAGS) -c -o main.o main.c
	gcc $(FLAGS) -c -o s21_decimal.o s21_decimal.c
	ar rcs s21_decimal.a helpers.o others.o comprasion.o conversion.o arithmetic.o main.o s21_decimal.o
	@rm -f *.o
clean:
	rm -f *.a *.o *.info *.gcda *.gcno *.out
	rm -rf report
rebuild: clean all

style_check:
	clang-format -n $(CLANGFLAGS) $(CFILES)
style_fix:
	clang-format -i $(CLANGFLAGS) *.c *.h

valgrind: clean test
	valgrind --tool=memcheck --leak-check=yes ./test.out