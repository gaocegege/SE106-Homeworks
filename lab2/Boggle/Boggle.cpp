/*
 * File: Boggle.cpp
 * ----------------
 * [TODO]
 * Student ID: 5120379091
 * Name: Gao Ce
 * This file is the main starter file for Boggle problem.
 */
 
/*不知道这段文字是不是乱码- -
 *--------------------------------
 *大致想法就是，用二维数组存cube里的字母，机器寻找答案的实现是靠begin()	
 *和robotBeginToKaiGua()实现，利用递归在九宫格里找还没有加过的字母，   	
 *找到一个字母就加到possibleAnswer里看是不是一个前缀，不是就把这个字  	
 *母剔除然后继续递归地往下找，如果全部找完以后，那就return，结束这一	 
 *条递归，继续上一层九宫格的循环之旅。
 */

#include <iostream>
#include <vector>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
   cout << "Welcome!  You're about to play an intense game ";
   cout << "of mind-numbing Boggle.  The good news is that ";
   cout << "you might improve your vocabulary a bit.  The ";
   cout << "bad news is that you're probably going to lose ";
   cout << "miserably to this little dictionary-toting hunk ";
   cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
   cout << endl;
   cout << "The boggle board is a grid onto which I ";
   cout << "I will randomly distribute cubes. These ";
   cout << "6-sided cubes have letters rather than ";
   cout << "numbers on the faces, creating a grid of ";
   cout << "letters on which you try to form words. ";
   cout << "You go first, entering all the words you can ";
   cout << "find that are formed by tracing adjoining ";
   cout << "letters. Two letters adjoin if they are next ";
   cout << "to each other horizontally, vertically, or ";
   cout << "diagonally. A letter can only be used once ";
   cout << "in each word. Words must be at least four ";
   cout << "letters long and can be counted only once. ";
   cout << "You score points based on word length: a ";
   cout << "4-letter word is worth 1 point, 5-letters ";
   cout << "earn 2 points, and so on. After your puny ";
   cout << "brain is exhausted, I, the supercomputer, ";
   cout << "will find all the remaining words and double ";
   cout << "or triple your paltry score." << endl << endl;
   cout << "Hit return when you're ready...";
   getLine();
}

/* Variables */
Lexicon english("EnglishWords.dat");
char theString[5][5];       /* the characters in the cube */
string possibleAnswer = ""; /* the possible answer */
int flag[5][5];             /* the flag in the cube, answer */
std::vector<int> vi,vj;     /* the path of the possible answer */
int buffx = 0, buffy = 0, sizeOfBoard = 0, number = 0;   /* easy to understand:D */
std::vector<string> v;

//define
void robotBeginToKaiGua(int funcx,int funcy);
bool HumanKaiGua(string &word, int funcx, int funcy,int number);


//initial
void initialVariables()
{
  buffx = 0;
  buffy = 0;
  number = 0;
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      {
        flag[i][j] = 0;
      }
}

// [TODO: Fill in the rest of the code]

//random initialize the board
void randomBoard()
{
  int number = 0;
  int flagbuff[25];
  for (int i = 0; i < 25; i++)
      flagbuff[i] = i;
  for (int j = 0; j < 100; j++)
  {
    int exchangei = randomInteger(0, sizeOfBoard*sizeOfBoard - 1);
    int exchangej = randomInteger(0, sizeOfBoard*sizeOfBoard - 1);
    int buff = flagbuff[exchangei];
    flagbuff[exchangei] = flagbuff[exchangej];
    flagbuff[exchangej] = buff;
  }
  if (sizeOfBoard == 4)
  {
    for (int i = 0; i < sizeOfBoard; i++)
      for (int j = 0; j < sizeOfBoard; j++)
      {
        theString[i][j] = STANDARD_CUBES[flagbuff[number]][randomInteger(0,5)];
        number++;
      }
  }
  else
  {
    for (int i = 0; i < sizeOfBoard; i++)
      for (int j = 0; j < sizeOfBoard; j++)
      {
        theString[i][j] = BIG_BOGGLE_CUBES[flagbuff[number]][randomInteger(0,5)];
        number++;
      }
  }
  return;
}

//to upper
void toupper(string &word)
{
  for (int i = 0; i < word.size(); i++)
  {
    if (word[i] >= 'a' && word[i] <= 'z')
      word[i] += ('A' - 'a');
  }
}

//is in the v?
bool isValid(string word)
{
  for (int ihaha = 0; ihaha < v.size(); ihaha++)
    {
      if (word == v[ihaha])
        return false;
    }
  return true;
}

