#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>


typedef struct {
    int day;
    int month;
    int year;
} date;

typedef struct {
    int id;
    char name[150];
    float salary;
    date birth;
    char address[150];
    long mobile;
    date enrollment;
    char email[150];
} employee;

int isname(char text[]) {
    getchar();
    int i;
    for (i=0;text[i]!='\0';i++){
         if (!isalpha(text[i]) && text[i]!=' ') {
            printf("the eneterd data is not a text , repate it again \n");
            return 0; 
        }
    }
    return 1; 
}

int load_company_data(employee information[]) {
    FILE *company = fopen("data.txt", "r");
    if (company == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    int i = 0,j=0;
    while (i < 1000) {
        int items_read = fscanf(company,"%d,%149[^,],%f,%d-%d-%4d,%149[^,],%ld,%d-%d-%4d,%149[^\n]",
                                &information[i].id, information[i].name,
                                &information[i].salary, &information[i].birth.day,
                                &information[i].birth.month, &information[i].birth.year,
                                information[i].address, &information[i].mobile,
                                &information[i].enrollment.day,
                                &information[i].enrollment.month,
                                &information[i].enrollment.year, information[i].email);

        if (items_read == 12) { 
            i++;
        } 
        else if (items_read == EOF) {
            break;
        } 
        else {
            printf("Error: Incorrectly formatted line. in employee number %d , program will colse .\n", i+1);
            exit(1);
        }
    }

    fclose(company);
    return i;
}
void load_start_data(employee information[],employee start[],int i) {
    
    int j;
     for (j=0;j<i;j++){

       start[j]=information[j];
     }

}

void rewrite_employee(employee information[],int a){
    int i;
    FILE *company = fopen("data.txt", "w");
    if (company == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    for (i = 0; i < a-1; i++) {
    fprintf(company, "%d,%s,%0.2f,%d-%d-%d,%s,0%ld,%d-%d-%d,%s\n",
        information[i].id, information[i].name, information[i].salary,
        information[i].birth.day, information[i].birth.month, information[i].birth.year,
        information[i].address, information[i].mobile,
        information[i].enrollment.day, information[i].enrollment.month, information[i].enrollment.year,
        information[i].email);
    }
    fprintf(company, "%d,%s,%0.2f,%d-%d-%d,%s,0%ld,%d-%d-%d,%s",
        information[i].id, information[i].name, information[i].salary,
        information[i].birth.day, information[i].birth.month, information[i].birth.year,
        information[i].address, information[i].mobile,
        information[i].enrollment.day, information[i].enrollment.month, information[i].enrollment.year,
        information[i].email);

       fclose(company);
       company = fopen("data.txt", "r");
       if (company == NULL) {
      printf("Error opening file!\n");
      exit(1);
      }
}

int check_bod(int day, int month, int year) {
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    int currentYear = localTime->tm_year + 1900;
    int currentMonth = localTime->tm_mon + 1; 
    int currentDay = localTime->tm_mday;
    int daysInMonth;


    if (year < 1900 || year > currentYear) {
        printf("Wrong year entered, add the date again\n");
        return -1;
    }
    
    if (month < 1 || month > 12) {
        printf("Wrong month entered, add the date again\n");
        return -1;
    }
    
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            daysInMonth = 31;
            break;
        case 4: case 6: case 9: case 11:
            daysInMonth = 30;
            break;
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                daysInMonth = 29;
            } else {
                daysInMonth = 28;
            }
            break;
        default:
            daysInMonth = 0;
    }
    
    if (day < 1 || day > daysInMonth) {
        printf("Wrong day entered, add the date again\n");
        return -1;
    }
    
    if (year > currentYear - 18 || (year == currentYear - 18 && month > currentMonth) ||  (year == currentYear - 18 && month == currentMonth && day > currentDay)) 
    {
        printf("Employee must be at least 18 years old\n");
        return -1;
    }

    return 1;
}

