all:
	gcc *.c -std=c99 -O3 `pkg-config --cflags --libs sdl2 gl glew` -o hw3.exe

debug:
	gcc *.c -std=c99 -O3 -g `pkg-config --cflags --libs sdl2 gl glew` -o hw3.exe

clean:
	rm -rf *.exe
