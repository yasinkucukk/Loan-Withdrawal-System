#include <stdio.h>
#include <stdlib.h>

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
            break;
        case 4:
            // printLoans function call here
            break;
        case 5:
            // createInstallments function call here
            break;
        case 6:
            // printInstallments function call here
            break;
        case 7:
            // readPayments function call here
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
