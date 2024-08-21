#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string ClientsFileName = "Clients.txt";

enum enATM_MainMenueOptions
{
    eQuickWithDraw = 1,
    eNormalWithDraw = 2,
    eDeposite = 3,
    eCheckBalance = 4,
    eLogout = 5
};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};

stClient CurrentClient;

void ShowATMMainMenueScreen();

void Login();

void ShowLoginScreen()
{
    cout << "\n____________________________________________" << endl;
    cout << "\t\tLogin Screen                             " << endl;
    cout << "____________________________________________" << endl;
}

short Read_ATM_MainMenueOption()
{
    short Choice = 0;

    cout << "Choose what do you want to do? [1 to 5]? ";
    cin >> Choice;

    return Choice;
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowATMMainMenueScreen();
}

void ShowQuickWithdrawScreen()
{
}

void PerfromATMMainMenueOption(enATM_MainMenueOptions ATM_MainMenueOption)
{
    switch (ATM_MainMenueOption)
    {
    case enATM_MainMenueOptions::eQuickWithDraw:
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToMainMenue();

        break;

    case enATM_MainMenueOptions::eNormalWithDraw:
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToMainMenue();

        break;

    case enATM_MainMenueOptions::eDeposite:
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToMainMenue();

        break;

    case enATM_MainMenueOptions::eCheckBalance:
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToMainMenue();

        break;

    case enATM_MainMenueOptions::eLogout:
        system("cls");
        Login();

        break;
    }
}

void ShowATMMainMenueScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposite.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";
    PerfromATMMainMenueOption((enATM_MainMenueOptions)Read_ATM_MainMenueOption());
}

vector<string> SplitString(string Line, string Seperator = "#//#")
{
    vector<string> vString;
    short pos;
    string sWord;

    while ((pos = Line.find(Seperator)) != Line.npos)
    {
        sWord = Line.substr(0, pos);

        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        Line.erase(0, pos + Seperator.length());
    }

    if (Line != "")
    {
        vString.push_back(Line);
    }

    return vString;
}

stClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    vector<string> vString = SplitString(Line, Seperator);

    stClient C;

    C.AccountNumber = vString[0];
    C.PinCode = vString[1];
    C.Name = vString[2];
    C.Phone = vString[3];
    C.AccountBalance = stod(vString[4]);

    return C;
}

string ConvertDataToLine(stClient Client, string Seperator = "#//#")
{
    string Line = "";

    Line += Client.AccountNumber + Seperator;
    Line += Client.PinCode + Seperator;
    Line += Client.Name + Seperator;
    Line += Client.Phone + Seperator;
    Line += Client.AccountBalance;

    return Line;
}

vector<stClient> LoadClientsDataFromFile(string FileName)
{

    vector<stClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open())
    {

        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;
}

bool IsValidClient(stClient &CurrentClient)
{
    vector<stClient> vClient = LoadClientsDataFromFile(ClientsFileName);

    for (stClient &C : vClient)
    {
        if ((C.AccountNumber == CurrentClient.AccountNumber) && (C.PinCode == CurrentClient.PinCode))
        {
            CurrentClient = C;
            return true;
        }
    }

    return false;
}

void ReadClientInfo()
{

    cout << "Enter Account Number ?" << endl;
    cin >> CurrentClient.AccountNumber;

    cout << "Enter Your pin ?" << endl;
    cin >> CurrentClient.PinCode;

    while (!IsValidClient(CurrentClient))
    {

        system("cls");
        ShowLoginScreen();

        cout << "Invalid Account Number/PinCode!" << endl;

        cout << "Enter Account Number ?" << endl;
        cin >> CurrentClient.AccountNumber;

        cout << "Enter Your pin ?" << endl;
        cin >> CurrentClient.PinCode;
    }

    ShowATMMainMenueScreen();
}

void Login()
{

    system("cls");
    ShowLoginScreen();
    ReadClientInfo();
    system("pause");
}

int main()
{
    Login();
}
