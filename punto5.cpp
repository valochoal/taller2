#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <cctype>
using namespace std;

// Clase que representa un termino de un polinomio, como 3x^2 o -5x
class CTermino {
private:
    double coeficiente;
    int exponente;

    // Devuelve el signo que debe mostrarse segun el valor del coeficiente
    string signoString(bool esPrimerTermino) const {
        if (coeficiente > 0) return esPrimerTermino ? "" : "+";
        if (coeficiente < 0) return "-";
        return "";
    }

public:
    // Constructor por defecto: crea un termino nulo
    CTermino() : coeficiente(0.0), exponente(0) {}

    // Constructor con valores definidos
    CTermino(double c, int e) : coeficiente(c), exponente(e) {
        if (coeficiente == 0.0) exponente = 0;
    }

    double getCoeficiente() const { return coeficiente; }
    int getExponente() const { return exponente; }

    // Convierte el termino a texto legible, por ejemplo "+3x^2" o "-x"
    string toString(bool esPrimerTermino = false) const {
        if (coeficiente == 0.0) return "0";

        stringstream ss;
        string signo = signoString(esPrimerTermino);
        double absCoef = abs(coeficiente);
        if (!signo.empty()) ss << signo;

        if (exponente == 0) {
            ss << absCoef;
        } else {
            if (absCoef != 1.0) ss << absCoef;
            ss << "x";
            if (exponente != 1) ss << "^" << exponente;
        }
        return ss.str();
    }

    // Permite comparar terminos por exponente
    bool operator==(const CTermino& otro) const {
        return exponente == otro.exponente;
    }

    // Suma dos terminos que tienen el mismo exponente
    CTermino operator+(const CTermino& otro) const {
        if (exponente != otro.exponente) return *this;
        return CTermino(coeficiente + otro.coeficiente, exponente);
    }
};

// Clase que representa un polinomio completo formado por varios terminos
class CPolinomio {
private:
    vector<CTermino> terminos;

    // Inserta un termino al polinomio, combinando si hay exponentes iguales
    void agregarTerminoInterno(const CTermino& t) {
        if (t.getCoeficiente() == 0.0) return;

        for (auto& term : terminos) {
            if (term.getExponente() == t.getExponente()) {
                double nuevoCoef = term.getCoeficiente() + t.getCoeficiente();
                if (abs(nuevoCoef) < 1e-12) {
                    auto it = find_if(terminos.begin(), terminos.end(),
                        [&](const CTermino& tt) { return tt.getExponente() == t.getExponente(); });
                    if (it != terminos.end()) terminos.erase(it);
                } else {
                    term = CTermino(nuevoCoef, t.getExponente());
                }
                sort(terminos.begin(), terminos.end(),
                    [](const CTermino& a, const CTermino& b) {
                        return a.getExponente() < b.getExponente();
                    });
                return;
            }
        }

        terminos.push_back(t);
        sort(terminos.begin(), terminos.end(),
            [](const CTermino& a, const CTermino& b) {
                return a.getExponente() < b.getExponente();
            });
    }

public:
    CPolinomio() {}
    CPolinomio(const CTermino& t) { agregarTerminoInterno(t); }

    int getCantidadTerminos() const { return terminos.size(); }
    void agregarTermino(const CTermino& t) { agregarTerminoInterno(t); }

    // Suma dos polinomios y devuelve el resultado
    CPolinomio sumar(const CPolinomio& otro) const {
        CPolinomio resultado = *this;
        for (const CTermino& t : otro.terminos) resultado.agregarTerminoInterno(t);
        return resultado;
    }

    // Multiplica dos polinomios y devuelve el resultado
    CPolinomio multiplicar(const CPolinomio& otro) const {
        CPolinomio resultado;
        for (const CTermino& t1 : terminos) {
            for (const CTermino& t2 : otro.terminos) {
                double c = t1.getCoeficiente() * t2.getCoeficiente();
                int e = t1.getExponente() + t2.getExponente();
                resultado.agregarTerminoInterno(CTermino(c, e));
            }
        }
        return resultado;
    }

