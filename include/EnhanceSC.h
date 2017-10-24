#ifndef ENHANCESC_H
#define ENHANCESC_H

#include "PRA_Interface.h"
#include "Page.h"

#include <deque>

/**

This class inhernets from PRA_Interface.

EnhanceSC is used to do the operation about the enhance second chance algorithm of ths OS.

**/

class EnhanceSC : public PRA_Interface<Page>
{
    public:
        EnhanceSC(std::deque<Page>*, TestRef_Interface*);
        EnhanceSC(TestRef_Interface*);
        virtual ~EnhanceSC();

        // Implement callOSEvent
        void callOSEvent() override;

        // Implement pageFaultEvent
        void pageFaultEvent(Page) override;

        //Implement writeDiskEvent
        void writeDiskEvent() override;

    protected:

    private:
        bool findZeroZero();

        bool findZeroOne();

        void replaceVictim(Page);
};

#endif // ENHANCESC_H
