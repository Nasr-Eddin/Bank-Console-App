#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
using namespace std;

class clsManageUsers : public clsScreen
{
    enum enManageUsers
    {
        eListUser = 1,
        eAddUser,
        eDeleteUser,
        eUpdateUser,
        eFindUser,
        eMainMenu
    };

    static enManageUsers _ReadChoice()
    {
        return (enManageUsers)clsInputValidate::ReadIntNumberBetween(1, 6, "\t\t\t\t\tEnter what do you want to do [1 -> 6] ");
    }


    static void _EnterKeyToGoBack()
    {
        cout << "\nEnter any Key to go back to Manage Users Menu....";
        cin.get();
    }

    static void _DrawManageUsersScreen()
    {

        std::cout << "\033[2J\033[H";

        _DrawScreenHeader("MANAGE USERS SCREEN");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t Manage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
    }

    static void AddUser()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void DeleteUser()
    {
        // cout << "Heeere the screen of the delete user will be shown" << endl;
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void UpdateUser()
    {

        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void FindUser()
    {
        clsFindUserScreen::ShoeFindUserScreen();
    }

    static void ListUsers()
    {
        clsListUsers::ShowUsersList();
    }

    
    static void _PerformUserChoice(enManageUsers Choice)
    {
        std::cout << "\033[2J\033[H";
        switch(Choice)
        {
            case enManageUsers::eAddUser:
            AddUser();
            break;

            case enManageUsers::eDeleteUser:
            DeleteUser();
            break;

            case enManageUsers::eFindUser:
            FindUser();
            break;

            case enManageUsers::eListUser:
            ListUsers();
            break;

            case enManageUsers::eUpdateUser:
            UpdateUser();
            break;
        }

        if(Choice != eMainMenu)
        _EnterKeyToGoBack(); 
    }

public:
    static void ShowManageUsersScreen()
    {
        enManageUsers Choice;

        do
        {
            _DrawManageUsersScreen();
            Choice = _ReadChoice();
            _PerformUserChoice(Choice);
        }while(Choice != enManageUsers::eMainMenu);
    }
};