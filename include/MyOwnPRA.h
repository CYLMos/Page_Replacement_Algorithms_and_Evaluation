#ifndef MYOWNPRA_H
#define MYOWNPRA_H

#include "PRA_Interface.h"
#include "Page.h"

#include <deque>

class MyOwnPRA : public PRA_Interface<Page>
{
    public:
        MyOwnPRA(std::deque<Page>*, TestRef_Interface*);
        MyOwnPRA(TestRef_Interface*);
        virtual ~MyOwnPRA();

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
        bool findFunction(bool, bool);

        void replaceVictim(Page);
};

#endif // MYOWNPRA_H
