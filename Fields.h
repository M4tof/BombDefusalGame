#include <iostream>

using namespace std;

class Field{            //wzorcowy rodzic
    protected:
        int X;
        int Y;
        int hidden=1;  //czy dane pole ma stan ukryty (tekstura -1)
        int flagged=0; //czy dane pole zostało oflagowane
    public:
        Field(int,int);
        Field();                    
        virtual int hasBomb()=0;                    // czy na polu jest bomba
        virtual char symbol()=0;                    // Zwraca symbol dla rysunku w terminalu (LEGACY METHOD)
        virtual void setNumofBombsDirect(int)=0;    // Ustawia wartość int numofBombs w SafeField, nic w BombField
        virtual void reveal()=0;                    // Zmienia stan flagi int hidden na false, sprawia, że pole jest ujawnione
        virtual int whatToDraw()=0;                 // Metoda kontrolująca co powinno zostać wyświetlone w okienku na danym polu
        virtual void setFlag()=0;                   // Zmienia stan flagi int flagged na przeciwny do aktualnego, stawia lub usuwa oznaczenia flagi na polu
        virtual int isDefused()=0;                  // Zwraca stan aktywności bomby, dla SafeField zawsze true, dla BombField zależne od stanu flagi defusedFlag
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

