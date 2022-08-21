#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <windows.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27
#define ENTER 13

int cuerpo[200][2];
int indice=1, tamaño=3, x=10, y=12, dir=3, xc, yc, score=0, m=1, vel=95000 ;
bool game;
char tecla;
const string clave="TA1997";
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

struct puntaje{
    char nombre[10];
    int pun;
    int pos;
};
vector <puntaje> lstPuntajes;
const string pathfile= "..\\resources\\scores.txt";
const string pathfilebin= "..\\resources\\scores.dat";


void sortearScore(){
	int x=1;
	sort(lstPuntajes.begin(),lstPuntajes.end(), [](puntaje a, puntaje b){
		return a.pun>b.pun;
	});
	for (auto &&i : lstPuntajes)
	{
		i.pos=x;
		x++;
	}
	
}

void invertirScore(){
	sort(lstPuntajes.begin(),lstPuntajes.end(), [](puntaje a, puntaje b){
		return a.pun<b.pun;
	});
}

void escribirArchivoBinario()
{
    ofstream f(pathfilebin, ios::out | ios_base::binary );
    if(f.good())
    {
        for (auto &&prov : lstPuntajes)  // { [*],[*],[*]...}
            f.write((char *) &prov, sizeof(puntaje));
    }
    f.close();
}

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

void guardarPos(){
	cuerpo[indice][0]=x;
	cuerpo[indice][1]=y;
	indice++;
	if(indice==tamaño)
		indice=1;
}

void pintarCuerpo(){
	setColor(BLACK,GREEN);
	for(int i=1; i<tamaño; i++){
		gotoxy(cuerpo[i][0], cuerpo[i][1]);
		cout<<"+";
        gotoxy(0,0);
        cout<<" ";
	}
}

void borrarCuerpo(){
	gotoxy(cuerpo[indice][0],cuerpo[indice][1]);
	cout<<" ";
}

void input(){
	if(kbhit()){
			tecla=getch();
			switch(tecla){
				case ARRIBA: 
					if(dir!=2)
						dir=1;
					break;
				case ABAJO:	
					if(dir!=1)
						dir=2;
					break;
				case DERECHA: 
					if(dir!=4)
						dir=3;
					break;
				case IZQUIERDA:
					if(dir!=3)
						dir=4;
					break;
			}
	}
}

void crearComida(){
	setColor(BLACK, CYAN);
	if(x == xc && y == yc){
		xc=(rand()%100)+2;
		yc=(rand()%18+6);
		tamaño++;
		gotoxy(xc,yc);
		cout<<char(254);
		score++;
	}
}

bool terminarJuego(){
	if(y==5||y==25||x==1||x==100)
		return true;
	for(int i=tamaño-1; i>0;i--){
		if(cuerpo[i][0]==x && cuerpo[i][1]==y)
			return true;
	}
	return false;
}

void printPuntos(){
	setColor(BLACK,LBLUE);
	gotoxy(70,4);
	cout<<"Score:"<<score;
}

void cambiarVel(){
	if(score == m*2){
		vel-=5000;
		m++;
	}
}

void chequearScore(){
	for (auto &&i : lstPuntajes)
	{
		puntaje p;
		if(score>i.pun){
			p.pos=i.pos;
			p.pun=score;
			system("cls");
			margin();
			gotoxy(7,8);
			cout<<"Puntaje alto!";
			gotoxy(7,9);
			cout<<"Ingrese su nombre: ";
			ShowConsoleCursor(true);
			cin>>p.nombre;
			ShowConsoleCursor(false);
			cin.ignore(10000, '\n');
			lstPuntajes.push_back(p);
			sortearScore();
			lstPuntajes.pop_back();
			escribirArchivoBinario();
    		cont();
			break;
		}
	}
}