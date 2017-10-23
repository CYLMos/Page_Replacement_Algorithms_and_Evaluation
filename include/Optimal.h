#ifndef OPTIMAL_H
#define OPTIMAL_H

#include "PRA_Interface.h"
#include "Page.h"

#include <deque>

/**

This class inhernets from PRA_Interface.

Optimal is used to do the operation about the optimal algorithm of ths OS.

**/

class Optimal : public PRA_Interface<Page>
{
    public:
        Optimal(std::deque<Page>*, TestRef_Interface*);
        Optimal(TestRef_Interface*);
        virtual ~Optimal();

        // Implement callOSEvent
        void callOSEvent() override;

        // Implement pageFaultEvent
        void pageFaultEvent(Page) override;

        //Implement writeDiskEvent
        void writeDiskEvent() override;

    protected:

    private:
};

#endif // OPTIMAL_H
