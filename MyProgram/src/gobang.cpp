#include".\include\gobang.h"

//定义棋盘情况 没有棋子 0  黑棋 1  白棋 2
enum Chess {
	none,
	black,
	white//就是1 2 3 
};
std::vector<std::tuple<std::string, std::string, int>> g_Gamer_Data;
//定义地图数组
int g_Gobang_Map[ROW][COL] = { 0 };
bool g_IsWin, g_IsFull = 0;
int g_B_Win, g_W_Win = 0;
std::string g_ID, g_Password;

struct Pos { //鼠标位置结构体
	int row;
	int col;
	bool is_show;//是否显示蓝框
	int chess_play;//棋手
}g_Pos = { -1, -1, false, black };//黑棋先行

IMAGE background, gobangmenu, gobanglogin;//加载地图

void Gobang::gamer_data_read() {
	std::ifstream file(GOBANGFILE); // 打开文本文件
	g_Gamer_Data.clear(); // 清空
	if (!file.is_open()) {
		std::cerr << "无法打开文件" << std::endl;
		return;
	}

	std::string line;
	std::tuple<std::string, std::string, int> current_tuple;

	int lineCount = 0;
	while (std::getline(file, line)) {
		if (lineCount == 0) {
			std::get<0>(current_tuple) = line;
		}
		else if (lineCount == 1) {
			std::get<1>(current_tuple) = line;
		}
		else {
			std::get<2>(current_tuple) = std::stoi(line);
			g_Gamer_Data.push_back(current_tuple); // 将当前元组存储到向量中
		}

		lineCount = (lineCount + 1) % 3;
	}

	file.close(); // 关闭文件
}

void Gobang::gamer_data_write() {
	std::ofstream file(GOBANGFILE, std::ofstream::trunc);
	if (!file.is_open()) {
		std::cerr << "无法打开输出文件" << std::endl;
		return;
	}

	for (const auto& data : g_Gamer_Data) {
		file << std::get<0>(data) << "\n"; // 写入id并换行
		file << std::get<1>(data) << "\n"; // 写入password并换行
		file << std::get<2>(data) << "\n"; // 写入得分并换行
	}

	file.close(); // 关闭文件
	return;
}

void Gobang::gobang_loading() {
	loadimage(&background, _T("..\\assets\\gobang图标\\background.jpg"), 840, 700);
	loadimage(&gobangmenu, _T("..\\assets\\gobang图标\\menu.jpg"), 840, 700);
	loadimage(&gobanglogin, _T("..\\assets\\gobang图标\\login.jpg"), 840, 700);
}

bool Gobang::judge_winner() {
	//五子连珠
	//横向：遍历列
	// 定义方向的增量数组  
	//思路来自文心一言
	std::vector<std::pair<int, int>> directions = {
		{0, 1}, {0, -1}, // 水平方向  
		{1, 0}, {-1, 0}, // 垂直方向  
		{1, 1}, {-1, -1}, // 对角线方向1  
		{1, -1}, {-1, 1}  // 对角线方向2  
	};
	//检查棋盘是否满了
	for (int x = 0; x < ROW; x++) {
		for (int y = 0; y < COL; y++) {
			g_IsFull = 1;
			if (g_Gobang_Map[x][y] == none) {
				g_IsFull = 0;
				break;
			}
		}
		if (!g_IsFull)break;
	}
	// 主循环检查所有可能的位置和方向  
	for (int x = 0; x < ROW; x++) {
		for (int y = 0; y < COL; y++) {
			for (const auto& dir : directions) {
				int dx = dir.first, dy = dir.second;
				bool foundPattern = true;
				// 检查五个连续的位置  
				for (int i = 1; i <= 4; i++) {
					int nx = x + dx * i;
					int ny = y + dy * i;

					// 检查坐标是否在棋盘范围内  
					if (nx < 0 || nx >= 15 || ny < 0 || ny >= 15) {
						foundPattern = false;
						break;
					}
					// 检查值是否匹配 
					if (i == 1 && (g_Gobang_Map[nx][ny] != g_Pos.chess_play || g_Gobang_Map[x][y] != g_Pos.chess_play)) {
						foundPattern = false;
						break;
					}
					if (i > 1 && g_Gobang_Map[nx][ny] != g_Pos.chess_play) {
						foundPattern = false;
						break;
					}
				}
				if (foundPattern) {
					return true;  // 如果找到连珠，则返回true  
				}
			}
		}
	}
	return false; // 如果没有找到连珠，则返回false
}

