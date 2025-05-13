#include <iostream>
#include "clsInputValidate.h"
#include "clsDeposit.h"
#include "/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/clsWithdraw.h"
#include "clsScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
#include "clsTotalBalances.h"
using namespace std;

class clsTarnsactionsScreen : private clsScreen
{

private:
    enum enTransactionOptions
    {
        eDeposit = 1,
        eWithdraw,
        eTotalBalances,
        eTransfer,
        eTransferLog,
        eMainMenu
    };

    static void _GoBackToTransactionsMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        cin.ignore();
    }

    static enTransactionOptions _ReadUserOption()
    {
        enTransactionOptions Input = (enTransactionOptions)clsInputValidate::ReadIntNumberBetween(1, 6, "\t\t\t\t\tEnter what do you want to do [1 - 6]: ");

        return (enTransactionOptions)Input;
    }

    static void Deposit()
    {
        clsDepositScreen::ShowDepositScreen();
    }

    static void Withdraw()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void TotalBalances()
    {
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void Transfer()
    {
        clsTransfer::ShowTransferScreen();
    }

    static void TrnansferLogList()
    {
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void DrawTransActionsScreen()
    {
        std::cout << "\033[2J\033[H";
        _DrawScreenHeader("\t\tTransations Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\t\t Transactions\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log List.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
    }

    static void _PerfromTransactionsOption(enTransactionOptions Choice)
    {
        

        if(Choice == enTransactionOptions::eMainMenu)
        return; // Exit the function

        std::cout << "\033[2J\033[H";
        switch (Choice)
        {
        case enTransactionOptions::eDeposit:
            Deposit();
            break;

        case enTransactionOptions::eWithdraw:
            Withdraw();
            break;

        case enTransactionOptions::eTotalBalances:
            TotalBalances();
            break;

        case enTransactionOptions::eTransfer:
            Transfer();
            break;
        
        case enTransactionOptions::eTransferLog:
            TrnansferLogList();
            break;

        }

        _GoBackToTransactionsMenu();
    }

public:
    static void

    ShowTransactionsMenu()
    {
        enTransactionOptions Choice;

        do
        {
            DrawTransActionsScreen(); // main screen layout including header and menu choices
            Choice = _ReadUserOption();
            _PerfromTransactionsOption(Choice);
        } while (Choice != enTransactionOptions::eMainMenu);
    }
};
