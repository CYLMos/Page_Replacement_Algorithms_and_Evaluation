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

// set reference string
void Page::setRefString(int refString){
    this->refString = refString;
}

// get reference string
void Page::setDirtyBit(bool dirtyBit){
    this->dirtyBit = dirtyBit;
}

// set dirty bit
int Page::getRefString(){
    return this->refString;
}

// get dirty bit
bool Page::getDirtyBit(){
    return this->dirtyBit;
}

// set reference bit
void Page::setRefBit(bool refBit){
    this->refBit = refBit;
}

// get reference bit
bool Page::getRefBit(){
    return this->refBit;
}
