#ifndef TESTREF_INTERFACE_H
#define TESTREF_INTERFACE_H

#include "Page.h"

#include <vector>


class TestRef_Interface
{
    public:
        virtual std::vector<Page> chooseReferenceAlog(int rang, int length) = 0;

    protected:

    private:
};

#endif // TESTREF_INTERFACE_H
