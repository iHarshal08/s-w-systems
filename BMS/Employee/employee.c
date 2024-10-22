#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "employee.h"
#include <sys/file.h>
#include "../Admin/admin.h"
#include "../Customer/customer.h"

#define BUFFER_SIZE 1024
#define MAX_EMPLOYEES 100
#define MINIMUM_INCOME_THRESHOLD 30000.0
#define CUSTOMER_FILE "Customer/customers.txt"
#define LOAN_FILE "Customer/loans.txt"
#define TRANSACTION_FILE "Customer/transaction_history.txt"
#define EMPLOYEE_FILE "Employee/employees.txt"

Employee emp;

// Function prototypes
int authenticate_employee(const char* username, const char* password);
void handle_employee_login(int sock);
void update_customer(int sock);
void Process_LoanApp(int sock);

// Authenticate employee
int authenticate_employee(const char* username, const char* password) {
    FILE *file = fopen(EMPLOYEE_FILE, "r");
    if (!file) {
        perror("Failed to open employee file");
        return 0;
    }
    if (flock(fileno(file), LOCK_SH) == -1) {
        perror("Failed to lock customer file");
        fclose(file);
        return 0;
    }

    while (fscanf(file, "%s %s %d", emp.username, emp.password, &emp.id) != EOF) {
        if (strcmp(emp.username, username) == 0 && strcmp(emp.password, password) == 0) {
            fclose(file);
            return 1;
        }
    }

    flock(fileno(file), LOCK_UN); 
    fclose(file);
    return 0;
}

void handle_employee_login(int sock) {
    char username[50], password[50];

    const char *username_prompt = "Enter username: ";
    send(sock, username_prompt, strlen(username_prompt), 0);
    recv(sock, username, sizeof(username), 0);
    username[strcspn(username, "\n")] = 0; 

    const char *password_prompt = "Enter password: ";
    send(sock, password_prompt, strlen(password_prompt), 0);
    recv(sock, password, sizeof(password), 0);
    password[strcspn(password, "\n")] = 0;

    if (authenticate_employee(username, password)) {
        const char *success_msg = "Login successful!";
        send(sock, success_msg, strlen(success_msg), 0);

        while (1) {
            char choice_str[BUFFER_SIZE];
            memset(choice_str, 0, sizeof(choice_str));
            recv(sock, choice_str, sizeof(choice_str), 0);
            int menu_choice = atoi(choice_str);
            switch (menu_choice) {
                case 1:
                    view_all_customer(sock);
                    break;
                case 2:
                    Process_LoanApp(sock);
                    break;
                case 3:
                    add_customer(sock);
                    break;
                case 4:
                    remove_customer(sock);
                    break;
                case 5:
                    update_customer(sock);
                    break;
                case 6:
                    const char *exit_msg = "Logging out...";
                    send(sock, exit_msg, strlen(exit_msg), 0);
                    close(sock);
                    return;
                default:
                    const char *invalid_choice = "Invalid choice, please try again.";
                    send(sock, invalid_choice, strlen(invalid_choice), 0);
            }
        }
    } else {
        const char *error_msg = "Login failed! Invalid username or password.";
        send(sock, error_msg, strlen(error_msg), 0);
    }
    close(sock);
    printf("Client disconnected.\n");
}

void update_customer(int sock) {
    char buffer[BUFFER_SIZE];
    char old_username[50], new_username[50], new_password[50];
    int found = 0;
    Customer customer;
    recv(sock, buffer, BUFFER_SIZE, 0);
    sscanf(buffer, "UPDATE_CUSTOMER %s %s %s", old_username, new_username, new_password);

    FILE *file = fopen(CUSTOMER_FILE, "r+");
    if (!file) {
        const char *error_msg = "Error: Could not open customer file.\n";
        send(sock, error_msg, strlen(error_msg), 0);
        return;
    }

    if (flock(fileno(file), LOCK_SH) == -1) {
        perror("Failed to lock customer file");
        fclose(file);
    }
    char line[BUFFER_SIZE];
    long int position;
    while (fgets(line, sizeof(line), file)) {
        position = ftell(file);  
        sscanf(line, "%s %s %f %d %d", customer.username, customer.password, &customer.balance, &customer.id, &customer.is_active);

        if (strcmp(customer.username, old_username) == 0) {
            found = 1; 
            fseek(file, position - strlen(line), SEEK_SET);  // Move back to the start of this record
            fprintf(file, "%s %s %.2f %d %d\n", new_username, new_password, customer.balance, customer.id, customer.is_active);
            break;
        }
    }
    flock(fileno(file), LOCK_UN);
    fclose(file);

    if (found) {
        const char *success_msg = "Customer update completed.\n";
        send(sock, success_msg, strlen(success_msg), 0);
    } else {
        const char *error_msg = "Error: Customer not found.\n";
        send(sock, error_msg, strlen(error_msg), 0);
    }
}

void Process_LoanApp(int sock) {
    FILE *file = fopen(LOAN_FILE, "r");
    if (!file) {
        perror("Failed to open loan file");
        const char *error_msg = "Failed to retrieve loan applications.";
        send(sock, error_msg, strlen(error_msg), 0);
        return;
    }

    LoanApplication loan_app;
    char line[BUFFER_SIZE];
    const char *header_msg = "Processing loan applications:\n";
    send(sock, header_msg, strlen(header_msg), 0);

    // Read each loan application from the file
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %f %s %f %s %s", loan_app.customer_username, 
               &loan_app.loan_amount, loan_app.loan_purpose, 
               &loan_app.monthly_income, loan_app.employment_status, loan_app.contact_info);
        
        // Process each loan application
        if (loan_app.monthly_income >= MINIMUM_INCOME_THRESHOLD) {
            char success_msg[BUFFER_SIZE];
            snprintf(success_msg, BUFFER_SIZE, 
                     "Loan approved for %s (Amount: %.2f, Purpose: %s)\n",
                     loan_app.customer_username, loan_app.loan_amount, loan_app.loan_purpose);
            send(sock, success_msg, strlen(success_msg), 0);
        } else {
            char reject_msg[BUFFER_SIZE];
            snprintf(reject_msg, BUFFER_SIZE, 
                     "Loan rejected for %s due to insufficient income (Income: %.2f)\n", 
                     loan_app.customer_username, loan_app.monthly_income);
            send(sock, reject_msg, strlen(reject_msg), 0);
        }
    }
    fclose(file);
    const char *completion_msg = "Loan processing completed.\n";
    send(sock, completion_msg, strlen(completion_msg), 0);
}


