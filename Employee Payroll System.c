#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================= FUNCTION DECLARATIONS ================= */
int managerLogin();
void forgotPassword();
void loadFile();
void mainMenu();

/* ===== MANAGER LOGIN DATA ===== */
char managerId[20] = "admin";
char managerPass[20] = "ak47";
char securityAnswer[20] = "payroll";

/* ================= GLOBAL VARIABLES ================= */
int choice, i, id, found;
int empCount = 0;

int empId[20], empAge[20];
char empName[30][40], empDepartment[30][40];
float basic[20], hra[20], da[20];
float gross[20], tax[20], net[20];

/* ================= MANAGER LOGIN ================= */
int managerLogin()
{
    char id[20], pass[20];
    int attempts = 3;

    while (attempts > 0)
    {
        printf("\n\n\n===== MANAGER LOGIN =====\n");
        printf("\nEnter Manager ID : ");
        scanf("%s", id);
        printf("Enter Password   : ");
        scanf("%s", pass);

        if (strcmp(id, managerId) == 0 && strcmp(pass, managerPass) == 0)
        {
            printf("\n------------------------\nLogin Successfully...!!!\n------------------------\n");
            return 1;
        }
        else
        {
            attempts--;
            printf("\nInvalid Credentials!");
            printf("\nAttempts Left: %d\n", attempts);

            if (attempts == 0)
            {
                int ch;
                printf("\n1. Forgot Password\n2. Exit\nChoose: ");
                scanf("%d", &ch);

                if (ch == 1)
                    forgotPassword();

                return 0;
            }
        }
    }
    return 0;
}

void forgotPassword()
{
    char answer[20];

    printf("\n=========== FORGOT PASSWORD ===========\n");
    printf("Security Question:\n");
    printf("What is the system keyword? : ");
    scanf("%s", answer);

    if (strcmp(answer, securityAnswer) == 0)
    {
        printf("\nPassword is: %s\n", managerPass);
    }
    else
    {
        printf("\nWrong Answer! Access Denied.\n");
    }
}

/* ================= EMPLOYEE FUNCTIONS ================= */
void addEmployee()
{
    int newId;

    printf("--------------------\n\n\nEnter Employee ID: ");
    scanf("%d", &newId);

    /* CHECK FOR DUPLICATE EMPLOYEE ID */
    for (i = 0; i < empCount; i++)
    {
        if (empId[i] == newId)
        {
            printf("\n------------------------------\n");
            printf("Employee ID Already Exists...!!!\n");
            printf("--------------------------------\n");
            return;
        }
    }

    empId[empCount] = newId;

    getchar(); // clear newline from buffer

    printf("Enter Employee Name: ");
    fgets(empName[empCount], 40, stdin);
    empName[empCount][strcspn(empName[empCount], "\n")] = '\0';

    printf("Enter Basic Salary: ");
    scanf("%f", &basic[empCount]);

    printf("Enter Employee Age: ");
    scanf("%d", &empAge[empCount]);

    getchar(); // clear newline again

    printf("Enter Employee Department : ");
    fgets(empDepartment[empCount], 40, stdin);
    empDepartment[empCount][strcspn(empDepartment[empCount], "\n")] = '\0';

    hra[empCount] = basic[empCount] * 0.20;
    da[empCount] = basic[empCount] * 0.10;
    gross[empCount] = basic[empCount] + hra[empCount] + da[empCount];
    tax[empCount] = gross[empCount] * 0.05;
    net[empCount] = gross[empCount] - tax[empCount];

    empCount++;
    printf("\n---------------------------------\nEmployee Added Successfully...!!!\n---------------------------------\n");
}

void viewEmployee()
{
    printf("--------------------\n\n\n\n                           =======================================\n                                 ");
    printf("E M P L O Y E E S   L I S T \n                           =======================================\n");
    for (i = 0; i < empCount; i++)
    {
        printf("\n\n");
        printf("Emp.ID: %d", empId[i]);
        printf(" | Emp.Name: %s", empName[i]);
        printf(" | Emp.Salary: %.1f", basic[i]);
        printf(" | Emp.Age: %d", empAge[i]);
        printf(" | Emp.Department : %s", empDepartment[i]);
    }
}

