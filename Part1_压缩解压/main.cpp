#include"Student.h"
int student_num;
int main()
{
    Student old_s[20];
    Student new_s[20];
    char message[4320];//20*216
    intput(old_s);
    system("cls");
    print(old_s);
    wait();

    cout << "bytebybyte" << endl;
    int len = pack_student_bytebybyte(old_s, student_num, message);
    cout << "原始长度:" << sizeof(Student) * student_num << " 压缩长度:" << len << endl;
    int num = restore_student(message, len, new_s);
    cout << "解压缩个数:" << num << endl << "解压缩new_s对比输出" << endl;
    cout << "原始" << endl;
    print(old_s);
    cout << "解压缩" << endl;
    print(new_s);
    wait();
    memset(new_s, 0, sizeof(new_s));
    memset(message, 0, sizeof(message));

    cout << "whole" << endl;
    len = pack_student_whole(old_s, student_num, message);
    cout << "原始长度:" << sizeof(Student) * student_num << " 压缩长度:" << len << endl;
    num = restore_student(message, len, new_s);
    cout << "解压缩个数:" << num << endl << "解压缩new_s对比输出" << endl;
    cout << "原始" << endl;
    print(old_s);
    cout << "解压缩" << endl;
    print(new_s);
    wait();
    memset(new_s, 0, sizeof(new_s));
    memset(message, 0, sizeof(message));

    cout << "bytebybyte 2 + whole 3" << endl;
    int len1 = pack_student_bytebybyte(old_s, 2, message);
    int len2 = pack_student_whole(old_s + 2, 3, message + len1);
    len = len1 + len2;
    cout << "原始长度:" << sizeof(Student) * student_num << " 压缩长度:" << len << endl;
    num = restore_student(message, len, new_s);
    cout << "解压缩个数:" << num << endl << "解压缩new_s对比输出" << endl;
    cout << "原始" << endl;
    print(old_s);
    cout << "解压缩" << endl;
    print(new_s);
    wait();


    for (int i = 0; i < 20; i++) {
        print_hex(message[i]);
    }
    return 0;
}