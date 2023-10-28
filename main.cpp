#include <iostream>
#include "Fields.h"
#include <unistd.h>

void clearScreen(){
	const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

using namespace std;
int main(int argc, char *argv[]){

	Board Plansza(5,5);
	Plansza.placeBombs(3);
	Plansza.drawBoard();
	
	return 0;
}