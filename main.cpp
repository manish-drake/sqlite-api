#include <iostream>
#include "dbmanager.h"
#include "db.h"
#include "table.h"
#include "entity.h"
#include "appdata.h"



int main(){
    /*example*/
    AppData appSettings("app.db", "data1");
//Insert 
    appSettings.populate(1, "distance", "25Ft");
    appSettings.Save();

    appSettings.populate(1, "port", "A");
    appSettings.Save();
//Select
    auto all = Entity::All(AppData("app.db", "data1")/*or appSettings*/);
    for(auto ad: all){
        cout << ad.key() << ":" << ad.value() << endl;
    }
//Update
    AppData& ad = all.at(0);
    ad.setKey("stars");
    ad.Update();
//Delete
    all.at(1).Remove();
    /*example*/
    return 0;
}