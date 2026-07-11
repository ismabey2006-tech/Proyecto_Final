#pragma once
#include "Jugador.h"

class Portero : public Jugador {
public:
    Portero(const std::string& nombre, const std::string& pais);

    std::string posicion() const override;
    void actuar() override;
};
