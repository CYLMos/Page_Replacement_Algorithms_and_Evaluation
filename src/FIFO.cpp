#include "FIFO.h"

FIFO::FIFO(int dramSize, std::vector<Page>* refStringVec, int refTimes){
    PRA_Interface::interrupt = 0;
    PRA_Interface::pageFault = 0;
    PRA_Interface::writeDisk = 0;

    this->dramSize = dramSize;
    this->refStringVec = refStringVec;
    this->refTimes = refTimes;

    this->refStringVec_History = new std::vector<Page>();
    this->refStringVec_History->reserve(this->historyRefStringVecSize);

    this->refAlog = new RandomRef();
    this->dram = new std::vector<Page>();
}

FIFO::~FIFO(){
    delete this->refStringVec;
}

void FIFO::setDramSize(int dramSize){
    this->dramSize = dramSize;
    if(this->dram == nullptr){
        this->dram = new std::vector<Page>();
    }

    if(!this->dram->empty()){
        this->dram->clear();
    }

    this->dram->reserve(dramSize);
}

void FIFO::setRefStringVec(std::vector<Page>* refStringVec){
    this->refStringVec = refStringVec;
}

void FIFO::setRefTimes(int refTimes){
    this->refTimes = refTimes;
}

void FIFO::callOSEvent(){

    if(this->refStringVec_History->size() + PRA_Interface::refStringVecSize > PRA_Interface::historyRefStringVecSize){
        int num = this->refStringVec_History->size() - PRA_Interface::refStringVecSize;

        for(int i = 0; i < num; i++){
            this->refStringVec_History->erase(this->refStringVec_History->begin());
        }
    }

    for(unsigned i = 0; i < this->refStringVec->size(); i++){
        this->refStringVec_History->push_back(this->refStringVec->at(i));
    }

    this->refStringVec->clear();

    delete this->refStringVec;

    std::vector<Page> temp = this->refAlog->chooseReferenceAlog(350, PRA_Interface::refStringVecSize);
    this->refStringVec = &temp;

    PRA_Interface::interrupt++;
}

void FIFO::pageFaultEvent(){

    PRA_Interface::pageFault++;
}

void FIFO::writeDiskEvent(){
    PRA_Interface::writeDisk++;
}

void FIFO::Run(){
}
