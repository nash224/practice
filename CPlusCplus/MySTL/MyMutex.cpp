#include "MyMutex.h"

void MyMutex::lock()
{
	while (false == mValue.compare_exchange_strong(IsLock, true))
	{
	}

}

void MyMutex::unlock()
{
	IsLock = false;
}
