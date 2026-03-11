#include "Estudiante.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================
//   IMPLEMENTACION: Estudiante
// ============================================================

// Constructor por defecto
Estudiante::Estudiante()
    : Persona(), grado(0), activo(true),
      estadoAcademico(EstadoAcademico::SIN_NOTAS) {}

// Constructor con parametros
// Llama al constructor de la clase base Persona (herencia)
Estudiante::Estudiante(const string& cod,
                       const string& nom,
                       int gr,
                       const Curso& cur,
                       const string& fecha)
    : Persona(cod, nom), grado(gr), curso(cur),
      fechaRegistro(fecha), activo(true),
      estadoAcademico(EstadoAcademico::SIN_NOTAS) {}

// Destructor
Estudiante::~Estudiante() {}

// ---- Getters ----
int          Estudiante::getGrado()         const { return grado;   }
const Curso& Estudiante::getCurso()         const { return curso;   }
int          Estudiante::getCantidadNotas() const { return (int)notas.size(); }
string       Estudiante::getFechaRegistro() const { return fechaRegistro; }
bool         Estudiante::isActivo()         const { return activo;  }

const Nota& Estudiante::getNota(int i) const {
    return notas[i];
}

// ---- Getter del enum class ----
EstadoAcademico Estudiante::getEstadoAcademico() const {
    return estadoAcademico;
}

// ---- Setters ----
void Estudiante::setGrado(int g)         { grado  = g; }
void Estudiante::setCurso(const Curso& c){ curso  = c; }
void Estudiante::setActivo(bool a)       { activo = a; }

// ---- Gestion de notas ----
void Estudiante::agregarNota(const Nota& nota) {
    notas.push_back(nota);
    actualizarEstado();  // Recalcular estado al agregar nota
}

void Estudiante::limpiarNotas() {
    notas.clear();
    estadoAcademico = EstadoAcademico::SIN_NOTAS;
}

// ---- Calcula promedio ----
float Estudiante::calcularPromedio() const {
    if (notas.empty()) return 0.0f;
    float suma = 0.0f;
    for (int i = 0; i < (int)notas.size(); i++)
        suma += notas[i].getValor();
    return suma / (float)notas.size();
}

// ============================================================
//   ENUM CLASS en logica de negocio
//   Concepto: uso de enum class con if/else para clasificar
//   el estado academico del estudiante.
//   EstadoAcademico:: es el ambito del enum class.
// ============================================================
void Estudiante::actualizarEstado() {
    if (notas.empty()) {
        estadoAcademico = EstadoAcademico::SIN_NOTAS;
        return;
    }
    float prom = calcularPromedio();
    if      (prom >= 14.0f) estadoAcademico = EstadoAcademico::APROBADO;
    else if (prom >= 11.0f) estadoAcademico = EstadoAcademico::RECUPERACION;
    else                    estadoAcademico = EstadoAcademico::DESAPROBADO;
}

// ---- Sobreescritura de mostrarInfo (polimorfismo) ----
void Estudiante::mostrarInfo() const {
    cout << "  Codigo    : " << getCodigo()             << "\n";
    cout << "  Nombre    : " << getNombre()             << "\n";
    cout << "  Grado     : " << grado                   << " de Secundaria\n";
    cout << "  Curso     : " << curso.getNombre()       << "\n";
    cout << "  Profesor  : " << curso.getProfesor()     << "\n";
    cout << "  Registrado: " << fechaRegistro           << "\n";

    if (!notas.empty()) {
        cout << "  Notas     : ";
        for (int j = 0; j < (int)notas.size(); j++) {
            // Uso del operador << sobrecargado de Nota
            cout << notas[j];
            if (j < (int)notas.size() - 1) cout << "  |  ";
        }
        float prom = calcularPromedio();
        string estado = (prom >= 14.0f) ? "[APROBADO]" :
                        (prom >= 11.0f) ? "[RECUPERACION]" : "[DESAPROBADO]";
        cout << "\n  Promedio  : " << fixed << setprecision(2)
             << prom << "  " << estado << "\n";
    } else {
        cout << "  Notas     : Sin notas registradas.\n";
    }
}

// ---- Tipo ----
string Estudiante::getTipo() const { return "Estudiante"; }

// ============================================================
//   SOBRECARGA DE OPERADORES
// ============================================================

// Operador < : compara estudiantes por promedio (para ranking)
// Concepto: operator overloading — permite ordenar estudiantes
bool Estudiante::operator<(const Estudiante& otro) const {
    return this->calcularPromedio() < otro.calcularPromedio();
}

// Operador << : imprime resumen del estudiante en una linea
// Concepto: friend function + operator overloading para salida
ostream& operator<<(ostream& os, const Estudiante& est) {
    os << est.getCodigo()
       << " | " << setw(24) << left << est.getNombre()
       << " | Grado " << est.grado
       << " | " << est.curso.getNombre();
    return os;
}
