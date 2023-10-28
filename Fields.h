#include <iostream>

using namespace std;

class Field{
    private:
        int X;
        int Y;
        int num;
        int bombFlag=0;
    public:
        Field(int,int,int);
        Field();
        int hasBomb();
        void plantBomb();
};

class Board{
    private:
        int width;
        int height;
        int nrOfFields;
        Field** fieldsContainer;
    public: 
        Board(int,int);
        ~Board();
        void drawBoard();
        void placeBombs(int);
        int bombsAround(int, int);
};