/* Author: Brandon Duong
 * AU ID: bhd0014
 * Class: COMP2710
 * Filename: Project1.cpp
 * Compile source code file with g++.
 * I used Dr. Li's "Project 1 Hints" to write my code. I also used
 * Google to figure out similar concepts between C++ and Java such as
 * clearing input and to learn the syntax of C++. I asked my friend
 * Abdul Mohammed for help on formatting.
 */

#include <iostream>
using namespace std;

int main() {

    //initialize variables
    double loan = 0;
    double interestRate = 0;
    double monthlyPayment = 0;

    //currency formatting
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    //user input
    //NOTE: all inputs must be positive, monthly payment must be big
    //enough to pay monthly interest + pay off loan completely
    cout << "\nLoan Amount: ";
    cin >> loan;

    while (loan <= 0 || cin.fail()) {
        cout << "Invalid input. Please enter a positive number.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Loan Amount: ";
        cin >> loan;
    }

    cout << "Interest Rate (% per year): ";
    cin >> interestRate;
    while (interestRate < 0 || cin.fail()) {
        cout << "Invalid input. Please enter a positive number.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Interest Rate (% per year): ";
        cin >> interestRate;
    }

    //calculate monthly interest rate
    interestRate /= 12;
    double interestRateA;
    interestRateA = interestRate / 100;
    double interestTotal = 0;

    cout << "Monthly Payments: ";
    cin >> monthlyPayment;
    while (monthlyPayment <= loan * interestRateA || monthlyPayment <= 0 || cin.fail()) {
        cout << "Monthly payment must be enough to pay off interest and loan.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Monthly Payments: ";
        cin >> monthlyPayment;
    }
    cout << endl;

    //amortization table
    cout << "*****************************************************************\n"
         << "\tAmortization Table\n"
         << "*****************************************************************\n"
         << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n";

    //loop for the table
    int currentMonth = 0;
    double interest;
    double principal;
    while (loan > 0) {
        interest = loan * interestRateA;
        if (currentMonth == 0) {
            cout << currentMonth++ << "\t$" << loan;
            //formatting purposes
            if (loan < 1000) {
                cout << "\t";
            }
            cout << "\tN/A\tN/A\tN/A\t\tN/A\n";
        }
        else {
            if (loan * (1 + interestRateA) < monthlyPayment) {
                monthlyPayment = loan + interest;
                principal = loan;
                loan -= loan;
                interestTotal += interest;
            }
            if (loan * (1 + interestRateA) >= monthlyPayment) {
                principal = monthlyPayment - interest;
                loan -= principal;
                interestTotal += interest;
            }
            cout << currentMonth++ << "\t$" << loan;
            //formatting purposes
            if (loan < 1000) {
                cout << "\t";
            }
            cout << "\t$" << monthlyPayment;
            cout << "\t" << interestRate << "\t$" << interest;
            cout << "\t\t$" << principal;
            cout << endl;
        }
    }

    cout << "****************************************************************\n";
    cout << "\nIt takes " << --currentMonth << " months to pay off "
         << "the loan.\n"
         << "Total interest paid is: $" << interestTotal;
    cout << endl << endl;
    return 0;
}
