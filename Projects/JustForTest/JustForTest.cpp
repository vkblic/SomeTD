// JustForTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "A.h"

class MyClass
{
public:
	int a;
	MyClass();
	~MyClass();
	void showSomeThing(){printf("show!%d\n", this->a);}
private:

};

MyClass::MyClass()
{
	this->a = 0;
}

MyClass::~MyClass()
{
}


int _tmain(int argc, _TCHAR* argv[])
{

	int* p = new int[4];
	int* pp = p;
	for(int i = 0; i < 4; i++)
	{
		*(pp + i) = i;
	}

	for(int i = 0; i < 4; i++)
	{
		printf("p:%d\n",p[i]);
	}

	for(int i = 0; i < 4; i++)
	{
		printf("pp:%d\n",*(pp + i));
	}

	return 0;

	MyClass** myClass = new MyClass*[4];
	auto classtest  = myClass[0];
	for (int i = 0; i < 4; i++)
	{
		myClass[i] = new MyClass();
		myClass[i]->showSomeThing();
		myClass[i]->a = i + 1;
	}

	for (int i = 0; i < 4; i++)
	{
		myClass[i]->showSomeThing();
	}
	return 0;

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

