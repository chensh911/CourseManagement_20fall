//
//  teacher.h
//  CourseManagement
//
//  Created by 陈尚衡 on 2020/9/1.
//  Copyright © 2020 陈尚衡. All rights reserved.
//

#ifndef teacher_h
#define teacher_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* teacher 结构体定义 */
typedef struct teacher {
    int teacherID;          // 教师工号
    char school[100];       // 学院
    char teacherName[20];   // 教师名称
    char email[100];         // 教师邮箱
    char password[50];      // 密码
    int  courseID[100];      // 存放开设课程编号的数组
    int  courseNum;         // 已开设课程的数量
} TEACHER;

typedef struct TeacherNode *TeacherClass;
struct TeacherNode {
    TEACHER* Data;
    int TeacherNum;
    int Capacity;
};

/* teacher 结构体相关函数*/
TeacherClass CreateTeacher(int capacity);
bool IsTeacherFull(TeacherClass H);
bool IsTeacherEmpty(TeacherClass H);
bool InsertTeacher(TeacherClass H, TEACHER X );
int SearchTeacher(TeacherClass H, int TeacherID);
void DeleteTeacher(TeacherClass H, int TeacherID);

/* teacher相关操作函数*/
void teacher(void); /* 主函数*/
void TeacherSearchCourse(int teacherID);
void TeacherAddCourse(int teacherID);
void TeacherChangeStatus(int teacherID, int courseID);
void TeacherChangeCourse(int teacherID, int courseID);
void TeacherDeleteCourse(int teacherID, int courseID);
void TeacherChangeInfo(int teacherID);
void TeacherPrintCourse(int teacherID);

#endif /* teacher_h */

