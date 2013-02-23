// JustForTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "A.h"

int _tmain(int argc, _TCHAR* argv[])
{
	while (true)
	{
		int a;
	}


	A a;
	MyStruct myStruct = a.GetStruct();

	MyStruct* s1 = &myStruct;
	MyStruct* s2 = &a.mStruct;
	MyStruct* s3 = &a.GetStructRef();
	MyStruct* s4 = &a.GetStruct();

	printf("&myStruct: %p \n&a.mStruct: %p \n&a.GetStructRef(): %p\n&a.GetStruct(): %p\n", s1, s2, s3, s4);
	return 0;
}

