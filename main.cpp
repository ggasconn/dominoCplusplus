/*
* Version: 2.0
*
* Domino realizado por Alejandro y Guillermo
* Ambas partes extras realizadas
*
* Happy Coding! :)
**/

//perico

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <stdexcept>  //Contiene metodos que permiten devolver excepciones
#include <fstream>

using namespace std;

//Colores para editar la terminal
//Implementar estructura que contenga todos los colores
string fgRojo = "\033[1;31m";
string fgVerde = "\033[1;32m";
string fgAzul = "\033[1;34m";
string finColor = "\033[0m";


const short int numFichas = 55;     //Numero de ficha disponibles
typedef short int tArray[numFichas];


//Prototipos de funciones a usar durante el programa
void clear();
int mostrarMenu();
string fichaToStr(short int izquierda, short int derecha);
//void mostrarTablero(short int fichaN1, short int fichaN2, string tablero, int numColocadas, int numRobadas);
void mostrarTablero(string tablero, short int numColocadas, short int numRobadas, \
    const tArray fichas1, const tArray fichas2, short int fichasCont);
string toStr(int n); // Se puede usar la implementada en C++11??
bool puedePonerIzq(string tablero, short int fichaN1, short int fichaN2);
bool puedePonerDer(string tablero, short int fichaN1, short int fichaN2);
string ponerFichaIzq(string tablero, short int fichaN1, short int fichaN2);
string ponerFichaDer(string tablero, short int fichaN1, short int fichaN2);
void generarPozo(tArray pozo1, tArray pozo2, int varianteJuego, short int &pozoCont);
void desordenarPozo(tArray pozo1, tArray pozo2, short int pozoCont);
void robarFicha(const tArray pozo1, const tArray pozo2, short int &cont, short int &fichaN1, short int &fichaN2);
void eliminarFicha (tArray fichas1, tArray fichas2, short int &fichasCont, short int fichaNum);
bool puedeColocarFicha(const tArray fichas1, const tArray fichas2, short int fichasCont, string tablero);
short int sumarPuntos(const tArray fichas1, const tArray fichas2, short int fichasCont);
bool salvarPartida(string tablero , short int numColocadas, short int numRobadas, short int fichasCont, short int pozoCont,\
    const tArray pozo1, const tArray pozo2, const tArray fichas1, const tArray fichas2);
