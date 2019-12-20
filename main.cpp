/*
* Version: 3.0
*
* Domino realizado por Alejandro Perea y Guillermo Gascon
*
* Happy Coding! :)
**/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <stdexcept>  //Contiene metodos que permiten devolver excepciones
#include <fstream>
#include <locale.h>

using namespace std;

//Colores para editar la terminal
string fgRojo = "\033[1;31m";
string fgVerde = "\033[1;32m";
string fgAzul = "\033[1;34m";
string finColor = "\033[0m";

const short int numFichas = 55;     //Numero de fichas disponibles
const short int MinJugadores = 2, MaxJugadores = 4;

//Declaración de tipos personalizados
typedef struct {
    short int izquierda, derecha;
} tFicha;

typedef tFicha tFichaArray[numFichas];

typedef struct {
    tFichaArray fichas;
    int contador;
} tListaFichas;

typedef tListaFichas tJugadores[MaxJugadores];
typedef int tPuntosJugadores[MaxJugadores];

typedef struct {
    string tablero;
    tListaFichas pozo;
    tJugadores jugadores;
    tPuntosJugadores puntos;
    int numJugadores;
    short int maxDig;
} tJuego;


//Prototipos de funciones a usar durante el programa
void clear();
int mostrarMenu();
string fichaToStr(tFicha ficha);
void mostrarTablero(const tJuego &juego);
string toStr(int n);
bool puedePonerIzq(string tablero, tFicha ficha);
bool puedePonerDer(string tablero, tFicha ficha);
void ponerFichaIzq(string &tablero, tFicha ficha);
void ponerFichaDer(string &tablero, tFicha ficha);
void generarPozo(tListaFichas &pozo, int varianteJuego);
void desordenarPozo(tListaFichas &pozo);
bool robarFicha(tListaFichas &pozo, tFicha &ficha);
void eliminarFicha (tListaFichas &lista, int indice);
bool puedeColocarFicha(const tListaFichas &jugador, string tablero);
int sumarPuntos(const tListaFichas &jugador);
bool operator==(tFicha opLeft, tFicha opRight);
bool contiene(tListaFichas fichas, tFicha ficha, int &indice);
int quienEmpieza(const tJuego &juego, int& indice);
void iniciar(tJuego &juego, int &jugador);
void configurarJuego(tJuego &juego, int &jugador);
bool sinSalida(const tJuego &juego);
bool estrategia1(tJuego &juego, int jugador);
bool estrategia2(tJuego &juego, int jugador);
bool leerJuego(tJuego &juego, int &jugador);
bool existePartida(string nombreFichero);
void leerListaFichas(ifstream &entrada, tListaFichas &listaFichas);
void escribirJuego(const tJuego& juego, int &jugador);
void escribirListaFichas(ofstream &salida, const tListaFichas &listaFichas);


