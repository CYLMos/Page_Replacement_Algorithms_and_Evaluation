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

    srand(this->randSeed);

    if(this->lastChooseDeque->size() != 0){
        int counter = length / 4;
        for(std::deque<Page>::iterator it = this->lastChooseDeque->begin(); it != this->lastChooseDeque->end(); it++){
            Page page = *it;

            refStringQue->push_back(page);
            counter--;

            if(counter == 0){break;}
        }

        for(int i = 0; i < length - refStringQue->size(); i++){
            Page page((rand() % rang) + 1, false, true);
            refStringQue->push_back(page);
        }

        // Shuffle
        for(std::deque<Page>::iterator it = refStringQue->begin(); it != refStringQue->end(); it++){
            int index = rand() % refStringQue->size();
            std::deque<Page>::iterator it2 = refStringQue->begin() + index;

            Page pageIt = *it;
            Page pageIt2 = *it2;
            Page temp = pageIt;

            pageIt.setRefString(pageIt2.getRefString());
            pageIt2.setRefString(temp.getRefString());

            *it = pageIt;
            *it2 = pageIt2;
        }

        this->lastChooseDeque->clear();

        this->lastChooseDeque->assign(refStringQue->begin(), refStringQue->end());
    }

    else{

        for(int i = 0; i < length; i++){
            Page page((rand() % rang) + 1, false, true);
            refStringQue->push_back(page);
        }

        this->lastChooseDeque->assign(refStringQue->begin(), refStringQue->end());
    }

    this->randSeed = rand() % time(NULL);

    return refStringQue;
}
