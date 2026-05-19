#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
#include<stack>
using namespace std;

struct student
{
	string name;//姓名
	string major;//专业
	string classes;//班级
	string sex;//性别
	int id;//学号
	int age;//年龄
	student* next;//指向下一个学生信息的指针
	int studytime=0;//学习时间
	string score="未录入成绩";//成绩
};

struct student* head=NULL;
int student_num = 0;
//操作面板对象
class record
{
public:
	struct student* Insertstu(struct student* h);	//插入学生信息
	struct student* Deletestu(struct student* h);	//删除学生信息
	struct student* Changestu(struct student* h);	//修改学生信息
	struct student* Mergesort(struct student* h);	//可指定排序字段的归并排序（学号/姓名/年龄等）
	struct student* Findstu(struct student* h, int id);     //根据学生学号查询学生信息	
	struct student* Findstu(struct student* h, string name);	//根据学生姓名查询学生信息
	void Printall(struct student* h);	//输出所有学生信息
	void MajorRecordFind(struct student* h, string x);     //统计指定专业的学生人数，并显示全部指定专业学生信息 
	void ClasRecordFind(struct student* h, string x);     //统计指定班级的学生人数，并显示全部指定班级学生信息 
	void AgeRecordFind(struct student* h, int x);     //统计指定年龄的学生人数，并显示全部指定年龄学生信息 
	void SexRecordFind(struct student* h, string x);     //统计指定性别的学生人数，并显示全部指定性别学生信息 
	void SaveRecordFile(struct student* h);     //保存学生信息到文件 
	struct student* LoadRecordFile(struct student* h);   //从文件中加载学生信息 
    struct student* InitList();	//初始化空链表，返回 NULL 或头结点
    void DestroyList(struct student* h);	//释放整个链表所有节点，避免内存泄漏
    void ClearList(struct student*& h);	//删除所有节点并将头指针置空，保留空链表状态
    int GetCount(struct student* h);	//获取当前链表中的学生总数
    bool IsIdExist(struct student* h, int id);	//检查学号是否已存在，用于插入时保证唯一性
    void FindByNameFuzzy(struct student* h, const string& keyword);	//模糊姓名查找，显示所有姓名包含关键字的记录
    void PrintPage(struct student* h, int pageSize, int pageNum);	//分页显示学生信息，避免数据过多刷屏
    void ShowSummary(struct student* h);	//显示汇总信息：总人数、各专业/班级人数分布、男女比例等
    struct student* AppendFromFile(struct student* h, const string& filename);	//从文件追加记录，不覆盖现有数据
    void ExportToCSV(struct student* h, const string& filename);	//导出为 CSV 文件，可用 Excel 打开
    void Backup(struct student* h);	//自动备份当前数据到带时间戳的文件
    struct student* Restore(const string& backupFile);	//从备份文件恢复数据
    struct student* Reverse(struct student* h);	//反转整个链表，便于按插入逆序查看
    struct student* RemoveDuplicates(struct student* h);	//删除学号重复的节点（保留第一个）
    void Undo();	//（需维护操作栈）撤销最近一次增/删/改操作

	
	record()
	{
		while(true)
		{
			cout<<"请输入管理员权限：学生，班干部，老师";
			cin>>record::primission;
			if(primission=="学生"||primission=="班干部"||primission=="老师")
			{
				break;
			}
			else
			{
				cout<<"输入错误，请重新输入\n";
				continue;
			}
		}
	}
	private:
		string primission;
};

//插入学生信息，按学号升序插入
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
	if(primission=="老师")
	{
		cout << "请输入学生的学习时间：";
		cin >> p1->studytime;
		cout << "请输入学生的成绩：";
		cin >> p1->score;
	}
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
	delete p1;
	delete p2;
	return h;
}

