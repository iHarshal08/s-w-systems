#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "customer.h"
#include <sys/file.h>

#define BUFFER_SIZE 1024
#define CUSTOMER_FILE "Customer/customers.txt"
#define LOAN_FILE "Customer/loans.txt"
#define FEEDBACK_FILE "Customer/feedback.txt"
#define TRANSACTION_FILE "Customer/transaction_history.txt"

Customer customers[100];
int customer_count = 0;
Customer new_customer;

typedef struct {
    char username[50];
    float loan_amount;
    char loan_purpose[50];
    float monthly_income;
    char employment_status[50];
    int contact_info;
} Loan;

// Function prototypes
void view_account_balance(const char *username, int sock);
void deposit_money(const char *username, int sock);
void withdraw_money(const char *username, int sock);
void transfer_funds(const char *username, int sock);
void handle_customer_login(int sock);
int authenticate_customer(const char *username, const char *password);
void apply_for_loan(const char *username, int sock); 
void change_password(const char *username, int sock); 
void add_feedback(const char *username, int sock); 
void view_transaction_history(const char *username, int sock); 
void log_transaction(const char *username, const char *type, float amount);

void handle_customer_login(int sock) {
    char username[30], password[30];

    const char *username_prompt = "Enter username: ";
    send(sock, username_prompt, strlen(username_prompt), 0);
    recv(sock, username, sizeof(username), 0);
    username[strcspn(username, "\n")] = 0;  

    const char *password_prompt = "Enter password: ";
    send(sock, password_prompt, strlen(password_prompt), 0);
    recv(sock, password, sizeof(password), 0);
    password[strcspn(password, "\n")] = 0;  

    int auth_result = authenticate_customer(username, password);
    if (auth_result == 1){
        const char *success_msg = "Login successful!";
        send(sock, success_msg, strlen(success_msg), 0);

        while (1) {
            char choice[2];
            recv(sock, choice, sizeof(choice), 0);
            int menu_choice = atoi(choice);

            switch (menu_choice) {
                case 1:
                    view_account_balance(username, sock);
                    break;
                case 2:
                    deposit_money(username, sock);
                    break;
                case 3:
                    withdraw_money(username, sock);
                    break;
                case 4:
                    transfer_funds(username, sock);
                    break;
                case 5:
                    apply_for_loan(username, sock); 
                    break;
                case 6:
                    change_password(username, sock);
                    break;
                case 7:
                    add_feedback(username, sock);
                    break;
                case 8:
                    view_transaction_history(username, sock);
                    break;
                case 9: // Logout
                    const char *logout_msg = "Logging out...";
                    send(sock, logout_msg, strlen(logout_msg), 0);
                    exit(0);                    
                default:
                    const char *invalid_choice = "Invalid choice, please try again.";
                    send(sock, invalid_choice, strlen(invalid_choice), 0);
            }
        }
    } 
    else if (auth_result == -1) {
        const char *inactive_msg = "Login failed! Your account is deactivated.";
        send(sock, inactive_msg, strlen(inactive_msg), 0);
    }
    else {
        const char *error_msg = "Login failed! Invalid username or password.";
        send(sock, error_msg, strlen(error_msg), 0);
    }
}

int authenticate_customer(const char *username, const char *password) {
    FILE *file = fopen(CUSTOMER_FILE, "r");
    if (!file) {
        perror("Failed to open customer file");
        return 0;
    }

    if (flock(fileno(file), LOCK_SH) == -1) {
        perror("Failed to lock customer file");
        fclose(file);
        return 0;
    }
    char line[BUFFER_SIZE];
    Customer customer;
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s %f %d %d", customer.username, customer.password, &customer.balance, &customer.id, &customer.is_active);
        customer.username[strcspn(customer.username, "\n")] = 0;
        customer.password[strcspn(customer.password, "\n")] = 0;

        if (strcmp(customer.username, username) == 0 && strcmp(customer.password, password) == 0) {
            if (customer.is_active == 1) {
                fclose(file);
                return 1;  // Login successful
            } else {
                fclose(file);
                return -1;  // Account is deactivated
            } 
        }
    }
    flock(fileno(file), LOCK_UN);
    fclose(file);
    return 0; 
}

void view_account_balance(const char *username, int sock) {
    FILE *file = fopen(CUSTOMER_FILE, "r");
    if (!file) {
        perror("Failed to open customer file");
        return;
    }
    if (flock(fileno(file), LOCK_SH) == -1) {
        perror("Failed to lock customer file");
        fclose(file);
        return;
    } 
    Customer customer;
    while (fscanf(file, "%s %s %f %d %d", customer.username, customer.password, &customer.balance, &customer.id, &customer.is_active) != EOF) {
        if (strcmp(customer.username, username) == 0) {
            char balance_msg[100];
            snprintf(balance_msg, sizeof(balance_msg), "Account Balance: %.2f\n", customer.balance);
            send(sock, balance_msg, strlen(balance_msg), 0);
            break;
        }
    }
    flock(fileno(file), LOCK_UN);
    fclose(file);
}

