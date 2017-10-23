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

    this->refStringQue = this->refAlgo->chooseReferenceAlgo(30, PRA_Interface<Page>::refStringQueSize);

    this->interrupt++;
}

// Implement pageFaultEvent
void EnhanceSC::pageFaultEvent(Page refString){
    if(this->dram->size() >= (unsigned)PRA_Interface<Page>::dramSize){
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
                /* If get (0, 0), break. */
                doubleZeroFlag = true;

                break;
            }
            else{
                nowPage.setRefBit(false);
                *it = nowPage;
            }
        }

        /**
        If not find (0, 0), find (0, 0) again.
        If still not find, find (0, 1).
        */
        if(!doubleZeroFlag){
            /** Find (0, 1) or (0, 0) next.
               (0, 0) first
            */
            while(nowPage.getRefString() != lastPage.getRefString()){
                Page beginPage = this->dram->front();
                this->dram->pop_front();
                this->dram->push_back(beginPage);

                nowPage = this->dram->front();
                if( nowPage.getRefBit() == false && nowPage.getDirtyBit() == false ){
                    doubleZeroFlag = true;

                    break;
                }
            }

            /**
            (0, 1) next
            */
            if(!doubleZeroFlag){
                bool otherFlag = true;
                while(nowPage.getRefString() != lastPage.getRefString()){
                    Page beginPage = this->dram->front();
                    this->dram->pop_front();
                    this->dram->push_back(beginPage);

                    nowPage = this->dram->front();
                    if(nowPage.getRefBit() == false && nowPage.getDirtyBit() == true){
                        this->writeDiskEvent();
                        break;
                    }
                }
            }
        }


        /**
        Replace reference string
        */
        std::deque<Page>::iterator it = this->dram->begin();
        Page victimPage = *it;

        victimPage.setRefString(refString.getRefString());
        victimPage.setDirtyBit(refString.getDirtyBit());
        victimPage.setRefBit(refString.getRefBit());

        *it = victimPage;
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
