#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/file.h>  
#include <fcntl.h>   
#include "manager.h"
#include "../Employee/employee.h"
#include "../Customer/customer.h"

#define BUFFER_SIZE 1024
#define MAX_CUSTOMERS 100

#define CUSTOMER_FILE "Customer/customers.txt"
#define EMPLOYEE_FILE "Employee/employees.txt"
#define LOAN_FILE "Customer/loans.txt"
#define FEEDBACK_FILE "Customer/feedback.txt"

const char manager_username[] = "BudgetBoss";
const char manager_password[] = "OnBudget";

void Activate_Customer_Acc(int sock);
void Deactivate_Customer_Acc(int sock);
void Assign_LoanApp_to_Employee(int sock);
void Review_Customer_feedback(int sock);

void handle_manager_login(int sock) {
    char username[30], password[30];

    const char *username_prompt = "Enter username: ";
    send(sock, username_prompt, strlen(username_prompt), 0);
    recv(sock, username, sizeof(username), 0);
    username[strcspn(username, "\n")] = 0;

    const char *password_prompt = "Enter password: ";
    send(sock, password_prompt, strlen(password_prompt), 0);
    recv(sock, password, sizeof(password), 0);
    password[strcspn(password, "\n")] = 0;

    if (strcmp(username, manager_username) == 0 && strcmp(password, manager_password) == 0) {
        const char *success_msg = "Login successful!";
        send(sock, success_msg, strlen(success_msg), 0);

        while (1) {
            char choice[2];
            recv(sock, choice, sizeof(choice), 0);
            int menu_choice = atoi(choice);
            switch (menu_choice) {
                case 1:
                    Activate_Customer_Acc(sock);
                    break;
                case 2:
                    Deactivate_Customer_Acc(sock);
                    break;
                case 3:
                    Assign_LoanApp_to_Employee(sock);
                    break;
                case 4:
                    Review_Customer_feedback(sock);
                    break;
                case 5:
                    const char *logout_msg = "Logging out...";
                    send(sock, logout_msg, strlen(logout_msg), 0);
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
}

void Activate_Customer_Acc(int sock) {
    char username[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    int found = 0;

    recv(sock, username, BUFFER_SIZE, 0);
    username[strcspn(username, "\n")] = 0;  // Remove newline character

    int fd = open(CUSTOMER_FILE, O_RDWR);
    if (fd == -1) {
        perror("Unable to open customer file");
        return;
    }

    if (flock(fd, LOCK_EX) == -1) {
        perror("Unable to lock file");
        close(fd);
        return;
    }

    FILE *file = fdopen(fd, "r+");
    if (file == NULL) {
        perror("Unable to open customer file stream");
        close(fd);
        return;
    }

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        char file_username[50], password[50];
        float balance;
        int id, is_active;

        sscanf(buffer, "%s %s %f %d %d", file_username, password, &balance, &id, &is_active);

        if (strcmp(file_username, username) == 0) {
            found = 1;
            if (is_active == 0) {
                fseek(file, -2, SEEK_CUR);  // Move to position to update the is_active flag
                fprintf(file, "1\n");       // Update the active flag to 1
                const char *activation_msg = "Customer's account is activated\n";
                send(sock, activation_msg, strlen(activation_msg), 0);
            } else {
                const char *already_active_msg = "Customer's account is already active\n";
                send(sock, already_active_msg, strlen(already_active_msg), 0);
            }
            break;
        }
    }

    if (!found) {
        const char *not_found_msg = "Username not found\n";
        send(sock, not_found_msg, strlen(not_found_msg), 0);
    }

    fclose(file);
    flock(fd, LOCK_UN);
    close(fd);
}

void Deactivate_Customer_Acc(int sock){
    char username[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    int found = 0;

    recv(sock, username, BUFFER_SIZE, 0);
    username[strcspn(username, "\n")] = 0; 

    int fd = open(CUSTOMER_FILE, O_RDWR);
    if (fd == -1) {
        perror("Unable to open customer file");
        return;
    }

    if (flock(fd, LOCK_EX) == -1) {
        perror("Unable to lock file");
        close(fd);
        return;
    }

    FILE *file = fdopen(fd, "r+");
    if (file == NULL) {
        perror("Unable to open customer file stream");
        close(fd);
        return;
    }

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        char file_username[50], password[50];
        float balance;
        int id, is_active;

        sscanf(buffer, "%s %s %f %d %d", file_username, password, &balance, &id, &is_active);

        if (strcmp(file_username, username) == 0) {
            found = 1;
            if (is_active == 1) {
                fseek(file, -2, SEEK_CUR);  // Move to position to update the is_active flag
                fprintf(file, "0\n");       // Update the active flag to 0
                const char *deactivation_msg = "Customer's account deactivated successfully\n";
                send(sock, deactivation_msg, strlen(deactivation_msg), 0);
            } else {
                const char *already_deactivated_msg = "Customer's account is already deactivated\n";
                send(sock, already_deactivated_msg, strlen(already_deactivated_msg), 0);
            }
            break;
        }
    }

    if (!found) {
        const char *not_found_msg = "Username not found\n";
        send(sock, not_found_msg, strlen(not_found_msg), 0);
    }

    fclose(file);
    flock(fd, LOCK_UN);
    close(fd);
}

void Assign_LoanApp_to_Employee(int sock) {
    FILE *loanFile = fopen(LOAN_FILE, "r");
    FILE *manageLoanFile = fopen("manage_loan.txt", "a");

    if (loanFile == NULL) {
        perror("Failed to open loans.txt");
        return;
    }

    if (manageLoanFile == NULL) {
        perror("Failed to open manage_loan.txt");
        fclose(loanFile);
        return;
    }

    LoanApplication loan;
    char buffer[BUFFER_SIZE];
    char employee_assigned[50];

    while (fgets(buffer, BUFFER_SIZE, loanFile) != NULL) {
        sscanf(buffer, "%s %f %s %f %s %s", loan.customer_username, &loan.loan_amount, loan.loan_purpose,
               &loan.monthly_income, loan.employment_status, loan.contact_info);

        if (strcmp(loan.loan_purpose, "car") == 0)
            strcpy(employee_assigned, "employee1 (car loan)");
         else if (strcmp(loan.loan_purpose, "home") == 0) {
            strcpy(employee_assigned, "employee2 (home loan)");
        } else if (strcmp(loan.loan_purpose, "education") == 0) {
            strcpy(employee_assigned, "employee3 (education loan)");
        } else if (strcmp(loan.loan_purpose, "gold") == 0) {
            strcpy(employee_assigned, "employee4 (gold loan)");
        } else if (strcmp(loan.loan_purpose, "personal") == 0) {
            strcpy(employee_assigned, "employee5 (personal loan)");
        } else {
            strcpy(employee_assigned, "No employee assigned for this loan purpose");
        }

        char message[BUFFER_SIZE];
        snprintf(message, sizeof(message), "Loan application for %s (Purpose: %s) assigned to %s\n",
                loan.customer_username, loan.loan_purpose, employee_assigned);

        send(sock, message, strlen(message), 0);

        fprintf(manageLoanFile, "%s | %f | %s | Assigned to: %s\n", 
                loan.customer_username, loan.loan_amount, loan.loan_purpose, employee_assigned);
    }
    fclose(loanFile);
    fclose(manageLoanFile);
}

void Review_Customer_feedback(int sock) {
    FILE *file = fopen(FEEDBACK_FILE, "r");
    char buffer[BUFFER_SIZE];

    if (file == NULL) {
        perror("Failed to open feedback file");
        return;
    }

    const char *header = "==========================\n     Customer Feedback\n==========================\n";
    send(sock, header, strlen(header), 0);

    while (fgets(buffer, sizeof(buffer), file) != NULL)
        send(sock, buffer, strlen(buffer), 0);

    const char *end_message = "==========================\n     All feedbacks reviewed\n==========================\n";
    send(sock, end_message, strlen(end_message), 0);
    fclose(file);
    file = fopen(FEEDBACK_FILE, "w");
    if (file != NULL) {
        fclose(file);
    }

}
