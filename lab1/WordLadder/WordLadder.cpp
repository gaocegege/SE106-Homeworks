/*
 * File: WordLadder.cpp
 * --------------------
 * [TODO: fill in your name and student ID]
 * Name: gaoce
 * Student ID: 5120379091
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"//
#include "lexicon.h"//
#include "queue.h"
#include "simpio.h"//
#include "vector.h"
#include "map.h"
using namespace std;

int main() {
	string startWord,finishWord;
	Queue<Vector<string> > queue;
	Vector<string> first,temp;
	string buff,answer;
	Map<string,int> usedWords;
	int count = 1;
	Lexicon words("EnglishWords.dat");
	while (true)
	{
		startWord = getLine("Enter start word (RETURN to quit):");
		if (startWord == "")
			return 0;
		if (words.contains(startWord) == false)
			getLine("the word is not in the lexicon");
		finishWord = getLine("Enter destination word:");
		if (words.contains(finishWord) == false)
			getLine("the word is not in the lexicon");
		if (startWord.size() != finishWord.size())
			getLine("the length of the word is not the same");
		first.add(startWord);
		queue.enqueue(first);
		usedWords.put(startWord,1);
		answer = "";
		while (queue.isEmpty() != true)
		{
			temp = queue.dequeue();//copy deeply?
			buff = temp[temp.size()-1];
			if (buff == finishWord)
			{
				for (int i = 0; i < temp.size(); i++)
					answer += (temp[i] + " ");
				getLine("Found ladder: " + answer + "(please return to continue)");

			}
			for (int i = 0; i < buff.size(); i++)
			{
				buff = temp[temp.size()-1];
				for (int j = 'a'; j < 'z'; j++)
				{
					buff[i] = j;
					if (words.contains(buff))
					{
						if (usedWords.containsKey(buff) != true)
						{
							Vector<string> cece;
							for (int i = 0; i < temp.size(); i++)
								cece.add(temp[i]);
							cece.add(buff);
							queue.enqueue(cece);
							usedWords.put(buff,1);
						}
					}
				}
			}
		}
		if (answer == "")
			getLine("No Ladder found");
	}
}
