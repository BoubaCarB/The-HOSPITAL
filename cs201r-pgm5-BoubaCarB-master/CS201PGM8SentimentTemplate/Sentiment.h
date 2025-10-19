#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;

struct wordList {
    string word;
    double value;
};

struct replaceList {
    string origWord;
    double origValue;
    string newWord;
    double newValue;
};

void   loadSentiment(vector<wordList>& sentList, vector<wordList>& posList, vector<wordList>& negList);
//PRE:   accepts an empty set of 3 <wordList> vectors
//POST:  loads all three vectors with data from sentiment.txt

void   processFile(ifstream& inFile, ofstream& outFile, string fileName,
                   vector<wordList>& words, vector<wordList>& posList, vector<wordList>& negList);
//PRE:   accepts the inFile (the current review file)  opened and verified in main 
//       the output file name (where all reviews are posted) opened and verified in main
//       a string containing the fileName (for printing to the output file)
//       and 3 <wordList> vectors with words loaded
//POST:  reviews the inFile and outputs to outFile the review sentiment, a more positive and more negative review (if possible)


 
