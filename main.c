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

void readCustomers(customer **customers)
{
    FILE *fp = fopen("customers.txt", "r");
    if (fp == NULL)
    {
        printf("File could not be opened\n");
        exit(1);
    }

    customer *temp = *customers; // Create a temporary pointer to traverse the customer linked list

    while (!feof(fp))
    { // Loop until the end of the file is reached
        if (*customers == NULL)
        {                                                                                                  // If the customer list is empty
            *customers = (customer *)malloc(sizeof(customer));                                             // Allocate memory for the first customer
            fscanf(fp, "%s %s %s", (*customers)->name, (*customers)->surname, (*customers)->customertype); // Read customer data from the file
            (*customers)->customerid = 1;                                                                  // Assign a customer ID
            (*customers)->totaldebt = 0;                                                                   // Initialize total debt to 0
            (*customers)->nextcust = NULL;                                                                 // Set the next customer pointer to NULL
            (*customers)->loanptr = NULL;                                                                  // Set the loan pointer to NULL
            temp = *customers;                                                                             // Update the temporary pointer to the current customer
        }
        else
        {
            temp->nextcust = (customer *)malloc(sizeof(customer));                                               // Allocate memory for the next customer
            fscanf(fp, "%s %s %s", temp->nextcust->name, temp->nextcust->surname, temp->nextcust->customertype); // Read customer data from the file
            temp->nextcust->customerid = temp->customerid + 1;                                                   // Assign a customer ID
            temp->nextcust->totaldebt = 0;                                                                       // Initialize total debt to 0
            temp->nextcust->nextcust = NULL;                                                                     // Set the next customer pointer to NULL
            temp->nextcust->loanptr = NULL;                                                                      // Set the loan pointer to NULL
            temp = temp->nextcust;                                                                               // Update the temporary pointer to the current customer
        }
    }

    fclose(fp); // Close the file
}

void readLoans(customer **customers)
{
    FILE *fp = fopen("loans.txt", "r");
    if (fp == NULL)
    {
        printf("File could not be opened\n");
        exit(1);
    }
    customer *temp = *customers; // Create a temporary pointer to traverse the customer linked list

    while (!feof(fp))
    { // Loop until the end of the file is reached
        char name[20], surname[30], type[30], processdate[11];
        float totalamount;
        int totalinstallmentnum;

        fscanf(fp, "%s %s %s %f %d %s", name, surname, type, &totalamount, &totalinstallmentnum, processdate);
        // Read loan data from the file

        int count = 2;     // Counter for loan IDs
        char countStr[50]; // String representation of the counter

        while (temp != NULL)
        { // Traverse the customer linked list
            if (strcmp(temp->name, name) == 0 && strcmp(temp->surname, surname) == 0)
            {
                // If the customer matches the loan data

                if (temp->loanptr == NULL)
                {                                                 // If the customer doesn't have any loans
                    temp->loanptr = (loan *)malloc(sizeof(loan)); // Allocate memory for the loan

                    // Create the loan ID using customer ID and loan counter
                    strcpy(temp->loanptr->loanid, strcat(strcat(itoa(temp->customerid, temp->loanptr->loanid, 10), "L"), "1"));

                    strcpy(temp->loanptr->type, type);                        // Copy loan type
                    temp->loanptr->totalamount = totalamount;                 // Assign total amount
                    temp->loanptr->totalinstallmentnum = totalinstallmentnum; // Assign total installment number
                    strcpy(temp->loanptr->processdate, processdate);          // Copy process date
                    temp->loanptr->nextloan = NULL;                           // Set the next loan pointer to NULL
                    temp->loanptr->insptr = NULL;                             // Set the installment pointer to NULL
                }
                else
                {
                    loan *temp2 = temp->loanptr;

                    while (temp2->nextloan != NULL)
                    {
                        temp2 = temp2->nextloan;
                        count++; // Increment the loan counter
                    }

                    temp2->nextloan = (loan *)malloc(sizeof(loan)); // Allocate memory for the next loan

                    // Create the loan ID using customer ID and loan counter
                    strcpy(temp2->nextloan->loanid, strcat(strcat(itoa(temp->customerid, temp2->nextloan->loanid, 10), "L"), itoa(count, countStr, 10)));

                    strcpy(temp2->nextloan->type, type);                        // Copy loan type
                    temp2->nextloan->totalamount = totalamount;                 // Assign total amount
                    temp2->nextloan->totalinstallmentnum = totalinstallmentnum; // Assign total installment number
                    strcpy(temp2->nextloan->processdate, processdate);          // Copy process date
                    temp2->nextloan->nextloan = NULL;                           // Set the next loan pointer to NULL
                    temp2->nextloan->insptr = NULL;                             // Set the installment pointer to NULL
                }
            }
            temp = temp->nextcust; // Move to the next customer
        }
        temp = *customers; // Reset the temporary pointer to the start of the customer list}
    }
}

