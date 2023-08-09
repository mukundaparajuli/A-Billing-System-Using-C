#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define the customer struct
struct customer
{
    char name[100];
    int age;
};

// Function prototypes
void PrintBill(char good[][100], float price[], int i, struct customer c[], int k);
void WriteSalesDetail(char good[][100], float price[], int i, struct customer c[], int k);
float calculateTotal(float price[], int i);

int main()
{
    FILE *fptr;
    FILE *fptr2;
    char input[100];
    char password[] = "mukunda";
    char checkPw[100];
    int i;
    struct customer c[100];
    int customerCount = 0;
    int k = 0;

    printf("_______________________________________________\n");
    printf("|_____________________________________________|\n");
    printf("|                                             |\n");
    printf("|***Welcome to the Big Mart Billing System****|\n");
    printf("|                                             |\n");
    printf("|_____________________________________________|\n");
    printf("|_____________________________________________|\n");
    printf("\n\n\nPress Enter to continue.");
    getchar();
    // Clear the screen
    system("cls");

    printf("How would you like to enter the system? (Buyer or Seller): ");

    fgets(input, sizeof(input), stdin);

    // Remove the newline character from the input buffer
    input[strcspn(input, "\n")] = '\0';

    if (strcasecmp(input, "seller") == 0)
    {
        system("cls");
        printf("You will need to enter the password to enter the system: ");
        fgets(checkPw, sizeof(checkPw), stdin);
        checkPw[strcspn(checkPw, "\n")] = '\0'; // Remove newline character

        int b = strcasecmp(checkPw, "mukunda");

        if (b == 0)
        {
            printf("Access Granted\n");
            printf("Now you can see all the details of the sale\n");
            getchar();
            system("cls");
            fptr = fopen("SalesDetail.txt", "r");
            if (fptr == NULL)
            {
                printf("No such file found.");
            }
            else
            {
                char ch;
                while ((ch = fgetc(fptr)) != EOF)
                {
                    putchar(ch);
                }
                fclose(fptr);
            }
        }
    }
    else if (strcasecmp(input, "buyer") == 0)
    {
        system("cls");

        printf("Enter the number of items that you had bought: ");
        scanf("%d", &i);
        // Dynamically allocate memory for goods and prices arrays
        char(*good)[100] = malloc(i * sizeof(*good));
        float *price = malloc(i * sizeof(float));
        printf("Enter your name: ");
        scanf("%s", c[k].name);
        printf("Enter your age: ");
        scanf("%d", &c[k].age);
        for (int j = 0; j < i; j++)
        {
            printf("Enter the name of item %d: ", j + 1);
            scanf("%s", good[j]);
            printf("Enter the price of item %d: ", j + 1);
            scanf("%f", &price[j]);
        }
        WriteSalesDetail(good, price, i, c, k);
        printf("Press Enter to print the bill.");
        PrintBill(good, price, i, c, k);
        getchar();

        // Free dynamically allocated memory
        free(good);
        free(price);
    }

    k++;

    return 0;
}

void PrintBill(char good[][100], float price[], int i, struct customer c[], int k)
{
    printf("Press Enter to print the bill.");
    getchar();
    system("cls");
    float count = 0;
    printf("_____________________________________________________________________________\n");
    printf("|____________________________________________________________________________|\n");
    printf("|             ***************BIGMART POKHARA***************                  |\n");
    printf("|____________________________________________________________________________|\n");
    printf("|____________________________________________________________________________|\n");
    printf("|Customer Name:                        |%s                                    \n", c[k].name);
    printf("|______________________________________|_____________________________________|\n");
    printf("|Customer Age:                         |%d                                    \n", c[k].age);
    printf("|______________________________________|_____________________________________|\n");
    printf("|           Name of the item           |          Price of the item          |\n");
    printf("|______________________________________|_____________________________________|\n");
    for (int j = 0; j < i; j++)
    {
        printf("|%s                                    Rs%.2f                                 \n", good[j], price[j]);
        printf("|______________________________________|_____________________________________|\n");
    }
    printf("|Total price                           Rs%.2f                                 \n", calculateTotal(price, i));
    printf("|______________________________________|_____________________________________|\n");
    printf("|Thank you for visiting.                                                     |\n");
    printf("|____________________________________________________________________________|\n");
}

void WriteSalesDetail(char good[][100], float price[], int i, struct customer c[], int k)
{
    FILE *fptr = fopen("salesDetail.txt", "a"); // Open file in append mode

    if (fptr == NULL)
    {
        printf("Error opening file.");
        return;
    }

    fprintf(fptr, "------------------------------------------------\n");
    fprintf(fptr, "Cutomer's Name: %s\n", c[k].name);
    fprintf(fptr, "Customer's Age: %d\n", c[k].age);
    fprintf(fptr, "------------------------------------------------\n");
    fprintf(fptr, "Items purchased:\n");
    for (int j = 0; j < i; j++)
    {
        fprintf(fptr, "Item: %s, Price: Rs%.2f\n", good[j], price[j]);
    }
    fprintf(fptr, "Total: Rs%.2f\n", calculateTotal(price, i));

    fprintf(fptr, "------------------------------------------------\n");
    fclose(fptr);
}

float calculateTotal(float price[], int i)
{
    float total = 0; // Initialize total before the loop
    for (int j = 0; j < i; j++)
    {
        total += price[j];
    }
    return total; // Return the calculated total
}
