#include "Alineacion.h"
#include "JugadorFactory.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

namespace {

// Quita espacios, tabs y '\r' (retorno de carro) al inicio y al final.
// El '\r' aparece cuando un archivo con saltos de linea estilo Windows
// (CRLF) se procesa en un entorno que solo separa por '\n'; sin este
// trim, el ultimo campo de cada linea ("pais") terminaria con un
// caracter invisible pegado al final.
string trim(const string& s) {
    size_t inicio = s.find_first_not_of(" \t\r\n");
    if (inicio == string::npos) return "";
    size_t fin = s.find_last_not_of(" \t\r\n");
    return s.substr(inicio, fin - inicio + 1);
}

const int MINUTO_MAXIMO = 90;

} // namespace

Equipo cargarAlineacion(const string& archivo) {
    Equipo equipo;
    ifstream file(archivo);

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << archivo << endl;
        return equipo;
    }

    string linea;
    int numLinea = 0;
    while (getline(file, linea)) {
        numLinea++;
        linea = trim(linea);
        if (linea.empty()) continue;

        stringstream ss(linea);
        string posicion, nombre, pais, sobrante;
        getline(ss, posicion, ',');
        getline(ss, nombre, ',');
        getline(ss, pais, ',');
        posicion = trim(posicion);
        nombre = trim(nombre);
        pais = trim(pais);

        // Linea mal formada: falta algun campo obligatorio.
        if (posicion.empty() || nombre.empty() || pais.empty()) {
            cerr << "Linea " << numLinea << " ignorada (formato invalido, se esperaba "
                 << "'Posicion,Nombre,Pais'): '" << linea << "'" << endl;
            continue;
        }

        // Campos de mas (una cuarta columna inesperada) tambien se avisan
        // en vez de truncarse en silencio.
        if (getline(ss, sobrante, ',') && !trim(sobrante).empty()) {
            cerr << "Linea " << numLinea << " tiene campos extra que seran ignorados: '"
                 << linea << "'" << endl;
        }

        unique_ptr<Jugador> j = crearJugador(posicion, nombre, pais);
        if (j) {
            equipo.push_back(move(j));
        } else {
            cerr << "Linea " << numLinea << " ignorada (posicion desconocida: '"
                 << posicion << "')" << endl;
        }
    }

    return equipo;
}

void imprimirPorCategoria(const Equipo& equipo) {
    string categorias[] = {"Portero", "Defensor", "Mediocampista", "Delantero"};

    cout << "\n===== ALINEACION POR CATEGORIA =====" << endl;
    for (const string& cat : categorias) {
        cout << "\n-- " << cat << " --" << endl;
        bool hayJugadores = false;
        for (const auto& j : equipo) {
            // j->posicion() y j->imprimir() son llamadas virtuales: aunque "j"
            // es del tipo estatico Jugador*, en tiempo de ejecucion se ejecuta
            // la version de la subclase real (Portero, Delantero, etc.).
            if (j->posicion() == cat) {
                j->imprimir();
                hayJugadores = true;
            }
        }
        if (!hayJugadores) {
            cout << "(sin jugadores en esta categoria)" << endl;
        }
    }
}

// Genera la cronologia con minutos aleatorios estrictamente crecientes.
// Primer minuto: aleatorio entre 1 y 90.
// Cada minuto siguiente: aleatorio entre (el minuto anterior + 1) y 90.
//
// Para garantizar que TODOS los jugadores reciban un minuto (incluso con 11
// jugadores en un rango de 90), en cada sorteo se reserva espacio para los
// jugadores que todavia faltan: si quedan k jugadores por asignar (contando
// el actual), el limite superior del sorteo se reduce a 90 - (k - 1), de modo
// que siempre alcance al menos un minuto disponible para cada uno de los que
// faltan despues de este.
void imprimirCronologia(const Equipo& equipo) {
    if (equipo.empty()) return;

    if (static_cast<int>(equipo.size()) > MINUTO_MAXIMO) {
        cerr << "No se puede generar la cronologia: hay mas jugadores ("
             << equipo.size() << ") que minutos disponibles (" << MINUTO_MAXIMO << ")." << endl;
        return;
    }

    srand(static_cast<unsigned int>(time(0)));

    // "equipo" es dueno de los jugadores via unique_ptr, y esta funcion no
    // debe ni puede tomar esa propiedad. Por eso mezclamos una copia de
    // punteros "observadores" (Jugador*, sin ownership) en vez de mover o
    // copiar los unique_ptr: el orden de la cronologia no afecta al vector
    // original que vive en main().
    vector<Jugador*> orden;
    orden.reserve(equipo.size());
    for (const auto& j : equipo) orden.push_back(j.get());

    // Fisher-Yates: recorre de atras hacia adelante e intercambia cada
    // elemento con uno aleatorio dentro del rango ya no procesado.
    for (size_t i = orden.size() - 1; i > 0; i--) {
        size_t k = rand() % (i + 1);
        swap(orden[i], orden[k]);
    }

    cout << "\n===== CRONOLOGIA DEL PARTIDO =====" << endl;

    int minutoAnterior = 0;
    int n = static_cast<int>(orden.size());

    // Si dos Mediocampistas narran de forma consecutiva, se interpreta como
    // una jugada encadenada entre ellos y el segundo termina anotando gol().
    // "cadenaResuelta" evita que un gol dispare otro de inmediato: tras un
    // gol, el siguiente jugador vuelve a actuar() normal aunque tambien sea
    // Mediocampista, y desde ahi se puede volver a formar una cadena nueva.
    bool anteriorEsMediocampista = false;
    bool cadenaResuelta = false;

    for (int i = 0; i < n; i++) {
        int limiteInferior = minutoAnterior + 1;              // no repetir minutos
        int jugadoresRestantesDespues = n - 1 - i;             // cuantos faltan despues de este
        int limiteSuperior = MINUTO_MAXIMO - jugadoresRestantesDespues; // reservar su espacio

        int minuto = rand() % (limiteSuperior - limiteInferior + 1) + limiteInferior;
        minutoAnterior = minuto;

        cout << "Minuto " << minuto << ": ";

        bool esMediocampista = orden[i]->posicion() == "Mediocampista";
        if (esMediocampista && anteriorEsMediocampista && !cadenaResuelta) {
            // Llamada virtual: el gol se narra segun la subclase real de
            // orden[i], igual que actuar().
            orden[i]->gol();
            cadenaResuelta = true;
        } else {
            // Llamada virtual de nuevo: cada jugador "actua" segun su propia
            // posicion (remata, ataja, despeja, pasa) sin que este codigo
            // necesite saber de que subclase es "orden[i]".
            orden[i]->actuar();
            cadenaResuelta = false;
        }

        anteriorEsMediocampista = esMediocampista;
    }
}
