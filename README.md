# Universidad Nacional de Colombia, sede de La Paz
## TALLER #2 PROGRAMACIÓN AVANZADA
### ESTUDIANTES:
Andres Mauricio Amaya Hernandez
Valery Michel Ochoa Lechuga
JhoeL David Ospino de La Rosa

### Explicación.
Para cada uno de los programas desarrollados se incluye el archivo ejecutable, por lo que no es necesario volver a compilar el código para su ejecución. Sin embargo, si se desea compilar de nuevo, el comando general que se debe utilizar es:
g++ nombreArchivo.cpp -o nombreArchivo -std=c++11
Este comando toma el archivo del código fuente (por ejemplo punto1.cpp, punto2.cpp, etc.), lo compila usando el estándar de C++11 (en Windows), para Linux utilizamos G++ de Build Essentials y genera un ejecutable con el mismo nombre. Para ejecutarlo se usa ./nombreArchivo en sistemas Linux o simplemente nombreArchivo en Windows. A continuación se describe cada punto con su metodología y forma de ejecución.

#### Punto 1:
Para compilar el archivo se usa el comando g++ punto1.cpp -o punto1 -std=c++11 y para ejecutarlo ./punto1 o punto1 en Windows. Este primer programa se enfocó en aplicar los conceptos básicos de programación estructurada en C++. La metodología consistió en identificar los datos de entrada, definir las operaciones que debía realizar el programa y mostrar los resultados de forma clara al usuario. Se buscó construir un código limpio, con funciones simples y bien separadas, que resolviera el problema propuesto por el profesor paso a paso.

#### Punto 2:
Para compilar se utiliza el comando g++ punto2.cpp -o punto2 -std=c++11 y se ejecuta con ./punto2 o punto2 en Windows. En este caso, el programa se desarrolló aplicando el paradigma de programación orientada a objetos, dividiendo el problema en clases y métodos. La metodología usada consistió en representar cada elemento del problema mediante objetos con atributos definidos y operaciones propias. Se priorizó la reutilización de código, la claridad en las relaciones entre las clases y la validación de los datos de entrada. Este enfoque permitió una solución modular y fácil de entender, donde cada parte cumple una función específica dentro del sistema.

#### Punto 3:
Para compilar se usa g++ punto3.cpp -o punto3 -std=c++11 y se ejecuta con ./punto3. En este punto se implementaron estructuras de control más complejas y manejo de datos en arreglos o vectores, según el problema dado. La metodología se basó en analizar el comportamiento esperado del sistema, definir las estructuras adecuadas para almacenar la información y desarrollar funciones que realizaran las operaciones necesarias. Se probaron varios casos para garantizar que los resultados fueran correctos. El enfoque fue combinar precisión matemática con un diseño ordenado que facilitara la lectura del código.

#### Punto 4:
Para compilar este programa se ejecuta g++ punto4.cpp -o punto4 -std=c++11 y para correrlo ./punto4 o punto4 en Windows. La metodología utilizada consistió en desarrollar una lógica que resolviera un problema de tipo algorítmico o numérico, descomponiendo el proceso general en pasos más pequeños. Se aplicaron conceptos de funciones, ciclos y condiciones para controlar el flujo del programa. El objetivo fue lograr que el código fuera lo suficientemente flexible para aceptar diferentes datos de entrada y producir resultados confiables sin necesidad de modificar su estructura principal.

#### Punto 5:
Para compilar el archivo se usa g++ punto5.cpp -o punto5 -std=c++11 y para ejecutar ./punto5 o punto5 en Windows. Este programa implementa la manipulación de polinomios mediante clases en C++. La metodología empleada se centró en representar matemáticamente los polinomios como combinaciones de términos individuales, donde cada término tiene un coeficiente y un exponente. Se crearon las clases CTermino y CPolinomio para manejar las operaciones de suma, multiplicación y evaluación de polinomios. La solución combina la teoría algebraica con la programación orientada a objetos, permitiendo trabajar con expresiones simbólicas y numéricas. El programa también ofrece interacción con el usuario para ingresar polinomios personalizados y obtener los resultados de manera dinámica.


En general, todos los programas se desarrollaron aplicando principios de programación limpia, modular y orientada a resolver los problemas paso a paso según las indicaciones del profesor. Cada uno fue probado individualmente para verificar su correcto funcionamiento antes de generar los ejecutables incluidos en la entrega.


## Juego de Dominó en C++ (Explicación)

Este proyecto implementa un juego de dominó clásico para 2 a 4 jugadores en la consola, desarrollado en C++ utilizando Programación Orientada a Objetos.

## Características

- **Clases**: `Ficha`, `Jugador`, `JuegoDomino`.
- **Jugadores**: Soporte para 2 a 4 jugadores humanos.
- **Reglas**:
    - Se reparten 7 fichas a cada jugador.
    - Los jugadores deben colocar una ficha que coincida con uno de los extremos del tablero.
    - Si un jugador no tiene fichas válidas, pasa el turno.
    - Gana la ronda quien se queda sin fichas o quien tiene menos puntos en caso de cierre (tranca).
- **Puntuación**: Se lleva un registro de las victorias de cada jugador.
- **Reiniciar**: Opción para jugar múltiples partidas sin salir del programa.

## Compilación y Ejecución

Para compilar el código, asegúrate de tener un compilador de C++ instalado (como `g++`).

### Compilar

```bash
g++ punto6.cpp -o punto6
```

### Ejecutar

```bash
./punto6
```

## Cómo Jugar

1.  Al iniciar, ingresa el número de jugadores (2-4).
2.  Ingresa los nombres de los jugadores.
3.  En cada turno, se mostrará el tablero y tu mano.
4.  Selecciona el número de la ficha que deseas jugar.
5.  Si es necesario, elige en qué extremo del tablero colocar la ficha (Izquierda/Derecha).
6.  El juego anunciará al ganador de la ronda y mostrará el marcador global.
7.  Elige si deseas jugar otra ronda.

## Estructura del Código

- **Ficha**: Representa una pieza de dominó con dos valores y métodos para voltearla y obtener su representación.
- **Jugador**: Gestiona la mano de fichas, el nombre y el puntaje de victorias.
- **JuegoDomino**: Controlador principal que maneja el flujo del juego, turnos, validación de reglas y estado del tablero.
