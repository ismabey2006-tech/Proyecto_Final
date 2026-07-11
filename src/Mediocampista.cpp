#include "Mediocampista.h"
#include <iostream>

using namespace std;

Mediocampista::Mediocampista(const string& nombre, const string& pais) : Jugador(nombre, pais) {}

string Mediocampista::posicion() const {
    return "Mediocampista";
}

void Mediocampista::actuar() {
    cout << nombre << " da el pase clave!" << endl;
}
