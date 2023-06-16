main: src/main.c src/ScreenSetting.c include/ScreenSetting.h
	gcc -o main.exe src/main.c src/ScreenSetting.c

clean:
	rm -f main.exe