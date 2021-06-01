ubuntu:
	g++ -O3 -o TimestampAC main.cpp
macos:
	g++ -O3 -o TimestampAC main.cpp
windows:
	cl /GL /std:c++latest main.cpp