//删除学生信息
struct student* record::Deletestu(struct student* h)
{
	if(primission=="学生")
	{
		cout<<"权限不足，无法删除学生信息\n";
		return h;
	}
	if(h==NULL)
	{
		cout<<"没有学生信息，无法删除\n";
		return h;
	}
	while(true)
	{
		cout<<"|-------------------------\n";
		cout<<"|请选择删除方式：\n";
		cout<<"|1.根据学号删除\n";
		cout<<"|2.根据姓名删除\n";
		cout<<"|3.退出\n";
		cout<<"|-------------------------\n";
		int op=0;
		cin>>op;
		student *p1=NULL,*p2=NULL;
		if(op==1)//根据学号删除
		{
			int id=0;
			cin>>id;
			p2=Findstu(h,id);
			if(p2==NULL)
			{
				cout<<"没有找到该学生的个人信息，请重新输入\n";
				delete p1;
				delete p2;
			}
			if(p2==h)
			{
				if(p2->id==id)
				{
					h=h->next;
					student_num--;
					delete p1;
					delete p2;
				}
			}
			p1=p2->next;

			if(p1==h)
			{
				h=h->next;
				student_num--;
				delete p1;
				delete p2;
			}
			else if(p1->next==NULL)
			{
				p2->next=NULL;
				student_num--;
				delete p1;
				delete p2;
			}
			else
			{
				p2->next=p1->next;
				student_num--;
				delete p1;
				delete p2;
			}
		}
		else if(op==2)
		{
			
			string name;
			cin>>name;
			p2=Findstu(h,name);
			if(p2==NULL)
			{
				cout<<"没有找到该学生的个人信息，请重新输入\n";
				delete p1;
				delete p2;
			}
			if(p2==h)
			{
				if(p2->name==name)
				{
					h=h->next;
					student_num--;
					delete p1;
					delete p2;
				}
			}
			p1=p2->next;

			if(p1==h)
			{
				h=h->next;
				student_num--;
				delete p1;
				delete p2;
			}
			else if(p1->next==NULL)
			{
				p2->next=NULL;
				student_num--;
				delete p1;
				delete p2;
			}
			else
			{
				p2->next=p1->next;
				student_num--;
				delete p1;
				delete p2;
			}
		}
		else if(op==3)
		{
			cout<<"已经退出删除界面\n";
			break;
		}
		else
		{
			cout<<"错误指令，请重新输入\n";
			continue;
		}
	}
	return h;
}

//根据学号查询学生信息
struct student* record::Findstu(struct student* h,int id)
{
	student *p1=NULL,*p2=NULL;
	p1=h;
	while(p1!=NULL&&p1->id!=id)
		{
			p2=p1;
			p1=p1->next;
		}
		if(p1==NULL)
		{
			cout<<"没有找到该学生的个人信息，请重新输入\n";
			return NULL;
			delete p1;
			delete p2;
		}
		else if(p1==h)
		{
			return p1;
			delete p1;
			delete p2;
		}
		else 
		{
			return p2;
			delete p1;
			delete p2;
		}
}

//根据姓名查询学生信息
struct student* Findstu(struct student* h,string name)
{
	student *p1=NULL,*p2=NULL;
	p1=h;
	while(p1!=NULL&&p1->name!=name)
		{
			p2=p1;
			p1=p1->next;
		}
		if(p1==NULL)
		{
			cout<<"没有找到该学生的个人信息，请重新输入\n";
			return NULL;
			delete p1;
			delete p2;
		}
		else if(p1==h)
		{
			return p1;
			delete p1;
			delete p2;
		}
		else 
		{
			return p2;
			delete p1;
			delete p2;
		}
}

