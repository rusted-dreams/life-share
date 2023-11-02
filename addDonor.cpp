#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>   // For time functions
#include <iomanip> // For date/time formatting
#include <vector>
#include <windows.h>

using namespace std;

const string DONOR_CSV_FILE_PATH = "donor.csv";

struct DonorDetails
{
    string DonorID;
    string DonorName;
    string OrganType;
    string DonorContact;
    string DonorAge;
    string DonorBloodType;
    string DonorRegistrationDate;
    string DonorCity;
    string DonorState;
    string DonorCountry;
    string DonorAddress;
    string DonorZipCode;
    string DonorMedicalHistory;
    string DonorInsurance;
    string DonorConsentForm;
};

vector<DonorDetails> donorDatabase; // Vector to store donor details

string generate_donor_id(const DonorDetails &donor)
{
    // Extract relevant components for DonorID
    string first_letter = donor.DonorName.substr(0, 1);
    string last_letter = donor.DonorName.substr(donor.DonorName.length() - 1, 1);
    string contact_digits = donor.DonorContact.substr(donor.DonorContact.length() - 2, 2);
    string organ_blood_type = donor.OrganType.substr(0, 1) + donor.DonorBloodType.substr(0, 1);

    // Combine components to form DonorID
    string donor_id = first_letter + last_letter + contact_digits + organ_blood_type;

    // Convert to uppercase
    for (char &c : donor_id)
    {
        c = toupper(c);
    }

    return donor_id;
}

void write_donor_to_csv(const DonorDetails &donor)
{
    ofstream csvfile(DONOR_CSV_FILE_PATH, ios::app);
    if (!csvfile.is_open())
    {
        cerr << "Error: Could not open the Donor CSV file for writing." << endl;
        return;
    }

    // Generate DonorID
    DonorDetails updatedDonor = donor;
    updatedDonor.DonorID = generate_donor_id(updatedDonor);

    // Check if DonorID already exists
    for (const auto &entry : donorDatabase)
    {
        if (entry.DonorID == updatedDonor.DonorID)
        {
            cout << "Your donor request is under process. A donor with the same DonorID already exists." << endl;
            return;
        }
    }

    // Get current date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream registration_date;
    registration_date << setw(2) << setfill('0') << ltm->tm_mday << '/'
                      << setw(2) << setfill('0') << 1 + ltm->tm_mon << '/'
                      << 1900 + ltm->tm_year;

    updatedDonor.DonorRegistrationDate = registration_date.str();

    // Append the updated donor details to the CSV file
    csvfile << updatedDonor.DonorID << ","
            << updatedDonor.DonorName << ","
            << updatedDonor.OrganType << ","
            << updatedDonor.DonorContact << ","
            << updatedDonor.DonorAge << ","
            << updatedDonor.DonorBloodType << ","
            << updatedDonor.DonorCity << ","
            << updatedDonor.DonorState << ","
            << updatedDonor.DonorCountry << ","
            << updatedDonor.DonorAddress << ","
            << updatedDonor.DonorZipCode << ","
            << updatedDonor.DonorMedicalHistory << ","
            << updatedDonor.DonorInsurance << ","
            << updatedDonor.DonorConsentForm << ","
            << updatedDonor.DonorRegistrationDate << "\n";

    // Add the updated donor details to the in-memory database
    donorDatabase.push_back(updatedDonor);

    cout << "Donor registration successful. Details have been saved to " << DONOR_CSV_FILE_PATH << endl;
}

int main()
{

    system("chcp 65001");
    system("cls");
    while (true)
    {
    start:
        DonorDetails donor;
        system("cls");
        system("color 4f");
        system("header.exe");
        cout << "Welcome to Organ Donor Registration" << endl;
        cout << "1: Register as an organ donor" << endl;
        cout << "2: Main Menu" << endl;
        int response;
        cout << endl << "What do you want to do?: ";
        cin >> response;

        switch (response)
        {
        case 1:
            system("cls");
            system("header.exe");
            cout << "Enter Donor Name: ";
            cin.ignore();
            getline(cin, donor.DonorName);

            cout << "Enter Organ Type: ";
            getline(cin, donor.OrganType);

            cout << "Enter Donor Contact: ";
            getline(cin, donor.DonorContact);

            cout << "Enter Donor Age: ";
            getline(cin, donor.DonorAge);

            cout << "Enter Donor Blood Type: ";
            getline(cin, donor.DonorBloodType);

            cout << "Enter Donor City: ";
            getline(cin, donor.DonorCity);

            cout << "Enter Donor State: ";
            getline(cin, donor.DonorState);

            cout << "Enter Donor Country: ";
            getline(cin, donor.DonorCountry);

            cout << "Enter Donor Address: ";
            getline(cin, donor.DonorAddress);

            cout << "Enter Donor Zip Code: ";
            getline(cin, donor.DonorZipCode);

            cout << "Enter Donor Medical History: ";
            getline(cin, donor.DonorMedicalHistory);

            cout << "Enter Donor Insurance: ";
            getline(cin, donor.DonorInsurance);

            cout << "Enter Donor Consent Form: ";
            getline(cin, donor.DonorConsentForm);

            // Write donor details to CSV file and update in-memory database
            write_donor_to_csv(donor);
            cout << "donor registered succesfully!";
            Sleep(2000);
            system("cls");
            goto start;
        case 2:
            cout << "Donor registration cancelled. Goodbye!" << endl;
            system("welcome.exe");
        }

        // Access in-memory database (vector) if needed
        for (const auto &entry : donorDatabase)
        {
            // Do something with each entry in the in-memory database
            cout << "DonorID: " << entry.DonorID << ", DonorName: " << entry.DonorName << endl;
        }
    }

    return 0;
}
