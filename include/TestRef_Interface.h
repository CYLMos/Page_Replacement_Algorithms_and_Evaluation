#ifndef TESTREF_INTERFACE_H
#define TESTREF_INTERFACE_H

#include "Page.h"

#include <deque>


class TestRef_Interface
{
    public:
        /*
         the class inherenting this class must implement this function
         */

        // Implement the choose reserence string algo.
        virtual std::deque<Page>* chooseReferenceAlgo(int rang, int length) = 0;

    protected:

    private:
};

#endif // TESTREF_INTERFACE_H