/**
* Funcion principal.
*/
int main() { 
    srand(time(NULL)); //Genera semilla para saltear el numero aleatorio
    setlocale (LC_ALL,""); //Permite usar carácteres ISO

    short int opcionElegida;
    int jugador;
    tJuego juego;
    tFicha ficha;
    bool ganado, interrumpido, jugar, haColocado;
    char guardar, reiniciar;
    short int fichaNum, sumaPuntos;

    //Hace las preguntas iniciales e inicializa la partida
    configurarJuego(juego, jugador);
   
    do {
        jugar = true;
        interrumpido = false;
        ganado = false;
        haColocado = false;

        do {
            mostrarTablero(juego);
            if (jugador == 0) {
                opcionElegida = mostrarMenu();

                switch (opcionElegida) {
                    case 0:
                        interrumpido = true;
                        break;        

                    case 1:
                        do {
                            cout << "¿Qué ficha quieres colocar? (1-" << juego.jugadores[0].contador << "): ";
                            cin >> fichaNum;
                        }while(fichaNum < 1 || fichaNum > juego.jugadores[0].contador);

                        clear();

                        if (puedePonerIzq(juego.tablero, juego.jugadores[0].fichas[fichaNum - 1])) {
                            ponerFichaIzq(juego.tablero, juego.jugadores[0].fichas[fichaNum - 1]);
                            juego.puntos[0]++;
                            eliminarFicha(juego.jugadores[0], fichaNum - 1);

                            juego.jugadores[0].contador == 0 ? ganado = true : jugador = (++jugador) % juego.numJugadores;  
                        }else {
                            cout << fgRojo << ">>> No se puede colocar una ficha a la izquierda" << finColor << endl << endl;
                        }
                        break;
                    
                    case 2:
                        do {
                            cout << "¿Qué ficha quieres colocar? (1-" << juego.jugadores[0].contador << "): ";
                            cin >> fichaNum;
                        }while(fichaNum < 1 || fichaNum > juego.jugadores[0].contador);

                        clear();

                        if (puedePonerDer(juego.tablero, juego.jugadores[0].fichas[fichaNum - 1])) {
                            ponerFichaDer(juego.tablero, juego.jugadores[0].fichas[fichaNum - 1]);
                            juego.puntos[0]++;
                            eliminarFicha(juego.jugadores[0], fichaNum - 1);

                            juego.jugadores[0].contador == 0 ? ganado = true : jugador = (++jugador) % juego.numJugadores;  
                        }else {
                            cout << fgRojo << ">>> No se puede colocar una ficha a la derecha" << finColor << endl << endl;
                        }
                        break;
                    
                    case 3:
                        clear();
                        if (puedeColocarFicha(juego.jugadores[0], juego.tablero)) {
                            cout << fgRojo << ">>> Aún puedes colocar fichas!" << finColor << endl;
                        }else if(juego.pozo.contador == 0) {
                            cout << fgRojo << ">>> No se pueden robar más fichas" << finColor << endl;
                            jugador = (++jugador) % juego.numJugadores;  
                        }else {
                            robarFicha(juego.pozo, ficha);
                            juego.jugadores[0].fichas[juego.jugadores[0].contador] = ficha;
                            juego.jugadores[0].contador++;
                        }

                        break;
                }
            }else {
                    haColocado = jugador == 1 ? estrategia2(juego, jugador) : estrategia1(juego, jugador);
                    
                    if (haColocado) {
                        juego.puntos[jugador]++;
                        if (juego.jugadores[jugador].contador == 0) {
                            ganado = true;
                        }else {
                            jugador = (++jugador) % juego.numJugadores;  
                        }
                    }else {
                        if (juego.pozo.contador == 0) {
                            jugador = (++jugador) % juego.numJugadores;  
                        }else {
                            robarFicha(juego.pozo, ficha);
                            juego.jugadores[jugador].fichas[juego.jugadores[jugador].contador] = ficha;
                            juego.jugadores[jugador].contador++;
                        }
                    }

                    clear();
            }

            if(sinSalida(juego)) {
                cout << fgRojo << ">>> No se puede seguir jugando" << finColor << endl;
                mostrarTablero(juego);
                opcionElegida = 0;
            }
        } while(opcionElegida != 0 && !ganado);
        
        if (interrumpido) {
            cout << fgRojo << ">>> El juego se ha interrrumpido. ¿Quiere guardar la partida? (y/n): " << finColor;
            cin >> guardar;
            
            if (guardar == 'y') escribirJuego(juego, jugador);

            jugar = false;
        }else {
            if (ganado) {
                mostrarTablero(juego); //Mostrar el tablero con el jugador sin fichas
                cout << endl << fgVerde << ">>> Gana el jugador " << jugador << finColor << endl;
            }

            for (int i=0; i<juego.numJugadores; i++) {
                sumaPuntos = sumarPuntos(juego.jugadores[i]);
                sumaPuntos += juego.puntos[i];
                cout << "Los puntos finales del jugador " << i << " son: " << sumaPuntos << endl;
            }

            cout << endl << "¿Desea jugar otra partida? (y/n): ";
            cin >> reiniciar;

            if (reiniciar == 'y') {
                configurarJuego(juego, jugador);
            }else {
                jugar = false;
            }
        }
    } while(jugar);
}


/**
 * Limpia la consola dependiendo del sistema operativo.
 */
 void clear() {
    //CLS para windows y CLEAR para Unix based OS
    if (system("CLS")) system("clear");
 }


