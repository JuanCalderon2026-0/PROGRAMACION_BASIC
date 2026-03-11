#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include "Persona.h"
#include "Curso.h"
#include "Nota.h"
#include "definiciones.h"
#include <vector>
#include <iostream>
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
//     - enum class EstadoAcademico como atributo de clase
//     - Sobrecarga de operadores (< para ranking, << para salida)
// ============================================================
class Estudiante : public Persona {
private:
    int           grado;
    Curso         curso;           // Composicion: Estudiante TIENE-UN Curso
    vector<Nota>  notas;           // Agregacion: Estudiante TIENE-MUCHOS Nota
    string        fechaRegistro;
    bool          activo;

    // ----------------------------------------------------------
    //   ATRIBUTO ENUM CLASS: estadoAcademico
    //   Concepto: enum class como atributo de una clase POO.
    //   El estado se recalcula automaticamente al pedir promedio.
    //   Uso de EstadoAcademico:: para acceder (ambito controlado).
    // ----------------------------------------------------------
    EstadoAcademico estadoAcademico;

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
    int              getGrado()           const;
    const Curso&     getCurso()           const;
    int              getCantidadNotas()   const;
    const Nota&      getNota(int i)       const;
    string           getFechaRegistro()   const;
    bool             isActivo()           const;

    // ----------------------------------------------------------
    //   Getter del enum class
    //   Concepto: exponer el estado calculado usando enum class
    //   con ambito propio (EstadoAcademico::APROBADO, etc.)
    // ----------------------------------------------------------
    EstadoAcademico  getEstadoAcademico() const;

    // Setters
    void setGrado(int g);
    void setCurso(const Curso& c);
    void setActivo(bool a);

    // Gestion de notas
    void agregarNota(const Nota& nota);
    void limpiarNotas();

    // Calcula el promedio y actualiza el estado academico (enum)
    float calcularPromedio() const;

    // ----------------------------------------------------------
    //   Metodo auxiliar: actualiza estadoAcademico segun promedio
    //   Concepto: enum class en control de flujo con if/else
    // ----------------------------------------------------------
    void actualizarEstado();

    // Sobreescritura del metodo virtual puro de Persona
    // Concepto: Polimorfismo en tiempo de ejecucion, override
    void mostrarInfo() const override;

    // Sobreescritura del tipo
    string getTipo() const override;

    // ----------------------------------------------------------
    //   SOBRECARGA DE OPERADOR <
    //   Concepto: operator overloading — compara dos Estudiante
    //   por su promedio. Permite ordenar estudiantes para ranking.
    // ----------------------------------------------------------
    bool operator<(const Estudiante& otro) const;

    // ----------------------------------------------------------
    //   SOBRECARGA DEL OPERADOR <<
    //   Concepto: friend function para salida formateada.
    //   Permite: cout << estudiante  (resumen en una linea)
    // ----------------------------------------------------------
    friend ostream& operator<<(ostream& os, const Estudiante& est);
};

#endif
