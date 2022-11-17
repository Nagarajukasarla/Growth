#include <iostream>
#include "headers/connect.h"
#include "headers/exefiles.h"
//#include <mariadb/mysql.h>

using namespace std;

class Load {

    private:
        string username;
        string email;
        string password;

    public:
        // Constructor
        Load () {
            system ("clear");
            cout << endl << endl << endl;
            cout.width(10); cout << " ################################################################################### " << endl;
            cout.width(10); cout << " #                                                                                 # " << endl;
            cout.width(10); cout << " #      ooooooo8 oooooooooo    ooooooo  oooo     oooo ooooooooooo ooooo ooooo      # " << endl;
            cout.width(10); cout << " #    o888    88  888    888 o888   888o 88   88  88  88  888  88  888   888       # " << endl;
            cout.width(10); cout << " #    888   ooooo 888oooo88  888     888  88 888 88       888      888ooo888       # " << endl;
            cout.width(10); cout << " #    888o    88  888  88o   888o   o888   888 888        888      888   888       # " << endl;
            cout.width(10); cout << " #     888ooo888 o888o  88o8   88ooo88      8   8        o888o    o888o o888o      # " << endl;
            cout.width(10); cout << " #                                                                                 # " << endl;
            cout.width(10); cout << " ################################################################################### " << endl;
            cout << endl << endl << endl << endl;
        }

        int loadUser (MYSQL* con) {
            int set = 1;
            int choice = 0;
            while (choice != 3) {
                cout << "  +------------------------+" << endl;
                cout << "  | Select any one option  |" << endl;
                cout << "  | 1. Sign Up             |" << endl;
                cout << "  | 2. Login               |" << endl;
                cout << "  | 3. Exit                |" << endl;
                cout << "  +------------------------+" << endl;
                cout << "  Make your choice : ";
                cin >> choice;
                cout << endl << endl;
                if (choice == 1) {
                    signingUp (con);// end
                    set = 1;
                }
                else if (choice == 2) {
                    userLogin (con);
                    set = 0;
                    break; // using break because when client choose login option he not showed this function again
                }
                else if (choice != 3) {
                    cout << "  !!!! Please make correct choice !!!!" << endl;
                }
                else {
                }
            }
            return set;
        }

        //Login
        void userLogin (MYSQL* con) {
            cout << " Email : ";
            cin >> email;
            cout << endl;
            cout << " Password : ";
            cin >> password;
            cout << endl;
            Load ();
            // User verification is in Activities class
        }

        // Sign  up
        void signingUp (MYSQL* con) {
            cout << "    ***Fill your details***" << endl << endl;
            cout << "  Username should be unique, use only letters and numbers" << endl << endl;
            cout << "  Username : ";
            cin >> username;
            cout << endl;
            cout << "  Email : ";
            cin >> email;
            cout << endl;
            cout << "  Password : ";
            cin >> password;
            signUp (con, username, email, password);
            char temp;
            cout << endl << "  Press 'Y' to continue  ";
            cin >> temp;
            Load ();
        }

        // getters
        string getUsername () {
            return username;
        }
        string getEmail () {
            return email;
        }
        string getPassword () {
            return password;
        }
};

class Activities {
    public :
        // Definitions are outside
        void openActivity (MYSQL* conn, string emailId);
        void newActivity (MYSQL* conn, string emailId);
        
        void userActivity (MYSQL* con, string email, string password) {
            bool check = isUserExist (con, email, password);
            if (check == 1) {
                int choice = 0;
                string userName = getUsernamedb (con, email);
                cout << "   \tWelcome Back " << userName << endl <<endl;
                while (choice != 3) {
                    cout << "  +--------------------------------+" << endl;
                    cout << "  | Please select any one :        |" << endl;
                    cout << "  |  1. Open my Activity           |" << endl;
                    cout << "  |  2. Create new Activity        |" << endl;
                    cout << "  |  3. Exit                       |" << endl;
                    cout << "  +--------------------------------+" << endl << endl;
                    cout << "  Make your choice : ";
                    cin >> choice;
                    Load load;
                    if (choice == 1) {
                        openActivity (con, email);
                    }
                    else if (choice == 2) {
                        newActivity (con, email);
                    }
                    else if (choice != 3) {
                        cout << "  !!!! Please make correct choice !!!!" << endl;
                        userActivity (con, email, password);
                    }
                    else {
                        system ("clear");
                    }
                }
            }
            else {
                cout << "  Invalid Email or Password" << endl;
                cout << "  Kindly Sign Up to Login" << endl << endl;
            }
        }
};

// Opening an existing activity
void Activities::openActivity(MYSQL* conn, string emailId) {
    // Reading an existing file
    int taskChoice = 0;
    while (taskChoice != 3) {
        cout << "       ** Your available Activites **" << endl << endl;
        cout << "  +==================+" << endl;
        cout << "  | 1. Food          |" << endl;
        cout << "  | 2. Workout       |" << endl;
        cout << "  | 3. Back to home  |" << endl;
        cout << "  +==================+" << endl;
        cout << "  Please make your choice : ";
        cin >> taskChoice;
        if (taskChoice == 1) {
            foodList ("read", getUsernamedb(conn, emailId));  // File will open in read mode
        }
        else if (taskChoice == 2) {
            workoutList ("read", getUsernamedb(conn, emailId));  // File will open in read mode
        }
        else if (taskChoice != 3){
            cout << "  Please make correct choice !" << endl << endl;
            openActivity (conn, emailId);
        }
        else {}
        Load load;
    }
}


// New activity creation
void Activities::newActivity(MYSQL* conn, string emailId) {
    int taskChoice = 0;
    while (taskChoice != 3) {
        cout << "   Adding new list of Activities" << endl;
        cout << "   You can add daily food list and workouts timing." << endl;
        cout << "   +======================+" << endl;
        cout << "   | 1. Food              |" << endl;
        cout << "   | 2. Workout           |" << endl;
        cout << "   | 3. Back to home      |" << endl;
        cout << "   +======================+" << endl;
        cout << "   Please make your choice : ";
        cin >> taskChoice;
        cout << endl;
        if (taskChoice == 1) {
            foodList ("write", getUsernamedb(conn, emailId));
        }
        else if (taskChoice == 2) {
            workoutList ("write", getUsernamedb(conn, emailId));
        }
        else if (taskChoice != 3){
            cout << "  Please make correct choice !" << endl << endl;
            newActivity (conn, emailId);
        }
        else {}
        Load laod;
    }
}



///////////////// MAIN FUNCTION HERE!!! ///////////////

int main () {

    MYSQL *connection;
    //MYSQL_RES *res;
    //MYSQL_ROW row;

    string myRow;
    struct connection_details mysqlD;
    mysqlD.server = "localhost";
    mysqlD.user = "root";
    mysqlD.password = "root";
    mysqlD.database = "Diet_db";

    // Connecting to database...
    connection = mysql_connection_setup (mysqlD);
    
    // Objects creation
    Load load;
    Activities myAct;

    // User login
    
    if(!(load.loadUser (connection))) {
        myAct.userActivity (connection, load.getEmail(), load.getPassword());
    }
    
    // Closing the connection
    mysql_close (connection);
    //system ("clear");
    return 0;
}
