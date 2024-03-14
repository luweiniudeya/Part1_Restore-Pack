#include"Student.h"
extern int student_num;
int restore_student(char* buf, int len, Student* s)
{
    /*buf Ϊѹ������洢�����׵�ַ��lenΪbuf�д�����ݵĳ��ȣ�sΪ��Ž�ѹ���ݵĽṹ�������ʼ��ַ��
        ���ؽ�ѹ����������ѹʱ������ʹ�ú����ӿ�֮�����Ϣ����������������ȫ�ֱ�����*/
    int ans = 0;
    char* p = buf;
    while (p < buf + len)//����len�Ϸ�ʱ��bug
    {
        strcpy(s[ans].name, p);
        p += (strlen(p) + 1);
        s[ans].age = *((short*)p);
        p += 2;//�˴���ʵû��Ҫsizeof ֱ�� 2  4����
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
    {//�ǳ����� Ϊʲô���ܰ�origin��(char*)sȻ������ָ��һ���ƶ�������������ȥ��ֵ��float�������쳣
        //name����
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
    /*sΪ��ѹ���������ʼ��ַ�� sno Ϊѹ�������� buf Ϊѹ���洢�����׵�ַ��
    ���������ķ��ؾ��ǵ��ú���ѹ������ֽ�����pack_student_bytebybyteҪ
    ��һ���ֽ�һ���ֽڵ���buf��д���ݣ�pack_student_wholeҪ���short��float�ֶ�
    ��ֻ����һ���������д�룬��strcpyʵ�ִ���д�롣*/
    //memset(buf, 0, sizeof(buf));
    char* origin = (char*)s;//ǿ��ת��
    char* begin = (char*)s;
    char* des = buf;
    int namehelp = 0;
    int remarkhelp = 0;
    while (origin < begin + sizeof(Student) * sno)
    {
        //д��name ��ѹ��
        namehelp = 0;
        remarkhelp = 0;
        for (int i = 0; i < sizeof(Student::name); i++)//byte by byte�ؽ���д��buf  �ұ�֤����
        {
            des[i] = origin[i];
            namehelp++;
            if (origin[i] == '\0')
                break;
        }
        origin += sizeof(Student::name);
        des += namehelp;

        //д��age �� float  ����ѹ��
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
        origin += 4;*/ //���Ҳ��

        //д��remark ��ѹ��
        for (int i = 0; i < sizeof(Student::remark); i++)//byte by byte�ؽ���д��buf  �ұ�֤����
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
    cout << "����\t" << "����\t" << "����\t" << "��ע\t" << endl;
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