#include "FIFO.h"

FIFO::FIFO(int dramSize, std::deque<Page>* refStringQue, int refTimes){
    PRA_Interface::interrupt = 0;
    PRA_Interface::pageFault = 0;
    PRA_Interface::writeDisk = 0;

    this->dramSize = dramSize;
    this->refStringQue = refStringQue;
    this->refTimes = refTimes;

    this->refStringQue_History = new std::deque<Page>();
    //this->refStringVec_History->reserve(this->historyRefStringVecSize);

    this->refAlog = new RandomRef();
    this->dram = new std::deque<Page>();
}

FIFO::~FIFO(){
    delete this->refStringQue;
}

void FIFO::setDramSize(int dramSize){
    this->dramSize = dramSize;
    if(this->dram == nullptr){
        this->dram = new std::deque<Page>();
    }

    if(!this->dram->empty()){
        this->dram->clear();
    }

    //this->dram->reserve(dramSize);
}

void FIFO::setRefStringQue(std::deque<Page>* refStringQue){
    this->refStringQue = refStringQue;
}

void FIFO::setRefTimes(int refTimes){
    this->refTimes = refTimes;
}

void FIFO::callOSEvent(){

    if(this->refStringQue_History->size() + PRA_Interface::refStringQueSize > PRA_Interface::historyRefStringQueSize){
        int num = this->refStringQue_History->size() - PRA_Interface::refStringQueSize;

        for(int i = 0; i < num; i++){
            this->refStringQue_History->pop_front();
        }
    }

    for(unsigned i = 0; i < this->refStringQue->size(); i++){
        this->refStringQue->push_back(this->refStringQue->at(i));
    }

    this->refStringQue->clear();

    delete this->refStringQue;

    std::deque<Page> temp = this->refAlog->chooseReferenceAlgo(350, PRA_Interface::refStringQueSize);
    this->refStringQue = &temp;

    PRA_Interface::interrupt++;
}

void FIFO::pageFaultEvent(Page refString){
    std::deque<Page>* tempDeque = new std::deque<Page>();
    tempDeque->assign(this->refStringQue->begin(), this->refStringQue->end());

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
    for(std::deque<Page>::iterator it = refStringQue->begin(); it!= refStringQue->end(); it++){
        Page dramPage = *it;

        if(dramPage.getRefString() == victimPage.getRefString()){
            dramPage.setRefString(refString.getRefString());
            dramPage.setDirtyBit(refString.getDirtyBit());
        }
    }

    PRA_Interface::pageFault++;
}

void FIFO::writeDiskEvent(){
    PRA_Interface::writeDisk++;
}

void FIFO::Run(){
}
