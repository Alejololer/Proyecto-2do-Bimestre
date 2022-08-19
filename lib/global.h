#include <iostream>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
using namespace std;

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27

int cuerpo[200][2];
int indice=1, tamaño=3, x=10, y=12, dir=3, xc, yc, score=0, m=1, vel=95000 ;
bool game;
char tecla;
enum colors{
    BLACK=0,
    BLUE=1,
    GREEN=2,
    CYAN=3,
    RED=4,
    MAGENTA=5,
    BROWN=6,
    LGREY=7,
    DGREY=8,
    LBLUE=9,
    LGREEN=10,
    LCYAN=11,
    LRED=12,
    LMAGENTA=13,
    YELLOW=14,
    WHITE=15
};

void setColor(int Background, int Text){
    int colorTexto= Text + (Background*16);
    HANDLE terminal = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(terminal, colorTexto);    
}
void gotoxy(int x, int y)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=x;
    dwPos.Y=y;
    SetConsoleCursorPosition(hcon, dwPos);
}
void cont()
{
    setColor (BLACK,RED);
    gotoxy(30,22);
    cout<<("<<PULSE CUALQUIER TECLA PARA CONTINUAR>>");
    getch();
	setColor(BLACK,WHITE);
}
void end()
{
    setColor (BLACK,RED);
    gotoxy(30,22);
    cout<<("<<PULSE CUALQUIER TECLA PARA FINALIZAR>>");
    getch();
}
void margin()
{
	//cabecera
	int i;
	setColor (BLACK,LBLUE);
	gotoxy(35,2);
	cout<<("ESCUELA POLITECNICA NACIONAL");
	gotoxy(30,3);
	cout<<("Recreacion del juego de la serpiente");
	gotoxy(3,4);
	cout<<("Por: Alejandro Alvarez, Alejandro Aleman");
	for(i=1;i<=100;i++)
	{

		setColor (BLACK,DGREY);
		gotoxy(i,1);
		cout<<char(205);
		gotoxy(i,5);
		cout<<char(205);
		gotoxy(i,25);
		cout<<char(205);
	}
	for(i=1;i<=25;i++)
	{
		gotoxy(1,i);
		cout<<char(186);
		gotoxy(100,i);
		cout<<char(186);
	}
    gotoxy(1,1);
    cout<<char(201);
    gotoxy(1,5);
    cout<<char(204);
    gotoxy(1,25);
    cout<<char(200);
    gotoxy(100,1);
    cout<<char(187);
    gotoxy(100,5);
    cout<<char(185);
    gotoxy(100,25);
    cout<<char(188);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}