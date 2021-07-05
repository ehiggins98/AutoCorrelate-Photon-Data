linux:
	g++ -O3 -o TimestampAC main.cpp
macos:
	g++ -O3 -o TimestampAC main.cpp
windows:
	/usr/bin/x86_64-w64-mingw32-g++-win32 -Wall -O3 -c main.cpp -o main.o
	/usr/bin/x86_64-w64-mingw32-g++-win32 -static -static-libgcc -static-libstdc++ -o TimestampAC-win32.exe main.o

