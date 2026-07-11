#include "Delantero.h"
#include <iostream>

using namespace std;

Delantero::Delantero(const string& nombre, const string& pais) : Jugador(nombre, pais) {}

string Delantero::posicion() const {
    return "Delantero";
}

void Delantero::actuar() {
    cout << nombre << " remata al arco!" << endl;
}
