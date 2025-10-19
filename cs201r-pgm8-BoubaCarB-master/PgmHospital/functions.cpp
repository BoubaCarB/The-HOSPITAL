#include "functions.h"

// constructor for Patient
Patient::Patient(string f, string l, string s, bool c)
    : firstName(f), lastName(l), ssn(s), isCritical(c) {}

// constructor for Clinic
Clinic::Clinic(string n, string c, ofstream& tf)
    : name(n), code(c), transFile(tf) {}

// if clinic is full
bool Clinic::isFull() const {
    return patients.size() >= MAX_PATIENTS;
}

//  if string is numeric
bool Clinic::isNumeric(const string& str) const {
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return !str.empty();
}

// add regular patient
void Clinic::addPatient(string first, string last, string ssn) {
    if (isFull()) {
        transFile << "ERROR: " << name << " is full.\n";
        cout << "Clinic is full, cannot add " << first << " " << last << ".\n";
        return;
    }
    if (!isNumeric(ssn)) {
        transFile << "ERROR: Invalid SSN for " << first << " " << last << ".\n";
        cout << "Invalid SSN, use numbers only.\n";
        return;
    }
    patients.push_back(Patient(first, last, ssn, false));
    string status = "(Regular)";
    cout << name << " Patient " << status << ": " << first << " " << last << " was added to the waiting room.\n";
    transFile << name << " Patient " << status << ": " << first << " " << last << " was added.\n";
}

// add critical patient
void Clinic::addCriticalPatient(string first, string last, string ssn) {
    if (isFull()) {
        transFile << "ERROR: " << name << " is full.\n";
        cout << "Clinic is full, cannot add " << first << " " << last << ".\n";
        return;
    }
    if (!isNumeric(ssn)) {
        transFile << "ERROR: Invalid SSN for " << first << " " << last << ".\n";
        cout << "Invalid SSN, use numbers only.\n";
        return;
    }
    // find the position to insert: after the last critical patient
    size_t pos = 0;
    for (size_t i = 0; i < patients.size(); i++) {
        if (patients[i].isCritical) {
            pos = i + 1;  // inser after this critical patient
        } else {
            break;  //  at the first non critical patient
        }
    }
    patients.insert(patients.begin() + pos, Patient(first, last, ssn, true));
    string status = "(Critical)";
    cout << name << " Patient " << status << ": " << first << " " << last << " was added to the waiting room.\n";
    transFile << name << " Patient " << status << ": " << first << " " << last << " was added.\n";
}

// operate on first patient
void Clinic::operatePatient() {
    if (patients.empty()) {
        transFile << "ERROR: No patients in " << name << ".\n";
        cout << "No more patients to operate on.\n";
        return;
    }
    Patient p = patients[0];
    patients.erase(patients.begin());
    string status = p.isCritical ? "(Critical)" : "(Regular)";
    cout << name << " Patient " << status << ": " << p.firstName << " " << p.lastName << " was taken to the operating room.\n";
    transFile << name << " Patient " << status << ": " << p.firstName << " " << p.lastName << " was taken to the operating room.\n";
}

// cancel patient by SSN

bool Clinic::cancelPatient(string ssn) {
    for (size_t i = 0; i < patients.size(); i++) {
        if (patients[i].ssn == ssn) {
            Patient p = patients[i];
            patients.erase(patients.begin() + i);
            string status = p.isCritical ? "(Critical)" : "(Regular)";
            cout << name << " Patient " << status << ": " << p.firstName << " " << p.lastName << " was removed from the waiting list.\n";
            transFile << name << " Patient " << status << ": " << p.firstName << " " << p.lastName << " was removed.\n";
            return true;
        }
    }
    cout << "ERROR " << name << ": Patient with SSN: " << ssn << " was already removed or does not exist in the waiting room.\n";
    transFile << "ERROR " << name << ": Patient with SSN: " << ssn << " was already removed or does not exist in the waiting room.\n";
    return false;
}


// list all patients

void Clinic::listPatients() const {
    cout << "Patient List for " << name << ":\n";
    for (size_t i = 0; i < patients.size(); i++) {
        string status = patients[i].isCritical ? "C" : "R";
        cout << patients[i].firstName << "\t" << patients[i].lastName << "\t" 
             << patients[i].ssn << "\t" << status << "\n";
    }
    if (patients.empty()) {
        cout << "No patients in " << name << ".\n";
    }
}

// Save for next day
void Clinic::saveForTomorrow(ofstream& outFile) const {
    for (const auto& p : patients) {
        outFile << code << "," << p.firstName << "," << p.lastName << "," << p.ssn << "\n";
        transFile << name << " Patient: " << p.firstName << " " << p.lastName << " scheduled for tomorrow.\n";
    }
}