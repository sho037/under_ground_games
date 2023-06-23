main: src/main.c src/CheckScreenSize.c include/CheckScreenSize.h src/EndProcess.c include/EndProcess.h
	gcc -o ungames.exe src/main.c src/CheckScreenSize.c src/EndProcess.c -lncurses -ljansson

clean:
	rm -f ungames.exe