bool existePartida();
char confirmarBorrado();
void recuperarPartida(string &tablero , short int &numColocadas, short int &numRobadas, short int &fichasCont, \
    short int &pozoCont, tArray pozo1, tArray pozo2, tArray fichas1, tArray fichas2);


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
    short int varianteJuego = 6;
    tArray pozo1;
    tArray pozo2;
    tArray fichas1;
    tArray fichas2;
    short int fichaN1;
    short int fichaN2;
    short int pozoCont;
    short int fichasCont = 0;
    short int fichaNum;
    string tablero;
    bool salir = false;
    char restaurar;

    //Preguntar por la variante del juego
    do {
        cout << "Escoja el número máximo que puede tener una ficha (6-9): ";
        cin >> varianteJuego;
    } while (varianteJuego > 9 || varianteJuego < 6);

    //Llena el pozo y lo desordena
    generarPozo(pozo1, pozo2, varianteJuego, pozoCont);
    desordenarPozo(pozo1, pozo2, pozoCont);
    robarFicha(pozo1, pozo2, pozoCont, fichaN1, fichaN2);
    numRobadas++;
    tablero = fichaToStr(fichaN1, fichaN2);

    for (int i=0; i <= 6; i++) {
        robarFicha(pozo1, pozo2, pozoCont, fichaN1, fichaN2);
        fichas1[i] = fichaN1;
        fichas2[i] = fichaN2;
        fichasCont++;
        numRobadas++;
    }

    clear(); //Limpia la consola

    do {
        //Muestra el tablero y el menu
        mostrarTablero(tablero, numColocadas, numRobadas, fichas1, fichas2, fichasCont);
        opcionElegida = mostrarMenu();

        switch (opcionElegida) {
            case 0:
                salir = true;
                break;

            case 1:
                do {
                    cout << "¿Qué ficha quieres colocar? (1-" << fichasCont << "): ";
                    cin >> fichaNum;
                } while(fichaNum < 0 || fichaNum > fichasCont);

                if (0 < fichaNum || fichaNum <= fichasCont) {
                    fichaN1 = fichas1[fichaNum - 1];
                    fichaN2 = fichas2[fichaNum - 1];

                    if (puedePonerIzq(tablero, fichaN1, fichaN2)) {
                        tablero = ponerFichaIzq(tablero, fichaN1, fichaN2);
                        numColocadas++;
                        eliminarFicha(fichas1, fichas2, fichasCont, fichaNum);
                    }else {
                        cout << fgRojo << ">>> No se puede colocar una ficha a la izquierda" << finColor << endl << endl;
                    }
                }
                break;

            case 2:
                do {
                    cout << "¿Qué ficha quieres colocar? (1-" << fichasCont << "): ";
                    cin >> fichaNum;
                } while(fichaNum < 0 || fichaNum > fichasCont);

                if (0 < fichaNum || fichaNum <= fichasCont) {
                    fichaN1 = fichas1[fichaNum - 1];
                    fichaN2 = fichas2[fichaNum - 1];

                    if (puedePonerDer(tablero, fichaN1, fichaN2)) {
                        tablero = ponerFichaDer(tablero, fichaN1, fichaN2);
                        numColocadas++;
                        eliminarFicha(fichas1, fichas2, fichasCont, fichaNum);
                    }else {
                        cout << fgRojo << ">>> No se puede colocar una ficha a la derecha" << finColor << endl << endl;
                    }
                }
                break;

            case 3:
                if (puedeColocarFicha(fichas1, fichas2, fichasCont, tablero)) {
                    cout << fgRojo << ">>> Áun puedes colocar fichas" << finColor << endl;
                }else if (pozoCont <= 0) {
                    salir = true;
                }else {
                    robarFicha(pozo1, pozo2, pozoCont, fichaN1, fichaN2);
                    fichas1[fichasCont] = fichaN1;
                    fichas2[fichasCont] = fichaN2;
                    fichasCont++;
                    numRobadas++;
                }
                break;

            case 4:
                cout << fgVerde << ">>> Salvando partida a fichero game_history.txt" << finColor << endl;

                if (salvarPartida(tablero, numColocadas, numRobadas, fichasCont, pozoCont, pozo1, pozo2, fichas1, fichas2)) {
                    cout << fgVerde << ">>> OK" << finColor << endl << endl;
                }else {
                    cout << endl << fgRojo << ">>> Error: no se pudo guardar la partida o se denegó la acción" << finColor << endl << endl;
                }
                break;

            case 5:
                if(!existePartida()) {
                    cout << fgRojo << ">>> No existe ninguna partida guardada" << finColor << endl;
                }else {
                    recuperarPartida(tablero, numColocadas, numRobadas, fichasCont, pozoCont, \
                                        pozo1, pozo2, fichas1, fichas2);
                    cout << fgVerde << ">>> Partida restaurada" << finColor << endl << endl;
                }
                break;

            default:
                if (1 > opcionElegida || opcionElegida > 5) cout << fgRojo << ">>>" << opcionElegida << " no es una opción válida" << finColor << endl;
                break;
        }

        //clear();

        if (fichasCont == 0) {
            cout << fgVerde << "Has ganado!!" << finColor << endl;
            salir = true;
        }

        if (!puedeColocarFicha(fichas1, fichas2, fichasCont, tablero) && pozoCont <= 0) {
            cout << fgRojo << "No se pueden robar más fichas" << finColor << endl;
            cout << fgRojo << "Los puntos totales son: " << finColor;
            cout << fgVerde << sumarPuntos(fichas1, fichas2, fichasCont) << finColor << endl;
            salir = true;
        }
    } while(!salir);
}


