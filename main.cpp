#include <iostream>
#include <time.h>

#include "PRA_Interface.h"
#include "FIFO.h"
#include "Optimal.h"
#include "EnhanceSC.h"
#include "MyOwnPRA.h"
#include "RandomRef.h"
#include "Locality.h"
#include "MyOwnRef.h"
#include "PRA.h"

#include <deque>

using namespace std;

int main()
{
    TestRef_Interface* refAlgorithm = new Locality(1000);
    PRA_Interface<Page>* algorithm = new EnhanceSC(refAlgorithm);

    int refStringNum;

    cout << "Input the number of the frams: ";
    cin >> PRA_Interface<Page>::dramSize;

    cout << "Input the number of the refence string: ";
    cin >> refStringNum;

    cout << "Input the range: ";
    cin >> PRA_Interface<Page>::range;

    PRA* pra = new PRA(algorithm, refStringNum);

    pra->Run();

    cout << "Interrupt: " << pra->getAlgorithm()->getInterruptTimes() << endl;
    cout << "Page fault: " << pra->getAlgorithm()->getPageFaultTimes() << endl;
    cout << "Write disk: " << pra->getAlgorithm()->getWriteDiskTimes() << endl;

    delete pra;

    return 0;
}
