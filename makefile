main: src/main.c
	gcc -o ungames.exe src/main.c -lncurses -ljansson

clean:
	rm -f ungames.exe