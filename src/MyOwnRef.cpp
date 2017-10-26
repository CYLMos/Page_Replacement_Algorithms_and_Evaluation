#include "MyOwnRef.h"
#include <cstdlib>
#include <time.h>

MyOwnRef::MyOwnRef(int randSeed){
    this->randSeed = randSeed;
    this->lastChooseDeque = new std::deque<Page>();
}

MyOwnRef::~MyOwnRef(){
    delete this->lastChooseDeque;
}

std::deque<Page>* MyOwnRef::chooseReferenceAlgo(int rang, int length){
    std::deque<Page>* refStringQue = new std::deque<Page>();

    if(this->lastChooseDeque->size() != 0){
        int counter = length / 2;
        for(std::deque<Page>::reverse_iterator rit = this->lastChooseDeque->rbegin(); rit != this->lastChooseDeque->rend(); rit++){
            Page page = *rit;

            refStringQue->push_back(page);
            counter--;

            if(counter == 0){break;}
        }

        srand(this->randSeed);

        for(int i = 0; i < length - refStringQue->size(); i++){
            Page page((rand() % rang) + 1, false, true);
            refStringQue->push_back(page);
        }

        this->lastChooseDeque->assign(refStringQue->begin(), refStringQue->end());
    }

    else{
        srand(this->randSeed);

        for(int i = 0; i < length; i++){
            Page page((rand() % rang) + 1, false, true);
            refStringQue->push_back(page);
        }

        this->lastChooseDeque->assign(refStringQue->begin(), refStringQue->end());
    }

    this->randSeed = rand() % time(NULL);

    return refStringQue;
}
