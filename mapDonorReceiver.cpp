#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

const string DONOR_CSV_FILE_PATH = "donor.csv";
const string RECEIVER_CSV_FILE_PATH = "receiver.csv";
const string DETAILS_CSV_FILE_PATH = "details.csv";

// DonorDetails structure
struct DonorDetails {
    string DonorID;
    string DonorName;
    string OrganType;
    string DonorContact;
    string DonorAge;
    string DonorBloodType;
    string DonorCity;
    string DonorState;
    string DonorCountry;
    string DonorAddress;
    string DonorZipCode;
    string DonorMedicalHistory;
    string DonorInsurance;
    string DonorConsentForm;
    string DonorRegistrationDate;

    friend ostream& operator<<(ostream& os, const DonorDetails& donor) {
        os << setw(15) << donor.DonorID << setw(20) << donor.DonorName
           << setw(20) << donor.OrganType << setw(20) << donor.DonorContact
           << setw(15) << donor.DonorAge << setw(15) << donor.DonorBloodType
           << setw(20) << donor.DonorCity << setw(15) << donor.DonorState
           << setw(15) << donor.DonorCountry << setw(20) << donor.DonorAddress
           << setw(15) << donor.DonorZipCode << setw(20) << donor.DonorMedicalHistory
           << setw(20) << donor.DonorInsurance << setw(20) << donor.DonorConsentForm
           << setw(25) << donor.DonorRegistrationDate;
        return os;
    }
};

// ReceiverDetails structure
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

    friend ostream& operator<<(ostream& os, const ReceiverDetails& receiver) {
        os << setw(15) << receiver.ReceiverID << setw(20) << receiver.ReceiverName
           << setw(20) << receiver.ReceiverContact << setw(15) << receiver.OrganType
           << setw(15) << receiver.ReceiverAge << setw(20) << receiver.ReceiverBloodType
           << setw(20) << receiver.ReceiverAddress << setw(15) << receiver.ReceiverCity
           << setw(15) << receiver.ReceiverState << setw(15) << receiver.ReceiverCountry
           << setw(15) << receiver.ReceiverZipCode << setw(20) << receiver.ReceiverMedicalHistory
           << setw(20) << receiver.ReceiverInsurance << setw(20) << receiver.ReceiverConsentForm
           << setw(25) << receiver.ReceiverRegistrationDate;
        return os;
    }
};

// Binary Search Tree for Donors
class DonorBST {
private:
    struct Node {
        DonorDetails data;
        Node* left;
        Node* right;
        Node(const DonorDetails& donor) : data(donor), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Helper function to insert a donor into the BST
    Node* insert(Node* node, const DonorDetails& donor) {
        if (node == nullptr) {
            return new Node(donor);
        }

        if (donor.DonorID < node->data.DonorID) {
            node->left = insert(node->left, donor);
        } else if (donor.DonorID > node->data.DonorID) {
            node->right = insert(node->right, donor);
        }

        return node;
    }

    // Helper function to search for donors based on blood type and organ type
    void search(Node* node, const string& bloodType, const string& organType, vector<DonorDetails>& result) const {
        if (node == nullptr) {
            return;
        }

        if (node->data.DonorBloodType == bloodType && node->data.OrganType == organType) {
            result.push_back(node->data);
        }

        if (bloodType < node->data.DonorBloodType || (bloodType == node->data.DonorBloodType && organType < node->data.OrganType)) {
            search(node->left, bloodType, organType, result);
        }

        if (bloodType > node->data.DonorBloodType || (bloodType == node->data.DonorBloodType && organType > node->data.OrganType)) {
            search(node->right, bloodType, organType, result);
        }
    }

public:
    DonorBST() : root(nullptr) {}

    // Function to insert a donor into the BST
    void insert(const DonorDetails& donor) {
        root = insert(root, donor);
    }

