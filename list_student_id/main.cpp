#include"studentList.h"
#include<fstream>
using namespace std;

int main() {
	
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    record manager;// 创建管理对象，构造时会询问权限
    
    // 尝试加载已有数据文件（可选）
    head = manager.LoadRecordFile(head);
    
    int choice;
    while (true) {
        cout << "\n========== 学生信息管理系统 ==========\n";
        cout << "1. 插入学生信息\n";
        cout << "2. 删除学生信息\n";
        cout << "3. 修改学生信息\n";
        cout << "4. 查找学生信息\n";
        cout << "5. 统计学生信息\n";
        cout << "6. 显示所有学生信息\n";
        cout << "7. 分页显示学生信息\n";
        cout << "8. 排序学生信息\n";
        cout << "9. 保存学生信息到文件\n";
        cout << "10. 从文件加载学生信息\n";
        cout << "11. 从文件追加学生记录\n";
        cout << "12. 导出为CSV文件\n";
        cout << "13. 备份当前数据\n";
        cout << "14. 从备份文件恢复数据\n";
        cout << "15. 反转学生链表\n";
        cout << "16. 删除重复学号节点\n";
        cout << "17. 批量条件删除\n";
        cout << "18. 显示汇总信息\n";
        cout << "19. 模糊查找姓名(KMP)\n";
        cout << "20. 获取学生总数\n";
        cout << "21. 检查学号是否存在\n";
        cout << "22. 清空所有学生记录\n";
        cout << "0. 退出系统\n";
        cout << "请选择操作: ";
        cin >> choice;
        
        if (choice == 0) break;
        
        switch (choice) {
            case 1:
                head = manager.Insertstu(head);
                break;
            case 2:
                head = manager.Deletestu(head);
                break;
            case 3:
                head = manager.Changestu(head);
                break;
            case 4: {
                cout << "查找方式：1.按学号  2.按姓名: ";
                int way; cin >> way;
                if (way == 1) {
                    int id; cout << "学号: "; cin >> id;
                    student* s = manager.Findstu(head, id);
                    if (s) {
                        cout << "\n学号：" << s->id << "\t姓名：" << s->name
                             << "\t性别：" << s->sex << "\t专业：" << s->major
                             << "\t班级：" << s->classes
                             << "\n学习时长:" << s->studytime << "\t成绩：" << s->score << '\n';
                    }
                } else {
                    string name; cout << "姓名: "; cin >> name;
                    student* s = manager.Findstu(head, name);
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
                    manager.MajorRecordFind(head, major);
                } else if (way == 2) {
                    string cls; cout << "班级: "; cin >> cls;
                    manager.ClasRecordFind(head, cls);
                } else if (way == 3) {
                    string sex; cout << "性别: "; cin >> sex;
                    manager.SexRecordFind(head, sex);
                } else if (way == 4) {
                    int age; cout << "年龄: "; cin >> age;
                    manager.AgeRecordFind(head, age);
                }
                break;
            }
            case 6:
                manager.Printall(head);
                break;
            case 7: {
                int pageSize, pageNum;
                cout << "每页记录数: "; cin >> pageSize;
                cout << "页码: "; cin >> pageNum;
                manager.PrintPage(head, pageSize, pageNum);
                break;
            }
            case 8: {
                cout << "排序依据：1.姓名  2.学号  3.专业+班级: ";
                int op; cin >> op;
                head = manager.Mergesort(head, op);
                cout << "排序完成。\n";
                break;
            }
            case 9:
                manager.SaveRecordFile(head);
                break;
            case 10:
                head = manager.LoadRecordFile(head);
                break;
            case 11: {
                string filename;
                cout << "输入追加文件名: "; cin >> filename;
                head = manager.AppendFromFile(head, filename);
                break;
            }
            case 12: {
                string filename;
                cout << "输入CSV文件名: "; cin >> filename;
                manager.ExportToCSV(head, filename);
                break;
            }
            case 13:
                manager.Backup(head);
                break;
            case 14: {
                string filename;
                cout << "输入备份文件名: "; cin >> filename;
                head = manager.Restore(filename);   // 假定已实现
                break;
            }
            case 15:
                head = manager.Reverse(head);
                cout << "链表已反转。\n";
                break;
            case 16:
                head = manager.RemoveDuplicates(head);
                cout << "重复节点已删除（需已排序或改为哈希方式）。\n";
                break;
            case 17:
                head = manager.DeleteByCondition(head);
                break;
            case 18:
                manager.ShowSummary(head);
                break;
            case 19: {
                string keyword;
                cout << "输入姓名关键字: "; cin >> keyword;
                manager.FindByNameKMP(head, keyword);
                break;
            }
            case 20:
                cout << "当前学生总数: " << manager.GetCount(head) << endl;
                break;
            case 21: {
                int id; cout << "输入学号: "; cin >> id;
                if (manager.IsIdExist(head, id))
                    cout << "学号 " << id << " 已存在。\n";
                else
                    cout << "学号 " << id << " 不存在。\n";
                break;
            }
            case 22:
                manager.ClearList(head);
                cout << "链表已清空。\n";
                break;
            default:
                cout << "无效选项，请重新输入。\n";
        }
    }
    
    // 退出前释放所有节点，防止内存泄漏
    manager.DestroyList(head);
    head = NULL;
    cout << "系统已退出，内存已释放。\n";
    return 0;
}