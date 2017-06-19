#include <iostream>
#include <stdio.h>
#include "A.h"
#include "Test.h"
using namespace std;
/*
void *operator new(size_t size)
{
	printf("global new\n");
	return malloc(size);
}
*/
int main()
{
	test::fun7();
	system("pause");
	return 0;
}