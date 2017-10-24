#ifndef MYOWNREF_H
#define MYOWNREF_H

#include "TestRef_Interface.h"
#include "Page.h"

#include <deque>
#include <cstdlib>

class MyOwnRef : public TestRef_Interface
{
    public:
        MyOwnRef(int);
        virtual ~MyOwnRef();

        std::deque<Page>* chooseReferenceAlgo(int, int) override;

    protected:

    private:
        int randSeed;
        std::deque<Page>* lastChooseDeque = nullptr;
};

#endif // MYOWNREF_H
