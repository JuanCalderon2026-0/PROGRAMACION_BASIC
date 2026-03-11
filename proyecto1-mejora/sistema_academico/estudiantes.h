#ifndef ESTUDIANTES_H
#define ESTUDIANTES_H

#include "definiciones.h"

// ============================================================
//   MODULO: Gestion de Estudiantes (CRUD)
// ============================================================

void registrarEstudiante (SistemaAcademico* sys);
void mostrarEstudiantes  (const SistemaAcademico* sys);
void ingresarNotas       (SistemaAcademico* sys);
void editarEstudiante    (SistemaAcademico* sys);
void eliminarEstudiante  (SistemaAcademico* sys);

#endif
