#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include <cstring>
#include <queue>
#include <map>
#include <stdint.h>

using namespace std;

int FxxkTheStrcmp_WhyIsTheFunctionSoManyBugs(string &fxxk0, string &fxxk1)
{
  int flag = 0;
  for (int i = 0; i < fxxk1.size(); i++)
  {
    if (fxxk1[i] != fxxk0[i])
      flag = 1;
  }
  return flag;
}

uint32_t binaryPow(int p)//right
{
  uint32_t result = 1;
  if (p == 0)
    return 1;
  for (int i = 1; i < p + 1; i++)
  {
    result *= 2;
  }
  return result;
}

uint32_t binaryStringToint(string &s)//right
{
  uint32_t result = 0;
  uint32_t p = 0;
  for (int i = s.size() - 1; i > -1; i--)
  {
    result += (s[i] - '0') * binaryPow(p);
    p++;
  }
  return result;
}

unsigned char ctoa(string a)
{
  unsigned char c = 0;
  for (int i = 0; i < 8; i++)
  if (a[i] != 0)
  {
    c = c + (int)(a[i] - '0')*binaryPow(8 - 1 - i);
  }
  return c;
}

string ByteToBinaryString(uint32_t v) {  
    if (v == 1) {  
        return "1";   
    }  
      
    if (v % 2 == 0) {  
        return ByteToBinaryString(v / 2) + "0";  
    } 

    else {  
        return ByteToBinaryString(v / 2) + "1";  
    }  
}

string ByteToBinaryString(int v) {  
    if (v == 1) {  
        return "1";   
    }  
      
    if (v % 2 == 0) {  
        return ByteToBinaryString(v / 2) + "0";  
    } 

    else {  
        return ByteToBinaryString(v / 2) + "1";  
    }  
}

string ByteToBinaryString(unsigned char v) {  
    if (v == 1) {  
        return "1";   
    }  
      
    if (v % 2 == 0) {  
        return ByteToBinaryString(v / 2) + "0";  
    } else {  
        return ByteToBinaryString(v / 2) + "1";  
    }  
}  

struct MyCode
{
  char c;
  uint32_t bits;
  uint32_t sizes;
};

struct HulfmanTreeNode
{
  /* data */
  char v;
  int num;
  string code;
  bool is_node;
  int left;
  int right;

  /* Func */
  HulfmanTreeNode(char x, int y, bool ff, int l=-1, int r=-1)
  { 
    v = x; 
    num = y;
    code = "";
    is_node = ff;
    left = l;
    right = r;
  }

  HulfmanTreeNode(){}

  // bool operator> (const HulfmanTreeNode &a)
  // {
  //   return num > a.num;
  // }
};

struct cmpFunction
{
  bool operator()(HulfmanTreeNode &a,HulfmanTreeNode &b)
  {
      return a.num > b.num;
  }
};

class HulfmanTree
{
public:
  HulfmanTree(bool isDecompress, string fileName1, string fileName2);

private:
  priority_queue<HulfmanTreeNode, vector<HulfmanTreeNode>, cmpFunction> queue;//the main struction
  map<char, int> contains;//used for the input to build the pre-char map
  uint32_t used;
  uint32_t maxsizes;


  void buildQueue();
  void compress(string fileName1, string fileName);
  void decompress(string fileName1, string fileName);
};

HulfmanTree::HulfmanTree(bool isDecompress, string fileName1, string fileName2)
  :used(0), maxsizes(0)
{
  ifstream ifs(fileName1.c_str(), ios::in | ios::binary);
  char c;
  if (isDecompress == true)
  {
    ifs.close();
    decompress(fileName1, fileName2);
  }

  else
  {
    while (ifs.get(c))
    {
      // if (c != '\n')//erase the last char
      // {
        // cout<<c<<endl<<"haha"<<endl;
        contains[c]++;
      // }
    }
    ifs.close();
    buildQueue();
    compress(fileName1, fileName2);
  }
}

void HulfmanTree::buildQueue()
{
  map<char,int>::iterator it = contains.begin();
  for ( ; it != contains.end(); it++)
  {
    used++;
    queue.push(HulfmanTreeNode(it->first, it->second, true));
  }
}

