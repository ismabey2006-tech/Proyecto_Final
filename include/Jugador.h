#pragma once
#include <string>

// Clase base abstracta: define el "contrato" que todo jugador debe cumplir.
// Es abstracta porque tiene al menos un metodo puro (= 0), por lo que
// no se puede instanciar directamente (no se puede hacer "new Jugador(...)").
class Jugador {
protected:
    // protected en vez de private para que las clases hijas puedan
    // acceder directamente a nombre y pais sin necesitar getters.
    std::string nombre;
    std::string pais;

public:
    Jugador(const std::string& nombre, const std::string& pais);

    // Metodos puramente virtuales (= 0): cada subclase esta OBLIGADA
    // a implementarlos. Esto es lo que hace a Jugador una clase abstracta.
    virtual std::string posicion() const = 0;
    virtual void actuar() = 0;

    // Con implementacion por defecto, pero sigue siendo virtual por si
    // alguna subclase quisiera imprimir distinto.
    virtual void imprimir() const;

    // Con implementacion por defecto: representa el gol de un jugador.
    // No es puro (a diferencia de posicion()/actuar()) porque no todas las
    // subclases necesitan personalizarlo; se hereda tal cual salvo que una
    // subclase decida sobreescribirlo.
    virtual void gol();

    // Destructor virtual: OBLIGATORIO cuando se hace "delete" (o se destruye
    // un unique_ptr) sobre un puntero a la clase base que en realidad apunta
    // a un objeto de una clase hija. Sin "virtual" aqui, solo se llamaria al
    // destructor de Jugador y el comportamiento seria indefinido.
    virtual ~Jugador() = default;
};
