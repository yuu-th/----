#include <algorithm>
//#include <conio.h>
#include <iostream>
#include <random>
#include <string>
#include <time.h>
#include <vector>
//#include <windows.h>
//#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <thread>

//using std::thread::sleep_for;

using namespace std;


#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
 
 
 int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
 
 
/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
 
/* reads from keypress, echoes */
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

class Game {
public:

    // 関数のプロトタイプ宣言
    


    int x = 3, y;
    int nextMino = -1;
    int nowMino, nowState;
    clock_t game_start_time = clock();

    string map[22][40] = {
        { " ", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_",
            "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_",
            "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", "_", " " },
        { "|", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { "|", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { "|", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { "|", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", "-", "-", "-", "-", "-", "-", "-", "-", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", " ", " ", " ", " ", " ", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", "-", "-", "-", "-", "-", "-", "-", "-", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", "|", " ", " ", " ", " ",
            " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
            " ", " ", "|", "0", "0", ":", "0", "0", " ", " ", " ", "|" },
        { " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", "-", "-", "-", "-",
            "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-",
            "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", " " },
    };

    int field[22][22] = {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };

    int minoArr[7][4][4][4] = { { // Iミノ
                                    {
                                        { 0, 0, 0, 0 },
                                        { 1, 1, 1, 1 },
                                        { 0, 0, 0, 0 },
                                        { 0, 0, 0, 0 },
                                    },
                                    {
                                        { 0, 0, 1, 0 },
                                        { 0, 0, 1, 0 },
                                        { 0, 0, 1, 0 },
                                        { 0, 0, 1, 0 },
                                    },
                                    {
                                        { 0, 0, 0, 0 },
                                        { 0, 0, 0, 0 },
                                        { 1, 1, 1, 1 },
                                        { 0, 0, 0, 0 },
                                    },
                                    {
                                        { 0, 1, 0, 0 },
                                        { 0, 1, 0, 0 },
                                        { 0, 1, 0, 0 },
                                        { 0, 1, 0, 0 },
                                    } },

        { // jミノ(青)
            {
                { 0, 0, 0, 0 },
                { 1, 0, 0, 0 },
                { 1, 1, 1, 0 },
                { 0, 0, 0, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 1, 1, 0 },
                { 0, 1, 0, 0 },
                { 0, 1, 0, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 },
                { 1, 1, 1, 0 },
                { 0, 0, 1, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 1, 0, 0 },
                { 0, 1, 0, 0 },
                { 1, 1, 0, 0 },
            } },
        { // Lミノ(オレンジ)
            {
                { 0, 0, 0, 0 },
                { 0, 0, 1, 0 },
                { 1, 1, 1, 0 },
                { 0, 0, 0, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 1, 0, 0 },
                { 0, 1, 0, 0 },
                { 0, 1, 1, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 },
                { 1, 1, 1, 0 },
                { 1, 0, 0, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 1, 1, 0, 0 },
                { 0, 1, 0, 0 },
                { 0, 1, 0, 0 },
            } },
        {
            // Oミノ(黄色)
            {
                { 0, 0, 0, 0 },
                { 0, 1, 1, 0 },
                { 0, 1, 1, 0 },
                { 0, 0, 0, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 1, 1, 0 },
                { 0, 1, 1, 0 },
                { 0, 0, 0, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 1, 1, 0 },
                { 0, 1, 1, 0 },
                { 0, 0, 0, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 1, 1, 0 },
                { 0, 1, 1, 0 },
                { 0, 0, 0, 0 },
            },
        },
        { // Sミノ(緑)
            {
                { 0, 0, 0, 0 },
                { 0, 1, 1, 0 },
                { 1, 1, 0, 0 },
                { 0, 0, 0, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 1, 0, 0 },
                { 0, 1, 1, 0 },
                { 0, 0, 1, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 },
                { 0, 1, 1, 0 },
                { 1, 1, 0, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 1, 0, 0, 0 },
                { 1, 1, 0, 0 },
                { 0, 1, 0, 0 },
            } },
        { // Zミノ(赤)
            {
                { 0, 0, 0, 0 },
                { 1, 1, 0, 0 },
                { 0, 1, 1, 0 },
                { 0, 0, 0, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 0, 1, 0 },
                { 0, 1, 1, 0 },
                { 0, 1, 0, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 },
                { 1, 1, 0, 0 },
                { 0, 1, 1, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 1, 0, 0 },
                { 1, 1, 0, 0 },
                { 1, 0, 0, 0 },
            } },
        { // Tミノ(紫)
            {
                { 0, 0, 0, 0 },
                { 0, 1, 0, 0 },
                { 1, 1, 1, 0 },
                { 0, 0, 0, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 1, 0, 0 },
                { 0, 1, 1, 0 },
                { 0, 1, 0, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 0, 0, 0 },
                { 1, 1, 1, 0 },
                { 0, 1, 0, 0 },
            },
            {
                { 0, 0, 0, 0 },
                { 0, 1, 0, 0 },
                { 1, 1, 0, 0 },
                { 0, 1, 0, 0 },
            }

        } };

    vector<int> nextMinoArr = {};

    bool check_CD(int x, int y, int state)
    {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (field[y + i + 1][2 * (x + j) + 1] > 0 && minoArr[nowMino][state][i][j] == 1) {
                    return false;
                }
            }
        }
        return true;
    }

    
    void gameover(){
        cout << "finish" << endl;
        exit(0);
    }

    bool turn_mino(int direction)
    {
        int temp = nowState;
        nowState += direction;
        if (nowState == 4)
            nowState = 0;
        else if (nowState == -1)
            nowState = 3;
        if (check_CD(x, y, nowState)) {
            upgrade_mino();
            print_map();
        } else if (nowState == 1 || nowState == 3) {
            if (check_CD(x + nowState - 2, y, nowState)) {
                x += nowState - 2;
            } else if (check_CD(x + nowState - 2, y - 1, nowState)) {
                x += nowState - 2;
                y--;
            } else if (check_CD(x, y + 2, nowState)) {
                y += 2;
            } else if (check_CD(x + nowState - 2, y + 2, nowState)) {
                x += nowState - 2;
                y += 2;
            } else {
                nowState = temp;
                return false;
            }
            upgrade_mino();
            print_map();
        } else {
            if (check_CD(x - direction * (1 - nowState), y, nowState)) {
                x -= direction * (1 - nowState);
            } else if (check_CD(x - direction * (1 - nowState), y + 1, nowState)) {
                x -= direction * (1 - nowState);
                y++;
            } else if (check_CD(x, y - 2, nowState)) {
                y -= 2;
            } else if (check_CD(x - direction * (1 - nowState), y - 2, nowState)) {
                x -= direction * (1 - nowState);
                y -= 2;
            } else {
                nowState = temp;
                return false;
            }
            upgrade_mino();
            print_map();
        }
        return true;
    }

    void wait(int n)
    {
        clock_t start = clock();
        clock_t now = clock();
        bool OK = true;
        string keyState;
        while (now - start < n) {
            if (kbhit()) {
                keyState = getch();
                while(kbhit()){getch();};
                //Sleep(100);
                std::this_thread::sleep_for(chrono::milliseconds(100));
            } else {
                OK = true;
                keyState = "";
            }
            if (keyState == "a" && check_CD(x - 1, y, nowState)) {
                OK = false;
                x--;
                upgrade_mino();
                print_map();
            } else if (keyState == "d" && check_CD(x + 1, y, nowState)) {
                OK = false;
                x++;
                upgrade_mino();
                print_map();
            } else if (keyState == "s" && check_CD(x, y + 1, nowState)) {
                y++;
                OK = false;
                upgrade_mino();
                print_map();
            } else if (keyState == "w"){
                while(check_CD(x,y + 1, nowState)){
                    y++;
                }
                OK = false;
                upgrade_mino();
                print_map();
            } else if (keyState == "e") {
                turn_mino(1);
                wait(n);
                break;
            } else if (keyState == "q") {
                turn_mino(-1);
                wait(n);
                break;
            } else if (keyState == "x") {
                if (nextMino == -1) {

                    for (int i = 0; i < 4; i++)
                        for (int j = 0; j < 4; j++) {
                            if (minoArr[nowMino][0][i][j] == 1) {
                                map[i + 1][j * 2 + 1] = "[";
                                map[i + 1][j * 2 + 2] = "]";
                            }
                        }

                    nextMino = nowMino;
                    update_next_mino();
                    start_mino();
                    print_map();
                } else {
                    for (int i = 0; i < 4; i++)
                        for (int j = 0; j < 4; j++) {
                            if (minoArr[nowMino][0][i][j] == 1) {
                                map[i + 1][j * 2 + 1] = "[";
                                map[i + 1][j * 2 + 2] = "]";
                            } else {
                                map[i + 1][j * 2 + 1] = " ";
                                map[i + 1][j * 2 + 2] = " ";
                            }
                        }
                    int temp = nextMino;
                    nextMino = nowMino;
                    nowMino = temp;
                    nowState = 0;
                    x = 3;
                    y = (nextMinoArr[0] == 0) - 1;
                    set_mino(x, y, minoArr[nowMino][nowState]);
                    print_map();
                }
            } else if (keyState == " ") {
                exit(0);
            }
            now = clock();
        }
    }

    void print_map()
    {
        system("cls");
        cout << endl;
        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 20; j++) {
                if (field[i + 1][j + 1] == 1)
                    map[1 + i][10 + j] = "[";
                else if (field[i + 1][j + 1] == 2)
                    map[1 + i][10 + j] = "]";
            }

        for (int i = 0; i < 6; i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < 4; k++) {
                    map[i * 3 + j + 1][2 * k + 31] = " ";
                    map[i * 3 + j + 1][2 * k + 32] = " ";

                    if (minoArr[nextMinoArr[i]][0][j][k] == 1) {
                        map[i * 3 + j + 1][2 * k + 31] = "[";
                        map[i * 3 + j + 1][2 * k + 32] = "]";
                    }
                }

        clock_t now = clock();

        int elapsed_secs = (now-game_start_time)/1000;

        map[20][31]=to_string(elapsed_secs/60/10);
        map[20][32]=to_string(elapsed_secs/60%10);
        map[20][34]=to_string(elapsed_secs%60/10);
        map[20][35]=to_string(elapsed_secs%60%10);

        string output ="";
        for (int i = 0; i < 22; i++) {
            for (int j = 0; j < 40; j++) {
                output+=map[i][j];
            }
            output+="\n";
        }
        output+="a: move left , d: move right , s: move down ,\nw: drop , q: rotate left , e: rotate right , \nx: hold , Space: quit\n";
        cout << output;

        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 20; j++)
                if (map[i + 1][j + 10] != " ")
                    map[1 + i][10 + j] = " ";
    }

    //テトリミノの候補を表示する。
    /*配列には[1,2,3,,,]のようになっていて
    これの長さが7未満になったらもう一度、一周分生成する
    */
    void update_next_mino()
    {
        if (nextMinoArr.size() < 7) {
            vector<int> tempArr = { 0, 1, 2, 3, 4, 5, 6 };
            for (int i = 0; i < 7; i++) {
                srand((int)time(NULL));
                int randomN = rand() % (7 - i);
                nextMinoArr.push_back(tempArr[randomN]);
                tempArr.erase(tempArr.begin() + randomN);
            }
        }
    }

    void set_mino(int x, int y, int shapeArr[4][4])
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                if (shapeArr[i][j] == 1) {
                    map[i + y + 1][j * 2 + 2 * x + 10] = "[";
                    map[i + y + 1][j * 2 + 2 * x + 11] = "]";
                }
            }
    }

    void set_field(int x, int y, int shapeArr[4][4])
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                if (shapeArr[i][j] == 1) {
                    field[i + y + 1][j * 2 + 2 * x + 1] = 1;
                    field[i + y + 1][j * 2 + 2 + 2 * x] = 2;
                }
            }
    }
    // 0x62f0c4 0x62f11c 0x62f174 0x62f1cc 0x62f224 0x62f27c 0x62f2d4 0x62f32c 0x62f384 0x62f3dc 0x62f434 0x62f48c 0x62f4e4 0x62f53c 0x62f594 0x62f5ec 0x62f644 0x62f69c 0x62f6f4 0x62f74c

    void start_mino()
    {
        nowState = 0;
        x = 3;
        y = (nextMinoArr[0] == 0) - 1;
        nowMino = nextMinoArr[0];
        set_mino(x, y, minoArr[nowMino][nowState]);
        nextMinoArr.erase(nextMinoArr.begin());
        if(!check_CD(x,y,nowState)){
            gameover();
        }
    }

    int upgrade_mino()
    {
        if (!check_CD(x, y, nowState)) {
            y--;
            set_field(x, y, minoArr[nowMino][nowState]);
            bool OK = false;
            for (int i = y + 1; i < y + 5; i++) {
                if (i < 21) {
                    if (count(begin(field[i]), end(field[i]), 0) == 0) {
                        field[i][0] = -1;
                        OK = true;
                    }
                }
            }
            if (OK) {
                for (int i = y + 4; i >= 1; i--) {
                    if (field[i][0] == -1) {
                        int count = 1;
                        while (field[i - count][0] == -1 && i - count > 0) {
                            count++;
                        }
                        if (i - count <= 0)
                            continue;
                        count = i - count;
                        for (int j = 0; j < 22; j++) {
                            field[i][j] = field[count][j];
                        }
                        field[count][0] = -1;
                    }
                }
                for (int i = 1; i < y + 5; i++)
                    if (field[i][0] = -1)
                        field[i][0] = 1;
            }
            return false;
        }
        set_mino(x, y, minoArr[nowMino][nowState]);
        return true;
        /*
        y++;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {

            if (field[y + i + 1][2 * (x + j) + 1] > 0 &&
        minoArr[nowMino][nowState][i][j] == 1)
            {
                y--;
                set_field(x, y, minoArr[nowMino][nowState]);
                return false;
            }
        }
        }
        set_mino(x, y, minoArr[nowMino][nowState]);
        return true;
        */
    }

};

int main()
{
    Game game;
    cout << "start" << endl;
    int time = 500;
    while(1) {

        game.update_next_mino();
        game.start_mino();
        game.print_map();
        game.y++;
        game.wait(time);
        while (game.upgrade_mino()) {
            game.print_map();
            game.wait(time);
            game.y++;
        }
        time = time * 99 / 100;
    }
}