#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

struct stUsers
{
    string UserName;
    string PassWord;
    short Permission;
    bool MarkForDeleteU = false;
};

stUsers CurrentUser;

void ShowMainMenue();

void ShowTransactionsMenue();

void ShowMainMenue(stUsers CurrentUser);

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable

    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length()); /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;
}

stClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    stClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]); // cast string to double

    return Client;
}

stUsers ConvertLinetoRecord_Users(string Line, string Seperator = "#//#")
{

    stUsers Users;
    vector<string> vUsersData;

    vUsersData = SplitString(Line, Seperator);

    Users.UserName = vUsersData[0];
    Users.PassWord = vUsersData[1];
    Users.Permission = stoi(vUsersData[2]); // cast string to int

    return Users;
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

string ConvertRecordToLine_Users(stUsers Users, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Users.UserName + Seperator;
    stClientRecord += Users.PassWord + Seperator;
    stClientRecord += to_string(Users.Permission);

    return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
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
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }

            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return false;
}

bool UserExistsByAccountNumber(string UserName, string FileName)
{

    vector<stUsers> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open())
    {

        string Line;
        stUsers Users;

        while (getline(MyFile, Line))
        {

            Users = ConvertLinetoRecord_Users(Line);

            if (Users.UserName == UserName)
            {
                MyFile.close();
                return true;
            }

            vUsers.push_back(Users);
        }

        MyFile.close();
    }

    return false;
}

