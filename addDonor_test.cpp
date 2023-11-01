#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h> // For sleep on Unix-based systems
#endif

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

vector<ReceiverDetails> receiverDatabase;

string generate_receiver_id(const ReceiverDetails& receiver) {
    string first_letter = receiver.ReceiverName.substr(0, 1);
    string last_letter = receiver.ReceiverName.substr(receiver.ReceiverName.length() - 1, 1);
    string contact_digits = receiver.ReceiverContact.substr(receiver.ReceiverContact.length() - 2, 2);
    string organ_blood_type = receiver.OrganType.substr(0, 1) + receiver.ReceiverBloodType.substr(0, 1);

    string receiver_id = first_letter + last_letter + contact_digits + organ_blood_type;

    for (char &c : receiver_id) {
        c = tolower(c);  // Convert to lowercase
    }

    return receiver_id;
}

#ifdef _WIN32
void setColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor | (bgColor << 4));
}
#else
void setColor(int textColor, int bgColor) {
    cout << "\033[0;" << textColor << ";" << bgColor << "m";
}
#endif

void clearScreen() {
    cout << "\033[2J\033[1;1H"; // Clear the screen
    setColor(30, 42); // Set text color to grey and background color to lime green
}

void write_to_csv(const ReceiverDetails& receiver) {
    ofstream csvfile(CSV_FILE_PATH, ios::app);
    if (!csvfile.is_open()) {
        cerr << "Error: Could not open the CSV file for writing." << endl;
        return;
    }

    ReceiverDetails updatedReceiver = receiver;
    updatedReceiver.ReceiverID = generate_receiver_id(updatedReceiver);

    for (const auto& entry : receiverDatabase) {
        if (entry.ReceiverID == updatedReceiver.ReceiverID) {
            cout << "Your request is under process. A receiver with the same ReceiverID already exists." << endl;
            return;
        }
    }

    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream registration_date;
    registration_date << setw(2) << setfill('0') << ltm->tm_mday << '/'
                     << setw(2) << setfill('0') << 1 + ltm->tm_mon << '/'
                     << 1900 + ltm->tm_year;

    updatedReceiver.ReceiverRegistrationDate = registration_date.str();

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

    receiverDatabase.push_back(updatedReceiver);

    clearScreen(); // Clear the screen and set colors again
    cout << "Registration successful. Details have been saved to " << CSV_FILE_PATH << endl;
}

void display_menu() {
    clearScreen();
    cout << "Organ Receiver Registration Menu" << endl;
    cout << "1. Register as an organ receiver" << endl;
    cout << "2. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    ReceiverDetails receiver;

    cout << "Welcome to Organ Receiver Registration" << endl;

    while (true) {
        display_menu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
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

                write_to_csv(receiver);
                break;

            case 2:
                clearScreen();
                cout << "Goodbye!" << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << "Press Enter to continue...";
        cin.get(); // Wait for Enter key
    }

    return 0;
}
