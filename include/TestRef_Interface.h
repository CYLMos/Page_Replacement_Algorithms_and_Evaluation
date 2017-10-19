#ifndef TESTREF_INTERFACE_H
#define TESTREF_INTERFACE_H

#include "Page.h"

#include <deque>


class TestRef_Interface
{
    public:
        virtual std::deque<Page> chooseReferenceAlgo(int rang, int length) = 0;

    protected:

    private:
};

#endif // TESTREF_INTERFACE_H
