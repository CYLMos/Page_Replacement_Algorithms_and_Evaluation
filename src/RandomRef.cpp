#include "RandomRef.h"
#include "time.h"
#include <iostream>

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
        Page page((rand() % rang) + 1, false, true);
        refStringQue->push_back(page);
    }

    this->randSeed = rand() % time(nullptr);

    /*for(std::deque<Page>::iterator it = refStringQue->begin(); it != refStringQue->end(); it++){
        Page page = *it;
        std::cout << " " << page.getRefString();
    }*/
    //std::cout << std::endl;

    return refStringQue;
}
