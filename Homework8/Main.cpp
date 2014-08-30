#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class minHeap
{
private:
    vector<int> array;
    vector<string> v;
    int theSize;
public:
    minHeap()
    {
        array = vector<int>(100);
        v= vector<string>(100);
        theSize =0;
    }
    int GetLittleInt();
    string GetLittleStr();
    int Size();
    void Insert(int theData, string str);
    void Delete(int pos);
    void Print();
};

int minHeap::GetLittleInt()
{
    return array[1];
}

string minHeap::GetLittleStr()
{
    return v[1];
}

int minHeap::Size()
{
    return theSize;
}

void minHeap::Insert(int theData,string str)
{
    if(theSize+1>array.size())
    {
        array.resize(array.size()*2);//resize the vector
        v.resize(v.size()*2);
    }

    int hole = ++theSize;//the next of the size is the hole

    for(; hole > 1 && array[hole / 2] > theData; hole = hole / 2)//when the hole > its parent or it becomes the root,stop
    {
        array[hole]=array[hole/2];
        v[hole]=v[hole/2];
    }

    array[hole]=theData;//insert the data
    v[hole] = str;
}

void minHeap::Delete(int pos)
{
    if(theSize < pos)
    {    
        cout<<"error!"<<endl;
        return;
    }

    int hole = pos;//the position becomes a hole

    string strtmp = v[theSize];
    int tmp = array[theSize--];

    while(hole*2 <= theSize)
    {
        int child;

        if(hole*2 == theSize)
            child = hole*2;

        if(array[hole*2]>array[hole*2+1])
            child = hole*2+1;
        else
            child = hole*2;

        array[hole] = array[child];
        v[hole] = v[child];

        hole = child;
    }

    array[hole] = tmp;
    v[hole] = strtmp;
}

void minHeap::Print()
{
    for(int i=1;i<=theSize;i++)
        cout<<array[i]<<"\t"<<v[i]<<endl;
}

struct myChar
{
    /* data */
    int pre;
    int times;
    char c;
};

int main()
{
    minHeap heap;
    myChar buff;
    string str;
    int sum = 0;
    int cposition = 0;
    vector<myChar> charBuf;

    cout<<"Please input the number\n";
    while (getline(cin, str))
    {
        if (str == "")
            break;
        int number;
        string strBuf;
        stringstream strStream;
        strStream<<str;

        strStream>>number;
        buff.pre = 0;
        buff.times = number;
        buff.c = 'a' + cposition;

        charBuf.push_back(buff);

        strStream.clear();
        strStream<<buff.c;
        strStream>>strBuf;

        heap.Insert(number, strBuf);

        cposition++;
    }

    heap.Print();

    while (heap.Size() != 1)
    {
        int littleNumber1, littleNumber2;
        string littleStr1, littleStr2;

        littleNumber1 = heap.GetLittleInt();
        littleStr1 = heap.GetLittleStr();
        heap.Delete(1);

        littleNumber2 = heap.GetLittleInt();
        littleStr2 = heap.GetLittleStr();
        heap.Delete(1);

        littleNumber1 += littleNumber2;
        littleStr1 += littleStr2;

        for (int i = 0; i < littleStr1.size(); i++)
        {
            for (int j = 0; j < charBuf.size(); j++)
                if (littleStr1[i] == charBuf[j].c)
                {
                    charBuf[j].pre++;
                    break;
                }
        }

        heap.Insert(littleNumber1, littleStr1);
    }

    for (int i = 0; i < charBuf.size(); i++)
    {
        sum += charBuf[i].pre*charBuf[i].times;
    }

    cout<<"The calculation is over\n"<<"The sum is "<<sum<<endl;
}