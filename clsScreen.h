#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsDate.h"
#include "Global.h"

using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        std::cout << "\033[2J\033[H";
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n";

        
        cout << "\n\t\t\t\t\t  " << "Current User: " << CurrentUser.UserName();
        cout << "\n\t\t\t\t\t  " << "Current Date: " << clsDate::DateToString(clsDate());
        cout << "\n\t\t\t\t\t______________________________________\n";
    }

    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {

        std::cout << "\033[2J\033[H";

        if (!CurrentUser.HadPermission(Permission))
        {
            cout << "\t\t\t\t\t______________________________________";
            cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
            cout << "\n\t\t\t\t\t______________________________________\n\n";
            cout << "Enter any key to go back to main menu..." << endl;
            cin.ignore();
            return false;
        }
        else
        {
            return true;
        }
    }
};
