#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>  // ���Windowsͷ�ļ�֧��system��Sleep

#define MAX_NAME_LEN 20
#define FILE_NAME "text.txt"  // ͳһ�ļ���

typedef struct Student {
    int num;
    char name[MAX_NAME_LEN];
    float score1, score2, score3;
    float total;
    struct Student* next;
} STU;

// ȫ�ֱ�������
char filename[20] = { 0 };  // ��ȷ��ʼ��

// ��������
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
    printf("��ӭ����ѧ���ɼ�����ϵͳ\n");
    printf("1. ¼��ѧԱ\n");
    printf("2. ����ѧԱ\n");
    printf("3. ɾ��ѧԱ\n");
    printf("4. �޸ĳɼ�\n");
    printf("5. ���ļ�\n");
    printf("0. �˳�ϵͳ\n");
    printf("��ѡ��");
    scanf_s("%d", &key);
    return key;
}

STU* CreateList() {
    STU* p = (STU*)malloc(sizeof(STU));
    if (!p) {
        printf("�ڴ����ʧ�ܣ�\n");
        exit(1);
    }
    p->next = NULL;
    return p;
}

int NumIsExist(STU* plist, int num) {
    STU* p = plist->next;  // Ӧ�ӵ�һ���ڵ㿪ʼ����
    while (p) {
        if (p->num == num)
            return 1;
        p = p->next;
    }
    return 0;
}

void InsertStu(STU* plist) {
    system("cls");
    printf("����¼��ѧԱ��Ϣ\n");
    STU* p = plist;
    int count = 0;

    printf("��������Ҫ��Ӷ���ѧԱ��");
    scanf_s("%d", &count);
    if (count <= 0) {
        printf("���������������0��\n");
        system("pause");
        return;
    }

    for (int i = 0; i < count; i++) {
        STU* pnew = (STU*)malloc(sizeof(STU));
        if (!pnew) {
            printf("�ڴ����ʧ�ܣ�\n");
            system("pause");
            return;
        }

        // ����ѧ��
        do {
            printf("������ѧ��ѧ�ţ�");
            scanf_s("%d", &pnew->num);
        } while (NumIsExist(plist, pnew->num));  // ѭ��ֱ��ѧ��Ψһ

        // ��������
        printf("������ѧ��������");
        scanf_s("%s", pnew->name,(unsigned)_countof(pnew->name));

        // ����ɼ�
        printf("������ɼ�1��");
        scanf_s("%f", &pnew->score1);
        printf("������ɼ�2��");
        scanf_s("%f", &pnew->score2);
        printf("������ɼ�3��");
        scanf_s("%f", &pnew->score3);

        pnew->total = pnew->score1 + pnew->score2 + pnew->score3;  // �޸��ּܷ������
        pnew->next = NULL;

        // ��ѧ��������루������������
        while (p->next && p->next->num < pnew->num) {
            p = p->next;
        }
        pnew->next = p->next;
        p->next = pnew;
    }
    printf("¼����ɣ�\n");
    system("pause");
}

void SerchByNum(STU* plist) {
    system("cls");
    int num = 0;
    printf("������ѧԱѧ�ţ�");
    scanf_s("%d", &num);

    STU* p = plist->next;
    while (p) {
        if (p->num == num) {
            printf("ѧ��: %d\n����: %s\n�ɼ�1: %.1f\n�ɼ�2: %.1f\n�ɼ�3: %.1f\n�ܷ�: %.1f\n",
                p->num, p->name, p->score1, p->score2, p->score3, p->total);
            system("pause");
            return;
        }
        p = p->next;
    }
    printf("δ�ҵ���ѧ����\n");
    system("pause");
}

