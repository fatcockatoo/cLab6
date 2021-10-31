#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

const int itrSem = 8, itrStr = 5; //количество семестров/строк

struct date 
{
    int day;
    int month;
    int year;
};

struct info 
{
    char discipline[50];
    char typeRating[5];
    union grade {
        bool testGrade;
        enum
        {
            Failing = 2,
            Fair = 3,
            Good = 4,
            Excellent = 5
        }gradeNum;
    };
    struct date exTestDate;
    char teacherLastName[30];
};

struct semester
{
    int numSem, yearS;
    struct info infDisc[5];
};

struct certificate
{
    char lastName[30], firstName[30], patronymic[30];
    int certifNum;
    struct semester sem[13];
};

void gradeExamFunc(int *t)
{
    int gradeExam;
    printf("Grade? (from 2 to 5) ");
    scanf("%d", &gradeExam);
    switch (gradeExam)
    {
    case(Excellent):
        *t = Excellent;
        break;
    case(Good):
        *t = Good;
        break;
    case(Fair):
        *t = Fair;
        break;
    case(Failing):
        *t = Failing;
        break;
    default: {
        printf("i will be think it was a ''fair'' (read the tips next time, please!) \n");
        *t = Fair;
        break;
    }
    }
}

void gradeTestFunc(bool* t)
{
    int gradeTest;
    printf("Grade? (1 is got test, 0 isnt) ");
    scanf("%d", &gradeTest);
    if (gradeTest == 0)
        *t = false;
    else *t = true;
}

void printall(struct certificate c, bool r, bool f)
{
    printf("Name: %s %s %s \n", c.lastName, c.firstName, c.patronymic);
    printf("Number of certificate: %d \n", c.certifNum);
    for (int i = 0; i < itrSem; i++) {
        printf("\n \nIn %d semester %d year result is:\n", c.sem[i].numSem, c.sem[i].yearS);
        for (int j = 0; j <= itrStr; j++) {
            if (r)
                printf("%s \t%s \t%d \t", c.sem[i].infDisc[j].discipline, c.sem[i].infDisc[j].typeRating, c.sem[i].infDisc[j].gradeNum);
            else if (f)
                printf("%s \t%s \t%d \t", c.sem[i].infDisc[j].discipline, c.sem[i].infDisc[j].typeRating, c.sem[i].infDisc[j].testGrade);
            else
            printf("%s \t%s \t%d \t", c.sem[i].infDisc[j].discipline, c.sem[i].infDisc[j].typeRating, c.sem[i].infDisc[j].gradeNum);
            printf("%d.%d.%d \t%s\n", c.sem[i].infDisc[j].exTestDate.day, c.sem[i].infDisc[j].exTestDate.month, c.sem[i].infDisc[j].exTestDate.year, c.sem[i].infDisc[j].teacherLastName);
        }
    }
}

void main()
{
    int gradeTest; bool r = 0,f = 0;
    struct certificate cer;
    printf("Name? ");
    scanf("%s", cer.firstName);
    printf("Last name? ");
    scanf("%s", cer.lastName);
    printf("Patronymic? ");
    scanf("%s", cer.patronymic);
    printf("Number of certificate? ");
    scanf("%d", &cer.certifNum);
    for (int i = 0; i < itrSem; i++) {
        cer.sem[i].numSem = i + 1;
        cer.sem[i].yearS = (i + 2) / 2;
        printf("\n \nNumber of semester is %d, number of year is %d \n", cer.sem[i].numSem, cer.sem[i].yearS);
        for (int j = 0; j <= itrStr; j++){
            printf("Discipline name? ");
            scanf("%s", cer.sem[i].infDisc[j].discipline);
            printf("Exam or test? ");
            scanf("%s", cer.sem[i].infDisc[j].typeRating);
            char q1[5] = "Exam", q2[5] = "exam", q3[5] = "Test", q4[5] = "test";
            if (!strcmp(cer.sem[i].infDisc[j].typeRating, q1) || !strcmp(cer.sem[i].infDisc[j].typeRating, q2)) {
                gradeExamFunc(&cer.sem[i].infDisc[j].gradeNum); r = 1;
            }
            else if (!strcmp(cer.sem[i].infDisc[j].typeRating, q3) || !strcmp(cer.sem[i].infDisc[j].typeRating, q4)) {
                gradeTestFunc(&cer.sem[i].infDisc[j].testGrade); f = 1;
            }
            else {
                printf(" i will be think it was an exam (read the tips next time, please!) \n");
                gradeExamFunc(&cer.sem[i].infDisc[j].gradeNum); r = 1;
            }
            printf("Day of exam? ");
            scanf("%d", &cer.sem[i].infDisc[j].exTestDate.day);
            printf("Month of exam? ");
            scanf("%d", &cer.sem[i].infDisc[j].exTestDate.month);
            printf("Year of exam? ");
            scanf("%d", &cer.sem[i].infDisc[j].exTestDate.year);
            printf("Teacher`s last name? ");
            scanf("%s", &cer.sem[i].infDisc[j].teacherLastName);
        }
    }
    system("cls");
    printall(cer,r,f);
}