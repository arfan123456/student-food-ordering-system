#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

/* ============================================================
                    FUNCTION PROTOTYPES
   ============================================================ */

void mainMenu(void);

/* Normal User */
void userMenu(void);
void userRegistration(void);
void userLogin(void);
void userDashboard(char username[]);

/* Admin */
void adminLogin(void);
void adminDashboard(void);
void updateAdminPassword(void);

/* Main Features */
void orderFood(char username[]);
void foodAccordingToWeight(void);
void fitnessTest(void);
void viewOrders(void);


/* ============================================================
                        MAIN MENU
   ============================================================ */

void mainMenu(void)
{
    int choice;

    while (1)
    {
        system("CLS");

        printf("\n\n");
        printf("============================================================\n");
        printf("                 STUDENT FOOD ORDERING SYSTEM\n");
        printf("============================================================\n\n");

        printf("1. Normal User\n\n");
        printf("2. Admin Login\n\n");
        printf("3. Exit\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                userMenu();
                break;

            case 2:
                adminLogin();
                break;

            case 3:
                printf("\nThank you for using the system!\n");
                Sleep(1000);
                exit(0);

            default:
                printf("\nInvalid choice! Please try again.");
                getch();
        }
    }
}


/* ============================================================
                      NORMAL USER MENU
   ============================================================ */

void userMenu(void)
{
    int choice;

    while (1)
    {
        system("CLS");

        printf("\n\n");
        printf("============================================================\n");
        printf("                     NORMAL USER MENU\n");
        printf("============================================================\n\n");

        printf("1. Login\n\n");
        printf("2. Registration\n\n");
        printf("3. Back to Main Menu\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                userLogin();
                break;

            case 2:
                userRegistration();
                break;

            case 3:
                return;

            default:
                printf("\nInvalid choice!");
                getch();
        }
    }
}


/* ============================================================
                     USER REGISTRATION
   ============================================================ */

void userRegistration(void)
{
    char username[50];
    char password[50];

    char existingUser[50];

    FILE *users;
    FILE *passwords;

    int duplicate = 0;

    system("CLS");

    printf("\n\n");
    printf("============================================================\n");
    printf("                   USER REGISTRATION\n");
    printf("============================================================\n\n");

    printf("Enter Username: ");
    scanf("%49s", username);


    /* Check duplicate username */

    users = fopen("users.txt", "r");

    if (users != NULL)
    {
        while (fscanf(users, "%49s", existingUser) == 1)
        {
            if (strcmp(username, existingUser) == 0)
            {
                duplicate = 1;
                break;
            }
        }

        fclose(users);
    }


    if (duplicate == 1)
    {
        printf("\nThis username already exists!");
        printf("\nPlease choose another username.");

        printf("\n\nPress any key to return...");
        getch();

        return;
    }


    printf("Enter Password: ");
    scanf("%49s", password);


    /* Open files */

    users = fopen("users.txt", "a");
    passwords = fopen("user_passwords.txt", "a");


    if (users == NULL || passwords == NULL)
    {
        printf("\nFile error!");

        if (users != NULL)
            fclose(users);

        if (passwords != NULL)
            fclose(passwords);

        getch();

        return;
    }


    /* Save username and password */

    fprintf(users, "%s\n", username);
    fprintf(passwords, "%s\n", password);

    fclose(users);
    fclose(passwords);


    printf("\n\nRegistration Successful!");

    printf("\n\nPress any key to continue...");
    getch();
}


/* ============================================================
                         USER LOGIN
   ============================================================ */

void userLogin(void)
{
    char username[50];
    char password[50];

    char fileUser[50];
    char filePass[50];

    FILE *users;
    FILE *passwords;

    int found = 0;

    system("CLS");

    printf("\n\n");
    printf("============================================================\n");
    printf("                       USER LOGIN\n");
    printf("============================================================\n\n");


    users = fopen("users.txt", "r");
    passwords = fopen("user_passwords.txt", "r");


    if (users == NULL || passwords == NULL)
    {
        printf("\nNo user account found!");
        printf("\nPlease register first.");

        if (users != NULL)
            fclose(users);

        if (passwords != NULL)
            fclose(passwords);

        printf("\n\nPress any key to return...");
        getch();

        return;
    }


    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);


    /* Check username and password */

    while (fscanf(users, "%49s", fileUser) == 1 &&
           fscanf(passwords, "%49s", filePass) == 1)
    {
        if (strcmp(username, fileUser) == 0 &&
            strcmp(password, filePass) == 0)
        {
            found = 1;
            break;
        }
    }


    fclose(users);
    fclose(passwords);


    if (found == 1)
    {
        printf("\n\nLogin Successful!");
        printf("\nWelcome %s!", username);

        printf("\n\nPress any key to continue...");
        getch();

        userDashboard(username);
    }
    else
    {
        printf("\n\nWrong Username or Password!");

        printf("\n\nPress any key to return...");
        getch();
    }
}


