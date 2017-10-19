#include "Page.h"

Page::Page(){
    //ctor
}

Page::Page(int refString, bool dirtyBit){
    this->refString = refString;
    this->dirtyBit = dirtyBit;
}

Page::~Page(){
    //dtor
}

void Page::setRefString(int refString){
    this->refString = refString;
}

void Page::setDirtyBit(bool dirtyBit){
    this->dirtyBit = dirtyBit;
}

int Page::getRefString(){
    return this->refString;
}

bool Page::getDirtyBit(){
    return this->dirtyBit;
}
