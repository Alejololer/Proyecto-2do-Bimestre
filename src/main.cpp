#include "..\lib\global.h"
#include <cstdlib>
using namespace std;
void jugar();

void reiniciarDat(){
	string input;
	gotoxy(7,8);
	cout<<"Ingrese la clave para reiniciar los datos: ";
	ShowConsoleCursor(true);
	cin>>input;
	ShowConsoleCursor(false);
	cin.ignore(10000, '\n');
	if(input==CLAVE){
		for (auto &&i : lstPuntajes)
		{
			char aux[10]="-";
			i.pun=0;
			strncpy(i.nombre, aux, 10);
		}
		gotoxy(7,9);
		cout<<"Puntajes reiniciados!";
	}
	else{
		gotoxy(7,9);
		cout<<"Clave incorrecta!";
		return;
	}
}


void presentarPuntaje(puntaje p)
{
    setColor(BLACK,BROWN);
	gotoxy(7,p.pos+8);
    cout<<p.pos<<". "<<p.nombre;
	gotoxy(25,p.pos+8);
	cout<<"Score: "<<p.pun<<endl;
}

void presentarPuntajes(){
	gotoxy(7,8);
	cout<<"Puntajes altos";
	for (auto &&i : lstPuntajes)
	{
		presentarPuntaje(i);
	}
	
}

void jugar()

{
	int cuerpo[200][2];
indice=1, tamaño=3, x=10, y=12, dir=3, xc, yc, score=0, m=1, vel=95000 ;
game;
tecla;
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
		input();
		input();	
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
		cout<<"==> ";

		gotoxy(7, 8);
		cout<<"\n\t1. JUGAR\n";
		gotoxy(7, 9);
		cout<<"\n\t2. MOSTRAR PUNTUACIONES\n";
		gotoxy(7, 10);
		cout<<"\n\t3. RESETEAR PUNTAJE\n";
		gotoxy(7, 11);
		cout<<"\n\t4. SALIR\n";

		do{
			tecla=getch();
		} while (tecla != ARRIBA && tecla != ABAJO && tecla != ENTER);
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


int main()
{
	ShowConsoleCursor(false);
	leerArchivoBinario();
	int punt[100];
	int b=0;
	menu();
}		


