#include <vector>
#include "Fields.h"

class Board{            //enkapsulacja główna
    private:
        int width;
        int height;
        int nrOfFields;
        std::vector<std::vector<Field*>> boardFields;

    public: 
        Board(int,int);
        Board(int,int,int);                 //  Konstruktor przy podanej ilości bomb
        void drawBoard();                   //  rysowanie w terminalu (LEGACY METHOD)
        void setNumOfBombs(int,int);        //  Ustawia wartość w int numofBombs dla SafeField
        void revealField(int,int);          //  Rekurencyjne odsłanianie pól po kliknięciu na podane w int int
        int whatToDrawHere(int,int);        //  Zwraca numer do rysowania pola dla danego koordynatu
        void setFlagHere(int,int);          //  Zmienia wartość flagi int flagged dla pola na koordynatach
        void firstClickHandler(int,int);    //  Metoda wykonująca się przy pierwszym wybraniu pola w grze, rozważa warunek pierwszego pola będącego bombą
        int gameOver();                     //  Zwraca ilość wszystkich pól o wartości dla pozytywnego zakończenia gry
        ~Board();                   
};