void HulfmanTree::compress(string fileName1, string fileName)
{
  ifstream ifs(fileName1.c_str(), ios::in | ios::binary);
  ofstream ofs(fileName.c_str(), ios::out | ios::binary);
  char c;
  string strBuf = "";
  maxsizes = 0;

  std::vector<HulfmanTreeNode> result;
  while (queue.size() > 1)
  {
    HulfmanTreeNode firstNode = queue.top();
    // cout<<"first:"<<firstNode.v<<"\t"<<firstNode.num<<endl;
    queue.pop();
    result.push_back(firstNode);

    HulfmanTreeNode secondNode = queue.top();
    // cout<<"second:"<<secondNode.v<<"\t"<<secondNode.num<<endl;
    queue.pop();
    result.push_back(secondNode);

    queue.push(HulfmanTreeNode('0', firstNode.num + secondNode.num, false, result.size() - 2, result.size() - 1));
  }
  HulfmanTreeNode lastNode = queue.top();
  queue.pop();
  result.push_back(lastNode);

  for (int i = result.size() - 1; i >= 0; i--)//encode the Hulfman
  {
    if (result[i].left != -1)
      result[ result[i].left ].code = result[i].code + "0";
    if (result[i].right != -1)
      result[ result[i].right ].code = result[i].code + "1";
  }

  for (int i = 0; i < result.size(); i++)
  {
    if (result[i].is_node == true)
      cout<<result[i].v<<"\t"<<result[i].code<<endl;
  }
  MyCode buf;

  //cout<<used<<endl<<sizeof(used)<<endl<<sizeof(MyCode)<<endl;

  ofs.write((char *)(&used),sizeof(used));
  ofs.seekp(sizeof(uint32_t) * 2);

  for (int i = 0; i < result.size(); i++)
  {
    if (result[i].is_node == true)
    {
      buf.c = result[i].v;
      buf.bits = binaryStringToint(result[i].code);
      buf.sizes = result[i].code.size();

      //cout<<buf.c<<"\t"<<buf.bits<<endl;

      ofs.write((char *)(&buf), sizeof(buf));
    }
  }

  ifs.seekg(0);

  while (ifs.get(c))
  {
    // maxsizes++;
    // cout<<c<<endl;
    // if (c != '\n')//maybe wrong
    // {
      for (int i = 0; i < result.size(); i++)
      {
        if (result[i].v == c && result[i].is_node == true)
        {
          strBuf += result[i].code;

          // cout<<result[i].v<<"\t"<<result[i].code<<endl;
          // cout<<strBuf<<endl;

          if (strBuf.size() > 8)
          {
            unsigned char temp = ctoa(strBuf.substr(0, 8));

            // cout<<strBuf<<endl;

            ofs.write((char *)&temp, sizeof(unsigned char));
            strBuf = strBuf.substr(8, strBuf.size() - 8);
          }
          break;
        }
      }
    // }
  }

  /* deal with the stringBuf < 8 */
  maxsizes = 8 - strBuf.size();
  strBuf += "00000000";
  strBuf = strBuf.substr(0, 8);
  unsigned char temp = ctoa(strBuf);
  ofs.write((char *)&temp, sizeof(unsigned char));
  strBuf.clear();
  ofs.seekp(sizeof(uint32_t));
  cout<<maxsizes<<endl;
  ofs.write((char *)(&maxsizes), sizeof(maxsizes));
}

