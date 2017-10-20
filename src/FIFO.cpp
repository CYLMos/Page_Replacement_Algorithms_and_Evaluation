#include "FIFO.h"

FIFO::FIFO(std::deque<Page>* refStringQue, TestRef_Interface* refAlgo){
    this->interrupt = 0;
    this->pageFault = 0;
    this->writeDisk = 0;

    this->refStringQue = refStringQue;

    this->refStringQue_History = new std::deque<Page>();

    this->refAlgo = refAlgo;
    this->dram = new std::deque<Page>();
}

FIFO::FIFO(TestRef_Interface* refAlgo){
    this->interrupt = 0;
    this->pageFault = 0;
    this->writeDisk = 0;

    this->refStringQue_History = new std::deque<Page>();

    this->refAlgo = refAlgo;
    this->dram = new std::deque<Page>();
}

FIFO::~FIFO(){
    if(this->refStringQue != nullptr){delete this->refStringQue;}
    if(this->refStringQue_History != nullptr){delete this->refStringQue_History;}
    if(this->dram != nullptr){delete this->dram;}
    if(this->refAlgo != nullptr){delete this->refAlgo;}
}

void FIFO::setRefStringQue(std::deque<Page>* refStringQue){
    if(this->refStringQue != nullptr){
        this->refStringQue->clear();
        delete this->refStringQue;
    }
    this->refStringQue = refStringQue;
}

std::deque<Page>* FIFO::getRefStringQue(){
    return this->refStringQue;
}

void FIFO::setRefStringQue_History(std::deque<Page>* refStringQue_History){
    this->refStringQue_History = refStringQue_History;
}

std::deque<Page>* FIFO::getRefStringQue_History(){
    return this->refStringQue_History;
}

void FIFO::setDram(std::deque<Page>* dram){
    this->dram = dram;
}

std::deque<Page>* FIFO::getDram(){
    return this->dram;
}

void FIFO::setRefAlog(TestRef_Interface* refAlgo){
    if(this->refAlgo != nullptr){
        delete this->refStringQue;
    }
    this->refAlgo = refAlgo;
}

TestRef_Interface* FIFO::getRefAlog(){
    return this->refAlgo;
}

int FIFO::getInterruptTimes(){
    return this->interrupt;
}

int FIFO::getPageFaultTimes(){
    return this->pageFault;
}

int FIFO::getWriteDiskTimes(){
    return this->writeDisk;
}

void FIFO::callOSEvent(){
    if(this->refStringQue != nullptr){
        if(this->refStringQue->size() > 0){
            this->refStringQue->clear();
        }
        delete this->refStringQue;
    }

    this->refStringQue = this->refAlgo->chooseReferenceAlgo(350, PRA_Interface<Page>::refStringQueSize);

    this->interrupt++;
}

void FIFO::pageFaultEvent(Page refString){
    if(this->dram->size() >= (unsigned)PRA_Interface<Page>::dramSize){
        std::deque<Page>* tempDeque = new std::deque<Page>();
        tempDeque->assign(this->dram->begin(), this->dram->end());

        bool stopFlag = false;
        for(std::deque<Page>::reverse_iterator rit = this->refStringQue_History->rbegin(); rit != this->refStringQue_History->rend(); rit++){
            Page page = *rit;

            for(std::deque<Page>::iterator it = tempDeque->begin(); it!= tempDeque->end(); it++){
                Page dramPage = *it;
                if(page.getRefString() == dramPage.getRefString() && tempDeque->size() > 1){
                    tempDeque->erase(it);

                    break;
                }
                else if(tempDeque->size() == 1){
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

void FIFO::writeDiskEvent(){
    this->writeDisk++;
}
