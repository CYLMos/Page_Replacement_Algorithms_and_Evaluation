#ifndef OPTIMAL_H
#define OPTIMAL_H

#include "PRA_Interface.h"
#include "Page.h"

#include <deque>

class Optimal : public PRA_Interface<Page>
{
    public:
        Optimal(std::deque<Page>*, TestRef_Interface*);
        Optimal(TestRef_Interface*);
        virtual ~Optimal();

        /*void setRefStringQue(std::deque<Page>*) override;

        std::deque<Page>* getRefStringQue() override;

        void setRefStringQue_History(std::deque<Page>*) override;

        std::deque<Page>* getRefStringQue_History() override;

        void setDram(std::deque<Page>*) override;

        std::deque<Page>* getDram() override;

        void setRefAlog(TestRef_Interface*) override;

        TestRef_Interface* getRefAlog() override;*/

        // the event calling the OS happended. interrupt++
        void callOSEvent() override;

        // the event causing page fault happended. pageFault++
        void pageFaultEvent(Page) override;

        // the event writting the disk happended. writeDisk++
        void writeDiskEvent() ;

    protected:

    private:
};

#endif // OPTIMAL_H
