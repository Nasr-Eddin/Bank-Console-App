#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
using namespace std;

class clsAddNewUserScreen : public clsScreen
{
private:
    static void _ReadUserInfo(clsUser &User)
    {
        cout << "\nEnter FirstName: ";
        User.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        User.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        User.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        User.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter Password: ";
        User.Password(clsInputValidate::ReadString());

        User.Permissions(SetPermissions());
    }


    static void _PrintUser(clsUser& User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nUser Name   : " << User.UserName();
        cout << "\nFirstName   : " << User.FirstName();
        cout << "\nLastName    : " << User.LastName();
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email();
        cout << "\nPhone       : " << User.Phone();
        cout << "\nPassword    : " << User.Password();
        cout << "\n___________________\n";

    }


    static short SetPermissions()
    {
        short Per = 0;
        if (clsInputValidate::YesOrNO("Do You want to give full access?[Y/N]: "))
            return clsUser::enPermissions::eAll; // = -1

        string PerArr[] = {"List Client", "Add New Client", "Delete Client", "Update Client", "Find Client", "Transactions", "Manage Users", "Login Registers", "Currency Exchange"};

        for (short i = 0; i < 9; i++)
        {
            if (clsInputValidate::YesOrNO("Do You want [" + PerArr[i] + "] Permission? [Y/N]: "))
                Per += pow(2,i);
            // Per |= (short)pow(2, i) // We can use the bitwise OR also, it gives the same result
        }

        return Per;
    }

public:
    static void ShowAddNewUserScreen()
    {
        _DrawScreenHeader("\tADD NEW USER SCREEN");

        cout << "\nEnter the User Name you want to add: ";
        string UN = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(UN))
        {
            cout << "User Name already exist, choos another one: ";
            UN = clsInputValidate::ReadString();
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UN);

        _ReadUserInfo(NewUser);


        clsUser::enSaveResults SaveResult = NewUser.Save();

        switch(SaveResult)
        {
            case clsUser::enSaveResults::svFaildUserExists:
            cout << "Failed, User Already exists" << endl;
            break;

            case clsUser::enSaveResults::svSucceeded:
            cout << "Hooray!, Save New User succeeded :)" << endl;
            _PrintUser(NewUser);
            break;

            case clsUser::enSaveResults::svFaildEmptyObject:
            cout << "Failed to save because The user is empty" << endl;
            break;
        }
    }
};