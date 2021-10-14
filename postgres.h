#ifndef POSTGRES_H
#define POSTGRES_H

#include <iostream>
#include <string>
#include <pqxx/pqxx>

using namespace std;

class Postgres {
    public:
        Postgres();
        Postgres(string, string, string, string, string);
        ~Postgres();

        string getHost();
        string getPort();
        string getDBname();
        string getUsername();
        string getPassword();

        string getConnection_str();

    private:
        string host;
        string port;
        string dbname;
        string username;
        string password;
        string connection_str;
};

#endif
