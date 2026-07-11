#include "Alineacion.h"
#include <iostream>
#include <limits>

using namespace std;

// Al hacer doble clic en el .exe desde el Explorador de Windows, la consola
// se cierra sola apenas el programa termina y no da tiempo a leer la salida.
// Esta pausa evita esa confusion (correr desde una terminal no molesta,
// solo pide presionar Enter).
void pausarAntesDeSalir() {
    cout << "\nPresiona Enter para salir..." << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main() {
    Equipo equipo = cargarAlineacion("data/alineacion.txt");

    if (equipo.empty()) {
        cerr << "No se cargaron jugadores. Revisa el archivo data/alineacion.txt" << endl;
        pausarAntesDeSalir();
        return 1;
    }

    imprimirPorCategoria(equipo);
    imprimirCronologia(equipo);

    // Ya no hace falta liberar memoria manualmente: cada Jugador vive dentro
    // de un unique_ptr en "equipo", asi que se destruye solo (RAII) cuando
    // "equipo" sale de alcance al terminar main().
    pausarAntesDeSalir();
    return 0;
}
