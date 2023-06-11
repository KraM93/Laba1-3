#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#pragma warning(disable : 4996)
using namespace std;

class Client {
private:
    string firstName;
    string lastName;
    string dateOfBirth;
    string uniqueID;

public:
    Client(string firstName, string lastName, string dateOfBirth, string uniqueID)
        : firstName(firstName), lastName(lastName), dateOfBirth(dateOfBirth), uniqueID(uniqueID) {}

    string getFirstName() const {
        return firstName;
    }

    string getLastName() const {
        return lastName;
    }

    string getDateOfBirth() const {
        return dateOfBirth;
    }

    string getUniqueID() const {
        return uniqueID;
    }
};

class Deposit {
private:
    double amount;
    double interestRate;
    int duration;

public:
    Deposit(double amount, double interestRate, int duration)
        : amount(amount), interestRate(interestRate), duration(duration) {}

    double calculateIncome() const {
        double totalInterest = amount * interestRate * duration;
        return amount + totalInterest;
    }

    int getDuration() const {
        return duration;
    }
};

class Credit {
private:
    double amount;
    double interestRate;
    int duration;

public:
    Credit(double amount, double interestRate, int duration)
        : amount(amount), interestRate(interestRate), duration(duration) {}

    double calculateInterest() const {
        double totalInterest = amount * interestRate * duration;
        return totalInterest;
    }

    vector<pair<time_t, double>> getPaymentSchedule() const {
        vector<pair<time_t, double>> payments;
        time_t currentDate = time(nullptr);

        for (int i = 0; i < duration; i++) {
            double monthlyPayment = amount / duration;
            payments.push_back(make_pair(currentDate, monthlyPayment));
            currentDate += 30 * 24 * 60 * 60;
        }

        return payments;
    }
};

class Bank {
private:
    vector<Client> clients;
    vector<Deposit> deposits;
    vector<Credit> credits;

public:
    void addClient(const Client& client) {
        clients.push_back(client);
    }

    void createDeposit(double amount, double interestRate, int duration) {
        Deposit deposit(amount, interestRate, duration);
        deposits.push_back(deposit);
    }

    void createCredit(double amount, double interestRate, int duration) {
        Credit credit(amount, interestRate, duration);
        credits.push_back(credit);
    }

    void printClientInfo(const Client& client) const {
        cout << "Имя: " << client.getFirstName() << endl;
        cout << "Фамилия: " << client.getLastName() << endl;
        cout << "Дата рождения: " << client.getDateOfBirth() << endl;
        cout << "Уникальный идентификатор: " << client.getUniqueID() << endl;
    }

    void printDepositInfo(const Deposit& deposit) const {
        cout << "Сумма вклада: " << deposit.calculateIncome() << endl;
        cout << "Дата окончания вклада: " << getEndDate(deposit.getDuration()) << endl;
    }

    void printCreditInfo(const Credit& credit) const {
        cout << "Сумма кредита: " << credit.calculateInterest() << endl;

        cout << "График платежей:" << endl;
        vector<pair<time_t, double>> paymentSchedule = credit.getPaymentSchedule();
        for (const auto& payment : paymentSchedule) {
            struct tm* timeinfo;
            char buffer[80];
            timeinfo = localtime(&payment.first);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
            cout << "Дата платежа: " << buffer << endl;
            cout << "Сумма платежа: " << payment.second << endl;
        }
    }

    void printClientFinancialInfo(const Client& client) const {
        cout << "Информация о клиенте:" << endl;
        printClientInfo(client);
        cout << endl;

        cout << "Вклады:" << endl;
        for (const auto& deposit : deposits) {
            printDepositInfo(deposit);
            cout << endl;
        }

        cout << "Кредиты:" << endl;
        for (const auto& credit : credits) {
            printCreditInfo(credit);
            cout << endl;
        }
    }

private:
    string getEndDate(int duration) const {
        time_t currentDate = time(nullptr);
        time_t endDate = currentDate + duration * 30 * 24 * 60 * 60;

        struct tm* timeinfo;
        char buffer[80];
        timeinfo = localtime(&endDate);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);

        return buffer;
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    Bank bank;

    Client client("Иван", "Иванов", "01.01.1990", "12345");
    bank.addClient(client);

    double depositAmount = 10000.0;
    double depositInterestRate = 0.05;
    int depositDuration = 12;
    bank.createDeposit(depositAmount, depositInterestRate, depositDuration);

    double creditAmount = 50000.0;
    double creditInterestRate = 0.1;
    int creditDuration = 24;
    bank.createCredit(creditAmount, creditInterestRate, creditDuration);

    bank.printClientFinancialInfo(client);

    return 0;
}
