#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size1 100
#define size2 50
#define MAX_LENGTH 100
struct students{
  int roll_no;
  char first_name[20];
  char second_name[20];
  int mains_rank;
  int adv_rank;
};
typedef struct {
  int rollNumber;
  char first_name[25];
  char last_name[25];
  int jee_mains;
  int jee_adv;
  char collegeCode[MAX_LENGTH];
  char collegeName[MAX_LENGTH];
  char branch[MAX_LENGTH];
} Student;

struct dept{
  char dname[5];
  int seat;
};
struct inst{
  char code[5];
  char name[100];
  struct dept d[5];
};
int institution(int len){
  
  struct inst i1[len];
  FILE *f1;
  f1=fopen("allotcheck_Institutions.txt","w");
  for(int i=0;i<len;i++){
    printf("Enter institution code: ");
    scanf("%s",i1[i].code);
    printf("Enter institution name: ");
    scanf("%s",i1[i].name);
    fprintf(f1,"%s %s\n",i1[i].code,i1[i].name);
    for(int j=0;j<5;j++){
      printf("Enter department name: ");
      scanf("%s",i1[i].d[j].dname);
      printf("Enter no.of seats: ");
      scanf("%d",&i1[i].d[j].seat);
      fprintf(f1,"%s %d\n",i1[i].d[j].dname,i1[i].d[j].seat);
    }
   
  }
  fclose(f1);
  
}
void student(int len) {
    FILE *f1;
    f1 = fopen("Student.txt", "w");
    if (f1 == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    struct students s1[len];
    for (int i = 0; i < len; i++) {
        printf("Enter student rollno: ");
        scanf("%d", &s1[i].roll_no);
        printf("Enter student first name: ");
        scanf("%s", s1[i].first_name);
        printf("Enter student second name: ");
        scanf("%s", s1[i].second_name);
        printf("Enter mains rank: ");
        scanf("%d", &s1[i].mains_rank);
        printf("Enter advanced rank(-1 if not applicable): ");
        scanf("%d", &s1[i].adv_rank);
    }

    for (int i = 0; i < len; i++) {
        fprintf(f1, "\n%d %s %s %d %d", s1[i].roll_no, s1[i].first_name, s1[i].second_name, s1[i].mains_rank, s1[i].adv_rank);
    }

    fclose(f1); 
}
void writeChoicesToFile(Student student);

int main(){
  int len,opt;
  while(1){
    printf("1.Enter Institution details\n2.Enter entire student choicelist\n3.Enter student details\n4.Exit.\n");
    printf("Enter your choice: ");
    scanf("%d",&opt);
    if(opt==1){
      printf("Enter no.of institution:");
      scanf("%d",&len);
      institution(len);
    }if(opt==2){
       FILE *file = fopen("Student.txt", "r");
  FILE *outputFile = fopen("base_choice_list.txt", "w");

  if (file == NULL || outputFile == NULL) {
    printf("Failed to open file(s).\n");
    return 1;
  }
   int ins_count=0;
    char ins_line[MAX_LENGTH];
    FILE *f1;
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


  Student student;
  //char dummy[MAX_LENGTH]; // Dummy variable to read remaining characters on each
                          // line

  while (fscanf(file, "%d %s %s %d %d", &student.rollNumber, student.first_name,
                student.last_name, &student.jee_mains, &student.jee_adv) == 5) {
    for (int j = 0; j < 5; j++) {
      if (student.jee_adv == -1) {
        printf("You can give only NITs choices!\n");
      } else {
        printf("You can give both IITs and NITs choices!\n");
      }
      printf("Enter choice %d for student with roll number %d:\n", j + 1,
             student.rollNumber);

      printf("College code: ");
      if (scanf(" %99[^\n]", student.collegeCode) != 1) {
        printf("Error reading college code.\n");
        break;
      }

      printf("College name: ");
      if (scanf(" %99[^\n]", student.collegeName) != 1) {
        printf("Error reading college name.\n");
        break;
      }

      printf("Branch: ");
      if (scanf(" %99[^\n]", student.branch) != 1) {
        printf("Error reading branch.\n");
        break;
      }

      writeChoicesToFile(student);
    }
  }

  fclose(file);
  fclose(outputFile);

  printf("Choices have been written to base_choice_list.txt.\n");

      continue;
    }
    if(opt==3){
    int len;
  printf("Enter no.of students: ");
  scanf("%d",&len);
  student(len);
      continue;
    }
    if(opt==4){
      break;
    }
  
  }
  
}
void writeChoicesToFile(Student student) {
    FILE *outputFile = fopen("base_choice_list.txt", "w");

    if (outputFile == NULL) {
        printf("Failed to open output file.\n");
        return;
    }

    fprintf(outputFile, "Roll Number: %d ", student.rollNumber);
    fprintf(outputFile, "College Code: %s ", student.collegeCode);
    fprintf(outputFile, "College Name: %s ", student.collegeName);
    fprintf(outputFile, "Branch: %s\n", student.branch);

    fclose(outputFile);
}