int check_id(int id, int employees) {
    char Hold[900];
    employee temp;
    FILE *company = fopen("data.txt", "r");

    if (company == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    while (fgets(Hold, sizeof(Hold), company)!=NULL) { 
        sscanf(Hold, "%d", &temp.id);
        if (id == temp.id) {
            fclose(company);
            return -1; 
        }
    }

    fclose(company); 
    return 1; 
}
int check_email(char email[150]) {
    char name[51];
    char domain[51];
    char tld[51];
    int flag1 = 0, flag11 = 0, flag2 = 0, flag3 = 0;

    if (sscanf(email, "%50[^@]@%50[^.].%50s", name, domain, tld) == 3) {

        for (int i = 0; name[i] != '\0'; i++) {
            if (isalpha(name[i])) {
                flag1 = 1;
            }
            if (!isalpha(name[i]) && !isdigit(name[i]) && name[i] != '-') {
                flag11 = 1;
                break;
            }
        }
        for (int i = 0; domain[i] != '\0'; i++) {
            if (!isalpha(domain[i]) && !isdigit(domain[i]) && domain[i] != '-') {
                flag2 = 1;
                break;
            }
        }
        for (int i = 0; tld[i] != '\0'; i++) {
            if (!isalpha(tld[i])) {
                flag3 = 1;
                break;
            }
        }

        if (flag1 == 1 && flag11 == 0 && flag2 == 0 && flag3 == 0) {
            return 1;
        } else {
            if (flag1 == 0) {
                printf("The email's name part should contain at least one letter.\n");
            }
            if (flag11 != 0) {
                printf("The email's name part should contain only letters, numbers, and '-'.\n");
            }
            if (flag2 != 0) {
                printf("The email's domain part should contain only letters, numbers, and '-'.\n");
            }
            if (flag3 != 0) {
                printf("The email's TLD part should contain only letters.\n");
            }
            return -1;
        }
    }
     else {
        printf("wrong email entered , add the email again\n");
        return -1;
    }
}
    
int check_number(long int number) {
    int count=0 ;
    while (number!=0){
    count++;
    number = number/10;
     }
    if (count ==10)
    return 1;
    else {
     printf ("wrong mobile entered , add the mobile again\n");
    return -1;
    }
}


void add_employee(int a){
    employee temp;
    int scancheck;

    FILE *company = fopen("data.txt", "a");
    if (company == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    
    do{
     scancheck = 0;
    printf("Enter employee ID : ");
    scancheck = scanf("%d",&temp.id);
    while (getchar() != '\n');     
    if (scancheck!=1) {
          printf("You did not enter a valid number. Please try again.\n");   
    }
    if (check_id(temp.id ,a)==-1) {
    printf("You entered a duplicated ID.\n");
    }
    }while(check_id(temp.id ,a)==-1||scancheck!=1);
    
    do{
    printf("Enter employee full name : ");
    scanf("%149[^\n]",temp.name);
    }while(isname(temp.name)==0);

    do {
    scancheck=0;
    printf("Enter employee salary : ");
    scancheck = scanf("%f",&temp.salary);
    while (getchar() != '\n');     
    if (scancheck!=1) {
          printf("You did not enter a valid number. Please try again.\n");   
    } 
    }while(scancheck!=1);

    do{
    printf("Enter employee  birth date (dd/mm/yyyy) : ");
    scanf("%d/%d/%d",&temp.birth.day,&temp.birth.month,&temp.birth.year);
    getchar();
    }while(check_bod(temp.birth.day,temp.birth.month,temp.birth.year)==-1);

    printf("Enter employee address : ");
    scanf("%149[^\n]",temp.address);
    do {
            scancheck=0;

    printf("Enter employee mobile number : ");
    scancheck = scanf("%ld",&temp.mobile);
    while (getchar() != '\n');   
    if (scancheck!=1) {
        printf("You did not enter a valid number. Please try again.\n");   
    } 
    } while (check_number(temp.mobile) == -1|| scancheck!=1);

    do {
    printf("Enter employee email: ");
    scanf("%149[^\n]", temp.email);
    while ((getchar()) != '\n'); 
    } while (check_email(temp.email) == -1);
    
    
    setenv("TZ", "Africa/Cairo", 1);
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    temp.enrollment.day = (*localTime).tm_mday;
    temp.enrollment.month = (*localTime).tm_mon + 1; 
    temp.enrollment.year = (*localTime).tm_year + 1900;


    fprintf(company, "\n%d,%s,%0.2f,%d-%d-%4d,%s,0%ld,%d-%d-%4d,%s",
            temp.id, temp.name, temp.salary,
            temp.birth.day, temp.birth.month, temp.birth.year,temp.address,temp.mobile,temp.enrollment.day,temp.enrollment.month,temp.enrollment.year,temp.email);

    fclose(company); 

    
}

void search_employee(int a,employee information[]){

    char temp[151];
    int i,j,count=0,enter=0;
    
    getchar();
    printf("Enter employee name: ");
    scanf("%150[^\n]",temp);

    int n = strlen(temp);

    for (i=0;i<a;i++){
         count =0;
         for (j=0;j<n;j++){
            if (information[i].name[j]==temp[j])
            count ++;
          }

        if (count == n){
            printf("%d,%s,%0.2f,%d-%d-%d,%s,0%ld,%d-%d-%d,%s\n",information[i].id, information[i].name,
                                information[i].salary, information[i].birth.day,
                                information[i].birth.month, information[i].birth.year,
                                information[i].address, information[i].mobile,
                                information[i].enrollment.day,
                                information[i].enrollment.month,
                                information[i].enrollment.year, information[i].email);
                                
                                 enter=1;
        }
    }
        if (enter==0){
            printf("No matches found \n");
        }

}
 void quit (employee start[],int employee){
    int i;
    FILE *company = fopen("data.txt", "w");
    if (company == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    
    for (i=0;i<employee;i++){
    fprintf(company, "%d,%s,%0.2f,%d-%d-%4d,%s,0%ld,%d-%d-%4d,%s\n",
            start[i].id, start[i].name, start[i].salary,
            start[i].birth.day, start[i].birth.month, start[i].birth.year,start[i].address,start[i].mobile,start[i].enrollment.day,start[i].enrollment.month,start[i].enrollment.year,start[i].email);
    }
   fclose(company);
    

 }

 void delete_employee(employee information[],int a)
 {
    int id_delete,i,j=0;
    employee delete[1000];

    do{
    printf("Enter the Id of the employee you want to delete : ");
    scanf("%d",&id_delete);
    if (check_id(id_delete,a) == 1) {
    printf("You entered a wrong ID. Please try again.\n");
    }
    } while (check_id(id_delete,a)== 1);

    for (i = 0; i < a; i++) {
    if (id_delete != information[i].id) {
        
        delete[i - j] = information[i];
    } else {
        
        j++;
    }
      }

    rewrite_employee(delete, a-1);

 }
         
void modify_employee(employee information[],int a)
 {


    int id_modify,i,j=0,function=0;
    char text[150];
    long int numarical;
    float sala;
    do{
    printf("Enter the Id of the employee you want to modify : ");
    scanf("%d",&id_modify);
    getchar();
    if (check_id(id_modify,a)== 1 )
    printf("You entered wrong Id. add it again \n");
    } while (check_id(id_modify,a)== 1);

    for (i = 0; i < a; i++) {
    if (id_modify == information[i].id) {
        break;
        } 
      }
     
     do{
    printf("What you want to moodify\n1-Name\n2-salary\n3-mobile\n4-address\n5-email \n Enter the number of data you want to modify : ");
    scanf("%d",&function);
        getchar();

    } while (function<1 || function>5);

    if(function==1 ||function==4||function==5 ){
    printf("Enter the new data : ");
            scanf("%149[^\n]",text);

    }
    else if(function==2 ){
    printf("Enter the new data : ");
            scanf("%f",&sala);

    }
    else if(function==3 ){
    do {
         printf("Enter the new data : ");
            scanf("%ld",&numarical);

    }while (check_number(numarical) == -1);
    }
    
    if (function==1 ){
        strcpy(information[i].name,text);

    }

    else if (function==2 ){
        information[i].salary=sala;
        
    }

    else if (function==3 ){
    information[i].mobile=numarical;    
    }

    else if (function==4 ){
    strcpy(information[i].address,text);

        
    }
    else if (function==5 ){
      strcpy(information[i].email,text);
    }
    rewrite_employee(information, a);
 }

void sorted_salary(employee information[],int a){
    employee sort[1000];
    employee temp;
    int i,j;
    for (i=0;i<a;i++){

        sort[i]=information[i];
    }
     
    for(i=0;i<a-1;i++){
        
        for (j=0;j<a-1;j++){
        if(sort[j].salary<sort[j+1].salary){
        temp=sort[j];
        sort[j]=sort[j+1];
        sort[j+1]=temp;
        }

        }
    } 
    for (i=0;i<a;i++){
         printf("%d,%s,%0.2f,%d-%d-%4d,%s,0%ld,%d-%d-%4d,%s\n",sort[i].id, sort[i].name,
                                sort[i].salary, sort[i].birth.day,
                                sort[i].birth.month, sort[i].birth.year,
                                sort[i].address, sort[i].mobile,
                                sort[i].enrollment.day,
                                sort[i].enrollment.month,
                                sort[i].enrollment.year, sort[i].email);
    }
}
void sorted_name(employee information[],int a){
    employee sort[1000];
    employee temp;
    int i,j;
    for (i=0;i<a;i++){

        sort[i]=information[i];
    }
     
    for(i=0;i<a-1;i++){
        
        for (j=0;j<a-1;j++){
        if(strcmp(sort[j].name,sort[j+1].name)>0){
        temp=sort[j];
        sort[j]=sort[j+1];
        sort[j+1]=temp;
        }

        }
    } 
    for (i=0;i<a;i++){
         printf("%d,%s,%0.2f,%d-%d-%4d,%s,0%ld,%d-%d-%d,%s\n",sort[i].id, sort[i].name,
                                sort[i].salary, sort[i].birth.day,
                                sort[i].birth.month, sort[i].birth.year,
                                sort[i].address, sort[i].mobile,
                                sort[i].enrollment.day,
                                sort[i].enrollment.month,
                                sort[i].enrollment.year, sort[i].email);
    }
}

int check_bigger(int ad,int am,int ay,int bd,int bm,int by){

if (ay>by){

    return 1;
}

else if (ay==by&& am>bm){
    return 1;

}
else if (ay==by && am==bm && ad>bd){
    return 1;
}
else
return 0;

}

void sorted_birth(employee information[],int a){
    employee sort[1000];
    employee temp;
    int i,j;
    for (i=0;i<a;i++){

        sort[i]=information[i];
    }
    for(i=0;i<a-1;i++){
        
        for (j = 0; j < a - i - 1; j++) {
    if (check_bigger(sort[j].birth.day, sort[j].birth.month, sort[j].birth.year,sort[j + 1].birth.day, sort[j + 1].birth.month, sort[j + 1].birth.year) == 1)
     {
        temp = sort[j];
        sort[j] = sort[j + 1];
        sort[j + 1] = temp;
    }
}
    } 
    for (i=0;i<a;i++){
         printf("%d,%s,%0.2f,%d-%d-%4d,%s,0%ld,%d-%d-%d,%s\n",sort[i].id, sort[i].name,
                                sort[i].salary, sort[i].birth.day,
                                sort[i].birth.month, sort[i].birth.year,
                                sort[i].address, sort[i].mobile,
                                sort[i].enrollment.day,
                                sort[i].enrollment.month,
                                sort[i].enrollment.year, sort[i].email);
    }
}


 void print_sorted(employee information[],int a){
    int function;

    do {
     printf("What type of sort You want ? \n1-Name \n2-Salary \n3-Date of Birth \nEnter sort type : ");     
     scanf("%d",&function);
     } while (function<1|| function>3);

     if(function==1){
        sorted_name(information,a);
     }

     if(function==2){
        sorted_salary(information,a);
     }
     if(function==3){
        sorted_birth(information,a);
     }

 }


int main() {
    int function=0;
    employee information[1000];
    employee start[1000];
    int Q,em_start;

    FILE *company = fopen("data.txt", "r");
    if (company == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fclose(company);
    
    int a=load_company_data(information);
    em_start=a;
    load_start_data(information,start,em_start);

    do{
    do {
     printf("Choose the function \n 1-ADD \n 2-DELETE \n 3-MODIFY \n 4-SEARCH \n 5-PRINT \n 6-SAVE \n 7-QUIT  \n By enter the number of the function :  ");
     scanf("%d",&function);
     } while (function<1 || function>7);
     if (function==1){
     add_employee(a);
     a=load_company_data(information);
     printf("Added Successfully\n");
     printf("\n\n");
     }
     if (function==2){
     delete_employee(information,a);
     a=load_company_data(information);
     printf("delete Successfully\n");
     printf("\n\n");
     }
     if (function==3){
     modify_employee(information,a);
     printf("modifded Successfully\n");
     printf("\n\n");
     }
     else if (function==4){
     search_employee(a,information);
     printf("\n\n");
     }
     else if (function==5){
     print_sorted(information,a);
     printf("\n\n");
     }
     else if (function==6){
        a=load_company_data(information);
       printf("Saved Successfully\n");
     }
     
     else if (function==7){
        
        printf ("Are you want to exit without saving the data?\nEnter : \n1 for not saving \n2 For saving  \nany number else for show menu again :  ");
        scanf("%d",&Q);
        if (Q==1)
        {
            quit(start,em_start);
            exit(1);
        }
        else if (Q==2)
        exit(1);
        }
        
        else 

        function =0;
     

    }while (function!=7 );


return 1;

}