all: clean main

libs:
	gcc -c lib/listen.c -o build/listen.o
	gcc -c lib/print.c -o build/print.o

main: libs
	gcc -c src/main.c -o build/main.o
	gcc -g -o final build/listen.o build/main.o build/print.o

clean:
	rm -rf build/*