stClient ReadNewClient()
{
    stClient Client;

    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

stUsers ReadNewUser()
{
    stUsers Users;
    char FullAccess = 'n';
    char AccessTo = 'n';

    cout << "Enter User Name? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Users.UserName);

    while (UserExistsByAccountNumber(Users.UserName, UsersFileName))
    {
        cout << "\nClient with [" << Users.UserName << "] already exists, Enter another User Name? ";
        getline(cin >> ws, Users.UserName);
    }

    cout << "Enter Password ? ";
    getline(cin >> ws, Users.PassWord);

    cout << "Do you Want to give full access  (y/n) ? ";
    cin >> FullAccess;

    if (FullAccess == 'y' || FullAccess == 'Y')
    {
        Users.Permission = -1;
    }

    else
    {
        cout << "\n\nDo you want to give access to :" << endl;
        Users.Permission = 0;

        cout << "Show Client List (y/n)?";
        cin >> AccessTo;

        if (AccessTo == 'y' || AccessTo == 'Y')
        {
            Users.Permission = 1;
        }

        cout << "Add New Client (y/n)?";
        cin >> AccessTo;

        if (AccessTo == 'y' || AccessTo == 'Y')
        {
            Users.Permission |= 2;
        }

        cout << "Delete Client (y/n)?";
        cin >> AccessTo;

        if (AccessTo == 'y' || AccessTo == 'Y')
        {
            Users.Permission |= 4;
        }

        cout << "Update Client (y/n)?";
        cin >> AccessTo;

        if (AccessTo == 'y' || AccessTo == 'Y')
        {
            Users.Permission |= 8;
        }

        cout << "Find Client (y/n)?";
        cin >> AccessTo;

        if (AccessTo == 'y' || AccessTo == 'Y')
        {
            Users.Permission |= 16;
        }

        cout << "Transactions (y/n)?";
        cin >> AccessTo;

        if (AccessTo == 'y' || AccessTo == 'Y')
        {
            Users.Permission |= 32;
        }

        cout << "Manage Users (y/n)?";
        cin >> AccessTo;

        if (AccessTo == 'y' || AccessTo == 'Y')
        {
            Users.Permission |= 64;
        }
    }

    return Users;
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

vector<stUsers> LoadUsersDataFromFile(string FileName)
{

    vector<stUsers> vUsers;

    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open())
    {

        string Line;
        stUsers Users;

        while (getline(MyFile, Line))
        {

            Users = ConvertLinetoRecord_Users(Line);

            vUsers.push_back(Users);
        }

        MyFile.close();
    }

    return vUsers;
}

void PrintClientRecordLine(stClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintUsersRecordLine(stUsers Users)
{

    cout << "| " << setw(20) << left << Users.UserName;
    cout << "| " << setw(15) << left << Users.PassWord;
    cout << "| " << setw(30) << left << Users.Permission;
}

void PrintClientRecordBalanceLine(stClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (stClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
}

void listUsersScreen()
{

    vector<stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);

    cout << "\n\t\t\t\t\tUs Users List (" << vUsers.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << "| " << left << setw(20) << "User Name";
    cout << "| " << left << setw(15) << "PassWord";
    cout << "| " << left << setw(30) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    if (vUsers.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (stUsers Users : vUsers)
        {

            PrintUsersRecordLine(Users);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
}

void ShowTotalBalances()
{

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (stClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;
}

void PrintClientCard(stClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

void PrintUserCard(stUsers User)
{
    cout << "\nThe following are the User details:\n";
    cout << "-----------------------------------";
    cout << "\nUser Name    : " << User.UserName;
    cout << "\nPassword     : " << User.PassWord;
    cout << "\nPermission   : " << User.Permission;
    cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<stClient> vClients, stClient &Client)
{

    for (stClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool FindUserByUserName(string UserName, vector<stUsers> vUsers, stUsers &User)
{

    for (stUsers U : vUsers)
    {

        if (U.UserName == UserName)
        {
            User = U;
            return true;
        }
    }
    return false;
}

stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

stUsers ChangeUserRecord(string UserName)
{
    stUsers Users;
    char FullAccess, AccessTo;

    Users.UserName = UserName;

    cout << "\n\nEnter Password? ";
    getline(cin >> ws, Users.PassWord);

    cout << "Do you Want to give full access  (y/n) ? ";
    cin >> FullAccess;

    if (FullAccess == 'y' || FullAccess == 'Y')
    {
        Users.Permission = -1;
    }

    else
    {
        cout << "\n\nDo you want to give access to :" << endl;
        Users.Permission = 0;

        cout << "Show Client List (y/n)?";
        cin >> AccessTo;

        if (AccessTo == 'y' || AccessTo == 'Y')
        {
            Users.Permission = 1;
        }

        cout << "Add New Client (y/n)?";
        cin >> AccessTo;

        if (AccessTo == 'y' || AccessTo == 'Y')
        {
            Users.Permission |= 2;
        }

        cout << "Delete Client (y/n)?";
        cin >> AccessTo;

        if (AccessTo == 'y' || AccessTo == 'Y')
        {
            Users.Permission |= 4;
        }

        cout << "Update Client (y/n)?";
        cin >> AccessTo;

        if (AccessTo == 'y' || AccessTo == 'Y')
        {
            Users.Permission |= 8;
        }

        cout << "Find Client (y/n)?";
        cin >> AccessTo;

        if (AccessTo == 'y' || AccessTo == 'Y')
        {
            Users.Permission |= 16;
        }

        cout << "Transactions (y/n)?";
        cin >> AccessTo;

        if (AccessTo == 'y' || AccessTo == 'Y')
        {
            Users.Permission |= 32;
        }

        cout << "Manage Users (y/n)?";
        cin >> AccessTo;

        if (AccessTo == 'y' || AccessTo == 'Y')
        {
            Users.Permission |= 64;
        }
    }

    return Users;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClient> &vClients)
{

    for (stClient &C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

bool MarkUserForDeleteByUserName(string UserName, vector<stUsers> &vUsers)
{

    for (stUsers &U : vUsers)
    {

        if (U.UserName == UserName)
        {
            U.MarkForDeleteU = true;

            return true;
        }
    }

    return false;
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
                // we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }

    return vClients;
}

vector<stUsers> SaveUserDataToFile(string FileName, vector<stUsers> vUsers)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (stUsers &U : vUsers)
        {

            if (U.MarkForDeleteU == false)
            {
                // we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine_Users(U);
                MyFile << DataLine << endl;
            }
        }

        MyFile.close();
    }

    return vUsers;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

void AddNewClient()
{
    stClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewUser()
{
    stUsers Users;
    Users = ReadNewUser();
    AddDataLineToFile(UsersFileName, ConvertRecordToLine_Users(Users));
}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        // system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";

        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {
        // system("cls");
        cout << "Adding New User:\n\n";

        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more User? Y/N? ";

        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient> &vClients)
{

    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            // Refresh Clients
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool DeleteUserByUserName(string UserName, vector<stUsers> &vUsers)
{

    stUsers Users;

    char Answer = 'n';
    bool Found = FindUserByUserName(UserName, vUsers, Users);

    while ((Users.Permission == -1 && Found) && (UserName != CurrentUser.UserName))
    {
        cout << "Admin Users Can't Be Daleted !, Enter another User Name ?" << endl;
        getline(cin >> ws, UserName);
        Found = FindUserByUserName(UserName, vUsers, Users);
    }

    if (Found)
    {
        PrintUserCard(Users);

        cout << "\n\nAre you sure you want delete this User? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByUserName(UserName, vUsers);
            SaveUserDataToFile(UsersFileName, vUsers);

            // Refresh Clients
            vUsers = LoadUsersDataFromFile(UsersFileName);

            cout << "\n\nUser Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with User Name (" << UserName << ") is Not Found!";

        return false;
    }
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient> &vClients)
{

    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {

            for (stClient &C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool UpdateUsersByUserName(string UserName, vector<stUsers> &vUsers)
{

    stUsers Users;

    char Answer = 'n';
    bool Found = FindUserByUserName(UserName, vUsers, Users);

    while ((Users.Permission == -1 && Found) && (UserName != CurrentUser.UserName))
    {
        cout << "Admin Users Can't Be Updated !, Enter another User Name ?" << endl;
        getline(cin >> ws, UserName);
        Found = FindUserByUserName(UserName, vUsers, Users);
    }

    if (Found)
    {
        for (stUsers &U : vUsers)
        {
            if (U.UserName == UserName)
            {
                U = ChangeUserRecord(UserName);
                break;
            }
        }

        SaveUserDataToFile(UsersFileName, vUsers);

        cout << "\n\nUser Updated Successfully.";
        return true;
    }

    else
    {
        cout << "\nUser with User Name (" << UserName << ") is Not Found!";

        return false;
    }
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

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

string ReadUserName()
{
    string UserName = "";

    cout << "\nPlease enter User Name ? ";
    cin >> UserName;

    return UserName;
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete User Screen";
    cout << "\n-----------------------------------\n";

    vector<stUsers> vUser = LoadUsersDataFromFile(UsersFileName);
    string UserName = ReadUserName();
    DeleteUserByUserName(UserName, vUser);
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate User Info Screen";
    cout << "\n-----------------------------------\n";

    vector<stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
    string UserName = ReadUserName();
    UpdateUsersByUserName(UserName, vUsers);
}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();
}

void ShowAddNewUsersScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Users Screen";
    cout << "\n-----------------------------------\n";

    AddNewUsers();
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    stClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";

    vector<stUsers> vUsers = LoadUsersDataFromFile(UsersFileName);
    stUsers Users;
    string UserName = ReadUserName();
    if (FindUserByUserName(UserName, vUsers, Users))
        PrintUserCard(Users);
    else
        cout << "\nUser with Account Number[" << UserName << "] is not found!";
}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    stClient Client;

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    stClient Client;

    vector<stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    // Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void ShowTotalBalancesScreen()
{

    ShowTotalBalances();
}

enum enTransactionsMenueOptions
{
    eDeposit = 1,
    eWithdraw = 2,
    eShowTotalBalance = 3,
    eShowMainMenue = 4
};

enum enMainMenueOptions
{
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eShowTransactionsMenue = 6,
    eManageUsers = 7,
    eLogout = 8
};

enum enManageUsersOptions
{
    eListUsers = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMenue = 6
};

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}

void GoBackToMainMenue(stUsers CurrentUser)
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue(CurrentUser);
}

void ShowManageUsersMenueScreen();

void GoBackToManageUsersMenue()
{
    cout << "\n\nPress any key to go back to Manage Users Menue ...";
    system("pause>0");
    ShowManageUsersMenueScreen();
}

void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();
}

short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eShowMainMenue:
    {

        ShowMainMenue();
    }
    }
}

void ShowTransactionsMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

short ReadMainMenueOption()
{
    short Choice = 0;
    cout << "Choose what do you want to do? [1 to 7]? ";
    cin >> Choice;

    return Choice;
}

short ReadManageUsersOption()
{
    short Choice = 0;
    cout << "Choose what do you want to do? [1 to 6]? ";
    cin >> Choice;

    return Choice;
}

void Login();

void ShowManageUsersMenueScreen();

void ShowAccessDeniedScreen();

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{

    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eShowTransactionsMenue:
        system("cls");
        ShowTransactionsMenue();
        break;

    case enMainMenueOptions::eManageUsers:
        system("cls");
        ShowManageUsersMenueScreen();
        break;

    case enMainMenueOptions::eLogout:
        system("cls");
        Login();
        break;
    }
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption, stUsers CurrentUser)
{

    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        if ((CurrentUser.Permission & 1) != 1)
            ShowAccessDeniedScreen();
        else
            ShowAllClientsScreen();

        GoBackToMainMenue(CurrentUser);
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        if ((CurrentUser.Permission & 2) != 2)
            ShowAccessDeniedScreen();
        else
            ShowAddNewClientsScreen();

        GoBackToMainMenue(CurrentUser);
        break;

    case enMainMenueOptions::eDeleteClient:
        system("cls");
        if ((CurrentUser.Permission & 4) != 4)
            ShowAccessDeniedScreen();
        else
            ShowDeleteClientScreen();

        GoBackToMainMenue(CurrentUser);
        break;

    case enMainMenueOptions::eUpdateClient:
        system("cls");
        if ((CurrentUser.Permission & 8) != 8)
            ShowAccessDeniedScreen();
        else
            ShowUpdateClientScreen();

        GoBackToMainMenue(CurrentUser);
        break;

    case enMainMenueOptions::eFindClient:
        system("cls");
        if ((CurrentUser.Permission & 16) != 16)
            ShowAccessDeniedScreen();
        else
            ShowFindClientScreen();

        GoBackToMainMenue(CurrentUser);
        break;

    case enMainMenueOptions::eShowTransactionsMenue:
        system("cls");
        if ((CurrentUser.Permission & 32) != 32)
            ShowAccessDeniedScreen();
        else
            ShowTransactionsMenue();

        GoBackToMainMenue(CurrentUser);
        break;

    case enMainMenueOptions::eManageUsers:
        system("cls");
        if ((CurrentUser.Permission & 64) != 64)
            ShowAccessDeniedScreen();
        else
            ShowManageUsersMenueScreen();

        GoBackToMainMenue(CurrentUser);

        break;

    case enMainMenueOptions::eLogout:
        system("cls");
        Login();
        break;
    }
}

void PerfromManageUsersOption(enManageUsersOptions);

void ShowManageUsersMenueScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\tManage users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User Info.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===========================================\n";
    PerfromManageUsersOption((enManageUsersOptions)ReadManageUsersOption());
}

void ShowAccessDeniedScreen()
{
    cout << "\n________________________________________________";
    cout << "\nAccess Denied,\nYou Don't Have Permission To Do This,\nPlease Contact Your Admin.\n";
    cout << "\n________________________________________________\n";
}

void PerfromManageUsersOption(enManageUsersOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enManageUsersOptions::eListUsers:
    {
        system("cls");
        listUsersScreen();
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eAddNewUser:
        system("cls");
        ShowAddNewUsersScreen();
        GoBackToManageUsersMenue();
        break;

    case enManageUsersOptions::eDeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageUsersMenue();
        break;

    case enManageUsersOptions::eUpdateUser:
        system("cls");
        ShowUpdateUserScreen();
        GoBackToManageUsersMenue();
        break;

    case enManageUsersOptions::eFindUser:
        system("cls");
        ShowFindUserScreen();
        GoBackToManageUsersMenue();
        break;

    case enManageUsersOptions::eMainMenue:
        system("cls");
        ShowMainMenue();
        break;
    }
}

void ShowMainMenue(stUsers CurrentUser)
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption(), CurrentUser);
}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

void ShowLoginScreen()
{
    cout << "\n________________________________________________";
    cout << "\n                 Login Screen                   ";
    cout << "\n________________________________________________\n";
}

vector<stUsers> LoadUsersDateFromFile(string UsersFileName, string Seperator = "#//#")
{
    fstream MyFile;
    string Line = "";
    vector<stUsers> vUsers;
    stUsers Users;

    MyFile.open(UsersFileName, ios::in);

    if (MyFile.is_open())
    {
        while (getline(MyFile, Line))
        {

            Users = ConvertLinetoRecord_Users(Line);
            vUsers.push_back(Users);
        }

        MyFile.close();
    }

    return vUsers;
}

bool IsUserValid(string UserName, string PassWord, stUsers &CurrentUser)
{
    vector<stUsers> vUsers = LoadUsersDateFromFile(UsersFileName);

    for (stUsers &v : vUsers)
    {
        if (v.UserName == UserName && v.PassWord == PassWord)
        {
            CurrentUser = v;
            return true;
        }
    }

    return false;
}

void ReadUserInfo()
{
    string UserName, Password;

    cout << "Enter User Name ? " << endl;
    getline(cin >> ws, UserName);

    cout << "Enter Password ? " << endl;
    getline(cin, Password);

    while (!IsUserValid(UserName, Password, CurrentUser))
    {
        system("cls");

        ShowLoginScreen();
        cout << "Invalid Username/Password!" << endl;

        cout << "Enter User Name ? " << endl;
        getline(cin, UserName);

        cout << "Enter Password ? " << endl;
        getline(cin, Password);
    }

    ShowMainMenue(CurrentUser);
}

void Login()
{

    system("cls");
    ShowLoginScreen();
    ReadUserInfo();
}

int main()
{
    Login();
    system("pause>0");
    return 0;
}