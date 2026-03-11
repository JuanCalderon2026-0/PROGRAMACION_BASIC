#include "Curso.h"

// Constructor por defecto
Curso::Curso() : nombre(""), profesor("") {}

// Constructor con parametros
Curso::Curso(const string& n, const string& p) : nombre(n), profesor(p) {}

// Getters
string Curso::getNombre()   const { return nombre;   }
string Curso::getProfesor() const { return profesor;  }

// Setters
void Curso::setNombre(const string& n)   { nombre   = n; }
void Curso::setProfesor(const string& p) { profesor = p; }