//Human stage
bool whetherIsInBoard(string &word)
{
  possibleAnswer.clear();
  vi.clear();
  vj.clear();
  vi.push_back(-1);
  vj.push_back(-1);
  for (int i = 0; i < sizeOfBoard; i++)
    for (int j = 0; j < sizeOfBoard; j++)
      if (word[0] == theString[i][j])
      {
        flag[i][j] = 1;
        vi.push_back(i);
        vj.push_back(j);
        if (HumanKaiGua(word,i,j,1) == true)
          return true;
        else
          continue;
      }
  return false;
}

bool HumanKaiGua(string &word, int funcx, int funcy,int number)
{
  if (number == word.size())
    return true;
  int xiMin = (funcx - 1 >= 0? funcx - 1 : 0);
  int yiMin = (funcy - 1 >= 0? funcy - 1 : 0);
  int xiMax = (funcx + 1 <= sizeOfBoard - 1? funcx + 1 : sizeOfBoard - 1);
  int yiMax = (funcy + 1 <= sizeOfBoard - 1? funcy + 1 : sizeOfBoard - 1);
  for (int i = xiMin ; i <= xiMax; i++)
    for (int j = yiMin ;j <= yiMax; j++)
    {
      if (flag[i][j] == 0 && word[number] == theString[i][j])
      {
        number++;
        vi.push_back(i);
        vj.push_back(j);
        flag[i][j] = 1;
        if (!HumanKaiGua(word, i, j, number))
        {
          flag[i][j] = 0;
          continue;
        }
        else return true;
      }
    }
  return false;
}

//begin to claculate
void beginRobot()
{
  for (int i = 0; i < sizeOfBoard; i++)
    for (int j = 0; j < sizeOfBoard; j++)
    {
      vi.clear();
      vj.clear();
      for (int ib = 0; ib < sizeOfBoard; ib++)
        for (int jb = 0; jb < sizeOfBoard; jb++)
        {
          flag[ib][jb] = 0;
        }
      vi.push_back(-1);
      vj.push_back(-1);
      possibleAnswer = theString[i][j];
      flag[i][j] = 1;
      vi.push_back(i);
      vj.push_back(j);
      robotBeginToKaiGua(i, j);
    }
}

//robot stage:robot begins to kai gua;
void robotBeginToKaiGua(int funcx, int funcy)
{
  buffx = funcx;
  buffy = funcy;
  int xiMin = (funcx - 1 >= 0? funcx - 1 : 0);
  int yiMin = (funcy - 1 >= 0? funcy - 1 : 0);
  int xiMax = (funcx + 1 <= sizeOfBoard - 1? funcx + 1 : sizeOfBoard - 1);
  int yiMax = (funcy + 1 <= sizeOfBoard - 1? funcy + 1 : sizeOfBoard - 1);
  for (int i = xiMin ; i <= xiMax; i++)
    for (int j = yiMin ;j <= yiMax; j++)
    {
      if (flag[i][j] == 0)
      {
        possibleAnswer += theString[i][j];
        flag[i][j] = 1;
        if (!english.containsPrefix(possibleAnswer))
        {
          possibleAnswer = possibleAnswer.substr(0,possibleAnswer.size() - 1);//maybe wrong
          flag[i][j] = 0;
        }
        else 
        {
          funcx = i;
          funcy = j;
          vi.push_back(i);
          vj.push_back(j);
          if (english.contains(possibleAnswer) && possibleAnswer.size() > 3)
          {
            if (isValid(possibleAnswer))
            {
              v.push_back(possibleAnswer);
              recordWordForPlayer(possibleAnswer, COMPUTER);
              for (int ianswer = 1; ianswer < vi.size(); ianswer++)
                {
                  highlightCube(vi[ianswer], vj[ianswer], true);
                  pause(50);
                }
                pause(250);
              for (int ianswer = 1; ianswer < vi.size(); ianswer++)
                  highlightCube(vi[ianswer], vj[ianswer], false);
            }
          }
          robotBeginToKaiGua(funcx, funcy);
        }
      }
    }
  possibleAnswer = possibleAnswer.substr(0,possibleAnswer.size() - 1);//maybe wrong
  flag[vi[vi.size() - 1]][vj[vj.size() - 1]] = 0;
  vi.pop_back();
  vj.pop_back();
  return;
}

/* Main program */

