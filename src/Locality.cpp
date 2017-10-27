#include "Locality.h"
#include "PRA_Interface.h"

#include <cstdlib>
#include <time.h>
#include <iostream>

Locality::Locality(int randSeed){
    this->randSeed = randSeed;
    this->lastChooseDeque = new std::deque<Page>();
}

Locality::~Locality(){
    delete this->lastChooseDeque;
}

std::deque<Page>* Locality::chooseReferenceAlgo(int rang, int length){
    std::deque<Page>* refStringQue = new std::deque<Page>();

    if(this->lastChooseDeque->size() != 0){
        int subSetNum = length / 4;

        srand(this->randSeed);

        int counter = subSetNum;
        for(int i = 0; i < length; i++){
            int randNum = rand();

            if( counter != 0){
                int index = randNum % length;
                Page page = this->lastChooseDeque->at(index);
                refStringQue->push_back( page );

                counter--;
            }
            else{
                Page page((rand() % rang) + 1, false, true);
                refStringQue->push_back(page);
            }
        }

        // Shuffle
        for(std::deque<Page>::iterator it = refStringQue->begin(); it != refStringQue->end(); it++){
            int index = rand() % length;
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
        srand(this->randSeed);

        for(int i = 0; i < length; i++){
            Page page((rand() % rang) + 1, false, true);
            refStringQue->push_back(page);
        }

        this->lastChooseDeque->assign(refStringQue->begin(), refStringQue->end());
    }

    this->randSeed = rand() % time(NULL);

    /*for(std::deque<Page>::iterator it = this->lastChooseDeque->begin(); it != this->lastChooseDeque->end(); it++){
        Page page = *it;
        std::cout << " " << page.getRefString();
    }
    std::cout << std::endl;*/

    return refStringQue;
}
