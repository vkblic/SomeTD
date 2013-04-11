// JustForTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "A.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <queue>
#include <vector>
#include <deque>
#include <list>
#include <iostream>

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

inline int rangedRand(int range_min, int range_max)
{
	int r = (double)rand() / (RAND_MAX + 1) * (range_max - range_min)
		+ range_min;
	return r;


}


typedef long entity_id;
const entity_id nonEntity = -1;
#define non_entity nonEntity
static entity_id id_seed = 0;

static entity_id generateID()
{
	id_seed++;
	//CCLog("idSeed: %d ", id_seed);
	return id_seed;
}


#define assertMsg(a, b) assert(a && b)

int _tmain(int argc, _TCHAR* argv[])
{
	//assertMsg(false, "aasdfsa");

	//	printf("%d" maxaa(1, 5));

	for(int i =0; i < 10; i++)
	{
		printf("%d\n", generateID());
	}

	//err("aaaa%d", 10);
	//printf(#a);
	return 0;

 }


