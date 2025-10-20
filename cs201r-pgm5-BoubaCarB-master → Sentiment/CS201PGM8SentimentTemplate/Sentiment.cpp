#include "Sentiment.h"



//SUPPORT FUNCTION TO FIND THE CURRENT WORD IN THE SENTEMENT VECTOR & RETURN THE SENTIMENT VALUE
//PRE:   accepts a string (in) and the words list
//POST:  returns the sentiment of the word if found or the value 0 if not
double sentimentVal(string in, vector<wordList> &words) {
    for (const auto& w : words) {
        if (w.word == in) {
            return w.value;
        }
    }
    return 0; // if word is not found
}




//PRE:   accepts an empty set of 3 <wordList> vectors
//POST:  loads all three vectors with data from sentiment.txt
void loadSentiment(vector<wordList>& sentList,
    vector<wordList>& posList,
    vector<wordList>& negList) {

    //open sentiment.txt
    ifstream inFile("sentiment.txt");
    if (!inFile) {
        cout << "Error: Unable to open sentiment.txt\n";
        return;
    }

    //add the word to the sentList vector
    string line, word;
    double value;
    while (getline(inFile, line)) {
        size_t commaPos = line.find(','); // Find the comma separator
        if (commaPos != string::npos) {     // If word does nto contain comma ---- Chatgpt 
            word = line.substr(0, commaPos);  // Extract the word
            value = stod(line.substr(commaPos + 1));  // Convert sentiment value to double

            // a temporary wordList struct and assign values
            wordList temp;
            temp.word = word;
            temp.value = value;

            // Store word and sentiment value in sentList
            sentList.push_back(temp);

            //if positive enough add to posList
            if (value > 1.25) {
                posList.push_back(temp);
            //if negative enough add to negList
            } else if (value < -1.25) {
                negList.push_back(temp);
            }
        }
    }
    

    //close sentiment.txt
    inFile.close();


 
}
    

//PRE:  positive & negative word lists are sent
//POST: Open the input file & output file (infile+Output 
//      'Clean' the input by removing syntax and setting all to lower case
//       Get the sentiment value for the edited word
//        store unedited word in vector with sentiment value
//         if sentiment < -1  find a positive word to replace it
//         if sentiment > 1   find a negative word to replace

