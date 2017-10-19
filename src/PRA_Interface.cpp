#include "PRA_Interface.h"

int PRA_Interface::getInterruptTimes()
{
    return this->interrupt;
}

int PRA_Interface::getPageFaultTimes()
{
    return this->pageFault;
}

int PRA_Interface::getWriteDiskTimes()
{
    return this->writeDisk;
}
