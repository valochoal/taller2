# Trabajo Práctico No. 2 - POO en C/C++

## Universidad Nacional de Colombia, Sede de La Paz
### Programación Avanzada
**Profesor:** M.Sc. Mauro Baquero-Suárez  
**Programa:** Ingeniería Mecatrónica

### Estudiantes
- Andres Mauricio Amaya Hernandez
- Valery Michel Ochoa Lechuga
- JhoeL David Ospino de La Rosa

---

## Tabla de Contenidos

- [Descripción General](#descripción-general)
- [Requisitos de Compilación](#requisitos-de-compilación)
- [Ejercicios Implementados](#ejercicios-implementados)
  - [Ejercicio 1: Vector3D (10%)](#ejercicio-1-vector3d-10)
  - [Ejercicio 2: Matriz (10%)](#ejercicio-2-matriz-10)
  - [Ejercicio 3: Polinomio (10%)](#ejercicio-3-polinomio-10)
  - [Ejercicio 4: Números Complejos (10%)](#ejercicio-4-números-complejos-10)
  - [Ejercicio 5: Manipulación de Polinomios (20%)](#ejercicio-5-manipulación-de-polinomios-20)
  - [Ejercicio 6: Juego de Dominó (40%)](#ejercicio-6-juego-de-dominó-40)

---

## Descripción General

Este repositorio contiene la solución completa del Trabajo Práctico No. 2 de la asignatura Programación Avanzada. El trabajo consiste en 6 ejercicios de Programación Orientada a Objetos (POO) en C++, abarcando desde la implementación de estructuras matemáticas básicas hasta el desarrollo de un juego de dominó completo.

Cada ejercicio está implementado en un archivo fuente independiente (`punto1.cpp`, `punto2.cpp`, ..., `punto6.cpp`) y se incluyen los ejecutables precompilados para facilitar la ejecución inmediata.

---

## Requisitos de Compilación

### Linux

Se requiere tener instalado el compilador `g++` (parte de **build-essential**):

```bash
sudo apt-get update
sudo apt-get install build-essential
```

### Windows

Se recomienda instalar **MinGW** o **MinGW-w64** para tener acceso al compilador `g++`:

1. Descargar MinGW desde [mingw-w64.org](https://www.mingw-w64.org/)
2. Instalar y agregar el directorio `bin` al PATH del sistema
3. Verificar la instalación ejecutando `g++ --version` en la terminal

### Comando General de Compilación

Para compilar cualquiera de los programas, utilice el siguiente comando:

**Linux:**
```bash
g++ puntoX.cpp -o puntoX -std=c++11
```

**Windows:**
```bash
g++ puntoX.cpp -o puntoX.exe -std=c++11
```

Donde `X` es el número del ejercicio (1, 2, 3, 4, 5 o 6).

---

## Ejercicios Implementados

### Ejercicio 1: Vector3D (10%)

**Archivo:** `punto1.cpp`

#### Descripción

Implementación de una clase `Vector3D` que representa un vector en un espacio tridimensional. La clase incluye operaciones vectoriales básicas y sobrecarga de operadores.

#### Características Implementadas

- Constructor que inicializa las coordenadas del vector (x, y, z)
- Método para calcular la magnitud del vector
- Método para normalizar el vector
- Sobrecarga de operadores:
  - `+` (suma de vectores)
  - `-` (resta de vectores)
  - `*` (producto escalar)
- Método para imprimir las coordenadas del vector

#### Metodología

Este programa aplica los conceptos fundamentales de POO en C++. Se diseñó una clase que encapsula las propiedades y operaciones de un vector tridimensional. La implementación se enfoca en:
- Encapsulación de datos mediante atributos privados
- Métodos públicos para acceder y manipular los datos
- Sobrecarga de operadores para operaciones matemáticas intuitivas
- Validación de operaciones (evitar división por cero en normalización)

#### Compilación y Ejecución

**Linux:**
```bash
g++ punto1.cpp -o punto1 -std=c++11
./punto1
```

**Windows:**
```bash
g++ punto1.cpp -o punto1.exe -std=c++11
punto1.exe
```

---

### Ejercicio 2: Matriz (10%)

**Archivo:** `punto2.cpp`

#### Descripción

Implementación de una clase `Matriz` que representa una matriz cuadrada de tamaño n×n con asignación dinámica de memoria.

#### Características Implementadas

- Constructor que inicializa la matriz con valores aleatorios
- Método para calcular la transpuesta de la matriz
- Método para multiplicar la matriz por otra matriz del mismo tamaño
- Método para imprimir la matriz en formato tabular
- Sobrecarga del operador de acceso `[]` para indexación de elementos
- Destructor que libera la memoria asignada dinámicamente

#### Metodología

El desarrollo de este ejercicio se centró en:
- Gestión dinámica de memoria usando punteros y operadores `new`/`delete`
- Implementación de operaciones matriciales fundamentales
- Sobrecarga de operadores para acceso intuitivo a elementos
- Prevención de fugas de memoria mediante un destructor apropiado
- Validación de dimensiones en operaciones matriciales

#### Compilación y Ejecución

**Linux:**
```bash
g++ punto2.cpp -o punto2 -std=c++11
./punto2
```

**Windows:**
```bash
g++ punto2.cpp -o punto2.exe -std=c++11
punto2.exe
```

---

### Ejercicio 3: Polinomio (10%)

**Archivo:** `punto3.cpp`

#### Descripción

Diseño de una clase `Polinomio` que representa un polinomio de grado n con coeficientes en arreglo dinámico.

#### Características Implementadas

- Constructor que inicializa los coeficientes del polinomio
- Método para evaluar el polinomio en un valor dado de x
- Sobrecarga de operadores:
  - `+` (suma de polinomios)
  - `*` (multiplicación de polinomios)
- Método para imprimir el polinomio en forma estándar
- Destructor que libera la memoria asignada dinámicamente
- Método para derivar el polinomio (retorna un nuevo objeto `Polinomio`)

#### Metodología

La implementación incluye:
- Representación algebraica mediante arreglos de coeficientes
- Operaciones aritméticas entre polinomios preservando el grado resultante
- Cálculo de la derivada aplicando la regla de potencias
- Evaluación eficiente usando el método de Horner
- Formateo matemático estándar para la salida

#### Compilación y Ejecución

**Linux:**
```bash
g++ punto3.cpp -o punto3 -std=c++11
./punto3
```

**Windows:**
```bash
g++ punto3.cpp -o punto3.exe -std=c++11
punto3.exe
```

---

### Ejercicio 4: Números Complejos (10%)

**Archivo:** `punto4.cpp`

#### Descripción

Implementación de dos clases para representar números complejos en forma binomial (`complex`) y polar (`polar`), con funciones de conversión entre ambas formas.

#### Características Implementadas

- Clase `complex` para números complejos en forma binomial (a + ib)
- Clase `polar` para números complejos en forma polar (r·e^(iθ))
- Operadores implementados para ambas clases:
  - `+` (suma)
  - `-` (resta)
  - `*` (multiplicación)
  - `/` (división)
  - `conj` (conjugado)
- Funciones de conversión entre formas binomial y polar
- Constructores flexibles para inicialización
- Función `acumula` que suma un número indefinido de números complejos y polares

#### Metodología

El diseño se basó en:
- Dos representaciones complementarias de números complejos
- Conversiones usando fórmulas trigonométricas estándar
- Sobrecarga de operadores para operaciones naturales
- Uso de funciones variadicas para la función `acumula`
- Manejo correcto de casos especiales (división por cero, logaritmos)

#### Compilación y Ejecución

**Linux:**
```bash
g++ punto4.cpp -o punto4 -std=c++11
./punto4
```

**Windows:**
```bash
g++ punto4.cpp -o punto4.exe -std=c++11
punto4.exe
```

---

### Ejercicio 5: Manipulación de Polinomios (20%)

**Archivo:** `punto5.cpp`

#### Descripción

Sistema completo para manipular ecuaciones algebraicas o polinómicas dependientes de una variable, utilizando las clases `CTermino` y `CPolinomio`.

#### Características Implementadas

**Clase CTermino:**
- Atributos privados: coeficiente y exponente
- Constructor con inicialización a 0 por omisión
- Métodos de acceso al coeficiente y exponente
- Método para obtener la representación en cadena (formato: ±7x⁴)

**Clase CPolinomio:**
- Atributo privado: arreglo dinámico de términos
- Constructor con inicialización de cero términos por omisión
- Método para obtener el número de términos
- Método para asignar términos (ordenados ascendentemente por exponente)
- Suma automática de coeficientes para términos con igual exponente
- Incremento automático del tamaño al insertar nuevos términos
- Método para sumar dos polinomios (retorna nuevo objeto `CPolinomio`)
- Método para multiplicar dos polinomios (retorna nuevo objeto `CPolinomio`)
- Método para obtener la representación en cadena (formato estándar)

#### Ejemplo de Operación

```
P(x) = 4x³ + 3x² - 2x + 7
Q(x) = 5x² - 6x + 10
R(x) = P(x) + Q(x) = 4x³ + 8x² - 8x + 17
```

#### Metodología

El desarrollo siguió estos principios:
- Descomposición del polinomio en términos individuales
- Arreglos dinámicos con redimensionamiento automático
- Mantenimiento del orden ascendente de exponentes
- Simplificación automática (suma de términos con igual exponente)
- Validación para evitar términos con coeficiente nulo
- Interacción con el usuario para entrada personalizada de polinomios

#### Compilación y Ejecución

**Linux:**
```bash
g++ punto5.cpp -o punto5 -std=c++11
./punto5
```

**Windows:**
```bash
g++ punto5.cpp -o punto5.exe -std=c++11
punto5.exe
```

---

### Ejercicio 6: Juego de Dominó (40%)

**Archivo:** `punto6.cpp`

#### Descripción

Implementación completa de un juego de dominó para 2-4 jugadores utilizando Programación Orientada a Objetos en C++, con interfaz de consola interactiva.

#### Características Implementadas

**Clase Ficha:**
- Representa una ficha de dominó con dos valores (números) en cada extremo
- Métodos para voltear la ficha y obtener su representación visual
- Validación de valores (0-6 para dominó estándar)

**Clase Jugador:**
- Representa a un jugador con nombre, mano de fichas y puntaje
- Métodos para agregar/quitar fichas
- Método para verificar si tiene jugadas válidas
- Sistema de puntuación para múltiples rondas

**Clase JuegoDomino:**
- Gestiona el flujo completo del juego
- Distribución aleatoria de las 28 fichas del set completo
- Control de turnos entre jugadores
- Verificación de reglas y movimientos válidos
- Detección de ganador o estado de bloqueo (tranca)
- Sistema de puntuación global
- Opción para reiniciar sin salir del programa

#### Reglas del Juego

1. **Inicio:**
   - Se reparten 7 fichas a cada jugador de forma aleatoria
   - El jugador con la ficha doble más alta comienza (o se elige al azar)

2. **Jugabilidad:**
   - Los jugadores colocan fichas que coincidan con los extremos del tablero
   - Si un jugador no tiene fichas válidas, pasa su turno
   - El juego continúa hasta que un jugador se quede sin fichas o se produzca un cierre

3. **Victoria:**
   - Gana quien se queda sin fichas primero
   - En caso de cierre (tranca), gana quien tenga menos puntos en su mano
   - Se lleva registro de victorias a lo largo de múltiples rondas

4. **Puntuación:**
   - Cada ficha vale la suma de sus dos números
   - El puntaje total es la suma de todas las fichas en la mano

#### Metodología

El desarrollo aplicó principios avanzados de POO:

- **Encapsulación:** Datos privados con acceso controlado mediante métodos públicos
- **Modularidad:** Separación clara de responsabilidades entre clases
- **Reutilización:** Métodos genéricos para operaciones comunes
- **Validación:** Verificación exhaustiva de movimientos válidos
- **Aleatoriedad:** Uso de `<random>` para distribución justa de fichas
- **Manejo de estado:** Control del estado del juego (en curso, ganado, bloqueado)
- **Interfaz amigable:** Menús claros y visualización del estado del juego

El código está completamente comentado para facilitar su comprensión y mantenimiento.

#### Compilación y Ejecución

**Linux:**
```bash
g++ punto6.cpp -o punto6 -std=c++11
./punto6
```

**Windows:**
```bash
g++ punto6.cpp -o punto6.exe -std=c++11
punto6.exe
```

#### Cómo Jugar

1. Al iniciar, ingresa el número de jugadores (2-4)
2. Ingresa los nombres de cada jugador
3. En cada turno:
   - Se muestra el tablero actual
   - Se muestran tus fichas disponibles
   - Selecciona el número de la ficha que deseas jugar
   - Si ambos extremos del tablero son válidos, elige dónde colocarla (Izquierda/Derecha)
   - Si no tienes jugadas válidas, se pasa automáticamente el turno
4. El juego anuncia al ganador de la ronda y actualiza el marcador global
5. Puedes optar por jugar otra ronda o salir del programa

#### Estructura del Código

```
punto6.cpp
├── Clase Ficha
│   ├── Atributos: valor1, valor2
│   └── Métodos: voltear(), obtenerRepresentacion(), getters
├── Clase Jugador
│   ├── Atributos: nombre, mano[], victorias
│   └── Métodos: agregarFicha(), quitarFicha(), tieneJugadaValida()
└── Clase JuegoDomino
    ├── Atributos: jugadores[], tablero[], fichasRestantes[]
    └── Métodos: iniciarJuego(), jugarTurno(), verificarGanador()
```

---

## Notas Finales

Todos los programas han sido desarrollados aplicando principios de programación limpia, modular y orientada a objetos. Cada ejercicio fue probado para verificar su correcto funcionamiento antes de generar los ejecutables incluidos en la entrega.

Los ejecutables precompilados están incluidos en el repositorio para facilitar la ejecución inmediata sin necesidad de recompilar. Sin embargo, se recomienda revisar el código fuente para comprender la implementación completa de cada solución.

---

## Entrega

**Plataforma:** Github  
**Formato:** Repositorio digital con código fuente, ejecutables y este README

