#include<iostream>
#include<fstream>
#include<iomanip>
#include <algorithm>
#include <string>
using namespace std;



class account {
    int acno;
    char name[50];
    int deposit;
    char type;
public:
    char* getName();
    void create_account_for_client();// get data from user
    void show_account_for_client() const;// show data on screen
    void modify();//add new data
    void deposit_amount_for_client(int);//accept amount and add balance amount
    void withdraw_amount_for_client(int);//accept amount subtract balance amount
    void report_for_client() const;// do a tabular format
    int return_account_for_client() const;// return account number
    int balance_enquiry_for_client() const;//return balance amount
    char return_type_for_client() const;//return type of account
    double create_account_for_Employee();// get data of Employee from user
    double show_account_for_Employee();// show data of Employee on screen
    double modify_account_for_Employee();// add new data of Employee
    double report_for_Employee();//do a tabular format for Employee
    double retacno_for_Employee();//return account number for Employee
    double return_type_for_Employee();//return type of account for Employee
    double write_account_for_Employee();	//function to write record in binary file
    double display_account_for_Employee(int);	//function to display account details given by user
    double modify_account_ST(int);	//function to modify record of file
    double delete_account_for_Employee(int);	//function to delete record of file
    double display_all_for_Employee();		//function to display all account details
    double deposit_withdraw_STT(int, int); // function to desposit/withdraw amount for given account
    double intro_for_Employee();	//introductory screen function
};
char* account::getName() {
    return name;
}
void account::create_account_for_client() {
    cout << "\nEnter The account No. :";
    cin >> acno;
    ifstream inFile("account.dat", ios::binary);
    account temp;
    bool exists = false;
    while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(account))) {
        if (temp.return_account_for_client() == acno) {
            exists = true;
            break;
        }
    }
    inFile.close();
    if (exists) {
        cout << "\nAccount with this account number already exists!\n";
        return;
    }
    cout << "\n\nEnter The Name of The account Holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nEnter Type of The account (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
    cin >> deposit;
    deposit = deposit - (deposit*5/100);
    cout << "\n\n\nAccount Created..";
}
void account::show_account_for_client() const {
    cout << "\nAccount No. : " << acno;
    cout << "\nAccount Holder Name : " << name;
    cout << "\nType of Account : " << type;
    cout << "\nBalance amount : " << deposit;
}
void account::modify() {
    cout << "\nAccount No. : " << acno;
    cout << "\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Balance amount : ";
    cin >> deposit;
}
void account::deposit_amount_for_client(int x) {
    deposit += x;
}
void account::withdraw_amount_for_client(int x) {
    deposit -= x;
}
void account::report_for_client() const {
    cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}
int account::return_account_for_client() const {
    return acno;
}
int account::balance_enquiry_for_client() const {
    return deposit;
}
char account::return_type_for_client() const {
    return type;
}

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();    //introductory screen function

void write_account() {
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account_for_client();
    outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
    outFile.close();
}
void display_sp(int n) {
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\nBALANCE DETAILS\n";

    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account))) {
        if (ac.return_account_for_client() == n) {
            ac.show_account_for_client();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nAccount number does not exist";
}
void modify_account(int n) {
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char*> (&ac), sizeof(account));
        if (ac.return_account_for_client() == n) {
            ac.show_account_for_client();
            cout << "\n\nEnter The New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}
void delete_account(int n) {
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account))) {
        if (ac.return_account_for_client() != n) {
            outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\n\tRecord Deleted ..";

}
void display_all() {
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Type  Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account))) {
        ac.report_for_client();
    }
    inFile.close();
}
void deposit_withdraw(int n, int option) {
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char*> (&ac), sizeof(account));
        if (ac.return_account_for_client() == n) {
            ac.show_account_for_client();
            if (option == 1) {
                cout << "\n\n\tTO DEPOSIT AMOUNT ";
                cout << "\n\nEnter The amount to be deposited: ";
                cin >> amt;
                ac.deposit_amount_for_client(amt);
            }
            if (option == 2) {
                cout << "\n\n\tTO WITHDRAW AMOUNT ";
                cout << "\n\nEnter The amount to be withdrawn: ";
                cin >> amt;
                int bal = ac.balance_enquiry_for_client() - amt;
                if ((bal < 500 && ac.return_type_for_client() == 'S') || (bal < 1000 && ac.return_type_for_client() == 'C'))
                    cout << "Insufficient balance";
                else
                    ac.withdraw_amount_for_client(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}
void check_account_by_name() {
    char inputName[50];
    cout << "\nEnter the name of the account holder to search: ";
    cin.ignore();
    cin.getline(inputName, 50);

    // Convert input name to lower case for case insensitive comparison
    string lowercaseInputName(inputName);
    transform(lowercaseInputName.begin(), lowercaseInputName.end(), lowercaseInputName.begin(), ::tolower);

    ifstream inFile("account.dat", ios::binary);
    account ac;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account))) {
        string accountName(ac.getName());
        // Convert account name to lower case
        transform(accountName.begin(), accountName.end(), accountName.begin(), ::tolower);

        if (accountName == lowercaseInputName) {
            cout << "Account found:\n";
            ac.show_account_for_client();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account not found for the name provided.\n";
    }

    inFile.close();
}


