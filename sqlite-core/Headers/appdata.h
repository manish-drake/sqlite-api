#ifndef APPDATA_H
#define APPDATA_H

#include "entity.h"
using namespace std;

class   AppData: public Entity
{

  private:
    int m_userId = 0;
    string m_key;
    string m_value;

  public:
    // AppData();
    AppData(const char* dbName, const char* tableName);
    void populate(const int userId, const string &key, const string &value);

    /**
     * The three functions that need to be created
     * in the class that has to be serialized.
     * All three functions are called internally
     * and should not be required to be called
     * from outside at any point of time.
    */
    schema getschema() const override;  //to define schema
    void setData() override;            //to get data from object into db
    void reset(Columns col) override;   //to get data from db into object
    /*----------------------------------------------*/

    int userId()const;
    void setUserId(const int userId);

    string key()const;
    void setKey(const string &key);

    string value()const;
    void setValue(const string &value);


};

#endif // APPDATA_H
