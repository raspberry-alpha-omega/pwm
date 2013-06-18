LC_ALL=C 
LANG=C

all : console-demo

clean :
	rm console-demo

console-demo : console-demo.c
	c99 -o console-demo console-demo.c

