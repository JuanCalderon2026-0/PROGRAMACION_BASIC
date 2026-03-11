#ifndef CURSO_H
#define CURSO_H

#include <string>
using namespace std;

// ============================================================
//   CLASE: Curso
//   Encapsula la informacion de un curso y su profesor.
//   Concepto POO: Encapsulamiento, Constructores,
//                 Abstraccion (modelado de entidad real)
// ============================================================
class Curso {
private:
    string nombre;
    string profesor;

public:
    // Constructor por defecto
    Curso();

    // Constructor con parametros
    Curso(const string& nombre, const string& profesor);

    // Getters
    string getNombre()   const;
    string getProfesor() const;

    // Setters
    void setNombre(const string& n);
    void setProfesor(const string& p);
};

#endif
