#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "Curso.h"
#include <string>
using namespace std;

// ============================================================
//   CLASE: Utilidades
//   Agrupa funciones de apoyo como metodos estaticos.
//   Concepto POO: Abstraccion, Clases con metodos estaticos
// ============================================================

// Tabla de cursos disponibles (definida en Utilidades.cpp)
extern Curso tablaCursos[];
extern const int TOTAL_CURSOS;

class Utilidades {
public:
    static string obtenerFechaHora();
    static string obtenerFraseAleatoria();
    static string generarCodigoAleatorio();
    static string etiquetaEstado(float promedio);
    static void   mostrarMenuCursos();
};

#endif
