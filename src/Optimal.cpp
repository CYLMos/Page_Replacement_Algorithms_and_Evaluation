#include "Optimal.h"
#include <iostream>

Optimal::Optimal(std::deque<Page>* refStringQue, TestRef_Interface* refAlgo){
    this->interrupt = 0;
    this->pageFault = 0;
    this->writeDisk = 0;

    this->refStringQue = refStringQue;

    this->refStringQue_History = new std::deque<Page>();

    this->refAlgo = refAlgo;
    this->dram = new std::deque<Page>();
}

Optimal::Optimal(TestRef_Interface* refAlgo){
    this->interrupt = 0;
    this->pageFault = 0;
    this->writeDisk = 0;

    this->refStringQue_History = new std::deque<Page>();

    this->refAlgo = refAlgo;
    this->dram = new std::deque<Page>();
}

Optimal::~Optimal(){
    if(this->refStringQue != nullptr){delete this->refStringQue;}
    if(this->refStringQue_History != nullptr){delete this->refStringQue_History;}
    if(this->dram != nullptr){delete this->dram;}
    if(this->refAlgo != nullptr){delete this->refAlgo;}
}

void Optimal::callOSEvent(){
    if(this->refStringQue != nullptr){
        if(this->refStringQue->size() > 0){
            this->refStringQue->clear();
        }
        delete this->refStringQue;
    }

    this->refStringQue = this->refAlgo->chooseReferenceAlgo(30, PRA_Interface<Page>::refStringQueSize);

    this->interrupt++;
}

void Optimal::pageFaultEvent(Page refString){
    if(this->dram->size() >= (unsigned)PRA_Interface<Page>::dramSize){
        std::deque<Page>* tempDeque = new std::deque<Page>();
        tempDeque->assign(this->dram->begin(), this->dram->end());

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

            if(stopFlag){break;}
        }

        Page victimPage = tempDeque->front();
        for(std::deque<Page>::iterator it = this->dram->begin(); it!= this->dram->end(); it++){
            Page dramPage = *it;

            if(dramPage.getRefString() == victimPage.getRefString()){
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

void Optimal::writeDiskEvent(){
    this->writeDisk++;
}
