#include".\include\push_box.h"

int g_AllMap[3][10][10]{ 
	{
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,2,3,1,0,0,0,1 },
		{ 1,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,0,4,0,0,0,3,1 },
		{ 1,1,1,1,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,2,0,0,1 },
		{ 1,0,2,0,0,1,0,0,0,1 },
		{ 1,0,0,3,1,1,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
	},
	{
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,2,3,1,0,0,0,1 },
		{ 1,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,0,4,0,0,0,3,1 },
		{ 1,1,1,1,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,2,0,0,1 },
		{ 1,0,2,0,0,1,0,0,0,1 },
		{ 1,0,0,3,1,1,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
	},
	{
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,2,3,1,0,0,0,1 },
		{ 1,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,0,4,0,0,0,3,1 },
		{ 1,1,1,1,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,2,0,0,1 },
		{ 1,0,2,0,0,1,0,0,0,1 },
		{ 1,0,0,3,1,1,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
	},
};//0代表空地，1代表墙，2代表箱子，3代表目的地，4代表人，5代表箱子在目的地上，7代表人在目的地上
int g_Push_Box_Map[10][10];//当前的地图
int g_Level = 0;//游戏关卡
int g_Theme = 1;//推箱子主题
int g_R, g_C; //人的行与列
bool g_WoL = true;//win or ose
std::unordered_map<int, int> g_NumsGetBox;//箱子到达的数量
IMAGE wall, people, box, goal, blank, getbox, gamewin, gamelose, gameend, themeselection; //图标

void PushBox::push_box_loading(int th) {
	//地图框架
	switch (th) {
	case 1: {
		loadimage(&wall, _T("..\\assets\\pushBox图标\\wall.jpg"), 80, 80);
		loadimage(&people, _T("..\\assets\\pushBox图标\\people1.png"), 80, 80);
		loadimage(&box, _T("..\\assets\\pushBox图标\\box1.jpg"), 80, 80);
		loadimage(&goal, _T("..\\assets\\pushBox图标\\goal1.jpg"), 80, 80);
		loadimage(&blank, _T("..\\assets\\pushBox图标\\blank.jpg"), 80, 80);
		loadimage(&getbox, _T("..\\assets\\pushBox图标\\getbox1.jpg"), 80, 80);
		loadimage(&gamewin, _T("..\\assets\\pushBox图标\\gamewin1.png"), 800, 800);
		loadimage(&gamelose, _T("..\\assets\\pushBox图标\\gamelose1.png"), 800, 800);
		loadimage(&gameend, _T("..\\assets\\pushBox图标\\gameend.jpg"), 800, 800);
		loadimage(&themeselection, _T("..\\assets\\pushBox图标\\themeselection.jpg"), 800, 800);
		break;
	}
	case 2: {
		loadimage(&wall, _T("..\\assets\\pushBox图标\\wall.jpg"), 80, 80);
		loadimage(&people, _T("..\\assets\\pushBox图标\\people2.png"), 80, 80);
		loadimage(&box, _T("..\\assets\\pushBox图标\\box2.jpg"), 80, 80);
		loadimage(&goal, _T("..\\assets\\pushBox图标\\goal2.jpg"), 80, 80);
		loadimage(&blank, _T("..\\assets\\pushBox图标\\blank.jpg"), 80, 80);
		loadimage(&getbox, _T("..\\assets\\pushBox图标\\getbox2.jpg"), 80, 80);
		loadimage(&gamewin, _T("..\\assets\\pushBox图标\\gamewin2.png"), 800, 800);
		loadimage(&gamelose, _T("..\\assets\\pushBox图标\\gamelose2.png"), 800, 800);
		loadimage(&gameend, _T("..\\assets\\pushBox图标\\gameend.jpg"), 800, 800);
		loadimage(&themeselection, _T("..\\assets\\pushBox图标\\themeselection.jpg"), 800, 800);
		break;
	}
	case 3: {
		loadimage(&wall, _T("..\\assets\\pushBox图标\\wall.jpg"), 80, 80);
		loadimage(&people, _T("..\\assets\\pushBox图标\\people3.png"), 80, 80);
		loadimage(&box, _T("..\\assets\\pushBox图标\\box3.jpg"), 80, 80);
		loadimage(&goal, _T("..\\assets\\pushBox图标\\goal3.jpg"), 80, 80);
		loadimage(&blank, _T("..\\assets\\pushBox图标\\blank.jpg"), 80, 80);
		loadimage(&getbox, _T("..\\assets\\pushBox图标\\getbox3.jpg"), 80, 80);
		loadimage(&gamewin, _T("..\\assets\\pushBox图标\\gamewin3.png"), 800, 800);
		loadimage(&gamelose, _T("..\\assets\\pushBox图标\\gamelose3.png"), 800, 800);
		loadimage(&gameend, _T("..\\assets\\pushBox图标\\gameend.jpg"), 800, 800);
		loadimage(&themeselection, _T("..\\assets\\pushBox图标\\themeselection.jpg"), 800, 800);
		break;
	}
	}
}
void PushBox::init_map() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			g_Push_Box_Map[i][j] = g_AllMap[g_Level][i][j];
		}
	}
}
void PushBox::theme_selection() {
	putimage(0, 0, &themeselection);
	while (1) {
		char key = _getch();
		switch (key) {
		case '1':
			g_Theme = 1;
			break;
		case '2':
			g_Theme = 2;
			break;
		case '3':
			g_Theme = 3;
			break;
		default:
			continue;
		}
		if (g_Theme != 0) {
			break;
		}
	}
}

