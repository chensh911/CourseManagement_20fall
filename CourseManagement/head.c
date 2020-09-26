//
//  head.c
//  CourseManagement
//
//  Created by 陈尚衡 on 2020/9/2.
//  Copyright © 2020 陈尚衡. All rights reserved.
//

#include "head.h"
#include "course.h"
#include "student.h"
#include "teacher.h"
#include <string.h>
#include <ctype.h>

/* 加载数据使用的函数*/

/* 加载主函数*/
void load(void){
    LoadTeacher();
    LoadStudent();
    LoadCourse();
}

/* 将老师的信息导入到程序中*/
void LoadTeacher(void) {
    FILE* fp = fopen("/Users/chenshangheng/Desktop/CourseManagement/teacher.txt", "r");
    if( fp )
    {
        TEACHER T; // 用于存放数据的临时结构体
        
        // 将老师的信息从文件读入结构体中
        while(fscanf(fp, "%d%s%s%s%s%d", &T.teacherID, T.school, T.teacherName,
                     T.email, T.password,&T.courseNum) != EOF)
        {
            for (int i=0; i<T.courseNum;i++)
            {
                fscanf(fp,"%d",&T.courseID[i]);
            }
            InsertTeacher(Teacher, T);
        }
        fclose(fp);
    }
    else
    {
        printf("无法打开文件\n");
    }
    
}

/* 将学生的信息导入到程序中*/
void LoadStudent(void) {
    FILE* fp = fopen("/Users/chenshangheng/Desktop/CourseManagement/student.txt", "r");
    if( fp )
    {
        STUDENT S; // 用于存放数据的临时结构体
        
        // 将学生的信息添加到学生结构体中
        while(fscanf(fp, "%s%s%s%s%s%s%d%d%d", S.studentName, S.school,
                     S.major, S.password, S.telephone, S.mail, &S.gender,
                     &S.studentID, &S.courseNum) != EOF)
        {
            for(int i = 0;i < S.courseNum;i++)
            {
                fscanf(fp,"%d",&S.courseID[i]);
            }
            // 将结构体添加到学生的类中
            InsertStudent(Student, S);
        }
        fclose(fp);
    }
    else
    {
        printf("无法打开文件\n");
    }
    
}

/* 将课程的信息导入到程序中*/
void LoadCourse(void) {
    
    FILE* fp = fopen("/Users/chenshangheng/Desktop/CourseManagement/course.txt", "r");
    if( fp )
    {
        COURSE C; // 用于存放数据的临时结构体
        
        //  将课程的信息导入到结构体中
        while(fscanf(fp, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &C.status, &C.courseID,
                     &C.teacherID, &C.credit, &C.classHour, &C.property,&C.day,
                     &C.sectionStart, &C.sectionNum, &C.limitNum,  &C.leftNum,
                     &C.timeStart, &C.timeEnd, &C.studentNum) != EOF)
        {
            // 用循环添加该门课程的学生编号信息
            for(int i=0; i<C.studentNum ;i++)
            {
                fscanf(fp, "%d", &C.studentID[i]);
            }
            fscanf(fp, "%s%s%s%s", C.place, C.courseName, C.textbook, C.courseDecri);
            
            // 将课程信息导入到类中
            InsertCourse(Course, C);
        }
        fclose(fp);
    }
    
    else
    {
        printf("无法打开文件\n");
    }
}

/* 存储数据使用的函数*/
void save() {
    SaveStudent();
    SaveTeacher();
    SaveCourse();
}

