#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

class clsTransfer : public clsScreen
{
    struct stTransferRegister
    {
        string Date;
        clsBankClient Source;
        clsBankClient Destination;
        float Amount;
    };

    static void ShortInfo_(clsBankClient Client)
    {
        cout << "\nClient card" << endl;
        cout << "___________________\n";
        cout << "Full Name    : " << Client.FullName() << endl;
        cout << "Acc. Number  : " << Client.AccountNumber() << endl;
        cout << "Total Balance: " << Client.GetAccountBalance() << endl;
    }

    static string ReadAccount(string TheWay)
    {
        string Account = clsInputValidate::ReadString("\nPlease enter the account you want to transfer " + TheWay + " : ");
        while (!clsBankClient::IsClientExist(Account))
        {
            cout << "Invalid account, Enter a valid one\n";
            Account = clsInputValidate::ReadString("\nPlease enter the account you want to transfer " + TheWay + " : ");
        }

        return Account;
    }

    static double ReadAmount(clsBankClient &Source)
    {
        cout << "\nEnter the transfer amount" << endl;
        double TransferAmount = clsInputValidate::ReadDblNumber();
        while (TransferAmount > Source.GetAccountBalance())
        {
            cout << "Transfer amount exceeds the balance, You can transfer till " << Source.GetAccountBalance() << endl;
            cout << "\nEnter the transfer amount" << endl;
            TransferAmount = clsInputValidate::ReadDblNumber();
        }

        return TransferAmount;
    }


public:
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\tTRANSFER SCREEN");

        stTransferRegister Transfer;
        Transfer.Source = clsBankClient::Find(ReadAccount("From"));
        ShortInfo_(Transfer.Source);

        Transfer.Destination = clsBankClient::Find(ReadAccount("to"));
        while (Transfer.Destination.AccountNumber() == Transfer.Source.AccountNumber())
        {
            cout << "\nError, You cant transfer to the same account\n";
            Transfer.Destination = clsBankClient::Find(ReadAccount("to"));
        }
        ShortInfo_(Transfer.Destination);
        Transfer.Amount = ReadAmount(Transfer.Source);

        if (!clsInputValidate::YesOrNO("Are you sure you want to complete this transfer? [Y/N]: "))
        {
            cout << "\n\nOperation Denied.. ):" << endl;
        }

        else if (Transfer.Source.Transfer(Transfer.Amount, Transfer.Destination, CurrentUser.UserName()))
        {
            cout << "Operation done successfully :)" << endl;
            ShortInfo_(Transfer.Source);
            ShortInfo_(Transfer.Destination);
        }
        else
            cout << "\n\nOPeration Failed ):" << endl;
    }
};