#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <locale>
#include <vector>

using namespace std;

/**
 * @class Polinomio
 * @brief Representa un polinomio de grado n con coeficientes dinámicos
 * 
 * Esta clase implementa un polinomio P(x) = a_n*x^n + ... + a_1*x + a_0
 * con operaciones de suma, multiplicación, evaluación y derivación.
 */
class Polinomio {
private:
    int grado;        // Grado del polinomio
    double* coef;     // Arreglo dinámico de coeficientes
    
    /**
     * @brief Elimina coeficientes cero del término de mayor grado
     */
    void ajustarGrado() {
        while (grado > 0 && abs(coef[grado]) < 1e-10) {
            grado--;
        }
    }

public:
    /**
     * @brief Constructor que inicializa el polinomio con coeficientes dados
     * @param grado Grado del polinomio
     * @param coeficientes Vector con los coeficientes (opcional)
     */
    Polinomio(int grado, const vector<double>& coeficientes = vector<double>()) 
        : grado(grado), coef(nullptr) {
        
        if (grado < 0) {
            cerr << "Error: El grado debe ser no negativo." << endl;
            this->grado = 0;
        }
        
        // Reservar memoria para grado+1 coeficientes (de x^0 hasta x^grado)
        coef = new double[this->grado + 1];
        
        // Inicializar coeficientes
        for (int i = 0; i <= this->grado; i++) {
            if (i < (int)coeficientes.size()) {
                coef[i] = coeficientes[i];
            } else {
                coef[i] = 0.0;
            }
        }
        
        ajustarGrado();
    }
    
    /**
     * @brief Constructor que solicita coeficientes al usuario
     * @param grado Grado del polinomio
     * @param pedirCoeficientes Si true, solicita los coeficientes al usuario
     */
    Polinomio(int grado, bool pedirCoeficientes) : grado(grado), coef(nullptr) {
        if (grado < 0) {
            cerr << "Error: El grado debe ser no negativo." << endl;
            this->grado = 0;
        }
        
        coef = new double[this->grado + 1];
        
        if (pedirCoeficientes) {
            cout << "\nIngrese los coeficientes del polinomio:" << endl;
            cout << "(P(x) = a_" << grado << "*x^" << grado << " + ... + a_1*x + a_0)" << endl;
            
            for (int i = grado; i >= 0; i--) {
                cout << "  Coeficiente de x^" << i << ": ";
                cin >> coef[i];
            }
        } else {
            for (int i = 0; i <= grado; i++) {
                coef[i] = 0.0;
            }
        }
        
        ajustarGrado();
    }
    
    /**
     * @brief Constructor de copia
     */
    Polinomio(const Polinomio& otro) : grado(otro.grado), coef(nullptr) {
        coef = new double[grado + 1];
        for (int i = 0; i <= grado; i++) {
            coef[i] = otro.coef[i];
        }
    }
    
    /**
     * @brief Destructor que libera la memoria asignada dinámicamente
     */
    ~Polinomio() {
        if (coef != nullptr) {
            delete[] coef;
            coef = nullptr;
        }
    }
    
    /**
     * @brief Operador de asignación
     */
    Polinomio& operator=(const Polinomio& otro) {
        if (this != &otro) {
            delete[] coef;
            grado = otro.grado;
            coef = new double[grado + 1];
            for (int i = 0; i <= grado; i++) {
                coef[i] = otro.coef[i];
            }
        }
        return *this;
    }
    
    /**
     * @brief Obtiene el grado del polinomio
     */
    int getGrado() const { return grado; }
    
    /**
     * @brief Obtiene un coeficiente específico
     */
    double getCoeficiente(int i) const {
        if (i >= 0 && i <= grado) {
            return coef[i];
        }
        return 0.0;
    }
    
    /**
     * @brief Evalúa el polinomio en un valor x dado
     * @param x Valor en el cual evaluar el polinomio
     * @return P(x)
     */
    double evaluar(double x) const {
        double resultado = 0.0;
        double potencia = 1.0; // x^0 = 1
        
        // Método de Horner para eficiencia
        // P(x) = a_0 + x(a_1 + x(a_2 + ... + x(a_n)))
        resultado = coef[grado];
        for (int i = grado - 1; i >= 0; i--) {
            resultado = resultado * x + coef[i];
        }
        
        return resultado;
    }
    
