#ifndef ENHANCESC_H
#define ENHANCESC_H

#include "PRA_Interface.h"
#include "Page.h"

#include <deque>

class EnhanceSC : public PRA_Interface<Page>
{
    public:
        EnhanceSC(std::deque<Page>*, TestRef_Interface*);
        EnhanceSC(TestRef_Interface*);
        virtual ~EnhanceSC();

        // the event calling the OS happended. interrupt++
        void callOSEvent() override;

        // the event causing page fault happended. pageFault++
        void pageFaultEvent(Page) override;

        // the event writting the disk happended. writeDisk++
        void writeDiskEvent() override;

    protected:

    private:
};

#endif // ENHANCESC_H
