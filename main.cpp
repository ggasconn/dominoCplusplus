#include <iostream>
#include <cstdlib>
#import <time.h>

using namespace std;


//Prototipos de funciones a usar durante el programa
int mostrarMenu();
string fichaToStr(short int izquierda, short int derecha);
void mostrarTablero(short int fichaN1, short int fichaN2, string tablero, int numColocadas, int numRobadas);
short int aleat();
string toStr(int n); // Se puede usar la implementada en C++???
bool puedePonerIzq(string tablero, short int fichaN1, short int fichaN2);
bool puedePonerDer(string tablero, short int fichaN1, short int fichaN2);
int ponerFichaIzq(string tablero, short int fichaN1, short int fichaN2);
int ponerFichaDer(string tablero, short int fichaN1, short int fichaN2);


/**
* Funcion principal, contiene un menu interminable. 
* Se finaliza la ejecución con 0.
*/
int main() {
    short int opcionElegida;

    do {
        opcionElegida = mostrarMenu();

        switch (opcionElegida)
        {
        case 1:
            cout << "Elegida opción 1" << endl;
            break;
        
        case 2:
            cout << "Elegida opción 2" << endl;
            break;
        
        case 3:
            cout << "Elegida opción 3" << endl;
            break;
        
        default:
            if (opcionElegida != 0) cout << opcionElegida << " no es una opción válida" << endl;
            break;
        }

    } while(opcionElegida != 0);
}


/**
* Devuelve menu principal con opciones y recupera la elegida.
*/
int mostrarMenu() {
    short int opcionElegida; // Almacena lo que el usuario elije del menu

    cout << "-------------------" << endl;
    cout << "| MENU DE OPCIONES |" << endl;
    cout << "-------------------" << endl;
    cout << "1. Poner ficha por la izquierda" << endl;
    cout << "2. Poner ficha por la derecha" << endl;
    cout << "3. Robar ficha nueva" << endl;
    cout << "0. Salir" << endl << endl;
    cout << "Elija una opción: ";

    cin >> opcionElegida;

    return opcionElegida;
}

/**
* Breve descripcion de la funcion
*
* @param
* @param
*/
string fichaToStr(short int izquierda, short int derecha){

}


/**
* Breve descripcion de la funcion
*
* @param fichaN1
* @param fichaN2
* @param tablero
* @param numColocadas
* @param numRobadas
*/
void mostrarTablero(short int fichaN1, short int fichaN2, string tablero, int numColocadas, int numRobadas){

}


/**
* Deuvuelve un entero aleatorio entre 1 y 6
*/
short int aleat(){
    int numAleat;
    //Genera semilla para saltear el numero aleatorio
    srand(time(NULL));

    numAleat = rand() % 6 + 1;

    return numAleat;
}


/**
* Breve descripcion de la funcion
*
* @param n
*/
string toStr(int n){ // Se puede usar la implementada en C++???

}


/**
* Breve descripcion de la funcion
*
* @param tablero
* @param fichaN1
* @param fichaN2
*/
bool puedePonerIzq(string tablero, short int fichaN1, short int fichaN2){

}


/**
* Breve descripcion de la funcion
*
* @param tablero
* @param fichaN1
* @param fichaN2
*/
bool puedePonerDer(string tablero, short int fichaN1, short int fichaN2){

}


/**
* Breve descripcion de la funcion
*
* @param tablero
* @param fichaN1
* @param fichaN2
*/
int ponerFichaIzq(string tablero, short int fichaN1, short int fichaN2){

}


/**
* Breve descripcion de la funcion
*
* @param tablero
* @param fichaN1
* @param fichaN2
*/
int ponerFichaDer(string tablero, short int fichaN1, short int fichaN2){

}