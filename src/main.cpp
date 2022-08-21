#include "..\lib\global.h"
#include <cstdlib>
using namespace std;
void jugar();

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

void presentarPuntaje(puntaje p)
{
    setColor(BLACK,BROWN);
	gotoxy(7,p.pos+8);
    cout<<p.pos<<". "<<p.nombre;
	gotoxy(18,p.pos+8);
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
		cout<<"\n\t3. SALIR\n";

		do{
			tecla=getch();
		} while (tecla != ARRIBA && tecla != ABAJO && tecla != ENTER);
		switch (tecla)
		{
			case ARRIBA: 
			opcionsel--;
			if (opcionsel == 0)
			{
				opcionsel=3;
			}
			break;

			case ABAJO: 
			opcionsel++;
			if (opcionsel == 4)
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
			end();
			menu();
			break;

			case 3:
            repetir=false;
			system("cls");
			break;		
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
			cin.ignore(10000, '\n');
			ShowConsoleCursor(false);
			lstPuntajes.push_back(p);
			sortearScore();
			lstPuntajes.pop_back();
			escribirArchivoBinario();
    		end();
			break;
		}
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


//Menu con seleccion de flecha
//Puntajes altos que se guardan entre cada ejecucion.	

