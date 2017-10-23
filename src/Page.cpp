#include "Page.h"

// Init
Page::Page(){
    //ctor
}

// Init
Page::Page(int refString, bool dirtyBit){
    this->refString = refString;
    this->dirtyBit = dirtyBit;
}

// Init
Page::Page(int refString, bool dirtyBit, bool refBit){
    this->refString = refString;
    this->dirtyBit = dirtyBit;
    this->refBit = refBit;
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

void Page::setRefBit(bool refBit){
    this->refBit = refBit;
}

bool Page::getRefBit(){
    return this->refBit;
}
