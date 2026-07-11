#include "Defensor.h"
#include <iostream>

using namespace std;

Defensor::Defensor(const string& nombre, const string& pais) : Jugador(nombre, pais) {}

string Defensor::posicion() const {
    return "Defensor";
}

void Defensor::actuar() {
    cout << nombre << " despeja el balon!" << endl;
}