void HulfmanTree::decompress(string fileName1, string fileName)//wrong?
{
  ifstream ifs(fileName1.c_str(), ios::in | ios::binary);
  ofstream ofs(fileName.c_str(), ios::out | ios::binary);
  std::vector<HulfmanTreeNode> result;
  MyCode buf;
  bool flag = false;
  HulfmanTreeNode nodeBuf;

  ifs.read((char *)(&used), sizeof(used));
  ifs.read((char *)(&maxsizes), sizeof(maxsizes));
  cout<<maxsizes<<endl;
  for (int i = 0; i < used; i++)
  {
    ifs.read((char *)(&buf), sizeof(buf));
    if (buf.bits == 0)
    {
      nodeBuf.v = buf.c;
      nodeBuf.code = "";
      nodeBuf.is_node = true;
      nodeBuf.num = buf.sizes;
      nodeBuf.left = -1;
      nodeBuf.right = -1;
      for (int i = 0; i < buf.sizes; i++)
        nodeBuf.code += "0";

      cout<<nodeBuf.v<<"\t"<<nodeBuf.code<<"\t"<<nodeBuf.num<<endl;

      result.push_back(nodeBuf);
    }
    else
    {
      nodeBuf.v = buf.c;
      nodeBuf.code = ByteToBinaryString(buf.bits);
      nodeBuf.is_node = true;
      nodeBuf.num = nodeBuf.code.size();
      nodeBuf.left = -1;
      nodeBuf.right = -1;
      for (int i = 0; i < buf.sizes - nodeBuf.num; i++)
        nodeBuf.code = "0" + nodeBuf.code;
      nodeBuf.num = buf.sizes;

      cout<<nodeBuf.v<<"\t"<<nodeBuf.code<<"\t"<<nodeBuf.num<<endl;

      result.push_back(nodeBuf);
    }
  }
//------------------------------------------------------------------------------------------------
  string streamBuf = "";

  ifs.seekg(2 * sizeof(used) + used * sizeof(buf));

  string mystrBuf = "";

  while (1)
  {
    while (streamBuf.size() < 256)//maybe wrong
    {
      if (ifs.peek() == EOF)  //http://hi.baidu.com/yjc0407/item/fc8c591a03a84af865eabfd2
      {
        cout<<"flag"<<endl;
        flag = true;
        break;
      }
      unsigned char tmp;
      ifs.read((char *)(&tmp), sizeof(tmp));

      // cout<<tmp<<endl;

      if (tmp == 0)
        streamBuf += "00000000";
      else
      {
        mystrBuf = ByteToBinaryString(tmp);
        int hehe = mystrBuf.size();
        for (int i = 0; i < 8 - hehe; i++)
        {
          mystrBuf = "0" + mystrBuf;
        }
        // cout<<mystrBuf<<endl;
        streamBuf += mystrBuf;
      }
    }

    while (streamBuf.size() >= 256)
    {
      char tmp;
      for (int i = 0; i < result.size(); i++)
      {
        string resultBuf = "";
        resultBuf += result[i].code;
        if (FxxkTheStrcmp_WhyIsTheFunctionSoManyBugs(streamBuf, resultBuf) == 0)
        {
          tmp = result[i].v;
          ofs.write((char *)&tmp, sizeof(tmp));
          streamBuf = streamBuf.substr(resultBuf.size(), streamBuf.size() - resultBuf.size());
          break;
        }
      }
    }

    if (flag == true)
      break;
  }

  flag = false;
  string tmpB = "";
  tmpB = streamBuf;
  tmpB = tmpB.substr(0, tmpB.size() - maxsizes);
  /* deal with the else */
  while (tmpB.size() != 0)
  {
    char tmp;
    for (int i = 0; i < result.size(); i++)
    {
      char resultBuf[512] = "\0";
      strcat(resultBuf, result[i].code.c_str());
      if (strncmp(tmpB.c_str(), resultBuf, strlen(resultBuf)) == 0)
      {
        tmp = result[i].v;
        ofs.write((char *)&tmp, sizeof(tmp));
        tmpB = tmpB.substr(strlen(resultBuf), tmpB.size() - strlen(resultBuf));
        // strcpy(tmpB, tmpB + strlen(resultBuf));//maybe wrong
        break;
      }
    }
  }
}

void useage(string prog) {
  cerr << "Useage: " << endl
      << "    " << prog << "[-d] input_file output_file" << endl;
  exit(2);
}

int main(int argc, char* argv[]) {
  int i;
  string inputFilename, outputFilename;
  bool isDecompress = false;
  for (i = 1; i < argc; i++) {
    if (argv[i] == string("-d")) isDecompress = true;
    else if (inputFilename == "") inputFilename = argv[i];
    else if (outputFilename == "") outputFilename = argv[i];
    else useage(argv[0]);
  }
  if (outputFilename == "") useage(argv[0]);
  // if (isDecompress) decompress(inputFilename, outputFilename);
  // else compress(inputFilename, outputFilename);

  HulfmanTree myTree(isDecompress, inputFilename, outputFilename);
  return 0;
}
