COMPILER = gcc
CFLAGS = -Wall -g
AR = ar 
all: sl 


sl: main.o libsl.a
	$(COMPILER) $(CFLAGS) -o sl main.o libsl.a

libsl.a: sorted-list.o
	$(AR) -r libsl.a sorted-list.o

main.o: main.c
	$(COMPILER) $(CFLAGS) -c main.c 

sorted-list.o: sorted-list.c sorted-list.h 
	$(COMPILER) $(CFLAGS) -c sorted-list.c

clean:
	rm -rf sl
	rm -rf *.o
	rm -rf *.a

rebuild: clean all
