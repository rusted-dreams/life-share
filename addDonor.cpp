#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct Donor {
    std::string name;
    std::string organType;
    std::string contact;
    int age;
    std::string bloodType;
    std::string regDate;
    std::string city;
    std::string state;
    std::string country;
    std::string address;
    std::string zipCode;
    std::string medicalHistory;
    std::string insurance;
    std::string consentForm;
};

void registerDonor(std::ofstream& file, Donor& newDonor);
void printDonorDetails(const Donor& donor);
bool confirmRegistration();
void runDonorRegistrationSystem();

int main() {
    std::cout << "Do you want to register as a donor? (Y/N): ";
    char registrationChoice;
    std::cin >> registrationChoice;

    if (registrationChoice == 'Y' || registrationChoice == 'y') {
        system("CLS");
        system("color 3F"); // Change console color

        std::ofstream file("donor.csv", std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Error opening donor.csv for writing.\n";
            return 1;
        }

        runDonorRegistrationSystem();

        file.close();
        std::cout << "Registered successfully!\n";
        system("CLS");
        system("color 2F"); // Change console color to default

        std::cout << "Do you want to go to the Donor Registration System or Main Menu?\n";
        std::cout << "1. Donor Registration System\n";
        std::cout << "2. Main Menu\n";
        int menuChoice;
        std::cin >> menuChoice;

        if (menuChoice == 1) {
            runDonorRegistrationSystem();
        } else if (menuChoice == 2) {
            system("CLS");
            system("welcome_page.exe"); // Assuming welcome_page.exe is the main menu executable
        } else {
            std::cout << "Invalid choice. Returning to Main Menu.\n";
            system("CLS");
            system("welcome_page.exe"); // Assuming welcome_page.exe is the main menu executable
        }
    } else {
        std::cout << "Returning to Main Menu.\n";
        system("CLS");
        system("welcome_page.exe"); // Assuming welcome_page.exe is the main menu executable
    }

    return 0;
}

void registerDonor(std::ofstream& file, Donor& newDonor) {
    std::cout << "Enter donor details:\n";
    std::cout << "Name: ";
    std::cin >> newDonor.name;

    std::cout << "Organ Type: ";
    std::cin >> newDonor.organType;

    std::cout << "Contact: ";
    std::cin >> newDonor.contact;

    std::cout << "Age: ";
    std::cin >> newDonor.age;

    std::cout << "Blood Type: ";
    std::cin >> newDonor.bloodType;

    std::cout << "Registration Date: ";
    std::cin >> newDonor.regDate;

    std::cout << "City: ";
    std::cin >> newDonor.city;

    std::cout << "State: ";
    std::cin >> newDonor.state;

    std::cout << "Country: ";
    std::cin >> newDonor.country;

    std::cout << "Address: ";
    std::cin.ignore();
    std::getline(std::cin, newDonor.address);

    std::cout << "Zip Code: ";
    std::cin >> newDonor.zipCode;

    std::cout << "Medical History: ";
    std::cin.ignore();
    std::getline(std::cin, newDonor.medicalHistory);

    std::cout << "Insurance: ";
    std::cin >> newDonor.insurance;

    std::cout << "Consent Form: ";
    std::cin >> newDonor.consentForm;

    // Print entered details for confirmation
    printDonorDetails(newDonor);

    // Ask for confirmation
    if (confirmRegistration()) {
        // Write details to the file
        file << newDonor.name << "," << newDonor.organType << "," << newDonor.contact << ","
             << newDonor.age << "," << newDonor.bloodType << ","
             << newDonor.regDate << "," << newDonor.city << "," << newDonor.state << ","
             << newDonor.country << "," << newDonor.address << "," << newDonor.zipCode << ","
             << newDonor.medicalHistory << "," << newDonor.insurance << ","
             << newDonor.consentForm << "\n";
    }
}

void printDonorDetails(const Donor& donor) {
    std::cout << "\nDonor Details:\n";
    std::cout << "Name: " << donor.name << "\n";
    std::cout << "Organ Type: " << donor.organType << "\n";
    std::cout << "Contact: " << donor.contact << "\n";
    std::cout << "Age: " << donor.age << "\n";
    std::cout << "Blood Type: " << donor.bloodType << "\n";
    std::cout << "Registration Date: " << donor.regDate << "\n";
    std::cout << "City: " << donor.city << "\n";
    std::cout << "State: " << donor.state << "\n";
    std::cout << "Country: " << donor.country << "\n";
    std::cout << "Address: " << donor.address << "\n";
    std::cout << "Zip Code: " << donor.zipCode << "\n";
    std::cout << "Medical History: " << donor.medicalHistory << "\n";
    std::cout << "Insurance: " << donor.insurance << "\n";
    std::cout << "Consent Form: " << donor.consentForm << "\n";
}

bool confirmRegistration() {
    char confirmation;
    std::cout << "\nDo you want to confirm your registration? (Y/N): ";
    std::cin >> confirmation;

    return (confirmation == 'Y' || confirmation == 'y');
}

void runDonorRegistrationSystem() {
    
    system("CLS");
    system("color 3F");
    Donor newDonor;
    std::ofstream file("donor.csv", std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Error opening donor.csv for writing.\n";
        return;
    }

    // Initialize the registration date (assuming the system date can be retrieved)
    // Add other necessary initializations
    // ...

    registerDonor(file, newDonor);

    file.close();
}