/**
* Devuelve menu principal con opciones y recupera la elegida.
*
* @return Devuelve un entero, que hace referencia a la opcion elegida.
*/
int mostrarMenu() {
    short int opcionElegida; // Almacena lo que el usuario elije del menu
    
    cout << fgVerde << " ------------------" << finColor << endl;
    cout << fgVerde << "| MENU DE OPCIONES |" << finColor << endl;
    cout << fgVerde << " ------------------" << finColor << endl;
    cout << fgVerde << "1." << finColor << " Poner ficha por la izquierda" << endl;
    cout << fgVerde << "2." << finColor << " Poner ficha por la derecha" << endl;
    cout << fgVerde << "3." << finColor << " Robar ficha nueva" << endl;
    cout << fgVerde << "0." << finColor << " Salir" << endl;

    do {
        cout << "Elija una opción: ";
        cin >> opcionElegida;
    } while(opcionElegida < 0 || opcionElegida > 3);

    cout << endl;

    return opcionElegida;
}


/**
* Formatea una cadena en forma de ficha con los números recibidos como parámetros.
* En caso de que los números sean mayores que 9 se devuelve una excepción y se finaliza.
*
* @param ficha Struct con los numeros izquierda y derecha de la ficha
*
* @return Ficha formateada o excepción si hay error
*/
string fichaToStr(tFicha ficha){
    // Nos aseguramos de que hemos recibido un numero que está disponible como ficha.
    // Si no es así se devuelve una excepción y acaba el juego por inconcluencia.
    if (ficha.izquierda > 9 || ficha.derecha > 9) {
        throw invalid_argument("Los números de las fichas no pueden ser superiores a 9. Recibido: " \
                + toStr(ficha.izquierda) + "  " + toStr(ficha.derecha));
    }

    string fichaFinal = "|";

    fichaFinal.append(toStr(ficha.izquierda) + "-" + toStr(ficha.derecha) + "|");

    return fichaFinal;
}


