main: src/main.cpp
	g++ -o uggames.exe src/main.cpp src/UGGames.cpp src/PrintStatus.cpp src/common/CommonProcess.cpp -lncurses -ljansson

clean:
	rm -f uggames.exe