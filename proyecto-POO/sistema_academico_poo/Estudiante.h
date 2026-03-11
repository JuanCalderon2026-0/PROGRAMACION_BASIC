#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include "Persona.h"
#include "Curso.h"
#include "Nota.h"
#include "definiciones.h"
#include <vector>
using namespace std;

// ============================================================
//   CLASE: Estudiante — hereda de Persona
//
//   Relaciones:
//     - Hereda de Persona          (Herencia)
//     - TIENE-UN  Curso            (Composicion)
//     - TIENE-MUCHOS Nota          (Agregacion via vector)
//
//   Conceptos POO:
//     - Herencia y reutilizacion
//     - Sobreescritura (override) de mostrarInfo()
//     - Encapsulamiento (atributos privados)
//     - Relacion entre clases (usa / tiene)
//     - Constructores con parametros
// ============================================================
class Estudiante : public Persona {
private:
    int           grado;
    Curso         curso;           // Composicion: Estudiante TIENE-UN Curso
    vector<Nota>  notas;           // Agregacion: Estudiante TIENE-MUCHOS Nota
    string        fechaRegistro;
    bool          activo;

public:
    // Constructor por defecto
    Estudiante();

    // Constructor con parametros
    Estudiante(const string& codigo,
               const string& nombre,
               int grado,
               const Curso& curso,
               const string& fecha);

    // Destructor
    ~Estudiante() override;

    // Getters
    int           getGrado()         const;
    const Curso&  getCurso()         const;
    int           getCantidadNotas() const;
    const Nota&   getNota(int i)     const;
    string        getFechaRegistro() const;
    bool          isActivo()         const;

    // Setters
    void setGrado(int g);
    void setCurso(const Curso& c);
    void setActivo(bool a);

    // Gestion de notas
    void agregarNota(const Nota& nota);
    void limpiarNotas();

    // Calcula el promedio de todas las notas
    float calcularPromedio() const;

    // Sobreescritura del metodo virtual puro de Persona
    // Concepto: Polimorfismo en tiempo de ejecucion, override
    void mostrarInfo() const override;

    // Sobreescritura del tipo
    string getTipo() const override;
};

#endif
