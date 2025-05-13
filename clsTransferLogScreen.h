#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;



class clsTransferLogScreen : public clsScreen
{

    static void PrintLoginRegisterRecordLine(clsBankClient::stTransferRegister TransferRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(35) << left << TransferRegisterRecord.Date;
        cout << "| " << setw(20) << left << TransferRegisterRecord.SourceAccount;
        cout << "| " << setw(20) << left << TransferRegisterRecord.DestinationAccount;
        cout << "| " << setw(10) << left << TransferRegisterRecord.Amount;
        cout << "| " << setw(15) << left << TransferRegisterRecord.SourceSalary;
        cout << "| " << setw(15) << left << TransferRegisterRecord.DestinationSalary;
        cout << "| " << setw(10) << left << TransferRegisterRecord.UserName;

    }

public:

    static void ShowTransferLogScreen()
    {
        vector <clsBankClient::stTransferRegister> vTrRegisters = clsBankClient::GetTransfirLogList();

        string Title = "\tTransfer Register List Screen";
        string SubTitle =  "\t\t(" + to_string(vTrRegisters.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "S.Acct";
        cout << "| " << left << setw(20) << "D.acct";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(15) << "S.Balance";
        cout << "| " << left << setw(15) << "D.Balance";
        cout << "| " << left << setw(10) << "User";


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTrRegisters.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsBankClient::stTransferRegister Record : vTrRegisters)
            {

                PrintLoginRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


    }
};