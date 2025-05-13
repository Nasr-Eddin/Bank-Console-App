#pragma once
#include <iostream>
#include "/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
using namespace std;

class clsFindUserScreen : public clsScreen
{
private:
    static void _PrintUser(clsUser &User)
    {
        cout << "\nClient Card:";
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

public:
    static void ShoeFindUserScreen()
    {
        _DrawScreenHeader("\tFIND USER SCREEN");

        cout << "\nEnter the User Name you want to Update: ";
        string UN = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UN))
        {
            if (!clsInputValidate::YesOrNO("User Name is not exist, Wanna try again? [Y/N]: "))
                return;

            cout << "\nEnter the User Name you want to Update: ";
            UN = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UN);

        if(User1.IsEmpty())
        cout << "Not Found ):" << endl;
        else
        cout << "Hoorray!, The User has been found :)" << endl;


        _PrintUser(User1);
    }
};