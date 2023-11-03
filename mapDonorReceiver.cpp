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

    search(node->left, bloodType, organType, result);
    

    if (node->data.DonorBloodType == bloodType && node->data.OrganType == organType) {
        result.push_back(node->data);
    }

    search(node->right, bloodType, organType, result);
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
class ReceiverBST {
private:
    struct Node {
        ReceiverDetails data;
        Node* left;
        Node* right;
        Node(const ReceiverDetails& receiver) : data(receiver), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Helper function to insert a receiver into the BST
    Node* insert(Node* node, const ReceiverDetails& receiver) {
        if (node == nullptr) {
            return new Node(receiver);
        }

        if (receiver.ReceiverID < node->data.ReceiverID) {
            node->left = insert(node->left, receiver);
        } else if (receiver.ReceiverID > node->data.ReceiverID) {
            node->right = insert(node->right, receiver);
        }

        return node;
    }

    // Helper function to search for receivers based on blood type and organ type
    void search(Node* node, const string& bloodType, const string& organType, vector<ReceiverDetails>& result) const {
        if (node == nullptr) {
            return;
        }

        search(node->left, bloodType, organType, result);
        

        if (node->data.ReceiverBloodType == bloodType && node->data.OrganType == organType) {
            result.push_back(node->data);
        }

        search(node->right, bloodType, organType, result);
    }


public:
    ReceiverBST() : root(nullptr) {}

    // Function to insert a receiver into the BST
    void insert(const ReceiverDetails& receiver) {
        root = insert(root, receiver);
    }

