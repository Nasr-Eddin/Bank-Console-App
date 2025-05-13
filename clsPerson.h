#pragma once
#include <iostream>
using namespace std;


class clsPerson
{
private:

    string FirstName_;
    string LastName_;
    string Email_;
    string Phone_;

public:

    clsPerson(string F, string L, string E, string P) : FirstName_(F), LastName_(L), Email_(E), Phone_(P) {};

    
    string FirstName()
    {
        return FirstName_;
    }

    void SetFirstName(string set)
    {
        FirstName_ = set;
    }

    string LastName()
    {
        return LastName_;
    }

    void SetLastName(string set)
    {
        LastName_ = set;
    }

    string Phone()
    {
        return Phone_;
    }

    void SetPhone(string set)
    {
        Phone_ = set;
    }

    string Email()
    {
        return Email_;
    }

    void SetEmail(string set)
    {
        Email_ = set;
    }


    void Print()
    {
        cout << "INFO....\n";
        cout << "______________________________________\n";
        cout << "First Name: " << FirstName_ << endl;
        cout << "Last Name: " << LastName_ << endl;
        cout << "Email    : " << Email_ << endl;
        cout << "Phone    : " << Phone_ << endl;
        cout << "______________________________________\n";
    }

    string FullName()
    {
        return FirstName_ + " " + LastName_;
    }
};