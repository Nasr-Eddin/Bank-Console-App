#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen :protected clsScreen
{


private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName();
        cout << "\nLastName    : " << User.LastName();
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email();
        cout << "\nPhone       : " << User.Phone();
        cout << "\nUser Name   : " << User.UserName();
        cout << "\nPassword    : " << User.Password();
        cout << "\nPermissions : " << User.Permissions();
        cout << "\n___________________\n";

    }


public:
    static void ShowDeleteUserScreen()
    {

        _DrawScreenHeader("\tDelete User Screen");

        string UserName = "";

        do
        {
            cout << "\nPlease Enter UserName: ";
            UserName = clsInputValidate::ReadString();
            while (!clsUser::IsUserExist(UserName))
            {
                cout << "\nUser is not found, choose another one: ";
                UserName = clsInputValidate::ReadString();
            }

            if(UserName == "Admin")
            cout << "Admin cannot be deleted, Know you're size" << endl;

        }while (UserName == "Admin");

        clsUser User1 = clsUser::Find(UserName);
        _PrintUser(User1);


        if (clsInputValidate::YesOrNO("\nAre you sure you want to delete this User [y/n]? "))
        {

            if (User1.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User1);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";
            }
        }
    }

};
