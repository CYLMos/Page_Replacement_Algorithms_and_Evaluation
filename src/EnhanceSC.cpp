#include "EnhanceSC.h"
#include <iostream>

// Init
EnhanceSC::EnhanceSC(std::deque<Page>* refStringQue, TestRef_Interface* refAlgo){
    this->interrupt = 0;
    this->pageFault = 0;
    this->writeDisk = 0;

    this->refStringQue = refStringQue;

    this->refStringQue_History = new std::deque<Page>();

    this->refAlgo = refAlgo;
    this->dram = new std::deque<Page>();
}

// Init
EnhanceSC::EnhanceSC(TestRef_Interface* refAlgo){
    this->interrupt = 0;
    this->pageFault = 0;
    this->writeDisk = 0;

    this->refStringQue_History = new std::deque<Page>();

    this->refAlgo = refAlgo;
    this->dram = new std::deque<Page>();
}

// Release memory
EnhanceSC::~EnhanceSC(){
    if(this->refStringQue != nullptr){delete this->refStringQue;}
    if(this->refStringQue_History != nullptr){delete this->refStringQue_History;}
    if(this->dram != nullptr){delete this->dram;}
    if(this->refAlgo != nullptr){delete this->refAlgo;}
}

// Implement callOSEvent
void EnhanceSC::callOSEvent(){
    if(this->refStringQue != nullptr){
        if(this->refStringQue->size() > 0){
            this->refStringQue->clear();
        }
        delete this->refStringQue;
    }

    this->refStringQue = this->refAlgo->chooseReferenceAlgo(PRA_Interface<Page>::range, PRA_Interface<Page>::refStringQueSize);

    this->interrupt++;
}

// Implement pageFaultEvent
void EnhanceSC::pageFaultEvent(Page refString){
    if(this->dram->size() >= (unsigned)PRA_Interface<Page>::dramSize){

        if(!this->findZeroZero()){
            if(!this->findZeroOne()){
                if(!this->findZeroZero()){
                    this->findZeroOne();


                    this->replaceVictim(refString);
                }
                else{

                    this->replaceVictim(refString);
                }
            }
            else{
                this->replaceVictim(refString);
            }
        }
        else{
            this->replaceVictim(refString);
        }



        /**
        Replace reference string
        */
    }
    else{
            this->dram->push_back(refString);
    }

    this->pageFault++;
}

// Implement writeDskEvent
void EnhanceSC::writeDiskEvent(){
    this->writeDisk++;
}

bool EnhanceSC::findZeroZero(){
    bool doubleZeroFlag = false;
    Page lastPage = this->dram->front();
    Page nowPage;

        /**
        Find (0, 0) first.
        */
    while(nowPage.getRefString() != lastPage.getRefString()){
        Page beginPage = this->dram->front();
        this->dram->pop_front();
        this->dram->push_back(beginPage);

        std::deque<Page>::iterator it = this->dram->begin();
        nowPage = *it;
        if( nowPage.getRefBit() == false && nowPage.getDirtyBit() == false ){
            doubleZeroFlag = true;

            break;;
        }
    }

    return doubleZeroFlag;
}

bool EnhanceSC::findZeroOne(){
    bool findFlag = false;

    Page lastPage = this->dram->front();
    Page nowPage;

        /**
        Find (0, 1) first.
        */
    while(nowPage.getRefString() != lastPage.getRefString()){
        Page beginPage = this->dram->front();
        this->dram->pop_front();
        this->dram->push_back(beginPage);

        std::deque<Page>::iterator it = this->dram->begin();
        nowPage = *it;
        if( nowPage.getRefBit() == false && nowPage.getDirtyBit() == true ){
            findFlag = true;

            break;;
        }
        else{
            it->setRefBit(false);
        }
    }

    for(std::deque<Page>::iterator it = this->dram->begin();it != this->dram->end();it++){
    }
    /*int counter = 1;
    for(std::deque<Page>::iterator it = ++this->dram->begin(); it != this->dram->end(); it++){
        Page nowPage = *it;
        if(nowPage.getRefBit() == false && nowPage.getDirtyBit() == true){
            this->writeDiskEvent();

            findFlag = true;
            break;
        }
        else{
            it->setRefBit(false);

            counter++;
        }
    }

    if(!findFlag){
        std::deque<Page>::iterator it = this->dram->begin();
        it->setRefBit(false);
    }
    else{
        while(counter != 0){
            Page page = this->dram->front();
            this->dram->pop_front();
            this->dram->push_back(page);

            counter--;
        }
    }*/

    return findFlag;
}

void EnhanceSC::replaceVictim(Page page){
    Page victimPage;
    std::deque<Page>::iterator it = this->dram->begin();
    victimPage = *it;

    victimPage.setRefString(page.getRefString());
    victimPage.setDirtyBit(page.getDirtyBit());
    victimPage.setRefBit(page.getRefBit());

    *it = victimPage;
}
