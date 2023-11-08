all:
	g++ main.cpp Fields.cc Board.cc -o main.exe -lsfml-graphics -lsfml-window -lsfml-system