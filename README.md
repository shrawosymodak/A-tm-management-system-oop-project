**ATM Management System README**

This repository contains an ATM Management System implemented in C++. The system allows users to perform various operations such as logging in, depositing money, withdrawing money, checking account details, viewing transaction history, changing PIN, and logging out.

## Features

1. Login: Users can log in to their accounts by entering their account number and PIN. The system verifies the entered credentials before granting access.

2. Deposit: After logging in, users can deposit money into their accounts. They need to enter the desired deposit amount, and the system updates the account balance accordingly.

3. Withdraw: Users can withdraw money from their accounts after logging in. They need to enter the amount they want to withdraw, and the system checks if sufficient funds are available before processing the withdrawal.

4. Display Account Details: Once logged in, users can view their account details such as account number, account holder name, and current balance.

5. Display Transaction History: Users can check their transaction history to view the details of previous deposits and withdrawals.

6. Clear Transaction History: Users have the option to clear their transaction history, removing all the previous records.

7. Change PIN: Users can change their PIN for added security. The system prompts users to enter their current PIN, followed by the new PIN. The new PIN is then confirmed to ensure accuracy.

8. Logout: Users can log out of their accounts, terminating their session.

## Usage

1. Clone the repository to your local machine.

2. Compile the code using a C++ compiler.

3. Run the compiled executable file.

4. Follow the on-screen prompts to navigate through the ATM system and perform desired operations.

5. Make sure to provide valid inputs as required during the execution of the program.

The ATM Management System code provided demonstrates the following object-oriented programming (OOP) concepts:

1. **Inheritance**: The classes `Account` and `print` both inherit from the abstract base class `atmmanagement`. This allows them to inherit common attributes and behaviors defined in the base class.

2. **Polymorphism**: The `Account` class implements the `print()` function defined in the `atmmanagement` base class. This demonstrates polymorphism, as the derived class provides its own implementation of the base class function.

3. **Encapsulation**: The classes `Account`, `ATM`, and `print` all encapsulate data and functionality within their respective classes. Member variables are declared as private, and access to them is controlled through public member functions.

4. **Abstraction**: The `atmmanagement` class is an abstract base class that defines a pure virtual function `print()`. This abstraction allows for the creation of derived classes that implement their own versions of the `print()` function.

5. **Data Hiding**: The private member variables (`accountNumber`, `accountHolderName`, `pin`, and `balance`) in the `Account` class are hidden from direct access outside the class. They can only be accessed and modified through public member functions.

6. **Composition**: The `ATM` class contains a vector of `Account` objects. This composition relationship allows an ATM object to manage multiple accounts.

7. **Friend Function**: The `operator<<` friend function in the `print` class allows the class to override the `<<` operator for the purpose of displaying the menu options.

These OOP concepts help in organizing and structuring the code, promoting code reusability, modularity, and maintainability.
