#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 40
struct student {
  int rollno;
  char name[size];
  int mains_rank, adv_rank;
};
struct student2 {
  int rollno;
  char name[size];
  float rank;
};
struct institution {
  char inst_name[size];

  struct dept {
    char dept_name[20];
    int no_of_seats;
  } dp[5];
};
struct choice {
  int rollno;
  struct preference {
    char inst[20];
    char dept[20];
  } ch[10];
};
struct seatdetails {
  int rollno;
  char name[40];
  char clg[40];
  char branch[40];
};
void editchoices() {
  int len = 100;
  FILE *r1;
  struct choice choice1[len];
  r1 = fopen("Student_choices.txt", "r");
  fread(choice1, sizeof(choice1), 1, r1);
  fclose(r1);
  int rollnumber;
  int temp, c;
  printf("enter your rollnumber ");
  scanf("%d", &rollnumber);
  for (int i = 0; i < 100; i++) {
    if (rollnumber == choice1[i].rollno) {
      temp = i;
      break;
    }
  }
  printf("enter the number of choices you going to enter  ");
  scanf("%d", &c);
  for (int i = 0; i < c; i++) {
    printf("enter institute");
    scanf("%s", choice1[temp].ch[i].inst);
    printf("enter branch");
    scanf("%s", choice1[temp].ch[i].dept);
  }
  printf("completed");
  for (int i = c; i < 10; i++) {
    strcpy(choice1[temp].ch[i].inst, "a");
    strcpy(choice1[temp].ch[i].dept, "a");
  }
  FILE *r2;
  r2 = fopen("Student_choices.txt", "w");
  fwrite(choice1, sizeof(choice1), 1, r2);
  fclose(r2);
}