/**
* Imprime el tablero de la partida con los valores recibidos
*
* @param juego Struct con todos los datos de la partida
*/
void mostrarTablero(const tJuego &juego) {
    cout << fgVerde << " ------------------" << finColor << endl;
    cout << fgVerde << "|     TABLERO      |" << finColor << endl;
    cout << fgVerde << " ------------------" << finColor << endl;
    cout << juego.tablero << endl << endl;

    for (int x=1; x<=juego.numJugadores-1; x++) {
        cout << "Máquina #" << x << "    ";
        for (int z=0; z<=juego.jugadores[x].contador-1; z++) {
            cout << fichaToStr(juego.jugadores[x].fichas[z]);
        }
        cout << endl << endl;
    }
    cout << "Jugador       ";
    for (int i=0; i<juego.jugadores[0].contador; i++) {
        cout << fichaToStr(juego.jugadores[0].fichas[i]);
    }
    cout << endl << endl;
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
* Comprueba si el número del tablero por la izquierda coincide con 
* alguno de la ficha que recibe
*
* @param tablero
* @param ficha Struct que contiene los números de la ficha a colocar
*
* @return Devuelve true si se puede poner, false si no.
*/
bool puedePonerIzq(string tablero, tFicha ficha) {
    //Usando indices, saca el segundo caracter de la cadena
    bool sePuede = false;
    short int extremoTablero =  int(tablero[1]) - int('0');

    if (ficha.izquierda == extremoTablero || ficha.derecha == extremoTablero) sePuede = true;

    return sePuede;
}


/**
* Comprueba si el número del tablero por la derecha coincide con 
* alguno de la ficha que recibe
*
* @param tablero
* @param ficha Struct que contiene los números de la ficha a colocar
*
* @return Devuelve true si se puede poner, false si no.
*/
bool puedePonerDer(string tablero, tFicha ficha) {
    bool sePuede = false;
    short int extremoTablero = int(tablero[tablero.size() - 2]) - int('0');

    if (ficha.izquierda == extremoTablero || ficha.derecha == extremoTablero) sePuede = true;

    return sePuede;
}


/**
* Recibe el tablero y la ficha a colocar, coloca la ficha a la izquierda
* en el sentido que corresponda y devuelve el nuevo tablero.
*
* @param tablero
* @param ficha Struct que contiene los números de la ficha a colocar
*
* @return Devuelve el tablero actualizado.
*/
void ponerFichaIzq(string &tablero, tFicha ficha) {
    short int extremoTablero =  int(tablero[1]) - int('0');
    short int temp;
    string fichaFinal;

    if (extremoTablero == ficha.izquierda) {
        temp = ficha.derecha;
        ficha.derecha = ficha.izquierda;
        ficha.izquierda = temp;
        fichaFinal = fichaToStr(ficha);
    }else {
        fichaFinal = fichaToStr(ficha);
    }

    tablero = fichaFinal.append(tablero);
}


/**
* Recibe el tablero y la ficha a colocar, coloca la ficha a la derecha
* en el sentido que corresponda y devuelve el nuevo tablero.
*
* @param tablero
* @param ficha Struct que contiene los números de la ficha a colocar
*
* @return Devuelve el tablero actualizado.
*/
void ponerFichaDer(string &tablero, tFicha ficha) {
    short int extremoTablero = int(tablero[tablero.size() - 2]) - int('0');
    short int temp;
    string fichaFinal;

    if (extremoTablero == ficha.derecha) {
        temp = ficha.derecha;
        ficha.derecha = ficha.izquierda;
        ficha.izquierda = temp;
        fichaFinal = fichaToStr(ficha);
    }else {
        fichaFinal = fichaToStr(ficha);
    }

    tablero = tablero.append(fichaFinal);
}


/**
* Popula dos arrays con las fichas generadas. El array pozo1 se llena con 
* los numeros izquierdos de las fiches y el pozo2 los numeros de la derecha.
*
* @param pozo. Struct que contiene el pozo y un contador
* @param maxDig. Número máximo que puede tomar una ficha
*/
void generarPozo(tListaFichas &pozo, int maxDig) {
    short int pozoCont = 0;

    for (int i=0; i <= maxDig; i++) {
        for (int x=i; x <= maxDig; x++) {
            pozo.fichas[pozoCont].izquierda = i;
            pozo.fichas[pozoCont].derecha = x;
            pozoCont++;
        }
    }

    pozo.contador = pozoCont;
}


/**
* Desordena mediante el algoritmo de Fisher-Yates los dos arrays de manera
* no sesgaga.
*
* @param pozo. Struct que contiene el pozo y un contador
*/
void desordenarPozo(tListaFichas &pozo) {
    int idx;
    short int tmp1, tmp2;
        for (int i = pozo.contador - 1; i >= 0; i--) {
            idx = rand() % (i + 1);
            if (i != idx) {
                tmp1 = pozo.fichas[i].izquierda;
                tmp2 = pozo.fichas[i].derecha;
                pozo.fichas[i] = pozo.fichas[idx];
                pozo.fichas[idx].izquierda = tmp1;
                pozo.fichas[idx].derecha = tmp2;
            }
        }
}


/**
* Coge la siguiente ficha del pozo y modifica el contador que indexa el pozo.
*
* @param pozo. Struct que contiene el pozo y un contador
* @param ficha. Ficha en la que se cargarán los número de la ficha robada
*/
bool robarFicha(tListaFichas &pozo, tFicha &ficha) {
    bool roba = false;

    if (pozo.contador != 0) {
        ficha = pozo.fichas[pozo.contador - 1];
        pozo.contador--;
        roba = true;
    }

    return roba;
}


/**
* Desplaza las fichas en los arrays que recibe y decrementa el contador de la fichas del jugador.
*
* @param lista. Struct con las fichas del jugador y un contador
* @param fichas2. Número de la ficha a borrar
*/
void eliminarFicha (tListaFichas &lista, int indice) {
    for (int i = indice; i <= lista.contador - 1 ; i++) {
        lista.fichas[i] = lista.fichas[i+1];
    }
    lista.contador--;
}


/**
* Comprueba si entre todas las fichas del jugador se puede colocar alguna en algún
* extremo del tablero.
*
* @param lista. Struct con las fichas del jugador y un contador
* @param tablero. String que contiene el tablero actual.
*
* @return true si se puede colocar, false en caso contrario
*/
bool puedeColocarFicha(const tListaFichas &jugador, string tablero) {
    bool puedePoner = false;
    short int cont = 0;
    short int extremoIzquierda =  int(tablero[1]) - int('0');
    short int extremoDerecha = int(tablero[tablero.size() - 2]) - int('0');

    while(!puedePoner && cont < jugador.contador) {
        if (puedePonerDer(tablero, jugador.fichas[cont]) \
            || puedePonerIzq(tablero, jugador.fichas[cont])) {
            puedePoner = true;
        }
        cont++;
    }

    return puedePoner;
}


/**
* Recorre todas las fichas del jugador y suma los puntos de ellas.
*
* @param lista. Struct con las fichas del jugador y un contador
*
* @return La suma de todos los números de las fichas del jugador
*/
int sumarPuntos(const tListaFichas &jugador) {
    int sumaPuntos = 0;

    for (int i=0; i<=jugador.contador - 1; i++) {
        sumaPuntos += jugador.fichas[i].izquierda;
        sumaPuntos += jugador.fichas[i].derecha;
    }

    return sumaPuntos;
}


/**
* Funcion operador que compara dos structs de fichas
*
* @param opLeft. Ficha de la izquierda
* @param opRigth. Ficha de la derecha
*
* @return La suma de todos los números de las fichas del jugador
*/
bool operator==(tFicha opLeft, tFicha opRight) {
    bool igual = false;

    if (opLeft.izquierda == opRight.izquierda && opLeft.derecha == opRight.derecha) {
        igual = true;
    }

    return igual;
}


/**
* Busca la ficha recibida en las fichas del jugador
*
* @param fichas. Struct con las fichas del jugador y un contador
* @param ficha. Ficha que se busca
* @param indice. Posicion donde se encuentra la ficha
*
* @return True si encuentra la ficha, false en caso contrario
*/
bool contiene(tListaFichas fichas, tFicha ficha, int &indice) {
    bool encontrado = false;
    short int cont = 0;

    do {
        if (operator==(fichas.fichas[cont], ficha)) {
            encontrado = true;
        }else {
            cont++;
        }
    } while(!encontrado && cont < fichas.contador);

    indice = cont;
    return encontrado;
}


/**
* Busca quien tiene el doble más alto
*
* @param juego. Struct con todos los datos del juego
* @param indice. Posicion donde se encuentra el doble
*
* @return El jugador que tiene el doble mas alto, -1 si nadie
*/
int quienEmpieza(const tJuego &juego, int& indice) {
    short int jugador = -1, p, dd = juego.maxDig;
    tFicha ficha;

    while ((jugador < 0) && (dd >= 0)) {
        ficha.izquierda = dd;
        ficha.derecha = dd;
        p = 0;

        while((p < juego.numJugadores) && (!contiene(juego.jugadores[p], ficha, indice))) {
            p++;
        }

        p == juego.numJugadores ? dd-- : jugador = p;
    }

    return jugador;
}


/**
* Inicia una partida de cero, genera y desordena fichas. Roba y pone la primera ficha
*
* @param juego. Struct con todos los datos del juego
* @param jugador. Jugador que tenía en el turno en el momento de guardar
*/
void iniciar(tJuego &juego, int &jugador) {
    bool partidaIniciada = false;
    int indice;

    do {
        generarPozo(juego.pozo, juego.maxDig);
        desordenarPozo(juego.pozo);
        for (int i=0; i<=juego.numJugadores - 1; i++) {
            juego.jugadores[i].contador = 0;
            for (int x=0; x<=6; x++) {
                robarFicha(juego.pozo, juego.jugadores[i].fichas[x]);
                juego.jugadores[i].contador++;
            }
        }

        jugador = quienEmpieza(juego, indice);

        if (jugador >= 0) {
            juego.tablero = fichaToStr(juego.jugadores[jugador].fichas[indice]);
            eliminarFicha(juego.jugadores[jugador], indice);
            cout << fgVerde << ">>> Empieza el jugador " << jugador << finColor << endl;
            juego.puntos[jugador]++;
            partidaIniciada = true;
        }else {
            cout << "Nadie tiene dobles" << endl;
        }

    } while(!partidaIniciada);

    jugador = (++jugador) % juego.numJugadores;
}


/**
* Configura e inicia la partida. Se puede restaurar de un fichero o configurar de cero
*
* @param juego. Struct con todos los datos del juego
* @param jugador. Jugador que tenía en el turno en el momento de guardar
*
* @return La suma de todos los números de las fichas del jugador
*/
void configurarJuego(tJuego &juego, int &jugador) {
    char cargarPartida;

    clear(); //Limpia la consola

    cout << "¿Desea cargar una partida de un fichero externo existente? (y/n): ";
    cin >> cargarPartida;

    if (cargarPartida == 'y') {
        leerJuego(juego, jugador);
    }else {
        //Elegir número de jugadores máquina
        do {
            cout << "¿Cuántos jugadores quieres tener? (" << MinJugadores << "-" << MaxJugadores << "): ";
            cin >> juego.numJugadores;
        } while(juego.numJugadores < MinJugadores || juego.numJugadores > MaxJugadores);

        //Inicializar puntuacion de los jugadores a 0
        for (int i=0; i<=MaxJugadores - 1; i++) {
            juego.puntos[i] = 0;
        }

        //Número maximo que una ficha podrá tener
        do {
            cout << "Elige el número máximo podrán tener las fichas (6-9): ";
            cin >> juego.maxDig;
        } while(juego.maxDig < 6 || juego.maxDig > 9);

        iniciar(juego, jugador);
    }
}


/**
* Recorre todas las fichas de los jugadores buscando si alguien puede poner
*
* @param juego. Struct con todos los datos del juego
*
* @return True si alguien puede poner, false en caso contrario
*/
bool sinSalida(const tJuego &juego) {
    short int jugador = 0;
    short int ficha;
    bool sinSalida = true;

    while (sinSalida && jugador < juego.numJugadores) {
        if (puedeColocarFicha(juego.jugadores[jugador], juego.tablero)) sinSalida = false;

        jugador++; //Se pasa al siguiente jugador
    }

    if (sinSalida && juego.pozo.contador != 0) sinSalida = false;

    return sinSalida;
}


/**
* Busca la primera ficha del jugador que se pueda poner, primero a izquierda y luego a derechas.
*
* @param juego. Struct con todos los datos del juego
* @param jugador. Jugador que tenía en el turno en el momento de guardar
*
* @return True si pone ficha, false en caso contrario
*/
bool estrategia1(tJuego &juego, int jugador) {
    bool encontrado = false;
    short int fichaNum = 0;

    do {
        if (puedePonerIzq(juego.tablero, juego.jugadores[jugador].fichas[fichaNum])) {
            ponerFichaIzq(juego.tablero, juego.jugadores[jugador].fichas[fichaNum]);
            eliminarFicha(juego.jugadores[jugador], fichaNum);
            encontrado = true;
        }else if (puedePonerDer(juego.tablero, juego.jugadores[jugador].fichas[fichaNum])) {
            ponerFichaDer(juego.tablero, juego.jugadores[jugador].fichas[fichaNum]);
            eliminarFicha(juego.jugadores[jugador], fichaNum);
            encontrado = true;
        }else {
            fichaNum++;
        }
    } while(!encontrado && fichaNum < juego.jugadores[jugador].contador);

    return encontrado;
}


/**
* Busca la ficha del jugador que sume más puntos y la pone en el tablero
*
* @param juego. Struct con todos los datos del juego
* @param jugador. Jugador que tenía en el turno en el momento de guardar
*
* @return True si pone ficha, false en caso contrario
*/
bool estrategia2(tJuego &juego, int jugador) {
    bool encontrado = false;
    short int posMejor = -1, puntosMejor = -1, puntos;

    for (int i=0; i<=juego.jugadores[jugador].contador - 1; i++) {
        if (puedePonerIzq(juego.tablero, juego.jugadores[jugador].fichas[i]) \
            || puedePonerDer(juego.tablero, juego.jugadores[jugador].fichas[i])) {
                puntos = juego.jugadores[jugador].fichas[i].izquierda + juego.jugadores[jugador].fichas[i].derecha;
                
                if (puntos > puntosMejor) {
                    posMejor = i;
                    puntosMejor = puntos;
                }
        }
    }

    if (posMejor >= 0) {
        encontrado = true;

        if (puedePonerIzq(juego.tablero, juego.jugadores[jugador].fichas[posMejor])) {
            ponerFichaIzq(juego.tablero, juego.jugadores[jugador].fichas[posMejor]);
        }else {
            ponerFichaDer(juego.tablero, juego.jugadores[jugador].fichas[posMejor]);
        }

        eliminarFicha(juego.jugadores[jugador], posMejor);
    }

    return encontrado;
}


/**
* Lee todos los datos del juego a un struct.
*
* @param juego. Struct con todos los datos del juego
* @param jugador. Jugador que tenía en el turno en el momento de guardar
*/
bool leerJuego(tJuego &juego, int &jugador) {
    ifstream datosPartida;
    string nombreFichero;
    bool partidaCargada = false;

    do {
        cout << "Introduce el nombre del fichero para restaurar partida: ";
        cin >> nombreFichero;
    } while(!existePartida(nombreFichero));

    datosPartida.open(nombreFichero);

    if (!datosPartida.is_open()) {
        cout << endl << fgRojo << ">>> ERROR: No se pudo abrir el fichero para cargar partida. Revise el nombre." << finColor << endl;
    }else {
        datosPartida >> jugador; //Turno del jugador
        datosPartida >> juego.tablero; //Tablero 
        datosPartida >> juego.maxDig; //Numero maximo de fichas
        datosPartida >> juego.numJugadores; //Numero de jugadores
        //Cargar fichas de los jugadores
        for (int i=0; i<juego.numJugadores; i++) {
            leerListaFichas(datosPartida, juego.jugadores[i]);
        }
        leerListaFichas(datosPartida, juego.pozo); //Fichas del pozo
        //Puntos de cada jugador
        for (int x=0; x<juego.numJugadores; x++) {
            datosPartida >> juego.puntos[x];
        }

        cout << endl << fgVerde << ">>> Partida cargada desde fichero " << nombreFichero << finColor << endl;
        partidaCargada = true;
        datosPartida.close();
    }

    return partidaCargada;
}


/**
* Comprueba si existe el fichero que se le pasa.
*
* @param nombreFichero
*
* @return True si el fichero existe, false en caso contrario
*/
bool existePartida(string nombreFichero) {
    ifstream ficheroPartida;

    ficheroPartida.open(nombreFichero);

    if (!ficheroPartida.good()) {
        cout << fgRojo << ">>> ERROR: El fichero no existe. Compruebe el nombre." << finColor << endl;
    }else {
        ficheroPartida.close();
    }

    return ficheroPartida.good();
}


/**
* Lee todas las fichas guardadas en un fichero junto con su contador al struct
*
* @param entrada. Fichero abierto del que leer.
* @param listaFichas. Struct con las fichas del jugador y un contador
*/
void leerListaFichas(ifstream &entrada, tListaFichas &listaFichas) {
    //Guardar primero el contador para poder sacar las fichas posteriormente
    entrada >> listaFichas.contador;

    for (int i=0; i<listaFichas.contador; i++) {
        entrada >> listaFichas.fichas[i].izquierda;
        entrada >> listaFichas.fichas[i].derecha;
    }
}


/**
* Escribe todos los datos del juego a un fichero.
*
* @param juego. Struct con todos los datos del juego
* @param jugador. Jugador que tenía en el turno en el momento de guardar
*/
void escribirJuego(const tJuego &juego, int &jugador) {
    ofstream datosPartida;
    string nombreFichero;

    cout << "Introduce el nombre del fichero para guardar la partida: ";
    cin >> nombreFichero;

    datosPartida.open(nombreFichero);

    if (!datosPartida.is_open()) {
        cout << endl << fgRojo << ">>> ERROR: No se pudo abrir/crear el fichero para salvar partida." << finColor << endl;
    }else {
        datosPartida << jugador << endl; //Turno del jugador
        datosPartida << juego.tablero << endl; //Tablero 
        datosPartida << juego.maxDig << endl; //Numero maximo de fichas
        datosPartida << juego.numJugadores << endl; //Numero de jugadores
        //Cargar fichas de los jugadores
        for (int i=0; i<juego.numJugadores; i++) {
            escribirListaFichas(datosPartida, juego.jugadores[i]);
        }
        escribirListaFichas(datosPartida, juego.pozo); //Fichas del pozo
        //Puntos de cada jugador
        for (int x=0; x<juego.numJugadores; x++) {
            datosPartida << juego.puntos[x] << endl;
        }

        datosPartida.close();

        cout << endl << fgVerde << ">>> Partida salvada correctamente en fichero " << nombreFichero << finColor << endl;
    }
}


/**
* Escribe todas las fichas guardadas en un fichero junto con su contador al fichero
*
* @param salida. Fichero abierto donde escribir.
* @param listaFichas. Struct con las fichas del jugador y un contador
*/
void escribirListaFichas(ofstream &salida, const tListaFichas &listaFichas) {
    //Guardar primero el contador para poder sacar las fichas posteriormente
    salida << listaFichas.contador << endl;

    for (int i=0; i<listaFichas.contador; i++) {
        salida << listaFichas.fichas[i].izquierda << " ";
        salida << listaFichas.fichas[i].derecha << " ";
    }
    salida << endl;
}