void printCustomers(customer *customers, FILE *file)
{

    while (customers != NULL)
    {

        // Print customer information including ID, name, surname, customertype, and totaldebt
        printf("-----------------------------------------------\n");
        fprintf(file, "-----------------------------------------------\n");

        printf("%d - %s %s - type : %s - total debt : %.lf\n", customers->customerid, customers->name, customers->surname, customers->customertype, customers->totaldebt);
        fprintf(file, "%d - %s %s - type : %s - total debt : %.lf\n", customers->customerid, customers->name, customers->surname, customers->customertype, customers->totaldebt);

        customers = customers->nextcust; // Move to the next customer
    }
}

void printLoans(customer *customers, FILE *file)
{

    while (customers != NULL)
    {

        // Print customer information including ID, name, surname, customertype, and totaldebt
        printf("-----------------------------------------------\n");
        printf("%d - %s %s - type : %s - total debt : %.lf\n", customers->customerid, customers->name, customers->surname, customers->customertype, customers->totaldebt);

        fprintf(file, "-----------------------------------------------\n");
        fprintf(file, "%d - %s %s - type : %s - total debt : %.lf\n", customers->customerid, customers->name, customers->surname, customers->customertype, customers->totaldebt);

        loan *temp = customers->loanptr; // Pointer to traverse the loans
        while (temp != NULL)
        {
            // Print loan information including loan ID, type, total amount, process date, and total installment number
            printf("\t%s : %s - %.2f - %s - %d\n", temp->loanid, temp->type, temp->totalamount, temp->processdate, temp->totalinstallmentnum);
            fprintf(file, "\t%s : %s - %.2f - %s - %d\n", temp->loanid, temp->type, temp->totalamount, temp->processdate, temp->totalinstallmentnum);

            temp = temp->nextloan; // Move to the next loan
        }
        customers = customers->nextcust; // Move to the next customer
    }
}

void createInstallments(customer *customers)
{

    int count = 1;     // Counter for installment IDs
    char countStr[50]; // String to hold installment ID

    while (customers != NULL)
    {
        loan *temp = customers->loanptr;
        while (temp != NULL)
        {
            char tempdate[20]; // String to hold loan process date for manipulation
            strcpy(tempdate, temp->processdate);
            char *token = strtok(tempdate, "/");            // Tokenize the date string by '/'
            int day = atoi(token);                          // Extract day value from token
            token = strtok(NULL, "/");                      // Move the token to the next string after '/'
            int month = atoi(token);                        // Extract month value from token
            token = strtok(NULL, "/");                      // Move the token to the next string after '/'
            int year = atoi(token);                         // Extract year value from token
            int totaldays = 30 * temp->totalinstallmentnum; // Calculate total number of days for the installment period

            while (day <= totaldays)
            {
                if (temp->insptr == NULL)
                {
                    temp->insptr = (installment *)malloc(sizeof(installment));
                    char id[50];
                    strcpy(id, temp->loanid);
                    strcpy(temp->insptr->insid, strcat(strcat(id, "I"), itoa(count, countStr, 10))); // Generate installment ID using the loan ID and the counter
                    strcpy(temp->insptr->installmentdate, temp->processdate);                        // Set the installment date to the loan process date
                    temp->insptr->amount = temp->totalamount / temp->totalinstallmentnum;            // Calculate the installment amount
                    temp->insptr->ispaid = 0;                                                        // Set the installment payment status to "To be Paid"
                    temp->insptr->nextins = NULL;                                                    // Set the next installment pointer to NULL
                }
                else
                {
                    installment *temp2 = temp->insptr;

                    while (temp2->nextins != NULL) // Traverse to the last installment record
                    {
                        temp2 = temp2->nextins;
                    }

                    count++;
                    temp2->nextins = (installment *)malloc(sizeof(installment));
                    char id[50];
                    strcpy(id, temp->loanid);
                    strcpy(temp2->nextins->insid, strcat(strcat(id, "I"), itoa(count, countStr, 10))); // Generate installment ID using the loan ID and the counter
                    strcpy(temp2->nextins->installmentdate, temp->processdate);                        // Set the installment date to the loan process date
                    temp2->nextins->amount = temp->totalamount / temp->totalinstallmentnum;            // Calculate the installment amount
                    temp2->nextins->ispaid = 0;                                                        // Set the installment payment status to "To be Paid"
                    temp2->nextins->nextins = NULL;                                                    // Set the next installment pointer to NULL
                }
                day += 30; // Increment the day by 30 for the next installment
                month++;   // Increment the

                if (month > 12) // Check if the month exceeds 12
                {
                    month = 1; // Reset the month to 1
                    year++;    // Increment the year
                }

                sprintf(tempdate, "%d/%d/%d", (day % 30), month, year); // Format the new installment date
                strcpy(temp->processdate, tempdate);                    // Update the loan process date with the new installment date
            }

            count = 1;             // Reset the installment counter
            temp = temp->nextloan; // Move to the next loan record
        }

        customers = customers->nextcust; // Move to the next customer record
    }
}

