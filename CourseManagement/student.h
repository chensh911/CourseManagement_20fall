//
//  student.h
//  CourseManagement
//
//  Created by 陈尚衡 on 2020/9/1.
//  Copyright © 2020 陈尚衡. All rights reserved.
//

#ifndef student_h
#define student_h

#include <stdio.h>


/* student 结构体定义*/
typedef struct student {
    char studentName[20];
    char school[100];
    char major[50];
    char password[50];
    char telephone[50];
    char mail[30];
    int gender;
    int studentID;
    int courseID[3];
    int courseNum;
} STUDENT;

typedef struct StudentNode *StudentClass;
struct StudentNode {
    STUDENT* Data;
    int StudentNum;
    int Capacity;
};
/* student 结构体相关函数*/
StudentClass CreateStudent(int capacity);
bool IsStudentFull(StudentClass H);
bool IsStudentEmpty(StudentClass H);
bool InsertStudent(StudentClass H, STUDENT X);
int SearchStudent(StudentClass H, int StudentID);
void DeleteStudent(StudentClass H, int StudentID);

/* student相关操作函数*/
void student(void); /* 主函数*/
void StudentAddCourse(int studenID, int courseID);
void StudentSearchCourse(int studentID);
void StudentDeleteCourse(int studentID, int courseID);
void StudentChangeInfo(int studentID);

#endif /* student_h */
