#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <locale>
#include <vector>
#include <string>

using namespace std;

//  CLASE MATRIZ
// Representa una matriz de tamaño filas×columnas con memoria dinámica.
// Permite operaciones como transpuesta, multiplicación y acceso directo.
class Matriz {
private:
    int filas;               // Número de filas
    int columnas;            // Número de columnas
    double** datos;          // Puntero doble para almacenar la matriz
    string nombre;           // Nombre de la matriz (A, B, M1, etc.)

    // Reserva memoria dinámica
    void reservarMemoria() {
        datos = new double*[filas];
        for (int i = 0; i < filas; i++)
            datos[i] = new double[columnas];
    }

    // Libera la memoria dinámica
    void liberarMemoria() {
        if (datos != nullptr) {
            for (int i = 0; i < filas; i++)
                delete[] datos[i];
            delete[] datos;
            datos = nullptr;
        }
    }

public:
    // Constructor que inicializa la matriz con valores aleatorios
    Matriz(int filas, int columnas, double min, double max, string nombre = "M")
        : filas(filas), columnas(columnas), datos(nullptr), nombre(nombre) {

        if (filas <= 0 || columnas <= 0) {
            cerr << "Error: El tamaño de la matriz debe ser positivo.\n";
            this->filas = 1;
            this->columnas = 1;
        }

        reservarMemoria();

        for (int i = 0; i < this->filas; i++) {
            for (int j = 0; j < this->columnas; j++) {
                datos[i][j] = min + (max - min) * (rand() % 100) / 99.0;
            }
        }
    }

    // Constructor que permite ingresar valores manualmente
    Matriz(int filas, int columnas, string nombre = "M")
        : filas(filas), columnas(columnas), datos(nullptr), nombre(nombre) {

        if (filas <= 0 || columnas <= 0) {
            cerr << "Error: El tamaño de la matriz debe ser positivo.\n";
            this->filas = 1;
            this->columnas = 1;
        }

        reservarMemoria();

        cout << "\nIngrese los elementos de la matriz " << nombre 
             << " (" << filas << "x" << columnas << "):\n";
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << "  Elemento [" << i << "][" << j << "]: ";
                cin >> datos[i][j];
            }
        }
    }

    // Constructor de copia
    Matriz(const Matriz& otra)
        : filas(otra.filas), columnas(otra.columnas), datos(nullptr), nombre(otra.nombre) {
        reservarMemoria();
        for (int i = 0; i < filas; i++)
            for (int j = 0; j < columnas; j++)
                datos[i][j] = otra.datos[i][j];
    }

    // Constructor para matriz vacía o inicializada en ceros
    Matriz(int filas, int columnas, bool inicializar, string nombre)
        : filas(filas), columnas(columnas), datos(nullptr), nombre(nombre) {
        reservarMemoria();
        if (inicializar)
            for (int i = 0; i < filas; i++)
                for (int j = 0; j < columnas; j++)
                    datos[i][j] = 0.0;
    }

    // Destructor
    ~Matriz() {
        liberarMemoria();
    }

    // Operador de asignación
    Matriz& operator=(const Matriz& otra) {
        if (this != &otra) {
            liberarMemoria();
            filas = otra.filas;
            columnas = otra.columnas;
            nombre = otra.nombre;
            reservarMemoria();

            for (int i = 0; i < filas; i++)
                for (int j = 0; j < columnas; j++)
                    datos[i][j] = otra.datos[i][j];
        }
        return *this;
    }

    // Métodos de acceso
    int getFilas() const { return filas; }
    int getColumnas() const { return columnas; }
    string getNombre() const { return nombre; }
    void setNombre(string nuevoNombre) { nombre = nuevoNombre; }

    // Operador [] para acceso por fila
    double* operator[](int i) {
        if (i < 0 || i >= filas) {
            cerr << "Error: Índice fuera de rango.\n";
            return datos[0];
        }
        return datos[i];
    }

    const double* operator[](int i) const {
        if (i < 0 || i >= filas) {
            cerr << "Error: Índice fuera de rango.\n";
            return datos[0];
        }
        return datos[i];
    }

    // Calcula la transpuesta
    Matriz transpuesta() const {
        Matriz resultado(columnas, filas, true, nombre + "^T");
        for (int i = 0; i < filas; i++)
            for (int j = 0; j < columnas; j++)
                resultado[j][i] = datos[i][j];
        return resultado;
    }

    // Multiplica por otra matriz
    Matriz multiplicar(const Matriz& otra) const {
        if (columnas != otra.filas) {
            cerr << "Error: No se pueden multiplicar. Columnas de A ≠ Filas de B\n";
            return Matriz(1, 1, true, "Error");
        }

        Matriz resultado(filas, otra.columnas, true, nombre + "×" + otra.nombre);
        for (int i = 0; i < filas; i++)
            for (int j = 0; j < otra.columnas; j++)
                for (int k = 0; k < columnas; k++)
                    resultado[i][j] += datos[i][k] * otra.datos[k][j];
        return resultado;
    }

    // Sobrecarga del operador *
    Matriz operator*(const Matriz& otra) const {
        return multiplicar(otra);
    }

    // Imprime la matriz
    void imprimir(int precision = 2) const {
        cout << "Matriz " << nombre << " (" << filas << "x" << columnas << "):\n";
        for (int i = 0; i < filas; i++) {
            cout << "[ ";
            for (int j = 0; j < columnas; j++) {
                cout << setw(8) << fixed << setprecision(precision) << datos[i][j];
                if (j < columnas - 1) cout << ", ";
            }
            cout << " ]\n";
        }
        cout << endl;
    }

    // Establece o obtiene valores individuales
    void setValor(int i, int j, double valor) {
        if (i >= 0 && i < filas && j >= 0 && j < columnas)
            datos[i][j] = valor;
        else
            cerr << "Error: Índices fuera de rango.\n";
    }

    double getValor(int i, int j) const {
        if (i >= 0 && i < filas && j >= 0 && j < columnas)
            return datos[i][j];
        cerr << "Error: Índices fuera de rango.\n";
        return 0.0;
    }
};