/* ============================================================
                      USER DASHBOARD
   ============================================================ */

void userDashboard(char username[])
{
    int choice;

    while (1)
    {
        system("CLS");

        printf("\n\n");
        printf("============================================================\n");
        printf("                 STUDENT FOOD ORDERING SYSTEM\n");
        printf("============================================================\n\n");

        printf("Welcome: %s\n\n", username);

        printf("1. Order Food from Canteen\n\n");
        printf("2. Food According to Weight\n\n");
        printf("3. Give Fitness Test for Tournament\n\n");
        printf("4. Logout\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice)
        {
            case 1:
                orderFood(username);
                break;

            case 2:
                foodAccordingToWeight();
                break;

            case 3:
                fitnessTest();
                break;

            case 4:
                printf("\nLogging out...");
                Sleep(1000);
                return;

            default:
                printf("\nInvalid choice!");
                getch();
        }
    }
}


/* ============================================================
                         ADMIN LOGIN
   ============================================================ */

void adminLogin(void)
{
    char username[50];
    char password[50];
    char savedPassword[50];

    FILE *file;

    system("CLS");

    printf("\n\n");
    printf("============================================================\n");
    printf("                       ADMIN LOGIN\n");
    printf("============================================================\n\n");


    /*
        Default Admin Account:

        Username: admin
        Password: admin123
    */


    file = fopen("admin_password.txt", "r");


    /* Create default password automatically */

    if (file == NULL)
    {
        file = fopen("admin_password.txt", "w");

        if (file == NULL)
        {
            printf("\nError creating password file!");
            getch();
            return;
        }

        fprintf(file, "admin123");

        fclose(file);

        strcpy(savedPassword, "admin123");
    }
    else
    {
        fscanf(file, "%49s", savedPassword);
        fclose(file);
    }


    printf("Enter Admin Username: ");
    scanf("%49s", username);

    printf("Enter Admin Password: ");
    scanf("%49s", password);


    if (strcmp(username, "admin") == 0 &&
        strcmp(password, savedPassword) == 0)
    {
        printf("\n\nAdmin Login Successful!");
        printf("\nWelcome Admin!");

        printf("\n\nPress any key to continue...");
        getch();

        adminDashboard();
    }
    else
    {
        printf("\n\nWrong Admin Username or Password!");

        printf("\n\nPress any key to return...");
        getch();
    }
}


/* ============================================================
                       ADMIN DASHBOARD
   ============================================================ */

void adminDashboard(void)
{
    int choice;

    while (1)
    {
        system("CLS");

        printf("\n\n");
        printf("============================================================\n");
        printf("                     ADMIN DASHBOARD\n");
        printf("============================================================\n\n");

        printf("1. View All Food Orders\n\n");
        printf("2. Update Admin Password\n\n");
        printf("3. Logout\n\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch (choice)
        {
            case 1:
                viewOrders();
                break;

            case 2:
                updateAdminPassword();
                break;

            case 3:
                printf("\nAdmin Logout Successful!");
                Sleep(1000);
                return;

            default:
                printf("\nInvalid choice!");
                getch();
        }
    }
}


/* ============================================================
                   UPDATE ADMIN PASSWORD
   ============================================================ */

void updateAdminPassword(void)
{
    char currentPassword[50];
    char newPassword[50];
    char confirmPassword[50];
    char savedPassword[50];

    FILE *file;

    system("CLS");

    printf("\n\n");
    printf("============================================================\n");
    printf("                  UPDATE ADMIN PASSWORD\n");
    printf("============================================================\n\n");


    /* Read current saved password */

    file = fopen("admin_password.txt", "r");


    if (file == NULL)
    {
        printf("\nPassword file not found!");
        printf("\n\nPress any key to return...");
        getch();
        return;
    }


    fscanf(file, "%49s", savedPassword);

    fclose(file);


    printf("Enter Current Password: ");
    scanf("%49s", currentPassword);


    /* Check current password */

    if (strcmp(currentPassword, savedPassword) != 0)
    {
        printf("\n\nCurrent Password is Incorrect!");

        printf("\n\nPress any key to return...");
        getch();

        return;
    }


    printf("\nEnter New Password: ");
    scanf("%49s", newPassword);

    printf("Confirm New Password: ");
    scanf("%49s", confirmPassword);


    /* Check both new passwords */

    if (strcmp(newPassword, confirmPassword) != 0)
    {
        printf("\n\nNew Password and Confirm Password do not match!");

        printf("\n\nPress any key to return...");
        getch();

        return;
    }


    /* Update password */

    file = fopen("admin_password.txt", "w");


    if (file == NULL)
    {
        printf("\nError updating password!");
        getch();
        return;
    }


    fprintf(file, "%s", newPassword);

    fclose(file);


    printf("\n\nPassword Updated Successfully!");

    printf("\n\nPress any key to return...");
    getch();
}


/* ============================================================
                        ORDER FOOD
   ============================================================ */

void orderFood(char username[])
{
    int choice;
    int quantity;

    float price;
    float itemTotal;
    float total = 0;

    char foodName[50];
    char more;

    FILE *orders;


    orders = fopen("orders.txt", "a");


    if (orders == NULL)
    {
        printf("\nUnable to save order!");
        getch();
        return;
    }


    do
    {
        system("CLS");

        printf("\n\n");
        printf("============================================================\n");
        printf("                       CANTEEN MENU\n");
        printf("============================================================\n\n");

        printf("1. Burger        - 150 Tk\n");
        printf("2. Pizza         - 300 Tk\n");
        printf("3. Sandwich      - 100 Tk\n");
        printf("4. Chicken Fry   - 120 Tk\n");
        printf("5. Fried Rice    - 180 Tk\n");
        printf("6. Noodles       - 150 Tk\n");
        printf("7. Tea           - 20 Tk\n");
        printf("8. Coffee        - 50 Tk\n\n");

        printf("Choose Food: ");
        scanf("%d", &choice);


        printf("Enter Quantity: ");
        scanf("%d", &quantity);


        if (quantity <= 0)
        {
            printf("\nInvalid Quantity!");

            printf("\n\nPress any key to continue...");
            getch();

            continue;
        }


        price = 0;


        switch (choice)
        {
            case 1:
                strcpy(foodName, "Burger");
                price = 150;
                break;

            case 2:
                strcpy(foodName, "Pizza");
                price = 300;
                break;

            case 3:
                strcpy(foodName, "Sandwich");
                price = 100;
                break;

            case 4:
                strcpy(foodName, "Chicken Fry");
                price = 120;
                break;

            case 5:
                strcpy(foodName, "Fried Rice");
                price = 180;
                break;

            case 6:
                strcpy(foodName, "Noodles");
                price = 150;
                break;

            case 7:
                strcpy(foodName, "Tea");
                price = 20;
                break;

            case 8:
                strcpy(foodName, "Coffee");
                price = 50;
                break;

            default:
                printf("\nInvalid Food Choice!");

                printf("\n\nPress any key to continue...");
                getch();

                continue;
        }


        itemTotal = price * quantity;

        total = total + itemTotal;


        /* Save order in orders.txt */

        fprintf(orders,
                "User: %s | Food: %s | Quantity: %d | Price: %.2f Tk\n",
                username,
                foodName,
                quantity,
                itemTotal);


        printf("\n\n%s added successfully!", foodName);

        printf("\nItem Total: %.2f Tk", itemTotal);

        printf("\n\nDo you want to order more? (Y/N): ");
        scanf(" %c", &more);

    }
    while (more == 'Y' || more == 'y');


    /* Save separator and total */

    fprintf(orders, "Total Bill: %.2f Tk\n", total);

    fprintf(orders,
            "------------------------------------------------------------\n");


    fclose(orders);


    printf("\n\n");
    printf("============================================================\n");
    printf("                    ORDER SUCCESSFUL\n");
    printf("============================================================\n\n");

    printf("Total Bill: %.2f Tk\n", total);

    printf("\nOrder details have been saved successfully!");

    printf("\n\nPress any key to return...");
    getch();
}


/* ============================================================
                   ADMIN VIEW ALL ORDERS
   ============================================================ */

void viewOrders(void)
{
    FILE *orders;
    int ch;

    system("CLS");

    printf("\n\n");
    printf("============================================================\n");
    printf("                     ALL FOOD ORDERS\n");
    printf("============================================================\n\n");


    orders = fopen("orders.txt", "r");


    if (orders == NULL)
    {
        printf("No food orders found!");

        printf("\n\nPress any key to return...");
        getch();

        return;
    }


    while ((ch = fgetc(orders)) != EOF)
    {
        putchar(ch);
    }


    fclose(orders);


    printf("\n\nPress any key to return...");
    getch();
}


/* ============================================================
                   FOOD ACCORDING TO WEIGHT
   ============================================================ */

void foodAccordingToWeight(void)
{
    float weight;
    float height;
    float bmi;

    system("CLS");

    printf("\n\n");
    printf("============================================================\n");
    printf("                 FOOD ACCORDING TO WEIGHT\n");
    printf("============================================================\n\n");

    printf("Enter your Weight in KG: ");
    scanf("%f", &weight);

    printf("Enter your Height in Meter (Example: 1.65): ");
    scanf("%f", &height);


    if (weight <= 0 || height <= 0)
    {
        printf("\nInvalid input!");

        printf("\n\nPress any key to return...");
        getch();

        return;
    }


    bmi = weight / (height * height);


    printf("\nYour BMI is: %.2f\n\n", bmi);


    if (bmi < 18.5)
    {
        printf("Category: Underweight\n\n");

        printf("Suggested Foods:\n");
        printf("- Milk\n");
        printf("- Eggs\n");
        printf("- Banana\n");
        printf("- Rice\n");
        printf("- Fish\n");
        printf("- Chicken\n");
        printf("- Nuts\n");
    }
    else if (bmi < 25)
    {
        printf("Category: Normal Weight\n\n");

        printf("Suggested Foods:\n");
        printf("- Balanced Rice\n");
        printf("- Vegetables\n");
        printf("- Fruits\n");
        printf("- Fish\n");
        printf("- Eggs\n");
        printf("- Milk\n");
    }
    else
    {
        printf("Category: Above Normal Weight\n\n");

        printf("General Healthy Food Suggestions:\n");
        printf("- Vegetables\n");
        printf("- Fruits\n");
        printf("- Lean Protein\n");
        printf("- Drink Enough Water\n");
        printf("- Limit Fried Food\n");
        printf("- Limit Sugary Drinks\n");
    }


    printf("\nPress any key to return...");
    getch();
}


/* ============================================================
                       FITNESS TEST
   ============================================================ */

void fitnessTest(void)
{
    int pushups;
    int situps;

    float runningTime;

    int score = 0;


    system("CLS");

    printf("\n\n");
    printf("============================================================\n");
    printf("                       FITNESS TEST\n");
    printf("============================================================\n\n");


    printf("Enter Number of Push-ups: ");
    scanf("%d", &pushups);

    printf("Enter Number of Sit-ups: ");
    scanf("%d", &situps);

    printf("Enter Running Time in Minutes: ");
    scanf("%f", &runningTime);


    /* Push-up Score */

    if (pushups >= 30)
        score += 30;

    else if (pushups >= 20)
        score += 20;

    else if (pushups >= 10)
        score += 10;


    /* Sit-up Score */

    if (situps >= 30)
        score += 30;

    else if (situps >= 20)
        score += 20;

    else if (situps >= 10)
        score += 10;


    /* Running Score */

    if (runningTime <= 5)
        score += 40;

    else if (runningTime <= 8)
        score += 30;

    else if (runningTime <= 12)
        score += 20;

    else
        score += 10;


    printf("\n\n");
    printf("============================================================\n");
    printf("                  FITNESS TEST RESULT\n");
    printf("============================================================\n\n");


    printf("Push-ups: %d\n", pushups);
    printf("Sit-ups: %d\n", situps);
    printf("Running Time: %.2f Minutes\n", runningTime);

    printf("\nTotal Score: %d / 100\n", score);


    if (score >= 80)
    {
        printf("\nResult: EXCELLENT\n");
        printf("You are fit for the tournament!\n");
    }
    else if (score >= 60)
    {
        printf("\nResult: GOOD\n");
        printf("You are eligible for the tournament!\n");
    }
    else
    {
        printf("\nResult: NEEDS IMPROVEMENT\n");
        printf("Practice more before the tournament!\n");
    }


    printf("\nPress any key to return...");
    getch();
}


/* ============================================================
                        MAIN FUNCTION
   ============================================================ */

int main(void)
{
    mainMenu();

    return 0;
}