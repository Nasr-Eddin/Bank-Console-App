#include <iostream>
using namespace std;


class InterfaceComunication
{
public:

    virtual void SendEmail(string , string ) = 0;
    virtual void SendSMS(string, string) = 0;
};