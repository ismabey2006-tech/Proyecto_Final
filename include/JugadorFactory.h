#pragma once
#include <memory>
#include <string>
#include "Jugador.h"

// Factory Method: en vez de que el codigo que lee el archivo sepa construir
// cada subclase, delega esa decision aqui. Devuelve un unique_ptr<Jugador>:
// el llamador queda como dueno unico del objeto y la memoria se libera sola
// automaticamente cuando el puntero sale de alcance (RAII), sin necesitar
// "delete" manual.
//
// Devuelve nullptr si "posicion" no es reconocida.
std::unique_ptr<Jugador> crearJugador(const std::string& posicion,
                                       const std::string& nombre,
                                       const std::string& pais);