void MyMain()
{
  //variables
  string bogglesize = "", boardConfig = "", myString = "", humanWord = "";

  //initial the variables
  initialVariables();
  v.clear();

  //get the size
  cout<<"You can choose standard Boggle (4x4 grid)\nor Big Boggle (5x5)\n";
  while (1)
  {
    bogglesize = getLine("Would you like Big Boggle?[yes | no]");
    toupper(bogglesize);
    //decide the size
    if ((bogglesize[0] == 'Y' && bogglesize.size() == 1) || (bogglesize.size() == 3 && bogglesize[0] == 'Y' && bogglesize[1] == 'E' && bogglesize[2] == 'S'))
      {
        sizeOfBoard = 5;
        break;
      }
    else if ((bogglesize[0] == 'N' && bogglesize.size() == 1) || (bogglesize.size() == 2) && bogglesize[0] == 'N' && bogglesize[1] == 'O')
      {
        sizeOfBoard = 4;
        break;
      }
  }
  //input string or not
  cout<<"I'll give you a chance to set up the board to your specification, "
  <<"when makes it easier to confirm your boggle program is working.\n";
  while (1)
  {
    boardConfig = getLine("Do you want to force the badrdconfiguration? [yes|no]:");
    toupper(boardConfig);
    //get the input string
    if ((boardConfig[0] == 'N' && bogglesize.size() == 1) || (boardConfig.size() == 2) && boardConfig[0] == 'N' && boardConfig[1] == 'O')
    {
      randomBoard();
      break;
    }
    else if ((boardConfig[0] == 'Y' && boardConfig.size() == 1) || (boardConfig.size() == 3 && boardConfig[0] == 'Y' && boardConfig[1] == 'E' && boardConfig[2] == 'S'))
    {
      cout<<"enter a 16-character string to identify which letters you want"
      <<"on the cubes. The first 4 letters are the cubes on the top row from"
      <<"left to rignt, the next 4 letters are the second row,and so on.\n";
      myString = getLine("Enter a string:");
      toupper(myString);
      while (myString.size() < sizeOfBoard * sizeOfBoard)
      {
        myString = getLine("String must include 16 characters! Try again.Enter a string:");
        toupper(myString);
      }
      for (int i = 0; i < sizeOfBoard; i++)
        for (int j = 0; j < sizeOfBoard; j++)
        {
          int temp = (i)*sizeOfBoard + (j);
          theString[i][j] = myString[temp];
        }
      break;
    }
  }

  //draw the board
  drawBoard(sizeOfBoard, sizeOfBoard);

  //label the letters
  for (int i = 0; i < sizeOfBoard; i++)
    for (int j = 0; j < sizeOfBoard; j++)
    {
      labelCube(i, j,theString[i][j]);
    }

  //Human inputs
  while (1)
  {
    bool isInBoard = true;
    humanWord = getLine("Enter a word:");
    toupper(humanWord);
    if (humanWord == "")
      break;
    if (humanWord.size() < 4)
      cout<<"I'm sorry but we have our standards.\n"
          <<"That word doesn't meet the minimum word length.\n";
    else if (!english.contains(humanWord))
      cout<<"It is not a valid word!\n";
    else if (whetherIsInBoard(humanWord) && isValid(humanWord))
    {
      recordWordForPlayer(humanWord, HUMAN);
      v.push_back(humanWord);
      for (int ianswer = 1; ianswer < vi.size(); ianswer++)
        {
          highlightCube(vi[ianswer], vj[ianswer], true);
          pause(50);
        }
        pause(250);
      for (int ianswer = 1; ianswer < vi.size(); ianswer++)
          highlightCube(vi[ianswer], vj[ianswer], false);
    }
    else
      cout<<"It is not valid!\n";
      //initial the variables again
      initialVariables();
  }
  //robot begins to work
  beginRobot();
  return;
}

int main() {
  GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
  initGBoggle(gw);
  welcome();
  giveInstructions();
  cin.clear();
  string againOrNot = "";
  bool againBool = false;
  while (1)
  {
    MyMain();
    while (1)
    {
      againOrNot = getLine("Would you like to play again?[yes | no]");
      toupper(againOrNot);
      //decide the size
      if ((againOrNot[0] == 'Y' && againOrNot.size() == 1) || (againOrNot.size() == 3 && againOrNot[0] == 'Y' && againOrNot[1] == 'E' && againOrNot[2] == 'S'))
        {
          againBool = true;
          break;
        }
      else if ((againOrNot[0] == 'N' && againOrNot.size() == 1) || (againOrNot.size() == 2) && againOrNot[0] == 'N' && againOrNot[1] == 'O')
        {
          return 0;
        }
    }
    if (againBool == true)
      continue;
    else break;
  }
  return 0;
}

