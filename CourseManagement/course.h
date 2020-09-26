//
//  course.h
//  CourseManagement
//
//  Created by 陈尚衡 on 2020/9/1.
//  Copyright © 2020 陈尚衡. All rights reserved.
//

#ifndef course_h
#define course_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* course 结构体定义 */
typedef struct course {
    int status;             // 选课状态
    int courseID;           // 课程编号
    int teacherID;          // 教师编号
    int credit;             // 学分
    int classHour;          // 学时
    int property;           // 选修0，必修1
    int day;                // 星期几
    int limitNum;           // 课程限制人数
    int leftNum;            // 课程剩余人数
    int sectionStart;       // 起始时间端
    int sectionNum;         // 课程节数
    int timeStart;          // 202*-202*学年第*学期第**周
    int timeEnd;            // 202*-202*学年第*学期第**周
    int studentNum;         // 已选课的学生人数
    int studentID[100];     // 储存所有选课的学生编号的数组
    char place[6];          // 上课地点
    char courseName[50];    // 课程名称
    char textbook[200];     // 教材信息
    char courseDecri[200];  // 课程描述
} COURSE;

typedef struct CourseNode *CourseClass;
struct CourseNode {
    COURSE* Data;
    int CourseNum;
    int Capacity;
};

/* course 结构体相关函数 */
CourseClass CreateCourse(int capacity);
bool IsCourseFull(CourseClass H);
bool IsCourseEmpty(CourseClass H);
bool InsertCourse(CourseClass H, COURSE X);
int SearchCourse(CourseClass H, int CourseID);
void DeleteCourse(CourseClass H, int CourseID);

/* Course相关操作函数 */
void CoursePrintInfo(int courseID);
void CourseByName(char courseName[]);
void CourseBySchool(char schoolName[]);
void CourseByLeft(void);
void CourseByChosen(void);
void CoursePrintTime(int time);
void PrintTime(int sectionTime, int timeNum);
bool IsBetween(int timeStart, int timeEnd, int start, int end);
bool IsSameTime(int courseID1, int courseID2);
#endif /* course_h */
