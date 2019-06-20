// Assignment 3
// Programmer 	: John Lee
// Date 		: 06-11-2019
// Last Updated	: 06-19-2019
// Status 		: Complete
// Purpose		: Checkbook Balancing

// include libraries
#include <iostream>
#include <iomanip>
using namespace std;

// prototypes
void displayTitleGetBeginBalance(float &);
void menuSelectionAndDisplay(char &	);
void getTransactionAmt(float &);
void calcAndQuit(float &, float, bool, float);
void withdraw(float, float &);
void processingFee(float, float &, float &);
void deposit(float, float &);
void checkOverdraft(float &, float);
void checkLimit(float, bool &, float);

int main()
{
	float balance = 0.0;
	char menuChoice;
	float transactionAmount = 0.0;
	float serviceCharge = 0.35;
	float totalServiceCharge = 0.0;
	bool belowLimit = false;
	float belowFee = 15;
	float overDraftFee = 35;

	// Display title and Get Beginning Balance
	displayTitleGetBeginBalance(balance);

	// Show menu and Get Transaction Type
	menuSelectionAndDisplay(menuChoice);

	// while menu choice is not quit, proceed with transaction
	while(menuChoice != 'E')
	{
		// Get Transaction Amount
		getTransactionAmt(transactionAmount);

		// If menu choice is C, subtract from balance including processing fee
		if(menuChoice == 'C')
		{
			withdraw(transactionAmount, balance);
			processingFee(serviceCharge, balance, totalServiceCharge);
			checkLimit(balance, belowLimit, belowFee);
			checkOverdraft(balance, overDraftFee);
		}
		// If menu choice is D, add to balance
		else if(menuChoice == 'D')
		{
			deposit(transactionAmount, balance);
			processingFee(0.0, balance, totalServiceCharge);
		}

		// Display menu again
		menuSelectionAndDisplay(menuChoice);
	}

	// Quit after E is selected and display final balance
	calcAndQuit(balance, totalServiceCharge, belowLimit, belowFee);
}

void displayTitleGetBeginBalance(float &bal)
{
	// Program Title
	cout << "Checkbook Balancing Program" << endl;
	cout << "" << endl;

	// Get Beginning Balance
	cout << "Enter the Beginning Balance: ";
	cin >> bal;
}

void menuSelectionAndDisplay(char &choice)
{
	// Show Menu
	cout << "" << endl;
	cout << "Commands:" << endl;
	cout << "C - process a check" << endl;
	cout << "D - process a deposit" << endl;
	cout << "E - end the program" << endl;
	cout << "" << endl; 

	// Get Transaction Type
	cout << "Enter a transaction type: ";
	cin >> choice;

	// Choice Validation
	while(choice != 'C' and choice != 'D' and choice != 'E')
	{
		cout << "Enter a valid transaction type: ";
		cin >> choice;
	}
}

void calcAndQuit(float &balance, float totalServiceCharges, bool belowLimit, float belowFee)
{
	cout << "Processing end of month" << endl;
	cout << "Total service charges: $" << setprecision(2) << fixed << totalServiceCharges << endl;
	cout << "Total below limit penalty charges: $" << setprecision(2) << fixed << belowFee << endl;

	// Process charges
	balance -= totalServiceCharges;

	if(belowLimit == true)
		balance -= belowFee;

	cout << "" << endl; // formatting
	cout << "Final balance: $" << setprecision(2) << fixed << balance << endl;
	cout << "" << endl; // formatting
}

void getTransactionAmt(float &amount)
{
	// Get Transaction Amount
	cout << "Enter transaction amount: ";
	cin >> amount;

	// Validate input
	while(amount <= 0)
	{
		cout << "Enter valid transaction amount: ";
		cin >> amount;	
	}
}

void withdraw(float transactionAmt, float &balance)
{
	// Withdraw transaction amount from balance
	cout << "Processing a check for $" << setprecision(2) << fixed << transactionAmt << endl;
	balance -= transactionAmt;
	int balanceLimit = -100;

	// Check that resulting balance is at least -$100
	if(balance >= balanceLimit)
		cout << "Balance : $" << setprecision(2) << fixed << balance << endl;
	else
	{
		// If account has insufficient funds then do not withdraw money
		// Add transaction amount back to balance and write error output
		balance += transactionAmt;
		cout << "ERROR : Account does not have the available funds to withdraw." << endl;
		cout << "Balance : $" << setprecision(2) << fixed << balance << endl;
	}
}

void processingFee(float fee, float &balance, float &totalFees)
{
	// Subtract processing fee from balance
	cout << "Service charge: $" << setprecision(2) << fixed << fee << endl;
	totalFees += fee;
	cout << "Total service charges to be charged at end of month: $" << setprecision(2) << fixed << totalFees << endl;
}

void deposit(float transactionAmt, float &balance)
{
	// Deposit transaction amount into balance
	cout << "Processing deposit for $" << setprecision(2) << fixed << transactionAmt << endl;
	balance += transactionAmt;
	cout << "Balance : $" << setprecision(2) << fixed << balance << endl;
}

void checkLimit(float balance, bool &belowLimit, float belowFee)
{
	// If balance falls below 500 charge overdraft fee but only once
	int limit = 500;
	if(balance < limit && belowLimit == false)
	{
		belowLimit = true;
		cout << "Total balance fell below $" << setprecision(2) << fixed << limit << ", fees to be charged at end of month: $" << belowFee << endl;
	}
}

void checkOverdraft(float &balance, float overDraftFee)
{
	// If balance falls below 0 charge overdraft fee
	if(balance < 0)
	{
		balance -= overDraftFee;
		cout << "Account overdrafted, fee charged: $" << setprecision(2) << fixed << overDraftFee << endl;
	}
}