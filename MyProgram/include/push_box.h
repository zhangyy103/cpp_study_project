#ifndef PUSH_BOX_H
#define PUSH_BOX_H

#include<iostream>
#include <.\include\graphics.h>  
#include<unordered_map>
#include<Windows.h>
#include <mmsystem.h>
#include<dsound.h>
#include<conio.h>
#pragma comment(lib, "WINMM.LIB")

namespace PushBox {
    void push_box_loading(int th);//加载图标
    void init_map();//初始化地图
    void theme_selection();//主题选择
    void show_icon();//显示图标
    void find_people();//找到人的位置
    bool get_box();//箱子是否被吃
    void key();//按键
    bool game_win();//游戏胜利
    void game_play();//游戏进行
    void push_box();//推箱子游戏
}


#endif // !PUSH_BOX_H