/* 将老师信息保存到文件中*/
void SaveTeacher() {
    FILE* fp = fopen("/Users/chenshangheng/Desktop/CourseManagement/teacher.txt","w");
    
    // 循环打印信息
    for (int i = 0; i < Teacher->TeacherNum; i += 1) {
        fprintf(fp,"%d\t%s\t%s\t%s\t%s\t%d\t",Teacher->Data[i].teacherID,
                Teacher->Data[i].school, Teacher->Data[i].teacherName,
                Teacher->Data[i].email, Teacher->Data[i].password,Teacher->Data[i].courseNum);
        {
            for(int j = 0;j <Teacher->Data[i].courseNum;j++ )
            {
                fprintf(fp,"%d\t",Teacher->Data[i].courseID[j]);
            }
        }
        fprintf(fp, "\n");
        //Teacher单个结构体的表达为：Teacher->Data[i]
    }
}
/* 将学生信息保存到文件中*/
void SaveStudent() {
    FILE* fp = fopen("/Users/chenshangheng/Desktop/CourseManagement/student.txt","w");
    
    // 循环打印信息
    for (int i = 0; i < Student->StudentNum; i += 1) {
        fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t",Student->Data[i].studentName,Student->Data[i].school,Student->Data[i].major,Student->Data[i].password,Student->Data[i].telephone,Student->Data[i].mail,Student->Data[i].gender,Student->Data[i].studentID,Student->Data[i].courseNum);
        for (int j = 0; j < Student->Data[i].courseNum; j++) {
            fprintf(fp, "%d\t", Student->Data[i].courseID[j]);
        }
        fprintf(fp, "\n");
        //Student单个结构体的表达为：Student->Data[i]
    }
}

/* 将课程信息保存到文件中*/
void SaveCourse() {
    FILE* fp = fopen("/Users/chenshangheng/Desktop/CourseManagement/course.txt","w");
    
    // 循环打印信息
    for (int i = 0; i < Course->CourseNum; i += 1) {
        fprintf(fp,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
                Course->Data[i].status, Course->Data[i].courseID,
                Course->Data[i].teacherID, Course->Data[i].credit,
                Course->Data[i].classHour, Course->Data[i].property,
                Course->Data[i].day, Course->Data[i].sectionStart,
                Course->Data[i].sectionNum, Course->Data[i].limitNum,
                Course->Data[i].leftNum, Course->Data[i].timeStart,
                Course->Data[i].timeEnd, Course->Data[i].studentNum);
        {
            for(int j=0; j<Course->Data[i].studentNum; j++)
            {
                fprintf(fp,"%d\n",Course->Data[i].studentID[j]);
            }
            fprintf(fp, "\t%s\t%s\t%s\t%s\n",Course->Data[i].place,
                    Course->Data[i].courseName, Course->Data[i].textbook,
                    Course->Data[i].courseDecri);
        }
        //Course单个结构体的表达为：Course->Data[i]
    }
}

/*辅助函数 */

/* 用于排序的辅助函数，用冒泡排序实现
 * 1. 所传参数：
 * index [] 存储要排序的索引信息,
 * compare[] 存储相应索引需要比较的具体数值。
 * 2. 用法：
 * 根据compare的数值进行排序，并将index按排序结果顺序排列
 */
void Sort(int index[], int compare[], int len) {
    for (int i = 0; i < len - 1; i += 1) {
        for (int j = 0; j < len - i - 1; j += 1) {
            if (compare[j] < compare[j + 1]) {
                int temp = compare[j];
                compare[j] = compare[j + 1];
                compare[j + 1] = temp;
                temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
        }
    }
}

/* 判断邮箱是否符合规范
 * 1. 所传参数：EmailAddress[] 为需要判断的邮箱
 * 2. 符合要求则返回true，否则返回false
 */
bool IsEmailValid(char EmailAddress[]) {
    int i = 0;
    int j = 0;//邮箱中@的数量
    int k = 0;//邮箱中@的位置
    int l = 0;//邮箱中.的数量
    int m = 0;//邮箱中.的位置
    for(; i < strlen(EmailAddress); i++) {
        if((i == 0 && EmailAddress[i] == '@') || j>1 || l>1) {
            break;//第一位为@及邮箱中含有多个@或.的情况
        }
        if(EmailAddress[i] == '@') {
            j++;
            k=i;
        }//获取@的数量及位置
        if((EmailAddress[i] == '.' && i<=k) ||
           (EmailAddress[i] == '@' && EmailAddress[i+1] == '.')) {
            break;//.在@前面及@与.相邻的情况
        }
        if(EmailAddress[i] == '.') {
            l++;
            m=i;
        }//获取.的数量及位置
        if(EmailAddress[strlen(EmailAddress)-1] == '.') {
            break;
        }
    }
    if(l*j == 1 && k < m) {
        return true;
    } else {
        return false;
    }
}


bool IsAllDigit(char* s) {
    for (int i = 0; i < strlen(s); i += 1) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}
