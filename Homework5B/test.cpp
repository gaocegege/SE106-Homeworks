#include "quickSort.h"
#include "mergeSort.h"
#include <iostream>
#include <fstream>
#include "random.h"
#include <time.h>

using namespace std;

void printArray(int data[], int number)
{
	for (int i = 0; i < number; i++)
	{
		cout<<data[i]<< " ";
	}
	cout<<endl;
}

int main()
{
	clock_t start, finish;
	double myTime = 0;
	long number = 1000;
	// ofstream fileStream("quickSortResult", ios::app);
	// while (number < 10000)
	// {
	// 	start = clock();
	// 	for (int i = 0; i < 1000; i++)
	// 	{
	// 		int *quickNumber = new int[number];
	// 		for (int j = 0; j < number; j++)
	// 			quickNumber[j] = randomInteger(-65535, 65535);
	// 		quickSort(quickNumber,0, number - 1);
	// 		delete[] quickNumber;
	// 	}
	// 	finish = clock();
	// 	myTime = (double) (finish - start) / CLOCKS_PER_SEC;
	// 	myTime = myTime / 1000.0;
	// 	fileStream<<number<<"\t"<<myTime<<endl;
	// 	number += 100;
	// }
	// while (number >= 10000 && number < 100000)
	// {
	// 	start = clock();
	// 	for (int i = 0; i < 10; i++)
	// 	{
	// 		int *quickNumber = new int[number];
	// 		for (int j = 0; j < number; j++)
	// 			quickNumber[j] = randomInteger(-65535, 65535);
	// 		quickSort(quickNumber,0, number - 1);
	// 		delete[] quickNumber;
	// 	}
	// 	finish = clock();
	// 	myTime = (double) (finish - start) / CLOCKS_PER_SEC;
	// 	myTime = myTime / 10.0;
	// 	fileStream<<number<<"\t"<<myTime<<endl;
	// 	number += 1000;
	// }
	// while (number >= 100000 && number <= 1000000)
	// {
	// 	start = clock();
	// 	for (int i = 0; i < 5; i++)
	// 	{
	// 		int *quickNumber = new int[number];
	// 		for (int j = 0; j < number; j++)
	// 			quickNumber[j] = randomInteger(-65535, 65535);
	// 		quickSort(quickNumber,0, number - 1);
	// 		delete[] quickNumber;
	// 	}
	// 	finish = clock();
	// 	myTime = (double) (finish - start) / CLOCKS_PER_SEC;
	// 	myTime = myTime / 5.0;
	// 	fileStream<<number<<"\t"<<myTime<<endl;
	// 	number += 10000;
	// }
	// while (number >= 1000000 && number <= 10000000)
	// {
	// 	start = clock();
	// 	for (int i = 0; i < 2; i++)
	// 	{
	// 		int *quickNumber = new int[number];
	// 		for (int j = 0; j < number; j++)
	// 			quickNumber[j] = randomInteger(-65535, 65535);
	// 		quickSort(quickNumber,0, number - 1);
	// 		delete[] quickNumber;
	// 	}
	// 	finish = clock();
	// 	myTime = (double) (finish - start) / CLOCKS_PER_SEC;
	// 	myTime = myTime / 2.0;
	// 	fileStream<<number<<"\t"<<myTime<<endl;
	// 	number += 100000;
	// }
	// while (number >= 10000000 && number < 100000000)
	// {
	// 	start = clock();
	// 	for (int i = 0; i < 2; i++)
	// 	{
	// 		int *quickNumber = new int[number];
	// 		for (int j = 0; j < number; j++)
	// 			quickNumber[j] = randomInteger(-65535, 65535);
	// 		quickSort(quickNumber,0, number - 1);
	// 		delete[] quickNumber;
	// 	}
	// 	finish = clock();
	// 	myTime = (double) (finish - start) / CLOCKS_PER_SEC;
	// 	myTime = myTime / 2.0;
	// 	cout<<number<<"\t"<<myTime<<endl;
	// 	number += 1000000;
	// }

	number = 1000;
	ofstream fileStream("mergeSortResult", ios::app);
	while (number < 10000)
	{
		start = clock();
		for (int i = 0; i < 1000; i++)
		{
			int *mergeNumber = new int[number];
			int *mergeAnswer = new int[number];
			for (int j = 0; j < number; j++)
				mergeNumber[j] = randomInteger(-65535, 65535);
			MergeSort(mergeNumber, mergeAnswer, 0, number - 1);
			delete[] mergeNumber;
			delete[] mergeAnswer;
		}
		finish = clock();
		myTime = (double) (finish - start) / CLOCKS_PER_SEC;
		myTime = myTime / 1000.0;
		fileStream<<number<<"\t"<<myTime<<endl;
		number += 100;
	}
	while (number >= 10000 && number < 100000)
	{
		start = clock();
		for (int i = 0; i < 10; i++)
		{
			int *mergeNumber = new int[number];
			int *mergeAnswer = new int[number];
			for (int j = 0; j < number; j++)
				mergeNumber[j] = randomInteger(-65535, 65535);
			MergeSort(mergeNumber, mergeAnswer, 0, number - 1);
			delete[] mergeNumber;
			delete[] mergeAnswer;
		}
		finish = clock();
		myTime = (double) (finish - start) / CLOCKS_PER_SEC;
		myTime = myTime / 10.0;
		fileStream<<number<<"\t"<<myTime<<endl;
		number += 1000;
	}
	while (number >= 100000 && number <= 1000000)
	{
		start = clock();
		for (int i = 0; i < 5; i++)
		{
			int *mergeNumber = new int[number];
			int *mergeAnswer = new int[number];
			for (int j = 0; j < number; j++)
				mergeNumber[j] = randomInteger(-65535, 65535);
			MergeSort(mergeNumber, mergeAnswer, 0, number - 1);
			delete[] mergeNumber;
			delete[] mergeAnswer;
		}
		finish = clock();
		myTime = (double) (finish - start) / CLOCKS_PER_SEC;
		myTime = myTime / 5.0;
		fileStream<<number<<"\t"<<myTime<<endl;
		number += 10000;
	}
	while (number >= 1000000 && number < 10000000)
	{
		start = clock();
		for (int i = 0; i < 2; i++)
		{
			int *mergeNumber = new int[number];
			int *mergeAnswer = new int[number];
			for (int j = 0; j < number; j++)
				mergeNumber[j] = randomInteger(-65535, 65535);
			MergeSort(mergeNumber, mergeAnswer, 0, number - 1);
			delete[] mergeNumber;
			delete[] mergeAnswer;
		}
		finish = clock();
		myTime = (double) (finish - start) / CLOCKS_PER_SEC;
		myTime = myTime / 2.0;
		fileStream<<number<<"\t"<<myTime<<endl;
		number += 100000;
	}
	while (number >= 10000000 && number < 100000000)
	{
		start = clock();
		int *mergeNumber = new int[number];
		int *mergeAnswer = new int[number];
		for (int j = 0; j < number; j++)
			mergeNumber[j] = randomInteger(-65535, 65535);
		MergeSort(mergeNumber, mergeAnswer, 0, number - 1);
		delete[] mergeNumber;
		delete[] mergeAnswer;
		finish = clock();
		myTime = (double) (finish - start) / CLOCKS_PER_SEC;
		myTime = myTime / 2.0;
		cout<<number<<"\t"<<myTime<<endl;
		number += 1000000;
	}
}