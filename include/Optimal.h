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

        // the event calling the OS happended. interrupt++
        void callOSEvent() override;

        // the event causing page fault happended. pageFault++
        void pageFaultEvent(Page) override;

        // the event writting the disk happended. writeDisk++
        void writeDiskEvent() override;

    protected:

    private:
};

#endif // OPTIMAL_H
