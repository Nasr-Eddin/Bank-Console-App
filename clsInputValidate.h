#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include "clsDate.h"
#include <limits>
using namespace std;

class clsInputValidate
{
public:
    static char ReadChar(string Message)
    {
        cout << Message;
        char CH;
        cin >> CH;
        cin.ignore();
        return CH;
    }

    static string ReadString(string Message)
    {
        string s;
        cout << Message;
        getline(cin >> ws, s);
        return s;
    }

    static string ReadString()
    {
        string s;
        getline(cin >> ws, s);
        return s;
    }

    static bool IsNumberBetween(float num, float from, float to)
    {
        return !(num < from || num > to);
    }

    static bool IsNumberBetween(int num, int from, int to)
    {
        return !(num < from || num > to);
    }

    static bool IsNumberBetween(double num, double from, double to)
    {
        return !(num < from || num > to);
    }

    static bool IsDateBetween(clsDate Date, clsDate Compare1, clsDate Compare2)
    {
        if (Compare2.IsDateBeforeDate2(Compare1))
            Compare1.SwapDates(Compare2);

        return Date.CompareDates(Compare1) != clsDate::Before && Date.CompareDates(Compare2) != clsDate::After;
    }

    static int ReadIntNumber(string Message)
    {
        int Num;
        cout << Message;

        while (!(cin >> Num))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << Message;
        }
        cin.ignore();

        return Num;
    }

    static int ReadIntNumberBetween(int from, int to, string Message)
    {
        int Num;

        do
        {
            Num = ReadIntNumber(Message);

            if (Num < from || Num > to)
                cout << "Invalid Number, Try again\n";

        } while (Num < from || Num > to);

        return Num;
    }

    static double ReadDblNumber(string Message = "")
    {
        double Num;
        cout << Message;

        while (!(cin >> Num))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout <<  "Invald Number, Enter again:\n";
        }
        cin.ignore();

        return Num;
    }

    static double ReadDblNumberBetween(int from, int to, string Message = "Number is not within range, Enter again:\n")
    {
        double Num;

        do
        {
            cout << "Enter a number from " << from << " to " << to << " : " << endl;
            Num = ReadDblNumber("Invalid input, Try again and Enter a valid one: ");

            if (Num < from || Num > to)
                cout << Message;

        } while (Num < from || Num > to);

        return Num;
    }



    static float ReadFloatNumber(string Message = "")
    {
        float Num;
        cout << Message;

        while (!(cin >> Num))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout <<  "Invald Number, Enter again:\n";
        }
        cin.ignore();

        return Num;
    }

    static float ReadFloatNumberBetween(int from, int to, string Message = "Number is not within range, Enter again:\n")
    {
        float Num;

        do
        {
            cout << "Enter a number from " << from << " to " << to << " : " << endl;
            Num = ReadDblNumber("Invalid input, Try again and Enter a valid one: ");

            if (Num < from || Num > to)
                cout << Message;

        } while (Num < from || Num > to);

        return Num;
    }




    static bool IsValidDate(clsDate Date)
    {
        // return !(Date.Year <= 0 || Date.Month < 1 || Date.Month > 12 || Date.Day < 1 || Date.Day > clsDate::NumberOfDaysInAMonth(Date.Month, Date.Year));
        return Date.IsValid();
    }

    static bool YesOrNO(string Message)
    {
        char Choice;
        cout << Message;
        cin >> Choice;
        cin.ignore();

        return tolower(Choice) == 'y';
    }
};