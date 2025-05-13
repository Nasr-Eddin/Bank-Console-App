#include <iostream>
#include "clsLoginScreen.h"
#include "Global.h"
using namespace std;

int main()
{
    while (clsLoginScreen::ShowLoginScreen())
        continue;
    return 0;
}