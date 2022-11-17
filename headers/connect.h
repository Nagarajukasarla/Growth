#include <mariadb/mysql.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
using namespace std;

// Required structure for the connection
struct connection_details {
    const char *server, *user, *password, *database;
};

// Function which setup the connection to the database
MYSQL* mysql_connection_setup (struct connection_details mysql_details) {
    MYSQL* connection = mysql_init(NULL);

    // Checking whether the connection was successful or not
    if (!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, mysql_details.database, 0, NULL, 0)) {
        cout << "Connection Error : " << mysql_error(connection) << endl;
        exit(1);
    }
    return connection;
}

// Executing sql queries
MYSQL_RES* mysql_execute_query(MYSQL* connection, const char *sql_query) {
    if (mysql_query (connection, sql_query)) {
        cout << "Sql Execution Error : " << mysql_error(connection) << endl;
        exit (1);
    }
    return mysql_use_result (connection);
}

// Conforming whether the user exist or not in database
bool isUserExist (MYSQL* con, string email, string password) {
    bool check;
    MYSQL_RES *result;
    MYSQL_ROW row; // FORMAT : char**
    result = mysql_execute_query (con, "SELECT * FROM Users;");

    while ((row = mysql_fetch_row(result)) != NULL) {
        if (!(strcasecmp(row[2], email.c_str())) && !(strcasecmp(password.c_str(), row[3]))) {
            check = 1;
            break;
        }
        else {
            check = 0;
        }
    }
    mysql_free_result (result);
    if (check) return 1;
    else    return 0;
}

void signUp (MYSQL* con, string username, string email, string password) {
    
    MYSQL_RES *res;
    MYSQL_ROW row;
    bool userValidation = 0;
    // Make sure users is not exist
    res = mysql_execute_query (con, "SELECT * FROM Users;");
    while ((row = mysql_fetch_row(res)) != NULL) {
        if (!(strcasecmp(row[1], username.c_str())) || !(strcasecmp(row[2], email.c_str()))) {
            cout << "  User already exists!" << endl;
            cout << "  Please login" << endl;
            userValidation = 1;
            break;
        }
    }
    if (!userValidation) {
        stringstream ss;
        ss << "INSERT INTO Users(Username, Email, Password) VALUES ('"+username+"', '"+email+"', '"+password+"');";
        string queryBuffer = ss.str();
        const char* query = queryBuffer.c_str();
        if (mysql_query (con, query)) {
            cout << "SQL QUERY ERROR : " << mysql_error (con) << endl;
        }
        else {
            cout << endl << endl << "  CONGRATULATIONS, SIGN UP SUCCESSFUL" << endl;
            cout << "  Kindly login to experience the Application" << endl;
        }
    }
}

// returning the username for file creation in Users Folder
string getUsernamedb (MYSQL* conn, string emailId) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    string bufferName;
    res = mysql_execute_query (conn, "SELECT * FROM Users;");
    while ((row = mysql_fetch_row(res)) != NULL) {
        if (!(strcasecmp (row[2], emailId.c_str()))) {
            bufferName = row[1];
            break;
        }
    }
    mysql_free_result (res);
    return bufferName;
}