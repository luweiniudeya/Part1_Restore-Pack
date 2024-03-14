#include"Student.h"
extern int student_num;
int restore_student(char* buf, int len, Student* s)
{
    /*buf 为压缩区域存储区的首地址；len为buf中存放数据的长度；s为存放解压数据的结构数组的起始地址；
        返回解压的人数。解压时不允许使用函数接口之外的信息（即不允许定义其他全局变量）*/
    int ans = 0;
    char* p = buf;
    while (p < buf + len)//仅在len合法时无bug
    {
        strcpy(s[ans].name, p);
        p += (strlen(p) + 1);
        s[ans].age = *((short*)p);
        p += 2;//此处其实没必要sizeof 直接 2  4即可
        s[ans].score = *((float*)p);
        p += 4;
        strcpy(s[ans].remark, p);
        p = p + (strlen(p) + 1);
        ans++;
    }
    return ans;
}

int  pack_student_whole(Student* s, int sno, char* buf)
{
    char* origin = nullptr;
    char* des = buf;
    int ans = 0;
    while (ans < sno)
    {//非常疑问 为什么不能把origin赋(char*)s然后两个指针一起移动，这样做赋过去的值在float处出现异常
        //name复制
        origin = s[ans].name;
        strcpy(des, origin);
        des += (strlen(des) + 1);

        //short float
        origin = (char*)&s[ans].age;
        *((short*)des) = *((short*)origin);
        des += 2;

        origin = (char*)&s[ans].score;
        *((float*)des) = *((float*)origin);
        des += 4;
        //remark
        origin = (char*)&s[ans].remark;
        strcpy(des, origin);
        des += (strlen(des) + 1);
        ans++;
    }
    return des - buf;
}


int  pack_student_bytebybyte(Student* s, int sno, char* buf)
{
    /*s为待压缩数组的起始地址； sno 为压缩人数； buf 为压缩存储区的首地址；
    两个函数的返回均是调用函数压缩后的字节数。pack_student_bytebybyte要
    求一个字节一个字节的向buf中写数据；pack_student_whole要求对short、float字段
    都只能用一条语句整体写入，用strcpy实现串的写入。*/
    //memset(buf, 0, sizeof(buf));
    char* origin = (char*)s;//强制转换
    char* begin = (char*)s;
    char* des = buf;
    int namehelp = 0;
    int remarkhelp = 0;
    while (origin < begin + sizeof(Student) * sno)
    {
        //写入name 可压缩
        namehelp = 0;
        remarkhelp = 0;
        for (int i = 0; i < sizeof(Student::name); i++)//byte by byte地将串写入buf  且保证紧凑
        {
            des[i] = origin[i];
            namehelp++;
            if (origin[i] == '\0')
                break;
        }
        origin += sizeof(Student::name);
        des += namehelp;

        //写入age 与 float  不可压缩
        for (int i = 0; i < 2; i++)
        {
            *des = *origin;
            des++; origin++;
        }
        origin += 2;

        for (int i = 0; i < 4; i++)
        {
            *des = *origin;
            des++; origin++;
        }
        /**((unsigned int*)des) = *((unsigned int*)origin);
        des += 4;
        origin += 4;*/ //这个也行

        //写入remark 可压缩
        for (int i = 0; i < sizeof(Student::remark); i++)//byte by byte地将串写入buf  且保证紧凑
        {
            des[i] = origin[i];
            remarkhelp++;
            if (origin[i] == '\0')
                break;
        }
        origin += sizeof(Student::remark);
        des += remarkhelp;
    }
    return des - buf;
}

void  intput(Student s[])
{
    int n;
    cin >> n;
    student_num = n;
    char name[8];
    short age;
    float score;
    char remark[200];
    memset(name, 0, sizeof(name));
    memset(remark, 0, sizeof(remark));
    for (int i = 0; i < n; i++)
    {
        scanf("%s", name);
        cin >> age >> score;
        scanf("%s", remark);
        strcpy(s[i].name, name);
        s[i].age = age;
        s[i].score = score;
        strcpy(s[i].remark, remark);
    }
}
void print(Student s[])
{
    cout << "姓名\t" << "年龄\t" << "分数\t" << "备注\t" << endl;
    for (int i = 0; i < student_num; i++)
        cout << s[i].name << "\t" << s[i].age << "\t" << s[i].score << "\t" << s[i].remark << endl;
    cout << endl;
}
void wait()
{
    system("pause");
    system("cls");
}
void print_hex(char ch)
{
    int x = ch;
    int mask = (1 << 4) - 1;
    int temp = 0;
    
    temp = mask & (x >> 4);
    if (temp >= 0 && temp <= 9)
        cout << temp;
    else printf("%c", 'A' + temp - 10);
    
    temp = mask & x;
    if (temp >= 0 && temp <= 9)
        cout << temp;
    else printf("%c", 'A' + temp - 10);
    cout << " ";
}