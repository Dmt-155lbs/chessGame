# ♟️ Proyecto Final: Juego de Ajedrez en C++

Este proyecto es una implementación básica de un juego de ajedrez en C++, centrado en el desarrollo del método `Mover` y las validaciones específicas de movimiento para cada tipo de pieza.

## 👥 Integrantes
- Daniel Martínez  
- Wilmer Cárdenas  

📅 Fecha: 19/12/2023  

---

## 🎯 Objetivo

Desarrollar las funcionalidades principales de un juego de ajedrez virtual, haciendo énfasis en la implementación de:

- Movimiento de piezas (`Mover`)
- Validación de movimientos (`MovimientoValido`)
- Registro de movimientos válidos
- Interacción con un tablero virtual

---

## ⚙️ ¿Cómo funciona el método `Mover`?

El método `Mover` convierte la entrada del jugador (ej. `"a2 a a4"`) en coordenadas internas (0–7), y luego:

1. Verifica que exista una pieza en la posición de origen.
2. Comprueba si el movimiento es válido con `MovimientoValido`.
3. Revisa que no se mueva sobre una pieza del mismo equipo.
4. Si todo es correcto, actualiza el tablero y guarda el movimiento en el historial.

---

## 🧠 Validación con `MovimientoValido`

Cada pieza del ajedrez (torre, peón, alfil, etc.) implementa su propia versión del método `MovimientoValido`, respetando sus reglas clásicas. Por ejemplo:

- El **peón** puede avanzar una o dos casillas (si es su primer movimiento).
- La **torre** se mueve solo en línea recta horizontal o vertical.
- Etc.

---

## 💻 Requisitos

- C++11 o superior
- Compilador compatible (g++, MSVC, Clang, etc.)

---

## 🚀 Ejecución

Compila y ejecuta el archivo principal:

```bash
g++ main.cpp -o ajedrez
./ajedrez
