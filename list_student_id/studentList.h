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
	struct student* Mergesort(struct student* h,int op);	//可指定排序字段的归并排序（学号/姓名/班级等）
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
    struct student* DeleteByCondition(struct student* h);	//根据指定条件批量删除学生信息

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
	student_num++;
	return h;
}

//删除学生信息
struct student* record::Deletestu(struct student* h)
{
    if (primission == "学生") {
        cout << "权限不足，无法删除学生信息\n";
        return h;
    }
    if (h == NULL) {
        cout << "没有学生信息，无法删除\n";
        return h;
    }

    while (true) {
        cout << "|-------------------------\n";
        cout << "|请选择删除方式：\n";
        cout << "|1.根据学号删除\n";
        cout << "|2.根据姓名删除\n";
        cout << "|3.退出\n";
        cout << "|-------------------------\n";
        int op = 0;
        cin >> op;

        if (op == 3) {
            cout << "已经退出删除界面\n";
            break;
        }
        if (op != 1 && op != 2) {
            cout << "错误指令，请重新输入\n";
            continue;
        }

        // 获取要删除的关键字
        int id = 0;
        string name;
        if (op == 1) {
            cout << "请输入学号：";
            cin >> id;
        } else {
            cout << "请输入姓名：";
            cin >> name;
        }

        // 查找目标节点和前驱
        student* prev = NULL;
        student* target = h;
        while (target != NULL) {
            if ((op == 1 && target->id == id) ||
                (op == 2 && target->name == name))
                break;
            prev = target;
            target = target->next;
        }

        if (target == NULL) {
            cout << "没有找到该学生的信息，请重新输入\n";
            continue;
        }

        // 从链表中移除 target
        if (prev == NULL) {   // 删除头节点
            h = target->next;
        } else {              // 删除中间或尾节点
            prev->next = target->next;
        }

        delete target;        // 释放内存
        student_num--;
        cout << "删除成功！当前学生总数：" << student_num << endl;
    }
    return h;
}

//根据学号查询学生信息
struct student* record::Findstu(struct student* h, int id) {
    student* p = h;
    while (p != NULL) {
        if (p->id == id)
            return p;
        p = p->next;
    }
    cout << "未找到学号为 " << id << " 的学生\n";
    return NULL;
}

//根据姓名查询学生信息
struct student* record::Findstu(struct student* h, string name) {
    student* p = h;
    while (p != NULL) {
        if (p->name == name)
            return p;
        p = p->next;
    }
    cout << "未找到姓名为 " << name << " 的学生\n";
    return NULL;
}

//不同指令下排序规则
bool cmp(struct student* left,struct student* right,int op)
{
	if(op==1)
	{	
		if(left->name!=right->name) return left->name<=right->name;
		else return left->id<=right->id;
	}
	else if(op==2)
	{
		if(left->id!=right->id) return left->id<=right->id;
		else return left->name<=right->name;
	}
	else if(op==3)
	{
		if(left->major!=right->major) return left->major<=right->major;
		else if(left->classes!=right->classes) return left->classes<=right->classes;
		else return left->id<=right->id;
	}
	else
	{
		return left->id<=right->id;
	}
}

//修改学生信息
struct student* record::Changestu(struct student* h)
{
    if (primission == "学生") {
        cout << "权限不足，无法修改学生信息\n";
        return h;
    }
    if (h == NULL) {
        cout << "没有学生信息，无法修改\n";
        return h;
    }

