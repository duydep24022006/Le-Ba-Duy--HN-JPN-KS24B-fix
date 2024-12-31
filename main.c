#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char *argv[]) {
	Transaction *transaction=(Transaction *)malloc(sizeof(Transaction));
	if (transaction == NULL) {
        printf("\nCannot allocate memory.\n");
        return;
    }
	AccountInfo *accountInfo=(AccountInfo *)malloc(sizeof(AccountInfo));
	if (accountInfo == NULL) {
        printf("\nCannot allocate memory.\n");
        return;                
    }
	User *user = (User *)malloc(sizeof(User));
    if (user == NULL) {
        printf("\nCannot allocate memory.\n");
        return;
    }
	                                             
	do{
		printf("\n ");
		displayRoleMenu();
		scanf("%d",&choice);
		switch(choice) {
			case 1:
				selectAmindMenu(&choice,transaction,accountInfo,user);
				break;
			case 2:
				break;
			case 0:
				displayExitMessage();
				free(transaction);
				free(accountInfo);
				free(user);
           	 	return 0;
		default:
			printf("Invalid choice. Please try again.\n");
		}
		
	}while(1);
}
