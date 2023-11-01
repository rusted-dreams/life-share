#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>   // For time functions
#include <iomanip> // For date/time formatting
#include <vector>

using namespace std;

const string CSV_FILE_PATH = "receiver.csv";

struct ReceiverDetails {
    string ReceiverID;
    string ReceiverName;
    string ReceiverContact;
    string OrganType;
    string ReceiverAge;
    string ReceiverBloodType;
    string ReceiverAddress;
    string ReceiverCity;
    string ReceiverState;
    string ReceiverCountry;
    string ReceiverZipCode;
    string ReceiverMedicalHistory;
    string ReceiverInsurance;
    string ReceiverConsentForm;
    string ReceiverRegistrationDate;
};

vector<ReceiverDetails> receiverDatabase;  // Vector to store receiver details

string generate_receiver_id(const ReceiverDetails& receiver) {
    // Extract relevant components for ReceiverID
    string first_letter = receiver.ReceiverName.substr(0, 1);
    string last_letter = receiver.ReceiverName.substr(receiver.ReceiverName.length() - 1, 1);
    string contact_digits = receiver.ReceiverContact.substr(receiver.ReceiverContact.length() - 2, 2);
    string organ_blood_type = receiver.OrganType.substr(0, 1) + receiver.ReceiverBloodType.substr(0, 1);

    // Combine components to form ReceiverID
    string receiver_id = first_letter + last_letter + contact_digits + organ_blood_type;

    // Convert to uppercase
    for (char &c : receiver_id) {
        c = toupper(c);
    }

    return receiver_id;
}

void write_to_csv(const ReceiverDetails& receiver) {
    ofstream csvfile(CSV_FILE_PATH, ios::app);
    if (!csvfile.is_open()) {
        cerr << "Error: Could not open the CSV file for writing." << endl;
        return;
    }



    // Generate ReceiverID
    ReceiverDetails updatedReceiver = receiver;
    updatedReceiver.ReceiverID = generate_receiver_id(updatedReceiver);

    // Check if ReceiverID already exists
    for (const auto& entry : receiverDatabase) {
        if (entry.ReceiverID == updatedReceiver.ReceiverID) {
            cout << "Your request is under process. A receiver with the same ReceiverID already exists." << endl;
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

    updatedReceiver.ReceiverRegistrationDate = registration_date.str();

    // Append the updated receiver details to the CSV file
    csvfile << updatedReceiver.ReceiverID << ","
            << updatedReceiver.ReceiverName << ","
            << updatedReceiver.ReceiverContact << ","
            << updatedReceiver.OrganType << ","
            << updatedReceiver.ReceiverAge << ","
            << updatedReceiver.ReceiverBloodType << ","
            << updatedReceiver.ReceiverAddress << ","
            << updatedReceiver.ReceiverCity << ","
            << updatedReceiver.ReceiverState << ","
            << updatedReceiver.ReceiverCountry << ","
            << updatedReceiver.ReceiverZipCode << ","
            << updatedReceiver.ReceiverMedicalHistory << ","
            << updatedReceiver.ReceiverInsurance << ","
            << updatedReceiver.ReceiverConsentForm << ","
            << updatedReceiver.ReceiverRegistrationDate << "\n";

    // Add the updated receiver details to the in-memory database
    receiverDatabase.push_back(updatedReceiver);

    cout << "Registration successful. Details have been saved to " << CSV_FILE_PATH << endl;
}

int main() {
    ReceiverDetails receiver;

    cout << "Welcome to Organ Receiver Registration" << endl;

    cout << "Register as an organ receiver? (yes/no): ";
    string response;
    cin >> response;

    if (response == "yes") {
        cout << "Enter Receiver Name: ";
        cin.ignore();
        getline(cin, receiver.ReceiverName);

        cout << "Enter Receiver Contact: ";
        getline(cin, receiver.ReceiverContact);

        cout << "Enter Organ Type: ";
        getline(cin, receiver.OrganType);

        cout << "Enter Receiver Age: ";
        getline(cin, receiver.ReceiverAge);

        cout << "Enter Receiver Blood Type: ";
        getline(cin, receiver.ReceiverBloodType);

        cout << "Enter Receiver Address: ";
        getline(cin, receiver.ReceiverAddress);

        cout << "Enter Receiver City: ";
        getline(cin, receiver.ReceiverCity);

        cout << "Enter Receiver State: ";
        getline(cin, receiver.ReceiverState);

        cout << "Enter Receiver Country: ";
        getline(cin, receiver.ReceiverCountry);

        cout << "Enter Receiver Zip Code: ";
        getline(cin, receiver.ReceiverZipCode);

        cout << "Enter Receiver Medical History: ";
        getline(cin, receiver.ReceiverMedicalHistory);

        cout << "Enter Receiver Insurance: ";
        getline(cin, receiver.ReceiverInsurance);

        cout << "Enter Receiver Consent Form: ";
        getline(cin, receiver.ReceiverConsentForm);

        // Write receiver details to CSV file and update in-memory database
        write_to_csv(receiver);
    } else {
        cout << "Registration cancelled. Goodbye!" << endl;
    }

    // Access in-memory database (vector) if needed
    for (const auto& entry : receiverDatabase) {
        // Do something with each entry in the in-memory database
        cout << "ReceiverID: " << entry.ReceiverID << ", ReceiverName: " << entry.ReceiverName << endl;
    }

    return 0;
}
