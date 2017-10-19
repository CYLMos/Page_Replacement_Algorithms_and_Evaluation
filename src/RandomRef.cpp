#include "RandomRef.h"

RandomRef::RandomRef()
{
    //ctor
}

RandomRef::~RandomRef()
{
    //dtor
}

std::vector<Page> RandomRef::chooseReferenceAlog(int rang, int length){
    std::vector<Page> refStringVec;
    refStringVec.reserve(length);

    srand(1000);

    for(int i = 0; i < length; i++){
        Page page((rand() % rang) + 1, false);
        refStringVec.push_back(page);
    }

    return refStringVec;
}
