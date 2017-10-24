#ifndef LOCALITY_H
#define LOCALITY_H

#include "TestRef_Interface.h"
#include "Page.h"

#include <deque>

class Locality : public TestRef_Interface
{
    public:
        Locality(int);
        virtual ~Locality();

        // Implement the choose reserence string algo.
        std::deque<Page>* chooseReferenceAlgo(int rang, int length) override;

    protected:

    private:
        std::deque<Page>* lastChooseDeque = nullptr;
        int randSeed;

};

#endif // LOCALITY_H
