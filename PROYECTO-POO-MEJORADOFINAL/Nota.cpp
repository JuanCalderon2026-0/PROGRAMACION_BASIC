#include "Nota.h"
#include <iomanip>

// Constructores
Nota::Nota() : bimestre(0), valor(0.0f) {}
Nota::Nota(int b, float v) : bimestre(b), valor(v) {}

// Getters
int   Nota::getBimestre() const { return bimestre; }
float Nota::getValor()    const { return valor;    }

// Setters
void Nota::setBimestre(int b)  { bimestre = b; }
void Nota::setValor(float v)   { valor    = v; }

// ============================================================
//   SOBRECARGA DE OPERADORES
//   Concepto: operator overloading — los operadores se redefinen
//   para trabajar con objetos de tipo Nota de forma intuitiva.
// ============================================================

// Operador + : suma los valores de dos notas
// Conserva el bimestre de la nota izquierda (la base)
Nota Nota::operator+(const Nota& otra) const {
    return Nota(this->bimestre, this->valor + otra.valor);
}

// Operador < : compara por valor numerico (para ordenamiento)
bool Nota::operator<(const Nota& otra) const {
    return this->valor < otra.valor;
}

// Operador == : igualdad si mismo bimestre y mismo valor
bool Nota::operator==(const Nota& otra) const {
    return (this->bimestre == otra.bimestre) &&
           (this->valor    == otra.valor);
}

// Operador > : mayor por valor numerico
bool Nota::operator>(const Nota& otra) const {
    return this->valor > otra.valor;
}

// Operador << : salida formateada para cout
// Concepto: friend function — accede a privados desde afuera
ostream& operator<<(ostream& os, const Nota& nota) {
    os << "B" << nota.bimestre << ":"
       << fixed << setprecision(1) << nota.valor;
    return os;
}