void Gobang::mouse_move_message(ExMessage* msg) {//鼠标移动
	//根据鼠标获得坐标
	g_Pos.is_show = false;
	g_Pos.row = msg->y / LATTIC_LEN;
	g_Pos.col = msg->x / LATTIC_LEN;
	//坐标校准
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			//获取每个格子左上角的坐标
			int gridx = j * LATTIC_LEN + SPACE;
			int gridy = i * LATTIC_LEN + SPACE;
			//msg->y,msg->x 校准判断，让方框画在离鼠标最近的交叉点 abs()取绝对值
			if (abs(msg->x - gridx) < 20 && abs(msg->y - gridy) <= 20) {
				g_Pos.is_show = true;
				g_Pos.row = i;
				g_Pos.col = j;
			}
		}
	}
}

void Gobang::mouse_press_mseeage(ExMessage* msg) {//鼠标按下
	//如何是鼠标左键，就下棋
	if (msg->message == WM_LBUTTONDOWN && g_Gobang_Map[g_Pos.row][g_Pos.col] == 0 && g_Pos.is_show) {
		g_Gobang_Map[g_Pos.row][g_Pos.col] = g_Pos.chess_play;
		if (judge_winner()) {
			//绘制完在结束
			g_IsWin = judge_winner();
			if (g_Gobang_Map[g_Pos.row][g_Pos.col] == black) {
				setfillcolor(BLACK);
				solidcircle(g_Pos.col * LATTIC_LEN + SPACE, g_Pos.row * LATTIC_LEN + SPACE, 14);
				//"const char *" 类型的实参与 "LPCWSTR" 类型的形参不兼容
				MessageBox(GetHWnd(), _T("黑棋赢了"), _T("游戏结束nefu"), MB_OK);
				//exit(0);
			}
			else if (g_Gobang_Map[g_Pos.row][g_Pos.col] == white) {
				setfillcolor(WHITE);
				solidcircle(g_Pos.col * LATTIC_LEN + SPACE, g_Pos.row * LATTIC_LEN + SPACE, 14);
				MessageBox(GetHWnd(), _T("白棋赢了"), _T("游戏结束nefu"), MB_OK);
				//exit(0);
			}
		}
		//切换棋手
		g_Pos.chess_play = (g_Pos.chess_play == black ? white : black);
	}
}

void Gobang::show_gobang() {
	putimage(0, 0, &background);
	//绘制网格线 15*15
	setlinestyle(PS_SOLID, 1);//粗细
	setlinecolor(BLACK);//设置颜色
	for (int i = 0; i < 14; i++) {
		line(SPACE, i * LATTIC_LEN + SPACE, 20 * LATTIC_LEN - SPACE, i * LATTIC_LEN + SPACE);//绘制横线
		line(i * LATTIC_LEN + SPACE, +SPACE, i * LATTIC_LEN + SPACE, 20 * LATTIC_LEN - SPACE);//绘制竖线
	}

	//绘制边框(加粗）
	setlinestyle(PS_SOLID, 2);
	rectangle(SPACE, SPACE, SPACE + 14 * LATTIC_LEN, SPACE + 14 * LATTIC_LEN);
	//画点
	setfillcolor(BLACK);//颜色
	solidcircle(SPACE + 7 * LATTIC_LEN, SPACE + 7 * LATTIC_LEN, 5);
	solidcircle(SPACE + (7 - 4) * LATTIC_LEN, SPACE + (7 - 4) * LATTIC_LEN, 5);
	solidcircle(SPACE + (7 - 4) * LATTIC_LEN, SPACE + (7 + 4) * LATTIC_LEN, 5);
	solidcircle(SPACE + (7 + 4) * LATTIC_LEN, SPACE + (7 - 4) * LATTIC_LEN, 5);
	solidcircle(SPACE + (7 + 4) * LATTIC_LEN, SPACE + (7 + 4) * LATTIC_LEN, 5);

	//绘制棋子
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (g_Gobang_Map[i][j] == black) {//黑
				setfillcolor(BLACK);
				solidcircle(j * LATTIC_LEN + SPACE, i * LATTIC_LEN + SPACE, 14);
			}
			else if (g_Gobang_Map[i][j] == white) {//白
				setfillcolor(WHITE);
				solidcircle(j * LATTIC_LEN + SPACE, i * LATTIC_LEN + SPACE, 14);
			}
			//空
		}
	}

	//绘制鼠标移动时的蓝框
	setlinecolor(CYAN);
	if (g_Pos.is_show) {
		rectangle(g_Pos.col * LATTIC_LEN + SPACE - 12, g_Pos.row * LATTIC_LEN + SPACE - 12, g_Pos.col * LATTIC_LEN + SPACE + 12, g_Pos.row * LATTIC_LEN + SPACE + 12);
	}
}