void printInstallments(customer *customers, FILE *file)
{

    while (customers != NULL)
    {
        printf("-----------------------------------------------\n");
        printf("%d - %s %s - type : %s - total debt : %.lf\n", customers->customerid, customers->name, customers->surname, customers->customertype, customers->totaldebt);

        fprintf(file, "-----------------------------------------------\n");
        fprintf(file, "%d - %s %s - type : %s - total debt : %.lf\n", customers->customerid, customers->name, customers->surname, customers->customertype, customers->totaldebt);

        loan *temp = customers->loanptr; // Pointer to traverse the loans

        while (temp != NULL)
        {
            printf("\t%s : %s - %.2f - %s - %d\n", temp->loanid, temp->type, temp->totalamount, temp->processdate, temp->totalinstallmentnum);
            fprintf(file, "\t%s : %s - %.2f - %s - %d\n", temp->loanid, temp->type, temp->totalamount, temp->processdate, temp->totalinstallmentnum);

            installment *temp2 = temp->insptr; // Pointer to traverse the installments

            while (temp2 != NULL)
            {
                printf("\t\t%s -> %s - %.2f - ", temp2->insid, temp2->installmentdate, temp2->amount);
                fprintf(file, "\t\t%s -> %s - %.2f - ", temp2->insid, temp2->installmentdate, temp2->amount);

                if (temp2->ispaid == 0)
                {
                    printf("To be Paid\n");
                    fprintf(file, "To be Paid\n");
                }
                else if (temp2->ispaid == 1)
                {
                    printf("Paid\n");
                    fprintf(file, "Paid\n");
                }
                else
                {
                    printf("Delayed Payment\n");
                    fprintf(file, "Delayed Payment\n");
                }
                temp2 = temp2->nextins; // Move to the next installment
            }
            temp = temp->nextloan; // Move to the next loan
        }
        customers = customers->nextcust; // Move to the next customer
    }
}

