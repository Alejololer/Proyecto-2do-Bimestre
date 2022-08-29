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
//Definicion de los inputs que usaremos en el programa

int cuerpo[200][2];
int indice, tamaño, x, y, dir, xc, yc, score, m=1, vel=95000 ;
//"x" y "y" nos sirven para tener las coordenadas de la serpiente
//"xc" y "yc" son las coordenadas de la comida;
bool game;
char tecla;
const string CLAVE="GN1976";
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
//enumeracion de colores para usar el procedimiento setColor
struct puntaje{
    char nombre[10];
    int pun;
    int pos;
};
vector <puntaje> lstPuntajes;
//declaracion de la estructura y el vector para listar los puntajes
const string pathfile= "..\\resources\\scores.txt";
const string pathfilebin= "..\\resources\\scores.dat";

bool leerArchivoBinario()
{
    ifstream rf(pathfilebin, ios::in | ios::binary);
    cout << "Abrir archivo:" << pathfilebin << endl;
    if(!rf) 
    {
        cout << " << error >>" << endl;
        return false;
    } 
    puntaje tp[1];
    while(rf.read((char *) &tp[0], sizeof(puntaje)))
        lstPuntajes.push_back(tp[0]);
    rf.close();
    return true;
}
//Funcion sencilla para conocer si el archivo se hizo correctamente

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
//Este procedimiento ordena los puntajes en funcion del int score, de mayor a menor

void invertirScore(){
	sort(lstPuntajes.begin(),lstPuntajes.end(), [](puntaje a, puntaje b){
		return a.pun<b.pun;
	});
}
//Este procedimiento ordena los puntajes en funcion del int score, de menor a mayor
//para realizar el chequeo
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
//Procedmiento sencillo para escribir los puntajes

void setColor(int Background, int Text){
    int colorTexto= Text + (Background*16);
    HANDLE terminal = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(terminal, colorTexto);    
}
//Procedimiento para cambiar el color de la consola
void gotoxy(int x, int y)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=x;
    dwPos.Y=y;
    SetConsoleCursorPosition(hcon, dwPos);
}
//Procedimiento para mover el cursor de la consola y ayudar a crear una pseudo GUI
void cont()
{
    setColor (BLACK,RED);
    gotoxy(30,22);
    cout<<("<<PULSE CUALQUIER TECLA PARA CONTINUAR>>");
    getch();
	setColor(BLACK,WHITE);
}
//Procedimiento para cuando el juego se acaba, solo pide presionar una tecla para continuar.
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
	setColor (BLACK,BROWN);
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
//Procedimiento que imprime el margen que se presenta.

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
//Procedimiento para mostrar o no mostrar el cursor de la consola, sirve para que no
//se observen las actualizaciones al jugar.

void guardarPos(){
	cuerpo[indice][0]=x;
	cuerpo[indice][1]=y;
	indice++;
	if(indice==tamaño)
		indice=1;
}
//Guardamos la posicion en la matriz cuerpo y reiniciamos el indice al ser igual al tamanio

void pintarCuerpo(){
	setColor(BLACK,GREEN);
	for(int i=1; i<tamaño; i++){
		gotoxy(cuerpo[i][0], cuerpo[i][1]);
		cout<<"+";
		gotoxy(0,0);
		cout<<" ";
	}
}
// Exploramos las posiciones e imprimimos la serpiente

void borrarCuerpo(){
	gotoxy(cuerpo[indice][0],cuerpo[indice][1]);
	cout<<" ";
}
// Para simular el movimiento procedemos a eliminar la ultima posicion de la serpiente

void leerInput(){
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
//Leemos el input del usuario con kbhit, y con las definiciones que se dieron previamente
//podemos definir si es que queremos que la serpiente suba o bajo

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
//randomizamos las posiciones de la comida cuando la cabeza de la serpiente sea igual
//a las coordenadas y aumentamos el tamanio y el puntaje


bool terminarJuego(){
	if(y==5||y==25||x==1||x==100)
		return true;
	for(int i=tamaño-1; i>0;i--){
		if(cuerpo[i][0]==x && cuerpo[i][1]==y)
			return true;
	}
	return false;
}
//Si es que las coordenadas de la serpiente llegan a ser iguales a la del margen, o a
//alguna parte de su cuerpo, el juego termina al regresar un valor verdadero.

void printPuntos(){
	setColor(BLACK,BROWN);
	gotoxy(70,4);
	cout<<"Score:"<<score;
}
//Procedimiento sencillo para imprimir el puntaje en la parte superior de la pantalla.

void cambiarVel(){
	if(score == m*2){
		vel-=5000;
		m++;
	}
}
//Procedimiento para chequear si el puntaje es multiplo de 2, aumentando la velocidad
//al disminuir el tiempo de espera del ciclo.

void pedirNombre(string etiqueta,puntaje &p){
	gotoxy(7,9);
	cout<<etiqueta;
	ShowConsoleCursor(true);
	cin.getline(p.nombre,10);
	ShowConsoleCursor(false);
	cin.clear();
	fflush(stdin);
}
//Procedimiento para mantener buenas practicas

void chequearScore(){
	for (auto &&i : lstPuntajes)
	{
		if(score>i.pun){
			puntaje p;
			p.pos=i.pos;
			p.pun=score;
			system("cls");
			margin();
			gotoxy(7,8);
			cout<<"Puntaje alto!";
			pedirNombre("Ingrese su nombre: ", p);
			lstPuntajes.push_back(p);
			sortearScore();
			lstPuntajes.pop_back();
			escribirArchivoBinario();
    		cont();
			break;
		}
	}
}
//Procedimiento para comparar el puntaje logrado con los puntajes de la lista de puntajes
//altos, si es verdadero creamos una estructura donde pedimos el nombre, cogemos el puntaje y
//robamos la posicion e insertamos la estructura en la posicion, reorganizamos la lista en base
//a puntaje y eliminamos el ultimo.