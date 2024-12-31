#include <stdbool.h>

typedef struct{
    int month, day, year;
}Date;

typedef struct{
    char transferId[10];
    char receivingId[10];
    double amount;
    char type[10];
    char message[50];
    Date transactionDate;
}Transaction;

typedef struct{
    char userId[20];
    double balance;
    bool status;
    Transaction TransactionHistory[];
}AccountInfo;

typedef struct{
	char userName[20];
    char userId[10];
    char name[20];
    Date dateOfBirth;
    AccountInfo UserAccount;
    bool gender;
    char phone[10];
    char email[20];
}User;
