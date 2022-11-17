// This file execute bash commands
// Be carefull while editing.

#include <iostream>
#include <string>
#include <unistd.h>


using namespace std;

// Foodlist function definiton
void foodList (string opeartion, string username) {
    static string filename;
    char dirCmd[40] = "mkdir -p "; // Directory created by username
    char command[30] = "nano ";
    
    if (opeartion == "write") {
        cout << "  DON'T FORGET TO SAVE YOUR FILE EXTENSION AS .txt !!!" << endl;
        cout << "  Now a text file is created in food directory" << endl;
        cout << "  Give name for your file: ";
        cin >> filename;
        system ("mkdir -p Users/");
        system ("chmod +x Users");
        chdir ("Users/");
        system (strcat (dirCmd, username.c_str()));
        string usrCmd = username + "/";
        chdir (usrCmd.c_str());
        system ("mkdir -p Activities/");
        chdir ("Activities/");
        system ("mkdir -p Food/");
        chdir ("Food/");
        system (strcat (command, filename.c_str()));
        cout << endl << "  Your data is successfully written into file!" << endl << endl;
    }
    
    // Opening an existing file
    if (opeartion == "read") {
        string openCmd = "Users/" + username + "/" + "Activities/Food/";
        chdir (openCmd.c_str());
        cout <<  endl << "  Your available files : " << endl << endl;
        system ("ls --format=single-column");
        cout << endl << "  Enter filename : ";
        cin >> filename;
        system (strcat (command, filename.c_str()));
    }
    chdir ("../../../../");
}

// Workout list function definiton
void workoutList (string opeartion, string username) {
    static string filename;
    char dirCmd[40] = "mkdir -p "; // Directory created by username
    char command[30] = "nano ";
    if (opeartion == "write") {
        cout << "  DON'T FORGET TO SAVE YOUR FILE EXTENSION AS .txt !!!" << endl;
        cout << "  Now a text file is created in workout directory" << endl;
        cout << "  Give name for your file: ";
        cin >> filename;
        system ("mkdir -p Users/");
        chdir ("Users/");
        system (strcat (dirCmd, username.c_str()));
        string usrCmd = username + "/";
        chdir (usrCmd.c_str());
        system ("mkdir -p Activities/");
        chdir ("Activities/");
        system ("mkdir -p Workout/");
        chdir ("Workout/");
        system (strcat (command, filename.c_str()));
        cout << endl << "  Your data is successfully written into file!" << endl << endl;
    }
    if (opeartion == "read") {
        string openCmd = "Users/" + username + "/" + "Activities/Workout/";
        chdir (openCmd.c_str());
        cout <<  endl << "  Your available files : " << endl << endl;
        system ("ls --format=single-column");
        cout << endl << "  Enter filename : ";
        cin >> filename;
        system (strcat(command, filename.c_str()));
    }
    chdir ("../../../../");
}