int Gobang::evaluate_direction(int row, int col, int dirRow, int dirCol, int player) {
	static const int scores[] = { 0, 10, 30, 60, 90, 100 };  // 得分查找表
	int count = 0;
	// 向前搜索
	int r = row, c = col;
	while (r >= 0 && r < ROW && c >= 0 && c < COL && g_Gobang_Map[r][c] == player) {
		if (++count >= 5) return scores[5];  // 如果连成5子，满分
		r += dirRow;
		c += dirCol;
	}
	// 向后搜索
	r = row - dirRow;
	c = col - dirCol;
	while (r >= 0 && r < ROW && c >= 0 && c < COL && g_Gobang_Map[r][c] == player) {
		if (++count >= 5) return scores[5];  // 如果连成5子，满分
		r -= dirRow;
		c -= dirCol;
	}
	return scores[count];  // 根据连子数量计算得分
}


int Gobang::evaluate_move(int row, int col, int player) {
	int score = 0;
	int opponent = (player == black) ? white : black;

	// 向右水平方向评估
	score += evaluate_direction(row, col, 0, 1, player);
	// 向下垂直方向评估
	score += evaluate_direction(row, col, 1, 0, player);
	// 向右下对角线方向评估
	score += evaluate_direction(row, col, 1, 1, player);
	// 向左下对角线方向评估
	score += evaluate_direction(row, col, 1, -1, player);

	// 向右水平方向评估对手
	score += evaluate_direction(row, col, 0, 1, opponent);
	// 向下垂直方向评估对手
	score += evaluate_direction(row, col, 1, 0, opponent);
	// 向右下对角线方向评估对手
	score += evaluate_direction(row, col, 1, 1, opponent);
	// 向左下对角线方向评估对手
	score += evaluate_direction(row, col, 1, -1, opponent);

	return score;
	//这一函数将方向也作为参数，避免了代码的重复，与原来的方案相比，更加简洁

}

std::pair<int, int>Gobang::get_next_move() {
	int max_score = -1;
	std::pair<int, int> best_move = { -1, -1 };

	for (int row = 0; row < ROW; row++) {
		for (int col = 0; col < COL; col++) {
			if (g_Gobang_Map[row][col] == none) {
				int score = evaluate_move(row, col, g_Pos.chess_play);
				if (score > max_score) {
					max_score = score;
					best_move = { row, col };
				}
			}
		}
	}
	if (max_score == 0) {
		int r0 = rand() % 15;
		int c0 = rand() % 15;
		if (g_Gobang_Map[r0][c0] == none)best_move = { r0, c0 };
	}

	return best_move;
}

void Gobang::robot() {
	std::pair<int, int> best = get_next_move();
	g_Pos.row = best.first;
	g_Pos.col = best.second;
	g_Gobang_Map[g_Pos.row][g_Pos.col] = g_Pos.chess_play;
	if (judge_winner()) {
		//绘制完在结束
		g_IsWin = judge_winner();
		if (g_Gobang_Map[g_Pos.row][g_Pos.col] == black) {
			g_B_Win++;
			setfillcolor(BLACK);
			solidcircle(g_Pos.col * LATTIC_LEN + SPACE, g_Pos.row * LATTIC_LEN + SPACE, 14);
			//"const char *" 类型的实参与 "LPCWSTR" 类型的形参不兼容
			MessageBox(GetHWnd(), _T("黑棋赢了"), _T("游戏结束nefu"), MB_OK);
		}
		else if (g_Gobang_Map[g_Pos.row][g_Pos.col] == white) {
			g_W_Win++;
			setfillcolor(WHITE);
			solidcircle(g_Pos.col * LATTIC_LEN + SPACE, g_Pos.row * LATTIC_LEN + SPACE, 14);
			MessageBox(GetHWnd(), _T("白棋赢了"), _T("游戏结束nefu"), MB_OK);
		}
	}
	//切换棋手
	g_Pos.chess_play = (g_Pos.chess_play == black ? white : black);
}

bool Gobang::compare_tuple(const std::tuple<std::string, std::string, int>& a, const std::tuple<std::string, std::string, int>& b) {
	return std::get<2>(a) < std::get<2>(b);
}

void Gobang::leader_board() {
	system("cls");
	std::sort(g_Gamer_Data.begin(), g_Gamer_Data.end(), compare_tuple);
	int count = 0;
	for (const auto& data : g_Gamer_Data) {
		if (std::get<2>(data) != 9999) {
			std::cout << "ID:" << std::get<0>(data) << "  " << "战胜机器人所用的步数:" << std::get<2>(data) << std::endl;
			count++;
		}
		if (count == 10) {
			break;
		}
	}

	return;
}

