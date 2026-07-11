#pragma once
#include "Jugador.h"

class Mediocampista : public Jugador {
public:
    Mediocampista(const std::string& nombre, const std::string& pais);

    std::string posicion() const override;
    void actuar() override;
};
