#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <windows.h>
using namespace std;

// Structure to represent a receiver
struct Receiver {
    string ID;
    string Name;
    string Contact;
    string OrganType;
    string Age;
    string BloodType;
    string Address;
    string City;
    string State;
    string Country;
    string ZipCode;
    string MedicalHistory;
    string Insurance;
    string ConsentForm;
    string RegistrationDate;
    Receiver* next;
};

// Helper function to normalize strings for comparison
string normalizeString(const string& input) {
    string result = input;
    // Convert to lowercase
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    // Remove spaces
    result.erase(remove_if(result.begin(), result.end(), ::isspace), result.end());
    return result;
}

// Create a new receiver node and add it to the end of the linked list
Receiver* createReceiver(Receiver* head, const string& id, const string& name, const string& contact, const string& organType, const string& age, const string& bloodType, const string& address, const string& city, const string& state, const string& country, const string& zipCode, const string& medicalHistory, const string& insurance, const string& consentForm, const string& registrationDate) {
    Receiver* newNode = new Receiver;
    newNode->ID = id;
    newNode->Name = name;
    newNode->Contact = contact;
    newNode->OrganType = organType;
    newNode->Age = age;
    newNode->BloodType = bloodType;
    newNode->Address = address;
    newNode->City = city;
    newNode->State = state;
    newNode->Country = country;
    newNode->ZipCode = zipCode;
    newNode->MedicalHistory = medicalHistory;
    newNode->Insurance = insurance;
    newNode->ConsentForm = consentForm;
    newNode->RegistrationDate = registrationDate;
    newNode->next = nullptr;

    if (head == nullptr) {
        return newNode;
    }

    Receiver* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = newNode;
    return head;
}

// Search for matching receivers and print the results
void searchAndPrintMatches(Receiver* head, const string& organType, const string& bloodType, const string& city) {
    if (head == nullptr) {
        cout << "No matching receivers found." << endl;
        return;
    }

    string normalizedOrganType = normalizeString(organType);
    string normalizedBloodType = normalizeString(bloodType);
    string normalizedCity = normalizeString(city);

    Receiver* current = head;
    bool matchFound = false;

    while (current != nullptr) {
        string receiverOrganType = normalizeString(current->OrganType);
        string receiverBloodType = normalizeString(current->BloodType);
        string receiverCity = normalizeString(current->City);

        if (receiverOrganType.find(normalizedOrganType) != string::npos &&
            receiverBloodType.find(normalizedBloodType) != string::npos &&
            receiverCity.find(normalizedCity) != string::npos) {
                // system("header.exe");
            cout << "Receiver ID: " << current->ID << endl;
            cout << "Name: " << current->Name << endl;
            cout << "Organ Type: " << current->OrganType << endl;
            cout << "Blood Type: " << current->BloodType << endl;
            cout << "City: " << current->City << endl;
            cout << "Contact: " << current->Contact << endl;
            cout << "Age: " << current->Age << endl;
            cout << "Address: " << current->Address << endl;
            cout << "State: " << current->State << endl;
            cout << "Country: " << current->Country << endl;
            cout << "Zip Code: " << current->ZipCode << endl;
            cout << "Medical History: " << current->MedicalHistory << endl;
            cout << "Insurance: " << current->Insurance << endl;
            cout << "Consent Form: " << current->ConsentForm << endl;
            cout << "Registration Date: " << current->RegistrationDate << endl;
            cout << "--------------------------------" << endl;
            matchFound = true;
            cout << "press enter to continue...";
            cin.get();
        }

        current = current->next;
    }

    if (!matchFound) {
        cout << "No matching receivers found." << endl;
        cout << "press enter to continue...";
        cin.get();
    }
}

int main() {
    system("color 3f");
    Receiver* receiverList = nullptr;

    // Load data from receiver.csv file
    ifstream receiverFile("receiver.csv");

    if (!receiverFile.is_open()) {
        cout << "Error: Unable to open CSV file." << endl;
        return 1;
    }

    string line;
    // Read and discard the header line
    getline(receiverFile, line);

    while (getline(receiverFile, line)) {
        istringstream iss(line);
        string id, name, contact, organType, age, bloodType, address, city, state, country, zipCode, medicalHistory, insurance, consentForm, registrationDate;

        getline(iss, id, ',');
        getline(iss, name, ',');
        getline(iss, contact, ',');
        getline(iss, organType, ',');
        getline(iss, age, ',');
        getline(iss, bloodType, ',');
        getline(iss, address, ',');
        getline(iss, city, ',');
        getline(iss, state, ',');
        getline(iss, country, ',');
        getline(iss, zipCode, ',');
        getline(iss, medicalHistory, ',');
        getline(iss, insurance, ',');
        getline(iss, consentForm, ',');
        getline(iss, registrationDate, ',');

        receiverList = createReceiver(receiverList, id, name, contact, organType, age, bloodType, address, city, state, country, zipCode, medicalHistory, insurance, consentForm, registrationDate);
    }

    while (true) {
        system("cls");
        system("header.exe");
        cout << "Choose an option:" << endl;
        cout << "1. Search Receivers" << endl;
        cout << "2. Exit" << endl;

        string choice;
        cin >> choice;

        if (choice == "1") {
            system("cls");
            system("header.exe");
            string organType, bloodType, city;
            cout << "Enter the organ type (e.g., heart, kidney, etc.): ";
            cin >> organType;
            cout << "Enter the blood type: ";
            cin >> bloodType;
            cout << "Enter the city: ";
            cin >> city;

            cout << "Matching Receivers:" << endl;
            searchAndPrintMatches(receiverList, organType, bloodType, city);
            cout << "press enter to continue...";
            cin.get();
        } else if (choice == "2") {
            system("welcome.exe");
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    // Clean up: free memory
    Receiver* current = receiverList;
    while (current != nullptr) {
        Receiver* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}
