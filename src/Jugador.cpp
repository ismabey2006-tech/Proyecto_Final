#include "Jugador.h"
#include <iostream>

using namespace std;

Jugador::Jugador(const string& nombre, const string& pais)
    : nombre(nombre), pais(pais) {}

void Jugador::imprimir() const {
    cout << "[" << pais << "] " << nombre << " - " << posicion() << endl;
}

void Jugador::gol() {
    cout << nombre << " anota el gol!" << endl;
}
