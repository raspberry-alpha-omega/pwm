LC_ALL=C 
LANG=C

all : console-demo gpio-demo

clean :
	rm console-demo gpio-demo

console-demo : console-demo.c
	c99 -o console-demo console-demo.c

gpio-demo : gpio-demo.c
	c99 -o gpio-demo gpio-demo.c -lwiringPi

