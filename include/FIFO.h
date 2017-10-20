#ifndef FIFO_H
#define FIFO_H

#include "PRA_Interface.h"
#include "TestRef_Interface.h"
#include "Page.h"
#include "RandomRef.h"

#include <deque>
#include <algorithm>
#include <cstdlib>
#include <iostream>

class FIFO : public PRA_Interface<Page>
{
    public:
        FIFO(std::deque<Page>*, TestRef_Interface*);
        FIFO(TestRef_Interface*);
        virtual ~FIFO();

        //void setDramSize(int dramSize);

        void setRefStringQue(std::deque<Page>*) override;

        std::deque<Page>* getRefStringQue() override;

        void setRefStringQue_History(std::deque<Page>*) override;

        std::deque<Page>* getRefStringQue_History() override;

        void setDram(std::deque<Page>*) override;

        std::deque<Page>* getDram() override;

        void setRefAlog(TestRef_Interface*) override;

        TestRef_Interface* getRefAlog() override;

        void callOSEvent() override;

        void pageFaultEvent(Page) override;

        void writeDiskEvent() override;

        int getInterruptTimes() override;

        int getPageFaultTimes() override;

        int getWriteDiskTimes() override;

    protected:

    private:
        std::deque<Page>* refStringQue = nullptr;
        std::deque<Page>* refStringQue_History = nullptr;

        std::deque<Page>* dram = nullptr;
        TestRef_Interface* refAlgo = nullptr;

        int interrupt;
        int pageFault;
        int writeDisk;
};

#endif // FIFO_H
