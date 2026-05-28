#include "studentList.h"
#include <fstream>
using namespace std;

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    //cout.tie(nullptr);

    record manager; // 创建管理对象，构造时会询问权限
    manager.LoadRecordFile(); // 尝试加载已有数据文件

    int choice;
    while (true) {
        cout << "\n========== 学生信息管理系统 ==========" << endl;
        cout << "1. 插入学生信息" << endl;
        cout << "2. 删除学生信息" << endl;
        cout << "3. 修改学生信息" << endl;
        cout << "4. 查找学生信息" << endl;
        cout << "5. 统计学生信息" << endl;
        cout << "6. 显示所有学生信息" << endl;
        cout << "7. 分页显示学生信息" << endl;
        cout << "8. 排序学生信息" << endl;
        cout << "9. 保存学生信息到文件" << endl;
        cout << "10. 从文件加载学生信息" << endl;
        cout << "11. 从文件追加学生记录" << endl;
        cout << "12. 导出为CSV文件" << endl;
        cout << "13. 备份当前数据" << endl;
        cout << "14. 从备份文件恢复数据" << endl;
        cout << "15. 反转学生链表" << endl;
        cout << "16. 删除重复学号节点" << endl;
        cout << "17. 批量条件删除" << endl;
        cout << "18. 显示汇总信息" << endl;
        cout << "19. 模糊查找姓名(KMP)" << endl;
        cout << "20. 获取学生总数" << endl;
        cout << "21. 检查学号是否存在" << endl;
        cout << "22. 清空所有学生记录" << endl;
        cout << "0. 退出系统" << endl;
        cout << "请选择操作: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1:
                manager.Insertstu();
                break;
            case 2:
                manager.Deletestu();
                break;
            case 3:
                manager.Changestu();
                break;
            case 4: {
                cout << "查找方式：1.按学号  2.按姓名: ";
                int way; cin >> way;
                if (way == 1) {
                    int id; cout << "学号: "; cin >> id;
                    student* s = manager.Findstu(id);
                    if (s) {
                        cout << "\n学号：" << s->id << "\t姓名：" << s->name
                             << "\t性别：" << s->sex << "\t专业：" << s->major
                             << "\t班级：" << s->classes
                             << "\n学习时长:" << s->studytime << "\t成绩：" << s->score << '\n';
                    }
                } else {
                    string name; cout << "姓名: "; cin >> name;
                    student* s = manager.Findstu(name);
                    if (s) {
                        cout << "\n学号：" << s->id << "\t姓名：" << s->name
                             << "\t性别：" << s->sex << "\t专业：" << s->major
                             << "\t班级：" << s->classes
                             << "\n学习时长:" << s->studytime << "\t成绩：" << s->score << '\n';
                    }
                }
                break;
            }
            case 5: {
                cout << "统计方式：1.专业  2.班级  3.性别  4.年龄: ";
                int way; cin >> way;
                if (way == 1) {
                    string major; cout << "专业: "; cin >> major;
                    manager.MajorRecordFind(major);
                } else if (way == 2) {
                    string cls; cout << "班级: "; cin >> cls;
                    manager.ClasRecordFind(cls);
                } else if (way == 3) {
                    string sex; cout << "性别: "; cin >> sex;
                    manager.SexRecordFind(sex);
                } else if (way == 4) {
                    int age; cout << "年龄: "; cin >> age;
                    manager.AgeRecordFind(age);
                }
                break;
            }
            case 6:
                manager.Printall();
                break;
            case 7: {
                int pageSize, pageNum;
                cout << "每页记录数: "; cin >> pageSize;
                cout << "页码: "; cin >> pageNum;
                manager.PrintPage(pageSize, pageNum);
                break;
            }
            case 8: {
                cout << "排序依据：1.姓名  2.学号  3.专业+班级: ";
                int op; cin >> op;
                manager.Mergesort(op);
                cout << "排序完成。\n";
                break;
            }
            case 9:
                manager.SaveRecordFile();
                break;
            case 10:
                manager.LoadRecordFile();
                break;
            case 11: {
                string filename;
                cout << "输入追加文件名: "; cin >> filename;
                manager.AppendFromFile(filename);
                break;
            }
            case 12: {
                string filename;
                cout << "输入CSV文件名: "; cin >> filename;
                manager.ExportToCSV(filename);
                break;
            }
            case 13:
                manager.Backup();
                break;
            case 14: {
                string filename;
                cout << "输入备份文件名: "; cin >> filename;
                manager.Restore(filename);
                break;
            }
            case 15:
                manager.Reverse();
                cout << "链表已反转。\n";
                break;
            case 16:
                manager.RemoveDuplicates();
                cout << "重复节点已删除（若列表已排序）。\n";
                break;
            case 17:
                manager.DeleteByCondition();
                break;
            case 18:
                manager.ShowSummary();
                break;
            case 19: {
                string keyword;
                cout << "输入姓名关键字: "; cin >> keyword;
                manager.FindByNameKMP(keyword);
                break;
            }
            case 20:
                cout << "当前学生总数: " << manager.GetCount() << endl;
                break;
            case 21: {
                int id; cout << "输入学号: "; cin >> id;
                if (manager.IsIdExist(id))
                    cout << "学号 " << id << " 已存在。\n";
                else
                    cout << "学号 " << id << " 不存在。\n";
                break;
            }
            case 22:
                manager.ClearList();
                cout << "链表已清空。\n";
                break;
            default:
                cout << "无效选项，请重新输入。\n";
        }
    }

    cout << "系统已退出，内存已释放。\n";
    return 0;
}