    CPolinomio operator+(const CPolinomio& otro) const { return sumar(otro); }
    CPolinomio operator*(const CPolinomio& otro) const { return multiplicar(otro); }

    // Convierte el polinomio completo en texto
    string toString() const {
        if (terminos.empty()) return "0";
        stringstream ss;
        bool esPrimerTermino = true;

        for (const CTermino& t : terminos) {
            string termStr = t.toString(esPrimerTermino);
            if (termStr == "0") continue;
            if (esPrimerTermino && !termStr.empty() && termStr[0] == '+') {
                termStr = termStr.substr(1);
            }
            ss << termStr;
            esPrimerTermino = false;
        }

        string res = ss.str();
        return res.empty() ? "0" : res;
    }

    friend ostream& operator<<(ostream& os, const CPolinomio& p) {
        os << p.toString();
        return os;
    }

    // Evalua el polinomio en un valor dado de x
    double evaluar(double x) const {
        double resultado = 0.0;
        for (const CTermino& t : terminos) {
            resultado += t.getCoeficiente() * pow(x, t.getExponente());
        }
        return resultado;
    }
};

// Permite al usuario ingresar un termino desde teclado
CTermino leerTermino(int indice = -1) {
    double c;
    int e;
    if (indice >= 0) cout << "  Termino " << (indice + 1) << ":" << endl;
    cout << "    Coeficiente: ";
    cin >> c;
    cout << "    Exponente (entero >= 0): ";
    cin >> e;
    return CTermino(c, e);
}

// Permite construir un polinomio a partir de la entrada del usuario
CPolinomio leerPolinomio(const string& nombre) {
    cout << "Construyendo " << nombre << ":" << endl;
    int n;
    cout << "  Cuantos terminos tiene? ";
    cin >> n;
    if (n <= 0) return CPolinomio();

    CPolinomio p;
    for (int i = 0; i < n; ++i) {
        CTermino t = leerTermino(i);
        p.agregarTermino(t);
    }
    return p;
}

int main() {
    cout << "MANIPULACION DE POLINOMIOS" << endl;

    // Polinomio P(x) = 4x^3 + 3x^2 - 2x + 7
    CPolinomio P;
    P.agregarTermino(CTermino(4, 3));
    P.agregarTermino(CTermino(3, 2));
    P.agregarTermino(CTermino(-2, 1));
    P.agregarTermino(CTermino(7, 0));

    // Polinomio Q(x) = 5x^2 - 6x + 10
    CPolinomio Q;
    Q.agregarTermino(CTermino(5, 2));
    Q.agregarTermino(CTermino(-6, 1));
    Q.agregarTermino(CTermino(10, 0));

    cout << "P(x) = " << P << endl;
    cout << "Q(x) = " << Q << endl;

    // R(x) = P(x) + Q(x)
    CPolinomio R = P + Q;
    cout << "R(x) = P(x) + Q(x) = " << R << endl;

    // S(x) = P(x) * Q(x)
    CPolinomio S = P * Q;
    cout << "S(x) = P(x) * Q(x) = " << S << endl;

    // Verificar resultados con un valor numerico
    double x = 2.0;
    cout << "\nEvaluacion numerica en x = " << x << ":" << endl;
    cout << "  P(" << x << ") = " << P.evaluar(x) << endl;
    cout << "  Q(" << x << ") = " << Q.evaluar(x) << endl;
    cout << "  R(" << x << ") = " << R.evaluar(x) << endl;
    cout << "  S(" << x << ") = " << S.evaluar(x) << endl;

    cout << "\nDesea ingresar sus propios polinomios? (s/n): ";
    char resp;
    cin >> resp;
    if (resp == 's' || resp == 'S') {
        CPolinomio A = leerPolinomio("Polinomio A");
        CPolinomio B = leerPolinomio("Polinomio B");

        cout << "\nA(x) = " << A << endl;
        cout << "B(x) = " << B << endl;
        cout << "A + B = " << (A + B) << endl;
        cout << "A * B = " << (A * B) << endl;
    }

    cout << "\nFin del programa." << endl;
    return 0;
}
