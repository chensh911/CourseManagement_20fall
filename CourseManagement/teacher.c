//
//  teacher.c
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
#include <string.h>
#include <stdio.h>

extern CourseClass Course;
extern StudentClass Student;
TeacherClass Teacher;

/* 初始化*/
TeacherClass CreateTeacher(int capacity) {
    TeacherClass H = (TeacherClass)malloc(sizeof(struct TeacherNode));
    H->Data = (TEACHER *)malloc((capacity+1)*sizeof(TEACHER));
    H->TeacherNum = 0;
    H->Capacity = capacity;
    return H;
}

/* 传入老师的类，判断老师是否达到容量上限*/
bool IsTeacherFull(TeacherClass H) {
    return (H->TeacherNum == H->Capacity);
}

/* 传入老师的类，判断老师是否是空的*/
bool IsTeacherEmpty(TeacherClass H) {
    return (H->TeacherNum == 0);
}

/* 传入一个老师的结构体，将其插入老师的类中*/
bool InsertTeacher(TeacherClass H, TEACHER X) {
    if ( IsTeacherFull(H) ) {
        printf("老师已满\n");
        return false;
    }
    H->Data[H->TeacherNum] = X;
    H->TeacherNum += 1;
    return true;
}

/* 传入老师的编号，判断其是否在老师的类中。
 * 如果没找到返回-1，反之返回其下标
 */
int SearchTeacher(TeacherClass H, int TeacherID) {
    int ret;
    // 遍历搜寻
    for (ret = 0; ret < H->TeacherNum; ret += 1) {
        if (H->Data[ret].teacherID == TeacherID) {
            return ret;
        }
    }
    // 没有找到
    return -1;
}

/* 传入老师的编号，将其从老师的类中删除*/
void DeleteTeacher(TeacherClass H, int TeacherID) {
    // 判断是否为空
    if (IsTeacherEmpty(H)) {
        printf("没有任何课程，无法删除\n");
        return;
    }
    // 找到开始替换的下标
    int index = SearchTeacher(H, TeacherID);
    if (index == -1) {
        printf("没有找到相关课程，无法删除\n");
        return;
    }
    H->TeacherNum -= 1;
    // 将存放位置为最后一个的数据放到要删除的位置
    H->Data[index] = H->Data[H->TeacherNum];
}

/* teacher相关操作函数*/

/* 主函数 按照提示完成老师端的全部操作
 * 实现：输入相应数值，系统自动跳转到已经封装完成的相应模块
 * 封装模块：1.选课管理，2.课程管理，3.个人信息管理
 */
