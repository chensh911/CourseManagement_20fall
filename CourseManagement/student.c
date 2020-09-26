//
//  student.c
//  CourseManagement
//
//  Created by 陈尚衡 on 2020/9/1.
//  Copyright © 2020 陈尚衡. All rights reserved.
//

#include "course.h"
#include "student.h"
#include "teacher.h"
#include "head.h"
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>

extern CourseClass Course;
StudentClass Student;
extern TeacherClass Teacher;

/* 输入一个容量，创建一个学生的类*/
StudentClass CreateStudent(int capacity) {
    StudentClass H = (StudentClass)malloc(sizeof(struct StudentNode));
    H->Data = (STUDENT *)malloc((capacity+1)*sizeof(STUDENT));
    H->StudentNum = 0;
    H->Capacity = capacity;
    return H;
}

/* 传入学生的类，判断学生是否达到容量上限*/
bool IsStudentFull(StudentClass H) {
    return (H->StudentNum == H->Capacity);
}
/* 传入学生的类，判断学生是否是空的*/
bool IsStudentEmpty(StudentClass H ) {
    return (H->StudentNum == 0);
}
/* 传入一个学生的结构体，将其插入学生的类中*/
bool InsertStudent(StudentClass H, STUDENT X) {
    if ( IsStudentFull(H) ) {
        printf("学生已满\n");
        return false;
    }
    H->Data[H->StudentNum] = X;
    H->StudentNum += 1;
    return true;
}
/* 传入学生的编号，判断其是否在学生的类中。
 * 如果没找到返回-1，反之返回其下标
 */
int SearchStudent(StudentClass H, int StudentID) {
    int ret;
    for (ret = 0; ret < H->StudentNum; ret += 1) {
        if (H->Data[ret].studentID == StudentID) {
            return ret;
        }
    }
    return -1;
}
/* 传入学生的编号，将其从学生的类中删除*/
void DeleteStudent(StudentClass H, int StudentID) {
    if (IsStudentEmpty(H)) {
        printf("没有任何学生，无法删除\n");
        return;
    }
    int index = SearchStudent(H, StudentID);
    if (index == -1) {
        printf("没有找到相关学生，无法删除\n");
        return;
    }
    H->StudentNum -= 1;
    H->Data[index] = H->Data[H->StudentNum];
}

/* student相关操作函数 */

