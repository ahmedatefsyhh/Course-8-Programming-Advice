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

enum enQuickWithdrawOptions
{
    Twenty = 1,
    Fifty = 2,
    Hundred = 3,
    TwoHun = 4,
    FourHund = 5,
    SixHund = 6,
    EightHund = 7,
    oneThou = 8,
    Exit = 9
};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
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

    cout << "Choose what do you want to do? [1 to 5] ? ";
    cin >> Choice;

    return Choice;
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowATMMainMenueScreen();
}

short ReadQuickWithdrawOption()
{
    short Choice = 0;

    cout << "Choose what do you want to do? [1 to 8] ? ";
    cin >> Choice;

    return Choice;
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

string ConvertRecordToLine(stClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
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

vector<stClient> SaveCleintsDataToFile(string FileName, vector<stClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (stClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }

    return vClients;
}

vector<stClient> LoadCleintsDataFromFile(string FileName)
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

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<stClient> &vClients)
{
    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        for (stClient &C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }
        }

        return false;
    }
}

void QuickWithDrawScreen(double Amount)
{
    stClient Client;

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = CurrentClient.AccountNumber;

    // Validate that the amount does not exceeds the balance
    while (Amount > CurrentClient.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void ShowATMMainMenueScreen();

void PerfromQuickWithdrawOption(enQuickWithdrawOptions QuickWithdrawOptions)
{
    switch (QuickWithdrawOptions)
    {
    case enQuickWithdrawOptions::Twenty:
        QuickWithDrawScreen(20);
        GoBackToMainMenue();

        break;

    case enQuickWithdrawOptions::Fifty:
        QuickWithDrawScreen(50);
        GoBackToMainMenue();

        break;

    case enQuickWithdrawOptions::Hundred:
        QuickWithDrawScreen(100);
        GoBackToMainMenue();

        break;

    case enQuickWithdrawOptions::TwoHun:
        QuickWithDrawScreen(200);
        GoBackToMainMenue();

        break;

    case enQuickWithdrawOptions::FourHund:
        QuickWithDrawScreen(400);
        GoBackToMainMenue();

        break;

    case enQuickWithdrawOptions::SixHund:
        QuickWithDrawScreen(600);
        GoBackToMainMenue();

        break;

    case enQuickWithdrawOptions::EightHund:
        QuickWithDrawScreen(800);
        GoBackToMainMenue();

        break;

    case enQuickWithdrawOptions::oneThou:
        QuickWithDrawScreen(1000);
        GoBackToMainMenue();

        break;

    case enQuickWithdrawOptions::Exit:
        ShowATMMainMenueScreen();

        break;
    }
}

vector<stClient> LoadClientsDataFromFile(string);

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

void ShowQuickWithdrawScreen()
{
    vector<stClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
    IsValidClient(CurrentClient);

    system("cls");
    cout << "===========================================\n";
    cout << "\t   Quick Withdraw Menue                  \n";
    cout << "===========================================\n";
    cout << "\t[1] 20 \t\t[2] 50                        \n";
    cout << "\t[3] 100\t\t[4] 200                       \n";
    cout << "\t[5] 400\t\t[6] 600                       \n";
    cout << "\t[7] 800\t\t[8] 1000                      \n";
    cout << "\t[9] Exit.                                \n";
    cout << "===========================================\n";
    cout << "Your Balance Is : " << CurrentClient.AccountBalance << endl;

    PerfromQuickWithdrawOption((enQuickWithdrawOptions)ReadQuickWithdrawOption());
}

void ShowNormalWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tNormal Withdraw Screen";
    cout << "\n-----------------------------------\n";

    stClient Client = CurrentClient;
    IsValidClient(CurrentClient);

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = Client.AccountNumber;

    double Amount = 0;
    cout << "\nPlease enter an amount multible of 5's ? ";
    cin >> Amount;

    while ((int(Amount) % 5) != 0)
    {
        cout << "\nPlease enter an amount multible of 5's ? ";
        cin >> Amount;
    }

    // Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    stClient Client = CurrentClient;

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = CurrentClient.AccountNumber;

    double Amount = 0;
    cout << "\nPlease enter a positive deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowCheckBalanceScreen()
{
    IsValidClient(CurrentClient);
    cout << "\n-----------------------------------\n";
    cout << "\nCheck balance Screen";
    cout << "\n-----------------------------------\n";

    cout << "Your Balance Is : " << CurrentClient.AccountBalance << endl;
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
        ShowNormalWithDrawScreen();
        GoBackToMainMenue();

        break;

    case enATM_MainMenueOptions::eDeposite:
        system("cls");
        ShowDepositScreen();
        GoBackToMainMenue();

        break;

    case enATM_MainMenueOptions::eCheckBalance:
        system("cls");
        ShowCheckBalanceScreen();
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
