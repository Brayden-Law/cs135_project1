#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib> 
#include <ctime>

using namespace std;
#define y 0
#define x 1

void commands()
{
    std::cout << "w to move up" << std::endl; 
    std::cout << "s to move down" << std::endl; 
    std::cout << "a to move left" << std::endl; 
    std::cout << "d to move right" << std::endl; 
    std::cout << std::endl;
    std::cout << "W to attack up" << std::endl; 
    std::cout << "S to attack down" << std::endl; 
    std::cout << "A to attack left" << std::endl; 
    std::cout << "D to attack right" << std::endl; 
    std::cout << std::endl;
}

void display_map(char abc[40][40], int player[2])
{
    std::cout << abc[player[y] - 2][player[x] - 2] << abc[player[y] - 2][player[x] - 1] << abc[player[y] - 2][player[x]    ] << abc[player[y] - 2][player[x] + 1] << abc[player[y] - 2][player[x] + 2] << std::endl;
    std::cout << abc[player[y] - 1][player[x] - 2] << abc[player[y] - 1][player[x] - 1] << abc[player[y] - 1][player[x]    ] << abc[player[y] - 1][player[x] + 1] << abc[player[y] - 1][player[x] + 2] << std::endl;
    std::cout << abc[player[y]    ][player[x] - 2] << abc[player[y]    ][player[x] - 1] << 'X'                               << abc[player[y]    ][player[x] + 1] << abc[player[y]    ][player[x] + 2] << std::endl;
    std::cout << abc[player[y] + 1][player[x] - 2] << abc[player[y] + 1][player[x] - 1] << abc[player[y] + 1][player[x]    ] << abc[player[y] + 1][player[x] + 1] << abc[player[y] + 1][player[x] + 2] << std::endl;
    std::cout << abc[player[y] + 2][player[x] - 2] << abc[player[y] + 2][player[x] - 1] << abc[player[y] + 2][player[x]    ] << abc[player[y] + 2][player[x] + 1] << abc[player[y] + 2][player[x] + 2] << std::endl;
    std::cout << std::endl;
}

bool enemy_move(int (&enemy)[2], int player[2], char (&map)[40][40], int& wander, int& wander_multi)
{

    int randomNum = 0;
    int vect_x = player[x] - enemy[x];
    int vect_y = player[y] - enemy[y];

    if(wander <= 0)
    {
        wander = 0;
    }
    if(wander_multi <= 1)
    {
        wander_multi = 1;
    }

    if(enemy[y] == player[y] && enemy[x] == player[x])
    {
        return false;
    }else if(wander > 0)
    {   
        do
        {
            srand(time(0));
            randomNum = rand() % 4;
            if(map[enemy[y] - 1][enemy[x]] == ' ' && randomNum == 0)
            {
                //up
                map[enemy[y]][enemy[x]] = ' ';
                enemy[y] -= 1;
                map[enemy[y]][enemy[x]] = '!';
                wander -= 1;
                return true;

            }if(map[enemy[y] + 1][enemy[x]] == ' ' && randomNum == 1)
            {
                //down
                map[enemy[y]][enemy[x]] = ' ';
                enemy[y] += 1;
                map[enemy[y]][enemy[x]] = '!';
                wander -= 1;
                return true;

            }if(map[enemy[y]][enemy[x] + 1] == ' ' && randomNum == 2)
            {
                //right
                map[enemy[y]][enemy[x]] = ' ';
                enemy[x] += 1;
                map[enemy[y]][enemy[x]] = '!';
                wander -= 1;
                return true;

            }if(map[enemy[y]][enemy[x] - 1] == ' ' && randomNum == 3)
            {
                //left
                map[enemy[y]][enemy[x]] = ' ';
                enemy[x] -= 1;
                map[enemy[y]][enemy[x]] = '!';
                wander -= 1;
                return true;
            }

        }while(true);
    }else if(vect_y < 0 && map[enemy[y] - 1][enemy[x]] == ' ')
    {
        //up
        map[enemy[y]][enemy[x]] = ' ';
        enemy[y] -= 1;
        map[enemy[y]][enemy[x]] = '!';
        wander_multi -= 1;
        return true;

    }else if(vect_y > 0 && map[enemy[y] + 1][enemy[x]] == ' ')
    {
        //down
        map[enemy[y]][enemy[x]] = ' ';
        enemy[y] += 1;
        map[enemy[y]][enemy[x]] = '!';
        wander_multi -= 1;
        return true;


    }else if(vect_x > 0 && map[enemy[y]][enemy[x] + 1] == ' ')
    {
        //right
        map[enemy[y]][enemy[x]] = ' ';
        enemy[x] += 1;
        map[enemy[y]][enemy[x]] = '!';
        wander_multi -= 1;
        return true;

    }else if(vect_x < 0 && map[enemy[y]][enemy[x] - 1] == ' ')
    {
        //left
        map[enemy[y]][enemy[x]] = ' ';
        enemy[x] -= 1;
        map[enemy[y]][enemy[x]] = '!';
        wander_multi -= 1;
        return true;
    }
    else
    { 
        wander += wander_multi;
        wander_multi += 1;
    }
    return true;
}

