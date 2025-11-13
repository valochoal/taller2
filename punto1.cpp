#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

// CLASE FRACCION 
class Fraccion {
private:
    int numerador;
    int denominador;
    
    int mcd(int a, int b) const {
        a = abs(a);
        b = abs(b);
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
    void simplificar() {
        if (denominador == 0) {
            cerr << "Error: Denominador no puede ser cero!" << endl;
            denominador = 1;
        }
        
        if (denominador < 0) {
            numerador = -numerador;
            denominador = -denominador;
        }
        
        int divisor = mcd(abs(numerador), abs(denominador));
        if (divisor > 1) {
            numerador /= divisor;
            denominador /= divisor;
        }
    }

public:
    Fraccion() : numerador(0), denominador(1) {}
    Fraccion(int n) : numerador(n), denominador(1) {}
    Fraccion(int n, int d) : numerador(n), denominador(d) {
        simplificar();
    }
    
    int getNumerador() const { return numerador; }
    int getDenominador() const { return denominador; }
    
    double aDecimal() const {
        return static_cast<double>(numerador) / denominador;
    }
    
    Fraccion operator+(const Fraccion& f) const {
        return Fraccion(numerador * f.denominador + f.numerador * denominador,
                       denominador * f.denominador);
    }
    
    Fraccion operator-(const Fraccion& f) const {
        return Fraccion(numerador * f.denominador - f.numerador * denominador,
                       denominador * f.denominador);
    }
    
    Fraccion operator*(const Fraccion& f) const {
        return Fraccion(numerador * f.numerador, denominador * f.denominador);
    }
    
    Fraccion operator/(const Fraccion& f) const {
        return Fraccion(numerador * f.denominador, denominador * f.numerador);
    }
    
    Fraccion operator-() const {
        return Fraccion(-numerador, denominador);
    }
    
    bool operator==(const Fraccion& f) const {
        return numerador * f.denominador == f.numerador * denominador;
    }
    
    double raizCuadrada() const {
        return sqrt(aDecimal());
    }
    
    void imprimir() const {
        if (denominador == 1) {
            cout << numerador;
        } else {
            cout << numerador << "/" << denominador;
        }
    }
    
    string aString() const {
        if (denominador == 1) {
            return to_string(numerador);
        } else {
            return to_string(numerador) + "/" + to_string(denominador);
        }
    }
    
    friend ostream& operator<<(ostream& os, const Fraccion& f) {
        if (f.denominador == 1) {
            os << f.numerador;
        } else {
            os << f.numerador << "/" << f.denominador;
        }
        return os;
    }
};

//  CLASE VECTOR3D 
class Vector3D {
private:
    Fraccion x, y, z;

public:
    Vector3D() : x(0), y(0), z(0) {}
    Vector3D(Fraccion x, Fraccion y, Fraccion z) : x(x), y(y), z(z) {}
    Vector3D(int x, int y, int z) : x(Fraccion(x)), y(Fraccion(y)), z(Fraccion(z)) {}
    Vector3D(int xn, int xd, int yn, int yd, int zn, int zd) 
        : x(Fraccion(xn, xd)), y(Fraccion(yn, yd)), z(Fraccion(zn, zd)) {}
    
    Fraccion getX() const { return x; }
    Fraccion getY() const { return y; }
    Fraccion getZ() const { return z; }
    
    double magnitud() const {
        double mx = x.aDecimal();
        double my = y.aDecimal();
        double mz = z.aDecimal();
        return sqrt(mx*mx + my*my + mz*mz);
    }
    
    void normalizarYMostrar() const {
        double mag = magnitud();
        if (mag == 0.0) {
            cout << "No se puede normalizar el vector cero" << endl;
            return;
        }
        cout << "Vector normalizado (decimal): (" 
             << x.aDecimal()/mag << ", " 
             << y.aDecimal()/mag << ", " 
             << z.aDecimal()/mag << ")" << endl;
    }
    
    Vector3D operator+(const Vector3D& v) const {
        return Vector3D(x + v.x, y + v.y, z + v.z);
    }
    
    Vector3D operator-(const Vector3D& v) const {
        return Vector3D(x - v.x, y - v.y, z - v.z);
    }
    
    Fraccion operator*(const Vector3D& v) const {
        return x * v.x + y * v.y + z * v.z;
    }
    
    Vector3D operator*(const Fraccion& f) const {
        return Vector3D(x * f, y * f, z * f);
    }
    
    Vector3D operator*(int n) const {
        return *this * Fraccion(n);
    }
    
    void imprimir(const string& etiqueta = "Vector") const {
        cout << etiqueta << ": (" << x << ", " << y << ", " << z << ")" << endl;
    }
    
