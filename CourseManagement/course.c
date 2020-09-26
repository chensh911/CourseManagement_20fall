//
//  course.c
//  CourseManagement
//
//  Created by 陈尚衡 on 2020/9/1.
//  Copyright © 2020 陈尚衡. All rights reserved.
//

#include "course.h"
#include "student.h"
#include "teacher.h"
#include "head.h"
#include <string.h>

CourseClass Course;
extern StudentClass Student;
extern TeacherClass Teacher;

/* 初始化*/
CourseClass CreateCourse(int capacity) {
    CourseClass H = (CourseClass)malloc(sizeof(struct CourseNode));
    H->Data = (COURSE *)malloc((capacity+1)*sizeof(COURSE));
    H->CourseNum = 0;
    H->Capacity = capacity;
    return H;
}

/* 传入课程的类，判断课程是否达到容量上限*/
bool IsCourseFull(CourseClass H ) {
    return (H->CourseNum == H->Capacity);
}
/* 传入课程的类，判断课程是否是空的*/
bool IsCourseEmpty(CourseClass H ) {
    return (H->CourseNum == 0);
}
/* 传入一个课程的结构体，将其插入课程的类中*/
bool InsertCourse(CourseClass H, COURSE X ) {
    if ( IsCourseFull(H) ) {
        printf("课程已满\n");
        return false;
    }
    H->Data[H->CourseNum] = X;
    H->CourseNum += 1;
    return true;
}
/* 传入课程的编号，判断其是否在课程的类中。
 * 如果没找到返回-1，反之返回其下标
 */
int SearchCourse(CourseClass H, int CourseID) {
    int ret;
    for (ret = 0; ret < H->CourseNum; ret += 1) {
        if (H->Data[ret].courseID == CourseID) {
            return ret;
        }
    }
    return -1;
}
/* 传入课程的编号，将其从课程的类中删除*/
void DeleteCourse(CourseClass H, int CourseID) {
    if (IsCourseEmpty(H)) {
        printf("没有任何课程，无法删除\n");
        return;
    }
    int index = SearchCourse(H, CourseID);
    if (index == -1) {
        printf("没有找到相关课程，无法删除\n");
        return;
    }
    H->CourseNum -= 1;
    H->Data[index] = H->Data[H->CourseNum];
}

/* Course相关操作函数 */

/* 给出课程编号， 打印出相应课程*/
void CoursePrintInfo(int courseID) {
    int courseIndex = SearchCourse(Course, courseID);
    // 课程不存在
    if (courseIndex == -1) {
        printf("没有找到相应课程,请稍后重试\n");
        return;
    }
    int teacherIndex = SearchTeacher(Teacher, Course->Data[courseIndex].teacherID);
    printf("---------------------------------------------------------------------\n");
    printf("|课程名称|%-25s", Course->Data[courseIndex].courseName);
    printf("|课程编号|%06d\n", Course->Data[courseIndex].courseID);
    printf("|学分|%-28d|学时|%-7d\n", Course->Data[courseIndex].credit,
           Course->Data[courseIndex].classHour);
    printf("|开课教师|%-25s", Teacher->Data[teacherIndex].teacherName);
    printf("  |课程性质|");
    if (Course->Data[courseIndex].property == 0) {
        printf("选修\n");
    } else {
        printf("必修\n");
    }
    printf("|课程时间|星期%d", Course->Data[courseIndex].day);
    PrintTime(Course->Data[courseIndex].sectionStart, Course->Data[courseIndex].sectionNum);
    printf("\n        起始：");
    CoursePrintTime(Course->Data[courseIndex].timeStart);
    printf("        结束：");
    CoursePrintTime(Course->Data[courseIndex].timeEnd);
    printf("|上课地点|%-20s\n", Course->Data[courseIndex].place);
    printf("|课程教材|%-20s\n", Course->Data[courseIndex].textbook);
    printf("|课程描述|%-20s\n",Course->Data[courseIndex].courseDecri);
    printf("|最多人数|%-25d|剩余人数|%-25d\n",Course->Data[courseIndex].limitNum,
           Course->Data[courseIndex].leftNum);
    printf("|课程状态|");
    if (Course->Data[courseIndex].status == 0) {
        printf("未开始选课\n");
    } else if (Course->Data[courseIndex].status == 1) {
        printf("选课中\n");
    } else {
        printf("已开课\n");
    }
    printf("---------------------------------------------------------------------\n");
}

