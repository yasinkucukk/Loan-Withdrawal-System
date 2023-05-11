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
        return;
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
        return;
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
    while (customers != NULL)
    {
        loan *temp = customers->loanptr;
        while (temp != NULL)
        {
            if (temp->insptr == NULL)
            {
                temp->insptr = (installment *)malloc(sizeof(installment));
                strcpy(temp->insptr->insid, strcat(strcat(temp->loanid, "I"), "1"));
                temp->insptr->ispaid = 0;
                strcpy(temp->insptr->installmentdate, temp->processdate);
                temp->insptr->amount = temp->totalamount / temp->totalinstallmentnum;
                temp->insptr->nextins = NULL;
            }
            else
            {
                installment *temp2 = temp->insptr;
                while (temp2->nextins != NULL)
                {
                    temp2 = temp2->nextins;
                }
                temp2->nextins = (installment *)malloc(sizeof(installment));
                strcpy(temp2->nextins->insid, strcat(strcat(temp->loanid, "I"), itoa(temp2->insid + 1, temp2->nextins->insid, 10)));
                temp2->nextins->ispaid = 0;
                strcpy(temp2->nextins->installmentdate, temp->processdate);
                temp2->nextins->amount = temp->totalamount / temp->totalinstallmentnum;
                temp2->nextins->nextins = NULL;
            }
            temp = temp->nextloan;

        }

        customers = customers->nextcust;
    }
}


void readPayments(customer *customers){

    FILE *fp = fopen("C:\\Users\\yasin\\Desktop\\Data project1\\payments.txt", "r");
    if (fp == NULL)
    {
        printf("File could not be opened.\n");
        return;
    }
    char line[100];
    while (fgets(line, 100, fp) != NULL)
    {
        char *token = strtok(line, " ");
        char *loanid = token;
        token = strtok(NULL, " ");
        char *insid = token;
        while (customers != NULL)
        {
            loan *temp = customers->loanptr;
            while (temp != NULL)
            {
                if (strcmp(temp->loanid, loanid) == 0)
                {
                    installment *temp2 = temp->insptr;
                    while (temp2 != NULL)
                    {
                        if (strcmp(temp2->insid, insid) == 0)
                        {
                            temp2->ispaid = 1;
                            break;
                        }
                        temp2 = temp2->nextins;
                    }
                    break;
                }
                temp = temp->nextloan;
            }
            customers = customers->nextcust;
        }
    }
    fclose(fp);
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
            break;
        case 9:
            // DeletePaidInstallments function call here
            break;
        case 0:
            break;
        default:
            printf("invalid option\n");
        }
    }
    return 0;
}
