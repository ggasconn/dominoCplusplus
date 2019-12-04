/*
* Version: 3.0
*
* Domino realizado por Alejandro Perea y Guillermo Gascón
*
* Happy Coding! :)
**/

/* DUDAS
  *maxDig no puede ir dentro del struct juego?
  *Que hace exactamente la funcion quienEmpieza?
*/

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

const short int numFichas = 55;     //Numero de ficha disponibles
const short int MinJugadores = 2, MaxJugadores = 4;
short int maxDig = 6; //Numero máximo de ficha

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
short int sumarPuntos(const tListaFichas &jugador);
int quienEmpieza(const tJuego &juego, int& indice);
void iniciar(tJuego &juego, int &jugador);
bool sinSalida(const tJuego &juego);
bool estrategia1(tJuego &juego, int jugador);
bool estrategia2(tJuego &juego, int jugador);
bool operator==(tFicha opLeft, tFicha opRight);
bool contiene(tListaFichas fichas, tFicha ficha, int &indice);


/**
* Funcion principal, contiene un menu interminable.
*/
int main() { 
    srand(time(NULL)); //Genera semilla para saltear el numero aleatorio
    setlocale (LC_ALL,""); //Permite usar carácteres ISO

    short int opcionElegida;
    bool salir = false, restaurar = false;

    //Nuevas variables
    int jugador;
    tJuego juego;
    tFicha ficha;

    do {
        cout << "¿Cuántos jugadores quieres tener? (" << MinJugadores << "-" << MaxJugadores << "): ";
        cin >> juego.numJugadores;
    } while(juego.numJugadores < MinJugadores || juego.numJugadores > MaxJugadores);

    for (int i=0; i<=MaxJugadores - 1; i++) {
        juego.puntos[i] = 0;
    }

    iniciar(juego, jugador);
   
    do {
        //Muestra el tablero y el menu
        mostrarTablero(juego);
        opcionElegida = mostrarMenu();

        switch (opcionElegida) {
            case 0:
                salir = true;
                break;
                
            case 1:
                /*do {
                    cout << "¿Qué ficha quieres colocar? (1-" << fichasCont << "): ";
                    cin >> fichaNum;
                }while(fichaNum < 1 || fichaNum > fichasCont);

                fichaN1 = fichas1[fichaNum - 1];
                fichaN2 = fichas2[fichaNum - 1];

                clear();

                if (puedePonerIzq(tablero, fichaN1, fichaN2)) {
                    tablero = ponerFichaIzq(tablero, fichaN1, fichaN2);
                    numColocadas++;
                    eliminarFicha(fichas1, fichas2, fichasCont, fichaNum);
                }else {
                    cout << fgRojo << ">>> No se puede colocar una ficha a la izquierda" << finColor << endl << endl;
                }*/
                break;
            
            case 2:
                /*do {
                    cout << "¿Qué ficha quieres colocar? (1-" << fichasCont << "): ";
                    cin >> fichaNum;
                }while(fichaNum < 1 || fichaNum > fichasCont);

                fichaN1 = fichas1[fichaNum - 1];
                fichaN2 = fichas2[fichaNum - 1];

                clear();

                if (puedePonerDer(tablero, fichaN1, fichaN2)) {
                    tablero = ponerFichaDer(tablero, fichaN1, fichaN2);
                    numColocadas++;
                    eliminarFicha(fichas1, fichas2, fichasCont, fichaNum);
                }else {
                    cout << fgRojo << ">>> No se puede colocar una ficha a la derecha" << finColor << endl << endl;
                }*/
                break;
            
            case 3:
                /*clear();

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
                }*/
                break;
            
            case 4:
                clear();
                cout << fgVerde << ">>> Salvando partida a fichero game_history.txt..." << finColor << endl;
                
                /*if (salvarPartida(tablero, numColocadas, numRobadas, fichasCont, pozoCont, pozo1, pozo2, fichas1, fichas2)) {
                    cout << fgVerde << ">>> OK" << finColor << endl << endl;
                }else {
                    cout << endl << fgRojo << ">>> Error: no se pudo guardar la partida o se denegó la acción" << finColor << endl << endl;
                }*/
                break;

            default:
                clear();
                if (1 > opcionElegida || opcionElegida > 5) cout << fgRojo << ">>> " << opcionElegida << " no es una opción válida" << finColor << endl;
                break;
        }
    } while(!salir);
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
    
    do {
        cout << fgVerde << " ------------------" << finColor << endl;
        cout << fgVerde << "| MENU DE OPCIONES |" << finColor << endl;
        cout << fgVerde << " ------------------" << finColor << endl;
        cout << fgVerde << "1." << finColor << " Poner ficha por la izquierda" << endl;
        cout << fgVerde << "2." << finColor << " Poner ficha por la derecha" << endl;
        cout << fgVerde << "3." << finColor << " Robar ficha nueva" << endl;
        cout << fgVerde << "4." << finColor << " Salvar partida a fichero" << endl;
        cout << fgVerde << "0." << finColor << " Salir" << endl;
        cout << "Elija una opción: ";

        cin >> opcionElegida;

        cout << endl;
    } while(opcionElegida < 0 || opcionElegida > 4);

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
    if (ficha.izquierda > 9 || ficha.derecha > 9) throw invalid_argument("Los números de las fichas no pueden ser superiores a 9");

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
    //clear();

    cout << fgVerde << " ------------------" << finColor << endl;
    cout << fgVerde << "|     TABLERO      |" << finColor << endl;
    cout << fgVerde << " ------------------" << finColor << endl;
    cout << juego.tablero << endl;
    
    for(int i=juego.numJugadores; i>0; i--) {
        if (i!=1) {
            cout << "Máquina #" << i - 1 << "    ";
        }else {
            cout << "Jugador    ";
        }

        for (int x=0; x<=juego.jugadores[i].contador-1; x++) {
            cout << fichaToStr(juego.jugadores[i].fichas[x]);
        }
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
        fichaFinal = fichaToStr(ficha);
    }else {
        temp = ficha.derecha;
        ficha.derecha = ficha.izquierda;
        ficha.izquierda = temp;
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
                pozo.fichas[i].izquierda = pozo.fichas[idx].izquierda;
                pozo.fichas[i].derecha = pozo.fichas[idx].derecha;
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

    if (pozo.contador == 0) {
        roba = false;
    }else {
        ficha.izquierda = pozo.fichas[pozo.contador - 1].izquierda;
        ficha.derecha = pozo.fichas[pozo.contador - 1].derecha;
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
    for (int i = indice - 1; i <= lista.contador - 2 ; i++) {
        lista.fichas[i].izquierda = lista.fichas[i+1].izquierda;
        lista.fichas[i].derecha = lista.fichas[i+1].derecha;
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
        if (jugador.fichas[cont].izquierda == extremoIzquierda \
            || jugador.fichas[cont].izquierda == extremoDerecha \
            || jugador.fichas[cont].derecha == extremoIzquierda \
            || jugador.fichas[cont].derecha == extremoDerecha) {
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
int sumaPuntos(const tListaFichas &jugador) {
    short int sumaPuntos = 0;

    for (int i=0; i<=jugador.contador - 1; i++) {
        sumaPuntos += jugador.fichas[i].izquierda;
        sumaPuntos += jugador.fichas[i].derecha;
    }

    return sumaPuntos;
}

bool operator==(tFicha opLeft, tFicha opRight) {
    bool igual = false;

    if (opLeft.izquierda == opRight.izquierda && opLeft.derecha == opRight.derecha) {
        igual = true;
    }

    return igual;
}

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

/*int quienEmpieza(const tJuego &juego, int& indice) {
    short int jugador = -1, p, dd = 6;

    while ((jugador < 0) && (dd >= 0)) {
        p = 0;
        while((p < juego.numJugadores) && (contiene())) {
            p++;
        }
    }
}*/

void iniciar(tJuego &juego, int &jugador) {
    bool partidaIniciada = false;
    int indice;

    do {
        generarPozo(juego.pozo, maxDig);
        desordenarPozo(juego.pozo);
        for (int i=0; i<=juego.numJugadores - 1; i++) {
            for (int x=0; x<=6; x++) {
                robarFicha(juego.pozo, juego.jugadores[i].fichas[x]);
            }
        }
        jugador = quienEmpieza(juego, indice);
        if (jugador >= 0) {
            juego.tablero = fichaToStr(juego.jugadores[jugador].fichas[indice]);
            eliminarFicha(juego.jugadores[jugador], indice);
            cout << "Empieza el jugador " << jugador << endl;
            partidaIniciada = true;
        }else {
            cout << "Nadie tiene dobles" << endl;
        }

    } while(!partidaIniciada);

    jugador = (++jugador) % juego.numJugadores;
}
