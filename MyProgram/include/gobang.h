#ifndef GOBANG_H
#define GOBANG_H


#define LATTIC_LEN 35//线条间距
#define COL 15
#define ROW 15
#define SPACE (3*LATTIC_LEN)//空白
#define GOBANGFILE "../assets/GobangManage.txt"

#include <vector>
#include <tuple>
#include <fstream>
#include <utility>
#include <limits>
#include <algorithm>
#include <.\include\graphics.h>      
#include <dsound.h>
#include <conio.h>
#include <random>
#include<string>
#include<iostream>
#pragma comment(lib, "WINMM.LIB")
namespace Gobang {
	void gamer_data_read();//读取玩家数据
	void gamer_data_write();//写入玩家数据
	void gobang_loading();//加载五子棋图片
	bool judge_winner();//判断胜负
	void mouse_move_message(ExMessage* msg);//鼠标移动
	void mouse_press_mseeage(ExMessage* msg);//鼠标按下
	void show_gobang();//显示五子棋
	int evaluate_direction(int row, int col, int dirRow, int dirCol, int player);//评估方向
	int evaluate_move(int row, int col, int player);//评估移动
	std::pair<int, int> get_next_move();//获取下一步
	void robot();//机器人
	bool compare_tuple(const std::tuple<std::string, std::string, int>& a, const std::tuple<std::string, std::string, int>& b);//比较分数
	void leader_board();//排行榜
	void pvp();//玩家对战
	int pvr();//玩家机器人对战
	void rvr();//机器人对战
	void gobang();//五子棋
}


#endif // !GOBANG_H