    // Function to search for receivers based on blood type and organ type
    vector<ReceiverDetails> search(const string& bloodType, const string& organType) const {
        vector<ReceiverDetails> result;
        search(root, bloodType, organType, result);
        return result;
    }
};


// Function to print a table of details with dynamic spacing
void printTable(const vector<DonorDetails>& donors, const vector<ReceiverDetails>& receivers) {
    // Function to calculate the maximum length of each column
    auto calculateColumnWidth = [](const string& columnName, const vector<DonorDetails>& donors, const vector<ReceiverDetails>& receivers) {
        size_t maxColumnWidth = columnName.length();

        for (const auto& donor : donors) {
            size_t dataLength = 0;
            if (columnName == "DonorID") dataLength = donor.DonorID.length();
            else if (columnName == "DonorName") dataLength = donor.DonorName.length();
            else if (columnName == "OrganType") dataLength = donor.OrganType.length();
            else if (columnName == "DonorContact") dataLength = donor.DonorContact.length();
            else if (columnName == "DonorAge") dataLength = donor.DonorAge.length();
            else if (columnName == "DonorBloodType") dataLength = donor.DonorBloodType.length();
            else if (columnName == "DonorCity") dataLength = donor.DonorCity.length();
            else if (columnName == "DonorState") dataLength = donor.DonorState.length();
            else if (columnName == "DonorCountry") dataLength = donor.DonorCountry.length();
            else if (columnName == "DonorZipCode") dataLength = donor.DonorZipCode.length();
            else if (columnName == "DonorMedicalHistory") dataLength = donor.DonorMedicalHistory.length();
            else if (columnName == "DonorInsurance") dataLength = donor.DonorInsurance.length();
            else if (columnName == "DonorConsentForm") dataLength = donor.DonorConsentForm.length();
            else if (columnName == "DonorRegistrationDate") dataLength = donor.DonorRegistrationDate.length();

            if (dataLength > maxColumnWidth) {
                maxColumnWidth = dataLength;
            }
        }

        for (const auto& receiver : receivers) {
            size_t dataLength = 0;
            if (columnName == "ReceiverID") dataLength = receiver.ReceiverID.length();
            else if (columnName == "ReceiverName") dataLength = receiver.ReceiverName.length();
            else if (columnName == "ReceiverContact") dataLength = receiver.ReceiverContact.length();
            else if (columnName == "OrganType") dataLength = receiver.OrganType.length();
            else if (columnName == "ReceiverAge") dataLength = receiver.ReceiverAge.length();
            else if (columnName == "ReceiverBloodType") dataLength = receiver.ReceiverBloodType.length();
            else if (columnName == "ReceiverMedicalHistory") dataLength = receiver.ReceiverMedicalHistory.length();
            else if (columnName == "ReceiverInsurance") dataLength = receiver.ReceiverInsurance.length();
            else if (columnName == "ReceiverConsentForm") dataLength = receiver.ReceiverConsentForm.length();
            else if (columnName == "ReceiverRegistrationDate") dataLength = receiver.ReceiverRegistrationDate.length();

            if (dataLength > maxColumnWidth) {
                maxColumnWidth = dataLength;
            }
        }

        return maxColumnWidth;
    };

    // Print the column names for donors
    cout << left;  // Align the text to the left
    cout << setw(calculateColumnWidth("DonorID", donors, receivers)+5) << "DonorID";
    cout << setw(calculateColumnWidth("DonorName", donors, receivers)+5) << "DonorName";
    cout << setw(calculateColumnWidth("OrganType", donors, receivers)+5) << "OrganType";
    cout << setw(calculateColumnWidth("DonorContact", donors, receivers)+5) << "DonorContact";
    cout << setw(calculateColumnWidth("DonorAge", donors, receivers)+2) << "Age";
    cout << setw(calculateColumnWidth("DonorBloodType", donors, receivers)+3) << "BloodType";
    cout << setw(calculateColumnWidth("DonorMedicalHistory", donors, receivers)+3) << "MedicalHistory";
    cout << setw(calculateColumnWidth("DonorInsurance", donors, receivers)+3) << "Insurance";
    cout << setw(calculateColumnWidth("DonorConsentForm", donors, receivers)+3) << "ConsentForm";
    cout << setw(calculateColumnWidth("DonorRegistrationDate", donors, receivers)+3) << "Reg. Date";
    cout << endl;

    // Print the donor details directly under the respective column names
    for (const auto& donor : donors) {
        cout << setw(calculateColumnWidth("DonorID", donors, receivers)+5) << donor.DonorID;
        cout << setw(calculateColumnWidth("DonorName", donors, receivers)+5) << donor.DonorName;
        cout << setw(calculateColumnWidth("OrganType", donors, receivers)+5) << donor.OrganType;
        cout << setw(calculateColumnWidth("DonorContact", donors, receivers)+5) << donor.DonorContact;
        cout << setw(calculateColumnWidth("DonorAge", donors, receivers)+2) << donor.DonorAge;
        cout << setw(calculateColumnWidth("DonorBloodType", donors, receivers)+3) << donor.DonorBloodType;
        cout << setw(calculateColumnWidth("DonorMedicalHistory", donors, receivers)+3) << donor.DonorMedicalHistory;
        cout << setw(calculateColumnWidth("DonorInsurance", donors, receivers)+3) << donor.DonorInsurance;
        cout << setw(calculateColumnWidth("DonorConsentForm", donors, receivers)+3) << donor.DonorConsentForm;
        cout << setw(calculateColumnWidth("DonorRegistrationDate", donors, receivers)+3) << donor.DonorRegistrationDate;
        cout << endl;
    }

    cout << "\n\n";

    // Print the column names for receivers
    cout << setw(calculateColumnWidth("ReceiverID", donors, receivers)+2) << "Rec. ID";
    cout << setw(calculateColumnWidth("ReceiverName", donors, receivers)+2) << "Rec. Name";
    cout << setw(calculateColumnWidth("OrganType", donors, receivers)+5) << "OrganType";
    cout << setw(calculateColumnWidth("ReceiverContact", donors, receivers)+2) << "Rec. Contact";
    cout << setw(calculateColumnWidth("ReceiverAge", donors, receivers)-1) << "Age";
    cout << setw(calculateColumnWidth("ReceiverBloodType", donors, receivers)) << "BloodType";
    cout << setw(calculateColumnWidth("ReceiverMedicalHistory", donors, receivers)) << "MedicalHistory";
    cout << setw(calculateColumnWidth("ReceiverInsurance", donors, receivers)) << "Insurance";
    cout << setw(calculateColumnWidth("ReceiverConsentForm", donors, receivers)) << "ConsentForm";
    cout << setw(calculateColumnWidth("ReceiverRegistrationDate", donors, receivers)) << "Reg. Date";
    cout << endl;

    // Print the receiver details directly under the respective column names
    for (const auto& receiver : receivers) {
        cout << setw(calculateColumnWidth("ReceiverID", donors, receivers)+2) << receiver.ReceiverID;
        cout << setw(calculateColumnWidth("ReceiverName", donors, receivers)+2) << receiver.ReceiverName;
        cout << setw(calculateColumnWidth("OrganType", donors, receivers)+5) << receiver.OrganType;
        cout << setw(calculateColumnWidth("ReceiverContact", donors, receivers)+2) << receiver.ReceiverContact;
        cout << setw(calculateColumnWidth("ReceiverAge", donors, receivers)-1) << receiver.ReceiverAge;
        cout << setw(calculateColumnWidth("ReceiverBloodType", donors, receivers)) << receiver.ReceiverBloodType;
        cout << setw(calculateColumnWidth("ReceiverMedicalHistory", donors, receivers)) << receiver.ReceiverMedicalHistory;
        cout << setw(calculateColumnWidth("ReceiverInsurance", donors, receivers)) << receiver.ReceiverInsurance;
        cout << setw(calculateColumnWidth("ReceiverConsentForm", donors, receivers)) << receiver.ReceiverConsentForm;
        cout << setw(calculateColumnWidth("ReceiverRegistrationDate", donors, receivers)) << receiver.ReceiverRegistrationDate;
        cout << endl;
        cout << "press enter to continue...";
        cin.get();
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
    cout << "press enter to continue...";
    cin.get();
}


// Function to search for and display matching donors based on blood type and organ type
void searchAndDisplayMatches(const DonorBST& donorTree,const ReceiverBST& receiverTree,  const string& bloodType, const string& organType) {
    // Search for matching donors
    vector<DonorDetails> matchingDonors = donorTree.search(bloodType, organType);
    vector<ReceiverDetails> matchingReceivers = receiverTree.search(bloodType, organType);

    // Print the table of matching details
    printTable(matchingDonors, matchingReceivers);

    if (!matchingDonors.empty() && !matchingReceivers.empty()) {
        // Ask the user if they want to proceed with mapping
        cout << "Do you want to map a donor with a receiver? (y/n): ";
        string mapChoice;
        cin >> mapChoice;

        if (mapChoice == "y") {
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

            auto receiverIt = find_if(matchingReceivers.begin(), matchingReceivers.end(), [&receiverID](const ReceiverDetails& receiver) {
                return receiver.ReceiverID == receiverID;
            });

            if (donorIt != matchingDonors.end() && receiverIt != matchingReceivers.end()) {
                // Write mapping details to details.csv
                writeMappingToCSV(*donorIt, *receiverIt);
            } else {
                cout << "Invalid DonorID or ReceiverID. Mapping failed." << endl;
                cout << "press enter to go to main menu...";
                cin.get();
            }
        } else {
            cout << "Mapping skipped. No changes made to CSV files." << endl;
            cout << "press enter to go to main menu...";
            cin.get();
            system("welcome.exe");
        }
    } else if(matchingDonors.empty()){
        cout << "No matching donors found. Mapping skipped." << endl;
        cout << "press enter to go to main menu...";
        cin.get();
        system("welcome.exe");

    } else if(matchingReceivers.empty()){
        cout << "No matching receivers found. Mapping skipped." << endl;
        cout << "press enter to go to main menu...";
        cin.get();
        system("welcome.exe");
    }
    else{
        cout << "No matching receivers and donors found. Mapping skipped." << endl;
        cout << "press enter to go to main menu...";
        cin.get();
        system("welcome.exe");
    }
}

int main() {
    system("cls");
    system("color 6f");
    system("header.exe");
    DonorBST donorTree;
    ReceiverBST receiverTree;
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
            receiverTree.insert(receiver);
        }
        receiverFile.close();
    } else {
        cerr << "Error: Unable to open receiver CSV file." << endl;
        return 1;
    }

    // Ask the user if they want to map and search for matches
    cout << "1: map a donor with a receiver"<<endl;
    cout << "2: Main Menu" << endl << endl;
    int mapChoice;
    cout << "enter your choice: ";
    cin >> mapChoice;

    if (mapChoice == 1) {
        // Ask for blood type and organ type
        system("cls");
        system("header.exe");
        cout << "Enter the blood type: ";
        string bloodType;
        cin >> bloodType;

        cout << "Enter the organ type: ";
        string organType;
        cin >> organType;
        cout << endl << endl;

        // Search for matching donors and display results
        searchAndDisplayMatches(donorTree,receiverTree, bloodType, organType);
    } else {
        cout << "Mapping skipped. No changes made to CSV files." << endl;
        cout<< "press enter to go to main menu...";
        cin.get();
        system("welcome.exe");
    }

    return 0;
}

