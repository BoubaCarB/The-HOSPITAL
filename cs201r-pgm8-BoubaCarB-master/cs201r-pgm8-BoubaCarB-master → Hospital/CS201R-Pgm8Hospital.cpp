// CS201R-Pgm8Hospital.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Boubacar Balde

#include "functions.cpp"


int main() {
    ofstream transFile("transaction.log"); 
    if (!transFile.is_open()) {
        cout << "Cannot open transaction file.\n";
        return 1;
    }

    Clinic heartClinic("Heart Clinic", "HC", transFile); 
    Clinic pulmonaryClinic("Pulmonary Clinic", "PC", transFile);
    Clinic plasticClinic("Plastic Surgery Clinic", "PSC", transFile);

    ifstream inFile("patient.csv");  // read from patient.csv
    if (!inFile.is_open()) {
        cout << "Cannot open patient.csv\n";
        return 1;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string code, first, last, ssn;
        getline(ss, code, ',');
        getline(ss, first, ',');
        getline(ss, last, ',');
        getline(ss, ssn, ',');
        if (code == "HC") heartClinic.addPatient(first, last, ssn);
        else if (code == "PC") pulmonaryClinic.addPatient(first, last, ssn);
        else if (code == "PSC") plasticClinic.addPatient(first, last, ssn);
    }
    inFile.close();

    Clinic* currentClinic = &heartClinic;  
    bool running = true;

    while (running) {
        cout << "\nKC RESEARCH HOSPITAL\n";
        cout << "1 - Heart Clinic\n";
        cout << "2 - Pulmonary Clinic\n";
        cout << "3 - Plastic Surgery Clinic\n";
        cout << "4 - Quit\n";
        cout << "Please enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 4) {
            running = false;  // Quit 
            break;
        }
        if (choice == 1) currentClinic = &heartClinic;
        else if (choice == 2) currentClinic = &pulmonaryClinic;
        else if (choice == 3) currentClinic = &plasticClinic;
        else {
            cout << "Please enter a valid choice\n";  // invalid clinic choice
            continue;
        }

        
        bool inClinic = true;
        while (inClinic) {
            cout << "\n" << currentClinic->name << " Menu\n";
            cout << "1 - Add Patient\n";
            cout << "2 - Add Critical Patient\n";
            cout << "3 - Operate on Patient\n";
            cout << "4 - Cancel Patient\n";
            cout << "5 - List Patients\n";
            cout << "6 - Change Clinic\n";
            cout << "Please enter your choice: ";
            int option;
            cin >> option;
            cin.ignore(); 

            if (option == 6) {
                inClinic = false;  //  to main menu
                continue;
            }

            if (currentClinic->isFull() && (option == 1 || option == 2)) {
                cout << "ERROR: " << currentClinic->name << " is full.\n";  //error if full
                currentClinic->transFile << "ERROR: " << currentClinic->name << " is full.\n";
                continue;
            }

            if (option == 1) {
                string first, last, ssn;
                cout << "Enter Patient's First Name: ";
                getline(cin, first);
                cout << "Enter Patient's Last Name: ";
                getline(cin, last);
                cout << "Enter Patient's SSN: ";
                getline(cin, ssn);
                currentClinic->addPatient(first, last, ssn);
            }
            else if (option == 2) {
                string first, last, ssn;
                cout << "Enter Patient's First Name: ";
                getline(cin, first);
                cout << "Enter Patient's Last Name: ";
                getline(cin, last);
                cout << "Enter Patient's SSN: ";
                getline(cin, ssn);
                currentClinic->addCriticalPatient(first, last, ssn);
            }
            else if (option == 3) {
                currentClinic->operatePatient();
            }
            else if (option == 4) {
                string ssn;
                cout << "Enter SSN: ";
                getline(cin, ssn);
                currentClinic->cancelPatient(ssn);
            }
            else if (option == 5) {
                currentClinic->listPatients();
            }
            else {
                cout << "Please enter a valid choice\n";  // Invalid option
            }
        }
    }

    transFile << "\nHeart Clinic Report:\n";  // Save  reports
    heartClinic.saveForTomorrow(transFile);
    transFile << "\nPulmonary Clinic Report:\n";
    pulmonaryClinic.saveForTomorrow(transFile);
    transFile << "\nPlastic Surgery Clinic Report:\n";
    plasticClinic.saveForTomorrow(transFile);

    ofstream outFile("patient_next_day.csv");  // Save to new CSV
    heartClinic.saveForTomorrow(outFile);
    pulmonaryClinic.saveForTomorrow(outFile);
    plasticClinic.saveForTomorrow(outFile);
    outFile.close();

    transFile.close();  // Close files
    cout << "Program ended. Check transaction.log and patient_next_day.csv.\n";
    return 0;
}