void SerchByName(STU* plist) {
    system("cls");
    char name[MAX_NAME_LEN] = { 0 };
    printf("������ѧ��������");
    scanf_s("%s", name,(unsigned)_countof(name));

    STU* p = plist->next;
    int count = 0;
    while (p) {
        if (strcmp(p->name, name) == 0) {
            count++;
            printf("ѧ��: %d\n����: %s\n�ɼ�1: %.1f\n�ɼ�2: %.1f\n�ɼ�3: %.1f\n�ܷ�: %.1f\n",
                p->num, p->name, p->score1, p->score2, p->score3, p->total);
        }
        p = p->next;
    }
    if (count == 0)
        printf("δ�ҵ���ѧ����\n");
    else
        printf("���ҵ�%d����¼\n", count);
    system("pause");
}

void DelectStu(STU* plist) {
    system("cls");
    int num = 0;
    char key = 'F';
    STU* pre = plist;
    STU* p = plist->next;

    printf("��������Ҫɾ����ѧ�ţ�");
    scanf_s("%d", &num);

    while (p) {
        if (p->num == num) {
            printf("ѧ��: %d\n����: %s\n�ɼ�1: %.1f\n�ɼ�2: %.1f\n�ɼ�3: %.1f\n�ܷ�: %.1f\n",
                p->num, p->name, p->score1, p->score2, p->score3, p->total);

            printf("�Ƿ�ɾ����(T/F)");
            getchar();
            scanf_s(" %c", &key,1);  // ���տհ��ַ�

            if (key == 'T') {
                pre->next = p->next;
                free(p);
                p = pre->next;  // �ƶ�ָ��
                printf("ɾ���ɹ���\n");
            }
            else {
                printf("ȡ��ɾ����\n");
            }
            system("pause");
            return;
        }
        pre = p;
        p = p->next;
    }
    printf("δ�ҵ���ѧ����\n");
    system("pause");
}

void MosifyStu(STU* plist) {
    system("cls");
    int num = 0;
    char key = 'F';
    STU* p = plist->next;

    printf("��������Ҫ�޸ĵ�ѧ�ţ�");
    scanf_s("%d", &num);

    while (p) {
        if (p->num == num) {
            printf("ѧ��: %d\n����: %s\n�ɼ�1: %.1f\n�ɼ�2: %.1f\n�ɼ�3: %.1f\n�ܷ�: %.1f\n",
                p->num, p->name, p->score1, p->score2, p->score3, p->total);

            printf("�Ƿ��޸ģ�(T/F)");
            getchar();
            scanf_s(" %c", &key,1);

            if (key == 'T') {
                printf("1.�޸�����\n2.�޸ĳɼ�1\n3.�޸ĳɼ�2\n4.�޸ĳɼ�3\n0.�˳�");
                scanf_s(" %c", &key,1);

                switch (key) {
                case '1':
                    printf("��������������");
                    scanf_s("%s", p->name,(unsigned)_countof(p->name));
                    break;
                case '2':
                    printf("�������³ɼ�1��");
                    scanf_s("%f", &p->score1);
                    break;
                case '3':
                    printf("�������³ɼ�2��");
                    scanf_s("%f", &p->score2);
                    break;
                case '4':
                    printf("�������³ɼ�3��");
                    scanf_s("%f", &p->score3);
                    p->total = p->score1 + p->score2 + p->score3;  // �����ܷ�
                    break;
                default:
                    printf("��Чѡ��\n");
                }
                printf("�޸ĺ���Ϣ��\n");
                printf("ѧ��: %d\n����: %s\n�ɼ�1: %.1f\n�ɼ�2: %.1f\n�ɼ�3: %.1f\n�ܷ�: %.1f\n",
                    p->num, p->name, p->score1, p->score2, p->score3, p->total);
                system("pause");
                return;
            }
            else {
                printf("ȡ���޸ģ�\n");
            }
            break;
        }
        p = p->next;
    }
    printf("δ�ҵ���ѧ����\n");
    system("pause");
}

