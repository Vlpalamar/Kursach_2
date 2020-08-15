#pragma once
#include<iostream>
#include<time.h>
#include<windows.h>
#include<fstream>
#include<map>
#include<string>
#include<conio.h>
using namespace std;

enum Priority { LOW, MEDIUM, HIGH };

template<class T>
class MyData
{
public:
	T value;
	MyData* next = nullptr;
	MyData* prev = nullptr;
	Priority pre = LOW;
	MyData() {}
};