class EmpAccount {
    int EmpId;
    char EmpName[50];
    int EmpPassword;
    int Permissions;
public:
    EmpAccount(){
        Permissions = 1;
    }
    char* getName();
    void setPermissions(int);
    int getPermissions();
    void create_account_for_client();// get data from user
    void modify();//add new data
    void report_for_client() const;// do a tabular format
    int retid();// return account number
    int getEmpPassword();
    void show_account_for_client() const;
    double create_account_for_Employee();// get data of Employee from user
    double show_account_for_Employee();// show data of Employee on screen
    double modify_account_for_Employee();// add new data of Employee
    double report_for_Employee();//do a tabular format for Employee
    double write_account_for_Employee();	//function to write record in binary file
    double display_account_for_Employee(int);	//function to display account details given by user
    double display_all_for_Employee();		//function to display all account details
    int return_account_for_client() const;
};

int EmpAccount::retid() {
    return EmpId;
}
char* EmpAccount::getName() {
    return EmpName;
}
int EmpAccount::getEmpPassword() {
    return EmpPassword;
}
void EmpAccount::setPermissions(int n){
    Permissions = n;
}
int EmpAccount::getPermissions(){
    return Permissions;
}
void EmpAccount::report_for_client() const {
    cout << EmpId << setw(10) << " " << EmpName << endl;
}
int EmpAccount::return_account_for_client() const {
    return EmpId;
}
void EmpAccount::create_account_for_client() {
    cout << "\n\nEnter The Employee ID : ";
    cin >> EmpId;

    // Check if the employee ID already exists in the file
    ifstream inFile("employee_accounts.dat", ios::binary);
    if (inFile) {
        EmpAccount temp;
        while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(EmpAccount))) {
            if (temp.retid() == EmpId) {
                cout << "\nAccount with this ID already exists!\n";
                inFile.close();
                return;
            }
        }
        inFile.close();
    }

    cout << "\nEnter The Name of The Employee : ";
    cin.ignore();
    cin.getline(EmpName, 50);

    cout << "\nEnter The Password : ";
    cin >> EmpPassword;

    cout << "\n\n\nAccount Created..";

    // Append the new employee account to the file
    ofstream outFile("employee_accounts.dat", ios::binary | ios::app);
    outFile.write(reinterpret_cast<char*>(this), sizeof(EmpAccount));
    outFile.close();
}




void EmpAccount::show_account_for_client() const {
    cout << "\nEmployee Id : " << EmpId;
    cout << "\nEmployee Name : " << EmpName;
}
void EmpAccount::modify() {
    cout << "\nEmployee Id : " << EmpId;
    cout << "\nModify Employee Name : ";
    cin >> EmpName;
    cout << "\nModify Password : ";
    cin >> EmpPassword;
}





// prototype for employees
void write_account_employee();
void display_all_employee();
void check_account_by_name_employee();
void Edit_Permissions_for_employee();
void delete_account_for_Employee(int);
void modify_account_employee(int);
int set_permissions_employee(int);
string getNameForEmployee(int);
int getPermissionsForEmployee(int);

