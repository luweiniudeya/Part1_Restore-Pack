#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
struct Student {
    char  name[8];//8字节
    short  age;//2字节 后填充2字节才是score
    float  score;//4字节
    char  remark[200];  // 备注信息 200字节
};
int  pack_student_whole(Student* s, int sno, char* buf);
int  pack_student_bytebybyte(Student* s, int sno, char* buf);
int restore_student(char* buf, int len, Student* s);
void  intput(Student s[]);
void print(Student s[]);
void wait();
void print_hex(char ch);