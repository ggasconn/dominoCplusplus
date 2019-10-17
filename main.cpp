/*
* Dominó realizado por Alejandro y Guillermo
*
* Happy Coding! :)
**/

#include <iostream>
#include <cstdlib>
#import <time.h>
#include <string>
#include <stdexcept>  //Contiene metodos que permiten devolver excepciones
#include <fstream>

using namespace std;


//Prototipos de funciones a usar durante el programa
int mostrarMenu();
string fichaToStr(short int izquierda, short int derecha);
void mostrarTablero(short int fichaN1, short int fichaN2, string tablero, int numColocadas, int numRobadas);
short int aleat();
string toStr(int n); // Se puede usar la implementada en C++11??
bool puedePonerIzq(string tablero, short int fichaN1, short int fichaN2);
bool puedePonerDer(string tablero, short int fichaN1, short int fichaN2);
int ponerFichaIzq(string tablero, short int fichaN1, short int fichaN2);
int ponerFichaDer(string tablero, short int fichaN1, short int fichaN2);
bool salvarPartida(string tablero);
char comprobarPartida();
string recuperarPartida();

/**
* Funcion principal, contiene un menu interminable. 
* Se finaliza la ejecución con 0.
*/
int main() {
    short int opcionElegida;
    string tablero = "";

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
        
        case 4:
            cout << ">>> Salvando partida a fichero game_history.txt" << endl;
            
            if (salvarPartida(tablero)) {
                cout << ">>> OK" << endl << endl;
            }else {
                cout << ">>> Error: no se pudo guardar la partida o se denegó la acción" << endl << endl;
            }

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

    cout << " ------------------" << endl;
    cout << "| MENU DE OPCIONES |" << endl;
    cout << " ------------------" << endl;
    cout << "1. Poner ficha por la izquierda" << endl;
    cout << "2. Poner ficha por la derecha" << endl;
    cout << "3. Robar ficha nueva" << endl;
    cout << "4. Salvar partida a fichero" << endl;
    cout << "0. Salir" << endl << endl;
    cout << "Elija una opción: ";

    cin >> opcionElegida;

    return opcionElegida;
}


/**
* Formatea una cadena en forma de ficha con los números recibidos como parámetros.
* En caso de que los números sean mayores que 6 se devuelve una excepción y se finaliza.
*
* @param izquierda. Contiene el número izquierdo de la ficha.
* @param izquierda. Contiene el número derecho de la ficha.
*
* @return Ficha formateada o excepción si hay error
*/
string fichaToStr(short int izquierda, short int derecha){
    // Nos aseguramos de que hemos recibido un numero que está disponible como ficha.
    // Si no es así se devuelve una excepción y acaba el juego por inconcluencia.
    if (izquierda > 6 || derecha > 6) throw invalid_argument("Los números de las fichas no pueden ser superiores a 6");

    string fichaFinal = "|";

    fichaFinal.append(toStr(izquierda) + "-" + toStr(derecha) + "|");

    return fichaFinal;
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
    return to_string(n);
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


/**
* Recibe como parámetro una cadena que guarda en un fichero.
* Si el fichero previamente existe se supone que ya hay una partida
* guardada y se pregunta si se desea sobreescribir.
*
* @param tablero. Contiene el estado actual de la partida.
*/
bool salvarPartida(string tablero){
    bool partidaSalvada = false;
    
    if (comprobarPartida() == 'y') {
        ofstream ficheroPartida;

        ficheroPartida.open("game_history.txt");

        ficheroPartida << tablero;

        partidaSalvada = true;

        ficheroPartida.close();
    }

    return partidaSalvada;
}


/**
* Comprueba si existe una partida guardada y pregunta si se quiere sobreescribir.
*
* @return Char siendo 'y' que no existe o se quiere borrar y 'n' que se interrumpe la operacion.
*/
char comprobarPartida() {
    char borrarPartida = 'y';
    ifstream ficheroPartida;

    ficheroPartida.open("game_history.txt");

    if (ficheroPartida.is_open()) {
        cout << endl << "@@@@@@@@@@@@" << endl;
        cout << "@ ATENCION @" << endl;
        cout << "@@@@@@@@@@@@" << endl;
        cout << "Se ha encontrado una partida guardada con el siguiente estado: " << endl;
        // TODO: La funcion que recupera el tablero devuelve un uno antes de la cadena, 
        // pero ese 1 no existe en el fichero. ¿Puede ser el numero de linea?
        cout << recuperarPartida() << endl;
        cout << "Seguro que desea sobrescribirla? (y/n): ";
        cin >> borrarPartida;
    }
    return borrarPartida;
}


/**
* Recupera la partida guardada en un fichero.
*
* @return Cadena con el estado de la partida o excepción en error
*/
string recuperarPartida(){
    string tablero;
    //Declara el objeto con el fichero y comprueba si existe.
    ifstream ficheroPartida;
    
    ficheroPartida.open("game_history.txt");

    if (! ficheroPartida.is_open()) {
        throw runtime_error("No se pudo abrir el fichero con el historial. Compruebe si existe o si ha sido borrado.");
    }else {
        cout << getline(ficheroPartida, tablero);
    }

    ficheroPartida.close();

    return tablero;
}