int getPermissionsForEmployee(int EmpId){
    ifstream infile("employee_accounts.dat");
    if (!infile) {
        cerr << "Unable to open user data file." <<endl;
        return false;
    }
    int perm;
    EmpAccount ac;
    while (infile.read(reinterpret_cast<char*>(&ac), sizeof(EmpAccount))) {
        int EmpIdStored = ac.retid();
        if (EmpId == EmpIdStored) {
            perm = ac.getPermissions();
            infile.close();
            return perm;
        }
    }
}
string getNameForEmployee(int EmpId){
    ifstream infile("employee_accounts.dat");
    if (!infile) {
        cerr << "Unable to open user data file." <<endl;
        return " ";
    }
    EmpAccount ac;
    while (infile.read(reinterpret_cast<char*>(&ac), sizeof(EmpAccount))) {
        int EmpIdStored = ac.retid();
        if (EmpId == EmpIdStored) {
            string name(ac.getName());
            infile.close();
            return name;
        }
    }
}
int set_permissions_employee(int EmpId) {
    ifstream infile("employee_accounts.dat");
    if (!infile) {
        cerr << "Unable to open user data file." <<endl;
        return false;
    }
    int select;
    EmpAccount ac;
    while (infile.read(reinterpret_cast<char*>(&ac), sizeof(EmpAccount))) {
        int EmpIdStored = ac.retid();
        int EmpPasswordStored = ac.getEmpPassword();

        if (EmpId == EmpIdStored) {
            cout << "\n\n\tSelect Permissios";
            cout << "\n\t1. EveryThing Except Modify Account";
            cout << "\n\t2. All Permissions";
            cout << "\n\n\tSelect Option (1-2) : ";
            cin >> select;
            ac.setPermissions(select);
            infile.close();
            return select;
        }
    }
    infile.close();
    return 0;

}
void modify_account_employee(int n) {
    bool found = false;
    EmpAccount ac;
    fstream File;
    File.open("employee_accounts.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char*> (&ac), sizeof(EmpAccount));
        if (ac.return_account_for_client() == n) {
            ac.show_account_for_client();
            cout << "\n\nEnter The New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(EmpAccount));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*> (&ac), sizeof(EmpAccount));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}
void delete_account_for_Employee(int n) {
    EmpAccount ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("employee_accounts.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(EmpAccount))) {
        if (ac.return_account_for_client() != n) {
            outFile.write(reinterpret_cast<char*> (&ac), sizeof(EmpAccount));
        }
    }
    inFile.close();
    outFile.close();
    remove("employee_accounts.dat");
    rename("Temp.dat", "employee_accounts.dat");
    cout << "\n\n\tRecord Deleted ..";

}

void write_account_employee() {
    EmpAccount ac;
    ofstream outFile;
    outFile.open("employee_accounts.dat", ios::binary | ios::app);
    ac.create_account_for_client();
    outFile.write(reinterpret_cast<char*> (&ac), sizeof(EmpAccount));
    outFile.close();
}
void display_all_employee() {
    EmpAccount ac;
    ifstream inFile;
    inFile.open("employee_accounts.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "==========================\n";
    cout << "Emp Id.      NAME          \n";
    cout << "==========================\n";
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(EmpAccount))) {
        ac.report_for_client();
    }
    inFile.close();
}

void check_account_by_name_employee() {
    string inputName;
    cout << "\nEnter the name of the employee to search: ";
    cin.ignore();
    getline(cin, inputName);

    // Convert input name to lower case for case insensitive comparison
    transform(inputName.begin(), inputName.end(), inputName.begin(), ::tolower);

    ifstream inFile("employee_accounts.dat", ios::binary);
    if (!inFile) {
        cout << "Unable to open file.\n";
        return;
    }

    EmpAccount ac;
    bool found = false;

    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(EmpAccount))) {
        string accountName = ac.getName();
        // Convert account name to lower case
        transform(accountName.begin(), accountName.end(), accountName.begin(), ::tolower);

        if (accountName == inputName) {
            cout << "Account found:\n";
            ac.show_account_for_client();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account not found for the name provided.\n";
    }

    inFile.close();
}


int LOG_IN_ADMIN() {
    char ch, ch_E, ch_C;
    int num;
    do {
        system("cls");
        cout << "\n\n\t1- Employee Menu";
        cout << "\n\n\t2- Customers Menu";
        cout << "\n\n\tChoice (1 or 2) : ";
        cin >> ch;
    } while (!(ch == '1' || ch == '2'));

    if (ch == '1') {
        do {
            system("cls");
            cout << "\n\n\n\tmain menu";
            cout << "\n\n\t1. Create New Account";//1
            cout << "\n\n\t2. Show All Accounts";//2
            cout << "\n\n\t3. Close Employee Account";//3
            cout << "\n\n\t4. Modify Employee's info";//4
            cout << "\n\n\t5. Edit Permissions";//5
            cout << "\n\n\t6. Search Account";//6
            cout << "\n\n\t7. EXIT";//7
            cout << "\n\n\tSelect Your Option (1-7) : ";
            cin >> ch_E;
            system("cls");
            switch (ch_E) {
                case '1':
                    write_account_employee();
                    break;
                case '2':
                    display_all_employee();
                    break;
                case '3':
                    cout << "\n\n\tEnter The Employee Id : "; cin >> num;
                    delete_account_for_Employee(num);
                    break;
                case '4':
                    cout << "\n\n\tEnter The Employee Id : "; cin >> num;
                    modify_account_employee(num);
                    break;
                case '5':
                    cout << "\n\n\tEnter The Employee Id : "; cin >> num;
                    set_permissions_employee(num);
                    break;
                case '6':
                    check_account_by_name_employee();
                    break;
                case '7':
                    break;
                default:cout << "\a";
            }
            cin.ignore();
            cin.get();

        } while (ch_E != '7');
    }
    else {
        do {
            system("cls");
            cout << "\n\n\n\tmain menu";
            cout << "\n\n\t01. New Account";
            cout << "\n\n\t02. Deposit Amount";
            cout << "\n\n\t03. Withdraw Amount";
            cout << "\n\n\t04. Balance Enquiry";
            cout << "\n\n\t05. All Acounts";
            cout << "\n\n\t06. Close An Acount";
            cout << "\n\n\t07. Modify An Account";
            cout << "\n\n\t08. Search Account";
            cout << "\n\n\t09. EXIT";
            cout << "\n\n\tSelect Your Option (1-9) : ";
            cin >> ch_C;
            system("cls");
            switch (ch_C) {
                case '1':
                    write_account();
                    break;
                case '2':
                    cout << "\n\n\tEnter The account No. : "; cin >> num;
                    deposit_withdraw(num, 1);
                    break;
                case '3':
                    cout << "\n\n\tEnter The account No. : "; cin >> num;
                    deposit_withdraw(num, 2);
                    break;
                case '4':
                    cout << "\n\n\tEnter The account No. : "; cin >> num;
                    display_sp(num);
                    break;
                case '5':
                    display_all();
                    break;
                case '6':
                    cout << "\n\n\tEnter The account No. : "; cin >> num;
                    delete_account(num);
                    break;
                case '7':
                    cout << "\n\n\tEnter The account No. : "; cin >> num;
                    modify_account(num);
                    break;
                case '8':
                    check_account_by_name();
                    system("cls");
                    break;
                case '9':
                    cout << "\n\n\tTHANKS FOR USING MMR BANK";
                    return 0;
                    break;
                default:cout << "\a";
            }
            cin.ignore();
            cin.get();
        } while (ch_C != '8');
    }
    return 0;
}


bool authenticateUser(int EmpId, int EmpPassword) {
    ifstream infile("employee_accounts.dat");
    if (!infile) {
        cerr << "Unable to open user data file." <<endl;
        return false;
    }

    EmpAccount ac;
    while (infile.read(reinterpret_cast<char*>(&ac), sizeof(EmpAccount))) {
        int EmpIdStored = ac.retid();
        int EmpPasswordStored = ac.getEmpPassword();

        if (EmpId == EmpIdStored) {
            if(EmpPassword == EmpPasswordStored){
                infile.close();
                return true;
            }
        }
    }
    infile.close();
    return false;
}

int LOG_IN_ST() {
    char ch;
    int num, EmpId, EmpPassword;
    do {
        system("cls");
        cout << "\n\n\n\tLog In";
        cout << "\n\n\tEmployee Id : ";
        cin >> EmpId;
        cout << "\n\tPassword : ";
        cin >> EmpPassword;
    } while (!authenticateUser(EmpId, EmpPassword));

    string name;
    int Permissions;
    name = getNameForEmployee(EmpId);
    Permissions = getPermissionsForEmployee(EmpId);

    do {
        system("cls");
        cout << "\n\tUser : " << name;
        cout << "\n\n\n\tmain menu";
        if(Permissions == 1){
            cout << "\n\n\t01. New Account";
            cout << "\n\n\t02. Deposit Amount";
            cout << "\n\n\t03. Withdraw Amount";
            cout << "\n\n\t04. Balance Enquiry";
            cout << "\n\n\t05. Search Account";
            cout << "\n\n\t06. EXIT";
            cout << "\n\n\tSelect Your Option (1-6) ";
        }
        else{
            cout << "\n\n\t01. New Account";
            cout << "\n\n\t02. Deposit Amount";
            cout << "\n\n\t03. Withdraw Amount";
            cout << "\n\n\t04. Balance Enquiry";
            cout << "\n\n\t05. Close An Acount";
            cout << "\n\n\t06. Modify An Account";
            cout << "\n\n\t07. Search Account";
            cout << "\n\n\t08. EXIT";
            cout << "\n\n\tSelect Your Option (1-8) ";
        }

        cin >> ch;
        system("cls");
        if(Permissions == 1){
            switch (ch) {
                case '1':
                    write_account();
                    break;
                case '2':
                    cout << "\n\n\tEnter The account No. : "; cin >> num;
                    deposit_withdraw(num, 1);
                    break;
                case '3':
                    cout << "\n\n\tEnter The account No. : "; cin >> num;
                    deposit_withdraw(num, 2);
                    break;
                case '4':
                    cout << "\n\n\tEnter The account No. : "; cin >> num;
                    display_sp(num);
                    break;
                case '5':
                    check_account_by_name();
                    cin.ignore();
                    cin.get();
                    system("cls");
                    break;
                case '6':
                    cout << "\n\n\tTHANKS FOR USING MMR BANK";
                    exit(0);
                    break;
                default:cout << "\a";
            }
        }
        else{
            switch (ch) {
                case '1':
                    write_account();
                    break;
                case '2':
                    cout << "\n\n\tEnter The account No. : "; cin >> num;
                    deposit_withdraw(num, 1);
                    break;
                case '3':
                    cout << "\n\n\tEnter The account No. : "; cin >> num;
                    deposit_withdraw(num, 2);
                    break;
                case '4':
                    cout << "\n\n\tEnter The account No. : "; cin >> num;
                    display_sp(num);
                    break;
                case '5':
                    cout << "\n\n\tEnter The account No. : "; cin >> num;
                    delete_account(num);
                    break;
                case '6':
                    cout << "\n\n\tEnter The account No. : "; cin >> num;
                    modify_account(num);
                    break;
                case '7':
                    check_account_by_name();
                    cin.ignore();
                    cin.get();
                    system("cls");
                    break;
                case '8':
                    cout << "\n\n\tTHANKS FOR USING MMR BANK";
                    exit(0);
                    break;
                default:cout << "\a";
            }
        }

        cin.ignore();
        cin.get();
    } while (ch != '7');
    return 0;
}
int LOG_IN_C() {
    char ch;
    int num;
    do {
        system("cls");
        cout << "\n\n\n\tmain menu";
        cout << "\n\n\t1. Deposit Amount";
        cout << "\n\n\t2. Withdraw Amount";
        cout << "\n\n\t3. Balance Enquiry";
        cout << "\n\n\t4. EXIT";
        cout << "\n\n\tSelect Your Option (1-4) ";
        cin >> ch;
        system("cls");
        switch (ch) {
            case '1':
                cout << "\n\n\tEnter The account No. : "; cin >> num;
                deposit_withdraw(num, 1);
                break;
            case '2':
                cout << "\n\n\tEnter The account No. : "; cin >> num;
                deposit_withdraw(num, 2);
                break;
            case '3':
                cout << "\n\n\tEnter The account No. : "; cin >> num;
                display_sp(num);
                break;
            case '4':exit(0);
            default:cout << "please enter a number between 1-6";
        }
        cin.ignore();
        cin.get();
    } while (ch != '5');
    return 0;
}
void intro()
{
    cout << "\n\n\t\t\t\t |****************************************|";
    cout << "\n\n\t\t\t\t |        Welcome To MMR Bank             |";
    cout << "\n\n\t\t\t\t |****************************************|";

    cout << "\n\t\t\t\t*______________________________________*";
    cout << "\n\n\t\t\t\t|   Designed BY :                      | ";
    cout << "\n\n\t\t\t\t|                1.Mina Mamdouh        | ";
    cout << "\n\n\t\t\t\t|                2.Menna Alrefaay      | ";
    cout << "\n\n\t\t\t\t|                3.Rawan Abd Alrahman  | ";
    cout << "\n\n\t\t\t\t|                                      | ";
    cout << "\n\n\t\t\t\t|  DR : Mahmoud Khaled                 | ";
    cout << "\n\n\t\t\t\t|  Eng : Badr Sayed                    | ";
    cout << "\n\n\t\t\t\t*______________________________________*";
    cout << "\n\n\n\t\t\t Univeristy : ERU ";

    cout << "\n\n\t\t\t\t\t\t\t\t\nPLEASE PRESS ENTER TO COUNTINE";
    cin.get();
    system("cls");
}

int main() {
    intro();
    int operation;
    int stay;
    do {
        cout <<
             "\n1-Admin"
             "\n2-Employee"
             "\n3-Clint"
             "\n4- Exit\n";
        cout << "Choose an operation: ";
        cin >> operation;
        switch (operation) {
            case 1: stay = LOG_IN_ADMIN(); break;
            case 2: LOG_IN_ST(); break;
            case 3: LOG_IN_C(); break;
            case 4: exit(0);
            default:
                cout << "Enter a valid number!\n";
        }
    } while (operation !=4 &&stay);
}