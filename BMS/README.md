Banking Management System

This is a simple Banking Management System implemented in C using file handling, socket programming, file locking and concurrency. The system allows users to perform various banking operations such as viewing account balance, depositing money, withdrawing money, applying for loans, and more. There are four roles in the system: Admin, Manager, Employee, and Customer, each with specific functionalities.

Features

The system includes the following roles:
1. Admin

Login as Admin: Admin can log in using a predefined username and password.

View All Customers: Admin can view a list of all customers in the system along with their details.

Add New Customer: Admin can add a new customer by providing a unique ID, name, password, and initial balance.

Remove Customer: Admin can remove a customer from the system by entering their ID.

2. Manager

Login as Manager: Manager can log in using predefined credentials.

Activate Customer Account: Manager can activate a deactivated customer account.

Deactivate Customer Account: Manager can deactivate an active customer account.

Assign Loan Applications to Employees: Manager can assign customer loan applications to employees based on the loan type.

Review Customer Feedback: Manager can view all customer feedback and reset the feedback file after review.

3. Employee

Login as Employee: Employees can log in using their credentials to view assigned tasks.

Handle Loan Applications: Employees can view loan applications assigned to them by the manager and process them accordingly.

Customer Handling: Employees can view customer details and help manage transactions.

4. Customer

Login as Customer: Customers can log in using their credentials to perform various banking operations.

View Account Balance: Customers can view their current account balance.

Deposit Money: Customers can deposit money into their accounts.

Withdraw Money: Customers can withdraw money from their accounts.

Transfer Funds: Customers can transfer money to other customers.

Apply for a Loan: Customers can apply for loans by providing details such as loan amount, loan purpose, monthly income, and contact information.

Change Password: Customers can change their account password.

Provide Feedback: Customers can submit feedback about their banking experience.

View Transaction History: Customers can view their past transactions.

System Structure

BankingManagementSystem/
├── Admin/
│   ├── admin.c
│   └── admin.h
├── Manager/
│   ├── manager.c
│   └── manager.h
├── Employee/
│   ├── employee.c
│   └── employee.h
├── Customer/
│   ├── customer.c
│   ├── customer.h
|   ├── feedback.txt
|   ├── loans.txt
|   ├── transaction_history.txt
│   └── customers.txt
├── client.c
├── server.c
├── manage_loan.txt
└── README.md

Setup

gcc server.c Customer/customer.c Employee/employee.c Admin/admin.c Manager/manager.c -o server -lpthrea

gcc client.c Customer/customer.c Employee/employee.c Admin/admin.c Manager/manager.c -o client -lpthread

./server

./client

NOTE:
I have given Absolute paths to access the data files so make sure to change the paths according your file structure.
