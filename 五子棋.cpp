#include <stdio.h>
#include <graphics.h>
#include <windows.h>

#define ROWS 15

int map[ROWS][ROWS] = {1};           //����
int k = 1;                           //1Ϊ�����£�0Ϊ������
int _map[ROWS][ROWS] = {1};          //���̸���1
int __map[ROWS][ROWS] = {1};         //���̸���2
void print(void);                    //��ӡ
int TorF(void);                      //ʤ���ж�
void copy(int[][ROWS], int[][ROWS]); //��������
PIMAGE img[3];                       //����ͼƬ
int n = 1;                           //���帨���ж�
char flag;                           //��־λ
int x, y;                            //��갴������

int main(void)
{
    ShowWindow(FindWindow("ConsoleWindowClass", NULL), 0);
    initgraph(283, 283, 0);           //�½�����
    setbkcolor(WHITE);                //���ñ���ɫ
    setcolor(BLACK);                  //��������ɫ
    setfont(30, 0, "����");           //�������ֹ��
    setcaption("�����壨�Ҽ����壩"); //���ô�������
    int o;                            //ʤ���ж�
    char ch[15];                      //ͼƬ·��
    for (int x = 0; x <= 2; x++)      //����ͼƬ
    {
        img[x] = newimage();
        sprintf(ch, "%d.jpg", x);
        getimage(img[x], ch);
    }
    do
    {
        while (mousemsg()) //��ֹ�ڵȴ�����rʱ��������Ӱ����һ��
            getmouse();
        k = 1;
        for (int a = 0; a < ROWS; a++) //��������
        {
            for (int b = 0; b < ROWS; b++)
            {
                map[a][b] = 0;
                _map[a][b] = 0;
                __map[a][b] = 0;
            }
        }
        print(); //��ӡ��ͼ
        for (; is_run(); delay_fps(60))
        {
            mouse_msg msg = {0};
            flag = false;
            while (mousemsg())
            {
                msg = getmouse();
                if (msg.is_left() && msg.is_down())
                    flag = 1;
                else if (msg.is_right() && msg.is_down())
                    flag = 2;
            }
            if (flag)
            {
                printf("%d", flag);
                x = (int)(msg.x + 8) / 20;
                y = (int)(msg.y + 8) / 20;
                if (map[y][x] == 0 && flag == 1)
                {
                    k ? map[y][x] += 10 : map[y][x] += 20; //����k�������
                    copy(__map, _map);                     //��������
                    copy(_map, map);
                    k ? k = 0 : k = 1; //�����ڰ���
                    n = 1;
                }
                else if (flag == 2 && n)
                {
                    k = k ? 0 : 1;    //�����ڰ���
                    copy(map, __map); //�ָ�����
                    copy(_map, __map);
                    n = 0;
                }
            }
            print();
            if (o = TorF()) //�ж�ʤ��
                break;
        }
        cleardevice(); //����
        o == 1 ? outtextxy(0, 0, "black win") : outtextxy(0, 0, "write win");
        outtextxy(0, 50, "����r����һ��");
        static int r;
        while ((r = getch()) != 'R' && r != 'r')
            continue;
    } while (1);
    closegraph(); //�رմ���
    return 0;
}

void print(void) //��ӡ����
{
    cleardevice();          //����
    putimage(0, 0, img[0]); //��ӡ���̱���
    for (int a = 0; a < ROWS; a++)
    {
        for (int b = 0; b < ROWS; b++)
        {
            if (map[a][b] == 10) //��ӡ����
                putimage(b * 20 - 6, a * 20 - 6, img[1]);
            else if (map[a][b] == 20) //��ӡ����
                putimage(b * 20 - 6, a * 20 - 6, img[2]);
        }
    }
    return;
}

int TorF(void) //�ж�ʤ��
{
    int k = 1;
    for (int a = 0; a < ROWS; a++)
    {
        for (int b = 0; b < ROWS; b++)
        {
            if (map[a][b] == 10) //�жϰ���ʤ��
            {
                while (b + k < ROWS && map[a][b + k] == 10)
                {
                    k++;
                }
                if (k >= 5)
                    return 1;
                else
                    k = 1;
                while (a + k < ROWS && map[a + k][b] == 10)
                {
                    k++;
                }
                if (k >= 5)
                    return 1;
                else
                    k = 1;
                while (b + k < ROWS && a + k < ROWS && map[a + k][b + k] == 10)
                {
                    k++;
                }
                if (k >= 5)
                    return 1;
                else
                    k = 1;
                while (b - k > 0 && a + k < ROWS && map[a + k][b - k] == 10)
                {
                    k++;
                }
                if (k >= 5)
                    return 1;
                else
                    k = 1;
            }
            else if (map[a][b] == 20) //�жϺ���ʤ��
            {
                while (b + k < ROWS && map[a][b + k] == 20)
                {
                    k++;
                }
                if (k >= 5)
                    return 2;
                else
                    k = 1;
                while (a + k < ROWS && map[a + k][b] == 20)
                {
                    k++;
                }
                if (k >= 5)
                    return 2;
                else
                    k = 1;
                while (b + k < ROWS && a + k < ROWS && map[a + k][b + k] == 20)
                {
                    k++;
                }
                if (k >= 5)
                    return 2;
                else
                    k = 1;
                while (b - k > 0 && a + k < ROWS && map[a + k][b - k] == 20)
                {
                    k++;
                }
                if (k >= 5)
                    return 2;
                else
                    k = 1;
            }
        }
    }
    return 0;
}

void copy(int x[][ROWS], int y[][ROWS]) //��������
{
    for (int a = 0; a < ROWS; a++)
    {
        for (int b = 0; b < ROWS; b++)
        {
            x[a][b] = y[a][b];
        }
    }
    return;
}