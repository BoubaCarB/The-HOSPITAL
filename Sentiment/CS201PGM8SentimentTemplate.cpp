// CS201PGM8Sentiment 
// NAME:  Boubacar Balde

// Source : Chatgpt, used wherever I didn't know how to write a lin of code, and it also modified when stuck with errors.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Sentiment.h"
#include "sentiment1.h"
#include "SentimentMain.h"


  // Include this at the top of your file


void runSentiment() {

    
    vector<wordList> sentList, posList, negList;

    // load vectors 
    loadSentiment(sentList, posList, negList);

    // open output file 
    ofstream outFile("../Sentiment/output.txt");
    if (!outFile) {
        cout << "Error: Unable to create output file.\n";
        return;
    }

    // open review files
    string fileName;
    for (unsigned int i = 1; i < 9; i++) {

        // open input file adding to_string(i) + ".txt" to review
        string fileName = "../Sentiment/review" + to_string(i) + ".txt";
        ifstream inFile(fileName);
        
        // if not able to open, print a message and continue
        if (!inFile) {
            cout << "Error: Unable to open " << fileName << endl;
            continue;  // to the next file
        }

        // else process the file & close it
        // Process the review file
        processFile(inFile, outFile, fileName, sentList, posList, negList);

        cout << "Successfully opened " << fileName << endl;
        inFile.close();  // Close the file after checking
    }
    srand(time(0));  // for random seed so different replacements occur each run


     //close the output file
    outFile.close(); 
    return;
}

