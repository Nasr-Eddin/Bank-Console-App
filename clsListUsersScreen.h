#include "clsUser.h"
#include "clsScreen.h"
#include <iostream>
using namespace std;

class clsListUsers : public clsScreen
{
private:
    static void PrintUserRecordLine(clsUser User)
    {

        cout << setw(8) << left << "";
        cout << "| " << setw(10) << left << User.UserName();
        cout << "| " << setw(12) << left << User.Phone();
        cout << "| " << setw(20) << left << User.Email();
        cout << "| " << setw(20) << left << User.FullName();
        cout << "| " << setw(12) << left << User.Password();
        cout << "| " << setw(12) << left << User.Permissions();
    }

public:
    static void ShowUsersList()
    {

        vector<clsUser> vUsers = clsUser::GetUsersList();
        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;

        cout << setw(8) << left << "";
        cout << "| " << left << setw(10) << "UserName";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Password";
        cout << "| " << left << setw(10) << "Permessions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUser& User : vUsers)
            {
                PrintUserRecordLine(User);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
    }
};