#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

int flag[15];
int sum = 0;

int place(int k)   
{   
    int i;   
    for(i=1;i<k;i++)   
      if(abs(k-i)==abs(flag[k]-flag[i]) || flag[k] == flag[i])   
        return 0;   
    return 1;   
} 

void printQueen(int n)
{
  for (int i = 1; i < n + 1; i++)
    for (int j = 1; j < n + 1; j++)
      {
        if (flag[i] != j)
           cout<<". ";
        else if (flag[i] == j)
           cout<<"Q ";
        if (j == n)
           cout<<endl;
      }
  cout<<endl;
}

int queen(int n, int t)   
{   
    if(t>n && n>0) //当放置的皇后超过n时，可行解个数加1，此时n必须大于0   
      {
        printQueen(n);
        sum++;
      }   
    else  
      for(int i=1;i<=n;i++)   
      {   
          flag[t] = i; //标明第t个皇后放在第i列   
          if(place(t)) //如果可以放在某一位置，则继续放下一皇后   
            queen(n, t+1);    
      }   
    return sum;   
}   

int main (int argc, char *argv[])
{
	int t = 0;
	cout<<"test:D\n";
	int number = 0;
	number = atoi(argv[1]);
	t = queen(number, 1);
	cout<<t<<" in total:D"<<endl;
	return 0;
}