/* STU* OpenStuFile() {
    int key;
    FILE* filePtr;
    errno_t err;
    char butter[100];
    err = fopen_s(&filePtr, "text.txt", "r");
    if (err==0) {
        
        printf("�ļ��Ѵ��ڣ����ڼ�������...\n");
        STU* plist = CreateList();
        STU* pnew = plist;


        while (fscanf_s(filePtr, "%d%s%f%f%f%f",
            &pnew->num, pnew->name,
            &pnew->score1, &pnew->score2,
            &pnew->score3, &pnew->total) == 0) {
            // ����������������
            while (pnew->next && pnew->next->num < pnew->num) {
                pnew = pnew->next;
            }
            pnew->next = plist->next;
            plist->next = pnew;
            pnew = plist;  // ����ָ��
        }
        fclose(filePtr);
        printf("���ݼ�����ɣ�\n");
        return plist;
    }

    printf("�ļ������ڣ��Ƿ񴴽���(T/F)");
    getchar();
    scanf_s(" %c", &key);

    if (key == 'T') {
        errno_t err = fopen_s(&filePtr,FILE_NAME, "w");
        if (err==0) {
            printf("�ļ������ɹ���\n");
            fclose(filePtr);
            return CreateList();
        }
        else {
            printf("�����ļ�ʧ�ܣ�\n");
            system("pause");
            exit(1);
        }
    }
    else {
        printf("����ȡ����\n");
        system("pause");
        exit(1);
    }
}

void CloseStuFile(STU* plist) {
    FILE* fp;
        errno_t err= fopen_s(&fp,FILE_NAME, "w");
    if (!fp) {
        printf("�޷����ļ����棡\n");
        return;
    }

    STU* p = plist->next;
    while (p) {
        fprintf(fp, "%d\t%s\t%.1f\t%.1f\t%.1f\t%.1f\n",
            p->num, p->name, p->score1, p->score2, p->score3, p->total);
        p = p->next;
    }
    fclose(fp);
    printf("���ݱ���ɹ���\n");
}*/
STU* OpenStuFile() {
    int key;
    FILE* filePtr;
    errno_t err;
    char buffer[100];
    err = fopen_s(&filePtr, FILE_NAME, "r");  // ��Ϊ "r" ģʽ�����ڶ�ȡ�ļ�
    if (err == 0) {
        printf("�ļ��Ѵ��ڣ����ڼ�������...\n");
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
            // ����������������
            STU* prev = plist;
            while (prev->next && prev->next->num < pnew->num) {
                prev = prev->next;
            }
            pnew->next = prev->next;
            prev->next = pnew;
        }
        fclose(filePtr);
        printf("���ݼ�����ɣ�\n");
        return plist;
    }
    else {
        perror("���ļ�ʧ��");  // �������Ĵ�����Ϣ
        printf("�ļ������ڣ��Ƿ񴴽���(T/F)");
        getchar();
        scanf_s(" %c", &key);

        if (key == 'T') {
            err = fopen_s(&filePtr, FILE_NAME, "w");
            if (err == 0) {
                printf("�ļ������ɹ���\n");
                fclose(filePtr);
                return CreateList();
            }
            else {
                perror("�����ļ�ʧ��");  // �������Ĵ�����Ϣ
                system("pause");
                exit(1);
            }
        }
        else {
            printf("����ȡ����\n");
            system("pause");
            exit(1);
        }
    }
}

void CloseStuFile(STU* plist) {
    FILE* fp;
    errno_t err = fopen_s(&fp, FILE_NAME, "w");  // ��Ϊ "w" ģʽ������д���ļ�
    if (err != 0) {
        perror("�޷����ļ�����");  // �������Ĵ�����Ϣ
        return;
    }

    STU* p = plist->next;
    while (p) {
        fprintf(fp, "%d\t%s\t%.1f\t%.1f\t%.1f\t%.1f\n",
            p->num, p->name, p->score1, p->score2, p->score3, p->total);
        p = p->next;
    }
    fclose(fp);
    printf("���ݱ���ɹ���\n");
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
    // �ͷ��ڴ�
    while (plist) {
        STU* temp = plist;
        plist = plist->next;
        free(temp);
    }
    return 0;
}