void open_gates(char (&map)[40][40])
{
    for(int a = 0; a < 40; a += 1)
    {
        for(int b = 0; b < 40; b += 1)
        {
            if(map[a][b] == '*')
            {
                map[a][b] = ' ';
            }
        }    
    }
}

int main()
{   
    int player[2] = {36, 3};
    char ch;
    std::string temp;

    int enemy_1[2] = {3, 3};
    int enemy_stun_1 = 0;
    int enemy_wander_1 = 0;
    int enemy_wander_multi_1 = 1;
    bool enemy_alive_1 = true;

    int enemy_2[2] = {3, 36};
    int enemy_stun_2 = 0;
    int enemy_wander_2 = 0;
    int enemy_wander_multi_2 = 1;
    bool enemy_alive_2 = true;

    int enemy_3[2] = {3, 5};
    int enemy_stun_3 = 0;
    int enemy_wander_3 = 0;
    int enemy_wander_multi_3 = 1;
    bool enemy_alive_3 = true;

    bool cure = false;

    char map[40][40] = 
    {
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', '!', ' ', '!', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', '!', ' ', '0', '0'},
        {'0', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', '0', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', '0', '*', '0', '0', ' ', ' ', ' ', '0', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', ' ', ' ', '0', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', ' ', ' ', '0', '0', '0', ' ', '0', ' ', ' ', ' ', '0', ' ', ' ', ' ', '0', ' ', ' ', '*', ' ', ' ', ' ', ' ', '0', '0', '0', '0', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', '0', ' ', ' ', ' ', '0', ' ', '0', ' ', '0', '0', ' ', '*', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', '@', ' ', '*', ' ', '0', ' ', ' ', '0', ' ', '*', ' ', ' ', '0', ' ', '0', '0', ' ', '0', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', '0', ' ', '0', ' ', ' ', '0', ' ', '*', ' ', ' ', '0', ' ', '0', '0', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', '0', '0', '0', ' ', ' ', '0', '*', '0', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', '*', ' ', '0', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', '0', '0', ' ', '*', '*', ' ', '0', '0', ' ', '0', '0', '0', ' ', ' ', ' ', '*', ' ', '0', ' ', '0', '0', '0', '0', '0', ' ', '0', '0', ' ', '0', '0', '*', '*', '*', '0', '0', '0'},
        {'0', '0', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', '0', ' ', '0', ' ', '0', ' ', ' ', '0', '*', ' ', '0', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', '0', ' ', '0', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', '0', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', '0', '0', '0', '*', '*', '*', '0', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', ' ', ' ', ' ', '0', '0', '0', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', '0', '0', '0', '0', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', '0', '0', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', '0', ' ', ' ', '0', ' ', '0', '0', '0', ' ', '0', '0'},
        {'0', '0', ' ', ' ', '0', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', '0', '0', '0', ' ', ' ', ' ', ' ', ' ', '*', ' ', '0', ' ', '0', '0', '0', '0', ' ', '0', '$', '0', ' ', '0', '0'},
        {'0', '0', ' ', ' ', ' ', ' ', '0', ' ', '0', '0', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', '*', ' ', '0', ' ', ' ', ' ', ' ', '0', ' ', '0', ' ', '0', ' ', '0', '0'},
        {'0', '0', ' ', '0', '0', '0', '0', ' ', ' ', '0', ' ', '0', '0', '0', '0', ' ', '0', ' ', ' ', '0', '0', ' ', '0', '0', ' ', '*', ' ', '0', ' ', '0', ' ', '0', '0', ' ', '0', ' ', '0', ' ', '0', '0'},
        {'0', '0', ' ', '*', ' ', ' ', ' ', ' ', ' ', '0', '0', '0', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', '0', ' ', ' ', '0', ' ', '*', ' ', '0', ' ', '0', ' ', ' ', '0', ' ', ' ', ' ', '0', ' ', '0', '0'},
        {'0', '0', ' ', '0', '0', '0', '0', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', '0', '0', ' ', ' ', ' ', '*', ' ', '0', ' ', '0', '0', ' ', '0', '0', '0', '0', '0', ' ', '0', '0'},
        {'0', '0', ' ', '0', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', '0', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', '0', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', ' ', '0', ' ', '0', ' ', ' ', ' ', ' ', '0', '0', '0', ' ', '0', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', '0', ' ', '0', '0', '0', '0', ' ', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', ' ', '0', '0', ' ', '0', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', '*', '0', ' ', '0', ' ', ' ', '0', '0', '0', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', '0', ' ', ' ', ' ', ' ', '0', ' ', '0', '0', ' ', ' ', '0', ' ', ' ', ' ', '0', '0', ' ', '0', ' ', ' ', '0', ' ', ' ', ' ', '0', '0', '0', ' ', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', ' ', '0', ' ', '0', '0', ' ', ' ', '0', '0', ' ', ' ', ' ', '0', ' ', ' ', '*', ' ', '0', '0', ' ', '0', ' ', '0', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', '0', ' ', '0', ' ', ' ', '0', '0', ' ', ' ', '0', '0', ' ', '0', '0', ' ', ' ', '*', ' ', ' ', '0', ' ', '*', ' ', '0', ' ', ' ', ' ', '0', '0', '0', '0', '0', '0', ' ', '0', '0', '0', '0'},
        {'0', '0', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', '0', ' ', ' ', ' ', '0', ' ', '0', ' ', ' ', '0', ' ', '*', ' ', '0', '0', '0', ' ', '0', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', ' ', ' ', '*', '0', ' ', '0', '0', '0', ' ', ' ', '0', '0', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', ' ', ' ', '0', '0', ' ', '0', '0', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', '0', '0', ' ', ' ', '0', ' ', '0', '0', '0', ' ', '0', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', ' ', '0', ' ', ' ', '0', '0', ' ', ' ', ' ', '0', ' ', '0', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', ' ', ' ', '0', ' ', ' ', ' ', '0', ' ', ' ', ' ', '0', ' ', '0', ' ', '0', ' ', '0', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', '0', ' ', '0', '0', '0', '0', ' ', '0', '0', '0', ' ', '0', ' ', '0', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', '0', '0', ' ', '0', ' ', '0', ' ', '0', ' ', '0', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', ' ', ' ', ' ', '0', ' ', '0', ' ', ' ', ' ', '0', ' ', '0', '0', ' ', '0', ' ', ' ', '0', ' ', ' ', ' ', '0', ' ', '0', ' ', '0', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', ' ', '0', ' ', '0', ' ', '0', ' ', ' ', ' ', '0', ' ', ' ', '*', ' ', ' ', ' ', ' ', '0', ' ', '0', ' ', '0', ' ', '0', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', ' ', '0', ' ', '0', ' ', '0', ' ', '0', ' ', '0', '0', '0', '*', '0', '0', '0', ' ', '0', '0', '0', ' ', '0', ' ', '0', '0', '0', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'}
    };

    while(true)
    {
        commands();
        display_map(map, player);

        std::getline(cin, temp);
        ch = temp[0];
        temp = " ";
    
        switch(ch)
        {
            case 'w':
                if(map[player[y] - 1][player[x]] == ' ')
                {
                    player[y] -= 1;
                }
                break;

            case 's':
                if(map[player[y] + 1][player[x]] == ' ')
                {
                    player[y] += 1;
                }
                break;

            case 'a':
                if(map[player[y]][player[x] - 1] == ' ')
                {
                    player[x] -= 1;
                }
                break;

            case 'd':
                if(map[player[y]][player[x] + 1] == ' ')
                {
                    player[x] += 1;
                }
                break;

            case 'W':
                if(cure == false)   
                {
                    if((player[y] - 1) == enemy_1[y] && player[x] == enemy_1[x])
                    {
                        enemy_stun_1 = 3;
                    }
                    if((player[y] - 1) == enemy_2[y] && player[x] == enemy_2[x])
                    {
                        enemy_stun_2 = 3;
                    }
                    if((player[y] - 1) == enemy_3[y] && player[x] == enemy_3[x])
                    {
                        enemy_stun_3 = 3;
                    }
                }else
                {
                    if((player[y] - 1) == enemy_1[y] && player[x] == enemy_1[x])
                    {
                        enemy_alive_1 = false; 
                    }
                    if((player[y] - 1) == enemy_2[y] && player[x] == enemy_2[x])
                    {
                        enemy_alive_2 = false; 
                    }
                    if((player[y] - 1) == enemy_3[y] && player[x] == enemy_3[x])
                    {
                        enemy_alive_3 = false; 
                    }
                }
                if(map[player[y] - 1][player[x]] == '@')
                {
                    map[player[y] - 1][player[x]] = ' ';
                    open_gates(map);
                }
                if(map[player[y] - 1][player[x]] == '$')
                {
                    map[player[y] - 1][player[x]] = ' ';
                    cure = true;
                }
                break;

            case 'S':
             if(cure == false)
             {
                if((player[y] + 1) == enemy_1[y] && player[x] == enemy_1[x])
                {
                    enemy_stun_1 = 3;
                }
                if((player[y] + 1) == enemy_2[y] && player[x] == enemy_2[x])
                {
                    enemy_stun_2 = 3;
                }
                if((player[y] + 1) == enemy_3[y] && player[x] == enemy_3[x])
                {
                    enemy_stun_3 = 3;
                }
             }else
             {
                if((player[y] + 1) == enemy_1[y] && player[x] == enemy_1[x])
                {
                    enemy_alive_1 = false; 
                }
                if((player[y] + 1) == enemy_2[y] && player[x] == enemy_2[x])
                {
                    enemy_alive_2 = false; 
                }
                if((player[y] + 1) == enemy_3[y] && player[x] == enemy_3[x])
                {
                    enemy_alive_3 = false; 
                }
             }
                if(map[player[y] + 1][player[x]] == '@')
                {
                    map[player[y] + 1][player[x]] = ' ';
                    open_gates(map);
                }
                if(map[player[y] + 1][player[x]] == '$')
                {
                    map[player[y] + 1][player[x]] = ' ';
                    cure = true;
                }
                break;

            case 'A':
                if(cure == false)
                {
                    if(player[y] == enemy_1[y] && enemy_1[x] == (player[x] - 1))
                    {
                        enemy_stun_1 = 3;
                    }
                    if(player[y] == enemy_2[y] && enemy_2[x] == (player[x] - 1))
                    {
                        enemy_stun_2 = 3;
                    }
                    if(player[y] == enemy_3[y] && enemy_3[x] == (player[x] - 1))
                    {
                        enemy_stun_3 = 3;
                    }
                }else
                {
                    if(player[y] == enemy_1[y] && enemy_1[x] == (player[x] - 1))
                    {
                        enemy_alive_1 = false;
                    }
                    if(player[y] == enemy_2[y] && enemy_2[x] == (player[x] - 1))
                    {
                        enemy_alive_2 = false;
                    }
                    if(player[y] == enemy_3[y] && enemy_3[x] == (player[x] - 1))
                    {
                        enemy_alive_3 = false;
                    }
                }
                if(map[player[y]][player[x] - 1] == '@')
                {
                    map[player[y]][player[x] - 1] = ' ';
                    open_gates(map);
                }
                if(map[player[y]][player[x] - 1] == '$')
                {
                    map[player[y]][player[x] - 1] = ' ';
                    cure = true;
                }
                break;

            case 'D':
                if(cure == false)
                {
                    if(player[y] == enemy_1[y] && enemy_1[x] == (player[x] + 1))
                    {
                        enemy_stun_1 = 3; 
                    }
                    if(player[y] == enemy_2[y] && enemy_2[x] == (player[x] + 1))
                    {
                        enemy_stun_2 = 3;
                    }
                    if(player[y] == enemy_3[y] && enemy_3[x] == (player[x] + 1))
                    {
                        enemy_stun_3 = 3;
                    }
                }else
                {
                    if(player[y] == enemy_1[y] && enemy_1[x] == (player[x] + 1))
                    {
                        enemy_alive_1 = false;
                    }
                    if(player[y] == enemy_2[y] && enemy_2[x] == (player[x] + 1))
                    {
                        enemy_alive_2 = false;
                    }
                    if(player[y] == enemy_3[y] && enemy_3[x] == (player[x] + 1))
                    {
                        enemy_alive_3 = false;
                    }
                }
                if(map[player[y]][player[x] + 1] == '@')
                {
                    map[player[y]][player[x] + 1] = ' ';
                    open_gates(map);
                }
                if(map[player[y]][player[x] + 1] == '$')
                {
                    map[player[y]][player[x] + 1] = ' ';
                    cure = true;
                }
                break; 

            default:
                break; 
        }

        if(enemy_stun_1 < 0 && enemy_alive_1 == true)
        {
            if(enemy_move(enemy_1, player, map, enemy_wander_1, enemy_wander_multi_1) == false)
            {
                std::cout << std::endl << "GAME OVER";
                return 0;
            }
        }else
        {
            enemy_stun_1 -= 1;
        }

        if(enemy_stun_2 < 0 && enemy_alive_2 == true)
        {
            if(enemy_move(enemy_2, player, map, enemy_wander_2, enemy_wander_multi_2) == false)
            {
                std::cout << std::endl << "GAME OVER";
                return 0; 
            }
        }else
        {
            enemy_stun_3 -= 1;
        }

        if(enemy_stun_3 < 0 && enemy_alive_3 == true)
        {
            if(enemy_move(enemy_3, player, map, enemy_wander_3, enemy_wander_multi_3) == false)
            {
                std::cout << std::endl << "GAME OVER";
                return 0; 
            }
        }else
        {
            enemy_stun_3 -= 1;
        }


    }
   





}