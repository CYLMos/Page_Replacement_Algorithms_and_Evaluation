#ifndef PRA_INTERFACE_H
#define PRA_INTERFACE_H

#include <deque>
#include "TestRef_Interface.h"

template<class T>
class PRA_Interface
{
    public:

        static int refStringQueSize;
        static int historyRefStringQueSize;
        static int dramSize;
        static double dirtyRate;

        // return interrupt times
        virtual int getInterruptTimes() = 0;

        // retunr page fault times
        virtual int getPageFaultTimes() = 0;

        // return write disk times
        virtual int getWriteDiskTimes() = 0;

        /*
         the class inherenting this class must implement these function
         */

        virtual void setRefStringQue(std::deque<T>*) = 0;

        virtual std::deque<T>* getRefStringQue() = 0;

        virtual void setRefStringQue_History(std::deque<T>*) = 0;

        virtual std::deque<T>* getRefStringQue_History() = 0;

        virtual void setDram(std::deque<T>*) = 0;

        virtual std::deque<T>* getDram() = 0;

        virtual void setRefAlog(TestRef_Interface*) = 0;

        virtual TestRef_Interface* getRefAlog() = 0;

        // the event calling the OS happended. interrupt++
        virtual void callOSEvent() = 0;

        // the event causing page fault happended. pageFault++
        virtual void pageFaultEvent(T) = 0;

        // the event writting the disk happended. writeDisk++
        virtual void writeDiskEvent() = 0;

        // start
        //virtual void Run() = 0;

    protected:

};

template<class T>
int PRA_Interface<T>::refStringQueSize = 10;

template<class T>
int PRA_Interface<T>::historyRefStringQueSize = refStringQueSize * 3;

template<class T>
int PRA_Interface<T>::dramSize = 10;

template<class T>
double PRA_Interface<T>::dirtyRate = 0.01;
#endif // PRA_INTERFACE_H