/**
 * Limpia la consola dependiendo del sistema operativo.
 * No es la mejor manera de hacerlo.
 *
 */
 void clear() {
    if (system("CLS")) system("clear");
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
    cout << "5. Restaurar partida anterior" << endl;
    cout << "0. Salir" << endl;
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
    if (izquierda > 9 || derecha > 9) throw invalid_argument("Los números de las fichas no pueden ser superiores a 9");

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
void mostrarTablero(string tablero, short int numColocadas, short int numRobadas, \
                        const tArray fichas1, const tArray fichas2, short int fichasCont) {
    cout << " ------------------" << endl;
    cout << "|     TABLERO      |" << endl;
    cout << " ------------------" << endl;
    cout << tablero << endl;
    cout << "Fichas colocadas: " << numColocadas << " - Fichas robadas: " << numRobadas << endl;
    cout << "Fichas jugador: ";

    for (int i=0; i<=fichasCont-1; i++) {
        cout << "|" << fichas1[i] << "-" << fichas2[i] << "|";
    }

    cout << endl;
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
* Popula dos arrays con las fichas generadas. El array pozo1 se llena con
* los numeros izquierdos de las fiches y el pozo2 los numeros de la derecha.
*
* @param pozo1. Array que contiene los numeros izquierdos de las fichas
* @param pozo2. Array que contiene los numeros derechos de las fichas
*/
void generarPozo(tArray pozo1, tArray pozo2, int varianteJuego, short int &pozoCont) {
    for (int i=0; i <= varianteJuego; i++) {
        for (int x=i; x <= varianteJuego; x++) {
            pozo1[pozoCont] = i;
            pozo2[pozoCont] = x;
            pozoCont++;
        }
    }
}


/**
* Desordena mediante el algoritmo de Fisher-Yates los dos arrays de manera
* no sesgaga.
*
* @param pozo1. Array que contiene los numeros izquierdos de las fichas
* @param pozo2. Array que contiene los numeros derechos de las fichas
*/
void desordenarPozo(tArray pozo1, tArray pozo2, short int pozoCont) {
    int idx, i;
    short int tmp1, tmp2;
        for (int i = pozoCont - 1; i >= 0; i--) {
            idx = rand() % (i + 1);
            if (i != idx) {
                tmp1 = pozo1[i];
                tmp2 = pozo2[i];
                pozo1[i] = pozo1[idx];
                pozo2[i] = pozo2[idx];
                pozo1[idx] = tmp1;
                pozo2[idx] = tmp2;
            }
        }
}


/**
* Breve explicación
*
* @param
*
* @return
*/
void robarFicha(const tArray pozo1, const tArray pozo2, short int &cont, short int &fichaN1, short int &fichaN2) {
    fichaN1 = pozo1[cont - 1];
    fichaN2 = pozo2[cont - 1];
    cont--;
}


/**
* Breve explicación
*
* @param
*
* @return
*/
void eliminarFicha (tArray fichas1, tArray fichas2, short int &fichasCont, short int fichaNum) {
    for (int i = fichaNum - 1; i <= fichasCont - 2 ; i++) {
        fichas1[i] = fichas1[i+1];
        fichas2[i] = fichas2[i+1];
    }
    fichasCont--;
}


/**
* Breve explicación
*
* @param
*
* @return
*/
bool puedeColocarFicha(const tArray fichas1, const tArray fichas2, short int fichasCont, string tablero) {
    bool puedePoner = false;
    short int cont = 0;
    short int extremoIzquierda =  int(tablero[1]) - int('0');
    short int extremoDerecha = int(tablero[tablero.size() - 2]) - int('0');

    while(!puedePoner && cont < fichasCont) {
        if (fichas1[cont] == extremoIzquierda || fichas2[cont] == extremoDerecha) {
            puedePoner = true;
        }
        cont++;
    }

    return puedePoner;
}


/**
* Breve explicación
*
* @param
*
* @return
*/
short int sumarPuntos(const tArray fichas1, const tArray fichas2, short int fichasCont) {
    short int sumaPuntos = 0;

    for (int i=0; i<=fichasCont - 1; i++) {
        sumaPuntos += fichas1[i];
        sumaPuntos += fichas2[i];
    }

    return sumaPuntos;
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
bool salvarPartida(string tablero , short int numColocadas, short int numRobadas, short int fichasCont, short int pozoCont,\
                    const tArray pozo1, const tArray pozo2, const tArray fichas1, const tArray fichas2){
    bool partidaSalvada = false;

    if (confirmarBorrado() == 'y') {
        ofstream ficheroPartida;
        ficheroPartida.open("game_history.txt");

        //Se graban los datos linea a linea
        ficheroPartida << tablero << endl;
        ficheroPartida << numColocadas << endl;
        ficheroPartida << numRobadas << endl;
        ficheroPartida << fichasCont << endl;

        for (int i=0; i<=fichasCont-1; i++) {
            ficheroPartida << fichas1[i] << endl;
            ficheroPartida << fichas2[i] << endl;
        }

        ficheroPartida << pozoCont << endl;

        for (int x = 0; x<=pozoCont-1; x++) {
            ficheroPartida << pozo1[x] << endl;
            ficheroPartida << pozo2[x] << endl;
        }

        ficheroPartida.close();

        partidaSalvada = true;
    }

    return partidaSalvada;
}


/**
 * Comprueba si existe un fichero con una partida ya guardada.
 *
 * @return true si existe el fichero, false si no
 */
bool existePartida() {
    ifstream ficheroPartida;

    ficheroPartida.open("game_history.txt");

    return ficheroPartida.good();
}


/**
* Comprueba si existe una partida guardada y pregunta si se quiere sobreescribir.
*
* @return Char siendo 'y' que no existe o se quiere borrar y 'n' que se interrumpe la operacion.
*/
char confirmarBorrado() {
    char borrarPartida = 'y';

    if (existePartida()) {
        //struct datosPartida valores = recuperarPartida();

        cout << fgRojo << "@@@@@@@@@@@@" << finColor << endl;
        cout << fgRojo << "@ ATENCION @" << finColor << endl;
        cout << fgRojo << "@@@@@@@@@@@@" << finColor << endl;
        cout << "Se ha encontrado una partida guardada con el siguiente estado: " << endl;
        //cout << fgAzul << "Tablero: " << valores.tablero << "   Colocadas: " << valores.numColocadas \
        //<< "  Robadas: " << valores.numRobadas << finColor << endl;
        cout << "Seguro que desea sobrescribirla? (y/n): ";
        cin >> borrarPartida;
    }

    return borrarPartida;
}


/**
* Breve explicación
*
* @param
*
* @return
*/
void recuperarPartida(string &tablero , short int &numColocadas, short int &numRobadas, short int &fichasCont, \
                        short int &pozoCont, tArray pozo1, tArray pozo2, tArray fichas1, tArray fichas2) {
    ifstream ficheroPartida;
    ficheroPartida.open("game_history.txt");

    if (! ficheroPartida.is_open()) {
        throw runtime_error("No se pudo abrir el fichero con el historial. Compruebe si existe o si ha sido borrado.");
    }else {
        //Recupera linea a linea los datos y los mete en la posición adecuada
        ficheroPartida >> tablero;
        ficheroPartida >> numColocadas;
        ficheroPartida >> numRobadas;
        ficheroPartida >> fichasCont;

        for (int i=0; i<=fichasCont-1; i++) {
            ficheroPartida >> fichas1[i];
            ficheroPartida >> fichas2[i];
        }

        ficheroPartida >> pozoCont;

        for (int x = 0; x<=pozoCont-1; x++) {
            ficheroPartida >> pozo1[x];
            ficheroPartida >> pozo2[x];
        }
    }

    ficheroPartida.close();
}
