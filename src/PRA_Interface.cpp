#include "PRA_Interface.h"
template<class T>
int PRA_Interface<T>::getInterruptTimes()
{
    return this->interrupt;
}

template<class T>
int PRA_Interface<T>::getPageFaultTimes()
{
    return this->pageFault;
}

template<class T>
int PRA_Interface<T>::getWriteDiskTimes()
{
    return this->writeDisk;
}
