#include <stdio.h>
#include "functions.h"
#include <string.h>

void displayRoleMenu() {
    printf("\n***Bank Management System Using C***\n");
    printf("\n");
    printf("	CHOOSE YOUR ROLE\n");
    printf("     ======================\n");
    printf("	[1] Admin.\n");
    printf("	[2] User.\n");
    printf("	[0] Exit the Program.\n");
    printf("     ======================\n");
    printf("	Enter The Choice: ");
}

void displayLoginScreen() {
    printf("\n***Bank Management System Using C***\n");
    printf("\n");
    printf("		LOGIN\n");
    printf("     ======================\n");
    printf("     Email: test@gmail.com\n");
    printf("     Password: ******\n");
    printf("     ======================\n");
}

void displayMenu(){
	printf(" ***Student Management System Using C*** \n");
    printf("=========================================\n");
    printf("                  MENU                   \n");
    printf("=========================================\n");
    printf("[1] Add A New user.\n");
    printf("[2] Show All users.\n");
    printf("[3] Show detail an user.\n");
    printf("[4] Lock (Unlock) an user.\n");
    printf("[5] User details by ID (ID number).\n");
    printf("[6] Sort the user list (By name).\n");
    printf("[7] Search for users by name.\n");
    printf("[8] User Guideline.\n");
    printf("[9] About Us.\n");
    printf("[0] Exit the Program.\n");
    printf("=========================================\n");
    printf("Enter The Choice: ");
}
void displayExitMessage() {
	printf("\n");
    printf("==========  Thank You  ==========\n");
    printf("========== See You Soon =========\n");
}

bool isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            if (day > 29) return false;
        } else {
            if (day > 28) return false;
        }
    }
    return true;
}

bool isValidPhone(char *phone) {
	int cout=0;
    for (int i = 0; i < strlen(phone); i++) {
    	cout++;
        if (phone[i] < '0' || phone[i] > '9') {
            return false;
        }
    }
    if(cout++!=10){
    	return false;
	}
    return true;
}

bool isValidBalance(double balance) {
    return (balance >= 0);
}

bool isValidEmail(char *email) {
    return (strlen(email) > 0 && strchr(email, '@') != NULL);
}

bool isValidUsername(char *username) {

    return (strlen(username) > 0);
}

void saveUserToFile(User *user) {
    FILE *file = fopen("AccounttInfo.bin", "ab+");
    if (file == NULL) {
        printf("Error opening file for saving user!\n");
        return;
    }
    fwrite(user, sizeof(User), 1, file);
    fclose(file);
    printf("\nUser added successfully!\n");
}

void addANewUser(User *user) {
    user = (User *)malloc(sizeof(User));
	if (user == NULL) {
	    printf("Memory allocation failed!\n");
	    return;
	}
	
	getchar();
	do {
	    printf("Enter user ID (10 characters): ");
	    fgets(user->userId, 11, stdin);
	    user->userId[strcspn(user->userId, "\n")] = '\0';
	    getchar();
	} while (strlen(user->userId) != 10);
	
	
do {
	
    printf("Enter phone number (10 digits): ");
    fgets(user->phone, 11, stdin);
    user->phone[strcspn(user->phone, "\n")] = '\0';
} while (!isValidPhone(user->phone)&&strlen(user->phone) != 10);

	getchar();
	do {
	    printf("Enter email: ");
	    fgets(user->email, 21, stdin);
	    user->email[strcspn(user->email, "\n")] = '\0';
	} while (!isValidEmail(user->email));
	

do {
    printf("Enter username: ");
    fgets(user->userName, 21, stdin);
    user->userName[strcspn(user->userName, "\n")] = '\0';
} while (!isValidUsername(user->userName));

    do {
        printf("Enter full name: ");
        fgets(user->name, 21, stdin);
        user->name[strcspn(user->name, "\n")] = '\0';
    } while (strlen(user->name) == 0);
	
    do {
        printf("Enter birthdate:\n");
        printf("    Enter day: ");
        scanf("%d", &day);
        printf("    Enter month: ");
        scanf("%d", &month);
        printf("    Enter year: ");
        scanf("%d", &year);
        getchar();
    } while (!isValidDate(day, month, year));
    user->dateOfBirth.day = day;
    user->dateOfBirth.month = month;
    user->dateOfBirth.year = year;
    
    do {
        printf("Enter gender (male=1, female=0): ");
        scanf("%d", &user->gender);
    } while (user->gender != 0 && user->gender != 1);
    
    getchar();
    do {
        printf("Enter account balance: ");
        scanf("%lf", &balance);
    } while (!isValidBalance(balance));
    user->UserAccount.balance = balance;
    user->UserAccount.status = true;
    saveUserToFile(user);
    free(user);
}

