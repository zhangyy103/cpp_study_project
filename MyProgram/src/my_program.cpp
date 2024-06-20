#include".\include\my_program.h"

IMAGE myprogram;
void myProgramLoading() {
loadimage(&myprogram, _T("..\\assets\\myProgramÍ¼±ê\\background.jpg"), 960, 600);
}
void myProgram() {
	initgraph(960, 600, SHOWCONSOLE);
	putimage(0, 0, &myprogram);
	char key = _getch();
	closegraph();
	switch (key) {
	case 'a':
		PushBox::push_box();
		break;
	case 'b':
		Gobang::gobang();
		break;
	case 'e':exit(0);break;
	default:
		break;    
	}
 	closegraph();
}



int main() {
	myProgramLoading();
	while (true) {
		myProgram();
	}
}
