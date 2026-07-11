#include "JugadorFactory.h"
#include "Portero.h"
#include "Defensor.h"
#include "Mediocampista.h"
#include "Delantero.h"

using namespace std;

unique_ptr<Jugador> crearJugador(const string& posicion, const string& nombre, const string& pais) {
    if (posicion == "Portero")       return make_unique<Portero>(nombre, pais);
    if (posicion == "Defensor")      return make_unique<Defensor>(nombre, pais);
    if (posicion == "Mediocampista") return make_unique<Mediocampista>(nombre, pais);
    if (posicion == "Delantero")     return make_unique<Delantero>(nombre, pais);
    return nullptr; // posicion no reconocida
}
