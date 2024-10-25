#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#ifdef _WIN32
#include <direct.h>
#define CreateDir _mkdir
#else
#include <sys/stat.h>
#define CreateDir mkdir
#endif
typedef struct
{
    int year;
    int month;
} date;
typedef struct
{
    char account_number[11];
    char name[200];
    char phone[12];
    char email[200];
    float balance;
    date d;
} account;

account acc[1000];
account temp[1000];
int account_counter = 0; // counting users and accounts from the file to use in loops
time_t t;
char account_numberin[30]; // to use in search function

void construct_date(int month, int year)
{
    acc[account_counter].d.month = month;
    acc[account_counter].d.year = year;
}
void construct_account(char *account_number, char *name, char *phone, char *email, double balance, int month, int year)
{
    strcpy(acc[account_counter].account_number, account_number);
    strcpy(acc[account_counter].name, name);
    strcpy(acc[account_counter].phone, phone);
    strcpy(acc[account_counter].email, email);
    acc[account_counter].balance = balance;
    construct_date(month, year);
}

void clear()
{
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#elif __MACH__
    system("clear");
#else

#endif
}
int ask_to_save()
{
    char acceptence[100];
ask_save:
    printf("Want to save? Y/N: ");
    fgets(acceptence, sizeof(acceptence), stdin);
    while (!strchr(acceptence, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("Want to save? Y/N: ");
        fgets(acceptence, sizeof(acceptence), stdin);
    }
    acceptence[strlen(acceptence) - 1] = '\0';
    if (!stricmp(acceptence, "Y"))
        return 1;
    else if (!stricmp(acceptence, "N"))
        return 0;
    else
    {
        printf("Incorrect input! try again\n");
        goto ask_save;
    }
}
void load_accounts()
{
    FILE *fptr;
    fptr = fopen("D:\\project programming\\accounts.txt", "r"); // full path because it's null without the full location
    CreateDir("reports");
    if (fptr == NULL)
    {
        printf("Error opening file.\n");
        exit(0);
    }
    account_counter = 0;
    int i = 0;
    while (!feof(fptr) && i < 1000)
    {
        fscanf(fptr, "%[^,],", acc[i].account_number);
        fscanf(fptr, "%[^,],", acc[i].name);
        fscanf(fptr, "%[^,],", acc[i].email);
        fscanf(fptr, "%f,", &acc[i].balance); // Fix format specifier
        fscanf(fptr, "%[^,],", acc[i].phone);
        fscanf(fptr, "%d-%d,", &acc[i].d.month, &acc[i].d.year); // Fix delimiter
        fscanf(fptr, "\n");
        temp[i] = acc[i];
        char filename[50] = "reports/";
        strcat(filename, acc[i].account_number);
        strcat(filename, ".txt");
        FILE *ftransac = fopen(filename, "a");
        fclose(ftransac);
        i++;
        account_counter++;
    }
    fclose(fptr);
}
void print_date(date d)
{
    switch (d.month)
    {
    case 1:
        printf("January ");
        break;
    case 2:
        printf("February ");
        break;
    case 3:
        printf("March ");
        break;
    case 4:
        printf("April ");
        break;
    case 5:
        printf("May ");
        break;
    case 6:
        printf("June ");
        break;
    case 7:
        printf("July ");
        break;
    case 8:
        printf("August ");
        break;
    case 9:
        printf("September ");
        break;
    case 10:
        printf("October ");
        break;
    case 11:
        printf("November ");
        break;
    case 12:
        printf("December ");
        break;
    }
    printf("%d\n\n", d.year);
}
void fprint_date(FILE *fptr, date d)
{
    switch (d.month)
    {
    case 1:
        fprintf(fptr, "January ");
        break;
    case 2:
        fprintf(fptr, "February ");
        break;
    case 3:
        fprintf(fptr, "March ");
        break;
    case 4:
        fprintf(fptr, "April ");
        break;
    case 5:
        fprintf(fptr, "May ");
        break;
    case 6:
        fprintf(fptr, "June ");
        break;
    case 7:
        fprintf(fptr, "July ");
        break;
    case 8:
        fprintf(fptr, "August ");
        break;
    case 9:
        fprintf(fptr, "September ");
        break;
    case 10:
        fprintf(fptr, "October ");
        break;
    case 11:
        fprintf(fptr, "November ");
        break;
    case 12:
        fprintf(fptr, "December ");
        break;
    }
    fprintf(fptr, "%d\n\n", d.year);
}
void print_account(int i)
{
    printf("Account number: %s\n", acc[i].account_number);
    printf("Name: %s\n", acc[i].name);
    printf("E-mail: %s\n", acc[i].email);
    printf("Balance: %0.2f\n", acc[i].balance);
    printf("Mobile: %s\n", acc[i].phone);
    printf("Opened: ");
    print_date(acc[i].d);
}
void merge_Name(int l, int mid, int r)
{
    int i, j, k;
    int n1 = mid - l + 1;
    int n2 = r - mid;

    // create 2 temporary arrays and copy the elements to them
    account L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = acc[l + i];

    for (j = 0; j < n2; j++)
        R[j] = acc[mid + 1 + j];

    // Merge the temporary arrays back
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (stricmp(L[i].name, R[j].name) <= 0)
        {
            acc[k] = L[i];
            i++;
        }
        else
        {
            acc[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1)
    {
        acc[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2)
    {
        acc[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort_Name(int l, int r)
{
    if (l < r)
    {
        int mid = l + (r - l) / 2;
        // Sort first and second half
        mergeSort_Name(l, mid);
        mergeSort_Name(mid + 1, r);

        // Merge the sorted halves
        merge_Name(l, mid, r);
    }
}

void sortByName()
{

    mergeSort_Name(0, account_counter - 1);
}
void merge_Balance(int l, int mid, int r)
{
    int i, j, k;
    int n1 = mid - l + 1;
    int n2 = r - mid;

    // create 2 temporary arrays and copy the elements to them
    account L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = acc[l + i];

    for (j = 0; j < n2; j++)
        R[j] = acc[mid + 1 + j];

    // Merge the temporary arrays back
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].balance > R[j].balance)
        {
            acc[k] = L[i];
            i++;
        }
        else
        {
            acc[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1)
    {
        acc[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2)
    {
        acc[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort_Balance(int l, int r)
{
    if (l < r)
    {
        int mid = l + (r - l) / 2;
        // Sort first and second half
        mergeSort_Balance(l, mid);
        mergeSort_Balance(mid + 1, r);

        // Merge the sorted halves
        merge_Balance(l, mid, r);
    }
}
void sortByBalance()
{
    mergeSort_Balance(0, account_counter - 1);
}

void merge_Date(int l, int mid, int r)
{
    int i, j, k;
    int n1 = mid - l + 1;
    int n2 = r - mid;

    // create 2 temporary arrays and copy the elements to them
    account L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = acc[l + i];

    for (j = 0; j < n2; j++)
        R[j] = acc[mid + 1 + j];

    // Merge the temporary arrays back
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].d.year < R[j].d.year)
        {
            acc[k] = L[i];
            i++;
        }
        else if (L[i].d.year > R[j].d.year)
        {
            acc[k] = R[j];
            j++;
        }

        else if (L[i].d.month < R[j].d.month)
        {
            acc[k] = L[i];
            i++;
        }

        else
        {
            acc[k] = R[j];
            j++;
        }

        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1)
    {
        acc[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2)
    {
        acc[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort_Date(int l, int r)
{
    if (l < r)
    {
        int mid = l + (r - l) / 2;
        // Sort first and second half
        mergeSort_Date(l, mid);
        mergeSort_Date(mid + 1, r);

        // Merge the sorted halves
        merge_Date(l, mid, r);
    }
}

void sortByDate()
{

    mergeSort_Date(0, account_counter - 1);
}
void print()
{
    char choose[100];
    printf("1-Sort by name\n");
    printf("2-Sort by date opened\n");
    printf("3-Sort by date balance\n");
    printf("Please choose a method to sort by (choose number): ");
    fgets(choose, sizeof(choose), stdin);
    while (!strchr(choose, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("Please choose a method to sort by (choose number): ");
        fgets(choose, sizeof(choose), stdin);
    }
    choose[strlen(choose) - 1] = '\0';
    if (!strcmp(choose, "1"))
        sortByName();
    else if (!strcmp(choose, "2"))
        sortByDate();
    else if (!strcmp(choose, "3"))
        sortByBalance();
    for (int i = 0; i < account_counter; i++)
    {
        print_account(i);
    }
}
void advanced_search()
{
    char kword[200];
    short flag = 0, pr = 0;      // flag to determine if keyword is found or not
    int i = account_counter - 1; // i is a counter of structs
    printf("Enter Keyword: ");
    fgets(kword, sizeof(kword), stdin);
    while (!strchr(kword, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("Enter Keyword: ");
        fgets(kword, sizeof(kword), stdin);
    }
    kword[strlen(kword) - 1] = '\0';
    printf("Search Results:\n");
    do
    {
        flag = 0;
        char temporary[200]; // empty string to avoid modification of the main account name
        strcpy(temporary, acc[i].name);
        char *token = strtok(temporary, " ");
        do
        {
            if (!stricmp(token, kword))
            {
                print_account(i); // print the data of the related account name
                flag = 1;
                pr = 1;
            }
            if (!flag)
            {
                token = strtok(NULL, " ");
                if (!stricmp(token, kword))
                {
                    print_account(i);
                    flag = 1;
                    pr = 1;
                }
            }
            if (flag == 1)
            {
                token = NULL;
            }
        } while (token);
        --i;
    } while (i >= 0);
    if (!pr)
        printf("no matches are found\n");
}
char userin[200], passin[200]; // username and password input (global to display on the screen always)
int login()
{
    printf("Please Enter your username: ");
    fgets(userin, sizeof(userin), stdin);
    while (!strchr(userin, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("Please Enter your username: ");
        fgets(userin, sizeof(userin), stdin);
    }
    userin[strlen(userin) - 1] = '\0';
    printf("Please Enter your password: ");
    fgets(passin, sizeof(passin), stdin);
    while (!strchr(passin, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("Please Enter your password: ");
        fgets(passin, sizeof(passin), stdin);
    }
    passin[strlen(passin) - 1] = '\0';
    char userInfo[405];
    strcpy(userInfo, userin);
    strcat(userInfo, " ");
    strcat(userInfo, passin);
    FILE *fusers;
    fusers = fopen("D:\\project programming\\users.txt", "r");
    if (fusers == NULL)
    {
        printf("Error opening file.\n");
        exit(1);
    }
    char fileLine[400];
    while (!feof(fusers))
    {
        fgets(fileLine, sizeof(fileLine), fusers);
        strtok(fileLine, "\n");
        if (!strcmp(fileLine, userInfo))
            return 1;
    }

    printf("Wrong username or password! please try again\n");
    printf("Enter any key to retry login: ");
    char s[100];
    fgets(s, sizeof(s), stdin);
    if (!strchr(s, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
    }
    return 0;
}
void cancel()
{
    for (int i = 0; i < account_counter; i++)
    {
        temp[i] = acc[i];
    }
}
void save()
{
    int counted = 0;
    FILE *fptr = fopen("D:\\project programming\\accounts.txt", "w");
    for (int i = 0; i < account_counter; i++)
    {
        acc[i] = temp[i];
    }
    while (counted < account_counter)
    {
        fprintf(fptr, "%s,", acc[counted].account_number);
        fprintf(fptr, "%s,", acc[counted].name);
        fprintf(fptr, "%s,", acc[counted].email);
        fprintf(fptr, "%f,", acc[counted].balance);
        fprintf(fptr, "%s,", acc[counted].phone);
        fprintf(fptr, "%d-", acc[counted].d.month);
        fprintf(fptr, "%d\n", acc[counted++].d.year);
    }
    fclose(fptr);
    printf("CHANGES SAVED\n");
}
int search()
{
    int i;
    for (i = 0; i < account_counter; i++)
    {
        if (!strcmp(account_numberin, acc[i].account_number))
        {
            return i;
        }
    }
    i = -1;
    return i;
}
void fprint_transac(FILE *fptr, short type, float amount, char *acc_from, char *acc_to)
{
    switch (type)
    {
    case 1:
        fprintf(fptr, "Withdrawal...\n");
        break;
    case 2:
        fprintf(fptr, "Deposit...\n");
        break;
    case 3:
        fprintf(fptr, "Transfer...\n");
        break;
    }
    if (type == 3)
    {
        fprintf(fptr, "Amount = %.2f, From %s to %s\n", amount, acc_from, acc_to);
    }
    else
        fprintf(fptr, "Amount = %.2f\n", amount);
    date d;
    struct tm dateCurrent = *localtime(&t);
    d.month = dateCurrent.tm_mon + 1;
    d.year = dateCurrent.tm_year + 1900;
    fprint_date(fptr, d);
}
int check(char email[], char mobile[])
{
    for (int i = 0; i < account_counter; i++)
    {
        if (!strcmp(email, acc[i].email))
        {
            printf("E-mail is used before!\n");
            return -1;
        }
        if (!strcmp(mobile, acc[i].phone))
        {
            printf("Mobile number is used before!\n");
            return -2;
        }
    }
    return 1;
}
int withdraw()
{
    float withdrawBal;
    printf("Enter account number: ");
    fgets(account_numberin, sizeof(account_numberin), stdin);
    while (!strchr(account_numberin, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("Enter account number: ");
        fgets(account_numberin, sizeof(account_numberin), stdin);
    }
    account_numberin[strlen(account_numberin) - 1] = '\0';
    int n = search();
    if (n == -1)
    {
        printf("Transaction failed, incorrect account number.\n\n");
        return -1;
    }
    char filename[20] = "reports/";
    strcat(filename, acc[n].account_number);
    strcat(filename, ".txt");
    FILE *transFile = fopen(filename, "a");
    printf("Enter balance to withdraw: ");
    char Bal_Temp[30];
    fgets(Bal_Temp, sizeof(Bal_Temp), stdin);
    while (!strchr(Bal_Temp, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("Enter balance to withdraw: ");
        fgets(Bal_Temp, sizeof(Bal_Temp), stdin);
    }
    Bal_Temp[strlen(Bal_Temp) - 1] = '\0';
    int num = strlen(Bal_Temp);
    for (int i = 0; i < num; i++)
    {
        if (!((Bal_Temp[i] >= '0' && Bal_Temp[i] <= '9') || Bal_Temp[i] == '.'))
        {
            printf("Invalid Input\n");
            fclose(transFile);
            return -1;
        }
    }
    withdrawBal = atof(Bal_Temp);
    if (withdrawBal > 10000)
    {
        printf("Transaction failed! Exceded the limit to withdraw\n");
        fclose(transFile);
        return -1;
    }
    if (temp[n].balance >= withdrawBal)
    {
        printf("Withdrawing balance...\n\n");
        temp[n].balance -= withdrawBal;
        if (ask_to_save())
            fprint_transac(transFile, 1, -1 * withdrawBal, 0, 0);
        else
        {
            fclose(transFile);
            return -3;
        }
        fclose(transFile);
        return n;
    }
    else
    {
        printf("Transaction failed, Insufficient balance.\n\n");
        fclose(transFile);
        return -1;
    }
}
int deposit()
{
    float depositBal;
    printf("Enter account number: ");
    fgets(account_numberin, sizeof(account_numberin), stdin);
    while (!strchr(account_numberin, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("Enter account number: ");
        fgets(account_numberin, sizeof(account_numberin), stdin);
    }
    account_numberin[strlen(account_numberin) - 1] = '\0';
    int n = search();
    if (n == -1)
    {
        printf("Transaction failed, incorrect account number.\n\n");
        return n;
    }
    char filename[20] = "reports/";
    strcat(filename, acc[n].account_number);
    strcat(filename, ".txt");
    FILE *transFile = fopen(filename, "a");
    printf("Enter balance to deposit: ");
    char Bal_Temp[30];
    fgets(Bal_Temp, sizeof(Bal_Temp), stdin);
    while (!strchr(Bal_Temp, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("Enter balance to deposit: ");
        fgets(Bal_Temp, sizeof(Bal_Temp), stdin);
    }
    Bal_Temp[strlen(Bal_Temp) - 1] = '\0';
    int num = strlen(Bal_Temp);
    for (int i = 0; i < num; i++)
    {
        if (!((Bal_Temp[i] >= '0' && Bal_Temp[i] <= '9') || Bal_Temp[i] == '.'))
        {
            printf("Invalid Input\n");
            fclose(transFile);
            return -1;
        }
    }
    depositBal = atof(Bal_Temp);
    if (depositBal > 10000)
    {
        printf("Transaction failed! Exceded the limit to deposit\n");
        fclose(transFile);
        return -1;
    }
    printf("Depositing balance...\n\n");
    temp[n].balance += depositBal;
    if (ask_to_save())
    {
        fprint_transac(transFile, 2, depositBal, 0, 0);
        fclose(transFile);
        return n;
    }
    else
    {
        fclose(transFile);
        return -3;
    }
}
int transfer()
{
    float transferBal;
    char account_number_from[30], account_number_to[30];
    printf("Enter account number to transfer from: ");
    fgets(account_number_from, sizeof(account_number_from), stdin);
    while (!strchr(account_number_from, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("Enter account number to transfer from: ");
        fgets(account_number_from, sizeof(account_number_from), stdin);
    }
    account_number_from[strlen(account_number_from) - 1] = '\0';
    strcpy(account_numberin, account_number_from);
    int n_from = search();
    printf("Enter account number to transfer to: ");
    fgets(account_number_to, sizeof(account_number_to), stdin);
    while (!strchr(account_number_to, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("Enter account number to transfer to: ");
        fgets(account_number_to, sizeof(account_number_to), stdin);
    }
    account_number_to[strlen(account_number_to) - 1] = '\0';
    strcpy(account_numberin, account_number_to);
    int n_to = search();
    if (n_from == -1 || n_to == -1)
    {
        printf("Transaction failed, one or more incorrect account number.\n\n");
        return -1;
    }
    if (n_from == n_to)
    {
        printf("Can't transfer from an account to itself!\n");
        return -1;
    }
    char filename_from[20] = "reports/", filename_to[20] = "reports/";
    strcat(filename_from, acc[n_from].account_number);
    strcat(filename_from, ".txt");
    FILE *transFile_from = fopen(filename_from, "a");

    strcat(filename_to, acc[n_to].account_number);
    strcat(filename_to, ".txt");
    FILE *transFile_to = fopen(filename_to, "a");
    printf("Enter balance to transfer: ");
    char Bal_Temp[30];
    fgets(Bal_Temp, sizeof(Bal_Temp), stdin);
    while (!strchr(Bal_Temp, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("Enter balance to transfer: ");
        fgets(Bal_Temp, sizeof(Bal_Temp), stdin);
    }
    Bal_Temp[strlen(Bal_Temp) - 1] = '\0';
    int num = strlen(Bal_Temp);
    for (int i = 0; i < num; i++)
    {
        if (!((Bal_Temp[i] >= '0' && Bal_Temp[i] <= '9') || Bal_Temp[i] == '.'))
        {
            printf("Invalid Input\n");
            fclose(transFile_from);
            fclose(transFile_to);
            return -1;
        }
    }
    transferBal = atof(Bal_Temp);
    if (temp[n_from].balance >= transferBal)
    {
        printf("Transferring balance...\n\n");
        temp[n_from].balance -= transferBal;
        temp[n_to].balance += transferBal;
        if (ask_to_save())
        {
            fprint_transac(transFile_from, 3, -1 * transferBal, acc[n_from].account_number, acc[n_to].account_number);
            fprint_transac(transFile_to, 3, transferBal, acc[n_from].account_number, acc[n_to].account_number);
            fclose(transFile_from);
            fclose(transFile_to);
            return n_from;
        }
        else
        {
            fclose(transFile_from);
            fclose(transFile_to);
            return -3;
        }
    }
    else
    {
        printf("Transaction failed, Insufficient balance.\n\n");
        fclose(transFile_from);
        fclose(transFile_to);
        return -1;
    }
}
void report()
{
    printf("Enter account number: ");
    fgets(account_numberin, sizeof(account_numberin), stdin);
    while (!strchr(account_numberin, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("Enter account number: ");
        fgets(account_numberin, sizeof(account_numberin), stdin);
    }
    account_numberin[strlen(account_numberin) - 1] = '\0';
    int n = search();
    if (n == -1)
    {
        printf("Transaction failed, incorrect account number.\n");
        return;
    }
    char filename[30] = "reports/";
    strcat(filename, account_numberin);
    strcat(filename, ".txt");
    FILE *freport;
    freport = fopen(filename, "r");
    if (fgetc(freport) == EOF)
    {
        printf("User hasn't made any transactions.\n");
        fclose(freport);
        return;
    }

    char lines[20][100];
    int index = 0;
    rewind(freport);
    while (fgets(lines[index % 20], 100, freport))
    {
        index++;
    }
    // Index ends at last index in line + 1
    int start = index > 20 ? (index % 20) : 0;
    int count = index > 20 ? 20 : index;

    for (int i = 0; i < count; i++)
    {
        printf("%s", lines[(start + i) % 20]);
        // 15 --> 20 1 --> count
    }
    fclose(freport);
}
int emailvalidation(char newemail[])
{
    // strcpy email into variable
    char str[200];
    strcpy(str, newemail);
    if (strchr(str, ' ') || strchr(str, '\\'))
    {
        printf("Invalid Email!\n");
        return 0;
    }
    if (str[0] == '@')
    {
        printf("Invalid Email!\n");
        return 0;
    }
    char *S1 = strtok(str, "@");
    char *S2 = strtok(NULL, "\n");
    if (S1 == NULL || S2 == NULL || strlen(S2) < 3)
    {
        printf("Invalid Email!\n");
        return 0;
    }
    else if (strlen(S1) == 0 || strlen(S2) < 3 || strchr(S2, '@') || S2[strlen(S2) - 1] == '.' || !strchr(S2, '.') || S2[0] == '.' || S1[0] == '.' || S1[strlen(S1) - 1] == '.')
    {
        printf("Invalid Email!\n");
        return 0;
    }
    int n = strlen(S2);
    for (int i = 0; i < n - 1; i++)
    {
        if (S2[i] == S2[i + 1] && S2[i] == '.')
        {
            printf("Invalid Email\n");
            return 0;
        }
    }

    return 1;
}
void add_account()
{
    char addname[100];
    char addemail[50];
    char addmobile[14];
    int a = account_counter;
    int valid = 0;
    do
    {
        valid = 1;
        printf("Name: ");
        fgets(addname, sizeof(addname), stdin);
        while (!strchr(addname, '\n'))
        {
            scanf("%*[^\n]");
            scanf("%*c"); // clear upto newline
            printf("Too long input please try again!\n");
            printf("Name: ");
            fgets(addname, sizeof(addname), stdin);
        }
        addname[strlen(addname) - 1] = '\0';
        for (int i = 0; i <= strlen(addname); i++)
        {
            if (!((addname[i] >= 'a' && addname[i] <= 'z') || (addname[i] >= 'A' && addname[i] <= 'Z') || isspace(addname[i]) || addname[i] == '.' || addname[i] == '\0'))
            {
                valid = 0;
                break;
            }
        }
        if (strlen(addname) > 100 || strlen(addname) == 0 || !valid)
            printf("The Name is not valid Try again!\n");
    } while (strlen(addname) > 100 || strlen(addname) == 0 || !valid);
emailvalid:
    // int counter = 0;
    printf("E-mail: ");
    fgets(addemail, sizeof(addemail), stdin);
    while (!strchr(addemail, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("E-mail: ");
        fgets(addemail, sizeof(addemail), stdin);
    }
    addemail[strlen(addemail) - 1] = '\0';
    if (emailvalidation(addemail))
    {
        if (strlen(addemail) > 50 || strlen(addemail) == 0)
        {
            printf("The E-mail is too long Try again!");
            goto emailvalid;
        }
        int checking = check(addemail, "1");
        if (checking == -1)
        {
            goto emailvalid;
        }
    }
    else
    {
        goto emailvalid;
    }
mobilevalid:
    do
    {
        printf("Mobile: ");
        fgets(addmobile, sizeof(addmobile), stdin);
        while (!strchr(addmobile, '\n'))
        {
            scanf("%*[^\n]");
            scanf("%*c"); // clear upto newline
            printf("Too long input please try again!\n");
            printf("Mobile: ");
            fgets(addmobile, sizeof(addmobile), stdin);
        }
        addmobile[strlen(addmobile) - 1] = '\0';
        if (strlen(addmobile) != 11 || addmobile[0] != '0' || addmobile[1] != '1' || !((addmobile[2] >= '0' && addmobile[2] <= '2') || addmobile[2] == '5'))
            printf("Invalid mobile number try again!\n");
    } while ((strlen(addmobile) != 11) || addmobile[0] != '0' || addmobile[1] != '1' || !((addmobile[2] >= '0' && addmobile[2] <= '2') || addmobile[2] == '5'));
    int checking = check("1", addmobile);
    if (checking == -2)
    {
        goto mobilevalid;
    }
    char number_string[30];
invalid_acc_num:
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        number_string[i] = '0' + rand() % 10;
    }
    number_string[10] = '\0';
    strcpy(account_numberin, number_string);
    if (search() == -1)
    {
        strcpy(temp[a].account_number, number_string);
    }
    else
    {
        goto invalid_acc_num;
    }
    strcpy(temp[a].name, addname);
    strcpy(temp[a].email, addemail);
    strcpy(temp[a].phone, addmobile);
    temp[a].balance = 0;
    account_counter++;
    struct tm dateCurrent = *localtime(&t);
    temp[a].d.month = (short)(dateCurrent.tm_mon + 1);
    temp[a].d.year = (short)(dateCurrent.tm_year + 1900);
}
int delete_account()
{
    int i = 0, found = 0, j, balanceok;
    do
    {
        printf("Enter the account number to Delete data: ");
        fgets(account_numberin, sizeof(account_numberin), stdin);
        while (!strchr(account_numberin, '\n'))
        {
            scanf("%*[^\n]");
            scanf("%*c"); // clear upto newline
            printf("Too long input please try again!\n");
            printf("Enter the account number to Delete data: ");
            fgets(account_numberin, sizeof(account_numberin), stdin);
        }
        account_numberin[strlen(account_numberin) - 1] = '\0';
        found = search();
        if (found < 0)
        {
            printf("The account number is not found! Try again\n");
        }
    } while (!found);
    i = found;
    if (temp[i].balance == 0)
    {
        account_counter--;
        for (int k = i; k < account_counter; k++)
        {
            temp[k] = temp[k + 1];
        }
    }
    else
    {
        printf("the balance is not 0, CAN'T DELETE\n");
        return 0;
    }
    return 1;
}
void modify_account()
{
    char choice[100];
    char newname[50];
    char newmobile[14];
    char newemail[100];
    int i = 0, found = 0, j;
    do
    {
        printf("Enter the account number to Modify data: ");
        fgets(account_numberin, sizeof(account_numberin), stdin);
        while (!strchr(account_numberin, '\n'))
        {
            scanf("%*[^\n]");
            scanf("%*c"); // clear upto newline
            printf("Too long input please try again!\n");
            printf("Enter the account number to Modify data: ");
            fgets(account_numberin, sizeof(account_numberin), stdin);
        }
        account_numberin[strlen(account_numberin) - 1] = '\0';
        found = search();
        if (found == -1)
        {
            printf("The account number is not found! Try again\n");
        }
    } while (found == -1);
    while (!(!stricmp(choice, "q")))
    {
    label:
        printf("1.Name \n");
        printf("2.Mobile \n");
        printf("3.E-mail \n");
        printf("Choose from the one option to Modify or Enter q to quit: ");
        fgets(choice, sizeof(choice), stdin);
        while (!strchr(choice, '\n'))
        {
            scanf("%*[^\n]");
            scanf("%*c"); // clear upto newline
            printf("Too long input please try again!\n");
            printf("Choose from the one option to Modify or Enter q to quit: ");
            fgets(choice, sizeof(choice), stdin);
        }
        choice[strlen(choice) - 1] = '\0';
        if (!stricmp(choice, "quit") || !stricmp(choice, "Q"))
        {
            return;
        }
        else if (!stricmp(choice, "NAME") || !stricmp(choice, "n") || !strcmp(choice, "1"))
        {
            int valid = 1;
            do
            {
                valid = 1;
                printf("Enter the new name (can't contain special characters or digits): ");
                fgets(newname, sizeof(newname), stdin);
                while (!strchr(newname, '\n'))
                {
                    scanf("%*[^\n]");
                    scanf("%*c"); // clear upto newline
                    printf("Too long input please try again!\n");
                    printf("Enter the new name (can't contain special characters or digits): ");
                    fgets(newname, sizeof(newname), stdin);
                }
                newname[strlen(newname) - 1] = '\0';
                for (int i = 0; i < strlen(newname); i++)
                {
                    if (!((newname[i] >= 'a' && newname[i] <= 'z') || (newname[i] >= 'A' && newname[i] <= 'Z') || isspace(newname[i]) || newname[i] == '.'))
                    {
                        valid = 0;
                        break;
                    }
                }
            } while (!valid);
            strcpy(temp[found].name, newname);
        }
        else if (!stricmp(choice, "MOBILE") || !stricmp(choice, "m") || !strcmp(choice, "2"))
        {
            do
            {
            mobilevalidmodify:
                printf("Enter the new Mobile number (Must be 11 digits): ");
                fgets(newmobile, sizeof(newmobile), stdin);
                while (!strchr(newmobile, '\n'))
                {
                    scanf("%*[^\n]");
                    scanf("%*c"); // clear upto newline
                    printf("Too long input please try again!\n");
                    printf("Enter the new Mobile number (Must be 11 digits): ");
                    fgets(newmobile, sizeof(newmobile), stdin);
                }
                newmobile[strlen(newmobile) - 1] = '\0';
            } while ((strlen(newmobile) != 11) || newmobile[0] != '0' || newmobile[1] != '1' || !((newmobile[2] >= '0' && newmobile[2] <= '2') || newmobile[2] == '5'));
            int checking = check("1", newmobile);
            if (checking != -2)
                strcpy(temp[found].phone, newmobile);
            else
            {
                goto mobilevalidmodify;
            }
        }
        else if (!stricmp(choice, "EMAIL") || !stricmp(choice, "E-mail") || !stricmp(choice, "e") || !strcmp(choice, "3"))
        {
        emailvalidmodify:
            printf("Enter the new E-mail (contain numbers and special characters): ");
            fgets(newemail, sizeof(newemail), stdin);
            while (!strchr(newemail, '\n'))
            {
                scanf("%*[^\n]");
                scanf("%*c"); // clear upto newline
                printf("Too long input please try again!\n");
                printf("Enter the new E-mail (contain numbers and special characters): ");
                fgets(newemail, sizeof(newemail), stdin);
            }
            newemail[strlen(newemail) - 1] = '\0';
            if (emailvalidation(newemail))
            {
                int checking = check("1", newmobile);
                if (checking != -2)
                    strcpy(temp[found].email, newemail);
                else
                    goto emailvalidmodify;
            }
            else
                goto emailvalidmodify;
        }
        else
        {
            clear();
            printf("NOT FOUND!\n");
            goto label;
        }
        char acceptence[100];
    modify:
        printf("Want to modify again? Y/N: ");
        fgets(acceptence, sizeof(acceptence), stdin);
        while (!strchr(acceptence, '\n'))
        {
            scanf("%*[^\n]");
            scanf("%*c"); // clear upto newline
            printf("Too long input please try again!\n");
            printf("Want to modify again? Y/N: ");
            fgets(acceptence, sizeof(acceptence), stdin);
        }
        acceptence[strlen(acceptence) - 1] = '\0';
        if (!stricmp(acceptence, "Y"))
            goto label;
        else if (!stricmp(acceptence, "N"))
            return;
        else
        {
            clear();
            printf("Incorrect input!\n");
            goto modify;
        }
    }
}
int mini_menu()
{
    clear();
    char acceptence[100];
mini_menu:
    printf("1-Login\n");
    printf("2-Quit\n");
    printf("Please choose one of the previous commands: ");
    fgets(acceptence, sizeof(acceptence), stdin);
    while (!strchr(acceptence, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("Choose again please: ");
        fgets(acceptence, sizeof(acceptence), stdin);
    }
    acceptence[strlen(acceptence) - 1] = '\0';
    if (!stricmp(acceptence, "Login") || !strcmp(acceptence, "1"))
    {
        clear();
        if (login())
            return 1;
        else
        {
            clear();
            goto mini_menu;
        }
    }
    else if (!stricmp(acceptence, "Quit") || !strcmp(acceptence, "2"))
    {
        exit(0);
    }
    else
    {
        clear();
        printf("Incorrect input!\n");
        goto mini_menu;
    }
}
void menu();
int main()
{
    if (mini_menu()) // you have to login first
        load_accounts();
    while (1)
    {
        clear();
        time(&t);
        printf("%s\n", userin);
        printf("%s\n", ctime(&t));
        menu();
        printf("Enter any key to continue: ");
        char s[100];
        fgets(s, sizeof(s), stdin);
        while (!strchr(s, '\n'))
        {
            scanf("%*[^\n]");
            scanf("%*c"); // clear upto newline
            printf("Too long input please try again!\n");
            printf("Enter any key to continue: ");
            fgets(s, sizeof(s), stdin);
        }
    }
    return 0;
}
void menu()
{
    char choice[17];
    printf("1-ADD\n");
    printf("2-DELETE\n");
    printf("3-MODIFY\n");
    printf("4-SEARCH\n");
    printf("5-ADVANCED SEARCH\n");
    printf("6-WITHDRAW\n");
    printf("7-DEPOSIT\n");
    printf("8-TRANSFER\n");
    printf("9-REPORT\n");
    printf("10-PRINT\n");
    printf("11-Logout\n");
    printf("12-QUIT\n");
    printf("Choose one of the previous commands:");
    fgets(choice, sizeof(choice), stdin);
    while (!strchr(choice, '\n'))
    {
        scanf("%*[^\n]");
        scanf("%*c"); // clear upto newline
        printf("Too long input please try again!\n");
        printf("choose one of the previous commands: ");
        fgets(choice, sizeof(choice), stdin);
    }
    choice[strlen(choice) - 1] = '\0';
    clear();
    printf("%s\n", userin);
    printf("%s\n", ctime(&t));
    if (!stricmp(choice, "ADD") || !stricmp(choice, "1")) // any form will access the condition
    {
        printf("ADD\n");
        printf("---\n");
        add_account();
        if (ask_to_save())
        {
            char filename_add[30] = "reports/";
            strcat(filename_add, account_numberin);
            strcat(filename_add, ".txt");
            FILE *file_add = fopen(filename_add, "a");
            fclose(file_add);
            save();
        }

        else
        {
            cancel();
        }
    }
    else if (!stricmp(choice, "DELETE") || !stricmp(choice, "2"))
    {
        printf("Delete\n");
        printf("------\n");
        if (delete_account())
        {
            if (ask_to_save())
            {
                char filename_del[30] = "reports/";
                strcat(filename_del, account_numberin);
                strcat(filename_del, ".txt");
                remove(filename_del);
                save();
            }
            else
            {
                account_counter++;
                cancel();
            }
        }
    }
    else if (!stricmp(choice, "MODIFY") || !stricmp(choice, "3"))
    {
        printf("Modify\n");
        printf("------\n");
        modify_account();
        if (ask_to_save())
            save();
        else
            cancel();
    }
    else if (!stricmp(choice, "SEARCH") || !stricmp(choice, "4"))
    {
        printf("Search\n");
        printf("------\n");
        printf("Enter account number: ");
        fgets(account_numberin, sizeof(account_numberin), stdin);
        while (!strchr(account_numberin, '\n'))
        {
            clear();
            scanf("%*[^\n]");
            scanf("%*c"); // clear upto newline
            printf("Too long input please try again!\n");
            printf("Enter account number: ");
            fgets(account_numberin, sizeof(account_numberin), stdin);
        }
        account_numberin[strlen(account_numberin) - 1] = '\0';
        int i = 0;
        if ((i = search()) >= 0)
            print_account(i);
        else
            printf("This account number is not found!\n");
    }
    else if (!stricmp(choice, "ADVANCED SEARCH") || !stricmp(choice, "5"))
    {
        printf("Advanced Search\n");
        printf("---------------\n");
        advanced_search();
    }
    else if (!stricmp(choice, "WITHDRAW") || !stricmp(choice, "6"))
    {
        printf("Withdraw\n");
        printf("--------\n");
        int n = withdraw();
        if (n == -3)
            cancel();
        else if (n >= 0)
        {
            save();
        }

        else
            cancel();
    }
    else if (!stricmp(choice, "DEPOSIT") || !stricmp(choice, "7"))
    {
        printf("Deposit\n");
        printf("-------\n");
        int n = deposit();
        if (n == -3)
            cancel();
        else if (n >= 0)
            save();
        else
            cancel();
    }
    else if (!stricmp(choice, "TRANSFER") || !stricmp(choice, "8"))
    {
        printf("Transfer\n");
        printf("--------\n");
        int n = transfer();
        if (n == -3)
            cancel();
        else if (n >= 0)
            save();
        else
            cancel();
    }
    else if (!stricmp(choice, "REPORT") || !stricmp(choice, "9"))
    {
        printf("Report\n");
        printf("--------\n");
        report();
    }
    else if (!stricmp(choice, "PRINT") || !stricmp(choice, "10"))
    {
        printf("Print\n");
        printf("-----\n");
        print();
    }
    else if (!stricmp(choice, "Logout") || !stricmp(choice, "11"))
    {
        clear();
        main();
    }
    else if (!stricmp(choice, "QUIT") || !stricmp(choice, "12"))
    {
        clear();
        exit(0);
    }
    else
    {
        printf("Not found command please try again!\n");
    }
}
