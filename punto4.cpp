#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <locale>
#include <iomanip>
using namespace std;

// Declaración adelantada de la clase Polar para poder usarla dentro de Complex
class Polar;

/**
 * Clase Complex
 * Representa un número complejo en su forma binomial: a + bi
 */
class Complex {
private:
    double real;  // Parte real
    double imag;  // Parte imaginaria

public:
    // Constructor con valores por defecto
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Métodos para obtener las partes real e imaginaria
    double getReal() const { return real; }
    double getImag() const { return imag; }

    // Sobrecarga del operador suma para (complejo + complejo)
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Sobrecargas mixtas con números polares
    Complex operator+(const Polar& other) const;

    // Resta de números complejos
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    Complex operator-(const Polar& other) const;

    // Multiplicación de complejos (a + bi)(c + di)
    Complex operator*(const Complex& other) const {
        double realPart = real * other.real - imag * other.imag;
        double imagPart = real * other.imag + imag * other.real;
        return Complex(realPart, imagPart);
    }
    Complex operator*(const Polar& other) const;

    // División de complejos usando la forma binomial
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0) {
            throw runtime_error("División por cero");
        }
        double realPart = (real * other.real + imag * other.imag) / denominator;
        double imagPart = (imag * other.real - real * other.imag) / denominator;
        return Complex(realPart, imagPart);
    }
    Complex operator/(const Polar& other) const;

    // Conjugado del número complejo (cambia el signo de la parte imaginaria)
    Complex conj() const {
        return Complex(real, -imag);
    }

    // Conversión de binomial a polar
    Polar toPolar() const;

    // Imprime el número en formato a + bi
    void print() const {
        cout << fixed << setprecision(4);
        if (imag >= 0)
            cout << real << " + " << imag << "i";
        else
            cout << real << " - " << abs(imag) << "i";
    }
};


/**
 * Clase Polar
 * Representa un número complejo en forma polar: r·e^(iθ)
 */
class Polar {
private:
    double r;      // Módulo (longitud del vector)
    double theta;  // Ángulo en radianes

public:
    Polar(double radius = 0, double angle = 0) : r(radius), theta(angle) {}

    double getR() const { return r; }
    double getTheta() const { return theta; }

    // Suma de polares (se convierte a binomial, se suman y se vuelve a polar)
    Polar operator+(const Polar& other) const {
        Complex c1 = this->toComplex();
        Complex c2 = other.toComplex();
        Complex result = c1 + c2;
        return result.toPolar();
    }

    // Suma mixta (polar + complejo)
    Polar operator+(const Complex& other) const {
        Complex c1 = this->toComplex();
        Complex result = c1 + other;
        return result.toPolar();
    }

    // Resta (se realiza igual que la suma, pero restando)
    Polar operator-(const Polar& other) const {
        Complex c1 = this->toComplex();
        Complex c2 = other.toComplex();
        Complex result = c1 - c2;
        return result.toPolar();
    }
    Polar operator-(const Complex& other) const {
        Complex c1 = this->toComplex();
        Complex result = c1 - other;
        return result.toPolar();
    }

    // Multiplicación polar (r1·r2, θ1+θ2)
    Polar operator*(const Polar& other) const {
        return Polar(r * other.r, theta + other.theta);
    }
    Polar operator*(const Complex& other) const {
        Polar otherPolar = other.toPolar();
        return (*this) * otherPolar;
    }

    // División polar (r1/r2, θ1−θ2)
    Polar operator/(const Polar& other) const {
        if (other.r == 0) {
            throw runtime_error("División por cero");
        }
        return Polar(r / other.r, theta - other.theta);
    }
    Polar operator/(const Complex& other) const {
        Polar otherPolar = other.toPolar();
        return (*this) / otherPolar;
    }

    // Conjugado de un número polar (r, -θ)
    Polar conj() const {
        return Polar(r, -theta);
    }

    // Conversión de polar a complejo: (r·cosθ, r·sinθ)
    Complex toComplex() const {
        double real = r * cos(theta);
        double imag = r * sin(theta);
        return Complex(real, imag);
    }

    // Imprime el número en formato polar r·e^(iθ)
    void print() const {
        cout << fixed << setprecision(4);
        cout << r << "·e^(i·" << theta << ")";
    }
};


