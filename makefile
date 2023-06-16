main: src/main.c src/CheckScreenSize.c include/CheckScreenSize.h src/EndProcess.c include/EndProcess.h
	gcc -o main.exe src/main.c src/CheckScreenSize.c src/EndProcess.c -lncurses

clean:
	rm -f main.exe