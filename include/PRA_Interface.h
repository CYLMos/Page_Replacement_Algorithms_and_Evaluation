#ifndef PRA_INTERFACE_H
#define PRA_INTERFACE_H

template<class T>
class PRA_Interface
{
    public:

        static const int refStringQueSize = 10;
        static const int historyRefStringQueSize = refStringQueSize * 3;

        // return interrupt times
        int getInterruptTimes();

        // retunr page fault times
        int getPageFaultTimes();

        // return write disk times
        int getWriteDiskTimes();

        /*
         the class inherenting this class must implement these function
         */

        // the event calling the OS happended. interrupt++
        virtual void callOSEvent() = 0;

        // the event causing page fault happended. pageFault++
        virtual void pageFaultEvent(T) = 0;

        // the event writting the disk happended. writeDisk++
        virtual void writeDiskEvent() = 0;

        // start
        virtual void Run() = 0;

    protected:
        int interrupt;
        int pageFault;
        int writeDisk;
};

#endif // PRA_INTERFACE_H

