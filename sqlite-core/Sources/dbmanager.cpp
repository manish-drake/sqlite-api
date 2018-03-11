#include "dbmanager.h"
#include "db.h"


DbManager::DbManager(){}

DB DbManager::open(const char* dbName){
    auto find = this->m_dbs.find(dbName);
    if(find != this->m_dbs.end()){
        return m_dbs[dbName];
    }
    else{
        DB db(dbName);
        m_dbs.insert(std::pair<const char*, DB>(dbName, db));
        return db;
    }
}

DbManager DbManager::instance(){
    static DbManager s_instance;
    return s_instance;
}