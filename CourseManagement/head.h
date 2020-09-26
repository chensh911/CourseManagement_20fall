//
//  head.h
//  CourseManagement
//
//  Created by 陈尚衡 on 2020/9/2.
//  Copyright © 2020 陈尚衡. All rights reserved.
//

#ifndef head_h
#define head_h

#include <stdio.h>
#include <stdbool.h>
#include "course.h"
#include "student.h"
#include "teacher.h"

extern CourseClass Course;
extern StudentClass Student;
extern TeacherClass Teacher;

/* 加载数据使用的函数*/
void load(void);/* 主函数*/
void LoadTeacher(void);
void LoadStudent(void);
void LoadCourse(void);

/* 存储数据使用的函数*/
void save(void);/* 主函数*/
void SaveTeacher(void);
void SaveStudent(void);
void SaveCourse(void);

/* 辅助函数*/
void Sort(int index[], int compare[], int len);
bool IsEmailValid(char EmailAddress[]);
bool IsAllDigit(char* s);

#endif /* head_h */
