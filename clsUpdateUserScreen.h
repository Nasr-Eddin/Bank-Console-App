#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
using namespace std;

class clsUpdateUserScreen : public clsScreen
{
private:
    static void  _ReadUserInfo(clsUser &User)
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

    static void _PrintUser(clsUser &User)
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
    static void ShowUpdateUserScreen()
    {
        _DrawScreenHeader("\tUpdate USER SCREEN");

        cout << "\nEnter the User Name you want to Update: ";
        string UN = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UN))
        {
            cout << "User Name is NOT exist, choos a valid one: ";
            UN = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UN);

        _PrintUser(User1);

        if (!clsInputValidate::YesOrNO("Are you sure you want update this user? [Y/N]: "))
            return;

        _ReadUserInfo(User1);

        clsUser::enSaveResults SaveResult = User1.Save();

        switch (SaveResult)
        {
        case clsUser::enSaveResults::svFaildUserExists:
            cout << "Failed, User Already exists" << endl;
            break;

        case clsUser::enSaveResults::svSucceeded:
            cout << "Hooray!, Save New User succeeded :)" << endl;
            _PrintUser(User1);
            break;

        case clsUser::enSaveResults::svFaildEmptyObject:
            cout << "Failed to save because The user is empty" << endl;
            break;
        }
    }
};