    /**
     * @brief Suma dos polinomios
     * @param otro Polinomio a sumar
     * @return Nuevo polinomio resultado de la suma
     */
    Polinomio operator+(const Polinomio& otro) const {
        int nuevoGrado = max(grado, otro.grado);
        vector<double> nuevosCoef(nuevoGrado + 1, 0.0);
        
        for (int i = 0; i <= grado; i++) {
            nuevosCoef[i] += coef[i];
        }
        
        for (int i = 0; i <= otro.grado; i++) {
            nuevosCoef[i] += otro.coef[i];
        }
        
        return Polinomio(nuevoGrado, nuevosCoef);
    }
    
    /**
     * @brief Multiplica dos polinomios
     * @param otro Polinomio a multiplicar
     * @return Nuevo polinomio resultado de la multiplicación
     */
    Polinomio operator*(const Polinomio& otro) const {
        int nuevoGrado = grado + otro.grado;
        vector<double> nuevosCoef(nuevoGrado + 1, 0.0);
        
        // Multiplicar término a término
        for (int i = 0; i <= grado; i++) {
            for (int j = 0; j <= otro.grado; j++) {
                nuevosCoef[i + j] += coef[i] * otro.coef[j];
            }
        }
        
        return Polinomio(nuevoGrado, nuevosCoef);
    }
    
    /**
     * @brief Calcula la derivada del polinomio
     * @return Nuevo polinomio que representa la derivada
     */
    Polinomio derivar() const {
        if (grado == 0) {
            // La derivada de una constante es cero
            return Polinomio(0, vector<double>(1, 0.0));
        }
        
        int nuevoGrado = grado - 1;
        vector<double> nuevosCoef(nuevoGrado + 1);
        
        // d/dx(a_n * x^n) = n * a_n * x^(n-1)
        for (int i = 1; i <= grado; i++) {
            nuevosCoef[i - 1] = i * coef[i];
        }
        
        return Polinomio(nuevoGrado, nuevosCoef);
    }
    
    /**
     * @brief Imprime el polinomio en forma estándar
     */
    void imprimir() const {
        if (grado == 0 && abs(coef[0]) < 1e-10) {
            cout << "0" << endl;
            return;
        }
        
        bool primero = true;
        
        // Imprimir desde el término de mayor grado
        for (int i = grado; i >= 0; i--) {
            if (abs(coef[i]) < 1e-10) continue; // Saltar términos con coeficiente cero
            
            // Signo
            if (!primero) {
                if (coef[i] > 0) {
                    cout << " + ";
                } else {
                    cout << " - ";
                }
            } else {
                if (coef[i] < 0) {
                    cout << "-";
                }
                primero = false;
            }
            
            double coefAbs = abs(coef[i]);
            
            // Coeficiente (solo si no es 1, o si es término constante)
            if (i == 0 || coefAbs != 1.0) {
                // Mostrar sin decimales si es entero
                if (coefAbs == floor(coefAbs)) {
                    cout << (int)coefAbs;
                } else {
                    cout << fixed << setprecision(2) << coefAbs;
                }
            }
            
            // Variable y exponente
            if (i > 0) {
                cout << "x";
                if (i > 1) {
                    cout << "^" << i;
                }
            }
        }
        
        cout << endl;
    }
    
    /**
     * @brief Imprime el polinomio con etiqueta
     */
    void imprimir(const string& etiqueta) const {
        cout << etiqueta << ": ";
        imprimir();
    }
};

// ==================== PROGRAMA PRINCIPAL ====================

