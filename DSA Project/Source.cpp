#include "AVLTree.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void clearScreen() {
    this_thread::sleep_for(chrono::seconds(3));
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

void printBorderedText() {
    string message = "Welcome to Pakistan Airplane Landing Reservation System! \n\n                     Made by HALIMA & BISMA";
    int borderLength = 70;
    for (int i = 0; i < borderLength; i++) {
        cout << "*";
    }
    cout << endl;
    cout << "      " << message << endl;
    for (int i = 0; i < borderLength; i++) {
        cout << "*";
    }
    cout << endl;
}

int main() {
    printBorderedText();
    clearScreen();
    int minTimeDifference;
    cout << "Enter the minimum time difference in minutes: ";
    cin >> minTimeDifference;

    AVLTree tree(minTimeDifference);
    int choice;
    do {
        cout << "=========================================================\n";
        cout << "|      PAKISTAN AIRPLANE LANDING RESERVATION SYSTEM     |\n";
        cout << "---------------------------------------------------------\n";
        cout << "|            1. Insertion of Landing Time Slots         |\n";
        cout << "|            2. Retrieval of Minimum Landing Time       |\n";
        cout << "|            3. Retrieval of Maximum Landing Time       |\n";
        cout << "|            4. Rank of a Specific Time                 |\n";
        cout << "|            5. Deletion of the First Landing           |\n";
        cout << "|            6. Retrieval of Next Landing Time          |\n";
        cout << "|            7. Printing All Landing Times              |\n";
        cout << "|            8. Search for a Specific Time              |\n";
        cout << "|            9. Cancel Reservation                      |\n";
        cout << "|           10. Exit Program                            |\n";
        cout << "=========================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        int time;
        switch (choice) {
        case 1:
            cout << "Enter time in HHMM: ";
            cin >> time;
            tree.addReservation(time);
            break;
        case 2:
            tree.minimumReservation();
            break;
        case 3:
            tree.maximumReservation();
            break;
        case 4:
            cout << "Enter time in HHMM to find rank: ";
            cin >> time;
            tree.rankOfReservation(time);
            break;
        case 5:
            tree.planeLanded();
            break;
        case 6:
            cout << "Enter time in HHMM to find the next landing: ";
            cin >> time;
            tree.nextLandingTime(time);
            break;
        case 7:
            tree.displayReservations();
            break;
        case 8:
            cout << "Enter time in HHMM to search: ";
            cin >> time;
            tree.searchReservation(time);
            break;
        case 9:
            cout << "Enter time in HHMM to cancel: ";
            cin >> time;
            tree.cancelReservation(time);
            break;
        case 10:
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 10);
    clearScreen();
    int borderLength = 70;
    for (int i = 0; i < borderLength; i++) {
        cout << "*";
    }
    cout << endl;
    cout << "\t   Thank you for using the reservation system!  " << endl;
    for (int i = 0; i < borderLength; i++) {
        cout << "*";
    }
    cout << endl;
    clearScreen();
    for (int i = 0; i < borderLength; i++) {
        cout << "*";
    }
    cout << endl;
    cout << "\t Thank you for being a great teacher(Friend hehe)  " << endl;
    cout << "\t      Thanks to you, LAB became so FUN  " << endl;
    for (int i = 0; i < borderLength; i++) {
        cout << "*";
    }
    cout << endl;
    return 0;
}

