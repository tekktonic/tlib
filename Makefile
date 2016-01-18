VERSION = 0.1
DEBUG ?= 0
CFLAGS = -g -Wall -Wextra -pedantic -std=c11 -O0 -fPIC -Iinc

LDFLAGS = -shared

OBJS = src/t_vect.o

all: libtlib.so libtlib.a

libtlib.so: $(OBJS)
	$(CC) $(LDFLAGS) -g $(OBJS) -o libtlib.so

libtlib.a: $(OBJS)
	ar rcs libtlib.a $(OBJS)
test: tests/test_tlib.o tests/test_t_vect.h libtlib.so
	$(CC) -L. -g -Iinc -Itests -lcunit -ltlib -O0 tests/test_tlib.o src/t_vect.o -o test
	rm tests/test_tlib.o
