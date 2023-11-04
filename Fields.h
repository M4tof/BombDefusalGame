#include <iostream>
#include <vector>

using namespace std;

class Field{
    protected:
        int X;
        int Y;
        int hidden=1;
        int flagged=0;
    public:
        Field(int,int);
        Field();
        virtual int hasBomb()=0;
        virtual char symbol()=0;
        virtual void setNumofBombsDirect(int)=0;
        virtual void reveal()=0;
        virtual int whatToDraw()=0;
        virtual void setFlag()=0;
        virtual int isDefused()=0;
};

class SafeField : public Field {
    private:
        int numofBombs=0;
    public:
        SafeField();
        SafeField(int,int);
        int hasBomb() override;
        char symbol() override;
        void setNumofBombsDirect(int) override;
        void reveal() override;
        int whatToDraw() override;
        void setFlag() override;
        int isDefused() override;
};

class BombField : public Field {
    private:
        int defusedFlag=0;
    public:
        BombField(int,int);
        BombField();
        int hasBomb() override;
        char symbol() override;
        void setNumofBombsDirect(int) override;
        void reveal() override;
        int whatToDraw() override;
        void setFlag() override;
        int isDefused() override;
};

class Board{
    private:
        int width;
        int height;
        int nrOfFields;
        std::vector<std::vector<Field*>> boardFields;

    public: 
        Board(int,int);
        Board(int,int,int);
        void drawBoard();
        void setNumOfBombs(int,int);
        void revealField(int,int);
        int whatToDrawHere(int,int);
        void setFlagHere(int,int);
        void firstClickHandler(int,int);
        int gameOver();
        ~Board();
};