void readPayments(customer *customers)
{

    FILE *fptr;
    fptr = fopen("payments.txt", "r");

    if (fptr == NULL)
    {
        printf("File could not be opened");
        exit(1);
    }
    char loanid[50];
    char installmentid[50];

    // Read loan id and installment id from the file until end of file is reached
    while (!feof(fptr))
    {
        fscanf(fptr, "%s %s", loanid, installmentid);

        // Traverse the linked list of customers to find the corresponding loan and installment
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
                        strcpy(id, temp2->loanid);

                        // If the installment id matches, mark the installment as paid and update the customer's total debt
                        if (strcmp(temp3->insid, strcat(strcat(id, "I"), installmentid)) == 0)
                        {
                            temp3->ispaid = 1;
                            temp->totaldebt -= temp3->amount;
                        }

                        // If installment id is "ALL", mark all installments of the loan as paid and update the customer's total debt
                        if (strcmp("ALL", installmentid) == 0)
                        {
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

void findUnpaidInstallments(customer *customers, FILE *file)
{

    // Prompt the user to enter a date
    char date[20];
    printf("Enter a date: ");
    fprintf(file, "Enter a date: ");

    scanf("%s", date);
    fprintf(file, "%s\n", date);

    // Iterate through each customer
    customer *temp = customers;

    while (temp != NULL)
    {

        // Iterate through each loan of the customer
        loan *temp2 = temp->loanptr;

        while (temp2 != NULL)
        {
            // Iterate through each installment of the loan
            installment *temp3 = temp2->insptr;

            while (temp3 != NULL)
            {

                // Check if the installment date is different from the input date and is still unpaid
                if (strcmp(temp3->installmentdate, date) != 0 && temp3->ispaid == 0)
                {
                    // Mark the installment as delayed
                    temp3->ispaid = 2;
                }
                temp3 = temp3->nextins;
            }
            temp2 = temp2->nextloan;
        }
        temp = temp->nextcust;
    }

    // Iterate through each customer again to calculate total debt and count delayed installments
    temp = customers;

    while (temp != NULL)
    {

        // Iterate through each loan of the customer
        loan *temp2 = temp->loanptr;
        float debt = 0;
        int count = 0;
        while (temp2 != NULL)
        {

            // Iterate through each installment of the loan
            installment *temp3 = temp2->insptr;

            while (temp3 != NULL)
            {

                // Check if the installment is marked as delayed
                if (temp3->ispaid == 2)
                {
                    // Accumulate the amount of delayed installments and calculate total debt
                    debt += temp3->amount;
                    count++;
                }
                temp3 = temp3->nextins;
            }
            temp2 = temp2->nextloan;
        }
        // Print the customer's name, surname, total debt, and the number of delayed installments
        if (count != 0)
        {
            printf("%s %s : Debt %.2f Number of Delayed Installments %d\n", temp->name, temp->surname, debt, count);
            fprintf(file, "%s %s : Debt %.2f Number of Delayed Installments %d\n", temp->name, temp->surname, debt, count);
        }
        temp = temp->nextcust;
    }
}

void deletePaidInstallments(customer *customers)
{

    // Iterate through each loan of the customer
    customer *temp = customers;
    while (temp != NULL)
    {
        loan *temp2 = temp->loanptr;
        while (temp2 != NULL)
        {
            // Iterate through each installment of the loan
            installment *temp3 = temp2->insptr;
            while (temp3 != NULL)
            {

                // Check if the installment has been paid
                if (temp3->ispaid == 1)
                {
                    // Mark the installment as to-be-deleted
                    temp3->ispaid = 3;
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
        while (temp2 != NULL)
        {
            installment *temp3 = temp2->insptr;
            while (temp3 != NULL)
            {
                if (temp3->ispaid == 3)
                {
                    installment *temp4 = temp2->insptr;
                    if (temp4 == temp3)
                    {
                        temp2->insptr = temp3->nextins;
                        free(temp3);
                        temp3 = temp2->insptr;
                    }
                    else
                    {
                        while (temp4->nextins != temp3)
                        {
                            temp4 = temp4->nextins;
                        }
                        temp4->nextins = temp3->nextins;
                        free(temp3);
                        temp3 = temp4->nextins;
                    }
                }
                else
                {
                    temp3 = temp3->nextins;
                }
            }
            temp2 = temp2->nextloan;
        }
        temp = temp->nextcust;
    }
}

int main()
{
    FILE *file = fopen("output.txt", "w");
    if (file != NULL)
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

            fprintf(file, "\n\n#############################################################\n");
            fprintf(file, "1. read customers.\n");
            fprintf(file, "2. print customers.\n");
            fprintf(file, "3. read loans.\n");
            fprintf(file, "4. print loans.\n");
            fprintf(file, "5. create installments.\n");
            fprintf(file, "6. print installments.\n");
            fprintf(file, "7. read payments.\n");
            fprintf(file, "8. find unpaid installments.\n");
            fprintf(file, "9. delete completely paid installments.\n");
            fprintf(file, "please select your option : \n");
            fprintf(file, "%d\n", option);
            fprintf(file, "#############################################################\n");

            switch (option)
            {
            case 1:
                // readCustomers function call here
                readCustomers(&customers);
                break;
            case 2:
                // printCustomers function call here
                printCustomers(customers, file);
                break;
            case 3:
                // readLoans function call here
                readLoans(&customers);
                break;
            case 4:
                // printLoans function call here
                printLoans(customers, file);
                break;
            case 5:
                // createInstallments function call here
                createInstallments(customers);
                break;
            case 6:
                // printInstallments function call here
                printInstallments(customers, file);
                break;
            case 7:
                // readPayments function call here
                readPayments(customers);
                break;
            case 8:
                // findUnpaidInstallments function call here
                findUnpaidInstallments(customers, file);
                break;
            case 9:
                // deletePaidInstallments function call here
                deletePaidInstallments(customers);
                break;
            case 0:
                break;
            default:
                printf("invalid option\n");
                fprintf(file, "invalid option\n");
            }
        }
    }
    else
    {
        printf("File could not be opened\n.\n");
        fprintf(file, "File could not be opened\n.\n");
    }
    fclose(file);
    return 0;
}
