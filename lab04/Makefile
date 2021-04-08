#
# CIS330: Lab 3
#
# Makefile to build libraries and test applications.
#

CC=gcc
AR=ar

CFLAGS=-g -O2 -Wall -I./include -L./lib
LIBS=-llab4 -lm

all: lab4 lab4_dyn

obj:
	mkdir -p obj

lib:
	mkdir -p lib

obj/stats.o: src/stats.c include/stats.h obj
	$(CC) $(CFLAGS) -c -o $@ $<

obj/ohno.o: src/ohno.c include/ohno.h obj
	$(CC) $(CFLAGS) -c -o $@ $<

lib/liblab4.a: obj/stats.o obj/ohno.o lib
	$(AR) rc lib/liblab4.a obj/stats.o obj/ohno.o

lib/labstats.so: src/stats.c include/stats.h lib
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $< -lm

lib/libohno.so: src/ohno.c include/ohno.h lib
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $<

lib/liblab4.so: lib/libstats.so lib/libohno.so lib
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $< -lstats -lohno

lab4_dyn: src/lab4.c lib/liblab4.so
	$(CC) $(CFLAGS) -o $@ $< $(LIBS) -lstats -lohno

lab4: src/lab4.c lib/liblab4.a
	$(CC) $(CFLAGS) -Bstatic -o $@ $< $(LIBS)

clean:
	rm -f lab4 lib/liblab4.a obj/ohno.o obj/stats.o
	rm -f lab4_dyn lib/liblab4.so lib/libstats.so lib/libohno.so
	rmdir obj
	rmdir lib