//修改学生信息
struct student* record::Changestu(struct student* h)
{
	if(primission=="学生")
	{
		cout<<"权限不足，无法修改学生信息\n";
		return h;
	}
	if(h==NULL)
	{
		cout<<"没有学生信息，无法修改\n";
		return h;
	}
	while(true)
	{
		cout<<"|-------------------------\n";
		cout<<"|请选择修改方式：\n";
		cout<<"|1.根据学号修改\n";
		cout<<"|2.根据姓名修改\n";
		cout<<"|3.退出\n";
		cout<<"|-------------------------\n";
		int op1=0;
		cin>>op1;
		student *p1=NULL,*p2=NULL;
		if(op1==1)
		{
			int id=0;
			cin>>id;
			p2=Findstu(h,id);
			if(p2==NULL)
			{
				cout<<"没有找到该学生的个人信息，请重新输入\n";
				delete p1;
				delete p2;
				break;
			}
			else if(p2==h&&p2->id==id)
			{
				p1=p2;
			}
			else
			{
				p1=p2->next;
			}
			while(true)
			{
				cout<<"|-------------------------\n";
				cout<<"|请选择修改内容：\n";
				cout<<"|1.专业\n";
				cout<<"|2.班级\n";
				cout<<"|3.性别\n";
				cout<<"|4.年龄\n";
				if(primission=="老师")
				{
				cout<<"|5.学习时间\n";
				cout<<"|6.成绩\n";
				}
				cout<<"|0.退出\n";
				cout<<"|-------------------------\n";
				int op2=0;
				cin>>op2;
				if(op2==1)
				{
					string major;
					cin>>major;
					p1->major=major;
				}
				else if(op2==2)
				{
					string classes;
					cin>>classes;
					p1->classes=classes;
				}
				else if(op2==3)
				{
					string sex;
					cin>>sex;
					p1->sex=sex;
				}
				else if(op2==4)
				{
					int age;
					cin>>age;
					p1->age=age;
				}
				else if(op2==5&&primission=="老师")
				{
					int studytime;
					cin>>studytime;
					p1->studytime=studytime;
				}
				else if(op2==6&&primission=="老师")
				{
					string score;
					cin>>score;
					p1->score=score;
				}
				else if(op2==0)
				{
					cout<<"已经退出修改界面\n";
					delete p1;
					delete p2;
					break;
				}
				else
				{
					cout<<"错误指令，请重新输入\n";
					continue;
				}
			}
		}
		else if(op1==2)
		{
			int id=0;
			cin>>id;
			p2=Findstu(h,id);
			if(p2==NULL)
			{
				cout<<"没有找到该学生的个人信息，请重新输入\n";
				delete p1;
				delete p2;
				break;
			}
			else if(p2==h&&p2->id==id)
			{
				p1=p2;
			}
			else
			{
				p1=p2->next;
			}
			while(true)
			{
				cout<<"|-------------------------\n";
				cout<<"|请选择修改内容：\n";
				cout<<"|1.专业\n";
				cout<<"|2.班级\n";
				cout<<"|3.性别\n";
				cout<<"|4.年龄\n";
				if(primission=="老师")
				{
				cout<<"|5.学习时间\n";
				cout<<"|6.成绩\n";
				}
				cout<<"|0.退出\n";
				cout<<"|-------------------------\n";
				int op2=0;
				cin>>op2;
				if(op2==1)
				{
					string major;
					cin>>major;
					p1->major=major;
				}
				else if(op2==2)
				{
					string classes;
					cin>>classes;
					p1->classes=classes;
				}
				else if(op2==3)
				{
					string sex;
					cin>>sex;
					p1->sex=sex;
				}
				else if(op2==4)
				{
					int age;
					cin>>age;
					p1->age=age;
				}
				else if(op2==5&&primission=="老师")
				{
					int studytime;
					cin>>studytime;
					p1->studytime=studytime;
				}
				else if(op2==6&&primission=="老师")
				{
					string score;
					cin>>score;
					p1->score=score;
				}
				else if(op2==0)
				{
					cout<<"已经退出修改界面\n";
					delete p1;
					delete p2;
					break;
				}
				else
				{
					cout<<"错误指令，请重新输入\n";
					continue;
				}
			}
		}
		else if(op1==3)
		{
			cout<<"已经退出修改界面\n";
			delete p1;
			delete p2;
			break;
		}
		else
		{
			cout<<"错误指令，请重新输入\n";
			continue;
		}
	}
	return h;
}

//用归并排序对信息排序
struct student* record::Mergesort(struct student* h)
{
	if(h==NULL||h->next==NULL)
	{
		return h;
	}
	student *slow,*fast;
	slow=fast=h;
	while(fast!=NULL&&fast->next!=NULL)
	{
		fast=fast->next->next;
		slow=slow->next;
	}
	student* right=slow;
	student* left=h;
	left=Mergesort(left);
	right=Mergesort(right);
	return Merge(left,right);
}

//合并两个有序链表
struct student* Merge(struct student* left,struct student* right)
{
	student* dummy=new student;
	student* tail=dummy;
	while(left!=NULL&&right!=NULL)
	{
		if(left->id<right->id)
		{
			tail->next=left;
			left=left->next;
		}
		else
		{
			tail->next=right;
			right=right->next;
		}
		tail=tail->next;
	}
	while(left!=NULL)
	{
		tail->next=left;
		left=left->next;
		tail=tail->next;
	}
	while(right!=NULL)
	{
		tail->next=right;
		right=right->next;
		tail=tail->next;
	}return dummy->next;
}

//保存学生信息到文件
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
		ofile << '\n' << h->name << '\t' << h->id << '\t' << h->age << '\t' << h->sex << h->major << '\t' << h->classes<<'\t'<< h->studytime << '\t' << h->score;
		p = h;
		h = h->next;
		delete p;
	}
	ofile.close();
	return;
}

//从文件中加载学生信息
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
		ifile >> p->id >> p->name >> p->major >> p->classes >> p->sex >> p->age >> p->studytime >> p->score; 
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

