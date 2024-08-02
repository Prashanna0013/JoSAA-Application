#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size1 100
#define size2 50
#define MAX_CHOICES 50
struct login {
    char username[50];
    char password[9]; // Increased password size to accommodate null character
};

struct dept{
  char dname[5];
  int seat;
};
struct inst{
  char code[5];
  char name[20];
  struct dept d[5];
};
struct student {
    int rollno;
    char fname[20];
    char sname[20];
    int mains, adv;
    int allotted;  // Indicates whether the student is allotted a seat
    int allot_inst;  // Institution index where the student is allotted
};

struct choice{
  int rollNumber;
  char collegeCode[5];
  char collegeName[50];
  char branch[10];
};

void user_login() {
    struct login l;
    FILE *f1;
    f1 = fopen("login.txt", "w+");
    printf("Enter new username: ");
    scanf("%s", l.username);
    printf("Enter new password (up to 8 characters): ");
    scanf("%s", l.password);
    fprintf(f1, "%s %s", l.username, l.password);
    fclose(f1);
}

int login() {
    struct login l;
    char username[50], password[9];
    int opt;

    FILE *f1;
    f1 = fopen("login.txt", "r");
    if (f1 == NULL) {
        user_login();
        return 0;
    } else {
        printf("Enter your option:\n");
        printf("1. Log in\n2. Sign up\n3. Exit\n");
        scanf("%d", &opt);
    }

    fscanf(f1, "%s %s", l.username, l.password);
    fclose(f1);

    switch (opt) {
        case 1: {
            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", password);
            if ((strcmp(username, l.username) == 0) && (strcmp(password, l.password) == 0)) {
                printf("Logged in successfully!\n");
                return 1;
            } else {
                printf("Invalid username or password.\n");
                return 0;
            }
        }
        case 2: {
            user_login();
            return login();
        }
        case 3: {
            break;
        }
        default: {
            printf("Invalid option.\n");
            return 0;
        }
    }

    return 0;
}

void display() {
  printf("\n---Seat Allocation System Menu---");
    printf("\n1. Display institutions.\n2. Display Ranklist\n3. Display your rank\n4. Show allotted seat.\n");
    int opt, count = 0,ins_count;
    char c, ins_line[100], line2[100],line3[100];
    struct choice choices[MAX_CHOICES];
    FILE *f1, *f2;
    f2 = fopen("Student.txt", "r");
    while ((c = fgetc(f2)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }
    fclose(f2);
     struct student s[100];
    printf("Enter your option: ");
    scanf("%d", &opt);
    switch (opt) {
        case 1: {
            f1 = fopen("allotcheck_Institutions.txt", "r");
          struct inst ins[100];
          printf("\n---Institutions---");
            while (fgets(ins_line, sizeof(ins_line), f1)) {
        sscanf(ins_line, "%s %99[^\n]", ins[ins_count].code, ins[ins_count].name);
        for (int j = 0; j < 5; j++) {
            fgets(ins_line, sizeof(ins_line), f1);
            sscanf(ins_line, "%s %d", ins[ins_count].d[j].dname, &ins[ins_count].d[j].seat);
        }
        ins_count++;
    }
          for(int i=0;i<ins_count;i++){
            printf("\n%s %s\n",ins[i].code,ins[i].name);
            for(int j=0;j<5;j++){
              printf("%s ",ins[i].d[j].dname);
            }
            printf("\n");
          }
            fclose(f1);
            break;
        }
        case 2: {
            f1 = fopen("Student.txt", "r");
          printf("\n---Ranklist---");
            while (fgets(line2, sizeof(line2), f1) != NULL) {
                printf("%s", line2);
            }
            fclose(f1);
            break;
        }
        case 3: {
            int roll_no, stud_count = 0;
            f1 = fopen("Student.txt", "r");
            printf("Enter your roll no: ");
            scanf("%d", &roll_no);
           while (fscanf(f2, "%d %19s %19s %d %d", &s[stud_count].rollno, s[stud_count].fname, s[stud_count].sname, &s[stud_count].mains, &s[stud_count].adv) == 5) {
        s[stud_count].allotted = 0;  // Initialize allotted flag to 0
        s[stud_count].allot_inst = -1; // Initialize allotted institution index to -1
        stud_count++;
    }
            fclose(f1);
            for (int j = 0; j < stud_count; j++) {
                if (roll_no == s[j].rollno) {
                  printf("\n---Your Rank---\n");
                    printf("Mains rank: %d\nAdvanced rank: %d\n", s[j].mains, s[j].adv);
                    break;
                }
            }
            break;
        }
        case 4: {
            struct choice c[count];
            int roll_no,count1=0;
            f1 = fopen("allocations.txt", "r");
            printf("Enter your roll no: ");
            scanf("%d", &roll_no);
            while (fgets(line3, sizeof(line3),f1)!=NULL) {
                sscanf(line3,"Roll Number: %d College Code: %s College Name: %s Branch: %s",&c[count1].rollNumber,c[count1].collegeCode,c[count1].collegeName,c[count1].branch);
          
              count1++;
            }
            for (int j = 0; j < count1; j++) {
                if (roll_no == c[j].rollNumber) {
                  printf("\n---Allotted Seat---");
                    printf("\nRoll Number: %d\nCollege Code: %s\nCollege Name: %s\nBranch: %s\n\n", c[j].rollNumber,c[j].collegeCode,c[j].collegeName,c[j].branch);
                    break;
                }
            }
          char choose[10];
          printf("\nDo you accept the allocated seat?(yes/no): ");
          scanf("%s",choose);
          if(strcmp(choose, "yes")==0){
            printf("\nYou are seat is allocated. Futher information will be provided.");
          }
          else{
              printf("\nThank you for using JoSAA server.");
            }
          
          fclose(f1);
            break;
        }
        default:
            printf("Invalid option.\n");
            break;
    }
}

int main() {
    
    int log_in = login();
    
    if (log_in == 1) {
        while (1) {
            printf("\n---Seat Allocation System---\n");
            printf("\n1. Show options\n2. Exit\n");
            int opt;
            printf("Enter your option: ");
            scanf("%d", &opt);
            if (opt == 1) {
                display();
            } else if (opt == 2) {
                break;
            } else {
                printf("Invalid option.\n");
            }
        }
    } else {
        printf("Login Failed!\nPlease try again.\n");
        int opt,log_in;
        printf("1.Login again\n2.Exit\n");
        scanf("%d",&opt);
        if(opt==1){
            int log_in = login();
            if (log_in == 1) {
        while (1) {
            printf("\n---Seat Allocation System---\n");
            printf("\n1. Show options\n2. Exit\n");
            int opt;
            printf("Enter your option: ");
            scanf("%d", &opt);
            if (opt == 1) {
                display();
            } else if (opt == 2) {
                break;
            } else {
                printf("Invalid option.\n");
            }
        }
    }
        }
        else{
          printf("Thank you!");
        }
    }
    

    return 0;
}


