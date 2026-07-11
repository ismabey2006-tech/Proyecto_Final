#pragma once
#include "Jugador.h"

class Defensor : public Jugador {
public:
    Defensor(const std::string& nombre, const std::string& pais);

    std::string posicion() const override;
    void actuar() override;
};
