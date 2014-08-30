/*
 * File: RandomWriter.cpp
 * ----------------------
 * [TODO: fill in your name and student ID]
 * Name: gaoce
 * Student ID: 5120379091
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "filelib.h"

#include "simpio.h"

using namespace std;

int main() {
	string filename,temp,essay,first;
	int order,flag = 1,number = 0,max = 0;
	char buff;
	ifstream ifile;
	Map<string,Vector<char> > map;
	map.clear();
	temp = "";
	essay = "";
	while (true)
	{
		filename = getLine("Please enter filename containing text:");
		ifile.open(filename.c_str());
		if (!ifile)
			continue;
		else break;
	}
	while(true)
	{
		order = getInteger("What order of analysis?(a number from 1 to 10):");
		if (order < 1 || order >10)
			getLine("Try again.");
		else break;
	}
	while (ifile.get(buff))
	{
		if (flag <= order)
		{
			temp += buff;
			flag++;
		}
		else 
		{
			temp = temp.substr(temp.size() - order, temp.size());
			if (map.containsKey(temp))
			{
				Vector<char> vt;
				vt = map.get(temp);
				vt.add(buff);
				map.put(temp,vt);
			}
			else
			{
				Vector<char> vt;
				vt.clear();
				vt.add(buff);
				map.put(temp,vt);
			}
			if (map.get(temp).size() > max)
			{
				max = map.get(temp).size();
				first = temp;
			}
			temp += buff;
		}
	}
	cout<<first;
	for (int i = 0; i < 2000; i++)
	{
		first += map.get(first)[randomInteger(0,map.get(first).size()-1)];
		first = first.substr(1,order);
		cout<<first[first.size()-1];
	}
}
