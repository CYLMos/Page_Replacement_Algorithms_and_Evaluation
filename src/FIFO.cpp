#include "FIFO.h"

// Init
FIFO::FIFO(std::deque<Page>* refStringQue, TestRef_Interface* refAlgo){
    this->interrupt = 0;
    this->pageFault = 0;
    this->writeDisk = 0;

    this->refStringQue = refStringQue;

    this->refStringQue_History = new std::deque<Page>();

    this->refAlgo = refAlgo;
    this->dram = new std::deque<Page>();
}

// Init
FIFO::FIFO(TestRef_Interface* refAlgo){
    this->interrupt = 0;
    this->pageFault = 0;
    this->writeDisk = 0;

    this->refStringQue_History = new std::deque<Page>();

    this->refAlgo = refAlgo;
    this->dram = new std::deque<Page>();
}

// Release memory
FIFO::~FIFO(){
    if(this->refStringQue != nullptr){delete this->refStringQue;}
    if(this->refStringQue_History != nullptr){delete this->refStringQue_History;}
    if(this->dram != nullptr){delete this->dram;}
    if(this->refAlgo != nullptr){delete this->refAlgo;}
}

// Implement getNewRefString
void FIFO::getNewRefStrings(){
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
void FIFO::callOSEvent(){
    this->interrupt++;
}

// Implement pageFaultEvent
void FIFO::pageFaultEvent(Page refString){
    if(this->dram->size() >= (unsigned)PRA_Interface<Page>::dramSize){
        Page page = this->dram->front();

        // If the dirty bit is true, call writeDiskEvent.
        if(page.getDirtyBit()){
            this->writeDiskEvent();
        }

        /**
        FIFO don't clear reference bits because FIFO always pop out its first element in the queue.
        */

        // First out and newest add in last.
        this->dram->pop_front();
        this->dram->push_back(refString);
    }
    else{
        this->dram->push_back(refString);
    }

    this->pageFault++;
}

// Implement writeDskEvent
void FIFO::writeDiskEvent(){
    this->writeDisk++;
}
