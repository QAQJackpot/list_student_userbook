#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
using namespace std;

struct student
{
	string name;
	string major;
	string classes;
	string sex;
	int id;
	int age;
	student* next;
};

struct student* head;
int student_num = 0;

class record
{
public:
	struct student* Insertstu(struct student* h);	//插入学生信息
	struct student* Deletestu(struct student* h);	//删除学生信息
	struct student* Changestu(struct student* h, int op);	//修改学生信息
	struct student* mergesort(struct student* h);	 //用归并排序对信息排序
	void Findstu(struct student* h, int id);     //根据学生学号查询学生信息	
	void Findstu(struct student* h, string name);	//根据学生姓名查询学生信息
	void Printall(struct student* h);	//输出所有学生信息
	void MajorRecordFind(struct student* h, string x);     //统计指定专业的学生人数，并显示全部指定专业学生信息 
	void ClasRecordFind(struct student* h, string x);     //统计指定班级的学生人数，并显示全部指定班级学生信息 
	void AgeRecordFind(struct student* h, int x);     //统计指定年龄的学生人数，并显示全部指定年龄学生信息 
	void SexRecordFind(struct student* h, string x);     //统计指定性别的学生人数，并显示全部指定性别学生信息 
	void SaveRecordFile(struct student* h);     //保存学生信息到文件 
	struct student* LoadRecordFile(struct student* h);   //从文件中加载学生信息 
};

struct student* record::Insertstu(struct student* h)
{
	student* p1 = NULL, * p2 = NULL;

	p1 = new student;
	cout << "请输入学生的学号：";
	cin >> p1->id;
	cout << "请输入学生的姓名：";
	cin >> p1->name;
	cout << "请输入学生的专业：";
	cin >> p1->major;
	cout << "请输入学生的班级：";
	cin >> p1->classes;
	cout << "请输入学生的性别：";
	cin >> p1->sex;
	cout << "请输入学生的年龄：";
	cin >> p1->age;
	p1->next = NULL;
	if (h == NULL || p1->id < h->id)
	{
		p1->next = h;
		h = p1;
	}
	else
	{
		p2 = h;
		while (p2->next != NULL && p2->next->id < p1->id)
		{
			p2 = p2->next;
		}
		p1->next = p2->next;
		p2->next = p1;
	}

	return h;
}


void record::SaveRecordFile(struct student* h)
{
	struct student* p;
	ofstream ofile;
	ofile.open("student.dat", ios::out);
	if (!ofile)
	{
		cout << "文件打开错误，无法写入\n";
		return;
	}
	cout << "\n学号\t姓名\t专业\t班级\t性别\t年龄\n";
	while (h != NULL)
	{
		ofile << '\n' << h->name << '\t' << h->id << '\t' << h->age << '\t' << h->sex << h->major << '\t' << h->classes;
		p = h;
		h = h->next;
		delete p;
	}
	ofile.close();
	return;
}

struct student* record::LoadRecordFile(struct student* h)
{
	ifstream ifile;
	ifile.open("student.dat", ios::in);
	student *p,*q=NULL;
	if (!ifile)
	{
		cout << "文件打开错误，无法读取\n";
		return;
	}
	char str[50];
	ifile.getline(str,50);
	while (!ifile.eof())
	{
		student_num++;
		p = new student;
		ifile >> p->id >> p->name >> p->major >> p->classes >> p->sex >> p->age; //
		p->next = NULL;
		if (h == NULL)
		{
			q = h = p;
		}
		else
		{
			q ->next = p;
			q = p;
		}
	}
	ifile.close();
	return h;
}


int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	head = NULL;
	record r;

	return 0;
}

