#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
using namespace std;

class clsCurrencyClalculator : public clsScreen
{

private:
    static void _PrintCurrency(clsCurrency Currency, string Title = "Currency Card:")
    {
        cout << Title;
        cout << "\n_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";
    }

    static clsCurrency _GetCurrency(const string Message)
    {

        string strCode;
        cout << Message;
        strCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(strCode))
        {
            cout << "\nCurrency code doesn't exist, try again: ";
            strCode = clsInputValidate::ReadString();
        }

        return clsCurrency::FindByCode(strCode);
    }

    static float _ReadExchangeAmount()
    {
        cout << "\nEnter Amount to exchange: ";
        return clsInputValidate::ReadFloatNumber();
    }

public:
    static void ShowCurrencyCalculatorScreen()
    {

        do
        {
            _DrawScreenHeader("\tCURRENCY CALCLULATOR");

            clsCurrency C1 = _GetCurrency("Please etner Currency1 Code: ");
            clsCurrency C2 = _GetCurrency("\nPlease etner Currency2 Code: ");
            float Amount = _ReadExchangeAmount();
            
            float FinalResult = C1.ConvertToUSD(Amount);

            _PrintCurrency(C1, "\nConverting from:");

            cout << endl;

            _PrintCurrency(C2, "\nTo: ");

            FinalResult *= C2.Rate();

            cout << endl
                 << Amount << " " << C1.CurrencyCode() << " = " << FinalResult << " " << C2.CurrencyCode() << endl;

        } while (clsInputValidate::YesOrNO("\n\nDo you want to perform another claculation? [Y/N]: "));
    }
};