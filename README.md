# Alineacion de Futbol (C++)

Programa de consola en C++ que carga una alineacion de futbol desde un archivo
de texto y la muestra organizada por categoria (Portero, Defensor,
Mediocampista, Delantero) y como una "cronologia" de participacion con
minutos aleatorios en orden aleatorio de jugadores.

El proyecto esta pensado como ejercicio de POO en C++: usa una clase base
abstracta (`Jugador`) con subclases por posicion, un Factory Method para
crear jugadores segun el texto leido del archivo, y `unique_ptr` para manejo
automatico de memoria (RAII), sin necesidad de `delete` manual.

## Estructura del proyecto

```
include/          Headers (.h) de cada clase
src/              Implementacion (.cpp) de cada clase y punto de entrada (main.cpp)
data/             Datos de entrada (alineacion.txt)
bin/              Ejecutable generado y copia de data/ (se crea al compilar)
build.bat         Script de compilacion para Windows
```

### Clases principales

- `Jugador` — clase base abstracta, define el contrato (`posicion()`, `actuar()`) que cumplen todas las posiciones.
- `Portero`, `Defensor`, `Mediocampista`, `Delantero` — subclases concretas de `Jugador`.
- `JugadorFactory` — crea el jugador correcto (`crearJugador`) segun el texto de posicion leido del archivo.
- `Alineacion` — carga el equipo desde `data/alineacion.txt` (`cargarAlineacion`) e imprime la alineacion por categoria y en orden cronologico.

## Formato del archivo de datos

`data/alineacion.txt` tiene una linea por jugador con el formato:

```
Posicion,Nombre,Pais
```

Ejemplo:

```
Portero,Buffon,Italia
Defensor,Ramos,Espana
Mediocampista,Iniesta,Espana
Delantero,CR7,Portugal
```

Lineas vacias, con espacios de mas o con campos faltantes se reportan por
consola (stderr) y se ignoran, sin detener la carga del resto del archivo.

## Requisitos

- Un compilador de C++ compatible con C++14. En Windows, el mas comun es
  [MinGW-w64](https://www.mingw-w64.org/) (provee `g++`).
- El script `build.bat` esta hecho para Windows.

## Como compilarlo y ejecutarlo

Desde la raiz del proyecto:

```bat
build.bat
```

Esto compila todos los `.cpp` de `src/` (usando los headers de `include/`) y
genera `bin\programa.exe`. Tambien copia `data/` dentro de `bin/` para que el
ejecutable funcione tanto si se corre desde la raiz del proyecto como si se
hace doble clic directamente sobre el `.exe` dentro de `bin\`.

Para ejecutarlo:

```bat
bin\programa.exe
```

O bien, hacer doble clic en `bin\programa.exe` desde el Explorador de
Windows (el programa espera que presiones Enter antes de cerrar la consola,
para que puedas leer la salida).

## Salida esperada

El programa imprime:

1. La alineacion agrupada por categoria/posicion.
2. Una cronologia de la participacion de los jugadores, con minutos
   aleatorios estrictamente crecientes, en orden aleatorio.
