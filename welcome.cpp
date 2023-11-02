#include <iostream>
#include <windows.h>
using namespace std;

void welcomeMessage() {
    system("cls");
    char title[] = "\033[1;36m\t\t\t\t\t----------------------------\n\t\t\t\t\t\tLIFE SHARE\n\t\t\t\t\t----------------------------\033[0m";
    char *ptr = title;
    for (int i = 0; i < sizeof(title); i++)
    {
        cout << *(ptr + i);
        Sleep(10);
    }
    cout << endl;
}

int mainMenu() {
    cout << "1: Register Donor" << endl;
    cout << "2: Register Receiver" << endl;
    cout << "3: Search Donor" << endl;
    cout << "4: search Receiver" << endl;
    cout << "5: Map Donor and Receiver" << endl;
    cout << "6: Exit" << endl
         << endl;
    cout << "Enter Your choice: ";
    int choice;
    cin >> choice;
    system("cls");

    while (true){
        switch (choice){
        case 1:
            system("addDonor.exe");
        case 2:
            system("addReceiver.exe");
        case 3:
            system("searchDonor.exe");
        case 4:
            system("searchReceiver.exe");
        case 5:
            system("mapDonorReceiver.exe");
        case 6:
            return 0;
        default:
            cout << "Invalid choice please choose again!!" << endl;
            return 0;
        }
    }
}

int main(){
    welcomeMessage();
    mainMenu();
}