int main() {
    // Configurar UTF-8 para caracteres en español
    setlocale(LC_ALL, "es_ES.UTF-8");
    
    int opcion;
    vector<Polinomio*> polinomios; // Almacén de polinomios
    
    do {
        cout << "\n========================================" << endl;
        cout << "      CALCULADORA DE POLINOMIOS" << endl;
        cout << "========================================" << endl;
        cout << "1. Crear polinomio ingresando coeficientes" << endl;
        cout << "2. Mostrar todos los polinomios" << endl;
        cout << "3. Evaluar un polinomio en x" << endl;
        cout << "4. Sumar dos polinomios" << endl;
        cout << "5. Multiplicar dos polinomios" << endl;
        cout << "6. Derivar un polinomio" << endl;
        cout << "7. Eliminar un polinomio" << endl;
        cout << "8. Ejemplos predefinidos" << endl;
        cout << "0. Salir" << endl;
        cout << "========================================" << endl;
        cout << "Polinomios almacenados: " << polinomios.size() << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cout << endl;
        
        switch(opcion) {
            case 1: {
                cout << "=== CREAR POLINOMIO ===" << endl;
                int grado;
                cout << "Ingrese el grado del polinomio: ";
                cin >> grado;
                
                Polinomio* nuevo = new Polinomio(grado, true);
                polinomios.push_back(nuevo);
                
                cout << "\nPolinomio creado:" << endl;
                cout << "P" << polinomios.size() << "(x) = ";
                nuevo->imprimir();
                break;
            }
            
            case 2: {
                cout << "=== POLINOMIOS ALMACENADOS ===" << endl;
                if (polinomios.empty()) {
                    cout << "No hay polinomios almacenados." << endl;
                } else {
                    for (size_t i = 0; i < polinomios.size(); i++) {
                        cout << "P" << (i+1) << "(x) = ";
                        polinomios[i]->imprimir();
                    }
                }
                break;
            }
            
            case 3: {
                cout << "=== EVALUAR POLINOMIO ===" << endl;
                if (polinomios.empty()) {
                    cout << "No hay polinomios almacenados." << endl;
                    break;
                }
                
                // Mostrar polinomios
                for (size_t i = 0; i < polinomios.size(); i++) {
                    cout << (i+1) << ". P" << (i+1) << "(x) = ";
                    polinomios[i]->imprimir();
                }
                
                int idx;
                double x;
                cout << "\nSeleccione el polinomio: ";
                cin >> idx;
                
                if (idx < 1 || idx > (int)polinomios.size()) {
                    cout << "Opción inválida." << endl;
                    break;
                }
                
                cout << "Ingrese el valor de x: ";
                cin >> x;
                
                double resultado = polinomios[idx-1]->evaluar(x);
                cout << "\nP" << idx << "(" << x << ") = " << fixed << setprecision(4) 
                     << resultado << endl;
                break;
            }
            
            case 4: {
                cout << "=== SUMAR POLINOMIOS ===" << endl;
                if (polinomios.size() < 2) {
                    cout << "Se necesitan al menos 2 polinomios." << endl;
                    break;
                }
                
                // Mostrar polinomios
                for (size_t i = 0; i < polinomios.size(); i++) {
                    cout << (i+1) << ". P" << (i+1) << "(x) = ";
                    polinomios[i]->imprimir();
                }
                
                int idx1, idx2;
                cout << "\nSeleccione el primer polinomio: ";
                cin >> idx1;
                cout << "Seleccione el segundo polinomio: ";
                cin >> idx2;
                
                if (idx1 < 1 || idx1 > (int)polinomios.size() || 
                    idx2 < 1 || idx2 > (int)polinomios.size()) {
                    cout << "Opción inválida." << endl;
                    break;
                }
                
                cout << "\nP" << idx1 << "(x) = ";
                polinomios[idx1-1]->imprimir();
                cout << "P" << idx2 << "(x) = ";
                polinomios[idx2-1]->imprimir();
                
                Polinomio suma = (*polinomios[idx1-1]) + (*polinomios[idx2-1]);
                cout << "\nP" << idx1 << "(x) + P" << idx2 << "(x) = ";
                suma.imprimir();
                
                char guardar;
                cout << "\n¿Desea guardar el resultado? (s/n): ";
                cin >> guardar;
                if (guardar == 's' || guardar == 'S') {
                    polinomios.push_back(new Polinomio(suma));
                    cout << "Resultado guardado como P" << polinomios.size() << "(x)" << endl;
                }
                break;
            }
            
            case 5: {
                cout << "=== MULTIPLICAR POLINOMIOS ===" << endl;
                if (polinomios.size() < 2) {
                    cout << "Se necesitan al menos 2 polinomios." << endl;
                    break;
                }
                
                // Mostrar polinomios
                for (size_t i = 0; i < polinomios.size(); i++) {
                    cout << (i+1) << ". P" << (i+1) << "(x) = ";
                    polinomios[i]->imprimir();
                }
                
                int idx1, idx2;
                cout << "\nSeleccione el primer polinomio: ";
                cin >> idx1;
                cout << "Seleccione el segundo polinomio: ";
                cin >> idx2;
                
                if (idx1 < 1 || idx1 > (int)polinomios.size() || 
                    idx2 < 1 || idx2 > (int)polinomios.size()) {
                    cout << "Opción inválida." << endl;
                    break;
                }
                
                cout << "\nP" << idx1 << "(x) = ";
                polinomios[idx1-1]->imprimir();
                cout << "P" << idx2 << "(x) = ";
                polinomios[idx2-1]->imprimir();
                
                Polinomio producto = (*polinomios[idx1-1]) * (*polinomios[idx2-1]);
                cout << "\nP" << idx1 << "(x) × P" << idx2 << "(x) = ";
                producto.imprimir();
                
                char guardar;
                cout << "\n¿Desea guardar el resultado? (s/n): ";
                cin >> guardar;
                if (guardar == 's' || guardar == 'S') {
                    polinomios.push_back(new Polinomio(producto));
                    cout << "Resultado guardado como P" << polinomios.size() << "(x)" << endl;
                }
                break;
            }
            
            case 6: {
                cout << "=== DERIVAR POLINOMIO ===" << endl;
                if (polinomios.empty()) {
                    cout << "No hay polinomios almacenados." << endl;
                    break;
                }
                
                // Mostrar polinomios
                for (size_t i = 0; i < polinomios.size(); i++) {
                    cout << (i+1) << ". P" << (i+1) << "(x) = ";
                    polinomios[i]->imprimir();
                }
                
                int idx;
                cout << "\nSeleccione el polinomio a derivar: ";
                cin >> idx;
                
                if (idx < 1 || idx > (int)polinomios.size()) {
                    cout << "Opción inválida." << endl;
                    break;
                }
                
                cout << "\nP" << idx << "(x) = ";
                polinomios[idx-1]->imprimir();
                
                Polinomio derivada = polinomios[idx-1]->derivar();
                cout << "P" << idx << "'(x) = ";
                derivada.imprimir();
                
                char guardar;
                cout << "\n¿Desea guardar la derivada? (s/n): ";
                cin >> guardar;
                if (guardar == 's' || guardar == 'S') {
                    polinomios.push_back(new Polinomio(derivada));
                    cout << "Derivada guardada como P" << polinomios.size() << "(x)" << endl;
                }
                break;
            }
            
            case 7: {
                cout << "=== ELIMINAR POLINOMIO ===" << endl;
                if (polinomios.empty()) {
                    cout << "No hay polinomios almacenados." << endl;
                    break;
                }
                
                for (size_t i = 0; i < polinomios.size(); i++) {
                    cout << (i+1) << ". P" << (i+1) << "(x) = ";
                    polinomios[i]->imprimir();
                }
                
                int idx;
                cout << "\nSeleccione el polinomio a eliminar: ";
                cin >> idx;
                
                if (idx < 1 || idx > (int)polinomios.size()) {
                    cout << "Opción inválida." << endl;
                    break;
                }
                
                delete polinomios[idx-1];
                polinomios.erase(polinomios.begin() + idx - 1);
                cout << "Polinomio eliminado." << endl;
                break;
            }
            
            case 8: {
                cout << "\n=== EJEMPLOS PREDEFINIDOS ===" << endl;
                
                cout << "\nEjemplo 1: P(x) = 4x³ + 3x² - 2x + 7" << endl;
                Polinomio* p1 = new Polinomio(3, {7, -2, 3, 4});
                p1->imprimir("P1(x)");
                polinomios.push_back(p1);
                
                cout << "\nEjemplo 2: Q(x) = 5x² - 6x + 10" << endl;
                Polinomio* p2 = new Polinomio(2, {10, -6, 5});
                p2->imprimir("Q(x)");
                polinomios.push_back(p2);
                
                cout << "\nEjemplo 3: Suma P(x) + Q(x)" << endl;
                Polinomio suma = (*p1) + (*p2);
                suma.imprimir("P(x) + Q(x)");
                
                cout << "\nEjemplo 4: Producto P(x) × Q(x)" << endl;
                Polinomio producto = (*p1) * (*p2);
                producto.imprimir("P(x) × Q(x)");
                
                cout << "\nEjemplo 5: Derivada de P(x)" << endl;
                Polinomio derivada = p1->derivar();
                derivada.imprimir("P'(x)");
                
                cout << "\nEjemplo 6: Evaluar P(2)" << endl;
                double valor = p1->evaluar(2);
                cout << "P(2) = " << valor << endl;
                
                cout << "\nLos polinomios P1 y Q han sido añadidos al almacén." << endl;
                break;
            }
            
            case 0:
                cout << "Liberando memoria y saliendo..." << endl;
                break;
                
            default:
                cout << "Opción inválida. Intente de nuevo." << endl;
        }
        
        if (opcion != 0) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
        
    } while (opcion != 0);
    
    // Liberar memoria de todos los polinomios antes de salir
    for (size_t i = 0; i < polinomios.size(); i++) {
        delete polinomios[i];
    }
    polinomios.clear();
    
    return 0;
}