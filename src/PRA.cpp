#include "PRA.h"
#include <iostream>

//Init
PRA::PRA(){
    this->refTimes = 0;
}

//Init
PRA::PRA(PRA_Interface<Page>* algorithm, int refTimes){
    this->algorithm = algorithm;
    this->refTimes = refTimes;
}

//Release the memory
PRA::~PRA(){
    delete this->algorithm;
}

// set the algorithm about page replacement algorithm
void PRA::setAlgorithm(PRA_Interface<Page>* algorithm){
    this->algorithm = algorithm;
}

//get the algorithm about page replacement algorithm
PRA_Interface<Page>* PRA::getAlgorithm(){
    return this->algorithm;
}

// set the run times
void PRA::setRefTimes(int refTimes){
    this->refTimes = refTimes;
}

// get the run times
int PRA::getRefTimes(){
    return this->refTimes;
}

// start
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

                // A page fault wasn't happened
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

            // A page fault washappened
            if(!existFlag){
                this->algorithm->pageFaultEvent(page);
            }

            // Add the reference string that has read into history
            if(this->algorithm->getRefStringQue_History()->size() >= (unsigned)PRA_Interface<Page>::historyRefStringQueSize){
                this->algorithm->getRefStringQue_History()->pop_front();
            }
            this->algorithm->getRefStringQue_History()->push_back(page);

            this->algorithm->getRefStringQue()->pop_front();
        }

        // Change the write disk bit randomly
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