    while (true) {
        cout << "|-------------------------\n";
        cout << "|请选择修改方式：\n";
        cout << "|1.根据学号修改\n";
        cout << "|2.根据姓名修改\n";
        cout << "|3.退出\n";
        cout << "|-------------------------\n";
        int op;
        cin >> op;

        if (op == 3) {
            cout << "已经退出修改界面\n";
            break;
        }
        if (op != 1 && op != 2) {
            cout << "错误指令，请重新输入\n";
            continue;
        }

        // 按输入查找目标节点
        student* target = NULL;
        if (op == 1) {
            int id;
            cout << "请输入学号：";
            cin >> id;
            target = Findstu(h, id);   // 假设已改为返回目标节点
        } else {
            string name;
            cout << "请输入姓名：";
            cin >> name;
            target = Findstu(h, name);
        }

        if (target == NULL) {
            cout << "未找到该学生，请重新选择操作\n";
            continue;          // 回到外层菜单，不退出
        }

        // 进入字段修改循环
        while (true) {
            cout << "|-------------------------\n";
            cout << "|当前学生：" << target->name << " " << target->id << "\n";
            cout << "|请选择修改内容：\n";
            cout << "|1.专业\n";
            cout << "|2.班级\n";
            cout << "|3.性别\n";
            cout << "|4.年龄\n";
            if (primission == "老师") {
                cout << "|5.学习时间\n";
                cout << "|6.成绩\n";
            }
            cout << "|0.完成修改，返回上级\n";
            cout << "|-------------------------\n";
            int field;
            cin >> field;

            if (field == 0) break;

            switch (field) {
                case 1:
                    cout << "新专业："; cin >> target->major; break;
                case 2:
                    cout << "新班级："; cin >> target->classes; break;
                case 3:
                    cout << "新性别："; cin >> target->sex; break;
                case 4:
                    cout << "新年龄："; cin >> target->age; break;
                case 5:
                    if (primission == "老师") {
                        cout << "新学习时间："; cin >> target->studytime;
                    } else {
                        cout << "无效选项\n";
                    }
                    break;
                case 6:
                    if (primission == "老师") {
                        cout << "新成绩："; cin >> target->score;
                    } else {
                        cout << "无效选项\n";
                    }
                    break;
                default:
                    cout << "错误指令，请重新输入\n";
            }
        }
    }
    return h;
}

//用归并排序对信息排序
struct student* record::Mergesort(struct student* h,int op)
{
	if(h==NULL||h->next==NULL)
	{
		return h;
	}
	student *slow,*fast;
	slow=fast=h;
	student* pre=NULL;
	while(fast!=NULL&&fast->next!=NULL)
	{
		pre=slow;
		fast=fast->next->next;
		slow=slow->next;
	}
	if(pre!=NULL)
	{
		pre->next=NULL;
	}
	student* right=slow;
	student* left=h;
	left=Mergesort(left,op);
	right=Mergesort(right,op);
	return Merge(left,right,op);
}

//合并两个有序链表
struct student* Merge(struct student* left,struct student* right,int op)
{
	student* dummy=new student;
	student* tail=dummy;
	while(left!=NULL&&right!=NULL)
	{
		
		if(cmp(left,right,op))
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
	}
	student* head=dummy->next;
	delete dummy;
	return head;
}

//输出所有学生信息
void record::Printall(struct student* h)
{
	if(h==NULL)
	{
		cout<<"没有学生信息，无法输出\n";
		return;
	}
	student* p=h;
	while(p!=NULL)
	{
		cout<<"\n学号："<<p->id<<"\t姓名："<<p->name<<"\t性别："<<p->sex<<"\t专业："<<p->major<<"\t班级："<<p->classes;
		cout<<"\n学习时长:"<<p->studytime<<"\t成绩："<<p->score<<'\n';
		p=p->next;
	}
	cout<<"总人数："<<student_num<<'\n';
	return;
}

//统计指定专业的学生人数，并显示全部指定专业学生信息
void record::MajorRecordFind(struct student* h,string x)
{
	if(h==NULL)
	{
		cout<<"没有学生信息，无法查询统计\n";
		return;
	}
	student* p=h;
	int count=0;
	while(p!=NULL)
	{
		if(p->major==x)
		{
			count++;
			cout<<"\n学号："<<p->id<<"\t姓名："<<p->name<<"\t性别："<<p->sex<<"\t专业："<<p->major<<"\t班级："<<p->classes;
			cout<<"\n学习时长:"<<p->studytime<<"\t成绩："<<p->score<<'\n';
		}
		p=p->next;
	}
	if(count==0)
	{
		cout<<"没有找到该专业的学生，请查看输入专业是否正确\n";
		return;
	}
	cout<<"总人数："<<count<<'\n';
	return;
}

