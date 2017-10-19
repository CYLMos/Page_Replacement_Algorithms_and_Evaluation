#ifndef RANDOMREF_H
#define RANDOMREF_H

#include "TestRef_Interface.h"
#include "Page.h"

#include <vector>
#include <cstdlib>


class RandomRef : public TestRef_Interface
{
    public:
        RandomRef();
        virtual ~RandomRef();

        std::vector<Page> chooseReferenceAlog(int rang, int length) override;

    protected:

    private:
};

#endif // RANDOMREF_H