    // Function to search for donors based on blood type and organ type
    vector<DonorDetails> search(const string& bloodType, const string& organType) const {
        vector<DonorDetails> result;
        search(root, bloodType, organType, result);
        return result;
    }
};

// Function to print a table of details excluding address-related columns
void printTable(const vector<DonorDetails>& donors, const vector<ReceiverDetails>& receivers) {
    cout << setw(6) << "DonorID" << setw(15) << "DonorName"
         << setw(15) << "OrganType" << setw(15) << "ContactNo"
         << setw(12) << "Age" << setw(15) << "BloodType"
         << setw(18) << "MedicalHist." << setw(15) << "Insurance"
         << setw(20) << "ConsentForm" << setw(25) << "RegistrationDate" << endl;

    for (const auto& donor : donors) {
        cout << setw(7) << donor.DonorID << setw(20) << donor.DonorName
             << setw(15) << donor.OrganType << setw(15) << donor.DonorContact
             << setw(7) << donor.DonorAge << setw(7) << donor.DonorBloodType
             << setw(18) << donor.DonorMedicalHistory << setw(15) << donor.DonorInsurance
             << setw(20) << donor.DonorConsentForm << setw(25) << donor.DonorRegistrationDate << endl;
    }

    cout << "\n\n";

    cout << setw(6) << "Rec. ID" << setw(15) << "Rec. Name"
         << setw(15) << "OrganType"<< setw(15) << "ContactNo" 
         << setw(12) << "Age" << setw(15) << "BloodType"
         << setw(18) << "MedicalHist." << setw(15) << "Insurance"
         << setw(20) << "ConsentForm" << setw(25) << "RegistrationDate" << endl;

    for (const auto& receiver : receivers) {
        cout << setw(6) << receiver.ReceiverID << setw(20) << receiver.ReceiverName
             << setw(15) << receiver.OrganType << setw(15) << receiver.ReceiverContact 
             << setw(7) << receiver.ReceiverAge << setw(7) << receiver.ReceiverBloodType
             << setw(18) << receiver.ReceiverMedicalHistory << setw(15) << receiver.ReceiverInsurance
             << setw(20) << receiver.ReceiverConsentForm << setw(25) << receiver.ReceiverRegistrationDate << endl;
    }
}


// Function to write mapping details to details.csv
void writeMappingToCSV(const DonorDetails& donor, const ReceiverDetails& receiver) {
    ofstream detailsfile(DETAILS_CSV_FILE_PATH, ios::app);
    if (!detailsfile.is_open()) {
        cerr << "Error: Could not open the details CSV file for writing." << endl;
        return;
    }


    // Append the donor and receiver details to the details CSV file
    detailsfile << donor.DonorID << ","
                << donor.DonorName << ","
                << donor.OrganType << ","
                << donor.DonorContact << ","
                << donor.DonorAge << ","
                << donor.DonorBloodType << ","
                << donor.DonorCity << ","
                << donor.DonorState << ","
                << donor.DonorCountry << ","
                << donor.DonorAddress << ","
                << donor.DonorZipCode << ","
                << donor.DonorMedicalHistory << ","
                << donor.DonorInsurance << ","
                << donor.DonorConsentForm << ","
                << donor.DonorRegistrationDate << ","
                << receiver.ReceiverID << ","
                << receiver.ReceiverName << ","
                << receiver.ReceiverContact << ","
                << receiver.OrganType << ","
                << receiver.ReceiverAge << ","
                << receiver.ReceiverBloodType << ","
                << receiver.ReceiverAddress << ","
                << receiver.ReceiverCity << ","
                << receiver.ReceiverState << ","
                << receiver.ReceiverCountry << ","
                << receiver.ReceiverZipCode << ","
                << receiver.ReceiverMedicalHistory << ","
                << receiver.ReceiverInsurance << ","
                << receiver.ReceiverConsentForm << ","
                << receiver.ReceiverRegistrationDate << "\n";

    cout << "Mapping successful. Details have been saved to " << DETAILS_CSV_FILE_PATH << endl;
}

// Function to remove a record from a CSV file based on the ID
void removeRecordFromCSV(const string& filePath, const string& recordID) {
    ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the CSV file for reading." << endl;
        return;
    }

    ofstream tempFile("temp.csv");
    if (!tempFile.is_open()) {
        cerr << "Error: Could not create a temporary file." << endl;
        return;
    }

    // Copy lines to temp file excluding the record with the given ID
    string line;
    while (getline(inputFile, line)) {
        istringstream ss(line);
        string currentID;
        getline(ss, currentID, ',');

        if (currentID != recordID) {
            tempFile << line << "\n";
        }
    }

    inputFile.close();
    tempFile.close();

    // Replace the original file with the temp file
    if (rename("temp.csv", filePath.c_str()) != 0) {
        cerr << "Error: Could not replace the original CSV file." << endl;
    }
}

