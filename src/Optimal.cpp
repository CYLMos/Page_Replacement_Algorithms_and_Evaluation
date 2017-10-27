#include "Optimal.h"
#include <iostream>

// Init
Optimal::Optimal(std::deque<Page>* refStringQue, TestRef_Interface* refAlgo){
    this->interrupt = 0;
    this->pageFault = 0;
    this->writeDisk = 0;

    this->refStringQue = refStringQue;

    this->refStringQue_History = new std::deque<Page>();

    this->refAlgo = refAlgo;
    this->dram = new std::deque<Page>();
}

// Init
Optimal::Optimal(TestRef_Interface* refAlgo){
    this->interrupt = 0;
    this->pageFault = 0;
    this->writeDisk = 0;

    this->refStringQue_History = new std::deque<Page>();

    this->refAlgo = refAlgo;
    this->dram = new std::deque<Page>();
}

// Release memory
Optimal::~Optimal(){
    if(this->refStringQue != nullptr){delete this->refStringQue;}
    if(this->refStringQue_History != nullptr){delete this->refStringQue_History;}
    if(this->dram != nullptr){delete this->dram;}
    if(this->refAlgo != nullptr){delete this->refAlgo;}
}

// Implement getNewRefString
void Optimal::getNewRefStrings(){
    // If refStringQue not null, clear it.
    if(this->refStringQue != nullptr){
        if(this->refStringQue->size() > 0){
            this->refStringQue->clear();
        }
        delete this->refStringQue;
    }

    // Get new reference string.
    this->refStringQue = this->refAlgo->chooseReferenceAlgo(PRA_Interface<Page>::range, PRA_Interface<Page>::refStringQueSize);
}

// Implement callOSEvent
void Optimal::callOSEvent(){
    this->interrupt++;
}

// Implement pageFaultEvent
void Optimal::pageFaultEvent(Page refString){
    if(this->dram->size() >= (unsigned)PRA_Interface<Page>::dramSize){

        /**
        Copy dram to tempDeque.
        Only change tempDeque in the after operation.
        */
        std::deque<Page>* tempDeque = new std::deque<Page>();
        tempDeque->assign(this->dram->begin(), this->dram->end());

        /**
        Find the same reference string in refStringQue.

        And then erase it in tempDeque.

        If the size of tempDeque is 1, then the only one is victim.
        If the size bigger than 1, the first in tempDeque is victim.

        */

        bool stopFlag = false;
        for(std::deque<Page>::iterator it = this->refStringQue->begin(); it != this->refStringQue->end(); it++){
            Page page = *it;

            for(std::deque<Page>::iterator subIt = tempDeque->begin(); subIt!= tempDeque->end(); subIt++){
                Page dramPage = *subIt;
                if(page.getRefString() == dramPage.getRefString() && tempDeque->size() > 1){
                    tempDeque->erase(subIt);

                    break;
                }
                else if(tempDeque->size() <= 1){
                    stopFlag = true;

                    break;
                }
            }

            // If stopFlag is true, out Loop.
            if(stopFlag){break;}
        }

        /**
        Replace reference string
        */

        Page victimPage = tempDeque->front();
        for(std::deque<Page>::iterator it = this->dram->begin(); it != this->dram->end(); it++){
            Page dramPage = *it;

            if(dramPage.getRefString() == victimPage.getRefString()){
                if(dramPage.getDirtyBit()){
                    this->writeDiskEvent();
                }

                dramPage.setRefString(refString.getRefString());
                dramPage.setDirtyBit(refString.getDirtyBit());

                *it = dramPage;
            }
        }

        tempDeque->clear();
        delete tempDeque;
    }
    else{
        this->dram->push_back(refString);
    }

    this->pageFault++;
}

// Implement writeDskEvent
void Optimal::writeDiskEvent(){
    this->writeDisk++;
}
