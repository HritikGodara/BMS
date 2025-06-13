#include<iostream>
#include<string>
using namespace std;

class BankAccount {
private:
    string name;
    int accountNum;
    double balance;
    string accountType; // saving or current

public:
    BankAccount(string n, int ac, double bal, string type) {
        name = n;
        accountNum = ac;
        balance = bal;
        accountType = type;
    }

    string getName() { return name; }
    int getAccountNum() { return accountNum; }
    double getBalance() { return balance; }
    string getAccountType() { return accountType; }

    void deposit(double amount) { balance += amount; }

    void withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "\t\tWithdraw Successfully..." << endl;
        } else {
            cout << "\t\tInsufficient Balance...." << endl;
        }
    }
};

// Node for Linked List
struct Node {
    BankAccount* account;
    Node* next;

    Node(BankAccount* acc) {
        account = acc;
        next = nullptr;
    }
};

class BankManagement {
private:
    Node* head;
    static int nextAccountNum;

public:
    BankManagement() { head = nullptr; }

    int AddAccount(string name, double balance, string type) {
        int accountNum = nextAccountNum++;
        BankAccount* newAcc = new BankAccount(name, accountNum, balance, type);
        Node* newNode = new Node(newAcc);
        newNode->next = head;
        head = newNode;
        cout << "\t\tAccount Created Successfully. Account Number: " << accountNum << endl;
        return accountNum;
    }

    void showAllAccounts() {
        cout << "\t\tAll Account Holders " << endl;
        Node* temp = head;
        while (temp != nullptr) {
            cout << "Name :" << temp->account->getName()
                 << " Account Number :" << temp->account->getAccountNum()
                 << " Type :" << temp->account->getAccountType()
                 << " Balance :" << temp->account->getBalance() << endl;
            temp = temp->next;
        }
    }

