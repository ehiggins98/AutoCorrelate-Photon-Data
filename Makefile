ubuntu:
	g++ -O3 -o TimestampAC main.cpp
macos:
	g++ -O3 -o TimestampAC main.cpp
windows:
	cl /GL /std:c++latest /EHsc /Fe:TimestampAC-windows main.cpp
