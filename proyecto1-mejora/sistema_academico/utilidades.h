#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "definiciones.h"
#include <string>
using namespace std;

// ============================================================
//   MODULO: Utilidades (fecha, calculo, tabla de cursos)
// ============================================================

// Tabla de cursos disponibles (definida en utilidades.cpp)
extern Curso tablaCursos[];
extern const int TOTAL_CURSOS;

string  obtenerFechaHora();
string  obtenerFraseAleatoria();
string  generarCodigoAleatorio();

// Calcula promedio usando puntero a array de Nota
float   calcularPromedio(const Nota* notas, int cantidad);
string  etiquetaEstado(float promedio);

void    mostrarMenuCursos();

#endif