    void showAccount(int accountNum) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->account->getAccountNum() == accountNum) {
                cout << "\t\tAccount Holder " << endl;
                cout << "Name :" << temp->account->getName()
                     << " Account Number :" << temp->account->getAccountNum()
                     << " Type :" << temp->account->getAccountType()
                     << " Balance :" << temp->account->getBalance() << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "\t\tAccount Not Found..." << endl;
    }

    BankAccount* findAccount(int accountNum) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->account->getAccountNum() == accountNum) {
                return temp->account;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    bool deleteAccount(int accountNum) {
        Node* temp = head;
        Node* prev = nullptr;
        while (temp != nullptr) {
            if (temp->account->getAccountNum() == accountNum) {
                if (prev == nullptr) {
                    head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                delete temp->account;
                delete temp;
                cout << "\t\tAccount Deleted Successfully." << endl;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "\t\tAccount Not Found..." << endl;
        return false;
    }
};

int BankManagement::nextAccountNum = 1001;

bool adminLogin() {
    string user, pass;
    cout << "\t\tAdmin Login\n";
    cout << "\t\tUsername: ";
    cin >> user;
    cout << "\t\tPassword: ";
    cin >> pass;
    return (user == "admin" && pass == "admin123");
}

bool clientLogin(int& accountNum) {
    cout << "\t\tClient Login\n";
    cout << "\t\tEnter Account Number: ";
    cin >> accountNum;
    return true;
}

int main() {
    BankManagement bank;
    while (true) {
        int mode;
        cout << "\n\t\tSelect Login Mode:\n";
        cout << "\t\t1. Admin\n";
        cout << "\t\t2. Client\n";
        cout << "\t\t3. Exit\n";
        cout << "\t\tEnter choice: ";
        cin >> mode;

        if (mode == 1) {
            if (!adminLogin()) {
                cout << "\t\tInvalid admin credentials!\n";
                continue;
            }
            int choice;
            do {
                cout << "\t\t::Bank Management System (Admin)" << endl;
                cout << "\t\t1. Create New Account" << endl;
                cout << "\t\t2. Show All Accounts" << endl;
                cout << "\t\t3. View Specific Account" << endl;
                cout << "\t\t4. Deposit to Account" << endl;
                cout << "\t\t5. Withdraw from Account" << endl;
                cout << "\t\t6. Delete Account" << endl;
                cout << "\t\t7. Exit Program" << endl;
                cout << "\t\t8. Back to Main Menu" << endl;
                cout << "\t\tEnter Your Choice :";
                cin >> choice;

                switch (choice) {
                    case 1: {
                        string name, type;
                        double balance;
                        cout << "\t\tEnter Name :";
                        cin.ignore();
                        getline(cin, name);
                        do {
                            cout << "\t\tEnter Account Type (saving/current): ";
                            getline(cin, type);
                        } while (type != "saving" && type != "current");
                        cout << "\t\tEnter Initial Balance :";
                        cin >> balance;
                        bank.AddAccount(name, balance, type);
                        break;
                    }
                    case 2:
                        bank.showAllAccounts();
                        break;
                    case 3: {
                        int accNum;
                        cout << "\t\tEnter Account Number: ";
                        cin >> accNum;
                        bank.showAccount(accNum);
                        break;
                    }
                    case 4: {
                        int accNum;
                        double amount;
                        cout << "\t\tEnter Account Number: ";
                        cin >> accNum;
                        BankAccount* account = bank.findAccount(accNum);
                        if (account != nullptr) {
                            cout << "\t\tEnter Amount to Deposit :";
                            cin >> amount;
                            account->deposit(amount);
                            cout << "\t\t" << amount << " Deposit Successfully ...." << endl;
                        } else {
                            cout << "\t\tAccount Not Found ..." << endl;
                        }
                        break;
                    }
                    case 5: {
                        int accNum;
                        double amount;
                        cout << "\t\tEnter Account Number: ";
                        cin >> accNum;
                        BankAccount* account = bank.findAccount(accNum);
                        if (account != nullptr) {
                            cout << "\t\tEnter Amount to withdraw :";
                            cin >> amount;
                            account->withdraw(amount);
                        } else {
                            cout << "\t\tAccount Not Found ..." << endl;
                        }
                        break;
                    }
                    case 6: {
                        int accNum;
                        cout << "\t\tEnter Account Number to Delete: ";
                        cin >> accNum;
                        bank.deleteAccount(accNum);
                        break;
                    }
                    case 7:
                        exit(0);
                    case 8:
                        break;
                    default:
                        cout << "\t\tInvalid choice!\n";
                }
            } while (choice != 8);
        }
        // ... (client section remains unchanged)
        else if (mode == 2) {
            int clientAccountNum;
            if (!clientLogin(clientAccountNum)) {
                cout << "\t\tInvalid client credentials!\n";
                continue;
            }
            int choice;
            do {
                cout << "\t\t::Bank Management System (Client)" << endl;
                cout << "\t\t1. View Account" << endl;
                cout << "\t\t2. Deposit Money" << endl;
                cout << "\t\t3. Withdraw Money" << endl;
                cout << "\t\t4. Exit Program" << endl;
                cout << "\t\t5. Back to Main Menu" << endl;
                cout << "\t\tEnter Your Choice :";
                cin >> choice;

                switch (choice) {
                    case 1:
                        bank.showAccount(clientAccountNum);
                        break;
                    case 2: {
                        double amount;
                        BankAccount* account = bank.findAccount(clientAccountNum);
                        if (account != nullptr) {
                            cout << "\t\tEnter Amount to Deposit :";
                            cin >> amount;
                            account->deposit(amount);
                            cout << "\t\t" << amount << " Deposit Successfully ...." << endl;
                        } else {
                            cout << "\t\tAccount Not Found ..." << endl;
                        }
                        break;
                    }
                    case 3: {
                        double amount;
                        BankAccount* account = bank.findAccount(clientAccountNum);
                        if (account != nullptr) {
                            cout << "\t\tEnter Amount to withdraw :";
                            cin >> amount;
                            account->withdraw(amount);
                        } else {
                            cout << "\t\tAccount Not Found ..." << endl;
                        }
                        break;
                    }
                    case 4:
                        exit(0);
                    case 5:
                        break;
                    default:
                        cout << "\t\tInvalid choice!\n";
                }
            } while (choice != 5);
        } else if (mode == 3) {
            break;
        } else {
            cout << "\t\tInvalid mode selected!\n";
        }
    }
    return 0;
}