void allocation(int len) {
  struct student2 stud6[len];
  FILE *f1;
  f1 = fopen("ranklist.txt", "r");
  fread(stud6, sizeof(stud6), 1, f1);
  fclose(f1);
  struct choice studchoice1[len];

  f1 = fopen("Student_choices.txt", "r");
  fread(studchoice1, sizeof(studchoice1), 1, f1);
  fclose(f1);
  struct institution inst4[6];
  f1 = fopen("Institution_database.txt", "r");
  fread(inst4, sizeof(inst4), 1, f1);
  fclose(f1);

  struct seatdetails seat[len];
  int flag = 0;
  for (int i = 0; i < len; i++) // iterating ranklist
  {
    flag = 0;
    for (int j = 0; j < len; j++) // iterating choicelist
    {
      if (stud6[i].rollno == studchoice1[j].rollno) {
        for (int k = 0; k < 10; k++) // iterating choices (inst, dept)
        {
          for (int a = 0; a < 6; a++) // iterating institution database
          {
            if (strcmp(studchoice1[j].ch[k].inst, inst4[a].inst_name) == 0) {
              for (int b = 0; b < 5; b++) {
                if (strcmp(studchoice1[j].ch[k].dept,
                           inst4[a].dp[b].dept_name) == 0) {
                  if (inst4[a].dp[b].no_of_seats > 0) {
                    seat[i].rollno = stud6[i].rollno;
                    strcpy(seat[i].clg, inst4[a].inst_name);
                    strcpy(seat[i].branch, inst4[a].dp[b].dept_name);
                    inst4[a].dp[b].no_of_seats--;
                    // Seat allotted
                    flag = 1;
                    break;
                  }
                }
              }
            }
            if (flag == 1) {
              break; // Exit the loop once the seat is allocated
            }
          }
          if (flag == 1) {
            break; // Exit the loop once the seat is allocated
          }
        }
      }
      if (flag == 0) {
        seat[i].rollno = stud6[i].rollno;
        strcpy(seat[i].clg, "College not available");
        strcpy(seat[i].branch, " ");
      }
    }
  }

  // Assign student names to allocated seats
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
      if (seat[i].rollno == stud6[j].rollno) {
        strcpy(seat[i].name, stud6[j].name);
        break; // Exit the loop once the name is assigned
      }
    }
  }

  FILE *a1;
  a1 = fopen("seat details.txt", "w");
  fwrite(seat, sizeof(seat), 1, a1);
  fclose(a1);
  for (int i = 0; i < len; i++) {
    printf("\n%d  %s  %s  %s", seat[i].rollno, seat[i].name, seat[i].clg,
           seat[i].branch);
  }
  a1 = fopen("updated seat detials.txt", "w");
  fwrite(inst4, sizeof(inst4), 1, a1);
  fclose(a1);
}
void main() {
  printf("press 1 for admin \n press 0 for student-entering choice filling \n "
         "press 2 for student viewing the seat alloted  ");
  int n;
  scanf("%d", &n);
  if (n == 0) // student login
  {
    int a = 1;
    while (a) {
      // Declaring the variable required for the program;
      char userName[30], psd[30];

      // Declaring a pointer for the file.
      FILE *file;

      // REading the file using fopen():
      file = fopen("studentlogin.txt", "r");

      // Checking the wheather the file containing some  contents.
      if (file == NULL) {
        printf("The file not found");
      }

      else {
        // For login :
        printf("Enter the username:\n");
        scanf("%s", userName);

        printf("Enter the password:\n");
        scanf("%s", psd);
      }
      // using to get the control out of the loop:
      int flag = 0;

      char *get_name, *get_psd, combined_data[50];

      while (fscanf(file, "%s", combined_data) != EOF) {
        get_name = strtok(combined_data, ",");
        get_psd = strtok(NULL, ",");

        if (strcmp(get_name, userName) == 0 && strcmp(get_psd, psd) == 0) {
          flag = 1;
          break;
        }
      }
      fclose(file);
      if (flag == 1) {
        printf("access granted \n ");
        printf("\npress 1 for entering your choice preference\n press 2 for "
               "seeing the college and their respective seat matrix \n press 3 "
               "for viewing the sorted composite rank list\n press 4 for edit  "
               "choices   ");
        int h;
        scanf("%d", &h);
        if (h == 2) {
          printf("\nthese are the colleges and their seat details ");
          FILE *s1;
          struct institution inst2[6];
          s1 = fopen("Institution_database.txt", "r");
          fread(inst2, sizeof(inst2), 1, s1);

          for (int i = 0; i < 6; i++) {
            printf("\n %s ", inst2[i].inst_name);
            for (int j = 0; j < 5; j++) {
              printf("%s-%d  ", inst2[i].dp[j].dept_name,
                     inst2[i].dp[j].no_of_seats);
            }
          }
          fclose(s1);
        }
        if (h == 1) {
          struct choice student;
          int c;
          FILE *r1;
          r1 = fopen("Student_choices.txt", "a+");
          printf("enter your roll no");
          scanf("%d", &student.rollno);
          printf("enter the number of choices you going to enter  ");
          scanf("%d", &c);
          for (int i = 0; i < c; i++) {
            printf("enter institute");
            scanf("%s", student.ch[i].inst);
            printf("enter branch");
            scanf("%s", student.ch[i].dept);
          }
          printf("completed");
          for (int i = c; i < 10; i++) {
            strcpy(student.ch[i].inst, "a");
            strcpy(student.ch[i].dept, "a");
          }
          printf("completed");
          fwrite(&student, sizeof(student), 1, r1);
          fclose(r1);
        }
        if (h == 3) {
          FILE *f3;
          struct student2 stud8[100];
          f3 = fopen("ranklist.txt", "r");
          fread(stud8, sizeof(stud8), 1, f3);
          for (int i = 0; i < 100; i++) {
            printf("\n %d  %s ", stud8[i].rollno, stud8[i].name);
          }
          fclose(f3);
        }
        if (h == 4) {
          editchoices();
        }
        a = 0;
      } else {
        printf("access denied \n ");
      }
    }
  }
  if (n == 1) // admin login
  {
    int a = 1;
    while (a) {
      // Declaring the variable required for the program;
      char userName[30], psd[30];

      // Declaring a pointer for the file.
      FILE *file;

      // REading the file using fopen():
      file = fopen("adminlogin.txt", "r");

      // Checking the wheather the file containing some  contents.
      if (file == NULL) {
        printf("The file not found");
      }

      else {
        // For login :
        printf("Enter the username:\n");
        scanf("%s", userName);

        printf("Enter the password:\n");
        scanf("%s", psd);
      }
      // using to get the control out of the loop:
      int flag = 0;

      char *get_name, *get_psd, combined_data[50];

      while (fscanf(file, "%s", combined_data) != EOF) {
        get_name = strtok(combined_data, ",");
        get_psd = strtok(NULL, ",");

        if (strcmp(get_name, userName) == 0 && strcmp(get_psd, psd) == 0) {
          flag = 1;
          break;
        }
      }
      fclose(file);
      if (flag == 1) {

        printf("access granted \n ");

        struct student stud1[100];
        int len = 0, k = 0;
        FILE *p1;

        p1 = fopen("stu_ranklist.txt", "r");
        if (p1 == NULL) {
          printf("Error: File not found.\n");

        } else {
          int num1, rank1, rank2;
          char name2[40];

          while (fscanf(p1, "%d,%39[^,],%d,%d", &num1, name2, &rank1, &rank2) ==
                 4) {

            stud1[k].rollno = num1;
            stud1[k].mains_rank = rank1;
            stud1[k].adv_rank = rank2;
            strncpy(stud1[k].name, name2, 39);
            stud1[k].name[39] = '\0'; // Ensure null termination
            k++;
            len++;
          }
        }

        fclose(p1);
        len = len;

        // updating student details and their rank by admin.
        struct student stud2[len], stud3[len];
        struct student2 stud4[len], temp;
        char opt[5];

        int max_mains = 0, max_adv = 0;
        for (int i = 0; i < len; i++) {

          if (stud1[i].mains_rank > max_mains) {
            max_mains = stud1[i].mains_rank;
          }
          if (stud1[i].adv_rank > max_adv) {
            max_adv = stud1[i].adv_rank;
          }
        }

        for (int i = 0; i < len; i++) {
          if (stud1[i].adv_rank == 0) {
            stud1[i].adv_rank = max_adv;
          }
        }

        FILE *p2, *p3;
        // p3=fopen("Student_ranklist.txt","r");

        p2 = fopen("final_ranklist.txt", "w");
        // fread(stud3,sizeof(stud3),1,p3);
        float nor_main = 0, nor_adv = 0;
        for (int i = 0; i < len; i++) {
          stud4[i].rollno = stud1[i].rollno;
          strcpy(stud4[i].name, stud1[i].name);
          nor_main = stud1[i].mains_rank * 0.60;
          nor_adv = stud1[i].adv_rank * 0.40;
          stud4[i].rank = (nor_main + nor_adv);
        }
        fwrite(stud4, sizeof(stud4), 1, p2);
        fclose(p2);

        int swapped = 0, i, j;
        // sorting composite ranklist
        for (i = 0; i < len - 1; i++) {

          for (j = 0; j < len - i - 1; j++) {
            if (stud4[j].rank > stud4[j + 1].rank) {
              temp = stud4[j];
              stud4[j] = stud4[j + 1];
              stud4[j + 1] = temp;
            }
          }
        }
        printf(
            "\nenter 1  for update institue details \n press 2 for viewing the "
            "seat matrix of respective collges \n press 3 for viewing sorted "
            "composite ranklist \n press 4 for viewing the student choice "
            "filling \n press 5 for viewing the alloted seat details \n press "
            "6 for viewing updated seat matrix  ");
        int x;
        scanf("%d", &x);
        if (x == 3) {
          printf("this is the sorted ranklist ");
          for (int i = 0; i < len; i++) {
            printf("\n %d  %s ", stud4[i].rollno, stud4[i].name);
          }
        }
        FILE *g1;
        g1 = fopen("ranklist.txt", "w");
        fwrite(stud4, sizeof(stud4), 1, g1);
        fclose(g1);

        if (x == 1) {
          int inst_len;
          printf("enter how many institution");
          scanf("%d", &inst_len);
          struct institution inst1[inst_len];
          FILE *f1, *f2;
          f1 = fopen("Institution_database.txt", "w");
          for (int i = 0; i < inst_len; i++) {
            printf("Enter the name of the Institution: ");
            scanf("%s", inst1[i].inst_name);
            for (int j = 0; j < 5; j++) {
              printf("Enter the name of the department: ");
              scanf("%s", inst1[i].dp[j].dept_name);
              printf("Enter the total no.of seats: ");
              scanf("%d", &inst1[i].dp[j].no_of_seats);
            }
          }
          fwrite(inst1, sizeof(inst1), 1, f1);
          fclose(f1);
          for (int i = 0; i < inst_len; i++) {
            printf("\n %s ", inst1[i].inst_name);
            for (int j = 0; j < 5; j++) {
              printf("%s-%d  ", inst1[i].dp[j].dept_name,
                     inst1[i].dp[j].no_of_seats);
            }
          }
        }
        // seat allocation algorithm
        // completed-
        // ranklist
        // student choices
        // institution details
        FILE *s1;
        struct institution inst3[6];
        s1 = fopen("Institution_database.txt", "r");
        fread(inst3, sizeof(inst3), 1, s1);
        fclose(s1);
        if (x == 2) {
          for (int i = 0; i < 6; i++) {
            printf("\n %s ", inst3[i].inst_name);
            for (int j = 0; j < 5; j++) {
              printf("%s-%d  ", inst3[i].dp[j].dept_name,
                     inst3[i].dp[j].no_of_seats);
            }
          }
        }
        /*for(int i=0;i<len;i++){
              printf("\n %d  %s ",stud4[i].rollno,stud4[i].name);
            }*/
        struct choice stuchoice[len];

        s1 = fopen("Student_choices.txt", "r");
        fread(stuchoice, sizeof(stuchoice), 1, s1);
        fclose(s1);
        if (x == 4) {
          for (int i = 0; i < len; i++) {
            printf("\n\nROLL NO:%d ", stuchoice[i].rollno);
            printf("\nchoices=:");

            for (int j = 0; j < 10; j++) {
              printf(" %s-", stuchoice[i].ch[j].inst);
              printf("%s  ", stuchoice[i].ch[j].dept);
            }
          }
        }
        // calling of institute data base done-inst3(6-length)
        //  calling of length -len
        //  calling of ranklist -stud4
        //  calling  of choice -stuchoice

        if (x == 5) {

          allocation(100);
          printf("completed");
        }
        if (x == 6) {
          FILE *A1;
          struct institution inst4[6];
          A1 = fopen("updated seat detials.txt", "r");

          fread(inst4, sizeof(inst4), 1, A1);

          for (int i = 0; i < 6; i++) {
            printf("\n %s ", inst4[i].inst_name);
            for (int j = 0; j < 5; j++) {
              printf("%s-%d  ", inst4[i].dp[j].dept_name,
                     inst4[i].dp[j].no_of_seats);
            }
          }
        }
        a = 0;
      } else {
        printf("access denied \n ");
      }
    }
  }
  if (n == 2) {
    int a = 1;
    while (a) {
      // Declaring the variable required for the program;
      char userName[30], psd[30];

      // Declaring a pointer for the file.
      FILE *file;

      // REading the file using fopen():
      file = fopen("studentlogin.txt", "r");

      // Checking the wheather the file containing some  contents.
      if (file == NULL) {
        printf("The file not found");
      }

      else {
        // For login :
        printf("Enter the username:\n");
        scanf("%s", userName);

        printf("Enter the password:\n");
        scanf("%s", psd);
      }
      // using to get the control out of the loop:
      int flag = 0;

      char *get_name, *get_psd, combined_data[50];

      while (fscanf(file, "%s", combined_data) != EOF) {
        get_name = strtok(combined_data, ",");
        get_psd = strtok(NULL, ",");

        if (strcmp(get_name, userName) == 0 && strcmp(get_psd, psd) == 0) {
          flag = 1;
          break;
        }
      }
      fclose(file);
      if (flag == 1) {
        printf("access granted \n ");
        FILE *a1;
        struct seatdetails seat1[100];
        a1 = fopen("seat details.txt", "r");
        fread(seat1, sizeof(seat1), 1, a1);
        fclose(a1);
        int roll_no;
        printf("enter your roll no");
        scanf("%d", &roll_no);

        for (int i = 0; i < 100; i++) {
          if (roll_no == seat1[i].rollno) {
            printf(" \t Name: %s \t college: %s \t branch: %s", seat1[i].name,
                   seat1[i].clg, seat1[i].branch);
          }
        }
        printf("\npress 1 for viewing the updated seat matrix ");
        int x;
        scanf("%d", &x);
        FILE *A1;
        struct institution inst4[6];
        A1 = fopen("updated seat detials.txt", "r");

        fread(inst4, sizeof(inst4), 1, A1);

        if (x == 1) {
          for (int i = 0; i < 6; i++) {
            printf("\n %s ", inst4[i].inst_name);
            for (int j = 0; j < 5; j++) {
              printf("%s-%d  ", inst4[i].dp[j].dept_name,
                     inst4[i].dp[j].no_of_seats);
            }
          }
        }
        fclose(A1);
        a = 0;
      } else {
        printf("access denied \n ");
      }
    }
  }
}
