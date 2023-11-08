#include "Fields.h"
#include <stdlib.h>     
#include <time.h>

using namespace std;

Field::Field(int posX,int posY){
    this->X = posX;
    this->Y = posY;
}
Field::Field(){
    this->X = -1;
    this->Y = -1;
}


SafeField::SafeField(int posX,int posY){
    this->X = posX;
    this->Y = posY;
}

SafeField::SafeField(){
    this->X = -1;
    this->Y = -1;
}

int SafeField::hasBomb(){
    return 0;
}

char SafeField::symbol(){
    return this->numofBombs +'0';
}

void SafeField::setNumofBombsDirect(int num){
    this->numofBombs = num;
}

void SafeField::reveal(){
    this->hidden=0;
}

int SafeField::whatToDraw(){
    if(this->hidden == 1){
        if(this->flagged ==1){
            return 10;
        }
        else{
            return -1;
        }
    }
    else{
        return this->numofBombs;
    }
}

void SafeField::setFlag(){
    this->flagged = !(this->flagged);
}

int SafeField::isDefused(){
    return 1;
}


BombField::BombField(int posX,int posY){
    this->X = posX;
    this->Y = posY;
}

BombField::BombField(){
    this->X = -1;
    this->Y = -1;
}

int BombField::hasBomb(){
    return 1;
}

char BombField::symbol(){
    return 'B';
}

void BombField::setNumofBombsDirect(int num){}

void BombField::reveal(){
    this->hidden=0;
}

int BombField::whatToDraw(){
    if(this->hidden == 1){
        if(this->flagged ==1){
            return 10;
        }
        else{
            return -1;
        }
    }
    else{
        return 9;
    }
}

void BombField::setFlag(){
    this->flagged = !(this->flagged);
    
    if(this->flagged){
        this->defusedFlag=1;
    }
    else{
        this->defusedFlag=0;
    }
}

int BombField::isDefused(){
    return this->defusedFlag;
}