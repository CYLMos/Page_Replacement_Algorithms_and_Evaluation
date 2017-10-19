#ifndef PRA_INTERFACE_H
#define PRA_INTERFACE_H

class PRA_Interface
{
    public:

        static const int historyRefStringVecSize = 30;
        static const int refStringVecSize = 10;

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
        virtual void pageFaultEvent() = 0;

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

