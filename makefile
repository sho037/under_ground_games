main: src/main.c
	gcc -o uggames.exe src/main.c src/UGGames.c -lncurses -ljansson

clean:
	rm -f uggames.exe