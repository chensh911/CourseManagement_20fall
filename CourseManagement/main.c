//
//  main.c
//  CourseManagement
//
//  Created by 陈尚衡 on 2020/9/1.
//  Copyright © 2020 陈尚衡. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "course.h"
#include "student.h"
#include "teacher.h"
#include "head.h"

extern CourseClass Course;
extern StudentClass Student;
extern TeacherClass Teacher;

int main(int argc, const char * argv[]) {
// 初始化
    Course = CreateCourse(100);
    Student = CreateStudent(200);
    Teacher = CreateTeacher(100);
// 载入数据
    load();
// 欢迎界面
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("                          学生选课管理系统\n");
    printf("=====================================================================\n\n");
    char command[200];
    while (1) {
        printf("请输入相应字符，系统为您跳转到相应界面：\n");
        printf("1: 学生端， 2:教师端， 3:退出\n>>> ");
        scanf("%s", command);
        // 进入相应界面
        if (strcmp("1", command) == 0) {
            student();
        } else if (strcmp("2", command) == 0) {
            teacher();
        } else if (strcmp("3", command) == 0) {
            break;
        } else {
            printf("未找到指令，请重新输入！\n");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        }
    }
    printf("感谢使用本系统\n");
// 导出数据
    save();
    return 0;
}
