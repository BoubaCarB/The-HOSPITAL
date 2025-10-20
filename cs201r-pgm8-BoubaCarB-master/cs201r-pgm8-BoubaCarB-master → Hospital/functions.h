
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>




using namespace std;

struct Patient {
    string firstName;  
    string lastName;   
    string ssn;        
    bool isCritical; 

    Patient(string f, string l, string s, bool c = false);  // Constructor
};

class Clinic {
private:
           
    string code;       
    vector<Patient> patients;  
    const int MAX_PATIENTS = 10;  
      

public:
    ofstream& transFile;
    string name;
    Clinic(string n, string c, ofstream& tf);  // constructor
    bool isFull() const;  //  if clinic is full
    bool isNumeric(const string& str) const;  //  if string is numeric
    void addPatient(string first, string last, string ssn);  // add regular patient
    void addCriticalPatient(string first, string last, string ssn);  // add critical patient
    void operatePatient();  // operate on first patient
    bool cancelPatient(string ssn);  // cancel patient by SSN
    void listPatients() const;  // list all patients
    void saveForTomorrow(ofstream& outFile) const;  // save for next day
};