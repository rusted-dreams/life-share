#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

// Structure to represent a donor
struct Donor {
    string ID;
    string Name;
    string OrganType;
    string Contact;
    string Age;
    string BloodType;
    string City;
    string State;
    string Country;
    string Address;
    string ZipCode;
    string MedicalHistory;
    string Insurance;
    string ConsentForm;
    string RegistrationDate;
    Donor* next;
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

// Create a new donor node and add it to the end of the linked list
Donor* createDonor(Donor* head, const string& id, const string& name, const string& organType, const string& contact, const string& age, const string& bloodType, const string& city, const string& state, const string& country, const string& address, const string& zipCode, const string& medicalHistory, const string& insurance, const string& consentForm, const string& registrationDate) {
    Donor* newNode = new Donor;
    newNode->ID = id;
    newNode->Name = name;
    newNode->OrganType = organType;
    newNode->Contact = contact;
    newNode->Age = age;
    newNode->BloodType = bloodType;
    newNode->City = city;
    newNode->State = state;
    newNode->Country = country;
    newNode->Address = address;
    newNode->ZipCode = zipCode;
    newNode->MedicalHistory = medicalHistory;
    newNode->Insurance = insurance;
    newNode->ConsentForm = consentForm;
    newNode->RegistrationDate = registrationDate;
    newNode->next = nullptr;

    if (head == nullptr) {
        return newNode;
    }

    Donor* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = newNode;
    return head;
}

// Search for matching donors and print the results
void searchAndPrintMatches(Donor* head, const string& organType, const string& bloodType, const string& city) {
    if (head == nullptr) {
        cout << "No matching donors found." << endl;
        return;
    }

    string normalizedOrganType = normalizeString(organType);
    string normalizedBloodType = normalizeString(bloodType);
    string normalizedCity = normalizeString(city);

    Donor* current = head;
    bool matchFound = false;

    while (current != nullptr) {
        string donorOrganType = normalizeString(current->OrganType);
        string donorBloodType = normalizeString(current->BloodType);
        string donorCity = normalizeString(current->City);

        if (donorOrganType.find(normalizedOrganType) != string::npos &&
            donorBloodType.find(normalizedBloodType) != string::npos &&
            donorCity.find(normalizedCity) != string::npos) {
            cout << "Donor ID: " << current->ID << endl;
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
        }

        current = current->next;
    }

    if (!matchFound) {
        cout << "No matching donors found." << endl;
    }
}

int main() {
    Donor* donorList = nullptr;

    // Load data from donor.csv file
    ifstream donorFile("donor.csv");

    if (!donorFile.is_open()) {
        cout << "Error: Unable to open CSV file." << endl;
        return 1;
    }

    string line;
    // Read and discard the header line
    getline(donorFile, line);

    while (getline(donorFile, line)) {
        istringstream iss(line);
        string id, name, organType, contact, age, bloodType, city, state, country, address, zipCode, medicalHistory, insurance, consentForm, registrationDate;

        getline(iss, id, ',');
        getline(iss, name, ',');
        getline(iss, organType, ',');
        getline(iss, contact, ',');
        getline(iss, age, ',');
        getline(iss, bloodType, ',');
        getline(iss, city, ',');
        getline(iss, state, ',');
        getline(iss, country, ',');
        getline(iss, address, ',');
        getline(iss, zipCode, ',');
        getline(iss, medicalHistory, ',');
        getline(iss, insurance, ',');
        getline(iss, consentForm, ',');
        getline(iss, registrationDate, ',');

        donorList = createDonor(donorList, id, name, organType, contact, age, bloodType, city, state, country, address, zipCode, medicalHistory, insurance, consentForm, registrationDate);
    }

    while (true) {
        cout << "Choose an option:" << endl;
        cout << "1. Search Donors" << endl;
        cout << "2. Exit" << endl;

        string choice;
        cin >> choice;

        if (choice == "1") {
            string organType, bloodType, city;
            cout << "Enter the organ type (e.g., heart, kidney, etc.): ";
            cin >> organType;
            cout << "Enter the blood type: ";
            cin >> bloodType;
            cout << "Enter the city: ";
            cin >> city;

            cout << "Matching Donors:" << endl;
            searchAndPrintMatches(donorList, organType, bloodType, city);
        } else if (choice == "2") {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    // Clean up: free memory
    Donor* current = donorList;
    while (current != nullptr) {
        Donor* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}
