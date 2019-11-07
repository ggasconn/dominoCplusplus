/*
* Version: 2.0
*
* Domino realizado por Alejandro y Guillermo
* Ambas partes extras realizadas
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

//Colores para editar la terminal
//Implementar estructura que contenga todos los colores
string fgRojo = "\033[1;31m";
string fgVerde = "\033[1;32m";
string fgAzul = "\033[1;34m";
string finColor = "\033[0m";

struct datosPartida{
    string tablero;
    int numColocadas;
    int numRobadas;
};

const short int numFichas = 28;     //Numero de ficha disponibles
typedef short int tArray[numFichas];

//Prototipos de funciones a usar durante el programa
void clear();
int mostrarMenu();
string fichaToStr(short int izquierda, short int derecha);
void mostrarTablero(short int fichaN1, short int fichaN2, string tablero, int numColocadas, int numRobadas);
//void mostrarTablero(string tablero, short int numColocadas, short int numRobadas, \
//    const tArray fichas1, const tArray fichas2, short int fichasCont);short int aleat(short int numeroMaximo);
short int aleat(short int numero);
string toStr(int n); // Se puede usar la implementada en C++11??
bool puedePonerIzq(string tablero, short int fichaN1, short int fichaN2);
bool puedePonerDer(string tablero, short int fichaN1, short int fichaN2);
string ponerFichaIzq(string tablero, short int fichaN1, short int fichaN2);
string ponerFichaDer(string tablero, short int fichaN1, short int fichaN2);
bool salvarPartida(string tablero, short int numColocadas, short int numRobadas);
bool existePartida();
char confirmarBorrado();
datosPartida recuperarPartida();
void generarPozo(tArray pozo1, tArray pozo2, int varianteJuego);
void desordenarPozo(tArray pozo1, tArray pozo2);
void robarFicha(const tArray pozo1, const tArray pozo2, short int &cont, short int &fichaN1, short int &fichaN2);
void eliminarFicha (tArray fichas1, tArray fichas2, short int &fichasCont, short int fichaNum);
bool puedeColocarFicha(const tArray fichas1, const tArray fichas2, short int fichasCont, string tablero);
short int sumarPuntos(const tArray fichas1, const tArray fichas2, short int fichasCont);


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
    short int fichaN1 = aleat(varianteJuego);
    short int fichaN2 = aleat(varianteJuego);
    bool haRobado;
    bool haColocado;
    bool salir = false;
    string tablero = fichaToStr(aleat(varianteJuego), aleat(varianteJuego));

    //Variables v2
    //TODO: reordenar y elimnar no necesarias al acabar
    tArray pozo1;
    tArray pozo2;
    tArray fichas1;
    tArray fichas2;
    short int pozoCont;
    short int fichasCont;

    //Llena el pozo y lo desordena
    generarPozo(pozo1, pozo2, varianteJuego);
    desordenarPozo(pozo1, pozo2);

    clear(); //Limpia la consola

    if(existePartida()) {
        char restaurar;

        cout << fgAzul << "Se ha encontrado una partida guardada. ¿Quiere restaurarla? (y/n): " << finColor;
        cin >> restaurar;

        if (restaurar == 'y') {
            struct datosPartida valores = recuperarPartida();
            tablero = valores.tablero;
            numColocadas = valores.numColocadas;
            numRobadas = valores.numRobadas;

            cout << fgVerde << ">>> Partida restaurada" << finColor << endl << endl;
        }
    }
   
    do {
        bool haRobado = false;
        bool haColocado = false;

        //Muestra el tablero y el menu
        mostrarTablero(fichaN1, fichaN2, tablero, numColocadas, numRobadas);
        opcionElegida = mostrarMenu();

        clear(); //Limpia la consola

        switch (opcionElegida)
        {
        case 1:
            if (puedePonerIzq(tablero, fichaN1, fichaN2)) {
                tablero = ponerFichaIzq(tablero, fichaN1, fichaN2);
                numColocadas++;
                haColocado = true;
            }else {
                haRobado = true;
                cout << fgRojo << ">>> No se puede colocar una ficha a la izquierda" << finColor << endl << endl;
            }
            break;
        
        case 2:
            if (puedePonerDer(tablero, fichaN1, fichaN2)) {
                tablero = ponerFichaDer(tablero, fichaN1, fichaN2);
                numColocadas++;
                haColocado = true;
            }else {
                haRobado = true;
                cout << fgRojo << ">>> No se puede colocar una ficha a la derecha" << finColor << endl << endl;
            }
            break;
        
        case 3:
            fichaN1 = aleat(varianteJuego);
            fichaN2 = aleat(varianteJuego);
            numRobadas++;
            haRobado = true;
            break;
        
        case 4:
            cout << fgVerde << ">>> Salvando partida a fichero game_history.txt" << finColor << endl;
            
            if (salvarPartida(tablero, numColocadas, numRobadas)) {
                cout << fgVerde << ">>> OK" << finColor << endl << endl;
            }else {
                cout << endl << fgRojo << ">>> Error: no se pudo guardar la partida o se denegó la acción" << finColor << endl << endl;
            }

            break;
        
        case 5:
            do {
                cout << "Seleccione el número máximo que puede tomar una ficha (6-9):";
                cin >> varianteJuego;
            } while(varianteJuego < 6 || varianteJuego > 9);
            
            break;

        default:
            if (1 > opcionElegida > 5) cout << fgRojo << opcionElegida << " no es una opción válida" << finColor << endl;
            break;
        }

        if (!haRobado)
        {
            fichaN1 = aleat(varianteJuego);
            fichaN2 = aleat(varianteJuego);
        }
        

        //Mostrar tablero
        mostrarTablero(fichaN1, fichaN2, tablero, numColocadas, numRobadas);

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
    cout << "5. Cambiar máximo de puntos de las piezas" << endl;
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
* @return Devuelve un entero dentro del rango 0-numero
*/
short int aleat(short int numero){
    int numAleat;
    
    numAleat = rand() % numero;

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
* Los datos se almacenan linea a linea para sacarlos a un struct.
*
* @param tablero. Contiene el estado actual de la partida.
*
* @return Devuelve true si la partida se guardo, false si no.
*/
bool salvarPartida(string tablero , short int numColocadas, short int numRobadas){
    bool partidaSalvada = false;

    if (confirmarBorrado() == 'y') {
        ofstream ficheroPartida;
        ficheroPartida.open("game_history.txt");

        //Se graban los datos linea a linea para posteriormente volcarlos a un struct
        ficheroPartida << tablero << endl;
        ficheroPartida << numColocadas << endl;
        ficheroPartida << numRobadas << endl;

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
        struct datosPartida valores = recuperarPartida();

        cout << fgRojo << "@@@@@@@@@@@@" << finColor << endl;
        cout << fgRojo << "@ ATENCION @" << finColor << endl;
        cout << fgRojo << "@@@@@@@@@@@@" << finColor << endl;
        cout << "Se ha encontrado una partida guardada con el siguiente estado: " << endl;
        cout << fgAzul << "Tablero: " << valores.tablero << "   Colocadas: " << valores.numColocadas \
        << "  Robadas: " << valores.numRobadas << finColor << endl;
        cout << "Seguro que desea sobrescribirla? (y/n): ";
        cin >> borrarPartida;
    }

    return borrarPartida;
}


/**
* Recupera la partida guardada en un fichero.
*
* @return Struct conteniendo todos los datos necesarios.
*/
datosPartida recuperarPartida(){
    struct datosPartida valores;
    
    ifstream ficheroPartida;
    ficheroPartida.open("game_history.txt");
    
    if (! ficheroPartida.is_open()) {
        throw runtime_error("No se pudo abrir el fichero con el historial. Compruebe si existe o si ha sido borrado.");
    }else {
        //Recupera linea a linea los datos y los mete en la posición adecuada
        ficheroPartida >> valores.tablero;
        ficheroPartida >> valores.numColocadas;
        ficheroPartida >> valores.numRobadas;
    }

    ficheroPartida.close();

    return valores;
}


/**
* Popula dos arrays con las fichas generadas. El array pozo1 se llena con 
* los numeros izquierdos de las fiches y el pozo2 los numeros de la derecha.
*
* @param pozo1. Array que contiene los numeros izquierdos de las fichas
* @param pozo2. Array que contiene los numeros derechos de las fichas
*/
void generarPozo(tArray pozo1, tArray pozo2, int varianteJuego) {
    short int cont = 0; //Sirve de indice para almacenar el los arrays

    for (int i=0; i <= varianteJuego; i++) {
        for (int x=i; x <= varianteJuego; x++) {
            pozo1[cont] = i;
            pozo2[cont] = x;
            cont++;
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
void desordenarPozo(tArray pozo1, tArray pozo2) {
    int idx, i;
    short int tmp1, tmp2;
        for (int i = numFichas - 1; i >= 0; i--) {
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

}


/**
* Breve explicación
*
* @param
*
* @return
*/
void eliminarFicha (tArray fichas1, tArray fichas2, short int &fichasCont, short int fichaNum) {

}


/**
* Breve explicación
*
* @param
*
* @return
*/
bool puedeColocarFicha(const tArray fichas1, const tArray fichas2, short int fichasCont, string tablero) {

}


/**
* Breve explicación
*
* @param
*
* @return
*/
short int sumarPuntos(const tArray fichas1, const tArray fichas2, short int fichasCont) {
    
}