void Gobang::pvp() {
	initgraph(840, 700, SHOWCONSOLE);
	while (!g_IsWin && !g_IsFull) {
		BeginBatchDraw();
		show_gobang();
		EndBatchDraw();
		//处理输入信息
		ExMessage msg;
		//获取消息
		if (peekmessage(&msg, EM_MOUSE)) {//获取鼠标输入
			switch (msg.message) {//消息类型
			case WM_MOUSEMOVE://鼠标移动消息
				mouse_move_message(&msg);
				break;
			case WM_LBUTTONDOWN://鼠标左右键按下
				mouse_press_mseeage(&msg);
				break;
			default:
				break;
			}
		}
	}
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			g_Gobang_Map[i][j] = 0;
		}
	}
	g_IsWin = 0;
	g_IsFull = 0;
}
int Gobang::pvr() {
	int gamerscore = 0;
	initgraph(840, 700, SHOWCONSOLE);
	while (!g_IsWin && !g_IsFull) {
		BeginBatchDraw();
		show_gobang();
		EndBatchDraw();
		//处理输入信息
		ExMessage msg;
		//获取消息
		if (peekmessage(&msg, EM_MOUSE)) {//获取鼠标输入
			switch (msg.message) {//消息类型
			case WM_MOUSEMOVE://鼠标移动消息
				mouse_move_message(&msg);
				break;
			case WM_LBUTTONDOWN: {//鼠标左右键按下
				int pre_chees = g_Pos.chess_play;
				mouse_press_mseeage(&msg);
				if (pre_chees != g_Pos.chess_play)robot();
				
				gamerscore++;
				break;
			}
			default:
				break;
			}
		}
	}
	if (g_Gobang_Map[g_Pos.row][g_Pos.col] == black) {
		for (int i = 0; i < ROW; ++i) {
			for (int j = 0; j < COL; ++j) {
				g_Gobang_Map[i][j] = 0;
			}
		}
		g_IsWin = 0;
		g_IsFull = 0;
		return 9999;
	}
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			g_Gobang_Map[i][j] = 0;
		}
	}
	g_IsWin = 0;
	g_IsFull = 0;
	return gamerscore;
}

void Gobang::rvr() {
	initgraph(840, 700, SHOWCONSOLE);
	for (int game_num = 0; game_num < 10; game_num++) {
		std::cout << "模拟第" << game_num + 1 << "局" << std::endl;
		std::cout << "黑棋胜利" << g_B_Win << "局" << std::endl;
		std::cout << "白棋胜利" << g_W_Win << "局" << std::endl;
		while (!g_IsWin && !g_IsFull) {
			BeginBatchDraw();
			show_gobang();
			EndBatchDraw();
			robot();
			Sleep(10);
		}
		system("cls");
		for (int i = 0; i < ROW; ++i) {
			for (int j = 0; j < COL; ++j) {
				g_Gobang_Map[i][j] = 0;
			}
		}
		g_IsWin = 0;
		g_IsFull = 0;
	}
	std::cout << "模拟第10局" << std::endl;
	std::cout << "黑棋胜利" << g_B_Win << "局" << std::endl;
	std::cout << "白棋胜利" << g_W_Win << "局" << std::endl;
	std::cout << "模拟完成,5秒后退出" << std::endl;
	Sleep(5000);
	system("cls");
}

void Gobang::gobang() {
	gamer_data_read();
	initgraph(840, 700, SHOWCONSOLE);
	gobang_loading();
	putimage(0, 0, &gobanglogin);
	std::cout << "ID:";
	std::cin >> g_ID;
	std::cout << "password:";
	std::cin >> g_Password;
	std::cout << "成功登入......";
	std::tuple<std::string, std::string, int> temp = { g_ID ,g_Password ,9999 };
	g_Gamer_Data.push_back(temp);
	Sleep(1000);
	system("cls");
	int PVRscore = 9999;
	while (1) {
		putimage(0, 0, &gobangmenu);
		char key = _getch();
		switch (key) {
		case 'p': {system("cls"); pvp(); break; }
		case 'o': {system("cls"); PVRscore = pvr(); break; }
		case 'i': {system("cls"); rvr();g_B_Win = 0;g_W_Win =0; break; }
		case 'y': {system("cls"); leader_board(); break; }
		case 'u': {system("cls"); gamer_data_write(); return; break; }
		default:
			break;    //异常处理
		}
		for (auto& data : g_Gamer_Data) {
			if (std::get<0>(data) == g_ID) {
				if (PVRscore < std::get<2>(data)) {
					std::get<2>(data) = PVRscore; // 更新第三个值为 PVRscore
				}
			}
		}
	}
}