#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Jugador.h"

using Equipo = std::vector<std::unique_ptr<Jugador>>;

// Carga la alineacion desde un archivo .txt.
// Formato esperado por linea: Posicion,Nombre,Pais
// Ejemplo:      Portero,Buffon,Italia
// Lineas vacias, con espacios de mas o con campos faltantes se reportan
// por cerr y se ignoran (no detienen la carga del resto del archivo).
Equipo cargarAlineacion(const std::string& archivo);

// Imprime los jugadores agrupados por categoria/posicion.
void imprimirPorCategoria(const Equipo& equipo);

// Genera la cronologia con minutos aleatorios estrictamente crecientes,
// en orden aleatorio de jugadores. No modifica "equipo".
void imprimirCronologia(const Equipo& equipo);
