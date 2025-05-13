#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFIndClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsers.h"
#include "clsUser.h"
#include "cmath"
#include "clsLoginRegister.h"
#include "clsCurrencyExchangeMainScreen.h"
#include "Global.h"
#include <iomanip>

using namespace std;

class clsMainScreen : public clsScreen
{

private:
    enum enMainMenueOptions
    {
        eListClients = 1,
        eAddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClient = 4,
        eFindClient = 5,
        eShowTransactionsMenue = 6,
        eManageUsers = 7,
        eLoginRegisters = 8,
        enCcurrencyExchange = 9,
        eExit = 10
    };

    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Choice = clsInputValidate::ReadIntNumberBetween(1, 10, " ");
        return Choice;
    }

    static void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        cin.ignore();
        // ShowMainMenue();
    }

    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClient::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        clsTarnsactionsScreen::ShowTransactionsMenu();
    }

    static void _ShowManageUsersMenue()
    {
        clsManageUsers::ShowManageUsersScreen();
    }

    static void _ShowLoginRegistersMenu()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeScreen()
    {
        clsCurrenceExchangeScreen::ShowCurrencyExchangeMenu();
    }

    static void _Logout()
    {
        // cout << "\nEnd Screen Will be here...\n";
        CurrentUser = clsUser::Find("", "");
        // _GoBackToMainMenue();
    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {

        std::cout << "\033[2J\033[H";

        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
            _ShowAllClientsScreen();
            break;

        case enMainMenueOptions::eAddNewClient:
            _ShowAddNewClientsScreen();
            break;

        case enMainMenueOptions::eDeleteClient:
            _ShowDeleteClientScreen();
            break;

        case enMainMenueOptions::eUpdateClient:
            _ShowUpdateClientScreen();
            break;

        case enMainMenueOptions::eFindClient:
            _ShowFindClientScreen();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            _ShowTransactionsMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            _ShowManageUsersMenue();
            break;

        case enMainMenueOptions::eLoginRegisters:
            _ShowLoginRegistersMenu();
            break;

        case enMainMenueOptions::enCcurrencyExchange:
            _ShowCurrencyExchangeScreen();
            break;

        case enMainMenueOptions::eExit:
            _Logout();
            break;
        }

        if (MainMenueOption != enMainMenueOptions::eExit && MainMenueOption != eManageUsers && MainMenueOption != eShowTransactionsMenue)
            _GoBackToMainMenue();
    }

    static void _DrawMainMenuScreen()
    {
        std::cout << "\033[2J\033[H";
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Registers.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";
    }

public:
    /*     static void ShowMainMenu(clsUser &User)
        {
            enMainMenueOptions Choice;

            do
            {
                _DrawMainMenuScreen(); // main screen layout including header and menu choices
                Choice = (enMainMenueOptions)_ReadMainMenueOption();
                if (Choice == eExit)
                    break;
                if (clsUser::HasPermission((short)Choice, User.Permissions()))
                    _PerfromMainMenueOption(Choice);

                else
                {
                    std::cout << "\033[2J\033[H";
                    cout << "You don't have this permission. Contatct your admin" << endl;
                    _GoBackToMainMenue();
                }

            } while (true);
        }
*/

    static void ShowMainMenu()
    {
        enMainMenueOptions Choice;
        clsUser::enPermissions BinaryChoice;

        do
        {
            _DrawMainMenuScreen(); // main screen layout including header and menu choices
            Choice = (enMainMenueOptions)_ReadMainMenueOption();
            BinaryChoice = (clsUser::enPermissions)pow(2, Choice - 1);

            if (Choice == eExit)
                _PerfromMainMenueOption(eExit); // Any user can logout without any permessions :)

            else if (clsScreen::CheckAccessRights(BinaryChoice)) // Current user is a global clsUser object
                _PerfromMainMenueOption(Choice);

        } while (Choice != enMainMenueOptions::eExit);
    }


};
