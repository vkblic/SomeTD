#include "stdafx.h"
#include "A.h"


A::A(void)
{
	mStruct.a = 100;
	mStruct.b = 111.1111;
}


A::~A(void)
{
}

MyStruct& A::GetStructRef()
{
	return mStruct;
}
MyStruct A::GetStruct()
{
	return mStruct;
}