void record::ClasRecordFind(struct student* h,string x)
{
	if(h==NULL)
	{
		cout<<"没有学生信息，无法查询统计\n";
		return;
	}
	student* p=h;
	int count=0;
	while(p!=NULL)
	{
		if(p->classes==x)
		{
			count++;
			cout<<"\n学号："<<p->id<<"\t姓名："<<p->name<<"\t性别："<<p->sex<<"\t专业："<<p->major<<"\t班级："<<p->classes;
			cout<<"\n学习时长:"<<p->studytime<<"\t成绩："<<p->score<<'\n';
		}
		p=p->next;
	}
	if(count==0)
	{
		cout<<"没有找到该班级的学生，请查看输入班级是否正确\n";
		return;
	}
	cout<<"总人数："<<count<<'\n';
	return;
}

void record::SexRecordFind(struct student* h,string x)
{
	if(h==NULL)
	{
		cout<<"没有学生信息，无法查询统计\n";
		return;
	}
	student* p=h;
	int count=0;
	while(p!=NULL)
	{
		if(p->sex==x)
		{
			count++;
			cout<<"\n学号："<<p->id<<"\t姓名："<<p->name<<"\t性别："<<p->sex<<"\t专业："<<p->major<<"\t班级："<<p->classes;
			cout<<"\n学习时长:"<<p->studytime<<"\t成绩："<<p->score<<'\n';
		}
		p=p->next;
	}
	if(count==0)
	{
		cout<<"没有找到该性别的学生，请查看输入性别是否正确\n";
		return;
	}
	cout<<"总人数："<<count<<'\n';
	return;
}

void record::AgeRecordFind(struct student* h,int x)
{
	if(h==NULL)
	{
		cout<<"没有学生信息，无法查询统计\n";
		return;
	}
	student* p=h;
	int count=0;
	while(p!=NULL)
	{
		if(p->age==x)
		{
			count++;
			cout<<"\n学号："<<p->id<<"\t姓名："<<p->name<<"\t性别："<<p->sex<<"\t专业："<<p->major<<"\t班级："<<p->classes;
			cout<<"\n学习时长:"<<p->studytime<<"\t成绩："<<p->score<<'\n';
		}
		p=p->next;
	}
	if(count==0)
	{
		cout<<"没有找到该年龄的学生，请查看输入年龄是否正确\n";
		return;
	}
	cout<<"总人数："<<count<<'\n';
	return;
}

//保存学生信息到文件
void record::SaveRecordFile(struct student* h)
{
    ofstream ofile("student.dat");
    if (!ofile) {
        cout << "文件打开错误，无法写入\n";
        return;
    }

    student* p = h;
    while (p != NULL) {
        ofile << p->id  << '\t' << p->name << '\t' << p->sex  << '\t' << p->age
              << '\t' << p->major << '\t' << p->classes
              << '\t' << p->studytime << '\t' << p->score << '\n';
        p = p->next;
    }
    ofile.close();
    cout << "保存成功，共 " << student_num << " 条记录\n";
}

//从文件中加载学生信息
struct student* record::LoadRecordFile(struct student* h)
{
    // 1. 先销毁当前链表，避免内存泄漏和重复追加
    DestroyList(h);
    h = NULL;
    student_num = 0;

    ifstream ifile("student.dat");
    if (!ifile) {
        cout << "文件打开错误，无法读取\n";
        return NULL;
    }

    student* p = NULL;
    student* tail = NULL;

    int id, age, studytime;
    string name, sex, major, classes, score;

    // 2. 直接按格式读取，避免 eof 问题
    while (ifile >> id >> name >> sex >> age >> major >> classes >> studytime >> score) {
        student* newStu = new student;
        newStu->id = id;
        newStu->name = name;
        newStu->sex = sex;
        newStu->age = age;
        newStu->major = major;
        newStu->classes = classes;
        newStu->studytime = studytime;
        newStu->score = score;
        newStu->next = NULL;

        if (h == NULL) {
            h = newStu;
            tail = newStu;
        } else {
            tail->next = newStu;
            tail = newStu;
        }
        student_num++;
    }

    ifile.close();
    cout << "加载成功，共 " << student_num << " 条记录\n";
    return h;
}

void record::DestroyList(struct student* h) {
    while (h != NULL) {
        student* temp = h;
        h = h->next;
        delete temp;
    }
}

void record::ClearList(struct student*& h)
{
	DestroyList(h);
	h=NULL;
	student_num=0;
}