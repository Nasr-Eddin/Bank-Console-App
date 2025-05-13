#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include <vector>
#include <fstream>

using namespace std;

class clsBankClient : public clsPerson
{
public:
    struct stTransferRegister; // Struct Declaration

private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddMode = 2,
        DeleteMode = 3
    };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool MarkForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
                             vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static vector<clsBankClient> _LoadClientsFromFileToVector(string File)
    {
        vector<clsBankClient> vClients;

        fstream FILE;
        FILE.open(File, ios::in); // Reading Mode;.
        if (FILE.is_open())
        {
            string LINE;
            while (getline(FILE, LINE))
            {
                vClients.push_back(_ConvertLinetoClientObject(LINE));
            }

            FILE.close();
        }

        return vClients;
    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName() + Seperator;
        stClientRecord += Client.LastName() + Seperator;
        stClientRecord += Client.Email() + Seperator;
        stClientRecord += Client.Phone() + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client._PinCode + Seperator;
        stClientRecord += to_string(Client._AccountBalance);

        return stClientRecord;
    }

    static void _SaveClientsVectorToFile(vector<clsBankClient> vclients)
    {
        fstream FILE("/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/Clients.txt", ios::out); // overriding mode.

        if (FILE.is_open())
        {
            for (clsBankClient &C : vclients)
            {
                if (!C.MarkForDelete)
                    FILE << _ConverClientObjectToLine(C) << endl;
            }
        }
    }

    void Update_()
    {
        vector<clsBankClient> vClients = _LoadClientsFromFileToVector("/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/Clients.txt");
        for (clsBankClient &C : vClients)
        {
            if (C.AccountNumber() == this->AccountNumber())
            {
                C = *this;
                break;
            }
        }

        _SaveClientsVectorToFile(vClients);
    }

    void _AddClient()
    {
        fstream F("/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/Clients.txt", ios::out | ios::app);

        if (F.is_open())
        {
            F << _ConverClientObjectToLine(*this) << endl;
        }
    }

    bool YesOrNO(string Message)
    {
        char Choice;
        cout << Message;
        cin >> Choice;

        return tolower(Choice) == 'y';
    }

    string _PrepareTransferLogRecord(float Amount, clsBankClient Destination, string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += _AccountNumber + Seperator;
        TransferLogRecord += Destination._AccountNumber + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(_AccountBalance) + Seperator;
        TransferLogRecord += to_string(Destination._AccountBalance) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }

    void _RegisterTransferLog(float Amount, clsBankClient Destination, string UserName)
    {
        string stDataLine = _PrepareTransferLogRecord(Amount, Destination, UserName);

        fstream FILE("TransferRegister.txt", ios::out | ios::app);

        if (FILE.is_open())
        {
            FILE << stDataLine << endl;
            FILE.close();
        }
    }

    static stTransferRegister _ConvertRegisterLineToRegisterOrder(string Line)
    {
        vector<string> vOrder = clsString::Split(Line, "#//#");

        return {vOrder[0], vOrder[1], vOrder[2], stof(vOrder[3]), stof(vOrder[4]), stof(vOrder[5]), vOrder.at(6)};
    }

public:
    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    clsBankClient() : clsPerson("", "", "", ""), _Mode(AddMode), _AccountBalance(0), _AccountNumber(""), _PinCode("")
    {
    }

    struct stTransferRegister
    {
        string Date;
        string SourceAccount;
        string DestinationAccount;
        float Amount;
        float SourceSalary;
        float DestinationSalary;
        string UserName;
    };

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }

    void SetMode(enMode Mode)
    {
        _Mode = Mode;
    }

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }

    void Deposit(double amount)
    {
        _AccountBalance += amount;
        Save();
    }

    void Withdraw(double amount)
    {
        _AccountBalance -= amount;
        Save();
    }

    /*
        !NO UI code related to any object.
    void Print()
        {
            cout << "\nClient Card:";
            cout << "\n___________________";
            cout << "\nFirstName   : " << FirstName();
            cout << "\nLastName    : " << LastName();
            cout << "\nFull Name   : " << FullName();
            cout << "\nEmail       : " << Email();
            cout << "\nPhone       : " << Phone();
            cout << "\nAcc. Number : " << _AccountNumber;
            cout << "\nPassword    : " << _PinCode;
            cout << "\nBalance     : " << _AccountBalance;
            cout << "\n___________________\n";
        } */

    static clsBankClient Find(string AccountNumber)
    {

        fstream MyFile;
        MyFile.open("/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/Clients.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client._PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    static bool IsClientExist(string AccountNumber)
    {
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    enum enSaveResults
    {
        svFailedEmptyObject,
        svSucceeded,
        svFailedAccountNumberExists
    };

    static clsBankClient CreateTheAddNewClientObject(string Account)
    {

        return clsBankClient(AddMode, "", "", "", "", Account, "", 0);
    }

    enSaveResults Save()
    {
        switch (this->_Mode)
        {
        case enMode::EmptyMode:

            // cout << "Invalid Operation, the client info is empty" << endl; //! NO UI CODE IN OBJECTS.
            return enSaveResults::svFailedEmptyObject;

        case enMode::UpdateMode:
            Update_();
            return enSaveResults::svSucceeded;

        case enMode::AddMode:
            if (IsClientExist(_AccountNumber))
                return enSaveResults::svFailedAccountNumberExists;

            // else:
            _AddClient();
            _Mode = UpdateMode; //! Set the mode to the normal state.
            return enSaveResults::svSucceeded;
        }

        return enSaveResults::svFailedEmptyObject;
    }

    bool Delete()
    {
        vector<clsBankClient> vClients = _LoadClientsFromFileToVector("/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/Clients.txt");

        for (clsBankClient &CL : vClients)
        {
            if (CL._AccountNumber == _AccountNumber)
            {
                CL.MarkForDelete = true;
                this->MarkForDelete = true;
                break;
            }
        }
        bool WasDeleted = MarkForDelete;
        if (WasDeleted)
            _SaveClientsVectorToFile(vClients);

        *this = _GetEmptyClientObject();

        return WasDeleted;
    }

    static vector<clsBankClient> GetClientsList(string File = "/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/Clients.txt")
    {
        return _LoadClientsFromFileToVector(File); // Another function to do any other options to any one outside the class.
    }

    static float GetTotalBalances()
    {
        vector<clsBankClient> vClients = _LoadClientsFromFileToVector("/home/nasr/Programming/HadhoodRoadMap/C11/Project #1/Clients.txt");
        float Sum = 0;

        for (clsBankClient &CL : vClients)
        {
            Sum += CL._AccountBalance; // You can reach any private methods of any object, with an object from the same class.
        }

        return Sum;
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Transfer(float Amount, clsBankClient &Destination, string UserName)
    {
        if (Amount > _AccountBalance || Destination._AccountNumber == _AccountNumber)
            return false;

        Withdraw(Amount);
        Destination.Deposit(Amount);
        _RegisterTransferLog(Amount, Destination, UserName);
        return true;
    }

    static vector<stTransferRegister> GetTransfirLogList()
    {
        fstream FILE("TransferRegister.txt", ios::in);

        vector<stTransferRegister> vTrRegisters;
        if (FILE.is_open())
        {
            string Line;
            stTransferRegister Register;

            while (getline(FILE, Line))
            {
                Register = _ConvertRegisterLineToRegisterOrder(Line);
                vTrRegisters.push_back(Register);
            }

            FILE.close();
        }

        return vTrRegisters;
    }
};