/* 给出课程名称， 打印出课程信息*/
void CourseByName(char courseName[]) {
    for (int i = 0; i < Course->CourseNum; i += 1) {
        if (strcmp(courseName, Course->Data[i].courseName) == 0) {
            CoursePrintInfo(Course->Data[i].courseID);
            return;
        }
    }
    printf("没有找到课程信息，请检查后重试\n");
}
/* 给出学院， 打印出课程信息*/
void CourseBySchool(char schoolName[]) {
    bool hasFound = false;
    for (int i = 0; i < Course->CourseNum; i += 1) {
        int teacherIndex = SearchTeacher(Teacher, Course->Data[i].teacherID);
        // 是否找到学院
        if (strcmp(schoolName, Teacher->Data[teacherIndex].school) == 0) {
            if (!hasFound) {
                hasFound = true;
                printf("--------------------------------------------------------------------\n");
                printf("|    课程名称   |    课程编号  |   教师名称  |剩余课量|已选人数|选课状态\n");
                printf("--------------------------------------------------------------------\n");
            }
            printf("|%-13s|%06d       |%11s  |%8d|%7d|",
                   Course->Data[i].courseName,
                   Course->Data[i].courseID,
                   Teacher->Data[teacherIndex].teacherName,
                   Course->Data[i].leftNum,Course->Data[i].studentNum);
            if (Course->Data[i].status == 0) {
                printf("未选课｜\n");
            } else if (Course->Data[i].status == 1) {
                printf("选课中｜\n");
            } else {
                printf("已开课｜\n");
            }
        }
    }
    // 没有找到学院
    if (!hasFound) {
        printf("没有找到课程信息，请检查后重试\n");
    }
}

/* 根据剩余课量进行排序*/
void CourseByLeft(void) {
    // 判断课程总数是否为0
    if (Course->CourseNum == 0) {
        printf("还没有任何课程\n");
        return;
    }
    // index存储排序结果的下标，left存储对应的剩余课量
    int index[Course->CourseNum], left[Course->CourseNum];
    for (int i = 0; i < Course->CourseNum; i += 1) {
        left[i] = Course->Data[i].leftNum;
        index[i] = i;
    }
    // 排序
    Sort(index, left, Course->CourseNum);
    // 打印
    printf("--------------------------------------------------------------------\n");
    printf("|  课程名称   |   课程编号  |  教师名称 |剩余课量|已选人数|选课状态\n");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < Course->CourseNum; i += 1) {
        int teacherIndex = SearchTeacher(Teacher, Course->Data[index[i]].teacherID);
         printf("|%-13s|%06d       |%11s  |%8d|%7d|",
                          Course->Data[index[i]].courseName,
                          Course->Data[index[i]].courseID,
                          Teacher->Data[teacherIndex].teacherName,
                          Course->Data[index[i]].leftNum,Course->Data[index[i]].studentNum);
                   if (Course->Data[index[i]].status == 0) {
                       printf("未选课｜\n");
                   } else if (Course->Data[index[i]].status == 1) {
                       printf("选课中｜\n");
                   } else {
                       printf("已开课｜\n");
                   }
        printf("---------------------------------------------------------------------\n");
    }
}

