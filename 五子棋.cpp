#include <stdio.h>
#include <graphics.h>
#include <windows.h>

#define ROWS 15

int map[ROWS][ROWS] = {1};           //棋盘
int k = 1;                           //1为黑棋下，0为白棋下
int _map[ROWS][ROWS] = {1};          //棋盘副本1
int __map[ROWS][ROWS] = {1};         //棋盘副本2
void print(void);                    //打印
int TorF(void);                      //胜负判断
void copy(int[][ROWS], int[][ROWS]); //复制数组
PIMAGE img[3];                       //储存图片
int n = 1;                           //悔棋辅助判断
char flag;                           //标志位
int x, y;                            //鼠标按下坐标

int main(void)
{
    ShowWindow(FindWindow("ConsoleWindowClass", NULL), 0);
    initgraph(283, 283, 0);           //新建窗口
    setbkcolor(WHITE);                //设置背景色
    setcolor(BLACK);                  //设置文字色
    setfont(30, 0, "宋体");           //设置文字规格
    setcaption("五子棋（右键悔棋）"); //设置窗口名称
    int o;                            //胜负判断
    char ch[15];                      //图片路径
    for (int x = 0; x <= 2; x++)      //加载图片
    {
        img[x] = newimage();
        sprintf(ch, "%d.jpg", x);
        getimage(img[x], ch);
    }
    do
    {
        while (mousemsg()) //防止在等待输入r时的鼠标操作影响下一局
            getmouse();
        k = 1;
        for (int a = 0; a < ROWS; a++) //重置棋盘
        {
            for (int b = 0; b < ROWS; b++)
            {
                map[a][b] = 0;
                _map[a][b] = 0;
                __map[a][b] = 0;
            }
        }
        print(); //打印地图
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
                    k ? map[y][x] += 10 : map[y][x] += 20; //根据k添加棋子
                    copy(__map, _map);                     //拷贝棋盘
                    copy(_map, map);
                    k ? k = 0 : k = 1; //更换黑白棋
                    n = 1;
                }
                else if (flag == 2 && n)
                {
                    k = k ? 0 : 1;    //更换黑白棋
                    copy(map, __map); //恢复棋盘
                    copy(_map, __map);
                    n = 0;
                }
            }
            print();
            if (o = TorF()) //判断胜利
                break;
        }
        cleardevice(); //清屏
        o == 1 ? outtextxy(0, 0, "black win") : outtextxy(0, 0, "write win");
        outtextxy(0, 50, "输入r再来一局");
        static int r;
        while ((r = getch()) != 'R' && r != 'r')
            continue;
    } while (1);
    closegraph(); //关闭窗口
    return 0;
}

void print(void) //打印棋盘
{
    cleardevice();          //清屏
    putimage(0, 0, img[0]); //打印棋盘背景
    for (int a = 0; a < ROWS; a++)
    {
        for (int b = 0; b < ROWS; b++)
        {
            if (map[a][b] == 10) //打印黑棋
                putimage(b * 20 - 6, a * 20 - 6, img[1]);
            else if (map[a][b] == 20) //打印白棋
                putimage(b * 20 - 6, a * 20 - 6, img[2]);
        }
    }
    return;
}

int TorF(void) //判断胜负
{
    int k = 1;
    for (int a = 0; a < ROWS; a++)
    {
        for (int b = 0; b < ROWS; b++)
        {
            if (map[a][b] == 10) //判断白棋胜负
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
            else if (map[a][b] == 20) //判断黑棋胜负
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

void copy(int x[][ROWS], int y[][ROWS]) //复制数组
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