#include "Estudiante.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================
//   IMPLEMENTACION: Estudiante
// ============================================================

// Constructor por defecto
Estudiante::Estudiante()
    : Persona(), grado(0), activo(true) {}

// Constructor con parametros
// Llama al constructor de la clase base Persona (herencia)
Estudiante::Estudiante(const string& cod,
                       const string& nom,
                       int gr,
                       const Curso& cur,
                       const string& fecha)
    : Persona(cod, nom), grado(gr), curso(cur),
      fechaRegistro(fecha), activo(true) {}

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

// ---- Setters ----
void Estudiante::setGrado(int g)         { grado  = g; }
void Estudiante::setCurso(const Curso& c){ curso  = c; }
void Estudiante::setActivo(bool a)       { activo = a; }

// ---- Gestion de notas ----
void Estudiante::agregarNota(const Nota& nota) {
    notas.push_back(nota);
}

void Estudiante::limpiarNotas() {
    notas.clear();
}

// ---- Calcula promedio ----
float Estudiante::calcularPromedio() const {
    if (notas.empty()) return 0.0f;
    float suma = 0.0f;
    for (int i = 0; i < (int)notas.size(); i++)
        suma += notas[i].getValor();
    return suma / (float)notas.size();
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
            cout << "B" << notas[j].getBimestre() << ":"
                 << fixed << setprecision(1) << notas[j].getValor();
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
