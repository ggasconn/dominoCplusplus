/*
* Domino realizado por Alejandro y Guillermo
*
* Happy Coding! :)
**/

#include <iostream>
#include <cstdlib>
#include <time.h>
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
string ponerFichaIzq(string tablero, short int fichaN1, short int fichaN2);
string ponerFichaDer(string tablero, short int fichaN1, short int fichaN2);
bool salvarPartida(string tablero, short int numColocadas, short int numRobadas);
bool existePartida();
char comprobarPartida();
string recuperarPartida();


/**
* Funcion principal, contiene un menu interminable. 
* Se finaliza la ejecución con 0.
*/
int main() {
    //Genera semilla para saltear el numero aleatorio
    srand(time(NULL));

    short int opcionElegida;
    short int numColocadas = 0;
    short int numRobadas = 0;
    short int fichaN1 = aleat();
    short int fichaN2 = aleat();
    bool haRobado;
    bool haColocado;
    string tablero = fichaToStr(aleat(), aleat());

    if(existePartida()) {
        char restaurar;

        cout << "Se ha encontrado una partida guardada. ¿Quiere restaurarla? (y/n): ";
        cin >> restaurar;

        if (restaurar == 'y') {
            string s = recuperarPartida();
            tablero = s.substr(0, s.find('&'));
            string x = s.substr(s.find('&') + 1, s.find_last_of('&')-s.find('&')-1);
            string y = s.substr(tablero.length() + x.length() + 2, s.find('&'));
            numColocadas = stoi(x);
            numRobadas = stoi(x);

            cout << endl << ">>> Partida restaurada" << endl;
        }
    }

    //Mostrar tablero
    mostrarTablero(fichaN1, fichaN2, tablero, numColocadas, numRobadas);
   
    do {
        bool haRobado = false;
        bool haColocado = false;

        opcionElegida = mostrarMenu();

        switch (opcionElegida)
        {
        case 1:
            if (puedePonerIzq(tablero, fichaN1, fichaN2)) {
                tablero = ponerFichaIzq(tablero, fichaN1, fichaN2);
                numColocadas++;
                haColocado = true;
            }else {
                haRobado = true;
                cout << ">>> No se puede colocar una ficha a la izquierda" << endl << endl;
            }
            break;
        
        case 2:
            if (puedePonerDer(tablero, fichaN1, fichaN2)) {
                tablero = ponerFichaDer(tablero, fichaN1, fichaN2);
                numColocadas++;
                haColocado = true;
            }else {
                haRobado = true;
                cout << ">>> No se puede colocar una ficha a la derecha" << endl << endl;
            }
            break;
        
        case 3:
            fichaN1 = aleat();
            fichaN2 = aleat();
            numRobadas++;
            haRobado = true;
            break;
        
        case 4:
            cout << ">>> Salvando partida a fichero game_history.txt" << endl;
            
            if (salvarPartida(tablero, numColocadas, numRobadas)) {
                cout << ">>> OK" << endl << endl;
            }else {
                cout << ">>> Error: no se pudo guardar la partida o se denegó la acción" << endl << endl;
            }

            break;

        default:
            if (opcionElegida != 0) cout << opcionElegida << " no es una opción válida" << endl;
            break;
        }

        if (!haRobado)
        {
            fichaN1 = aleat();
            fichaN2 = aleat();
        }
        

        //Mostrar tablero
        mostrarTablero(fichaN1, fichaN2, tablero, numColocadas, numRobadas);

    } while(opcionElegida != 0);
}


/**
* Devuelve menu principal con opciones y recupera la elegida.
*
* @return Devuelve un entero, que hace referencia a la opcion elegida.
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

    cout << endl;

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
* Devuelve el tablero de la partida con los valores recibidos
*
* @param fichaN1
* @param fichaN2
* @param tablero
* @param numColocadas
* @param numRobadas
*
* @return La funcion no devuelve nada, pero durante la ejecución
* va imprimiendo el tablero con los datos recibidos
*/
void mostrarTablero(short int fichaN1, short int fichaN2, 
                    string tablero, int numColocadas, int numRobadas){
    cout << " ------------------" << endl;
    cout << "|     TABLERO      |" << endl;
    cout << " ------------------" << endl;
    cout << tablero << endl;
    cout << "Fichas colocadas: " << numColocadas << " - Fichas robadas: " << numRobadas << endl;
    cout << "Ficha jugador: " << fichaToStr(fichaN1, fichaN2) << endl << endl;
}


/**
* Devuelve un entero aleatorio entre 1 y 6
*
* @return Devuelve un entero dentro del rango 1-6
*/
short int aleat(){
    int numAleat;
    
    numAleat = rand() % 6 + 1;

    return numAleat;
}


