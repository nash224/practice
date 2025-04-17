#include "ClassB.h"

#include "ClassA.h"

void B::DoSomething()
{
	mChild = new A();
	// work
	delete mChild;
}
