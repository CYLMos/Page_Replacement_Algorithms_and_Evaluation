#ifndef RANDOMREF_H
#define RANDOMREF_H

#include "TestRef_Interface.h"
#include "Page.h"

#include <deque>
#include <cstdlib>

class RandomRef : public TestRef_Interface
{
    public:
        RandomRef(int);
        virtual ~RandomRef();

        std::deque<Page>* chooseReferenceAlgo(int rang, int length) override;

    protected:

    private:
        int randSeed;
};

#endif // RANDOMREF_H
