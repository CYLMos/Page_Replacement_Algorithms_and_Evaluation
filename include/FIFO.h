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

/**

This class inhernets from PRA_Interface.

FIFO is used to do the operation about FIFO algorithm of ths OS.

**/

class FIFO : public PRA_Interface<Page>
{
    public:
        FIFO(std::deque<Page>*, TestRef_Interface*);
        FIFO(TestRef_Interface*);
        virtual ~FIFO();

        // Implement getNewRefString
        void getNewRefStrings() override;

        // Implement callOSEvent
        void callOSEvent() override;

        // Implement pageFaultEvent
        void pageFaultEvent(Page) override;

        //Implement writeDiskEvent
        void writeDiskEvent() override;

    protected:

    private:
};

#endif // FIFO_H
