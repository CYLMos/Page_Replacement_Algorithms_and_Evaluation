#include "PRA.h"

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

        this->algorithm->callOSEvent();

        for(std::deque<Page>::iterator it = this->algorithm->getRefStringQue()->begin(); it!= this->algorithm->getRefStringQue()->end(); it++){
            Page page = *it;

            bool existFlag = false;
            for(std::deque<Page>::iterator subIt = this->algorithm->getDram()->begin(); subIt != this->algorithm->getDram()->end(); subIt++){
                Page dramPage = *subIt;
                if(page.getRefString() == dramPage.getRefString()){
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
        }

        srand(time(nullptr));
        for(std::deque<Page>::iterator it = this->algorithm->getDram()->begin(); it!= this->algorithm->getDram()->end(); it++){
            Page page = *it;

            if(page.getDirtyBit()){
                this->algorithm->writeDiskEvent();
                page.setDirtyBit(false);
            }

            double value = ((rand() % 100) + 1) * PRA_Interface<Page>::dirtyRate;

            if(value >= 0.1){
                page.setDirtyBit(true);
                *it = page;
            }
        }
    }
    printf("\n");
}