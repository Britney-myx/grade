#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>  // 添加Windows头文件支持system和Sleep

#define MAX_NAME_LEN 20
#define FILE_NAME "text.txt"  // 统一文件名

typedef struct Student {
    int num;
    char name[MAX_NAME_LEN];
    float score1, score2, score3;
    float total;
    struct Student* next;
} STU;

// 全局变量声明
char filename[20] = { 0 };  // 正确初始化

// 函数声明
int MainInterface();
STU* CreateList();
int NumIsExist(STU* plist, int num);
void InsertStu(STU* plist);
void SerchByNum(STU* plist);
void SerchByName(STU* plist);
void DelectStu(STU* plist);
void MosifyStu(STU* plist);
STU* OpenStuFile();
void CloseStuFile(STU* plist);

int MainInterface() {
    system("cls");
    int key;
    printf("欢迎来到学生成绩管理系统\n");
    printf("1. 录入学员\n");
    printf("2. 查找学员\n");
    printf("3. 删除学员\n");
    printf("4. 修改成绩\n");
    printf("5. 打开文件\n");
    printf("0. 退出系统\n");
    printf("请选择：");
    scanf_s("%d", &key);
    return key;
}

STU* CreateList() {
    STU* p = (STU*)malloc(sizeof(STU));
    if (!p) {
        printf("内存分配失败！\n");
        exit(1);
    }
    p->next = NULL;
    return p;
}

int NumIsExist(STU* plist, int num) {
    STU* p = plist->next;  // 应从第一个节点开始查找
    while (p) {
        if (p->num == num)
            return 1;
        p = p->next;
    }
    return 0;
}

void InsertStu(STU* plist) {
    system("cls");
    printf("正在录入学员信息\n");
    STU* p = plist;
    int count = 0;

    printf("请输入需要添加多少学员：");
    scanf_s("%d", &count);
    if (count <= 0) {
        printf("输入数量必须大于0！\n");
        system("pause");
        return;
    }

    for (int i = 0; i < count; i++) {
        STU* pnew = (STU*)malloc(sizeof(STU));
        if (!pnew) {
            printf("内存分配失败！\n");
            system("pause");
            return;
        }

        // 输入学号
        do {
            printf("请输入学生学号：");
            scanf_s("%d", &pnew->num);
        } while (NumIsExist(plist, pnew->num));  // 循环直到学号唯一

        // 输入姓名
        printf("请输入学生姓名：");
        scanf_s("%s", pnew->name,(unsigned)_countof(pnew->name));

        // 输入成绩
        printf("请输入成绩1：");
        scanf_s("%f", &pnew->score1);
        printf("请输入成绩2：");
        scanf_s("%f", &pnew->score2);
        printf("请输入成绩3：");
        scanf_s("%f", &pnew->score3);

        pnew->total = pnew->score1 + pnew->score2 + pnew->score3;  // 修复总分计算错误
        pnew->next = NULL;

        // 按学号有序插入（保持链表有序）
        while (p->next && p->next->num < pnew->num) {
            p = p->next;
        }
        pnew->next = p->next;
        p->next = pnew;
    }
    printf("录入完成！\n");
    system("pause");
}

void SerchByNum(STU* plist) {
    system("cls");
    int num = 0;
    printf("请输入学员学号：");
    scanf_s("%d", &num);

    STU* p = plist->next;
    while (p) {
        if (p->num == num) {
            printf("学号: %d\n姓名: %s\n成绩1: %.1f\n成绩2: %.1f\n成绩3: %.1f\n总分: %.1f\n",
                p->num, p->name, p->score1, p->score2, p->score3, p->total);
            system("pause");
            return;
        }
        p = p->next;
    }
    printf("未找到该学生！\n");
    system("pause");
}

