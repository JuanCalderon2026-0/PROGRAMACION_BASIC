#include "Nota.h"

// Constructor por defecto
Nota::Nota() : bimestre(0), valor(0.0f) {}

// Constructor con parametros
Nota::Nota(int b, float v) : bimestre(b), valor(v) {}

// Getters
int   Nota::getBimestre() const { return bimestre; }
float Nota::getValor()    const { return valor;    }

// Setters
void Nota::setBimestre(int b)  { bimestre = b; }
void Nota::setValor(float v)   { valor    = v; }
