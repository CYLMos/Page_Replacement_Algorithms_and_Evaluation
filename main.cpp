#include <iostream>
#include <time.h>

#include "PRA_Interface.h"
#include "FIFO.h"
#include "RandomRef.h"
#include "PRA.h"

using namespace std;

int main()
{
    TestRef_Interface* refAlgorithm = new RandomRef(time(nullptr));
    PRA_Interface<Page>* algorithm = new FIFO(refAlgorithm);

    PRA* pra = new PRA(algorithm, 70000);

    pra->Run();

    cout << "Interrupt: " << pra->getAlgorithm()->getInterruptTimes() << endl;
    cout << "Page fault: " << pra->getAlgorithm()->getPageFaultTimes() << endl;
    cout << "Write disk: " << pra->getAlgorithm()->getWriteDiskTimes() << endl;

    delete pra;

    return 0;
}
