#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <cmath>
#include "clsUtil.h"
#include <fstream>

using namespace std;
class clsUser : public clsPerson
{

public:
    struct stLoginRegisterRecord;

private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkedForDelete = false;

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        string Password = clsUtil::Decrypt(vUserData[5]);
        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
                       vUserData[3], vUserData[4], Password, stoi(vUserData[6]));
    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {

        string UserRecord = "";
        UserRecord += User.FirstName() + Seperator;
        UserRecord += User.LastName() + Seperator;
        UserRecord += User.Email() + Seperator;
        UserRecord += User.Phone() + Seperator;
        UserRecord += User.UserName() + Seperator;
        UserRecord += clsUtil::Encrypt(User.Password()) + Seperator;
        UserRecord += to_string(User.Permissions());

        return UserRecord;
    }

    string _PrepareLogInRecord(string Seperator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += _UserName + Seperator;
        LoginRecord += clsUtil::Encrypt(_Password) + Seperator;
        LoginRecord += to_string(_Permissions);
        return LoginRecord;
    }

    static vector<clsUser> _LoadUsersDataFromFile()
    {

        vector<clsUser> vUsers;

        fstream MyFile;
        MyFile.open("/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/Users.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                clsUser User = _ConvertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();
        }

        return vUsers;
    }

    static void _SaveUsersDataToFile(vector<clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/Users.txt", ios::out); // overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    // we only write records that are not marked for delete.
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser &U : _vUsers)
        {
            if (U.UserName() == _UserName)
            {
                U = *this;
                break;
            }
        }

        _SaveUsersDataToFile(_vUsers);
    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stLoginRegisterRecord LoginRegisterRecord;

        vector<string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = clsUtil::Decrypt(LoginRegisterDataLine[2]);
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

        return LoginRegisterRecord;
    }

public:
    clsUser(enMode Mode, string FirstName, string LastName,
            string Email, string Phone, string UserName, string Password,
            int Permissions) : clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    struct stLoginRegisterRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;
    };

    enum enPermissions
    {
        eAll = -1,
        pListClients = 1,
        pAddNewClient = 2,
        pDeleteClient = 4,
        pUpdateClients = 8,
        pFindClient = 16,
        pTranactions = 32,
        pManageUsers = 64,
        pLoginRegisters = 128
    };

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string UserName()
    {
        return _UserName;
    }

    void UserName(string UserName)
    {
        _UserName = UserName;
    }

    void Password(string Password)
    {
        _Password = Password;
    }

    string Password()
    {
        return _Password;
    }

    void Permissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int Permissions()
    {
        return _Permissions;
    }

    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/Users.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName() == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open("/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/Users.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName() == UserName && User.Password() == Password)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildUserExists = 2
    };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            // This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                // We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

        default:
            return svFaildEmptyObject;
        }
        }
    }

    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    bool Delete()
    {
        vector<clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();
        bool WasDeleted = false;
        for (clsUser &U : _vUsers)
        {
            if (U.UserName() == _UserName)
            {
                U._MarkedForDelete = true;
                WasDeleted = true;
                break;
            }
        }

        if (WasDeleted)
            _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return WasDeleted;
    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector<clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    // static bool HasPermission(short Choice, short Permessions)
    // {
    //     return Permessions & Choice;
    // }

    static bool HasPermission(short Choice, clsUser User)
    {
        return User.Permissions() & Choice != 0;
    }

    bool HadPermission(short Choice)
    {
        return this->_Permissions & Choice ;
    }

    void RegisterLogIn()
    {

        string stDataLine = _PrepareLogInRecord();

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    static vector<stLoginRegisterRecord> GetLoginRegisterList()
    {
        fstream FILE("/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/LoginRegister.txt", ios::in);
        vector<stLoginRegisterRecord> vOrders;
        if (FILE.is_open())
        {
            string Line;

            while (getline(FILE, Line))
            {
                stLoginRegisterRecord Record = _ConvertLoginRegisterLineToRecord(Line);
                vOrders.push_back(Record);
            }

            FILE.close();
        }

        return vOrders;
    }
};