#include <iostream>
#include "random.h"
#include <cmath>
#include <vector>
using namespace std;

void radix_sort(float input[], int length)
{
	//the float: 31st is sign, and the 23 ~ 30 are jie ma , the 0 ~ 22 are wei ma
    for (int i=0; i<length; i++)
    	//deal with sign
        reinterpret_cast<int&>(input[i]) = (reinterpret_cast<int&>(input[i])>>31 & 0x1)? ~reinterpret_cast<int&>(input[i]) : reinterpret_cast<int&>(input[i]) | 0x80000000;
    vector<float> bucket[256];
    for (int i=0; i<4; i++) {
        for (int j=0; j<length; j++)
            bucket[reinterpret_cast<int&>(input[j])>>(i*8) & 0xff].push_back(input[j]);
        int count = 0;
        for (int j=0; j<256; j++) {
            for (int k=0; k<bucket[j].size(); k++)
                input[count++] = bucket[j][k];
            bucket[j].clear();
        }
    }
    // after sort, recover
    for (int i=0; i<length; i++)
        reinterpret_cast<int&>(input[i]) = (reinterpret_cast<int&>(input[i])>>31 & 0x1)? reinterpret_cast<int&>(input[i]) & 0x7fffffff : ~reinterpret_cast<int&>(input[i]);
}

void printArray(float input[], int number)
{
	for (int i = 0; i < number; i++)
	{
		cout<<input[i]<<" ";
	}
	cout<<endl;
}

int main ()
{
	int number = randomInteger(1, 500);
	float* input = new float[number]; 
	for (int i = 0; i < number; i++)
	{
		input[i] = (float) randomInteger(-65535,65535) / (float) randomInteger(-65535, 65535);
	}
	radix_sort(input, number);
	printArray(input, number);
	delete[] input;
}