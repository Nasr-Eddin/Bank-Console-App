#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/clsAddNewClientScreen.h"
#include <iomanip>

class clsAddNewClientScreen : public clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.SetFirstName(clsInputValidate::ReadString());
    
        cout << "\nEnter LastName: ";
        Client.SetLastName(clsInputValidate::ReadString());
    
        cout << "\nEnter Email: ";
        Client.SetEmail(clsInputValidate::ReadString());
    
        cout << "\nEnter Phone: ";
        Client.SetPhone(clsInputValidate::ReadString());
    
        cout << "\nEnter PinCode: ";
        Client.SetPinCode(clsInputValidate::ReadString());
    
        cout << "\nEnter Account Balance: ";
        Client.SetAccountBalance(clsInputValidate::ReadDblNumber());
    }

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName();
        cout << "\nLastName    : " << Client.LastName();
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email();
        cout << "\nPhone       : " << Client.Phone();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n";

    }

public:

    static void ShowAddNewClientScreen()
    {

        _DrawScreenHeader("\t  Add New Client Screen"); //From the inherited class

        string AccountNumber = "";

        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number Is Already Used, Choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);


        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case  clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Addeded Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFailedEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }
        case clsBankClient::enSaveResults::svFailedAccountNumberExists:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;

        }
        }
    }



};