void inputPassword(char *password) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();
        if (ch == '\n' || ch == '\r') {
            password[i] = '\0';
            break;
        } else if (ch == '\b' || ch == 127) {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else if (i < 49) {
            password[i++] = ch;
            printf("*");
        }
    }
    printf("\n");
}

void readUsersFromFile() {
    FILE *file = fopen("AccounttInfo.bin", "rb");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }

    User user;
    printf("|===============|================|==================|===================|========|\n");
    printf("|     ID        |    Name        |    Email         |    Phone          | Status |\n");
    printf("|===============|================|==================|===================|========|\n");

    while (fread(&user, sizeof(User), 1, file)) {
        printf("| %-15s | %-15s | %-15s | %-15s |  %-7s|\n",
		    user.userId, user.name, user.email, user.phone,  user.UserAccount.status ? "Active" : "Inactive");
    }
    printf("|===============|================|==================|===================|========|\n");

    fclose(file);
}

void searchUser() {
    char keyword[21];
    printf("Enter the user ID, name, or email to search: ");
    getchar();
    fgets(keyword, 21, stdin);
    keyword[strcspn(keyword, "\n")] = '\0';

    FILE *file = fopen("AccounttInfo.bin", "rb");
    if (file == NULL) {
        printf("Error opening file for search!\n");
        return;
    }

    User user;
    int found = 0;

    printf("|===============|================|==================|===================|========|\n");
    printf("|     ID        |    Name        |    Email         |    Phone          | Status |\n");
    printf("|===============|================|==================|===================|========|\n");

    while (fread(&user, sizeof(User), 1, file)) {
        if (strstr(user.userId, keyword) || strstr(user.name, keyword) || strstr(user.email, keyword)) {
            printf("| %-11s | %-20s | %-20s | %-11s |  %-6s|\n",
                user.userId, user.name, user.email, user.phone, user.UserAccount.status ? "Active" : "Inactive");
            found = 1;
        }
    }

    if (!found) {
        printf("No user found matching the keyword: %s\n", keyword);
    }

    fclose(file);
}

void searchUserByName() {
    char keyword[21]; // Từ khóa để tìm kiếm
    printf("Enter the name to search: ");
    getchar(); // Xóa bộ đệm
    fgets(keyword, 21, stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; // Xóa ký tự xuống dòng

    FILE *file = fopen("AccounttInfo.bin", "rb");
    if (file == NULL) {
        printf("Error opening file for search!\n");
        return;
    }

    User user;
    int found = 0; // Biến kiểm tra có tìm thấy hay không

    printf("|====================|=====================|=======================|======================|========|\n");
    printf("|        ID          |        Name         |         Email         |       Phone          | Status |\n");
    printf("|====================|=====================|=======================|======================|========|\n");

    while (fread(&user, sizeof(User), 1, file)) {
        if (strstr(user.name, keyword)) { // Tìm kiếm tên chứa từ khóa
            printf("| %-15s | %-15s | %-15s | %-15s |  %-7s|\n",
                user.userId, user.name, user.email, user.phone, user.UserAccount.status ? "Active" : "Inactive");
            found = 1;
        }
    }

    if (!found) {
        printf("No user found matching the name: %s\n", keyword);
    }

   printf("|====================|=====================|=======================|======================|========|\n");
    fclose(file);
}

void selectAmindMenu(int *choice,Transaction *Transaction,AccountInfo *AccountInfo,User *User){
	do{
		displayMenu();
		scanf("%d",choice);
		switch(*choice){
		case 1:
			addANewUser(&User);
			break;
		case 2:
			readUsersFromFile(User);
			printf("2");
			break;
		case 3:
			printf("3");
			break;
		case 4:
			printf("4");
			break;
		case 5:
			printf("5");
			break;
		case 6:
			printf("3");
			break;
		case 7:
			searchUser();
			break;
		case 8:
			printf("5");
			break;
		case 9:
			printf("6");
			break;
		case 0:
			*choice=0;
           	return 0;
    	default:
			printf("Invalid choice. Please try again.\n");
		}
	}while(1);
}
