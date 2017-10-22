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

        void callOSEvent() override;

        void pageFaultEvent(Page) override;

        void writeDiskEvent() override;

    protected:

    private:
};

#endif // FIFO_H