// Function to search for and display matching donors based on blood type and organ type
void searchAndDisplayMatches(const DonorBST& donorTree, const vector<ReceiverDetails>& receivers, const string& bloodType, const string& organType) {
    // Search for matching donors
    vector<DonorDetails> matchingDonors = donorTree.search(bloodType, organType);

    // Print the table of matching details
    printTable(matchingDonors, receivers);

    if (!matchingDonors.empty()) {
        // Ask the user if they want to proceed with mapping
        cout << "Do you want to map a donor with a receiver? (yes/no): ";
        string mapChoice;
        cin >> mapChoice;

        if (mapChoice == "yes") {
            // Ask for the IDs of the donor and receiver to map
            cout << "Enter the DonorID: ";
            string donorID;
            cin >> donorID;

            cout << "Enter the ReceiverID: ";
            string receiverID;
            cin >> receiverID;

            // Find the donor and receiver details
            auto donorIt = find_if(matchingDonors.begin(), matchingDonors.end(), [&donorID](const DonorDetails& donor) {
                return donor.DonorID == donorID;
            });

            auto receiverIt = find_if(receivers.begin(), receivers.end(), [&receiverID](const ReceiverDetails& receiver) {
                return receiver.ReceiverID == receiverID;
            });

            if (donorIt != matchingDonors.end() && receiverIt != receivers.end()) {
                // Write mapping details to details.csv
                writeMappingToCSV(*donorIt, *receiverIt);

                // Remove donor from donor.csv
                removeRecordFromCSV(DONOR_CSV_FILE_PATH, donorID);

                // Remove receiver from receiver.csv
                removeRecordFromCSV(RECEIVER_CSV_FILE_PATH, receiverID);
            } else {
                cout << "Invalid DonorID or ReceiverID. Mapping failed." << endl;
            }
        } else {
            cout << "Mapping skipped. No changes made to CSV files." << endl;
        }
    } else {
        cout << "No matching donors found. Mapping skipped." << endl;
    }
}

int main() {
    DonorBST donorTree;

    // Read donor data and build the BST
    ifstream donorFile(DONOR_CSV_FILE_PATH);
    if (donorFile.is_open()) {
        string line;
        getline(donorFile, line); // Skip the header
        while (getline(donorFile, line)) {
            istringstream ss(line);
            DonorDetails donor;
            getline(ss, donor.DonorID, ',');
            getline(ss, donor.DonorName, ',');
            getline(ss, donor.OrganType, ',');
            getline(ss, donor.DonorContact, ',');
            getline(ss, donor.DonorAge, ',');
            getline(ss, donor.DonorBloodType, ',');
            getline(ss, donor.DonorCity, ',');
            getline(ss, donor.DonorState, ',');
            getline(ss, donor.DonorCountry, ',');
            getline(ss, donor.DonorAddress, ',');
            getline(ss, donor.DonorZipCode, ',');
            getline(ss, donor.DonorMedicalHistory, ',');
            getline(ss, donor.DonorInsurance, ',');
            getline(ss, donor.DonorConsentForm, ',');
            getline(ss, donor.DonorRegistrationDate, ',');
            donorTree.insert(donor);
        }
        donorFile.close();
    } else {
        cerr << "Error: Unable to open donor CSV file." << endl;
        return 1;
    }

    // Read receiver data
    vector<ReceiverDetails> receivers;
    ifstream receiverFile(RECEIVER_CSV_FILE_PATH);
    if (receiverFile.is_open()) {
        string line;
        getline(receiverFile, line); // Skip the header
        while (getline(receiverFile, line)) {
            istringstream ss(line);
            ReceiverDetails receiver;
            getline(ss, receiver.ReceiverID, ',');
            getline(ss, receiver.ReceiverName, ',');
            getline(ss, receiver.ReceiverContact, ',');
            getline(ss, receiver.OrganType, ',');
            getline(ss, receiver.ReceiverAge, ',');
            getline(ss, receiver.ReceiverBloodType, ',');
            getline(ss, receiver.ReceiverAddress, ',');
            getline(ss, receiver.ReceiverCity, ',');
            getline(ss, receiver.ReceiverState, ',');
            getline(ss, receiver.ReceiverCountry, ',');
            getline(ss, receiver.ReceiverZipCode, ',');
            getline(ss, receiver.ReceiverMedicalHistory, ',');
            getline(ss, receiver.ReceiverInsurance, ',');
            getline(ss, receiver.ReceiverConsentForm, ',');
            getline(ss, receiver.ReceiverRegistrationDate, ',');
            receivers.push_back(receiver);
        }
        receiverFile.close();
    } else {
        cerr << "Error: Unable to open receiver CSV file." << endl;
        return 1;
    }

    // Print the table of details
    printTable({}, {});

    // Ask the user if they want to map and search for matches
    cout << "Do you want to map a donor with a receiver? (yes/no): ";
    string mapChoice;
    cin >> mapChoice;

    if (mapChoice == "yes") {
        // Ask for blood type and organ type
        cout << "Enter the blood type: ";
        string bloodType;
        cin >> bloodType;

        cout << "Enter the organ type: ";
        string organType;
        cin >> organType;

        // Search for matching donors and display results
        searchAndDisplayMatches(donorTree, receivers, bloodType, organType);
    } else {
        cout << "Mapping skipped. No changes made to CSV files." << endl;
    }

    return 0;
}

