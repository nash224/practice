#pragma once

#include <iostream>
#include "ClassA.h"
#include "ClassB.h"

int main()
{
	A ObjectA;
	B ObjectB = B(&ObjectA);
	return 0;
}
