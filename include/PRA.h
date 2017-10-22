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

        void setAlgorithm(PRA_Interface<Page>*);

        PRA_Interface<Page>* getAlgorithm();

        void setRefAlgorithm(TestRef_Interface*);

        TestRef_Interface* getRefAlgorithm();

        void setRefTimes(int);

        int getRefTimes();

        void Run();

    protected:

    private:
        PRA_Interface<Page>* algorithm = nullptr;

        int refTimes;
};

#endif // PRA_H
