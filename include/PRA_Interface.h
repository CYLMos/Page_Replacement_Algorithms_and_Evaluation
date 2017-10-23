#ifndef PRA_INTERFACE_H
#define PRA_INTERFACE_H

#include <deque>
#include "TestRef_Interface.h"

/**
The interface aobut the page replacement algorithm.

To implement algorithm about page replacement algorithm must inherent this class.
*/

template<class T>
class PRA_Interface
{
    public:

        static int refStringQueSize;
        static int historyRefStringQueSize;
        static int dramSize;
        static double dirtyRate;

        // return interrupt times
        int getInterruptTimes();

        // retunr page fault times
        int getPageFaultTimes();

        // return write disk times
        int getWriteDiskTimes();

        // set reference string queue
        void setRefStringQue(std::deque<T>*);

        // get reference string queue
        std::deque<T>* getRefStringQue();

        // set reference string history queue
        void setRefStringQue_History(std::deque<T>*);

        // get reference string history queue
        std::deque<T>* getRefStringQue_History();

        // set dram
        void setDram(std::deque<T>*);

        // get dram
        std::deque<T>* getDram();

        // set the algorithm that get reference string
        void setRefAlog(TestRef_Interface*);

        // get the algorithm that get reference string
        TestRef_Interface* getRefAlog();

        /**
         the class inherenting this class must implement these function
         */

        // the event calling the OS happended. interrupt++
        virtual void callOSEvent() = 0;

        // the event causing page fault happended. pageFault++
        virtual void pageFaultEvent(T) = 0;

        // the event writting the disk happended. writeDisk++
        virtual void writeDiskEvent() = 0;

    protected:
        int interrupt;
        int pageFault;
        int writeDisk;

        std::deque<T>* refStringQue = nullptr;
        std::deque<T>* refStringQue_History = nullptr;

        std::deque<T>* dram = nullptr;
        TestRef_Interface* refAlgo = nullptr;

};

template<class T>
int PRA_Interface<T>::refStringQueSize = 60;

template<class T>
int PRA_Interface<T>::historyRefStringQueSize = refStringQueSize;

template<class T>
int PRA_Interface<T>::dramSize = 15;

template<class T>
double PRA_Interface<T>::dirtyRate = 0.5;

template<class T>
void PRA_Interface<T>::setRefStringQue(std::deque<T>*){
    if(this->refStringQue != nullptr){
        this->refStringQue->clear();
        delete this->refStringQue;
    }
    this->refStringQue = refStringQue;
}

template<class T>
std::deque<T>* PRA_Interface<T>::getRefStringQue(){
    return this->refStringQue;
}

template<class T>
void PRA_Interface<T>::setRefStringQue_History(std::deque<T>*){
    if(this->refStringQue_History != nullptr){
        this->refStringQue_History->clear();
        delete this->refStringQue_History;
    }
    this->refStringQue_History = refStringQue_History;
}

template<class T>
std::deque<T>* PRA_Interface<T>::getRefStringQue_History(){
    return this->refStringQue_History;
}

template<class T>
void PRA_Interface<T>::setDram(std::deque<T>*){
    if(this->dram != nullptr){
        this->dram->clear();
        delete this->dram;
    }
    this->dram = dram;
}

template<class T>
std::deque<T>* PRA_Interface<T>::getDram(){
    return this->dram;
}

template<class T>
void PRA_Interface<T>::setRefAlog(TestRef_Interface*){
    if(this->refAlgo != nullptr){
        delete this->refAlgo;
    }
    this->refAlgo = refAlgo;
}

template<class T>
TestRef_Interface* PRA_Interface<T>::getRefAlog(){
    return this->refAlgo;
}

template<class T>
int PRA_Interface<T>::getInterruptTimes(){
    return this->interrupt;
}

template<class T>
int PRA_Interface<T>::getPageFaultTimes(){
    return this->pageFault;
}

template<class T>
int PRA_Interface<T>::getWriteDiskTimes(){
    return this->writeDisk;
}
#endif // PRA_INTERFACE_H

