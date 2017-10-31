#ifndef MYOWNREF_H
#define MYOWNREF_H

#include "TestRef_Interface.h"
#include "Page.h"

#include <deque>
#include <cstdlib>

/**

This class inhernets from TestRef_Interface.

MyOwnRef is used to choose the new queue of reference strings about the OS.

*/

class MyOwnRef : public TestRef_Interface
{
    public:
        MyOwnRef(int);
        virtual ~MyOwnRef();

        // Implement the choose reserence string algo
        std::deque<Page>* chooseReferenceAlgo(int, int) override;

    protected:

    private:
        int randSeed;
        std::deque<Page>* lastChooseDeque = nullptr;
};

#endif // MYOWNREF_H
