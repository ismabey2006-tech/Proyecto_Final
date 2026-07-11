#pragma once
#include "Jugador.h"

class Delantero : public Jugador {
public:
    Delantero(const std::string& nombre, const std::string& pais);

    std::string posicion() const override;
    void actuar() override;
};
