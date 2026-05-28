#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <stack>
#include <unordered_map>
#include <iomanip>
#include <ctime>
using namespace std;

struct student
{
    string name; // 姓名
    string major; // 专业
    string classes; // 班级
    string sex; // 性别
    int id; // 学号
    int age; // 年龄
    student* next; // 指向下一个学生信息的指针
    int studytime = 0; // 学习时间
    string score = "未录入成绩"; // 成绩
};

class record
{
public:
    record();
    ~record();

    void Insertstu();
    void Deletestu();
    void Changestu();
    void Mergesort(int op);
    student* Findstu(int id);
    student* Findstu(const string& name);
    void Printall() const;
    void MajorRecordFind(const string& x) const;
    void ClasRecordFind(const string& x) const;
    void AgeRecordFind(int x) const;
    void SexRecordFind(const string& x) const;
    void SaveRecordFile() const;
    void LoadRecordFile();
    void ClearList();
    int GetCount() const;
    bool IsIdExist(int id) const;
    void FindByNameKMP(const string& keyword) const;
    void PrintPage(int pageSize, int pageNum) const;
    void ShowSummary() const;
    void AppendFromFile(const string& filename);
    void ExportToCSV(const string& filename) const;
    void Backup() const;
    void Restore(const string& backupFile);
    void Reverse();
    void RemoveDuplicates();
    void DeleteByCondition();

private:
    student* m_head;
    int m_count;
    string permission;

    void DestroyList();
    student* mergeSortRecur(student* head, int op);
};

bool cmp(struct student* left, struct student* right, int op)
{
    if (op == 1)
    {
        if (left->name != right->name) return left->name <= right->name;
        else return left->id <= right->id;
    }
    else if (op == 2)
    {
        if (left->id != right->id) return left->id <= right->id;
        else return left->name <= right->name;
    }
    else if (op == 3)
    {
        if (left->major != right->major) return left->major <= right->major;
        else if (left->classes != right->classes) return left->classes <= right->classes;
        else return left->id <= right->id;
    }
    else
    {
        return left->id <= right->id;
    }
}

