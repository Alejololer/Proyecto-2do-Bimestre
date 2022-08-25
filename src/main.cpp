/********************************************************************************
 Date:      26.08.2022
 Developer: Carlos Aleman y Alejandro Alvarez 
 Subject:   Proyecto 2do Bimestre
********************************************************************************/
#include "..\lib\global.h"
#include <cstdlib>
using namespace std;

void reiniciarDat(){
	string input;
	gotoxy(7,8);
	setColor(BLACK, LMAGENTA);
	cout<<"Ingrese la clave para reiniciar los datos: ";
	setColor(BLACK, WHITE);
	ShowConsoleCursor(true);
	cin>>input;
	ShowConsoleCursor(false);
	cin.clear();
	fflush(stdin);
	if(input==CLAVE){
		for (auto &&i : lstPuntajes)
		{
			char aux[10]=" ";
			i.pun=0;
			strncpy(i.nombre, aux, 10);
		}
		gotoxy(7,9);
		setColor(BLACK, GREEN);
		cout<<"Puntajes reiniciados!";
	}
	else{
		gotoxy(7,9);
		setColor(BLACK, RED);
		cout<<"Clave incorrecta!";
		return;
	}
}
//Procedimiento para reiniciar el puntaje, solamente pide la clave y si es correcta asigna
//los valores de " " y 0 para el nombre y el puntaje de las estructuras correspondientemente.


void presentarPuntaje(puntaje p)
{
    setColor(BLACK,LRED);
	gotoxy(7,p.pos+8);
    cout<<p.pos<<". ";
	setColor(BLACK,BROWN);
	cout<<p.nombre;
	gotoxy(25,p.pos+8);
	setColor(BLACK,YELLOW);
	cout<<"Score: "<<p.pun<<endl;
}
//Procedimiento que explora la estructura que se envia y la presente

void presentarPuntajes(){
	gotoxy(7,8);
	setColor(BLACK, LMAGENTA);
	cout<<"Puntajes altos";
	for (auto &&i : lstPuntajes)
	{
		presentarPuntaje(i);
	}
	
}
//Procedimiento para explorar la lista y enviar las estructuras a otro procedimiento

void jugar()

{
	int cuerpo[200][2];
indice=1, tamaño=3, x=10, y=12, dir=3, xc, yc, score=0, m=1, vel=95000 ;
	setColor(BLACK, CYAN);
	xc=(rand()%95)+2;
	yc=(rand()%18+6);
	gotoxy(xc,yc);
	cout<<char(254);
	margin();
	while(tecla != ESC && !terminarJuego()){
		borrarCuerpo();
		guardarPos();
		pintarCuerpo();
		crearComida();
		printPuntos();
		leerInput();
		leerInput();	
		cambiarVel();
		switch(dir){
			case 1: y--; break;
			case 2: y++; break;	
			case 3: x++; break;
			case 4: x--; break;
		}
		if(dir==3||dir==4)
			usleep(vel);
		else
			usleep(vel*1.5);
	}
	invertirScore();
	chequearScore();
}
//Primero reinicia los datos y luego ejecuta todos los procedimientos referentes al juego

void menu()
{
	bool repetir=true;
	int opcion;	
	int opcionsel=1; 
	int mayor=0;
	do{
		
		system("cls");
		margin();

		gotoxy(4,8+opcionsel);
		setColor(LCYAN, RED);
		cout<<"==> ";
		setColor(BLACK, CYAN);
		gotoxy(7, 8);
		if(opcionsel == 1)
		{
			setColor(LCYAN, RED);
			cout<<"\n\t1. JUGAR\n";
			setColor(BLACK, CYAN);
		}
		else
		cout<<"\n\t1. JUGAR\n";
		gotoxy(7, 9);
		if(opcionsel == 2)
		{
			setColor(LCYAN, RED);
			cout<<"\n\t2. MOSTRAR PUNTUACIONES\n";
			setColor(BLACK, CYAN);
		}
		else
		cout<<"\n\t2. MOSTRAR PUNTUACIONES\n";
		gotoxy(7, 10);
		if(opcionsel == 3)
		{
			setColor(LCYAN, RED);
			cout<<"\n\t3. RESETEAR PUNTAJE\n";
			setColor(BLACK, CYAN);
		}
		else
		cout<<"\n\t3. RESETEAR PUNTAJE\n";
		gotoxy(7, 11);
		if(opcionsel == 4)
		{
			setColor(LCYAN, RED);
			cout<<"\n\t4. SALIR\n";
			setColor(BLACK, CYAN);
		}
		else
		cout<<"\n\t4. SALIR\n";

		do{
			tecla=getch();
		} while (tecla != ARRIBA  && tecla != ABAJO && tecla != ENTER);
		switch (tecla)
		{
			case ARRIBA: 
			opcionsel--;
			if (opcionsel == 0)
			{
				opcionsel=4;
			}
			break;

			case ABAJO: 
			opcionsel++;
			if (opcionsel == 5)
			{
				opcionsel=1;
			}
			break;

			case ENTER: 
			repetir=false;
			break;
		}
		//cout<<"\n\tOpcion: ";
		//cin>>opcion;
	


	}while (repetir);
	switch(opcionsel)
		{
			case 1:
            system("cls");
            jugar();
			menu();
			break;

			case 2:
            system("cls");
			margin();
			sortearScore();
			presentarPuntajes();
			cont();
			menu();
			break;

			case 3:
			system("cls");
			margin();
			reiniciarDat();
			cont();
			menu();
			break;

			case 4:
            repetir=false;
			system("cls");
			break;		
		}
	 
}
//menu que hace uso de los inputs del teclado para simular la seleccion como en una GUI real


int main()
{
	ShowConsoleCursor(false);
	leerArchivoBinario();
	int punt[100];
	int b=0;
	menu();
}		