/**
* Convierte un entero recibido a string
*
* @param n Entero a convertir
*
* @return Devuelve una cadena con el entero recibido
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
*
* @return Devuelve true si se puede poner, false si no.
*/
bool puedePonerIzq(string tablero, short int fichaN1, short int fichaN2){
    //Usando indices, saca el segundo caracter de la cadena
    bool sePuede = false;
    short int extremoTablero =  int(tablero[1]) - int('0');

    if (fichaN1 == extremoTablero || fichaN2 == extremoTablero) sePuede = true;

    return sePuede;
}


/**
* Breve descripcion de la funcion
*
* @param tablero
* @param fichaN1
* @param fichaN2
*
* @return Devuelve true si se puede poner, false si no.
*/
bool puedePonerDer(string tablero, short int fichaN1, short int fichaN2){
    bool sePuede = false;
    short int extremoTablero = int(tablero[tablero.size() - 2]) - int('0');

    if (fichaN1 == extremoTablero || fichaN2 == extremoTablero) sePuede = true;

    return sePuede;
}


/**
* Recibe el tablero y la ficha a colocar, si se puede realizar la acción
* coloca la ficha en la posicion adecuada dentro del tablero, si no se puede
* deja el tablero como estaba.
*
* @param tablero
* @param fichaN1
* @param fichaN2
*
* @return Devuelve el tablero actualizado o no.
*/
string ponerFichaIzq(string tablero, short int fichaN1, short int fichaN2){
    short int extremoTablero =  int(tablero[1]) - int('0');
    string fichaFinal;

    if (extremoTablero == fichaN1) {
        fichaFinal = fichaToStr(fichaN2, fichaN1);
    }else {
        fichaFinal = fichaToStr(fichaN1, fichaN2);
    }

    tablero = fichaFinal.append(tablero);

    return tablero;
}


/**
* Recibe el tablero y la ficha a colocar, si se puede realizar la acción
* coloca la ficha en la posicion adecuada dentro del tablero, si no se puede
* deja el tablero como estaba.
*
* @param tablero
* @param fichaN1
* @param fichaN2
*
* @return Devuelve el tablero actualizado o no.
*/
string ponerFichaDer(string tablero, short int fichaN1, short int fichaN2){
    short int extremoTablero = int(tablero[tablero.size() - 2]) - int('0');
    string fichaFinal;

    if (extremoTablero == fichaN1) {
        fichaFinal = fichaToStr(fichaN1, fichaN2);
    }else {
        fichaFinal = fichaToStr(fichaN2, fichaN1);
    }

    tablero = tablero.append(fichaFinal);

    return tablero;
}


/**
* Recibe como parámetro una cadena que guarda en un fichero.
* Si el fichero previamente existe se supone que ya hay una partida
* guardada y se pregunta si se desea sobreescribir.
*
* @param tablero. Contiene el estado actual de la partida.
*
* @return Devuelve true si la partida se guardo, false si no.
*/
bool salvarPartida(string tablero , short int numColocadas, short int numRobadas){
    bool partidaSalvada = false;
    
    if (comprobarPartida() == 'y') {
        ofstream ficheroPartida;

        ficheroPartida.open("game_history.txt");

        ficheroPartida << tablero << "&" << numColocadas << "&" << numRobadas;

        partidaSalvada = true;

        ficheroPartida.close();
    }

    return partidaSalvada;
}


/**
 * Comprueba si existe un fichero con una partida ya guardada.
 * 
 * @return true si existe el fichero, false si no
 */
bool existePartida() {
    bool existe = false;
    ifstream ficheroPartida;

    ficheroPartida.open("game_history.txt");

    if (ficheroPartida.is_open()) {
        existe = true;
        ficheroPartida.close();
    }

    return existe;
}


/**
* Comprueba si existe una partida guardada y pregunta si se quiere sobreescribir.
*
* @return Char siendo 'y' que no existe o se quiere borrar y 'n' que se interrumpe la operacion.
*/
char comprobarPartida() {
    char borrarPartida = 'y';
    
    if (existePartida()) {
        string s = recuperarPartida();
        string x = s.substr(0, s.find('&'));
        string y = s.substr(s.find('&') + 1, s.find_last_of('&')-s.find('&')-1);
        string z = s.substr(x.length() + y.length() + 2, s.find('&'));

        
        cout << endl << "@@@@@@@@@@@@" << endl;
        cout << "@ ATENCION @" << endl;
        cout << "@@@@@@@@@@@@" << endl;
        cout << "Se ha encontrado una partida guardada con el siguiente estado: " << endl;
        cout << "Tablero: " << x << "   Colocadas: " << y << "  Robadas: " << z << endl;
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
    string datosPartida;
    //Declara el objeto con el fichero y comprueba si existe.
    ifstream ficheroPartida;
    
    ficheroPartida.open("game_history.txt");

    if (! ficheroPartida.is_open()) {
        throw runtime_error("No se pudo abrir el fichero con el historial. Compruebe si existe o si ha sido borrado.");
    }else {
        getline(ficheroPartida, datosPartida);
    }

    ficheroPartida.close();

    return datosPartida;
}