struct student* Merge(struct student* left, struct student* right, int op)
{
    student* dummy = new student;
    student* tail = dummy;
    while (left != NULL && right != NULL)
    {
        if (cmp(left, right, op))
        {
            tail->next = left;
            left = left->next;
        }
        else
        {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }
    while (left != NULL)
    {
        tail->next = left;
        left = left->next;
        tail = tail->next;
    }
    while (right != NULL)
    {
        tail->next = right;
        right = right->next;
        tail = tail->next;
    }
    student* head = dummy->next;
    delete dummy;
    return head;
}

record::record() : m_head(nullptr), m_count(0)
{
    while (true)
    {
        cout << "请输入管理员权限：学生，班干部，老师：";
        cin >> permission;
        if (permission == "学生" || permission == "班干部" || permission == "老师")
            break;
        else
            cout << "输入错误，请重新输入\n";
    }
}

record::~record()
{
    DestroyList();
}

void record::Insertstu()
{
    student* p1 = new student;
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
    if (permission == "老师")
    {
        cout << "请输入学生的学习时间：";
        cin >> p1->studytime;
        cout << "请输入学生的成绩：";
        cin >> p1->score;
    }
    if (IsIdExist(p1->id))
    {
        cout << "学号已存在，插入失败\n";
        delete p1;
        return;
    }
    p1->next = nullptr;
    if (m_head == nullptr || p1->id < m_head->id)
    {
        p1->next = m_head;
        m_head = p1;
    }
    else
    {
        student* p2 = m_head;
        while (p2->next != nullptr && p2->next->id < p1->id)
            p2 = p2->next;
        p1->next = p2->next;
        p2->next = p1;
    }
    m_count++;
}

void record::Deletestu()
{
    if (permission == "学生")
    {
        cout << "权限不足，无法删除学生信息\n";
        return;
    }
    if (m_head == nullptr)
    {
        cout << "没有学生信息，无法删除\n";
        return;
    }

    while (true)
    {
        cout << "|-------------------------\n";
        cout << "|请选择删除方式：\n";
        cout << "|1.根据学号删除\n";
        cout << "|2.根据姓名删除\n";
        cout << "|3.退出\n";
        cout << "|-------------------------\n";
        int op = 0;
        cin >> op;

        if (op == 3)
        {
            cout << "已经退出删除界面\n";
            break;
        }
        if (op != 1 && op != 2)
        {
            cout << "错误指令，请重新输入\n";
            continue;
        }

        int id = 0;
        string name;
        if (op == 1)
        {
            cout << "请输入学号：";
            cin >> id;
        }
        else
        {
            cout << "请输入姓名：";
            cin >> name;
        }

        student* prev = nullptr;
        student* target = m_head;
        while (target != nullptr)
        {
            if ((op == 1 && target->id == id) || (op == 2 && target->name == name))
                break;
            prev = target;
            target = target->next;
        }

        if (target == nullptr)
        {
            cout << "没有找到该学生的信息，请重新输入\n";
            continue;
        }

        if (prev == nullptr)
        {
            m_head = target->next;
        }
        else
        {
            prev->next = target->next;
        }

        delete target;
        m_count--;
        cout << "删除成功！当前学生总数：" << m_count << endl;
    }
}

student* record::Findstu(int id)
{
    student* p = m_head;
    while (p != nullptr)
    {
        if (p->id == id)
            return p;
        p = p->next;
    }
    cout << "未找到学号为 " << id << " 的学生\n";
    return nullptr;
}

student* record::Findstu(const string& name)
{
    student* p = m_head;
    while (p != nullptr)
    {
        if (p->name == name)
            return p;
        p = p->next;
    }
    cout << "未找到姓名为 " << name << " 的学生\n";
    return nullptr;
}

void record::Changestu()
{
    if (permission == "学生")
    {
        cout << "权限不足，无法修改学生信息\n";
        return;
    }
    if (m_head == nullptr)
    {
        cout << "没有学生信息，无法修改\n";
        return;
    }

    while (true)
    {
        cout << "|-------------------------\n";
        cout << "|请选择修改方式：\n";
        cout << "|1.根据学号修改\n";
        cout << "|2.根据姓名修改\n";
        cout << "|3.退出\n";
        cout << "|-------------------------\n";
        int op;
        cin >> op;

        if (op == 3)
        {
            cout << "已经退出修改界面\n";
            break;
        }
        if (op != 1 && op != 2)
        {
            cout << "错误指令，请重新输入\n";
            continue;
        }

        student* target = nullptr;
        if (op == 1)
        {
            int id;
            cout << "请输入学号：";
            cin >> id;
            target = Findstu(id);
        }
        else
        {
            string name;
            cout << "请输入姓名：";
            cin >> name;
            target = Findstu(name);
        }

        if (target == nullptr)
        {
            cout << "未找到该学生，请重新选择操作\n";
            continue;
        }

        while (true)
        {
            cout << "|-------------------------\n";
            cout << "|当前学生：" << target->name << " " << target->id << "\n";
            cout << "|请选择修改内容：\n";
            cout << "|1.专业\n";
            cout << "|2.班级\n";
            cout << "|3.性别\n";
            cout << "|4.年龄\n";
            if (permission == "老师")
            {
                cout << "|5.学习时间\n";
                cout << "|6.成绩\n";
            }
            cout << "|0.完成修改，返回上级\n";
            cout << "|-------------------------\n";
            int field;
            cin >> field;

            if (field == 0) break;

            switch (field)
            {
            case 1:
                cout << "新专业：";
                cin >> target->major;
                break;
            case 2:
                cout << "新班级：";
                cin >> target->classes;
                break;
            case 3:
                cout << "新性别：";
                cin >> target->sex;
                break;
            case 4:
                cout << "新年龄：";
                cin >> target->age;
                break;
            case 5:
                if (permission == "老师")
                {
                    cout << "新学习时间：";
                    cin >> target->studytime;
                }
                else
                {
                    cout << "无效选项\n";
                }
                break;
            case 6:
                if (permission == "老师")
                {
                    cout << "新成绩：";
                    cin >> target->score;
                }
                else
                {
                    cout << "无效选项\n";
                }
                break;
            default:
                cout << "错误指令，请重新输入\n";
            }
        }
    }
}

student* record::mergeSortRecur(student* h, int op)
{
    if (h == nullptr || h->next == nullptr)
        return h;
    student* slow = h;
    student* fast = h;
    student* pre = nullptr;
    while (fast != nullptr && fast->next != nullptr)
    {
        pre = slow;
        fast = fast->next->next;
        slow = slow->next;
    }
    if (pre != nullptr)
        pre->next = nullptr;
    student* left = h;
    student* right = slow;
    left = mergeSortRecur(left, op);
    right = mergeSortRecur(right, op);
    return Merge(left, right, op);
}

void record::Mergesort(int op)
{
    m_head = mergeSortRecur(m_head, op);
}

void record::Printall() const
{
    if (m_head == nullptr)
    {
        cout << "没有学生信息，无法输出\n";
        return;
    }
    student* p = m_head;
    while (p != nullptr)
    {
        cout << "\n学号：" << p->id << "\t姓名：" << p->name << "\t性别：" << p->sex << "\t专业：" << p->major << "\t班级：" << p->classes;
        cout << "\n学习时长:" << p->studytime << "\t成绩：" << p->score << '\n';
        p = p->next;
    }
    cout << "总人数：" << m_count << '\n';
}

void record::MajorRecordFind(const string& x) const
{
    if (m_head == nullptr)
    {
        cout << "没有学生信息，无法查询统计\n";
        return;
    }
    student* p = m_head;
    int count = 0;
    while (p != nullptr)
    {
        if (p->major == x)
        {
            count++;
            cout << "\n学号：" << p->id << "\t姓名：" << p->name << "\t性别：" << p->sex << "\t专业：" << p->major << "\t班级：" << p->classes;
            cout << "\n学习时长:" << p->studytime << "\t成绩：" << p->score << '\n';
        }
        p = p->next;
    }
    if (count == 0)
    {
        cout << "没有找到该专业的学生，请查看输入专业是否正确\n";
        return;
    }
    cout << "总人数：" << count << '\n';
}

void record::ClasRecordFind(const string& x) const
{
    if (m_head == nullptr)
    {
        cout << "没有学生信息，无法查询统计\n";
        return;
    }
    student* p = m_head;
    int count = 0;
    while (p != nullptr)
    {
        if (p->classes == x)
        {
            count++;
            cout << "\n学号：" << p->id << "\t姓名：" << p->name << "\t性别：" << p->sex << "\t专业：" << p->major << "\t班级：" << p->classes;
            cout << "\n学习时长:" << p->studytime << "\t成绩：" << p->score << '\n';
        }
        p = p->next;
    }
    if (count == 0)
    {
        cout << "没有找到该班级的学生，请查看输入班级是否正确\n";
        return;
    }
    cout << "总人数：" << count << '\n';
}

void record::SexRecordFind(const string& x) const
{
    if (m_head == nullptr)
    {
        cout << "没有学生信息，无法查询统计\n";
        return;
    }
    student* p = m_head;
    int count = 0;
    while (p != nullptr)
    {
        if (p->sex == x)
        {
            count++;
            cout << "\n学号：" << p->id << "\t姓名：" << p->name << "\t性别：" << p->sex << "\t专业：" << p->major << "\t班级：" << p->classes;
            cout << "\n学习时长:" << p->studytime << "\t成绩：" << p->score << '\n';
        }
        p = p->next;
    }
    if (count == 0)
    {
        cout << "没有找到该性别的学生，请查看输入性别是否正确\n";
        return;
    }
    cout << "总人数：" << count << '\n';
}

void record::AgeRecordFind(int x) const
{
    if (m_head == nullptr)
    {
        cout << "没有学生信息，无法查询统计\n";
        return;
    }
    student* p = m_head;
    int count = 0;
    while (p != nullptr)
    {
        if (p->age == x)
        {
            count++;
            cout << "\n学号：" << p->id << "\t姓名：" << p->name << "\t性别：" << p->sex << "\t专业：" << p->major << "\t班级：" << p->classes;
            cout << "\n学习时长:" << p->studytime << "\t成绩：" << p->score << '\n';
        }
        p = p->next;
    }
    if (count == 0)
    {
        cout << "没有找到该年龄的学生，请查看输入年龄是否正确\n";
        return;
    }
    cout << "总人数：" << count << '\n';
}

void record::SaveRecordFile() const
{
    ofstream ofile("student.dat");
    if (!ofile)
    {
        cout << "文件打开错误，无法写入\n";
        return;
    }
    student* p = m_head;
    while (p != nullptr)
    {
        ofile << p->id << '\t' << p->name << '\t' << p->sex << '\t' << p->age
              << '\t' << p->major << '\t' << p->classes
              << '\t' << p->studytime << '\t' << p->score << '\n';
        p = p->next;
    }
    ofile.close();
    cout << "保存成功，共 " << m_count << " 条记录\n";
}

void record::LoadRecordFile()
{
    DestroyList();
    m_head = nullptr;
    m_count = 0;

    ifstream ifile("student.dat");
    if (!ifile)
    {
        cout << "文件打开错误，无法读取\n";
        return;
    }

    student* tail = nullptr;
    int id, age, studytime;
    string name, sex, major, classes, score;
    while (ifile >> id >> name >> sex >> age >> major >> classes >> studytime >> score)
    {
        student* newStu = new student;
        newStu->id = id;
        newStu->name = name;
        newStu->sex = sex;
        newStu->age = age;
        newStu->major = major;
        newStu->classes = classes;
        newStu->studytime = studytime;
        newStu->score = score;
        newStu->next = nullptr;
        if (m_head == nullptr)
        {
            m_head = newStu;
            tail = newStu;
        }
        else
        {
            tail->next = newStu;
            tail = newStu;
        }
        m_count++;
    }
    ifile.close();
    cout << "加载成功，共 " << m_count << " 条记录\n";
}

void record::DestroyList()
{
    student* p = m_head;
    while (p != nullptr)
    {
        student* temp = p;
        p = p->next;
        delete temp;
    }
    m_head = nullptr;
    m_count = 0;
}

void record::ClearList()
{
    DestroyList();
}

int record::GetCount() const
{
    return m_count;
}

bool record::IsIdExist(int id) const
{
    student* p = m_head;
    while (p != nullptr)
    {
        if (p->id == id)
            return true;
        p = p->next;
    }
    return false;
}

void record::FindByNameKMP(const string& keyword) const
{
    if (m_head == nullptr)
    {
        cout << "没有学生信息，无法查询\n";
        return;
    }
    if (keyword.empty())
    {
        cout << "请输入非空关键字\n";
        return;
    }
    vector<int> next(keyword.size(), 0);
    for (int i = 1, j = 0; i < (int)keyword.size(); i++)
    {
        while (j > 0 && keyword[i] != keyword[j])
            j = next[j - 1];
        if (keyword[i] == keyword[j])
            j++;
        next[i] = j;
    }
    student* p = m_head;
    int count = 0;
    while (p != nullptr)
    {
        int i = 0, j = 0;
        while (i < (int)p->name.size() && j < (int)keyword.size())
        {
            if (p->name[i] == keyword[j])
            {
                i++; j++;
            }
            else if (j > 0)
            {
                j = next[j - 1];
            }
            else
            {
                i++;
            }
            if (j == (int)keyword.size())
            {
                count++;
                cout << "\n学号：" << p->id << "\t姓名：" << p->name << "\t性别：" << p->sex << "\t专业：" << p->major << "\t班级：" << p->classes;
                cout << "\n学习时长:" << p->studytime << "\t成绩：" << p->score << '\n';
                break;
            }
        }
        p = p->next;
    }
    if (count == 0)
    {
        cout << "没有找到姓名包含该关键字的学生\n";
        return;
    }
    cout << "总人数：" << count << '\n';
}

void record::PrintPage(int pageSize, int pageNum) const
{
    if (m_head == nullptr)
    {
        cout << "没有学生信息，无法查询\n";
        return;
    }
    if (pageSize <= 0)
    {
        cout << "每页记录数必须大于0\n";
        return;
    }
    int total = m_count;
    int totalPages = (total + pageSize - 1) / pageSize;
    if (pageNum < 1 || pageNum > totalPages)
    {
        cout << "页码错误，请输入1到" << totalPages << "之间的页码\n";
        return;
    }
    int start = (pageNum - 1) * pageSize;
    int end = min(start + pageSize, total);
    student* p = m_head;
    for (int i = 0; i < start && p != nullptr; i++)
        p = p->next;
    for (int i = start; i < end && p != nullptr; i++)
    {
        cout << "\n学号：" << p->id << "\t姓名：" << p->name << "\t性别：" << p->sex << "\t专业：" << p->major << "\t班级：" << p->classes;
        cout << "\n学习时长:" << p->studytime << "\t成绩：" << p->score << '\n';
        p = p->next;
    }
    cout << "当前页码：" << pageNum << "/" << totalPages << "\t每页记录数：" << pageSize << "\t总记录数：" << total << '\n';
}

void record::Reverse()
{
    student* prev = nullptr;
    student* curr = m_head;
    while (curr != nullptr)
    {
        student* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    m_head = prev;
}

void record::RemoveDuplicates()
{
    if (m_head == nullptr)
        return;
    student* p = m_head;
    while (p->next != nullptr)
    {
        if (p->id == p->next->id)
        {
            student* temp = p->next;
            p->next = p->next->next;
            delete temp;
            m_count--;
        }
        else
        {
            p = p->next;
        }
    }
}

void record::DeleteByCondition()
{
    if (permission == "学生")
    {
        cout << "权限不足，无法删除学生信息\n";
        return;
    }
    if (m_head == nullptr)
    {
        cout << "没有学生信息，无法删除\n";
        return;
    }

    while (true)
    {
        cout << "|-------------------------\n";
        cout << "|请选择删除条件：\n";
        cout << "|1.根据专业删除\n";
        cout << "|2.根据班级删除\n";
        cout << "|3.根据性别删除\n";
        cout << "|4.根据年龄删除\n";
        cout << "|0.退出\n";
        cout << "|-------------------------\n";
        int op = 0;
        cin >> op;

        if (op == 0)
        {
            cout << "已经退出批量删除界面\n";
            return;
        }
        if (op < 1 || op > 4)
        {
            cout << "错误指令，请重新输入\n";
            continue;
        }

        string keyword;
        int ageKeyword = 0;
        if (op == 1)
        {
            cout << "请输入专业：";
            cin >> keyword;
        }
        else if (op == 2)
        {
            cout << "请输入班级：";
            cin >> keyword;
        }
        else if (op == 3)
        {
            cout << "请输入性别：";
            cin >> keyword;
        }
        else if (op == 4)
        {
            cout << "请输入年龄：";
            cin >> ageKeyword;
        }

        student* dummy = new student;
        dummy->next = m_head;
        student* p2 = dummy;
        student* p1 = m_head;
        int deleteCount = 0;

        while (p1 != nullptr)
        {
            bool match = false;
            if (op == 1 && p1->major == keyword)
                match = true;
            else if (op == 2 && p1->classes == keyword)
                match = true;
            else if (op == 3 && p1->sex == keyword)
                match = true;
            else if (op == 4 && p1->age == ageKeyword)
                match = true;

            if (match)
            {
                student* temp = p1;
                p2->next = p1->next;
                p1 = p2->next;
                delete temp;
                m_count--;
                deleteCount++;
            }
            else
            {
                p2 = p1;
                p1 = p1->next;
            }
        }
        m_head = dummy->next;
        delete dummy;
        if (deleteCount == 0)
        {
            cout << "没有找到满足条件的学生信息\n";
        }
        else
        {
            cout << "成功删除 " << deleteCount << " 条学生信息\n";
        }
    }
}

void record::ShowSummary() const
{
    if (m_head == nullptr)
    {
        cout << "没有学生信息，无法显示汇总\n";
        return;
    }
    int total = m_count;
    int maleCount = 0, femaleCount = 0;
    unordered_map<string, int> majorCount;
    unordered_map<string, int> classCount;
    student* p = m_head;
    while (p != nullptr)
    {
        if (p->sex == "男")
            maleCount++;
        else if (p->sex == "女")
            femaleCount++;
        majorCount[p->major]++;
        classCount[p->classes]++;
        p = p->next;
    }
    cout << "总人数：" << total << '\n';
    cout << "男女比例：" << maleCount << ":" << femaleCount << '\n';
    cout << "专业分布：\n";
    for (const auto& pair : majorCount)
        cout << pair.first << ":" << pair.second << '\n';
    cout << "班级分布：\n";
    for (const auto& pair : classCount)
        cout << pair.first << ":" << pair.second << '\n';
}

void record::AppendFromFile(const string& filename)
{
    ifstream ifile(filename);
    if (!ifile)
    {
        cout << "文件打开错误，无法读取\n";
        return;
    }

    student* tail = m_head;
    if (tail != nullptr)
    {
        while (tail->next != nullptr)
            tail = tail->next;
    }

    int id, age, studytime;
    string name, sex, major, classes, score;
    while (ifile >> id >> name >> sex >> age >> major >> classes >> studytime >> score)
    {
        if (IsIdExist(id))
        {
            cout << "学号 " << id << " 已存在，跳过该记录\n";
            continue;
        }
        student* newStu = new student;
        newStu->id = id;
        newStu->name = name;
        newStu->sex = sex;
        newStu->age = age;
        newStu->major = major;
        newStu->classes = classes;
        newStu->studytime = studytime;
        newStu->score = score;
        newStu->next = nullptr;
        if (tail == nullptr)
        {
            m_head = newStu;
        }
        else
        {
            tail->next = newStu;
        }
        tail = newStu;
        m_count++;
    }
    ifile.close();
}

void record::ExportToCSV(const string& filename) const
{
    ofstream ofile(filename);
    if (!ofile)
    {
        cout << "文件打开错误，无法写入\n";
        return;
    }
    ofile << "学号,姓名,性别,年龄,专业,班级,学习时间,成绩\n";
    student* p = m_head;
    while (p != nullptr)
    {
        ofile << p->id << ',' << p->name << ',' << p->sex << ',' << p->age
              << ',' << p->major << ',' << p->classes
              << ',' << p->studytime << ',' << p->score << '\n';
        p = p->next;
    }
    ofile.close();
    cout << "导出成功，文件名：" << filename << '\n';
}

void record::Backup() const
{
    if (m_head == nullptr)
    {
        cout << "无数据可备份\n";
        return;
    }
    time_t now = time(nullptr);
    tm* local = localtime(&now);
    char filename[100];
    strftime(filename, sizeof(filename), "backup_%Y%m%d_%H%M%S.txt", local);
    ofstream ofile(filename);
    if (!ofile)
    {
        cout << "备份文件创建失败\n";
        return;
    }
    student* p = m_head;
    while (p != nullptr)
    {
        ofile << p->id << '\t' << p->name << '\t' << p->sex << '\t' << p->age
              << '\t' << p->major << '\t' << p->classes
              << '\t' << p->studytime << '\t' << p->score << '\n';
        p = p->next;
    }
    ofile.close();
    cout << "备份成功，文件：" << filename << endl;
}

void record::Restore(const string& backupFile)
{
    DestroyList();
    m_head = nullptr;
    m_count = 0;

    ifstream ifile(backupFile);
    if (!ifile)
    {
        cout << "备份文件打开失败：" << backupFile << endl;
        return;
    }

    student* tail = nullptr;
    int id, age, studytime;
    string name, sex, major, classes, score;
    while (ifile >> id >> name >> sex >> age >> major >> classes >> studytime >> score)
    {
        student* newStu = new student;
        newStu->id = id;
        newStu->name = name;
        newStu->sex = sex;
        newStu->age = age;
        newStu->major = major;
        newStu->classes = classes;
        newStu->studytime = studytime;
        newStu->score = score;
        newStu->next = nullptr;
        if (m_head == nullptr)
        {
            m_head = newStu;
            tail = newStu;
        }
        else
        {
            tail->next = newStu;
            tail = newStu;
        }
        m_count++;
    }
    ifile.close();
    if (m_count == 0)
        cout << "备份文件中无有效记录\n";
    else
        cout << "恢复成功，共加载 " << m_count << " 条记录\n";
}
