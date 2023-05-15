#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct installment
{
    char insid[30];
    short ispaid;
    char installmentdate[11];
    float amount;
    struct installment *nextins;
} installment;

typedef struct loan
{
    char loanid[30];
    char type[30];
    float totalamount;
    int totalinstallmentnum;
    char processdate[11];
    struct loan *nextloan;
    installment *insptr;
} loan;

typedef struct customer
{
    char name[20];
    char surname[30];
    int customerid;
    char customertype[20];
    struct customer *nextcust;
    double totaldebt;
    loan *loanptr;
} customer;

/*
customers.txt file is read and a linked list of customers is created. 
Id of the first read customer is 1 and 
id of the customer is incremented by one each time a new customer is read and placed into the linked list.
totaldebt of each customer is 0 initially.
Head pointer of the linked list is called as customers
Each linked list members are connected to each other using the nextcust pointer.
Id of the first read customer is 1 and id of the customer is incremented by one each time a new customer is read and placed into the linked list. 
*/


void readCustomers(customer **customers){
    FILE *fp = fopen("C:\\Users\\yasin\\Desktop\\Data project1\\customers.txt", "r");
    if (fp == NULL)
    {
        printf("File could not be opened\n");
        exit(1);
    }
    customer *temp = *customers;
    while (!feof(fp))
    {
        
        if (*customers == NULL)
        {
            *customers = (customer *)malloc(sizeof(customer));
            fscanf(fp, "%s %s %s", (*customers)->name, (*customers)->surname, (*customers)->customertype);
            (*customers)->customerid = 1;
            (*customers)->totaldebt = 0;
            (*customers)->nextcust = NULL;
            (*customers)->loanptr = NULL;
            temp = *customers;
        }
        else
        {
            temp->nextcust = (customer *)malloc(sizeof(customer));
            fscanf(fp, "%s %s %s", temp->nextcust->name, temp->nextcust->surname, temp->nextcust->customertype);
            temp->nextcust->customerid = temp->customerid + 1;
            temp->nextcust->totaldebt = 0;
            temp->nextcust->nextcust = NULL;
            temp->nextcust->loanptr = NULL;
            temp = temp->nextcust;
        }
    }
    fclose(fp);
}


void readLoans(customer **customers){
    FILE *fp = fopen("C:\\Users\\yasin\\Desktop\\Data project1\\loans.txt", "r");
    if (fp == NULL)
    {
        printf("File could not be opened\n");
        exit(1);
    }
    customer *temp = *customers;
    
    while (!feof(fp))
    {
        char name[20], surname[30], type[30], processdate[11];
        float totalamount;
        int totalinstallmentnum;
        fscanf(fp, "%s %s %s %f %d %s", name, surname, type, &totalamount, &totalinstallmentnum, processdate);
        int count = 2;
		char countStr[50];
        while (temp != NULL)
        {
            if (strcmp(temp->name, name) == 0 && strcmp(temp->surname, surname) == 0)
            {
                if (temp->loanptr == NULL)
                {
                    temp->loanptr = (loan *)malloc(sizeof(loan));    
                    strcpy(temp->loanptr->loanid, strcat(strcat(itoa(temp->customerid, temp->loanptr->loanid, 10), "L"), "1"));
                    strcpy(temp->loanptr->type, type);
                    temp->loanptr->totalamount = totalamount;
                    temp->loanptr->totalinstallmentnum = totalinstallmentnum;
                    strcpy(temp->loanptr->processdate, processdate);
                    temp->loanptr->nextloan = NULL;
                    temp->loanptr->insptr = NULL;
               }
                else
                {
                    loan *temp2 = temp->loanptr;
                    while (temp2->nextloan != NULL)
                    {
                        temp2 = temp2->nextloan;
                        count++;
                    }
                    temp2->nextloan = (loan *)malloc(sizeof(loan));        
                    strcpy(temp2->nextloan->loanid, strcat(strcat(itoa(temp->customerid, temp2->nextloan->loanid, 10), "L"), itoa(count, countStr, 10)));
                    strcpy(temp2->nextloan->type, type);
                    temp2->nextloan->totalamount = totalamount;
                    temp2->nextloan->totalinstallmentnum = totalinstallmentnum;
                    strcpy(temp2->nextloan->processdate, processdate);
                    temp2->nextloan->nextloan = NULL;
                    temp2->nextloan->insptr = NULL;  
                }           
            }
            temp = temp->nextcust;
        }
        temp = *customers;
    }
}