void PushBox::show_icon() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			switch (g_Push_Box_Map[i][j]) {
			case 0:putimage(j * 80, i * 80, &blank); break;//空地
			case 1:putimage(j * 80, i * 80, &wall); break;//墙
			case 2:putimage(j * 80, i * 80, &box); break;//箱子
			case 3:putimage(j * 80, i * 80, &goal); break;//目的地
			case 4:putimage(j * 80, i * 80, &people); break;//人
			case 5:putimage(j * 80, i * 80, &getbox); break;//箱子在目的地上
			case 7:putimage(j * 80, i * 80, &people); break;//人在目的地上
			}
		}
	}
}
void PushBox::find_people() {
	bool is_find = false;
	//时刻找到人的位置
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (g_Push_Box_Map[i][j] == 4 || g_Push_Box_Map[i][j] == 7) {
				g_R = i;
				g_C = j;
				is_find = true;
				break;
			}
		}
		if (is_find)break;
	}
}

bool PushBox::get_box() {
	int num = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (g_Push_Box_Map[i][j] == 5)num++;
		}
	}
	int a = g_NumsGetBox[num];
	g_NumsGetBox[num]++;
	int b = g_NumsGetBox[num];
	return (a == 0 && b == 1 && num != 0);
}
void PushBox::key() {
	//按键
KEY:
	char key = _getch();
	int keyr, keyc;
	switch (key) {
	case 'w':keyr = -1, keyc = 0; break;
	case 's':keyr = 1, keyc = 0; break;
	case 'a':keyr = 0, keyc = -1; break;
	case 'd':keyr = 0, keyc = 1; break;
	case 'q':g_WoL = false; keyr = 0, keyc = 0; break;
	default:
		goto KEY;    //异常处理
	}
	//如果人移动方向是空地或目的地
	if (g_Push_Box_Map[g_R + keyr][g_C + keyc] == 0 || g_Push_Box_Map[g_R + keyr][g_C + keyc] == 3) {
		g_Push_Box_Map[g_R + keyr][g_C + keyc] += 4;
		g_Push_Box_Map[g_R][g_C] -= 4;
	}
	//如果人移动方向是箱子
	else if (g_Push_Box_Map[g_R + keyr][g_C + keyc] == 2 || g_Push_Box_Map[g_R + keyr][g_C + keyc] == 5) {
		//人移动方向的移动方向是空地或目的地
		if (g_Push_Box_Map[g_R + 2 * keyr][g_C + 2 * keyc] == 0 || g_Push_Box_Map[g_R + 2 * keyr][g_C + 2 * keyc] == 3) {
			g_Push_Box_Map[g_R + 2 * keyr][g_C + 2 * keyc] += 2;
			g_Push_Box_Map[g_R + keyr][g_C + keyc] += 2;
			g_Push_Box_Map[g_R][g_C] -= 4;
		}

		//人移动方向的移动方向是箱子或墙
	}
	//如果人右面是墙
}
bool PushBox::game_win() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (g_Push_Box_Map[i][j] == 2)return false;
		}
	}
	return true;
}
void PushBox::game_play() {
	PushBox::push_box_loading(g_Theme);
	while (g_Level < 4) {
		if (!g_WoL) {
			g_WoL = true;
			Sleep(500);
			putimage(0, 0, &gamelose);
			break;
		}
		std::cout << " 第" << " " << g_Level + 1 << " " << "关" << std::endl;
		std::cout << "本游戏为推箱子游戏套皮,玩家需要控制w(上)s(下)a(左)d(右)  (按q结束游戏)" << '\n';
		std::cout << "来推动人物吃到食物" << '\n';
		std::cout << "本游戏素材均来自网络，别举办我:-)" << '\n';
		//std::cout << "下载千恋万花 卸载爱抚基欧喵,谢谢喵谢谢喵" << '\n';
		init_map();
		show_icon();
		g_NumsGetBox.clear();
		while (1) {
			/*system("cls");
			for (int i = 0;i < 10;i++) {
				for (int j = 0;j < 10;j++) {
					cout << map[i][j] << " ";
				}
				cout << '\n';
			}*/
			find_people();
			key();
			show_icon();
			if (get_box()) {
				std::cout << "box has been taken" << std::endl;
			}
			if (game_win()) {
				show_icon();
				Sleep(2000);
				putimage(0, 0, &gamewin);
				Sleep(2000);
				g_Level++;//记录关卡
				system("cls");
				break;
			}
			else if (!g_WoL) {
				break;
			}
		}
		if (g_Level == 3) {
			g_Level = 0;//初始化
			putimage(0, 0, &gameend);
			Sleep(2000);
			break;
		}
	}
	Sleep(2000);
	system("cls");
}
void PushBox::push_box() {
	initgraph(800, 800, SHOWCONSOLE);
	IMAGE menu;
	loadimage(&menu, _T("..\\assets\\pushBox图标\\menu.jpg"), 800, 800);
	while (1) {
		putimage(0, 0, &menu);
		char key = _getch();
		//int keyr, keyc;
		bool exit = 0;
		switch (key) {
		case 'p':game_play(); break;
		case 'o':theme_selection(); break;
		case 'i':return; break;
		default:
			break;    //异常处理
		}
	}
}