void teacher(void){
    char command[200];
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("教师端 > \n\n");
    printf("工号:");
    int TeacherID = 0;
    scanf("%s", command);
    if (IsAllDigit(command)) {
        TeacherID = atoi(command);
    } else {
        printf("错误！你输入的工号有误！\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        return;
    }
    // 判断工号是否正确
    if (SearchTeacher(Teacher, TeacherID) == -1)
    {
        printf("该工号不存在，请重新登录！\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        return;
    }
    printf("密码:");
    char password[20];
    scanf("%s", password);
    // 检验密码正确性
    if (strcmp(Teacher->Data[SearchTeacher(Teacher , TeacherID)].password, password) != 0)
    {
        printf("密码错误！请重新进入登录页面！\n");
        return;
    }
    else
    {
        printf("登录成功！\n");
    }
    // 进入教室端主菜单
    while (1) {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("教师端 > \n\n");
        printf("请输入相应字符，系统为您跳转到相应界面：\n");
        printf("1. 选课管理，2.课程管理，3.个人信息管理, 4.返回\n>>> ");
        scanf("%s", command);
        if (strcmp(command, "1") == 0) {
            while (1) {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("教师端 > 选课管理 >\n\n");
                printf("请输入相应字符，系统为您跳转到相应界面：\n");
                printf("1.查看选课情况， 2.修改选课状态， 3.统计选课信息, 4.返回，\n>>> ");
                scanf("%s", command);
                if (strcmp(command, "1") == 0) {
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    printf("教师端 > 选课管理 > 查看选课情况\n\n");
                    TeacherSearchCourse(TeacherID);
                } else if (strcmp(command, "2") == 0) {
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    printf("教师端 > 选课管理 > 修改选课状态\n\n");
                    printf("请输入要修改状态的课程编号:");
                    int courseID = 0;
                    scanf("%s", command);
                    if (IsAllDigit(command)) {
                        courseID = atoi(command);
                    } else {
                        printf("错误！你输入的课程编号有误！\n");
                        continue;
                    }
                    TeacherChangeStatus(TeacherID, courseID);
                } else if (strcmp(command, "3") == 0) {
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    printf("教师端 > 选课管理 > 统计选课信息\n\n");
                    TeacherPrintCourse(TeacherID);
                } else if (strcmp(command, "4") == 0) {
                    printf("已为您返回上一级界面\n");
                    break;
                } else {
                    printf("没有找到相应指令，请重试！\n");
                }
            }
        } else if (strcmp(command, "2") == 0) {
            while(1){
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("教师端 > 课程管理 >\n\n");
                printf("请输入相应字符，系统为您跳转到相应界面：\n");
                printf("1.课程查询， 2.添加课程， 3.修改课程, 4.删除课程, 5.返回\n>>> ");
                scanf("%s",command);
                if (strcmp(command, "1") == 0) {
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    printf("教师端 > 课程管理 > 查询课程 >\n\n");
                    printf("请输入课程名称：");
                    scanf("%s", command);
                    // 遍历搜寻教师开设的课程中是否有该课程名的课程
                    bool hasFound = false;
                    int teacherIndex = SearchTeacher(Teacher, TeacherID);
                    for (int i = 0; i < Teacher->Data[teacherIndex].courseNum; i += 1) {
                        int courseID = Teacher->Data[teacherIndex].courseID[i];
                        int courseIndex = SearchCourse(Course, courseID);
                        // 找到相应名称的课程
                        if (strcmp(command, Course->Data[courseIndex].courseName) == 0) {
                            hasFound = true;
                            CoursePrintInfo(courseID);
                            break;
                        }
                    }
                    //没找到相应名称的课程
                    if (!hasFound) {
                        printf("没有找到该老师开设过这门课程\n");
                    }
                }
                else if (strcmp(command, "2") == 0) {
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    printf("教师端 > 课程管理 > 添加课程 >\n\n");
                    TeacherAddCourse(TeacherID);
                }
                else if (strcmp(command, "3") == 0) {
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    printf("教师端 > 课程管理 > 修改课程 >\n\n");
                    int courseID = 0;
                    printf("请输入课程编号:");
                    scanf("%s", command);
                    if (IsAllDigit(command)) {
                        courseID = atoi(command);
                    } else {
                        printf("错误！你输入的课程编号有误！\n");
                        continue;
                    }
                    TeacherChangeCourse(TeacherID, courseID);
                }
                else if (strcmp(command, "4") == 0) {
                    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                    printf("教师端 > 课程管理 > 删除课程 >\n\n");
                    int courseID = 0;
                    printf("请输入课程编号:");
                    scanf("%s", command);
                    if (IsAllDigit(command)) {
                        courseID = atoi(command);
                    } else {
                        printf("错误！你输入的课程编号有误！\n");
                        continue;
                    }
                    // 判断是否为老师开设
                    int teacherIndex = SearchTeacher(Teacher, TeacherID);
                    bool hasFound = false;
                    for (int i = 0; i < Teacher->Data[teacherIndex].courseNum; i += 1) {
                        if (Teacher->Data[teacherIndex].courseID[i] == courseID) {
                            hasFound = true;
                            break;
                        }
                    }
                    if (!hasFound) {
                        printf("没有找到该老师开设过此门课程！\n");
                    }
                    else {
                        if (Course->Data[SearchCourse(Course, courseID)].status != 0) {
                            printf("开始选课或开课后不能删除课程!\n");
                            break;
                        }
                        TeacherDeleteCourse(TeacherID, courseID);
                        printf("课程删除成功！\n");
                    }
                } else if (strcmp(command, "5") == 0) {
                    printf("已为您返回上一级\n");
                    break;
                } else {
                    printf("没有找到相应指令，请重试！\n");
                }
            }
        }
        else if (strcmp(command,"3") == 0) {
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("教师端 > 个人信息管理 >\n\n");
            TeacherChangeInfo(TeacherID);
        }
        else if (strcmp(command,"4") == 0){
            return;
        }
        else {
            printf("未找到相关指令！\n");
        }
    }
}

/* 传入老师的编号，系统根据相应指令完成操作
 * 实现：输入相应数值，系统自动跳转到已经封装完成的相应模块
 * 封装模块：1.查询个人课程选课情况 2.查询学生信息 3.查询课程学生名单
 */
void TeacherSearchCourse(int teacherID) {
    printf("请输入相应指令，系统将为您自动跳转\n");
    printf("1.查询个人课程选课情况 2.查询学生信息 3.查询课程学生名单 4.返回\n>>> ");
    char command[200];
    int index = SearchTeacher(Teacher, teacherID);
    scanf("%s",command);
    // 查询个人课程选课情况
    if (strcmp(command,"1") == 0){
        int i = 0;
        // 判断教师是否有开设课程
        if(Teacher->Data[index].courseNum == 0)
        {
            printf("目前您尚未开设课程\n");
        }
        else {
            // 遍历打印课程信息
            for(i = 0 ; i < Teacher->Data[index].courseNum ; i++)
                CoursePrintInfo(Teacher->Data[index].courseID[i]);
        }
    }
    // 查询学生信息
    else if (strcmp(command,"2") == 0){
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("教师端 > 选课管理 > 查看选课情况 > 查询学生信息 >\n\n");
        printf("请输入学生姓名：");
        char name[20];
        scanf("%s",name);
        int i;
        int index = -1;
        for(i = 0 ; i < Student->StudentNum ; i += 1){
            // 打印学生信息
            if(strcmp(name,Student->Data[i].studentName) == 0){
                index = i;
                printf("---------------------------------------------------------------------\n");
                printf("姓名：%s\n",Student->Data[index].studentName);
                printf("学号：%d\n",Student->Data[index].studentID);
                printf("性别：");
                if (Student->Data[index].gender == 1) {
                    printf("男\n");
                } else {
                    printf("女\n");
                }
                printf("学院：%s\n",Student->Data[index].school);
                printf("专业：%s\n",Student->Data[index].major);
                printf("电话：%s\n",Student->Data[index].telephone);
                printf("邮箱：%s\n",Student->Data[index].mail);
                break;
            }
        }
        // 没有找到学生
        if(index == -1) {
            printf("该学生不存在！\n");
            return;
        }
        if(index != -1 )
        {
            // 查看学生的选课数
            if(Student->Data[index].courseNum == 0){
                printf("该学生无已选择课程。\n");
            }
            else
            {
                // 遍历打印学生信息
                printf("该学生已报名以下课程：\n");
                for(i = 0 ; i < Student->Data[index].courseNum ; i++)
                {
                    CoursePrintInfo(Student->Data[index].courseID[i]);
                }
            }
        }
    }
    // 查询课程学生名单
    else if (strcmp(command,"3") == 0) {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("教师端 > 选课管理 > 查看选课情况 > 查询课程学生名单 >\n\n");
        printf("请输入课程名称：");
        char courseName[40];
        int courseIndex = -1;
        int teacherindex = SearchTeacher(Teacher, teacherID);
        scanf("%s",courseName);
        bool hasFound = false;
        // 遍历老师的全部课程，查看是否有对应的额课程名称
        for (int i = 0; i < Teacher->Data[teacherindex].courseNum; i += 1) {
            courseIndex = SearchCourse(Course, Teacher->Data[teacherindex].courseID[i]);
            if (strcmp(Course->Data[courseIndex].courseName, courseName) == 0) {
                hasFound = true;
                break;
            }
        }
        // 如果没有找到
        if (!hasFound) {
            printf("该老师没有开设相应课程\n");
            return;
        }else if(Course->Data[courseIndex].studentNum != 0) {
            // 打印学生信息
            printf("---------------------------\n");
            printf("|姓名        |学号          |\n");
            printf("|-------------------------|\n");
            for(int j = 0 ; j < Course->Data[courseIndex].studentNum ; j++ ) {
                printf("|%11s   |%13d|\n",
                       Student->Data[SearchStudent(Student ,Course->Data[courseIndex].studentID[j])].studentName,
                       Course->Data[courseIndex].studentID[j]);
                printf("---------------------------\n");
            }
        } else {
            // 学生数为0的情况
            printf("该课程暂无学生选择。\n");
        }
        
    }
    else if (strcmp(command,"4") == 0){
        return;
    }
    else {
        printf("您输入的指令不合法！请重新输入。\n");
    }
}

/* 实现教师加课的交互式界面
 * 传入：课程编号
 */
void TeacherAddCourse(int teacherID) {
    char command[200];
    int TeacherIndex = SearchTeacher(Teacher, teacherID);
    // 开始加课
    COURSE newCourse;
    printf("请输入课程编号：（如果输入的长度不足六位，系统会自动为您自动补零）\n>>>");
    scanf("%s", command);
    if (IsAllDigit(command)) {
        newCourse.courseID = atoi(command);
    } else {
        printf("错误！输入不全为数字！\n");
        return;
    }
    getchar();
    // 判断编号是否符合规范
    if (newCourse.courseID < 0 || newCourse.courseID > 999999) {
        printf("加课失败！课程编号溢出！\n");
        return;
    }
    // 判断课程编号是否冲突
    if (SearchCourse(Course, newCourse.courseID) != -1) {
        printf("加课失败！课程编号冲突！\n");
        return;
    }
    int a, b, c, d;
    printf("现在开始依次输入起始时间的信息：\n格式为(****-****学年第*学期第*周)\n");
    
    printf("请输入起始年份：");
    scanf("%s", command);
    if (IsAllDigit(command) && strlen(command) == 4) {
        a = atoi(command) % 10;
    } else {
        printf("输入有误！\n");
        return;
    }
    if (atoi(command) < 2020 || atoi(command) > 2029) {
        printf("只能加2020以后2030以前的课哦\n");
        return;
    }
    printf("请输入终止年份：");
    scanf("%s", command);
    if (IsAllDigit(command) && strlen(command) == 4) {
        b = atoi(command) % 10;
    } else {
        printf("输入有误！\n");
        return;
    }
    if (atoi(command) < 2020 || atoi(command) > 2029) {
        printf("只能加2020以后2030以前的课哦\n");
        return;
    }
    if ((a + 1) != b) {
        printf("加课失败！年份不符合规范！\n");
        return;
    }
    printf("请输入学期：");
    scanf("%s", command);
    if (IsAllDigit(command) && strlen(command) == 1) {
        c = atoi(command);
    } else {
        printf("输入有误！\n");
        return;
    }
    if (c > 2 || c < 0) {
        printf("加课失败！学期不符合规范！\n");
        return;
    }
    printf("请输入周次：");
    scanf("%s", command);
    if (IsAllDigit(command) && strlen(command) <= 2) {
        d = atoi(command);
    } else {
        printf("输入有误！\n");
        return;
    }
    getchar();
    newCourse.timeStart = a * 10000 + b * 1000 + c * 100 + d;
    if (d <= 0 || d > 20) {
        printf("加课失败！周次只能在1-20里选择哦！\n");
        return;
    }
    printf("现在开始输入终止时间：\n格式为:****-****学年第*学期第*周)\n");
    printf("请输入起始年份：");
    scanf("%s", command);
    if (IsAllDigit(command) && strlen(command) == 4) {
        a = atoi(command) % 10;
    } else {
        printf("输入有误！\n");
        return;
    }
    if (atoi(command) < 2020 || atoi(command) > 2029) {
        printf("只能加2020以后2030以前的课哦\n");
        return;
    }
    printf("请输入终止年份：");
    scanf("%s", command);
    if (IsAllDigit(command) && strlen(command) == 4) {
        b = atoi(command) % 10;
    } else {
        printf("输入有误！\n");
        return;
    }
    if (atoi(command) < 2020 || atoi(command) > 2029) {
        printf("只能加2020以后2030以前的课哦\n");
        return;
    }
    if ((a + 1) != b) {
        printf("加课失败！年份不符合规范！\n");
        return;
    }
    printf("请输入学期：");
    scanf("%s", command);
    if (IsAllDigit(command) && strlen(command) == 1) {
        c = atoi(command);
    } else {
        printf("输入有误！\n");
        return;
    }
    if (c > 2 || c < 0) {
        printf("加课失败！学期不符合规范！\n");
        return;
    }
    printf("请输入周次：");
    scanf("%s", command);
    if (IsAllDigit(command) && strlen(command) <= 2) {
        d = atoi(command);
    } else {
        printf("输入有误！\n");
        return;
    }
    if (d <= 0 || d > 20) {
        printf("加课失败！周次只能在1-20里选择哦！\n");
        return;
    }
    if (d < newCourse.timeStart % 100) {
        printf("加课失败！周次不合规范！\n");
        return;
    }
    newCourse.timeEnd = a * 10000 + b * 1000 + c * 100 + d;
    if (newCourse.timeStart / 100 != newCourse.timeEnd / 100) {
        printf("加课失败！不在一个学期！\n");
        return;
    } else if (newCourse.timeStart % 100 > newCourse.timeEnd % 100) {
        printf("加课失败！周次错误！\n");
        return;
    }
    printf("请输入课程性质(0为选修, 输入其他任意键为必修)：\n>>> ");
    scanf("%s", command);
    if (IsAllDigit(command) && atoi(command) == 0) {
        newCourse.property = 0;
    } else {
        newCourse.property = 1;
    }
    // 判断是否有两门选修课
    if (newCourse.property == 0) {
        int optionNum = 0;
        for (int i = 0; i < Teacher->Data[TeacherIndex].courseNum; i += 1) {
            int courseID = Teacher->Data[TeacherIndex].courseID[i];
            int courseIndex = SearchCourse(Course, courseID);
            if (Course->Data[courseIndex].timeStart / 100 == newCourse.timeStart / 100) {
                if (Course->Data[courseIndex].property == 0) {
                    optionNum += 1;
                    if (optionNum == 2) {
                        printf("加课失败！选修课已达上限!\n");
                        return;
                    }
                }
            }
        }
    }
    printf("请输入课程名称：");
    scanf("%s", newCourse.courseName);
    // 判断课程名称是否冲突
    for (int i = 0; i < Teacher->Data[TeacherIndex].courseNum; i += 1) {
        int courseID =Teacher->Data[TeacherIndex].courseID[i];
        int courseIndex = SearchCourse(Course, courseID);
        if (strcmp(Course->Data[courseIndex].courseName, newCourse.courseName) == 0) {
            printf("加课失败！和已开设的课程名冲突！\n");
            return;
        }
    }
    printf("请输入课程为星期几(数字)：");
    scanf("%s", command);
    if (IsAllDigit(command)) {
        newCourse.day = atoi(command);
    } else {
        printf("你输入的不是数字哦\n");
        return;
    }
    if (newCourse.day > 7 || newCourse.day < 0) {
        printf("一周只能输入1-7天！！你输错了\n");
        return;
    }
    printf("请输入起始课程时间对应的节数:\n");
    printf("1-4节：8:00-11:50\n5-8节：1:30-5:20\n");
    printf("9-10节：6:30-8:20\n>>> ");
    scanf("%s", command);
    if (IsAllDigit(command)) {
        newCourse.sectionStart= atoi(command);
    } else {
        printf("你输入的不是数字哦\n");
        return;
    }
    // 判断节数输入是否符合规范
    if (newCourse.sectionStart > 10 || newCourse.sectionStart < 1) {
        printf("加课失败！输入的节数超出范围!\n");
        return;
    }
    printf("请输入课程需要持续的时间段的数量:\n");
    scanf("%s", command);
    if (IsAllDigit(command)) {
        newCourse.sectionNum = atoi(command);
    } else {
        printf("你输入的不是数字哦\n");
        return;
    }
    if (newCourse.sectionNum <= 0) {
        printf("加课失败！持续的时间应为非负数\n");
        return;
    }
    // 判断持续时间是否符合规范
    if (newCourse.sectionStart <= 4) {
        //早上的课
        if (newCourse.sectionStart + newCourse.sectionNum > 5) {
            printf("加课失败！输入的节数超出早上时间段范围\n");
            return;
        }
    } else if (newCourse.sectionStart <= 8) {
        //下午的课
        if (newCourse.sectionStart + newCourse.sectionNum > 10) {
            printf("加课失败！输入的节数超出下午时间段范围\n");
            return;
        }
    } else {
        // 晚上的课
        if (newCourse.sectionStart + newCourse.sectionNum > 11) {
            printf("加课失败！输入的节数超出晚上时间段范围\n");
            return;
        }
    }
    // 判断老师的时间是否冲突
    for (int i = 0; i < Teacher->Data[TeacherIndex].courseNum; i += 1) {
        int courseID = Teacher->Data[TeacherIndex].courseID[i];
        InsertCourse(Course, newCourse);
        if (IsSameTime(courseID, newCourse.courseID)) {
            printf("加课失败！和自己的时间冲突！\n");
            DeleteCourse(Course, newCourse.courseID);
            return;
        }
        DeleteCourse(Course, newCourse.courseID);
    }
    printf("上课地点：（格式 *-***）\n>>> ");
    scanf("%s", newCourse.place);
    //判断地点输入是否规范
    if (strlen(newCourse.place) != 5) {
        printf("加课失败！你输入的长短有问题\n");
        return;
    } else if (newCourse.place[0] - '0' > 2 || newCourse.place[0] - '0' < 0) {
        printf("加课失败!第一位只能是1或2！\n");
        return;
    } else if (newCourse.place[1] != '-') {
        printf("加课失败!第二位是‘-’！\n");
        return;
    }
    for (int i = 2; i < 5; i += 1) {
        if (newCourse.place[i] - '0' > 9 || newCourse.place[i] - '0' < 0) {
            printf("加课失败！后三位输入错误\n");
            return;
        }
    }
    // 判断所有课程教室是否冲突
    for (int i = 0; i < Course->CourseNum; i += 1) {
        InsertCourse(Course, newCourse);
        if (IsSameTime(newCourse.courseID, Course->Data[i].courseID)) {
            if (strcmp(newCourse.place, Course->Data[i].place) == 0) {
                DeleteCourse(Course, newCourse.courseID);
                printf("加课失败！和已有课程教室冲突！\n");
                return;
            }
        }
        DeleteCourse(Course, newCourse.courseID);
    }
    printf("课程人数上限：输入1代表80人，输入其他表示100人\n>>> ");
    scanf("%s", command);
    if (IsAllDigit(command) && atoi(command) == 1) {
        newCourse.limitNum = 80;
    } else {
        newCourse.limitNum = 100;
    }
    printf("学分：");
    scanf("%s", command);
    if (IsAllDigit(command)) {
        newCourse.credit = atoi(command);
    } else {
        printf("你输的不是数字哦\n");
        return;
    }
    if (newCourse.credit > 4 || newCourse.credit < 0) {
        printf("加课失败！学分要在1-4之间！\n");
        return;
    }
    printf("学时：");
    scanf("%s", command);
    if (IsAllDigit(command)) {
        newCourse.classHour = atoi(command);
    } else {
        printf("你输入的不是数据哦\n");
        return;
    }
    getchar();
    printf("课程教材：");
    scanf("%s", newCourse.textbook);
    getchar();
    printf("课程描述：");
    scanf("%s", newCourse.courseDecri);
    newCourse.status = 0;
    newCourse.teacherID = teacherID;
    newCourse.leftNum = newCourse.limitNum;
    newCourse.studentNum = 0;
    // 添加课程
    InsertCourse(Course, newCourse);
    Teacher->Data[TeacherIndex].courseID[Teacher->Data[TeacherIndex].courseNum] = newCourse.courseID;
    Teacher->Data[TeacherIndex].courseNum += 1;
    printf("万丈高楼平地起，输入这么多字你终于加课成功啦:-)\n");
}
/* 改变课程的选课状态的交互式页面
 * 传入：老师编号，学生编号
 */
void TeacherChangeStatus(int teacherID, int courseID) {
    int teacherindex = SearchTeacher(Teacher, teacherID);
    // 判断课程是否存在
    bool hasFound = false;
    for (int i = 0 ; i < Teacher->Data[teacherindex].courseNum; i++ )
    {
        if (courseID == Teacher->Data[teacherindex].courseID[i]) {
            hasFound = true;
            break;
        }
    }
    if (!hasFound) {
        printf("失败!您没有开设这门课程\n");
        return;
    }
    int index;
    index = SearchCourse(Course , courseID);
    // 修改选课状态
    printf("请输入相应数字，修改成相应选课状态\n");
    printf("0.未开始选课 1.正在选课 2.选课结束\n>>> ");
    int opt = 0;
    char command[200];
    scanf("%s",command);
    if (IsAllDigit(command)) {
        opt = atoi(command);
    } else {
        printf("您输入的指令有误！\n");
        return;
    }
    if (opt < Course->Data[index].status) {
        // 判断opt是否对过去时间进行操作
        printf("修改失败！无法溯源到过去选课状态\n");
        return;
    } else if (opt == 0){
        // 未开始选课
        Course->Data[index].status = 0;
        printf("修改成功！该课程当前选课状态为未开始选课。\n");
        return;
    }
    else if (opt == 1){
        // 选课中
        Course->Data[index].status = 1;
        printf("修改成功！该课程当前选课状态为正在选课。\n");
        return;
    }
    else if(opt == 2){
        // 结束选课，开课中
        Course->Data[index].status = 2;
        printf("修改成功！该课程当前选课状态为选课结束。\n");
        if(Course->Data[SearchCourse(Course, courseID)].studentNum < 30)
        {
            TeacherDeleteCourse(teacherID,courseID);
            printf("由于该课程处于选课结束状态并且选课人数少于30人，已为您自动删除该课程。\n");
            return;
        }
    }
    else {
        printf("输入指令不合法！\n");
        return;
    }
}

/* 教师修改课程信息的交互式页面
 * 传入： 教师编号，课程编号
 */
void TeacherChangeCourse(int teacherID, int courseID) {
    int status = Course->Data[SearchCourse(Course, courseID)].status;
    bool hasFound = false;
    int teacherIndex = SearchTeacher(Teacher, teacherID);
    // 查看课程是否存在
    for (int i = 0; i < Teacher->Data[teacherIndex].courseNum; i += 1) {
        if (Teacher->Data[teacherIndex].courseID[i] == courseID) {
            hasFound = true;
            break;
        }
    }
    if (!hasFound) {
        printf("无法修改！该老师未开设该课程\n");
        return;
    }
    // 如果未开课，可以修改课程信息
    if(status != 2){
        printf("请输入相应指令，选择修改相应信息：\n");
        printf("1.限制人数 ");
        if(status == 0 || (status == 1
                           && Course->Data[SearchCourse(Course , courseID)].studentNum == 0))
        {
            printf("2.教材信息 3.课程简介");
        }
        printf("\n");
    } else {
        // 开课后无法修改课程信息
        printf("该课程已选课完成，无法进行信息修改。\n");
        return;
    }
    printf(">>> ");
    char opt[10];
    int courseindex = SearchCourse(Course, courseID);
    scanf("%s",opt);
    if(strcmp(opt,"1") == 0) {
        // 修改限制人数
        printf("请输入新的课程限制人数,输入1代表修改为80人，输入其他数字则修改为100人\n>>> ");
        int newlimitnum;
        scanf("%s", opt);
        if (IsAllDigit(opt)) {
            newlimitnum = atoi(opt);
        } else {
            printf("你输入的指令有误！请输入数字\n");
            return;
        }
        if(newlimitnum == 1){
            if(80 > Course->Data[courseindex].studentNum)
            {
                Course->Data[courseindex].limitNum = 80;
                Course->Data[courseindex].leftNum = 80 - Course->Data[courseindex].studentNum;
                printf("修改成功！\n");
                return;
            }
            else {
                printf("课程已选人数超过新的限制人数，修改失败！\n");
                return;
            }
           } else {
            Course->Data[courseindex].limitNum = 100;
            Course->Data[courseindex].leftNum = 100 - Course->Data[courseindex].studentNum;
            printf("修改成功！\n");
        }
    } else if (status == 0 || (status == 1 &&
                               Course->Data[courseindex].studentNum == 0)) {
        if(strcmp(opt,"2") == 0)
        {
            // 修改教材信息
            printf("请输入新的教材信息：");
            scanf("%s",Course->Data[courseindex].textbook);
            printf("修改成功！\n");
            return;
        }
        else if(strcmp(opt,"3") == 0)
        {
            // 修改课程简介
            printf("请输入新的课程简介信息：");
            scanf("%s",Course->Data[courseindex].courseDecri);
            printf("修改成功！\n");
            return;
        }
        else {
            printf("指令错误！\n");
            return;
        }
    } else {
        printf("指令错误！\n");
        return;
    }
    
}

/* 实现教师删课的函数
 * 传入：教师编号，要删除的课程编号
 */
void TeacherDeleteCourse(int teacherID, int courseID) {
    int courseindex;
    int teacherindex;
    courseindex = SearchCourse(Course,courseID);
    // 删除老师相关课程信息
    teacherindex = SearchTeacher(Teacher,teacherID);
    int formerCourseNumT = Teacher->Data[teacherindex].courseNum;
    for(int i=0 ; i < formerCourseNumT ; i++)
    {
        if (Teacher->Data[teacherindex].courseID[i] == courseID)
        {
            Teacher->Data[teacherindex].courseID[i] =
            Teacher->Data[teacherindex].courseID[formerCourseNumT-1];
            Teacher->Data[teacherindex].courseNum -= 1;
        }
    }
    DeleteCourse(Course, courseID);
}

/* 老师修改课程信息的交互式页面
 * 传入：老师编号
 */
void TeacherChangeInfo(int teacherID) {
    while(1) {
        int index = SearchTeacher(Teacher , teacherID);
        printf("请输入相应字符，系统将自动跳转\n");
        printf("1.密码修改 2.邮箱修改 3. 返回\n>>> ");
        char command[200];
        scanf("%s", command);
        if(strcmp(command,"1") == 0){
            // 修改密码
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("教师端 > 个人信息管理 > 密码修改 >\n\n");
            char password_1[20];
            char password_2[20];
            printf("请输入密码\n>>> ");
            scanf("%s",password_1);
            if (strlen(password_1) < 6) {
                printf("密码至少为六位！\n");
            }else{
                printf("请再次确认输入的密码：\n>>> ");
                     scanf("%s",password_2);
                     // 判断两次密码是否相同
                     if(strcmp(password_1,password_2)){
                         printf("两次输入的密码不一致，修改失败!\n");
                     }
                     else {
                         strcpy(Teacher->Data[index].password,password_1);
                         printf("修改成功！\n");
                         return;
                     }
            }
        } else if(strcmp(command,"2") == 0){
            // 修改邮箱
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("教师端 > 统计选课信息 > 邮箱修改 >\n\n");
            printf("请输入修改后的邮箱地址：");
            char mail_1[50];
            scanf("%s",mail_1);
            // 判断邮箱是否符合规范
            if (IsEmailValid(mail_1)) {
                strcpy(Teacher->Data[index].email,mail_1);
                printf("修改成功！\n");
                printf("修改后的邮箱是%s\n",Teacher->Data[index].email);
                return;
            } else {
                printf("邮箱格式不合法，请重新输入！\n");
            }
        } else if (strcmp(command,"3") == 0){
            return;
        } else {
             printf("输入指令不合法！\n");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                       printf("教师端 > 个人信息管理 >\n\n");
        }
    }
}

/* 打印出老师所开设的全部课程
 * 传入：老师编号
 */
void TeacherPrintCourse(int teacherID){
    int techerIndex = SearchTeacher(Teacher, teacherID);
    printf("您共开设%d门课程\n", Teacher->Data[techerIndex].courseNum);
    //统计学生人数信息并排序
    int index[Teacher->Data[techerIndex].courseNum];
    int chosenNum[Teacher->Data[techerIndex].courseNum];
    for (int i = 0; i < Teacher->Data[techerIndex].courseNum; i += 1) {
        index[i] = Teacher->Data[techerIndex].courseID[i];
        int courseIndex = SearchCourse(Course, Teacher->Data[techerIndex].courseID[i]);
        chosenNum[i] = Course->Data[courseIndex].studentNum;
    }
    Sort(index, chosenNum, Teacher->Data[techerIndex].courseNum);
    // 打印学生信息
    for (int i = 0; i < Teacher->Data[techerIndex].courseNum; i += 1) {
        CoursePrintInfo(index[i]);
    }
}