//  FUNCIONES AUXILIARES
void mostrarMatricesAlmacenadas(const vector<Matriz*>& matrices) {
    if (matrices.empty()) {
        cout << "No hay matrices almacenadas.\n";
        return;
    }

    cout << "\n=== MATRICES ALMACENADAS ===\n";
    for (size_t i = 0; i < matrices.size(); i++) {
        cout << i + 1 << ". " << matrices[i]->getNombre()
             << " (" << matrices[i]->getFilas() << "x"
             << matrices[i]->getColumnas() << ")\n";
    }
    cout << endl;
}

int seleccionarMatriz(const vector<Matriz*>& matrices, const string& mensaje) {
    if (matrices.empty()) {
        cout << "No hay matrices almacenadas.\n";
        return -1;
    }

    mostrarMatricesAlmacenadas(matrices);
    int opcion;
    cout << mensaje;
    cin >> opcion;

    if (opcion < 1 || opcion > (int)matrices.size()) {
        cout << "Opción inválida.\n";
        return -1;
    }

    return opcion - 1;
}


//  PROGRAMA PRINCIPAL


int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    srand(time(0));

    int opcion;
    vector<Matriz*> matrices;

    do {

        cout << "      CALCULADORA DE MATRICES\n";

        cout << "1. Crear matriz con valores aleatorios\n";
        cout << "2. Crear matriz ingresando valores manualmente\n";
        cout << "3. Mostrar todas las matrices almacenadas\n";
        cout << "4. Mostrar una matriz específica\n";
        cout << "5. Calcular transpuesta de una matriz\n";
        cout << "6. Multiplicar dos matrices\n";
        cout << "7. Acceder a un elemento\n";
        cout << "8. Modificar un elemento\n";
        cout << "9. Eliminar una matriz\n";
        cout << "10. Ejemplos predefinidos\n";
        cout << "0. Salir\n";

        cout << "Matrices almacenadas: " << matrices.size() << "\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
            case 1: {
                cout << " CREAR MATRIZ ALEATORIA \n";
                string nombre; int filas, columnas; double min, max;

                cout << "Nombre de la matriz: ";
                cin >> nombre;
                cout << "Número de filas: ";
                cin >> filas;
                cout << "Número de columnas: ";
                cin >> columnas;
                cout << "Valor mínimo: ";
                cin >> min;
                cout << "Valor máximo: ";
                cin >> max;

                Matriz* nueva = new Matriz(filas, columnas, min, max, nombre);
                matrices.push_back(nueva);

                cout << "\nMatriz creada exitosamente:\n";
                nueva->imprimir();
                break;
            }

            case 2: {
                cout << "CREAR MATRIZ MANUAL \n";
                string nombre; int filas, columnas;

                cout << "Nombre de la matriz: ";
                cin >> nombre;
                cout << "Número de filas: ";
                cin >> filas;
                cout << "Número de columnas: ";
                cin >> columnas;

                Matriz* nueva = new Matriz(filas, columnas, nombre);
                matrices.push_back(nueva);

                cout << "\nMatriz creada exitosamente:\n";
                nueva->imprimir();
                break;
            }

            case 3: {
                cout << " TODAS LAS MATRICES \n";
                if (matrices.empty())
                    cout << "No hay matrices almacenadas.\n";
                else
                    for (auto* m : matrices) m->imprimir();
                break;
            }

            case 4: {
                cout << " MOSTRAR MATRIZ \n";
                int idx = seleccionarMatriz(matrices, "Seleccione la matriz: ");
                if (idx >= 0) matrices[idx]->imprimir();
                break;
            }

            case 5: {
                cout << " TRANSPUESTA \n";
                int idx = seleccionarMatriz(matrices, "Seleccione la matriz: ");
                if (idx >= 0) {
                    matrices[idx]->imprimir();
                    Matriz transpuesta = matrices[idx]->transpuesta();
                    transpuesta.imprimir();

                    char guardar;
                    cout << "¿Desea guardar la transpuesta? (s/n): ";
                    cin >> guardar;
                    if (guardar == 's' || guardar == 'S') {
                        matrices.push_back(new Matriz(transpuesta));
                        cout << "Transpuesta guardada.\n";
                    }
                }
                break;
            }

            case 6: {
                cout << " MULTIPLICAR MATRICES \n";
                if (matrices.size() < 2) {
                    cout << "Debe haber al menos dos matrices.\n";
                    break;
                }

                int idx1 = seleccionarMatriz(matrices, "Primera matriz: ");
                if (idx1 < 0) break;
                int idx2 = seleccionarMatriz(matrices, "Segunda matriz: ");
                if (idx2 < 0) break;

                matrices[idx1]->imprimir();
                matrices[idx2]->imprimir();

                if (matrices[idx1]->getColumnas() != matrices[idx2]->getFilas()) {
                    cout << "Error: Las columnas de la primera deben coincidir con las filas de la segunda.\n";
                } else {
                    Matriz resultado = (*matrices[idx1]) * (*matrices[idx2]);
                    resultado.imprimir();

                    char guardar;
                    cout << "¿Desea guardar el resultado? (s/n): ";
                    cin >> guardar;
                    if (guardar == 's' || guardar == 'S') {
                        matrices.push_back(new Matriz(resultado));
                        cout << "Resultado guardado.\n";
                    }
                }
                break;
            }

            case 7: {
                cout << " ACCEDER A ELEMENTO \n";
                int idx = seleccionarMatriz(matrices, "Seleccione la matriz: ");
                if (idx >= 0) {
                    matrices[idx]->imprimir();
                    int i, j;
                    cout << "Fila (0-" << matrices[idx]->getFilas() - 1 << "): ";
                    cin >> i;
                    cout << "Columna (0-" << matrices[idx]->getColumnas() - 1 << "): ";
                    cin >> j;
                    cout << "Valor: " << (*matrices[idx])[i][j] << endl;
                }
                break;
            }

            case 8: {
                cout << " MODIFICAR ELEMENTO \n";
                int idx = seleccionarMatriz(matrices, "Seleccione la matriz: ");
                if (idx >= 0) {
                    matrices[idx]->imprimir();
                    int i, j; double valor;
                    cout << "Fila (0-" << matrices[idx]->getFilas() - 1 << "): ";
                    cin >> i;
                    cout << "Columna (0-" << matrices[idx]->getColumnas() - 1 << "): ";
                    cin >> j;
                    cout << "Nuevo valor: ";
                    cin >> valor;
                    (*matrices[idx])[i][j] = valor;
                    matrices[idx]->imprimir();
                }
                break;
            }

            case 9: {
                cout << "ELIMINAR MATRIZ \n";
                int idx = seleccionarMatriz(matrices, "Seleccione la matriz a eliminar: ");
                if (idx >= 0) {
                    cout << "Eliminando matriz " << matrices[idx]->getNombre() << "...\n";
                    delete matrices[idx];
                    matrices.erase(matrices.begin() + idx);
                    cout << "Matriz eliminada.\n";
                }
                break;
            }

            case 10: {
                cout << " EJEMPLOS PREDEFINIDOS \n";
                Matriz* m1 = new Matriz(3, 3, 1.0, 5.0, "Ejemplo1");
                m1->imprimir();
                matrices.push_back(m1);

                Matriz transp = m1->transpuesta();
                transp.imprimir();

                Matriz* m2 = new Matriz(3, 2, 0.0, 3.0, "Ejemplo2");
                m2->imprimir();
                matrices.push_back(m2);

                cout << "Ejemplos añadidos al almacén.\n";
                break;
            }

            case 0:
                cout << "Liberando memoria y saliendo...\n";
                break;

            default:
                cout << "Opción inválida. Intente de nuevo.\n";
        }

        if (opcion != 0) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

    } while (opcion != 0);

    for (auto* m : matrices)
        delete m;
    matrices.clear();

    return 0;
}
