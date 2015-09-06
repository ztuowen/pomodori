//
// Created by joe on 9/3/15.
//

#include "logging.h"
#include "stdlib.h"
#include "stdio.h"
#include <ctime>
#include <string>
#include <sqlite3.h>
#include <unistd.h>
#include <pwd.h>
#include "pomodori.h"
#include "trayicon.h"

struct passwd *pw = getpwuid(getuid());

using namespace std;
void log(tres* res,int code)
{
    if (code)
    {
        sqlite3 *db;
        char *zErrMsg = 0;
        char sqlop[50];
        sprintf(sqlop,"%s/." APPNAME,pw->pw_dir);
        int rc = sqlite3_open(sqlop,&db);
        if( rc ){
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            exit(0);
        }
        sprintf(sqlop,"insert into log (Cat) Values ('%s');",res->reason);
        rc = sqlite3_exec(db, sqlop, NULL, 0, &zErrMsg);
        if( rc!=SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            }
        sqlite3_close(db);
    }
    delete res->reason;
    delete res;
    tray_deactivate();
}