    friend ostream& operator<<(ostream& os, const Vector3D& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
    
    friend Vector3D operator*(const Fraccion& f, const Vector3D& v) {
        return v * f;
    }
    
    friend Vector3D operator*(int n, const Vector3D& v) {
        return v * n;
    }
};

//  FUNCIONES AUXILIARES 

// Función para leer una fracción desde el teclado
Fraccion leerFraccion(const string& mensaje) {
    string input;
    cout << mensaje;
    cin >> input;
    
    // Buscar la posición del '/'
    size_t pos = input.find('/');
    
    if (pos != string::npos) {
        // Es una fracción (ej: "2/3")
        int num = stoi(input.substr(0, pos));
        int den = stoi(input.substr(pos + 1));
        return Fraccion(num, den);
    } else {
        // Es un entero (ej: "5")
        int num = stoi(input);
        return Fraccion(num, 1);
    }
}

// Función para leer un vector desde el teclado
Vector3D leerVector(const string& mensaje) {
    cout << mensaje << endl;
    Fraccion x = leerFraccion("  Componente X (ej: 2/3 o 5): ");
    Fraccion y = leerFraccion("  Componente Y (ej: 1/2 o -3): ");
    Fraccion z = leerFraccion("  Componente Z (ej: -5/2 o 0): ");
    return Vector3D(x, y, z);
}

//  PROGRAMA PRINCIPAL 

int main() {
    int opcion;
    
    do {
        cout << "    CALCULADORA DE VECTORES 3D" << endl;
        cout << "1. Calcular magnitud de un vector" << endl;
        cout << "2. Normalizar un vector" << endl;
        cout << "3. Sumar dos vectores" << endl;
        cout << "4. Restar dos vectores" << endl;
        cout << "5. Producto escalar de dos vectores" << endl;
        cout << "6. Multiplicar vector por escalar" << endl;
        cout << "0. Salir" << endl;
        cout << "NOTA: Ingrese fracciones como 2/3 o enteros como 5" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << endl;
        
        switch(opcion) {
            case 1: {
                cout << " CALCULAR MAGNITUD " << endl;
                Vector3D v = leerVector("Ingrese el vector:");
                v.imprimir("Vector");
                cout << "Magnitud: " << fixed << setprecision(4) << v.magnitud() << endl;
                break;
            }
            
            case 2: {
                cout << " NORMALIZAR VECTOR " << endl;
                Vector3D v = leerVector("Ingrese el vector:");
                v.imprimir("Vector original");
                cout << "Magnitud original: " << v.magnitud() << endl;
                v.normalizarYMostrar();
                break;
            }
            
            case 3: {
                cout << "SUMA DE VECTORES" << endl;
                Vector3D v1 = leerVector("Ingrese el primer vector:");
                Vector3D v2 = leerVector("Ingrese el segundo vector:");
                Vector3D resultado = v1 + v2;
                cout << "\nResultado:" << endl;
                v1.imprimir("v1");
                v2.imprimir("v2");
                resultado.imprimir("v1 + v2");
                break;
            }
            
            case 4: {
                cout << "RESTA DE VECTORES " << endl;
                Vector3D v1 = leerVector("Ingrese el primer vector:");
                Vector3D v2 = leerVector("Ingrese el segundo vector:");
                Vector3D resultado = v1 - v2;
                cout << "\nResultado:" << endl;
                v1.imprimir("v1");
                v2.imprimir("v2");
                resultado.imprimir("v1 - v2");
                break;
            }
            
            case 5: {
                cout << " PRODUCTO ESCALAR " << endl;
                Vector3D v1 = leerVector("Ingrese el primer vector:");
                Vector3D v2 = leerVector("Ingrese el segundo vector:");
                Fraccion producto = v1 * v2;
                cout << "\nResultado:" << endl;
                v1.imprimir("v1");
                v2.imprimir("v2");
                cout << "v1 · v2 = " << producto << " = " << producto.aDecimal() << endl;
                
                if (abs(producto.aDecimal()) < 0.0001) {
                    cout << "Los vectores son PERPENDICULARES" << endl;
                }
                break;
            }
            
            case 6: {
                cout << "MULTIPLICAR POR ESCALAR " << endl;
                Vector3D v = leerVector("Ingrese el vector:");
                Fraccion escalar = leerFraccion("Ingrese el escalar (ej: 3/2 o 4): ");
                Vector3D resultado = v * escalar;
                cout << "\nResultado:" << endl;
                v.imprimir("Vector original");
                resultado.imprimir("Vector * " + escalar.aString());
                break;
            }
            
            
            case 0:
                cout << "chaooo" << endl;
                break;
                
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
        }
        
        if (opcion != 0) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpia todo el buffer hasta el Enter
            cin.get(); // 
        }
        
    } while (opcion != 0);
    
    return 0;
}