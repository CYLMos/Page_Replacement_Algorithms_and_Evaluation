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

void FIFO::callOSEvent(){
    if(this->refStringQue != nullptr){
        if(this->refStringQue->size() > 0){
            this->refStringQue->clear();
        }
        delete this->refStringQue;
    }

    this->refStringQue = this->refAlgo->chooseReferenceAlgo(30, PRA_Interface<Page>::refStringQueSize);

    this->interrupt++;
}

void FIFO::pageFaultEvent(Page refString){
    if(this->dram->size() >= (unsigned)PRA_Interface<Page>::dramSize){
        Page page = this->dram->front();
        if(page.getDirtyBit()){
            this->writeDiskEvent();
        }

        this->dram->pop_front();
        this->dram->push_back(refString);
    }
    else{
        this->dram->push_back(refString);
    }

    this->pageFault++;
}

void FIFO::writeDiskEvent(){
    this->writeDisk++;
}
