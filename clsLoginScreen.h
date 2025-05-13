#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsUser.h"
#include "Global.h"
using namespace std;

class clsLoginScreen : public clsScreen
{

private:
    static bool _Login()
    {
        string UserName, Password;
        short Trials = 3;

        for (short trials = 2; trials >= 0; --trials)
        {

            UserName = clsInputValidate::ReadString("Enter UserName: ");
            Password = clsInputValidate::ReadString("Enter Password: ");
            CurrentUser = clsUser::Find(UserName, Password);

            if (!CurrentUser.IsEmpty())
            {
                CurrentUser.RegisterLogIn();
                clsMainScreen::ShowMainMenu();
                return true;
            }
            cout << "\nInvalid username/password.\n";
            cout << "You have " << trials << " trial(s) left.\n\n";
        }

        cout << "You're Locked after 3 trials" << endl;
        return false;

        /*
        bool LoginFailed = false;
        do
        {

        UserName = clsInputValidate::ReadString("Enter UserName: ");
              Password = clsInputValidate::ReadString("Enter Password: ");
              CurrentUser = clsUser::Find(UserName, Password);
              LoginFailed = CurrentUser.IsEmpty();

              if (LoginFailed)
              {
                  cout << "\nInvalid username/password.\n";
                  cout << "You have " << --Trials << " trials to login.\n\n";
              }

          } while (LoginFailed && Trials > 0);

          if(!LoginFailed)
          {
              clsMainScreen::ShowMainMenu();
              return true;
          }

          else
          {
              cout << "You're Locked after 3 trials" << endl;
              return false;
          } */
    }

public:
    static bool ShowLoginScreen()
    {

        std::cout << "\033[2J\033[H";
        _DrawScreenHeader("\t\tLOGIN SCREEN");
        return _Login();
    }
};