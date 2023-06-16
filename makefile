main: src/main.c
	gcc -o main.exe src/main.c

clean:
	rm -f main.exe