void SerchByName(STU* plist) {
    system("cls");
    char name[MAX_NAME_LEN] = { 0 };
    printf("请输入学生姓名：");
    scanf_s("%s", name,(unsigned)_countof(name));

    STU* p = plist->next;
    int count = 0;
    while (p) {
        if (strcmp(p->name, name) == 0) {
            count++;
            printf("学号: %d\n姓名: %s\n成绩1: %.1f\n成绩2: %.1f\n成绩3: %.1f\n总分: %.1f\n",
                p->num, p->name, p->score1, p->score2, p->score3, p->total);
        }
        p = p->next;
    }
    if (count == 0)
        printf("未找到该学生！\n");
    else
        printf("共找到%d条记录\n", count);
    system("pause");
}

void DelectStu(STU* plist) {
    system("cls");
    int num = 0;
    char key = 'F';
    STU* pre = plist;
    STU* p = plist->next;

    printf("请输入需要删除的学号：");
    scanf_s("%d", &num);

    while (p) {
        if (p->num == num) {
            printf("学号: %d\n姓名: %s\n成绩1: %.1f\n成绩2: %.1f\n成绩3: %.1f\n总分: %.1f\n",
                p->num, p->name, p->score1, p->score2, p->score3, p->total);

            printf("是否删除？(T/F)");
            getchar();
            scanf_s(" %c", &key,1);  // 吸收空白字符

            if (key == 'T') {
                pre->next = p->next;
                free(p);
                p = pre->next;  // 移动指针
                printf("删除成功！\n");
            }
            else {
                printf("取消删除！\n");
            }
            system("pause");
            return;
        }
        pre = p;
        p = p->next;
    }
    printf("未找到该学生！\n");
    system("pause");
}

void MosifyStu(STU* plist) {
    system("cls");
    int num = 0;
    char key = 'F';
    STU* p = plist->next;

    printf("请输入需要修改的学号：");
    scanf_s("%d", &num);

    while (p) {
        if (p->num == num) {
            printf("学号: %d\n姓名: %s\n成绩1: %.1f\n成绩2: %.1f\n成绩3: %.1f\n总分: %.1f\n",
                p->num, p->name, p->score1, p->score2, p->score3, p->total);

            printf("是否修改？(T/F)");
            getchar();
            scanf_s(" %c", &key,1);

            if (key == 'T') {
                printf("1.修改姓名\n2.修改成绩1\n3.修改成绩2\n4.修改成绩3\n0.退出");
                scanf_s(" %c", &key,1);

                switch (key) {
                case '1':
                    printf("请输入新姓名：");
                    scanf_s("%s", p->name,(unsigned)_countof(p->name));
                    break;
                case '2':
                    printf("请输入新成绩1：");
                    scanf_s("%f", &p->score1);
                    break;
                case '3':
                    printf("请输入新成绩2：");
                    scanf_s("%f", &p->score2);
                    break;
                case '4':
                    printf("请输入新成绩3：");
                    scanf_s("%f", &p->score3);
                    p->total = p->score1 + p->score2 + p->score3;  // 更新总分
                    break;
                default:
                    printf("无效选择！\n");
                }
                printf("修改后信息：\n");
                printf("学号: %d\n姓名: %s\n成绩1: %.1f\n成绩2: %.1f\n成绩3: %.1f\n总分: %.1f\n",
                    p->num, p->name, p->score1, p->score2, p->score3, p->total);
                system("pause");
                return;
            }
            else {
                printf("取消修改！\n");
            }
            break;
        }
        p = p->next;
    }
    printf("未找到该学生！\n");
    system("pause");
}

