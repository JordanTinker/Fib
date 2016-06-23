CC = gcc
CFLAGS = -Wall

default:
	$(CC) $(CFLAGS) fib.c -o fib

clean:
	rm -rf fib