/* 根据选课数量进行排序*/
void CourseByChosen(void) {
    // 判断课程总数是否为0
    if (Course->CourseNum == 0) {
        printf("还没有任何课程\n");
        return;
    }
    // index存储排序结果的下标，chosen存储对应的已选课量
    int index[Course->CourseNum], chosen[Course->CourseNum];
    for (int i = 0; i < Course->CourseNum; i += 1) {
        index[i] = i;
        chosen[i] = Course->Data[i].limitNum - Course->Data[i].leftNum;
    }
    // 排序
    Sort(index, chosen, Course->CourseNum);
    // 打印
    printf("--------------------------------------------------------------------\n");
    printf("|   课程名称  |   课程编号  |  教师名称 |剩余课量|已选人数|选课状态\n");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < Course->CourseNum; i += 1) {
        int teacherIndex = SearchTeacher(Teacher, Course->Data[index[i]].teacherID);
        printf("|%-13s|%06d       |%11s  |%8d|%7d|",
               Course->Data[index[i]].courseName,
               Course->Data[index[i]].courseID,
               Teacher->Data[teacherIndex].teacherName,
               Course->Data[index[i]].leftNum,Course->Data[index[i]].studentNum);
        if (Course->Data[index[i]].status == 0) {
            printf("未选课｜\n");
        } else if (Course->Data[index[i]].status == 1) {
            printf("选课中｜\n");
        } else {
            printf("已开课｜\n");
        }
        printf("---------------------------------------------------------------------\n");
    }
}

/* 将课程结构体中起止时间的数字打印成相应格式*/
void CoursePrintTime(int time) {
    // 202*-202*学年第*学期第**周
    printf("202%d-202%d学年第%d学期第%d周\n",
           time / 10000, time % 10000 / 1000,
           time % 1000 / 100, time % 100);
}

/* 判断上课起始时间是否冲突*/
bool IsBetween(int timeStart, int timeEnd, int start, int end) {
    if (timeStart / 1000 != start / 1000) {
        // 判断学年相同
        return false;
    } else if ((timeStart / 100 % 10) != (start / 100 % 10)) {
        // 判断学期相同
        return false;
    } else if (timeEnd % 100 < start % 100) {
        // 判断周次是否交叉
        return false;
    } else if (end % 100 < timeStart % 100) {
        // 判断周次是否交叉
        return false;
    }
    return true;
}

/* 判断上课时间是否冲突*/
bool IsSameTime(int courseID1, int courseID2) {
    int index1 = SearchCourse(Course, courseID1);
    int index2 = SearchCourse(Course, courseID2);
    
    // 记录起始时间
    int start1 = Course->Data[index1].timeStart;
    int start2 = Course->Data[index2].timeStart;
    int end1 = Course->Data[index1].timeEnd;
    int end2 = Course->Data[index2].timeEnd;
    // 判断周次是否冲突
    if (IsBetween(start1, end1, start2, end2)) {
        // 判断星期几是否冲突
        if (Course->Data[index1].day == Course->Data[index2].day) {
            // 判断节次是否冲突
            int CourseStart1 = Course->Data[index1].sectionStart;
            int CourseStart2 = Course->Data[index2].sectionStart;
            int CourseEnd1 = Course->Data[index1].sectionStart + Course->Data[index1].sectionNum - 1;
            int CourseEnd2 = Course->Data[index2].sectionStart + Course->Data[index2].sectionNum - 1;
            if (CourseEnd1 < CourseStart2) {
                return false;
            } else if (CourseEnd2 < CourseStart1) {
                return false;
            }
            return true;
        }
    }
    return false;
}

/* 打印课程持续时间*/
void PrintTime(int sectionTime, int timeNum) {
    if (sectionTime <= 4) {
        //早晨的打印
        printf("早上%d:00-", sectionTime + 7);
        printf("%d:50", sectionTime + timeNum + 6);
    } else if (sectionTime <= 8) {
        //下午的打印
        printf("下午%d:30-", sectionTime - 4);
        printf("%d:20", sectionTime + timeNum - 4);
    } else {
        // 晚上的打印
        printf("晚上%d:30-", sectionTime - 3);
        printf("%d:20", sectionTime + timeNum - 3);
    }
}
