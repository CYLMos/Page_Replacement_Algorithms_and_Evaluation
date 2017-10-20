#include "RandomRef.h"

RandomRef::RandomRef(int randSeed)
{
    this->randSeed = randSeed;
}

RandomRef::~RandomRef()
{
    //dtor
}

std::deque<Page>* RandomRef::chooseReferenceAlgo(int rang, int length){
    std::deque<Page>* refStringQue = new std::deque<Page>();

    srand(this->randSeed);

    for(int i = 0; i < length; i++){
        Page page((rand() % rang) + 1, false);
        refStringQue->push_back(page);
    }

    this->randSeed = rand() % 10000;

    return refStringQue;
}