/* STU* OpenStuFile() {
    int key;
    FILE* filePtr;
    errno_t err;
    char butter[100];
    err = fopen_s(&filePtr, "text.txt", "r");
    if (err==0) {
        
        printf("文件已存在，正在加载数据...\n");
        STU* plist = CreateList();
        STU* pnew = plist;


        while (fscanf_s(filePtr, "%d%s%f%f%f%f",
            &pnew->num, pnew->name,
            &pnew->score1, &pnew->score2,
            &pnew->score3, &pnew->total) == 0) {
            // 插入链表（保持有序）
            while (pnew->next && pnew->next->num < pnew->num) {
                pnew = pnew->next;
            }
            pnew->next = plist->next;
            plist->next = pnew;
            pnew = plist;  // 重置指针
        }
        fclose(filePtr);
        printf("数据加载完成！\n");
        return plist;
    }

    printf("文件不存在！是否创建？(T/F)");
    getchar();
    scanf_s(" %c", &key);

    if (key == 'T') {
        errno_t err = fopen_s(&filePtr,FILE_NAME, "w");
        if (err==0) {
            printf("文件创建成功！\n");
            fclose(filePtr);
            return CreateList();
        }
        else {
            printf("创建文件失败！\n");
            system("pause");
            exit(1);
        }
    }
    else {
        printf("操作取消！\n");
        system("pause");
        exit(1);
    }
}

void CloseStuFile(STU* plist) {
    FILE* fp;
        errno_t err= fopen_s(&fp,FILE_NAME, "w");
    if (!fp) {
        printf("无法打开文件保存！\n");
        return;
    }

    STU* p = plist->next;
    while (p) {
        fprintf(fp, "%d\t%s\t%.1f\t%.1f\t%.1f\t%.1f\n",
            p->num, p->name, p->score1, p->score2, p->score3, p->total);
        p = p->next;
    }
    fclose(fp);
    printf("数据保存成功！\n");
}*/
STU* OpenStuFile() {
    int key;
    FILE* filePtr;
    errno_t err;
    char buffer[100];
    err = fopen_s(&filePtr, FILE_NAME, "r");  // 改为 "r" 模式，用于读取文件
    if (err == 0) {
        printf("文件已存在，正在加载数据...\n");
        STU* plist = CreateList();
        STU* pnew;

        while (1) {
            pnew = (STU*)malloc(sizeof(STU));
            if (fscanf_s(filePtr, "%d%s%f%f%f%f",
                &pnew->num, pnew->name, (unsigned)_countof(pnew->name),
                &pnew->score1, &pnew->score2,
                &pnew->score3, &pnew->total) != 0) {
                free(pnew);
                break;
            }
            // 插入链表（保持有序）
            STU* prev = plist;
            while (prev->next && prev->next->num < pnew->num) {
                prev = prev->next;
            }
            pnew->next = prev->next;
            prev->next = pnew;
        }
        fclose(filePtr);
        printf("数据加载完成！\n");
        return plist;
    }
    else {
        perror("打开文件失败");  // 输出具体的错误信息
        printf("文件不存在！是否创建？(T/F)");
        getchar();
        scanf_s(" %c", &key);

        if (key == 'T') {
            err = fopen_s(&filePtr, FILE_NAME, "w");
            if (err == 0) {
                printf("文件创建成功！\n");
                fclose(filePtr);
                return CreateList();
            }
            else {
                perror("创建文件失败");  // 输出具体的错误信息
                system("pause");
                exit(1);
            }
        }
        else {
            printf("操作取消！\n");
            system("pause");
            exit(1);
        }
    }
}

void CloseStuFile(STU* plist) {
    FILE* fp;
    errno_t err = fopen_s(&fp, FILE_NAME, "w");  // 改为 "w" 模式，用于写入文件
    if (err != 0) {
        perror("无法打开文件保存");  // 输出具体的错误信息
        return;
    }

    STU* p = plist->next;
    while (p) {
        fprintf(fp, "%d\t%s\t%.1f\t%.1f\t%.1f\t%.1f\n",
            p->num, p->name, p->score1, p->score2, p->score3, p->total);
        p = p->next;
    }
    fclose(fp);
    printf("数据保存成功！\n");
}


int main() {
    STU* plist = OpenStuFile();
    if (!plist) return 1;

    int key;
    while (1) {
        key = MainInterface();
        if (key == 0) break;

        switch (key) {
        case 1: InsertStu(plist); break;
        case 2: SerchByNum(plist); break;
        case 3: DelectStu(plist); break;
        case 4: MosifyStu(plist); break;
        case 5: plist = OpenStuFile(); break;
        }
    }

    CloseStuFile(plist);
    // 释放内存
    while (plist) {
        STU* temp = plist;
        plist = plist->next;
        free(temp);
    }
    return 0;
}