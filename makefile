main: src/main.c
	gcc -o uggames.exe src/main.c -lncurses -ljansson

clean:
	rm -f uggames.exe