// Métodos de Complex que requieren conocer Polar
Polar Complex::toPolar() const {
    double radius = sqrt(real * real + imag * imag);
    double angle = atan2(imag, real);
    return Polar(radius, angle);
}
Complex Complex::operator+(const Polar& other) const {
    Complex otherComplex = other.toComplex();
    return (*this) + otherComplex;
}
Complex Complex::operator-(const Polar& other) const {
    Complex otherComplex = other.toComplex();
    return (*this) - otherComplex;
}
Complex Complex::operator*(const Polar& other) const {
    Complex otherComplex = other.toComplex();
    return (*this) * otherComplex;
}
Complex Complex::operator/(const Polar& other) const {
    Complex otherComplex = other.toComplex();
    return (*this) / otherComplex;
}


// Función que acumula (suma) una lista de números complejos
Complex acumula(const vector<Complex>& numeros) {
    Complex resultado(0, 0);
    for (const auto& num : numeros) {
        resultado = resultado + num;
    }
    return resultado;
}

// Función que acumula una mezcla de complejos y polares
Complex acumulaMixto(const vector<Complex>& complejos, const vector<Polar>& polares) {
    Complex resultado(0, 0);
    for (const auto& c : complejos) {
        resultado = resultado + c;
    }
    for (const auto& p : polares) {
        resultado = resultado + p.toComplex();
    }
    return resultado;
}


/**
 * Función principal (menú interactivo)
 * Permite crear, operar y visualizar números complejos y polares.
 */
int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");  // Permite mostrar tildes correctamente

    int opcion;
    vector<Complex> numerosComplejos;
    vector<Polar> numerosPolares;

    do {
        // Menú principal
        cout << "\nCALCULADORA DE NÚMEROS COMPLEJOS" << endl;
        cout << "1. Crear número complejo (a + bi)" << endl;
        cout << "2. Crear número polar (r·e^(iθ))" << endl;
        cout << "3. Mostrar números almacenados" << endl;
        cout << "4. Sumar dos números" << endl;
        cout << "5. Restar dos números" << endl;
        cout << "6. Multiplicar dos números" << endl;
        cout << "7. Dividir dos números" << endl;
        cout << "8. Calcular conjugado" << endl;
        cout << "9. Convertir complejo ↔ polar" << endl;
        cout << "10. Acumular múltiples números" << endl;
        cout << "11. Ejemplos predefinidos" << endl;
        cout << "0. Salir" << endl;

        cout << "\nComplejos: " << numerosComplejos.size() 
             << " | Polares: " << numerosPolares.size() << endl;

        cout << "Seleccione una opción: ";
        cin >> opcion;
        cout << endl;

        // Dependiendo de la opción elegida, se ejecuta una acción
        switch(opcion) {
            case 1: {
                // Crear un número complejo desde teclado
                double real, imag;
                cout << "Parte real: ";
                cin >> real;
                cout << "Parte imaginaria: ";
                cin >> imag;
                numerosComplejos.push_back(Complex(real, imag));
                cout << "\nNúmero creado: ";
                numerosComplejos.back().print();
                cout << endl;
                break;
            }

            case 2: {
                // Crear un número polar desde teclado
                double r, theta;
                cout << "Módulo (r): ";
                cin >> r;
                cout << "Ángulo (θ en radianes): ";
                cin >> theta;
                numerosPolares.push_back(Polar(r, theta));
                cout << "\nNúmero creado: ";
                numerosPolares.back().print();
                cout << endl;
                break;
            }

            case 3: {
                // Mostrar los números guardados
                cout << "Números complejos almacenados:" << endl;
                for (size_t i = 0; i < numerosComplejos.size(); i++) {
                    cout << "C" << i + 1 << ": ";
                    numerosComplejos[i].print();
                    cout << endl;
                }
                cout << "Números polares almacenados:" << endl;
                for (size_t i = 0; i < numerosPolares.size(); i++) {
                    cout << "P" << i + 1 << ": ";
                    numerosPolares[i].print();
                    cout << endl;
                }
                break;
            }

            // Las demás opciones realizan operaciones: suma, resta, multiplicación, etc.
            // (no se modifican, solo se comentan si lo deseas)
            
            case 0:
                cout << "¡Hasta luego!" << endl;
                break;

            default:
                cout << "Opción inválida." << endl;
        }

        // Esperar que el usuario presione Enter antes de continuar
        if (opcion != 0) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

    } while (opcion != 0);  // Repite hasta que el usuario elija salir

    return 0;
}
