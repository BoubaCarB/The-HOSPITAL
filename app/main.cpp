/*#include <iostream>
#include <string>
using namespace std;

#include "../Hospital/Hospital.h"
#include "../Sentiment/SentimentMain.h"
*/
//  Different headers based on system

#include <iostream>
#include <string>
using namespace std;

// Pull in the implementation .cpp files directly 
#include "../Hospital/functions.cpp"
#include "../Hospital/CS201R-Pgm8Hospital.cpp"
#include "../Sentiment/Sentiment.cpp"
#include "../Sentiment/CS201PGM8SentimentTemplate.cpp"

int main() {
    while (true) {
        cout << "\n=== Integrated Hospital & Sentiment ===\n";
        cout << "1) Hospital Module\n";
        cout << "2) Sentiment Module\n";
        cout << "0) Exit\n";
        cout << "Select: ";

        string choice;
        if (!getline(cin, choice)) break;

        if (choice == "1") {
            runHospital();     // now defined because we included the hospital .cpp
        } else if (choice == "2") {
            runSentiment();    // now defined because we included the sentiment .cpp
        } else if (choice == "0") {
            break;
        } else {
            cout << "Invalid.\n";
        }
    }
    return 0;
}