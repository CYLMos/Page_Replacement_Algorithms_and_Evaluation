#ifndef RANDOMREF_H
#define RANDOMREF_H

#include "TestRef_Interface.h"
#include "Page.h"

#include <deque>
#include <cstdlib>

/**

This class inhernets from TestRef_Interface.

RandomRef is used to choose the new queue of reference strings about the OS.

*/

class RandomRef : public TestRef_Interface
{
    public:
        RandomRef(int);
        virtual ~RandomRef();

        std::deque<Page>* chooseReferenceAlgo(int, int) override;

    protected:

    private:
        int randSeed;
};

#endif // RANDOMREF_H
