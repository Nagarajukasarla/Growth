#include <iostream>
#include <mariadb/mysql.h>

using namespace std;


int main () {

    MYSQL* con;
    
    con = mysql_init (NULL);
    
    // if connection not success then edit it
    if ((mysql_real_connect (con, "localhost", "u0_a259", "", "Diet_db", 0, NULL, 0)) == NULL) {
        cout << "Connection error: " << mysql_error (con) << endl;
    }
    else {
        if ((mysql_query (con, "INSERT INTO Users(User_id, Username, Password) VALUES(8, '"john@growth.com"', '"pass"'), (9, '"sahasra@growth.com"', '"pass"');"))) {
            cout << "Sql query error: " << mysql_error (con) << endl;
        }
    }
    return 0;
}
