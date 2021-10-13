#include "postgres.h"

Postgres::Postgres(string hst, string prt, string db, string usr, string pw)
{
    host = hst;
    port = prt;
    dbname = db;
    username = usr;
    password = pw;

    connection_str = (
        "host=" + hst +
        " port=" + prt +
        " dbname=" + db +
        " user=" + usr +
        " password=" + pw);
}

Postgres::Postgres()
{
    host = "localhost";
    port = "5432";
    dbname = "ProjLingProg";
    username = "myuser";
    password = "mypassword";

    connection_str = (
        "host=" + host +
        " port=" + port +
        " dbname=" + dbname +
        " user=" + username +
        " password=" + password);
}
string Postgres::getHost() { return host; }
string Postgres::getPort() { return port; }
string Postgres::getDBname() { return dbname; }
string Postgres::getUsername() { return username; }
string Postgres::getPassword() { return password; }
string Postgres::getConnection_str() { return connection_str; }