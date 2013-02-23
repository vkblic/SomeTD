#pragma once

struct MyStruct
{
	int a;
	double b;
};


class A
{
public:
	A(void);
	~A(void);
public:
	MyStruct& GetStructRef();
	MyStruct GetStruct();
public:	
	MyStruct mStruct;
};