void printInstallments(customer *customers){
    
    while (customers != NULL)
    {
        printf("-----------------------------------------------\n");
        printf("%d - %s %s - type : %s - total debt : %d\n", customers->customerid, customers->name, customers->surname, customers->customertype, customers->totaldebt);
        loan *temp = customers->loanptr;
        while (temp != NULL)
        {
            printf("\t%s : %s - %.2f - %s - %d\n", temp->loanid, temp->type, temp->totalamount, temp->processdate, temp->totalinstallmentnum);
            installment *temp2 = temp->insptr;
            while (temp2 != NULL)
            {
                printf("\t\t%s -> %s - %.2f - ", temp2->insid, temp2->installmentdate, temp2->amount);
                if (temp2->ispaid == 0)
                {
                    printf("To be Paid\n");
                }
                else if (temp2->ispaid == 1)
                {
                    printf("Paid\n");
                }
                else
                {
                    printf("Delayed Payment\n");
                }
                temp2 = temp2->nextins;
            }
            temp = temp->nextloan;
        }
        customers = customers->nextcust;
    }

}


/*printCustomers function is called and the customers linked list is traversed and name,
 surname, type and totaldebt values of each customers in the list
 are printed using printCustomers function. 
*/

void printCustomers(customer *customers){
    
    while (customers != NULL)
    {
        printf("-----------------------------------------------\n");
        printf("%d - %s %s - type : %s - total debt : %d\n", customers->customerid, customers->name, customers->surname, customers->customertype, customers->totaldebt);
        customers = customers->nextcust;
    }
}
/*printLoans function is called to iterate through the linked list and print the loan related information.   
*/
void printLoans(customer *customers){
    
    while (customers != NULL)
    {
        printf("-----------------------------------------------\n");
        printf("%d - %s %s - type : %s - total debt : %d\n", customers->customerid, customers->name, customers->surname, customers->customertype, customers->totaldebt);
        loan *temp = customers->loanptr;
        while (temp != NULL)
        {
            printf("\t%s : %s - %.2f - %s - %d\n", temp->loanid, temp->type, temp->totalamount, temp->processdate, temp->totalinstallmentnum);
            temp = temp->nextloan;
        }
        customers = customers->nextcust;
    }
}



void createInstallments(customer *customers){
    int count = 1;
	char countStr[50];
    while (customers != NULL)
    {
        loan *temp = customers->loanptr;
        while (temp != NULL)
        {
            char tempdate[20];
            strcpy(tempdate, temp->processdate);
            char *token = strtok(tempdate, "/");
            int day = atoi(token);
            token = strtok(NULL, "/");
            int month = atoi(token);
            token = strtok(NULL, "/");
            int year = atoi(token);
            int totaldays = 30 * temp->totalinstallmentnum;
  
            while (day <= totaldays)
            {
                if (temp->insptr == NULL)
                {
                    temp->insptr = (installment *)malloc(sizeof(installment));
                    char id[50];
                	strcpy(id , temp ->loanid);
                    strcpy(temp->insptr->insid, strcat(strcat(id, "I"), itoa(count, countStr, 10)));
                    strcpy(temp->insptr->installmentdate, temp->processdate);
                    temp->insptr->amount = temp->totalamount / temp->totalinstallmentnum;
                    temp->insptr->ispaid = 0;
                    temp->insptr->nextins = NULL;
                }
                else
                {
                    installment *temp2 = temp->insptr;
                    while (temp2->nextins != NULL)
                    {
                        temp2 = temp2->nextins;
                    }
                  
                 	count++;
                    temp2->nextins = (installment *)malloc(sizeof(installment));
                    char id[50];
                	strcpy(id , temp ->loanid);
                    strcpy(temp2->nextins->insid, strcat(strcat(id, "I"), itoa(count, countStr, 10)));
                    strcpy(temp2->nextins->installmentdate, temp->processdate);
                    temp2->nextins->amount = temp->totalamount / temp->totalinstallmentnum;
                    temp2->nextins->ispaid = 0;
                    temp2->nextins->nextins = NULL;
                
                }
                day += 30;
                month++;

                if (month > 12)
                {
                    month = 1;
                    year++;
                }
                
                sprintf(tempdate, "%d/%d/%d", (day %30), month, year);
                strcpy(temp->processdate, tempdate);
            }
			count = 1;
            temp = temp->nextloan;
        }
  		
        customers = customers->nextcust;
    }
}

/*This function updates the ispaid field as 1 of the paid installments read from the file. 
payments.txt file For example, "9L1 ALL" means all installments of loan 9L1 are paid. In addition, "1L1 4" means fourth installment of loan 1L1 is paid.
example payments.txt file
id of the loan and which installment of the loan is paid.
9L1 ALL 
1L1 4
1L1 1
1L1 2

use fscanf
*/