void processFile(ifstream& inFile, ofstream& outFile, string fileName,
                    vector<wordList>& words,               // vectors containing the word & sentiment
                    vector<wordList>& posList, 
                    vector<wordList>& negList) {
    

    string inWord, newWord;
    char newChar;
    vector<wordList> origWords, negWords, posWords;
    double totalSentiment = 0.0; // Total sentiment value for the review
    double newNegSentiment = 0.0; // after making it more negative
    double newPosSentiment = 0.0; // after making it more positive
    vector<replaceList> negReplacements, posReplacements;



    cout << "PROCESSING FILE: " << fileName << endl << endl;
    outFile << "PROCESSING FILE: " << fileName << endl << endl;

    // reset all vectors & values before processing inFile
    //   read and edit the initial file
    //   remove any unnecessary characters
    while (inFile >> inWord) {
        //  the inFile read will read a word up to the next space.
        //  there may be some unwanted characters
        //  read char by char and only use alphabetic characters
        //  and change all uppercase to lowercase
        newWord = "";
        for (int i = 0, len = inWord.size(); i < len; i++) {
            if (isalpha(inWord[i])) {
                newChar = tolower(inWord[i]);
                newWord += newChar;
            }
        }
        // add the 'clean' word to a temp location & add original word & sentiment value to origWords
        double sentiment = sentimentVal(newWord, words);
        totalSentiment += sentiment;
        wordList temp;
        temp.word = inWord; // store original word (not cleaned)
        temp.value = sentiment;
        origWords.push_back(temp);

        //CHECK TO MAKE SENTIMENT MORE NEGATIVE
        if (sentiment > 1 && !negList.empty()) {
            int randIndex = rand() % negList.size();
            wordList replacement = negList[randIndex];

            replaceList negChange = {inWord, sentiment, replacement.word, replacement.value};
            negReplacements.push_back(negChange);
            negWords.push_back(replacement);
            newNegSentiment += replacement.value;
        } else {
            negWords.push_back(temp);
            newNegSentiment += sentiment;
        }

        //CHECK TO MAKE SENTIMENT MORE POSITIVE
        if (sentiment < -1 && !posList.empty()) {
            int randIndex = rand() % posList.size();
            wordList replacement = posList[randIndex];

            replaceList posChange = {inWord, sentiment, replacement.word, replacement.value};
            posReplacements.push_back(posChange);
            posWords.push_back(replacement);
            newPosSentiment += replacement.value;
        } else {
            posWords.push_back(temp);
            newPosSentiment += sentiment;
        }
    }

    //OUTPUT UPDATES
    //EDIT ORIGINAL WORDS VECTOR FOR OUTPUT
    //check to see if the length of the words written so far

    outFile << "FORMATTED REVIEW: \n";
    cout << "FORMATTED REVIEW: \n";
    int lineLength = 0;
    for (unsigned int i = 0; i < origWords.size(); i++) {
        lineLength += origWords[i].word.length() + 1;
        if (lineLength > 80) {
            outFile << "\n";
            cout << "\n";
            lineLength = origWords[i].word.length() + 1;
        }
        outFile << origWords[i].word << " ";
        cout << origWords[i].word << " ";
    }

    // Output sentiment value
    outFile << "\n\nORIGINAL SENTIMENT: " << totalSentiment << "\n\n";
    cout << "\n\nORIGINAL SENTIMENT: " << totalSentiment << "\n\n";

    //EDIT MORE NEGATIVE VECTOR FOR OUTPUT
    if (totalSentiment == newNegSentiment) {
        outFile << "REVIEW NOT UPDATED. THE SENTIMENT REMAINS: " << totalSentiment << "\n";
        cout << "REVIEW NOT UPDATED. THE SENTIMENT REMAINS: " << totalSentiment << "\n";
    } else {
        outFile << "WORDS UPDATED TO BE MORE NEGATIVE:\n\n";
        cout << "WORDS UPDATED TO BE MORE NEGATIVE:\n\n";
        double negTotalBefore = 0, negTotalAfter = 0;
        for (const auto& change : negReplacements) {
            cout << setw(15) << left << change.origWord << setw(8) << change.origValue 
                 << setw(15) << left << change.newWord << setw(8) << change.newValue << endl;
            outFile << setw(15) << left << change.origWord << setw(8) << change.origValue 
                   << setw(15) << left << change.newWord << setw(8) << change.newValue << endl;
            negTotalBefore += change.origValue;
            negTotalAfter += change.newValue;
        }
        cout << "\nTOTALS: " << setw(20) <<  left << negTotalBefore  << setw(10) << " " << negTotalAfter << endl << endl;
        outFile <<  "\nTOTALS: " << setw(20) <<  left << negTotalBefore  << setw(10) << " " << negTotalAfter << endl << endl;

        outFile << "UPDATED REVIEW (MORE NEGATIVE):\n";
        cout << "UPDATED REVIEW (MORE NEGATIVE):\n";
        lineLength = 0;
        for (const auto& w : negWords) {
            lineLength += w.word.length() + 1;
            if (lineLength > 80) {
                outFile << "\n";
                cout << "\n";
                lineLength = w.word.length() + 1;
            }
            outFile << w.word << " ";
            cout << w.word << " ";
        }
        outFile << "\n\nUPDATED SENTIMENT: " << newNegSentiment << "\n\n";
        cout << "\n\nUPDATED SENTIMENT: " << newNegSentiment << "\n\n";
    }

    //EDIT MORE POSITIVE VECTOR FOR OUTPUT
    if (totalSentiment == newPosSentiment) {
        outFile << "REVIEW NOT UPDATED. THE SENTIMENT REMAINS: " << totalSentiment << "\n";
        cout << "REVIEW NOT UPDATED. THE SENTIMENT REMAINS: " << totalSentiment << "\n";
    } else {
        outFile << "\nWORDS UPDATED TO BE MORE POSITIVE:\n\n";
        cout << "\nWORDS UPDATED TO BE MORE POSITIVE:\n\n";
        double posTotalBefore = 0, posTotalAfter = 0;
        for (const auto& change : posReplacements) {
            cout << setw(15) << left << change.origWord << setw(8) << change.origValue 
                 << setw(15) << left << change.newWord << setw(8) << change.newValue << endl;
            outFile << setw(15) << left << change.origWord << setw(8) << change.origValue 
                   << setw(15) << left << change.newWord << setw(8) << change.newValue << endl;
            posTotalBefore += change.origValue;
            posTotalAfter += change.newValue;
        }
        cout << "\nTOTALS: " << setw(20) <<  left << posTotalBefore  << setw(10) << " " << posTotalAfter << endl << endl;
        outFile <<  "\nTOTALS: " << setw(20) <<  left << posTotalBefore  << setw(10) << " " << posTotalAfter << endl << endl;


        outFile << "\nUPDATED REVIEW (MORE POSITIVE):\n";
        cout << "\nUPDATED REVIEW (MORE POSITIVE):\n";
        lineLength = 0;
        for (const auto& w : posWords) {
            lineLength += w.word.length() + 1;
            if (lineLength > 80) {
                outFile << "\n";
                cout << "\n";
                lineLength = w.word.length() + 1;
            }
            outFile << w.word << " ";
            cout << w.word << " ";
        }
        outFile << "\nUPDATED SENTIMENT: " << newPosSentiment << "\n";
        cout << "\nUPDATED SENTIMENT: " << newPosSentiment << "\n";
    }
}