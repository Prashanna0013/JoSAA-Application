#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_CHOICES 5
#define MAX_CODE_LENGTH 5
#define MAX_NAME_LENGTH 100
#define MAX_DEPT_LENGTH 100

struct dept {
    char dept[20];
    int seats;
};

struct institution {
    char ccode[5];
    char cname[100];
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

struct ChoiceList {
    int roll_no;
    char code[MAX_CODE_LENGTH];
    char name[MAX_NAME_LENGTH];
    char dept[MAX_DEPT_LENGTH];
};
struct allotment{
  int rollno;
  char code[MAX_CODE_LENGTH];
  char name[MAX_NAME_LENGTH];
  char dept[MAX_DEPT_LENGTH];
};
struct allocate{
  int rollno;
  char code[MAX_CODE_LENGTH];
  char name[MAX_NAME_LENGTH];
  char dept[MAX_DEPT_LENGTH]; 
};
void allocate_seats(struct student s[], struct institution ins[], struct ChoiceList cl[], int stud_count, int ins_count, int choice_count) {
    FILE *f4;
    struct allotment allot[stud_count];
    struct allocate allot1[stud_count];
    f4 = fopen("allocations.txt", "w");
    int count = 0, a = 0, mrank1, mrank2, adrank1, adrank2, unallot[stud_count + 1], temp = 0, unall = 0, incre;

    for (int i = 0; i < choice_count; i++) {
        if (a != cl[i].roll_no) {
            for (int j = 0; j < ins_count; j++) {
                if ((strcmp(cl[i].code, ins[j].ccode) == 0) && (strcmp(cl[i].name, ins[j].cname) == 0)) {
                    for (int k = 0; k < 5; k++) {
                        if ((strcmp(cl[i].dept, ins[j].d[k].dept) == 0) && (ins[j].d[k].seats != 0)) {
                            a = cl[i].roll_no;
                            allot[count].rollno = cl[i].roll_no;
                            strncpy(allot[count].code, cl[i].code, MAX_CODE_LENGTH - 1);
                            allot[count].code[MAX_CODE_LENGTH - 1] = '\0';
                            strncpy(allot[count].name, cl[i].name, MAX_NAME_LENGTH - 1);
                            allot[count].name[MAX_NAME_LENGTH - 1] = '\0';
                            strncpy(allot[count].dept, cl[i].dept, MAX_DEPT_LENGTH - 1);
                            allot[count].dept[MAX_DEPT_LENGTH - 1] = '\0';
                            ins[j].d[k].seats--;
                            count++;
                            break;
                        }
                        if ((strcmp(cl[i].dept, ins[j].d[k].dept) == 0) && (ins[j].d[k].seats == 0)) {
                            if (strncmp(cl[i].name, "NITTrichy", 3) == 0) {
                                for (int x = 0; x < count; x++) {
                                    if ((strcmp(cl[i].name, allot[x].name) == 0) && (strcmp(cl[i].dept, allot[x].dept) == 0)) {
                                        for (int y = 0; y < stud_count; y++) {
                                            if (cl[i].roll_no == s[y].rollno) {
                                                mrank1 = s[y].mains;
                                            }
                                            if (allot[x].rollno == s[y].rollno) {
                                                mrank2 = s[y].mains;
                                            }
                                        }
                                        if (mrank1 < mrank2) {
                                            unallot[unall] = allot[x].rollno;
                                            //Increment the seat count for the branch
                                            for (int z = 0; z < ins_count; z++) {
                                                if (strcmp(allot[x].code, ins[z].ccode) == 0 && strcmp(allot[x].name, ins[z].cname) == 0) {
                                                    for (int w = 0; w < 5; w++) {
                                                        if (strcmp(allot[x].dept, ins[z].d[w].dept) == 0) {
                                                            ins[z].d[w].seats++;
                                                            break;
                                                        }
                                                    }
                                                    break;
                                                }
                                            }
                                            allot[x].rollno = cl[i].roll_no;
                                            //printf("%d\n", cl[i].roll_no);
                                            unall++;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                }
                            }
                            else if (strncmp(cl[i].name, "IITMadras", 3) == 0) {
                                for (int x = 0; x < count; x++) {
                                    if ((strcmp(cl[i].name, allot[x].name) == 0) && (strcmp(cl[i].dept, allot[x].dept) == 0)) {
                                        for (int y = 0; y < stud_count; y++) {
                                            if (cl[i].roll_no == s[y].rollno) {
                                                adrank1 = s[y].adv;
                                            }
                                            if (allot[x].rollno == s[y].rollno) {
                                                adrank2 = s[y].adv;
                                            }
                                        }
                                        if (adrank1 < adrank2) {
                                            unallot[unall] = allot[x].rollno;
                                            // Increment the seat count for the branch
                                            for (int z = 0; z < ins_count; z++) {
                                                if (strcmp(allot[x].code, ins[z].ccode) == 0 && strcmp(allot[x].name, ins[z].cname) == 0) {
                                                    for (int w = 0; w < 5; w++) {
                                                        if (strcmp(allot[x].dept, ins[z].d[w].dept) == 0) {
                                                            ins[z].d[w].seats++;
                                                            break;
                                                        }
                                                    }
                                                    break;
                                                }
                                            }
                                            allot[x].rollno = cl[i].roll_no;
                                            //printf("%d\n", cl[i].roll_no);
                                            unall++;
                                        }
                                        else {
                                            continue;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int b;
    for (int i = 0; i < unall; i++) {
        for (int j = 0; j < choice_count; j++) {
            if (unallot[i] == cl[j].roll_no) {
                if (b != cl[j].roll_no) {
                    for (int k = 0; k < ins_count; k++) {
                        if (strcmp(cl[j].code, ins[k].ccode) == 0 && strcmp(cl[j].name, ins[k].cname) == 0) {
                            for (int l = 0; l < 5; l++) {
                                if (strcmp(cl[j].dept, ins[k].d[l].dept) == 0 && ins[k].d[l].seats != 0) {
                                    b = cl[j].roll_no;
                                    allot1[temp].rollno = cl[j].roll_no;
                                    strncpy(allot1[temp].code, cl[j].code, MAX_CODE_LENGTH - 1);
                                    allot1[temp].code[MAX_CODE_LENGTH - 1] = '\0';
                                    strncpy(allot1[temp].name, cl[j].name, MAX_NAME_LENGTH - 1);
                                    allot1[temp].name[MAX_NAME_LENGTH - 1] = '\0';
                                    strncpy(allot1[temp].dept, cl[j].dept, MAX_DEPT_LENGTH - 1);
                                    allot1[temp].dept[MAX_DEPT_LENGTH - 1] = '\0';
                                    ins[k].d[l].seats--;
                                    temp++;
                                    break;
                                }
                            }
                        }
                        else {
                            continue;
                        }
                    }
                }
                else {
                    continue;
                }
            }
        }
    }

    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (allot[i].rollno == allot[j].rollno) {
                for (int k = j; k < count - 1; k++) {
                    allot[k].rollno = allot[k + 1].rollno;
                    strncpy(allot[k].code, allot[k + 1].code, MAX_CODE_LENGTH - 1);
                    allot[k].code[MAX_CODE_LENGTH - 1] = '\0';
                    strncpy(allot[k].name, allot[k + 1].name, MAX_NAME_LENGTH - 1);
                    allot[k].name[MAX_NAME_LENGTH - 1] = '\0';
                    strncpy(allot[k].dept, allot[k + 1].dept, MAX_DEPT_LENGTH - 1);
                    allot[k].dept[MAX_DEPT_LENGTH - 1] = '\0';
                }
                count--;
                j--;
            }
        }
    }

    for (int i = 0; i < temp; i++) {
        allot[count].rollno = allot1[i].rollno;
        strncpy(allot[count].code, allot1[i].code, MAX_CODE_LENGTH - 1);
        allot[count].code[MAX_CODE_LENGTH - 1] = '\0';
        strncpy(allot[count].name, allot1[i].name, MAX_NAME_LENGTH - 1);
        allot[count].name[MAX_NAME_LENGTH - 1] = '\0';
        strncpy(allot[count].dept, allot1[i].dept, MAX_DEPT_LENGTH - 1);
        allot[count].dept[MAX_DEPT_LENGTH - 1] = '\0';
        count++;
    }

    for (int i = 0; i < count; i++) {
        fprintf(f4, "Roll Number: %d College Code: %s College Name: %s Branch: %s\n", allot[i].rollno, allot[i].code, allot[i].name, allot[i].dept);
    }

    fclose(f4);
}

int main() {
    FILE *f1, *f2, *f3, *output;
    f1 = fopen("allotcheck_Institutions.txt", "r");
    f2 = fopen("Student.txt", "r");
    f3 = fopen("base_choice_list.txt", "r");
    
    if (f1 == NULL || f2 == NULL || f3 == NULL) {
        printf("Failed to open one or more files.\n");
        return 1;
    }

    struct institution ins[100];
    struct student s[100];
    struct ChoiceList cl[100];

    int ins_count = 0, stud_count = 0, choice_count = 0;
    char ins_line[100], stud_line[100], choice_line[100];

    while (fgets(ins_line, sizeof(ins_line), f1)) {
        sscanf(ins_line, "%s %99[^\n]", ins[ins_count].ccode, ins[ins_count].cname);
        for (int j = 0; j < 5; j++) {
            fgets(ins_line, sizeof(ins_line), f1);
            sscanf(ins_line, "%s %d", ins[ins_count].d[j].dept, &ins[ins_count].d[j].seats);
        }
        ins_count++;
    }

    while (fscanf(f2, "%d %19s %19s %d %d", &s[stud_count].rollno, s[stud_count].fname, s[stud_count].sname, &s[stud_count].mains, &s[stud_count].adv) == 5) {
        s[stud_count].allotted = 0;  // Initialize allotted flag to 0
        s[stud_count].allot_inst = -1; // Initialize allotted institution index to -1
        stud_count++;
    }

    while (fgets(choice_line, sizeof(choice_line), f3)) {
        sscanf(choice_line, "Roll Number: %d College Code: %s College Name: %s Branch: %s", &cl[choice_count].roll_no, cl[choice_count].code, cl[choice_count].name, cl[choice_count].dept);
        choice_count++;
    }

    // Call the function to allocate seats to all students based on their choices
    allocate_seats(s, ins, cl, stud_count, ins_count, choice_count);

    // Close the files
    fclose(f1);
    fclose(f2);
    fclose(f3);
    

    return 0;
}
