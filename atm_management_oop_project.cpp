#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
class atmmanagement
{
public:
    virtual void print()=0;
};

class Account :public atmmanagement{

private:
    int accountNumber;
    string accountHolderName;
    int pin;
    float balance;

public:
    void print()
    {
        cout<<"welcome to our atm service"<<endl;
    }
    Account(int number, string name, int accountPin, float initialBalance) {
        accountNumber = number;
        accountHolderName = name;
        pin = accountPin;
        balance = initialBalance;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    string getAccountHolderName() {
        return accountHolderName;
    }

    int getPin() const {  // Updated: Added const qualifier
        return pin;
    }

    float getBalance() {
        return balance;
    }

    void deposit(float amount) {
        balance += amount;
    }

    bool withdraw(float amount) {
        if (amount > balance) {
            cout << "Insufficient balance." << endl;
            return false;
        } else {
            balance -= amount;
            return true;
        }
    }

    void changePin(int newPin) {
        pin = newPin;
        cout << "PIN has been changed successfully." << endl;
    }
};

class ATM {
private:
    vector<Account> accounts;
    int currentAccountIndex;
    string transactionHistoryFile;

    Account& getCurrentAccount() {//obj referrence
        return accounts[currentAccountIndex];
    }

public:
    ATM(string historyFile) {
        currentAccountIndex = -1;
        transactionHistoryFile = historyFile;
    }

    void addAccount(Account account) {
        accounts.push_back(account);
    }

    bool login(int accountNumber, int enteredPin) {
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccountNumber() == accountNumber) {
                if (verifyPIN(accounts[i], enteredPin)) {
                    currentAccountIndex = i;
                    return true;
                } else {
                    cout << "Wrong PIN. Login failed." << endl;
                    return false;
                }
            }
        }
        cout << "Invalid account number." << endl;
        return false;
    }

    bool verifyPIN(const Account& account, int enteredPin) const {  // Updated: Added const qualifier
        if (enteredPin == account.getPin()) {
            return true;
        } else {
            return false;
        }
    }

    void deposit(float amount) {
        getCurrentAccount().deposit(amount);
        cout << "Deposit successful. New balance: " << getCurrentAccount().getBalance() << endl;
    }

    bool withdraw(float amount) {
        if (getCurrentAccount().withdraw(amount)) {
            cout << "Withdrawal successful. New balance: " << getCurrentAccount().getBalance() << endl;
            return true;
        } else {
            return false;
        }
    }

    void displayAccountDetails() {
        Account account = getCurrentAccount();
        cout << "Account Number: " << account.getAccountNumber() << endl;
        cout << "Account Holder Name: " << account.getAccountHolderName() << endl;
        cout << "Balance: " << account.getBalance() << endl;
    }

    void displayTransactionHistory() {
        ifstream file(transactionHistoryFile);
        string line;

        if (file.is_open()) {
            cout << "Transaction History:" << endl;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "No transaction history available." << endl;
        }
    }

    void updateTransactionHistory(const string& transaction) {
        ofstream file(transactionHistoryFile, ios::app);
        if (file.is_open()) {
            file << transaction << endl;
            file.close();
        } else {
            cout << "Failed to update transaction history." << endl;
        }
    }

    void clearTransactionHistory() {
        ofstream file(transactionHistoryFile);
        if (file.is_open()) {
            file.close();
            cout << "Transaction history cleared." << endl;
        } else {
            cout << "Failed to clear transaction history." << endl;
        }
    }

    void changePIN() {
        int currentPin, newPin, confirmPin;
        cout << "Enter current PIN: ";
        cin >> currentPin;

        if (verifyPIN(getCurrentAccount(), currentPin)) {
            cout << "Enter new PIN: ";
            cin >> newPin;
            cout << "Confirm new PIN: ";
            cin >> confirmPin;

            if (newPin == confirmPin) {
                getCurrentAccount().changePin(newPin);
            } else {
                cout << "PIN confirmation failed. PIN not changed." << endl;
            }
        } else {
            cout << "Wrong PIN. PIN change failed." << endl;
        }
    }

    void logout() {
        currentAccountIndex = -1;
    }
};
class print
{
public:
    friend ostream & operator<<(ostream & cout,print obj)
    {
         cout << "===== ATM Management System =====" << endl;
        cout << "1. Login" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Display Account Details" << endl;
        cout << "5. Display Transaction History" << endl;
        cout << "6. Clear Transaction History" << endl;
        cout << "7. Change PIN" << endl;
        cout << "8. Logout" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
    }
};

int main() {
    ATM atm("transaction_history.txt");

    // Create and add some sample accounts
    Account account1(1001, "karim", 1234, 5000);
    Account account2(1002, "salam", 4321, 10000);
    atm.addAccount(account1);
    atm.addAccount(account2);

    int accountNumber, pin;
    bool loggedIn = false;
    int choice;
    print p;

    do {
        cout<<p;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter account number: ";
                cin >> accountNumber;
                cout << "Enter PIN: ";
                cin >> pin;
                loggedIn = atm.login(accountNumber, pin);
                if(loggedIn)
                    cout<<"successfully logged in"<<endl;
                break;
            case 2:
                if (loggedIn) {
                    float depositAmount;
                    cout << "Enter amount to deposit: ";
                    cin >> depositAmount;
                    atm.deposit(depositAmount);
                    atm.updateTransactionHistory("Deposit: " + to_string(depositAmount));
                } else {
                    cout << "Please login first." << endl;
                }
                break;
            case 3:
                if (loggedIn) {
                    float withdrawAmount;
                    cout << "Enter amount to withdraw: ";
                    cin >> withdrawAmount;
                    if (atm.withdraw(withdrawAmount)) {
                        atm.updateTransactionHistory("Withdrawal: " + to_string(withdrawAmount));
                    }
                } else {
                    cout << "Please login first." << endl;
                }
                break;
            case 4:
                if (loggedIn) {
                    atm.displayAccountDetails();
                } else {
                    cout << "Please login first." << endl;
                }
                break;
            case 5:
                if (loggedIn) {
                    atm.displayTransactionHistory();
                } else {
                    cout << "Please login first." << endl;
                }
                break;
            case 6:
                if (loggedIn) {
                    atm.clearTransactionHistory();
                } else {
                    cout << "Please login first." << endl;
                }
                break;
            case 7:
                if (loggedIn) {
                    atm.changePIN();
                } else {
                    cout << "Please login first." << endl;
                }
                break;
            case 8:
                if (loggedIn) {
                    atm.logout();
                    loggedIn = false;
                    cout << "Logout successful." << endl;
                } else {
                    cout << "Please login first." << endl;
                }
                break;
            case 9:
                cout << "Thank you for using the ATM. Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 9);

    return 0;
}