void deposit_money(const char *username, int sock) {
    float amount;
    char msg[100];

    recv(sock, msg, sizeof(msg), 0);
    sscanf(msg, "%f", &amount);

    FILE *file = fopen(CUSTOMER_FILE, "r");
    if (!file) {
        perror("Failed to open customer file");
        return;
    }
    if (flock(fileno(file), LOCK_SH) == -1) {
        perror("Failed to lock customer file");
        fclose(file);
        return;
    }
    Customer customers[100];
    int count = 0;

    while (fscanf(file, "%s %s %f %d %d", customers[count].username, customers[count].password, &customers[count].balance, &customers[count].id, &customers[count].is_active) != EOF) {
        count++;
    }
    flock(fileno(file), LOCK_UN);
    fclose(file);

    for (int i = 0; i < count; i++) {
        if (strcmp(customers[i].username, username) == 0) {
            customers[i].balance += amount;
            snprintf(msg, sizeof(msg), "Deposit Successful! New Balance: %.2f", customers[i].balance);
            send(sock, msg, strlen(msg), 0);
            break;
        }
    }

    file = fopen(CUSTOMER_FILE, "w");
    if (!file) {
        perror("Failed to open customer file for writing");
        return;
    }

    if (flock(fileno(file), LOCK_EX) == -1) {
        perror("Failed to lock customer file for writing");
        fclose(file);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %.2f %d %d\n", customers[i].username, customers[i].password, customers[i].balance, customers[i].id, customers[i].is_active);
    }
    log_transaction(username, "Deposit", amount);
    flock(fileno(file), LOCK_UN);
    fclose(file);

}

void withdraw_money(const char *username, int sock) {
    float amount;
    char msg[100];

    recv(sock, msg, sizeof(msg), 0);
    sscanf(msg, "%f", &amount);

    FILE *file = fopen(CUSTOMER_FILE, "r");
    if (!file) {
        perror("Failed to open customer file");
        return;
    }
    if (flock(fileno(file), LOCK_SH) == -1) {
        perror("Failed to lock customer file");
        fclose(file);
        return;
    }
    Customer customers[100];
    int count = 0;

    while (fscanf(file, "%s %s %f %d %d", customers[count].username, customers[count].password, &customers[count].balance, &customers[count].id, &customers[count].is_active) != EOF) {
        count++;
    }

    flock(fileno(file), LOCK_UN); 
    fclose(file);

    for (int i = 0; i < count; i++) {
        if (strcmp(customers[i].username, username) == 0) {
            if (customers[i].balance >= amount) {
                customers[i].balance -= amount;
                snprintf(msg, sizeof(msg), "Withdrawal Successful! New Balance: %.2f", customers[i].balance);
            } else {
                snprintf(msg, sizeof(msg), "Insufficient funds! Current Balance: %.2f", customers[i].balance);
            }
            send(sock, msg, strlen(msg), 0);
            break;
        }
    }

    file = fopen(CUSTOMER_FILE, "w");
    if (!file) {
        perror("Failed to open customer file for writing");
        return;
    }

    if (flock(fileno(file), LOCK_EX) == -1) {
        perror("Failed to lock customer file for writing");
        fclose(file);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %.2f %d %d\n", customers[i].username, customers[i].password, customers[i].balance, customers[i].id, customers[i].is_active);
    }

    log_transaction(username, "Withdrawal", amount);
    flock(fileno(file), LOCK_UN);
    fclose(file);
}

// Function to transfer funds
void transfer_funds(const char *username, int sock) {
    char msg[100];
    int target_account_number;
    float transfer_amount;

    recv(sock, msg, sizeof(msg), 0);
    sscanf(msg, "%d %f", &target_account_number, &transfer_amount);

    FILE *file = fopen(CUSTOMER_FILE, "r");
    if (!file) {
        perror("Failed to open customer file");
        return;
    }

    if (flock(fileno(file), LOCK_SH) == -1) {
        perror("Failed to lock customer file");
        fclose(file);
        return;
    }
    Customer customers[100];
    int count = 0;

    while (fscanf(file, "%s %s %f %d %d", customers[count].username, customers[count].password, &customers[count].balance, &customers[count].id, &customers[count].is_active) != EOF) {
        count++;
    }
    flock(fileno(file), LOCK_UN);
    fclose(file);

    Customer *current_user = NULL;
    Customer *target_user = NULL;

    for (int i = 0; i < count; i++) {
        if (strcmp(customers[i].username, username) == 0) {
            current_user = &customers[i];
        }
        if (customers[i].id == target_account_number) {
            target_user = &customers[i];
        }
    }

    if (current_user && target_user) {
        if (current_user->balance >= transfer_amount) {
            current_user->balance -= transfer_amount;
            target_user->balance += transfer_amount;
            snprintf(msg, sizeof(msg), "Transfer Successful! New Balance: %.2f", current_user->balance);
        } else {
            snprintf(msg, sizeof(msg), "Insufficient funds! Current Balance: %.2f", current_user->balance);
        }
    } else {
        snprintf(msg, sizeof(msg), "Transfer Failed! User not found.");
    }

    send(sock, msg, strlen(msg), 0);

    file = fopen(CUSTOMER_FILE, "w");
    if (!file) {
        perror("Failed to open customer file for writing");
        return;
    }

    if (flock(fileno(file), LOCK_EX) == -1) {
        perror("Failed to lock customer file for writing");
        fclose(file);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %.2f %d %d\n", customers[i].username, customers[i].password, customers[i].balance, customers[i].id, customers[i].is_active);
    }
    log_transaction(username, "Transfer", transfer_amount);
    flock(fileno(file), LOCK_UN);
    fclose(file);
}