void deleteEmployee()
{
    printf("--------------------\n\n\n");
    printf("Enter Employee ID to Delete: ");
    scanf("%d", &id);
    found = 0;

    for (i = 0; i < empCount; i++)
    {
        if (empId[i] == id)
        {
            for (int j = i; j < empCount - 1; j++)
            {
                empId[j] = empId[j + 1];
                empAge[j] = empAge[j + 1];
                basic[j] = basic[j + 1];
                hra[j] = hra[j + 1];
                da[j] = da[j + 1];
                gross[j] = gross[j + 1];
                tax[j] = tax[j + 1];
                net[j] = net[j + 1];
            }
            empCount--;
            printf("\n-----------------------------------\nEmployee Deleted Successfully...!!!\n-----------------------------------\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf("\n------------------------\nEmployee Not Found...!!!\n------------------------\n");
}
void updateEmployee()
{
    int updateChoice;
    char cont;

    printf("--------------------\n\n");
    printf("Enter Employee ID to Update: ");
    scanf("%d", &id);
    found = 0;

    for (i = 0; i < empCount; i++)
    {
        if (empId[i] == id)
        {
            found = 1;

            do
            {
                printf("\n--------------------------------\nWhat do you want to update...???\n--------------------------------\n\n");
                printf("1. Name            ");
                printf("4. Age\n");
                printf("2. Basic Salary    ");
                printf("5. Department\n");
                printf("3. Update All\n\n---------------\n");
                printf("Enter choice: ");
                scanf("%d", &updateChoice);

                getchar(); // clear newline

                switch (updateChoice)
                {
                case 1:
                    printf("---------------\n\nEnter New Employee Name: ");
                    fgets(empName[i], 40, stdin);
                    empName[i][strcspn(empName[i], "\n")] = '\0';
                    break;

                case 2:
                    printf("---------------\n\nEnter New Basic Salary: ");
                    scanf("%f", &basic[i]);
                    break;

                case 3:

                    printf("---------------\n\nEnter New Employee Name: ");
                    fgets(empName[i], 40, stdin);
                    empName[i][strcspn(empName[i], "\n")] = '\0';

                    printf("Enter New Employee Age: ");
                    scanf("%d", &empAge[i]);

                    printf("Enter New Basic Salary: ");
                    scanf("%f", &basic[i]);
                    getchar();

                    printf("Enter New Employee Department: ");
                    fgets(empDepartment[i], 40, stdin);
                    empDepartment[i][strcspn(empDepartment[i], "\n")] = '\0';
                    break;

                case 4:

                    printf("---------------\n\nEnter New Employee Age: ");
                    scanf("%d", &empAge[i]);
                    break;

                case 5:
                    printf("---------------\n\nEnter New Employee Department: ");
                    fgets(empDepartment[i], 40, stdin);
                    empDepartment[i][strcspn(empDepartment[i], "\n")] = '\0';
                    break;

                default:
                    printf("\nInvalid Update Choice!\n");
                    continue;
                }

                /* Recalculate salary */
                hra[i] = basic[i] * 0.20;
                da[i] = basic[i] * 0.10;
                gross[i] = basic[i] + hra[i] + da[i];
                tax[i] = gross[i] * 0.05;
                net[i] = gross[i] - tax[i];

                printf("\n---------------------------------\nRecord Updated Successfully...!!!\n---------------------------------\n");

                printf("\nDo you want to continue updating this employee? (y/n): ");
                scanf(" %c", &cont);

            } while (cont == 'y' || cont == 'Y');

            break;
        }
    }

    if (!found)
        printf("\n------------------------\nEmployee Not Found...!!!\n------------------------\n");
}

void generatePaySlip()
{
    printf("--------------------\n\n\n                                ======================================\n                                     ");
    printf("P A Y R O L L    R E P O R T \n                                ======================================\n\n");
    for (i = 0; i < empCount; i++)
    {
        printf("\n ID : %d", empId[i]);
        printf(" | Basic : %.1f", basic[i]);
        printf(" | HRA : %.1f", hra[i]);
        printf(" | DA : %.1f", da[i]);
        printf(" | Gross : %.1f", gross[i]);
        printf(" | Tax : %.1f", tax[i]);
        printf(" | NetSalary : %.1f\n", net[i]);
    }
}

void saveFile()
{
    FILE *file = fopen("employees.txt", "w");

    if (file == NULL)
    {
        printf("\n-----------------------------\nError Saving File...!!!\n-----------------------------\n");
        return;
    }

    fprintf(file, "EMPLOYEE PAYROLL DATA\n");
    fprintf(file, "=============================================================\n");

    for (i = 0; i < empCount; i++)
    {
        fprintf(file, "Employee ID      : %d\n", empId[i]);
        fprintf(file, "Employee Name    : %s\n", empName[i]);
        fprintf(file, "Employee Age     : %d\n", empAge[i]);
        fprintf(file, "Department       : %s\n", empDepartment[i]);
        fprintf(file, "Basic Salary     : %.2f\n", basic[i]);
        fprintf(file, "HRA              : %.2f\n", hra[i]);
        fprintf(file, "DA               : %.2f\n", da[i]);
        fprintf(file, "Gross Salary     : %.2f\n", gross[i]);
        fprintf(file, "Tax              : %.2f\n", tax[i]);
        fprintf(file, "Net Salary       : %.2f\n", net[i]);
        fprintf(file, "-------------------------------------------------------------\n");
    }

    fclose(file);

    printf("--------------------\n\n-----------------------------\nData Saved Successfully...!!!\n-----------------------------\n\n");
}

void loadFile()
{
    FILE *file = fopen("employees.txt", "r");

    if (file == NULL)
    {
        return; // file does not exist
    }

    empCount = 0;

    char line[200];

    /* Skip header lines */
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);

    while (!feof(file))
    {
        if (fscanf(file, "Employee ID      : %d\n", &empId[empCount]) != 1)
            break;

        fscanf(file, "Employee Name    : %[^\n]\n", empName[empCount]);
        fscanf(file, "Employee Age     : %d\n", &empAge[empCount]);
        fscanf(file, "Department       : %[^\n]\n", empDepartment[empCount]);
        fscanf(file, "Basic Salary     : %f\n", &basic[empCount]);
        fscanf(file, "HRA              : %f\n", &hra[empCount]);
        fscanf(file, "DA               : %f\n", &da[empCount]);
        fscanf(file, "Gross Salary     : %f\n", &gross[empCount]);
        fscanf(file, "Tax              : %f\n", &tax[empCount]);
        fscanf(file, "Net Salary       : %f\n", &net[empCount]);
        fscanf(file, "-------------------------------------------------------------\n");

        empCount++;

        if (empCount >= 20)
            break;
    }

    fclose(file);
}

/* ================= MENU ================= */
void mainMenu()
{
    printf("\n\n\n=====================================================================================================\n\n");
    printf("                         E M P L O Y E E     P A Y R O L L     S Y S T E M \n\n");
    printf("=====================================================================================================\n");
    printf("\n                  1: ADD EMPLOYEE                             4: DELETE EMPLOYEE\n\n");
    printf("                  2: VIEW EMPLOYEES                           5: GENERATE PAYROLL SLIP\n\n");
    printf("                  3: UPDATE EMPLOYEE                          6: SAVE & EXIT\n\n\n");
    printf("--------------------\nEnter Your Choice: ");
}

/* ================= MAIN ================= */
int main()
{
    if (!managerLogin())
    {
        printf("\nUnauthorized Access! Program Terminated.\n");
        exit(0);
    }

    loadFile(); // LOAD DATA AFTER LOGIN

    while (1)
    {
        mainMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addEmployee();
            break;
        case 2:
            viewEmployee();
            break;
        case 3:
            updateEmployee();
            break;
        case 4:
            deleteEmployee();
            break;
        case 5:
            generatePaySlip();
            break;
        case 6:
            saveFile();
            exit(0);
        default:
            printf("\n---------------\nInvalid choice:\n---------------\n");
        }
    }
}
