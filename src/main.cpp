#include "..\lib\global.h"
#include <cstdlib>
using namespace std;
void menu();
void jugar();
void puntuaciones(int a);
void menu()
{
	ShowConsoleCursor(true);
	bool repetir=true;
	int opcion;
    int a;

	do{
		system("cls");
		cout<<"\n\t\t\t\tJUEGO ""LA SERPIENTE""\n";

		cout<<"\n\t1. JUGAR\n";
		cout<<"\n\t2. MOSTRAR ULTIMAS PUNTUACIONES\n";
		cout<<"\n\t3. SALIR\n";

		cout<<"\n\tOpcion: ";
		cin>>opcion;
		switch(opcion)
		{
			case 1:
             a++;
            system("cls");
            jugar();
			break;

			case 2:
            system("cls");
            puntuaciones(a);
			break;

			case 3:
            repetir=false;
			break;
		}


	}while (repetir); 
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

void jugar()

{
	x=10;
	y=12;
	dir=3;
    ShowConsoleCursor(false);
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
    end();

}

void puntuaciones(int a)
{
    for (int i = 0; i < a; i++)
    {
        gotoxy(5, i+3);
        cout<<"SCORE: "<<score;
    }
    end();

}

int main()
{
	menu();
}		


//Menu con seleccion de flecha
//Puntajes altos que se guardan entre cada ejecucion.	


//Menu con seleccion de flecha
//Puntajes altos que se guardan entre cada ejecucion.