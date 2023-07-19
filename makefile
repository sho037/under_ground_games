main: src/main.cpp
	g++ -o uggames.exe src/main.cpp src/UGGames.cpp src/PrintStatus.cpp src/common/CommonProcess.cpp src/common/CheckScreen.cpp src/common/JsonData.cpp src/Game.cpp src/Player.cpp -lncurses -ljansson

clean:
	rm -f uggames.exe