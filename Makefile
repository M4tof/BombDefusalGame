all:
	g++ main.cpp Fields.cc -o main.exe -I include/ -L lib/ -lpdcurses