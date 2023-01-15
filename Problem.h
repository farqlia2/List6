#pragma once
#ifndef LIST6_PROBLEM_H
#define LIST6_PROBLEM_H

#include "vector"
using namespace std;

class Problem
{
public:
	virtual double getFitness(vector<int>& genome) = 0;
	virtual int getLength() = 0;
};
#endif

