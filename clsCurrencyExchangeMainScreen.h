#include <iostream>
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
using namespace std;

class clsCurrenceExchangeScreen : private clsScreen
{

private:
    enum enCurrencyExchangeOnptions
    {
        eListCurrency = 1,
        eFindCrrency,
        eUpdateRate,
        eCurrencyCalculator,
        eMainMenu
    };

    static void _GoBackToCurrencyExchangeMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        cin.ignore();
    }

    static enCurrencyExchangeOnptions _ReadUserOption()
    {
        enCurrencyExchangeOnptions Input = (enCurrencyExchangeOnptions)clsInputValidate::ReadIntNumberBetween(1, 5, "\t\t\t\t\tEnter what do you want to do [1 - 5]: ");

        return (enCurrencyExchangeOnptions)Input;
    }

    static void ListCurrency()
    {
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void FindCurrency()
    {
        // cout << "Find Currency will appear hear :)" << endl;
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void UpdateRate()
    {
        // cout << "Update Rate will appear hear :)" << endl;
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void CurrencyCalculator()
    {
        // cout << "Currency Claculator will appear hear :)" << endl;
        clsCurrencyClalculator::ShowCurrencyCalculatorScreen();
    }

    static void DrawCurrencyExchangScreen()
    {
        std::cout << "\033[2J\033[H";
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t Currency Exchange Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency  Caclulator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
    }

    static void _PerfromCurrencyExchangeOption(enCurrencyExchangeOnptions Choice)
    {
        

        if(Choice == enCurrencyExchangeOnptions::eMainMenu)
        return; // Exit the function

        std::cout << "\033[2J\033[H";
        switch (Choice)
        {
        case enCurrencyExchangeOnptions::eListCurrency:
            ListCurrency();
            break;

        case enCurrencyExchangeOnptions::eFindCrrency:
            FindCurrency();
            break;

        case enCurrencyExchangeOnptions::eUpdateRate:
            UpdateRate();
            break;

        case enCurrencyExchangeOnptions::eCurrencyCalculator:
            CurrencyCalculator();
            break;
        
        }

        _GoBackToCurrencyExchangeMenu();
    }

public:
    static void ShowCurrencyExchangeMenu()
    {
        enCurrencyExchangeOnptions Choice;

        do
        {
            DrawCurrencyExchangScreen(); // main screen layout including header and menu choices
            Choice = _ReadUserOption();
            _PerfromCurrencyExchangeOption(Choice);
        } while (Choice != enCurrencyExchangeOnptions::eMainMenu);
    }
};