void apply_for_loan(const char *username, int sock) {
    Loan loan;
    char msg[100];

    recv(sock, msg, sizeof(msg), 0);
    
    sscanf(msg, "%f %s %f %s %d", 
           &loan.loan_amount, 
           loan.loan_purpose, 
           &loan.monthly_income, 
           loan.employment_status, 
           &loan.contact_info);

    strcpy(loan.username, username);

    FILE *file = fopen(LOAN_FILE, "a");
    if (!file) {
        perror("Failed to open loan file");
        return;
    }

    fprintf(file, "%s %.2f %s %.2f %s %d\n", 
            loan.username, 
            loan.loan_amount, 
            loan.loan_purpose, 
            loan.monthly_income, 
            loan.employment_status, 
            loan.contact_info); 
    fclose(file);

    const char *success_msg = "Loan application submitted successfully!";
    send(sock, success_msg, strlen(success_msg), 0);
}

void change_password(const char *username, int sock) {
    char old_password[50], new_password[50];
    int password_matched = 0;

    recv(sock, old_password, sizeof(old_password), 0);
    old_password[strcspn(old_password, "\n")] = 0;  

    FILE *file = fopen(CUSTOMER_FILE, "r");
    if (!file) {
        perror("Failed to open customer file");
        return;
    }

    Customer customers[100];
    int count = 0;

    while (fscanf(file, "%s %s %f %d %d", customers[count].username, customers[count].password, &customers[count].balance, &customers[count].id, &customers[count].is_active) != EOF) {
        count++;
    }
    fclose(file);

    for (int i = 0; i < count; i++) {
        if (strcmp(customers[i].username, username) == 0 && strcmp(customers[i].password, old_password) == 0) {
            password_matched = 1;
            break;
        }
    }

    if (password_matched) {
        const char *match_msg = "Password match! Enter new password.";
        send(sock, match_msg, strlen(match_msg), 0);

        recv(sock, new_password, sizeof(new_password), 0);
        new_password[strcspn(new_password, "\n")] = 0;  
        for (int i = 0; i < count; i++) {
            if (strcmp(customers[i].username, username) == 0) {
                strcpy(customers[i].password, new_password);  
                break;
            }
        }

        file = fopen(CUSTOMER_FILE, "w");
        if (!file) {
            perror("Failed to open customer file for writing");
            return;
        }

        for (int i = 0; i < count; i++) {
            fprintf(file, "%s %s %.2f %d %d\n", customers[i].username, customers[i].password, customers[i].balance, customers[i].id, customers[i].is_active);
        }
        fclose(file);

        const char *success_msg = "Password changed successfully!";
        send(sock, success_msg, strlen(success_msg), 0);
    } else {
        const char *error_msg = "Old password did not match.";
        send(sock, error_msg, strlen(error_msg), 0);
    }
}

void add_feedback(const char *username, int sock){
    char feedback[500];
    FILE *file;

    recv(sock, feedback, sizeof(feedback), 0);

    file = fopen(FEEDBACK_FILE, "a");
    if (file == NULL) {
        perror("Error opening feedback file");
        send(sock, "Failed to save feedback\n", 24, 0);
        return;
    }
    fprintf(file, "Feedback from %s: %s\n", username, feedback);
    fclose(file);

    send(sock, "Thank you for your feedback!\n", 29, 0);
}

void view_transaction_history(const char *username, int sock) {
    FILE *file = fopen("Customer/transaction_history.txt", "r");
    if (!file) {
        perror("Failed to open transaction history file");
        return;
    }

    char line[BUFFER_SIZE];
    char history[BUFFER_SIZE * 10] = "";  
    while (fgets(line, sizeof(line), file)) {
        // Check if the line contains the username
        if (strstr(line, username) != NULL) {
            strcat(history, line);  
        }
    }

    fclose(file);

    if (strlen(history) == 0) {
        send(sock, "No transaction history found.\n", strlen("No transaction history found.\n"), 0);
    } else {
        send(sock, history, strlen(history), 0);
    }
}

void log_transaction(const char *username, const char *type, float amount) {
    FILE *file = fopen("Customer/transaction_history.txt", "a");  
    if (!file) {
        perror("Failed to open transaction history file");
        return;
    }
    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strcspn(timestamp, "\n")] = 0;  
    fprintf(file, "%s | %s | %.2f | %s\n", username, type, amount, timestamp);
    fclose(file);
}

