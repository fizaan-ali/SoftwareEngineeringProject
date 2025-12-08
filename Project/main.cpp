/*
    SMART BANK MANAGEMENT SYSTEM (C++)

    Features:
    - Object Oriented Design (Account, User, Admin, Customer, BankSystem)
    - Inheritance & Polymorphism (User -> Admin, Customer)
    - Templates (Repository<T>)
    - File Handling (accounts.db for persistent accounts)
    - Exception Handling (withdraw with runtime_error / invalid_argument)
    - Input Validation (no crash on wrong input)
    - Transaction Log (in memory, mini-statement)
    - Admin & Customer Menus
    - Console formatting using <iomanip> and custom banner functions

    Admin Login:
        username: admin
        password: 1234
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <cctype>
#include <iomanip>
using namespace std;

class BankSystem; // forward declaration

// ======================================================================
//                     GLOBAL CONSOLE LAYOUT SETTINGS
// ======================================================================

const int SCREEN_WIDTH = 70;   // change this if your terminal is wider/narrower

void printLine(char ch = '=') {
    cout << string(SCREEN_WIDTH, ch) << "\n";
}

void printCentered(const string& text) {
    if ((int)text.size() >= SCREEN_WIDTH) {
        cout << text << "\n";
        return;
    }
    int padding = (SCREEN_WIDTH - (int)text.size()) / 2;
    cout << string(padding, ' ') << text << "\n";
}

void printBanner(const string& title) {
    printLine('=');
    printCentered(title);
    printLine('=');
}

// ======================================================================
//                       INPUT HELPER FUNCTIONS
// ======================================================================

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Invalid input. Please enter a whole number.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

long readLong(const string& prompt) {
    long value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Invalid input. Please enter digits only.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double readDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "Invalid input. Please enter a valid amount.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string readName(const string& prompt) {
    while (true) {
        cout << prompt;
        string name;
        getline(cin, name);

        if (name.empty()) {
            cout << "Name cannot be empty.\n\n";
            continue;
        }

        bool ok = true;
        for (char c : name) {
            if (!(isalpha(static_cast<unsigned char>(c)) ||
                  isspace(static_cast<unsigned char>(c)))) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            cout << "Invalid name. Please use only letters and spaces.\n\n";
            continue;
        }

        return name;
    }
}

string readCnic(const string& prompt) {
    while (true) {
        cout << prompt;
        string cnic;
        getline(cin, cnic);

        if (cnic.empty()) {
            cout << "CNIC cannot be empty.\n\n";
            continue;
        }

        bool ok = true;
        for (char c : cnic) {
            if (!isdigit(static_cast<unsigned char>(c))) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            cout << "Invalid CNIC. Please enter digits only (no letters/symbols).\n\n";
            continue;
        }

        return cnic;
    }
}

int readPin(const string& prompt) {
    while (true) {
        int pin = readInt(prompt);
        if (pin < 0 || pin > 9999) {
            cout << "Invalid PIN. It should be between 0000 and 9999.\n\n";
            continue;
        }
        return pin;
    }
}

// ======================================================================
//                            ACCOUNT CLASS
// ======================================================================

class Account {
private:
    long   accountNo;
    string holderName;
    string cnic;
    double balance;
    int    pin;
    bool   isActive;

    static long nextAccountNo;

public:
    Account()
        : accountNo(0), holderName(""), cnic(""),
          balance(0.0), pin(0), isActive(false) {}

    Account(const string& name, const string& cnic,
            double initialBalance, int pin)
        : holderName(name), cnic(cnic), balance(initialBalance),
          pin(pin), isActive(true)
    {
        if (balance < 0) balance = 0;
        accountNo = nextAccountNo++;
    }

    long   getAccountNo() const { return accountNo; }
    string getName()      const { return holderName; }
    string getCNIC()      const { return cnic; }
    double getBalance()   const { return balance; }
    bool   getStatus()    const { return isActive; }

    bool checkPin(int p) const {
        return isActive && (p == pin);
    }

    void deposit(double amt) {
        if (!isActive) {
            cout << "Account is closed. Deposit not allowed.\n";
            return;
        }
        if (amt <= 0) {
            cout << "Amount must be positive.\n";
            return;
        }
        balance += amt;
        cout << "Deposit successful.\n";
    }

    void ensureCanWithdraw(double amt) const {
        if (!isActive) {
            throw runtime_error("Account is closed.");
        }
        if (amt <= 0) {
            throw invalid_argument("Amount must be positive.");
        }
        if (balance < amt) {
            throw runtime_error("Insufficient funds.");
        }
    }

    bool withdraw(double amt) {
        try {
            ensureCanWithdraw(amt);
            balance -= amt;
            cout << "Withdrawal successful.\n";
            return true;
        } catch (const exception& ex) {
            cout << "Withdrawal failed: " << ex.what() << "\n";
            return false;
        }
    }

    void close() {
        isActive = false;
        cout << "Account has been closed.\n";
    }

    void print() const {
        printLine('-');
        cout << left << setw(12) << "Account #:" << accountNo  << "\n";
        cout << left << setw(12) << "Name:"      << holderName << "\n";
        cout << left << setw(12) << "CNIC:"      << cnic       << "\n";
        cout << left << setw(12) << "Balance:"   << balance    << "\n";
        cout << left << setw(12) << "Status:"    << (isActive ? "Active" : "Closed") << "\n";
        printLine('-');
    }

    string serialize() const {
        string safeName = holderName;
        for (char& c : safeName) {
            if (isspace(static_cast<unsigned char>(c))) c = '_';
        }
        return to_string(accountNo) + " " + safeName + " " + cnic + " " +
               to_string(balance) + " " + to_string(pin) + " " +
               (isActive ? "1" : "0");
    }

    friend class BankSystem;
};

long Account::nextAccountNo = 1000;

ostream& operator<<(ostream& out, const Account& acc) {
    out << "Account #" << acc.getAccountNo()
        << " | " << acc.getName()
        << " | Balance: " << acc.getBalance();
    return out;
}

// ======================================================================
//                         TRANSACTION CLASS
// ======================================================================

class Transaction {
public:
    long   id;
    long   fromAcc;
    long   toAcc;
    double amount;
    string type;
    string time;

    Transaction()
        : id(0), fromAcc(-1), toAcc(-1), amount(0.0),
          type("UNKNOWN"), time("N/A") {}

    Transaction(long id, long f, long t, double amt,
                const string& type, const string& time)
        : id(id), fromAcc(f), toAcc(t), amount(amt),
          type(type), time(time) {}
};

ostream& operator<<(ostream& out, const Transaction& tr) {
    out << "[" << tr.id << "] "
        << tr.type << " | Amt: " << tr.amount
        << " | From: " << tr.fromAcc
        << " | To: " << tr.toAcc
        << " | Time: " << tr.time;
    return out;
}

// ======================================================================
//                       TEMPLATE REPOSITORY<T>
// ======================================================================

template <typename T>
class Repository {
private:
    vector<T> items;

public:
    void add(const T& item)         { items.push_back(item); }
    size_t size() const             { return items.size(); }
    vector<T>&       getAll()       { return items; }
    const vector<T>& getAll() const { return items; }
};

// ======================================================================
//                         USER BASE CLASS
// ======================================================================

class User {
protected:
    int    id;
    string name;
    string username;
    string password;

public:
    User() : id(0), name(""), username(""), password("") {}

    User(int id, const string& name,
         const string& username, const string& password)
        : id(id), name(name), username(username), password(password) {}

    virtual ~User() {}

    virtual void showMenu(BankSystem& system) = 0;
};

class Admin;
class Customer;

// ======================================================================
//                           BANKSYSTEM CLASS
// ======================================================================

class BankSystem {
private:
    Repository<Account>     accounts;
    Repository<Transaction> transactions;
    string accountsFile;
    long   nextTransactionId;

public:
    BankSystem(const string& file = "accounts.db")
        : accountsFile(file), nextTransactionId(1)
    {
        loadFromFile();
    }

    void saveToFile() {
        ofstream out(accountsFile);
        if (!out) {
            cout << "Error opening file for saving.\n";
            return;
        }
        for (const auto& acc : accounts.getAll()) {
            out << acc.serialize() << "\n";
        }
    }

    void loadFromFile() {
        accounts.getAll().clear();
        ifstream in(accountsFile);
        if (!in) {
            // silently start with empty bank; no "empty db" message
            return;
        }

        long   accNo;
        string safeName;
        string cnic;
        double balance;
        int    pin;
        int    activeFlag;
        long   maxAccNo = 999;

        while (in >> accNo >> safeName >> cnic >> balance >> pin >> activeFlag) {
            string realName = safeName;
            for (char& c : realName) {
                if (c == '_') c = ' ';
            }

            Account acc(realName, cnic, balance, pin);
            acc.accountNo = accNo;
            acc.isActive  = (activeFlag == 1);

            if (accNo > maxAccNo) maxAccNo = accNo;

            accounts.add(acc);
        }
        in.close();

        Account::nextAccountNo = maxAccNo + 1;
        cout << "Loaded " << accounts.size() << " account(s) from file.\n";
    }

    Account* createAccount(const string& name, const string& cnic,
                           double bal, int pin) {
        Account acc(name, cnic, bal, pin);
        accounts.add(acc);
        saveToFile();
        cout << "Account created successfully.\n";
        return &accounts.getAll().back();
    }

    Account* findAccount(long accNo) {
        for (auto& acc : accounts.getAll()) {
            if (acc.getAccountNo() == accNo) return &acc;
        }
        return nullptr;
    }

    void listAccounts() const {
        const auto& all = accounts.getAll();
        if (all.empty()) {
            cout << "No accounts found.\n";
            return;
        }
        printBanner("ALL ACCOUNTS");
        for (const auto& acc : all) {
            acc.print();
        }
    }

    bool deposit(long accNo, double amt) {
        Account* acc = findAccount(accNo);
        if (!acc) {
            cout << "Account not found.\n";
            return false;
        }
        acc->deposit(amt);
        logTransaction(-1, accNo, amt, "DEPOSIT");
        saveToFile();
        return true;
    }

    bool withdraw(long accNo, double amt) {
        Account* acc = findAccount(accNo);
        if (!acc) {
            cout << "Account not found.\n";
            return false;
        }
        bool ok = acc->withdraw(amt);
        if (ok) {
            logTransaction(accNo, -1, amt, "WITHDRAW");
            saveToFile();
        }
        return ok;
    }

    bool transfer(long fromAcc, long toAcc, double amt) {
        Account* from = findAccount(fromAcc);
        Account* to   = findAccount(toAcc);
        if (!from || !to) {
            cout << "One or both accounts not found.\n";
            return false;
        }
        if (!from->withdraw(amt)) {
            cout << "Transfer failed.\n";
            return false;
        }
        to->deposit(amt);
        logTransaction(fromAcc, toAcc, amt, "TRANSFER");
        saveToFile();
        cout << "Transfer successful.\n";
        return true;
    }

    void miniStatement(long accNo) const {
        const auto& all = transactions.getAll();
        printBanner("MINI STATEMENT");
        cout << "Account #" << accNo << "\n";
        printLine('-');
        int count = 0;
        for (int i = (int)all.size() - 1; i >= 0 && count < 5; --i) {
            if (all[i].fromAcc == accNo || all[i].toAcc == accNo) {
                cout << all[i] << "\n";
                ++count;
            }
        }
        if (count == 0) cout << "No transactions.\n";
    }

    Account* customerLogin(long accNo, int pin) {
        Account* acc = findAccount(accNo);
        if (!acc) {
            cout << "No account with that number exists.\n";
            return nullptr;
        }
        if (acc->checkPin(pin)) {
            cout << "Login successful.\n";
            return acc;
        }
        cout << "Wrong PIN.\n";
        return nullptr;
    }

    bool adminLogin(const string& user, const string& pass) const {
        return (user == "admin" && pass == "1234");
    }

private:
    void logTransaction(long fromAcc, long toAcc,
                        double amt, const string& type) {
        Transaction t(nextTransactionId++, fromAcc, toAcc, amt, type, "N/A");
        transactions.add(t);
    }
};

// ======================================================================
//                       ADMIN & CUSTOMER CLASSES
// ======================================================================

class Admin : public User {
public:
    Admin() {}

    Admin(int id, const string& name,
          const string& username, const string& password)
        : User(id, name, username, password) {}

    void showMenu(BankSystem& system) override;
};

class Customer : public User {
private:
    long accountNo;

public:
    Customer() : User(), accountNo(-1) {}

    Customer(int id, const string& name,
             const string& username, const string& password,
             long accNo)
        : User(id, name, username, password), accountNo(accNo) {}

    void showMenu(BankSystem& system) override;
};

// ======================================================================
//                      ADMIN MENU IMPLEMENTATION
// ======================================================================
void Admin::showMenu(BankSystem& system) {
    int ch = -1;
    while (ch != 0) {
        printBanner("ADMIN MENU");
        printCentered("1. Create Account");
        printCentered("2. View All Accounts");
        printCentered("3. Deposit");
        printCentered("4. Withdraw");
        printCentered("5. Transfer");
        printCentered("6. Mini Statement");
        printCentered("0. Logout");
        cout << "\n";

        ch = readInt("Enter your choice: ");

        switch (ch) {
        case 1: {
            string name = readName("Enter account holder name: ");
            string cnic = readCnic("Enter CNIC (digits only): ");
            double bal  = readDouble("Enter initial balance: ");
            int    pin  = readPin("Set 4-digit PIN (0000-9999): ");

            Account* acc = system.createAccount(name, cnic, bal, pin);
            cout << "\nAccount created successfully. Details:\n";
            acc->print();
            break;
        }
        case 2:
            system.listAccounts();
            break;

        case 3: {
            long   accNo = readLong("Enter account number: ");
            double amt   = readDouble("Enter amount to deposit: ");
            system.deposit(accNo, amt);
            break;
        }
        case 4: {
            long   accNo = readLong("Enter account number: ");
            double amt   = readDouble("Enter amount to withdraw: ");
            system.withdraw(accNo, amt);
            break;
        }
        case 5: {
            long   from = readLong("From account number: ");
            long   to   = readLong("To account number: ");
            double amt  = readDouble("Enter amount to transfer: ");
            system.transfer(from, to, amt);
            break;
        }
        case 6: {
            long accNo = readLong("Enter account number: ");
            system.miniStatement(accNo);
            break;
        }
        case 0:
            cout << "Logging out admin.\n";
            break;

        default:
            cout << "Invalid choice. Please select a valid option.\n";
        }
    }
}

// ======================================================================
//                     CUSTOMER MENU IMPLEMENTATION
// ======================================================================
void Customer::showMenu(BankSystem& system) {
    int ch = -1;
    while (ch != 0) {
        string title = "CUSTOMER MENU (Account #" + to_string(accountNo) + ")";
        printBanner(title);
        printCentered("1. View Account");
        printCentered("2. Deposit");
        printCentered("3. Withdraw");
        printCentered("4. Transfer");
        printCentered("5. Mini Statement");
        printCentered("0. Logout");
        cout << "\n";

        ch = readInt("Enter your choice: ");

        switch (ch) {
        case 1: {
            Account* acc = system.findAccount(accountNo);
            if (acc) acc->print();
            else cout << "Account not found.\n";
            break;
        }
        case 2: {
            double amt = readDouble("Enter amount to deposit: ");
            system.deposit(accountNo, amt);
            break;
        }
        case 3: {
            double amt = readDouble("Enter amount to withdraw: ");
            system.withdraw(accountNo, amt);
            break;
        }
        case 4: {
            long   to  = readLong("Enter target account number: ");
            double amt = readDouble("Enter amount to transfer: ");
            system.transfer(accountNo, to, amt);
            break;
        }
        case 5:
            system.miniStatement(accountNo);
            break;

        case 0:
            cout << "Logging out customer.\n";
            break;

        default:
            cout << "Invalid choice. Please select a valid option.\n";
        }
    }
}

// ======================================================================
//                               MAIN
// ======================================================================
int main() {
    cout << fixed << setprecision(2);  // show balances with 2 decimal places

    // printBanner("SMART BANK MANAGEMENT SYSTEM");
    cout << "\033[33m" << "BANK MANAGEMENT SYSTEM";
    BankSystem bank;

    int choice = -1;
    while (choice != 0) {
        printBanner("MAIN MENU");
        printCentered("1. Admin Login");
        printCentered("2. Customer Login");
        printCentered("0. Exit");
        cout << "\n";

        choice = readInt("Enter your choice: ");

        switch (choice) {
        case 1: {
            string user, pass;
            cout << "Username: ";
            cin >> user;
            cout << "Password: ";
            cin >> pass;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (bank.adminLogin(user, pass)) {
                cout << "Admin login successful.\n";
                Admin admin(1, "Main Admin", user, pass);
                admin.showMenu(bank);
            } else {
                cout << "Invalid admin credentials.\n";
            }
            break;
        }
        case 2: {
            long accNo = readLong("Enter account number: ");
            int  pin   = readPin("Enter PIN: ");

            Account* acc = bank.customerLogin(accNo, pin);
            if (!acc) {
                cout << "Login failed.\n";
            } else {
                Customer cust(1, acc->getName(), "cust", "pass", accNo);
                cust.showMenu(bank);
            }
            break;
        }
        case 0:
            cout << "Saving data and exiting...\n";
            bank.saveToFile();
            break;

        default:
            cout << "Invalid choice. Please select 0, 1 or 2.\n";
        }
    }

    return 0;
}
