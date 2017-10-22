#include <iostream>
#include <time.h>

#include "PRA_Interface.h"
#include "FIFO.h"
#include "Optimal.h"
#include "EnhanceSC.h"
#include "RandomRef.h"
#include "PRA.h"

#include <deque>

using namespace std;

int main()
{
    TestRef_Interface* refAlgorithm = new RandomRef(1000);
    PRA_Interface<Page>* algorithm = new EnhanceSC(refAlgorithm);

    PRA* pra = new PRA(algorithm, 70000);

    pra->Run();

    cout << "Interrupt: " << pra->getAlgorithm()->getInterruptTimes() << endl;
    cout << "Page fault: " << pra->getAlgorithm()->getPageFaultTimes() << endl;
    cout << "Write disk: " << pra->getAlgorithm()->getWriteDiskTimes() << endl;

    delete pra;

    return 0;
}
