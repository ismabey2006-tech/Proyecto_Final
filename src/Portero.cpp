#include "Portero.h"
#include <iostream>

using namespace std;

Portero::Portero(const string& nombre, const string& pais) : Jugador(nombre, pais) {}

string Portero::posicion() const {
    return "Portero";
}

void Portero::actuar() {
    cout << nombre << " ataja el disparo!" << endl;
}
