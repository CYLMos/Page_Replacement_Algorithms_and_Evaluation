#ifndef PRA_H
#define PRA_H

#include "PRA_Interface.h"
#include "TestRef_Interface.h"
#include "Page.h"

#include <time.h>
#include <deque>
#include <cstdlib>
#include <cstdio>

class PRA
{
    public:

        PRA();
        PRA(PRA_Interface<Page>*, int);

        virtual ~PRA();

        // set the algorithm about page replacement algorithm
        void setAlgorithm(PRA_Interface<Page>*);

        //get the algorithm about page replacement algorithm
        PRA_Interface<Page>* getAlgorithm();

        // set the run times
        void setRefTimes(int);

        // get the run times
        int getRefTimes();

        // start
        void Run();

    protected:

    private:
        PRA_Interface<Page>* algorithm = nullptr;

        int refTimes;
};

#endif // PRA_H
