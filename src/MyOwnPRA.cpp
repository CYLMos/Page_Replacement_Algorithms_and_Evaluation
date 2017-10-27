#include "MyOwnPRA.h"
#include <time.h>
#include <cstdlib>

MyOwnPRA::MyOwnPRA(std::deque<Page>* refStringQue, TestRef_Interface* refAlgo){
    this->interrupt = 0;
    this->pageFault = 0;
    this->writeDisk = 0;

    this->refStringQue = refStringQue;

    this->refStringQue_History = new std::deque<Page>();

    this->refAlgo = refAlgo;
    this->dram = new std::deque<Page>();
}

MyOwnPRA::MyOwnPRA(TestRef_Interface* refAlgo){
    this->interrupt = 0;
    this->pageFault = 0;
    this->writeDisk = 0;

    this->refStringQue_History = new std::deque<Page>();

    this->refAlgo = refAlgo;
    this->dram = new std::deque<Page>();
}

MyOwnPRA::~MyOwnPRA(){
    if(this->refStringQue != nullptr){delete this->refStringQue;}
    if(this->refStringQue_History != nullptr){delete this->refStringQue_History;}
    if(this->dram != nullptr){delete this->dram;}
    if(this->refAlgo != nullptr){delete this->refAlgo;}
}

// Implement getNewRefString
void MyOwnPRA::getNewRefStrings(){
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

void MyOwnPRA::callOSEvent(){
    this->interrupt++;
}

void MyOwnPRA::pageFaultEvent(Page refString){
    if(this->dram->size() >= (unsigned)PRA_Interface<Page>::dramSize){
         std::deque<Page>* tempDeque = new std::deque<Page>();
         tempDeque->assign(this->dram->begin(), this->dram->end());

         bool stopFlag = false;
         int breakNum = tempDeque->size() / 4;
         for(std::deque<Page>::reverse_iterator rit = this->refStringQue_History->rbegin(); rit != this->refStringQue_History->rend(); rit++){
             Page page = *rit;

             for(std::deque<Page>::iterator it = tempDeque->begin(); it!= tempDeque->end(); it++){
                 Page dramPage = *it;
                 if(page.getRefString() == dramPage.getRefString() && tempDeque->size() > 1){
                     tempDeque->erase(it);

                     break;
                 }
                 else if(tempDeque->size() == breakNum){
                     stopFlag = true;

                     break;
                 }
              }
              if(stopFlag){break;}
          }

          if(stopFlag){
              srand(time(NULL));
              int counter = ( rand() % breakNum) + 1;

              while(counter != 0){
                  Page temp = this->dram->front();
                  this->dram->pop_front();
                  this->dram->push_back(temp);

                  counter--;
              }
          }

          Page victimPage = tempDeque->front();
          for(std::deque<Page>::iterator it = this->dram->begin(); it!= this->dram->end(); it++){
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

void MyOwnPRA::writeDiskEvent(){
    this->writeDisk++;
}
