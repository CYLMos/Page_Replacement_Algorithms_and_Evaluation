#include "PRA.h"
#include <iostream>

PRA::PRA(){
    this->refTimes = 0;
}

PRA::PRA(PRA_Interface<Page>* algorithm, int refTimes){
    this->algorithm = algorithm;
    this->refTimes = refTimes;
}

PRA::~PRA(){
    delete this->algorithm;
}

void PRA::setAlgorithm(PRA_Interface<Page>* algorithm){
    this->algorithm = algorithm;
}

PRA_Interface<Page>* PRA::getAlgorithm(){
    return this->algorithm;
}

void PRA::setRefTimes(int refTimes){
    this->refTimes = refTimes;
}

int PRA::getRefTimes(){
    return this->refTimes;
}

void PRA::Run(){
    for(int runTimes = 0; runTimes < this->refTimes; runTimes++){
        printf("\rrunTimes: %d", runTimes + 1);
        fflush(stdout);

        this->algorithm->getNewRefStrings();

        while(this->algorithm->getRefStringQue()->size() > 0){
            std::deque<Page>::iterator it = this->algorithm->getRefStringQue()->begin();

            Page page = *it;

            bool existFlag = false;
            for(std::deque<Page>::iterator subIt = this->algorithm->getDram()->begin(); subIt != this->algorithm->getDram()->end(); subIt++){
                Page dramPage = *subIt;
                if(page.getRefString() == dramPage.getRefString()){
                    if(!dramPage.getRefBit()){
                        this->algorithm->callOSEvent();
                        dramPage.setRefBit(true);
                    }
                    *subIt = dramPage;

                    existFlag = true;

                    break;
                }
            }

            if(!existFlag){
                this->algorithm->pageFaultEvent(page);
            }

            if(this->algorithm->getRefStringQue_History()->size() >= (unsigned)PRA_Interface<Page>::historyRefStringQueSize){
                this->algorithm->getRefStringQue_History()->pop_front();
            }
            this->algorithm->getRefStringQue_History()->push_back(page);

            this->algorithm->getRefStringQue()->pop_front();
        }

        srand(time(nullptr));
        for(std::deque<Page>::iterator it = this->algorithm->getDram()->begin(); it!= this->algorithm->getDram()->end(); it++){
            Page page = *it;

            if(page.getDirtyBit()){
                this->algorithm->writeDiskEvent();
                page.setDirtyBit(false);
            }

            double value = ((rand() % 100) + 1) * 0.01;

            if(value >= PRA_Interface<Page>::dirtyRate){
                if(!page.getDirtyBit()){
                    this->algorithm->callOSEvent();
                    page.setDirtyBit(true);
                }
                *it = page;
            }
        }
    }
    printf("\n");
}