void readPayments(customer *customers)
{

    FILE *fptr;
    fptr = fopen("C:\\Users\\yasin\\Desktop\\Data project1\\payments.txt", "r");
    if (fptr == NULL)
    {
        printf("File could not be opened\n");
        exit(1);
    }
    char loanid[50];
    char installmentid[50];
    while (!feof(fptr))
    {
        fscanf(fptr, "%s %s", loanid, installmentid);
        customer *temp = customers;
        while (temp != NULL)
        {
            loan *temp2 = temp->loanptr;
            while (temp2 != NULL)
            {
                if (strcmp(temp2->loanid, loanid) == 0)
                {
                    installment *temp3 = temp2->insptr;
                    while (temp3 != NULL)
                    {
                    	char id[50];
                		strcpy(id , temp2 ->loanid);
                        if (strcmp(temp3->insid, strcat(strcat(id,"I"),installmentid)) == 0)
                        {
                            temp3->ispaid = 1;
                            temp->totaldebt -= temp3->amount;
                        }
                        if(strcmp("ALL" , installmentid )==0){
                        	temp3->ispaid = 1;
                            temp->totaldebt -= temp3->amount;
						}
                        temp3 = temp3->nextins;
                    }
                }
                temp2 = temp2->nextloan;
            }
            temp = temp->nextcust;
        }
    }
    fclose(fptr);
    

}
    

void findUnpaidInstallments(customer *customers){
    
    char date[20];
    printf("Enter a date: ");
    scanf("%s", date);
    customer *temp = customers;
    while (temp != NULL)
    {
        loan *temp2 = temp->loanptr;
        while (temp2 != NULL)
        {
            installment *temp3 = temp2->insptr;
            while (temp3 != NULL)
            {
                if (strcmp(temp3->installmentdate, date) != 0 && temp3->ispaid ==0)
                {
                    temp3->ispaid = 2;
                }
                temp3 = temp3->nextins;
            }
            temp2 = temp2->nextloan;
        }
        temp = temp->nextcust;
    }
    temp = customers;
    while (temp != NULL)
    {
        loan *temp2 = temp->loanptr;
        float debt = 0;
        int count = 0;
        while (temp2 != NULL)
        {
            installment *temp3 = temp2->insptr;
            while (temp3 != NULL)
            {
                if (temp3->ispaid == 2)
                {
                    debt += temp3->amount;
                    count++;
                }
                temp3 = temp3->nextins;
            }
            temp2 = temp2->nextloan;
        }
        if (count != 0)
        {
            printf("%s %s : Debt %.2f Number of Delayed Installments %d\n", temp->name, temp->surname, debt, count);
        }
        temp = temp->nextcust;
    }
}


// function deletePaidInstallments, if a customer has no loan then delete his loans
void deletePaidInstallments(customer *temp)
{
    loan *temp2 = temp->loanptr;
    while (temp2 != NULL)
    {
        installment *temp3 = temp2->insptr;
        while (temp3 != NULL)
        {
            if (temp3->ispaid == 1)
            {
                temp3->ispaid = 3;
            }
            temp3 = temp3->nextins;
        }
        temp2 = temp2->nextloan;
    }
    temp2 = temp->loanptr;
    while (temp2 != NULL)
    {
        installment *temp3 = temp2->insptr;
        while (temp3 != NULL)
        {
            if (temp3->ispaid == 3)
            {
                temp2->insptr = temp3->nextins;
                free(temp3);
            }
            temp3 = temp3->nextins;
        }
        temp2 = temp2->nextloan;
    }
    temp2 = temp->loanptr;
    while (temp2 != NULL)
    {
        if (temp2->insptr == NULL)
        {
            temp->loanptr = temp2->nextloan;
            free(temp2);
        }
        temp2 = temp2->nextloan;
    }
}


int main()
{
    customer *customers = NULL;
    int option = 1000;
    while (option != 0)
    {
        printf("\n\n#############################################################\n");
        printf("1. read customers.\n");
        printf("2. print customers.\n");
        printf("3. read loans.\n");
        printf("4. print loans.\n");
        printf("5. create installments.\n");
        printf("6. print installments.\n");
        printf("7. read payments.\n");
        printf("8. find unpaid installments.\n");
        printf("9. delete completely paid installments.\n");
        printf("please select your option : \n");
        scanf("%d", &option);
        printf("#############################################################\n");

        switch (option)
        {
        case 1:
            // readCustomers function call here
            readCustomers(&customers);
            break;
        case 2:
            // printCustomers function call here
            printCustomers(customers);
            break;
        case 3:
            // readLoans function call here
            readLoans(&customers);
            break;
        case 4:
            // printLoans function call here
            printLoans(customers);
            break;
        case 5:
            // createInstallments function call here
            createInstallments(customers);
            break;
        case 6:
            // printInstallments function call here
            printInstallments(customers);
            break;
        case 7:
            // readPayments function call here
            readPayments(customers);
            break;
        case 8:
            // findUnpaidInstallments function call here
            findUnpaidInstallments(customers);
            break;
        case 9:
            // deletePaidInstallments function call here
            deletePaidInstallments(&customers);
            break;
        case 0:
            break;
        default:
            printf("invalid option\n");
        }
    }
    return 0;
}
