all: wc env true false head tail
wc: wc.c
	gcc -o wc -Wall -pedantic-errors wc.c
env: env.c
	gcc -o env -Wall -pedantic-errors env.c
true: true.c
	gcc -o true -Wall -pedantic-errors true.c
false: false.c
	gcc -o false -Wall -pedantic-errors false.c
head: head.c
	gcc -o head -Wall -pedantic-errors head.c
tail: tail.c
	gcc -o tail -Wall -pedantic-errors tail.c
clean:
	rm wc.o env.o true.o head.o false.o tail.o