/* 主函数 按照提示完成学生端的全部操作
* 实现：输入相应数值，系统自动跳转到已经封装完成的相应模块
* 封装模块：1.学生选课 2.查询课程 3.查询选课结果 4.删除选课结果 5.修改个人信息
*/
void student(void) {
    int studentID = 0;
    char password[20];
    char command[200];
    printf("学号：");
    scanf("%s", command);
    if (IsAllDigit(command)) {
        studentID = atoi(command);
    } else {
        printf("错误！你输入的学号有误！\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        return;
    }
    // 判断学生是否存在
    int studentIndex = SearchStudent(Student, studentID);
    if (studentIndex == -1) {
        printf("学号不存在！请重新登录！\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        return;
    }
    printf("密码：");
    scanf("%s", password);
    // 判断密码是否正确
    if (strcmp(Student->Data[studentIndex].password, password) != 0) {
        printf("密码错误！请重新登录\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        return;
    }
    printf("登录成功！\n");
    // 进入学生端主菜单
    while (1) {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("学生端 >\n\n");
        printf("请输入相应字符，系统为您跳转到相应界面：\n");
        printf("1.学生选课 2.查询课程 3.查询选课结果 4.删除选课结果 5.修改个人信息 6.返回\n>>> ");
        char command[200];
        scanf("%s", command);
        if (strcmp(command, "1") == 0) {
            // 学生选课
            int courseID = 0;
            printf("请输入要加的课程编号:");
            scanf("%s", command);
            if (IsAllDigit(command)) {
                courseID = atoi(command);
            } else {
                printf("错误！你输入的课程编号有误！\n");
                continue;
            }
            StudentAddCourse(studentID,courseID);
        } else if (strcmp(command, "2") == 0) {
            // 查询课程
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("学生端 > 查询课程 >\n\n");
            printf("请输入相应字符，系统为您跳转到相应界面：\n");
            printf("1.按课程名查询 2.按学院查询 3.按课余量查询 4.按选课人数查询\n>>> ");
            scanf("%s", command);
            if (strcmp(command, "1") == 0) {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("学生端 > 查询课程 > 按课程名查询 >\n\n");
                printf("请输入课程名称：");
                scanf("%s", command);
                CourseByName(command);
            } else if (strcmp(command, "2") == 0) {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("学生端 > 查询课程 > 按学院查询 >\n\n");
                printf("请输入学院名称:");
                scanf("%s", command);
                CourseBySchool(command);
            } else if (strcmp(command, "3") == 0) {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("学生端 > 查询课程 > 按课余量查询 >\n\n");
                CourseByLeft();
            } else if (strcmp(command, "4") == 0) {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("学生端 > 查询课程 > 按选课人数查询 >\n\n");
                CourseByChosen();
            } else{
                printf("指令错误！请重新输入！\n");
            }
        } else if (strcmp(command, "3") == 0) {
            // 查询选课结果
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("学生端 > 查询课程 > 查询选课结果 >\n\n");
            printf("您本学期共修%d门课，以下是详细信息:\n", Student->Data[studentIndex].courseNum);
            StudentSearchCourse(studentID);
        } else if (strcmp(command, "4") == 0) {
            // 删除选课结果
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("学生端 > 删除选课结果 >\n\n");
            int courseID;
            printf("请输入要删除的课程ID:");
            scanf("%s", command);
            if (IsAllDigit(command)) {
                courseID = atoi(command);
            } else {
                printf("错误！你输入的课程编号有误！\n");
                continue;
            }
            StudentDeleteCourse( studentID,  courseID);
        } else if (strcmp(command, "5") == 0) {
            // 修改个人信息
          //
            StudentChangeInfo(studentID);
        } else if (strcmp(command, "6") == 0) {
            return;
        } else {
            printf("指令未找到\n");
        }
        
    }
}


/* 实现学生加课的函数
 * 传入：学生编号，课程编号
 */
void StudentAddCourse(int studenID, int courseID) {
    int StudentIndex = SearchStudent(Student, studenID);
    int CourseIndex = SearchCourse(Course, courseID);
    /* 判断该课程是否存在*/
    int courseIndex = SearchCourse(Course, courseID);
    if (courseIndex == -1) {
        printf("加课失败！该门课程不存在！\n");
        return;
    }
    if (courseID < 100000) {
        printf("不足六位系统默认已经自动在左侧补0\n");
    }
    /* 判断是否已经添加该门课程*/
    for (int i = 0; i < Student->Data[StudentIndex].courseNum; i += 1) {
        if (courseID == Student->Data[StudentIndex].courseID[i]) {
            printf("加课失败！该门课程已经被您添加！\n");
            return;
        }
    }
    if (Course->Data[CourseIndex].status != 1) {
        printf("加课失败！该门课程不在选课状态！\n");
        return;
    } else if (Student->Data[StudentIndex].courseNum == 3) {
        printf("加课失败！可选课程已满！\n");
        return;
    } else if (Course->Data[CourseIndex].leftNum == 0) {
        printf("加课失败！选课人数已达上限！\n");
        return;
    } else {
        for (int i = 0; i < Student->Data[StudentIndex].courseNum; i += 1) {
            if (IsSameTime(courseID, Student->Data[StudentIndex].courseID[i])) {
                printf("加课失败！和已选课程时间冲突！\n");
                return;
            }
        }
    }
    printf("学生加课成功！\n");
    //对学生来说
    Student->Data[StudentIndex].courseID[Student->Data[StudentIndex].courseNum] = courseID;
    Student->Data[StudentIndex].courseNum += 1;
    //对课程来说
    Course->Data[CourseIndex].leftNum -= 1;
    Course->Data[CourseIndex].studentID[Course->Data[CourseIndex].studentNum] = studenID;
    Course->Data[CourseIndex].studentNum += 1;
}

/* 学生查询选课结果
 * 传入：学生的编号
 */
void StudentSearchCourse(int studentID) {
    int studentIndex = SearchStudent(Student, studentID);
    if (Student->Data[studentIndex].courseNum == 0) {
        printf("现在没有选过任何一门课程\n");
        return;
    }
    for(int i = 0 ; i < Student->Data[studentIndex].courseNum ; i++)
    {
        CoursePrintInfo( Student->Data[studentIndex].courseID[i] );
    }
}

/* 删除选课结果
 * 传入学生的编号，课程的编号
 */
void StudentDeleteCourse(int studentID, int courseID) {
    int studentindex = SearchStudent(Student, studentID);
    int courseindex  = SearchCourse(Course, courseID);
    if (courseindex == -1) {
        printf("未找到该课程，请重新输入\n");
        return;
    }
    // 遍历一边学生加的全部课
    if(Course->Data[courseindex].status == 1)
    {
        for(int i = 0 ; i < Student->Data[studentindex].courseNum ; i++ )
        {
            if( Student->Data[studentindex].courseID[i] == courseID)
            {
                // 删课方式：将数组的最后一个课程编号赋值给要删除的下标位置
                Student->Data[studentindex].courseID[i] =
                Student->Data[studentindex].courseID[Student->Data[studentindex].courseNum-1];
                Student->Data[studentindex].courseNum -= 1;
                Course->Data[courseindex].leftNum += 1;
                Course->Data[courseindex].studentID[studentindex] = Course->Data[courseindex].studentID[Course->Data[courseindex].studentNum-1];
                Course->Data[courseindex].studentNum -= 1;
                printf("课程已删除\n");
                return;
            }
        }
        printf("没有找到学生加过这门课程\n");
        
    } else {
        printf("该课程不能被删除\n");
    }
}

/* 修改个人信息的交互式界面
 * 传入：学生编号
 */
void StudentChangeInfo(int studentID) {
    int studentIndex = SearchStudent(Student, studentID);
    char command[200];
    while (1) {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("学生端 > 个人信息修改\n\n");
        printf("请输入相应指令，系统将自动为您跳转\n");
        printf("1.密码修改 2.邮箱修改 3.电话修改 4.返回\n>>> ");
        scanf("%s", command);
        if (strcmp("1", command) == 0) {
            // 密码修改
            char password_1[20];
            char password_2[20];
            printf("请输入新密码:");
            scanf("%s", password_1);
            if (strlen(password_1) < 6) {
                printf("密码至少为六位！\n");
            } else {
                printf("请再次确认新密码:");
                scanf("%s", password_2);
                if (strcmp(password_1, password_2) == 0) {
                    printf("修改成功!\n");
                    strcpy(Student->Data[studentIndex].password, password_1);
                    break;
                } else {
                    printf("错误!两次输入不一致，请重新进入修改页面\n");
                }
            }
        } else if (strcmp("2", command) == 0) {
            // 邮箱修改
            char email[20];
            printf("请输入修改的邮箱:");
            scanf("%s", email);
            if (IsEmailValid(email)) {
                strcpy(Student->Data[studentIndex].mail, email);
                printf("修改成功!\n");
                break;
            } else {
                printf("错误!邮箱不符合要求！如需更改请重新进入修改界面\n");
            }
        } else if (strcmp("3", command) == 0) {
            // 电话修改
            char telephone[20];
            printf("请输入新的电话号码：");
            scanf("%s", telephone);
            if (strlen(telephone) != 11) {
                printf("错误!位数不是11位!如需更改请重新进入修改界面\n");
            }else if (!IsAllDigit(telephone)){
                printf("错误!您输入了非法字符!请输入数字！如需更改请重新进入修改界面\n");
            }else {
                strcpy(Student->Data[studentIndex].telephone, telephone);
                printf("修改成功!\n");
                break;
            }
        } else if (strcmp("4", command) == 0){
            break;
        } else {
            printf("未找到指令，请重新输入!\n");
        }
    }
}
