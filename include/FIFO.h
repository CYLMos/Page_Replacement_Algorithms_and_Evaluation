#ifndef FIFO_H
#define FIFO_H

#include "PRA_Interface.h"
#include "TestRef_Interface.h"
#include "Page.h"
#include "RandomRef.h"

#include <deque>
#include <algorithm>

class FIFO : public PRA_Interface<Page>
{
    public:
        FIFO(int dramSize, std::deque<Page>* refStringQue, int refTimes);
        virtual ~FIFO();

        void setDramSize(int dramSize);

        void setRefStringQue(std::deque<Page>* refStringQue);

        void setRefTimes(int refTimes);

        void callOSEvent() override;

        void pageFaultEvent(Page) override;

        void writeDiskEvent() override;

        void Run() override;

    protected:

    private:
        int dramSize;
        std::deque<Page>* refStringQue = nullptr;
        std::deque<Page>* refStringQue_History = nullptr;
        int refTimes;

        std::deque<Page>* dram = nullptr;
        TestRef_Interface* refAlog = nullptr;

        //void
};

#endif // FIFO_H
