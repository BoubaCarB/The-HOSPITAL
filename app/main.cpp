#include <iostream>
#include <string>
using namespace std;

#include "../Hospital/Hospital.h"
#include "../Sentiment/SentimentMain.h"

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
            runHospital();
        } else if (choice == "2") {
            runSentiment();
        } else if (choice == "0") {
            break;
        } else {
            cout << "Invalid.\n";
        }
    }
    return 0;
}