#include "Persona.h"

// Constructor por defecto
Persona::Persona() : codigo(""), nombre("") {}

// Constructor con parametros
Persona::Persona(const string& c, const string& n) : codigo(c), nombre(n) {}

// Destructor virtual
Persona::~Persona() {}

// Getters
string Persona::getCodigo() const { return codigo; }
string Persona::getNombre() const { return nombre; }

// Setters
void Persona::setCodigo(const string& c) { codigo = c; }
void Persona::setNombre(const string& n) { nombre = n; }

// Implementacion base de getTipo
string Persona::getTipo() const { return "Persona"; }
