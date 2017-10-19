#ifndef FIFO_H
#define FIFO_H

#include "PRA_Interface.h"
#include "TestRef_Interface.h"
#include "Page.h"
#include "RandomRef.h"

#include <vector>

class FIFO : public PRA_Interface
{
    public:
        FIFO(int dramSize, std::vector<Page>* refStringVec, int refTimes);
        virtual ~FIFO();

        void setDramSize(int dramSize);

        void setRefStringVec(std::vector<Page>* refStringVec);

        void setRefTimes(int refTimes);

        void callOSEvent() override;

        void pageFaultEvent() override;

        void writeDiskEvent() override;

        void Run() override;

    protected:

    private:
        int dramSize;
        std::vector<Page>* refStringVec = nullptr;
        std::vector<Page>* refStringVec_History = nullptr;
        int refTimes;

        std::vector<Page>* dram = nullptr;
        TestRef_Interface* refAlog = nullptr;

        //void
};

#endif // FIFO_H
