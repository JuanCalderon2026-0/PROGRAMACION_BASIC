#ifndef MEMORIA_H
#define MEMORIA_H

#include "definiciones.h"

// ============================================================
//   MODULO: Memoria Dinamica
//   Gestiona toda la creacion, expansion y liberacion
//   de memoria del sistema.
//
//   Estructura en memoria:
//
//   SistemaAcademico
//     └── lista  →  [ Estudiante* | Estudiante* | Estudiante* | ... ]
//                        │               │
//                        ▼               ▼
//                    Estudiante      Estudiante
//                      └── notas*     └── notas*
//                           │               │
//                           ▼               ▼
//                       [Nota][Nota]    [Nota][Nota][Nota]
//
// ============================================================

// Inicializa el sistema con capacidad inicial y lista dinamica
void inicializarSistema(SistemaAcademico* sys);

// Libera TODA la memoria del sistema (lista + cada estudiante + sus notas)
void liberarSistema(SistemaAcademico* sys);

// Crea un Estudiante en el heap con notas inicialmente vacias
Estudiante* crearEstudiante();

// Libera la memoria de un Estudiante (incluyendo su arreglo de notas)
void liberarEstudiante(Estudiante* est);

// Agrega un estudiante al sistema, expandiendo la lista si es necesario
void agregarEstudiante(SistemaAcademico* sys, Estudiante* est);

// Asigna o re-asigna el arreglo de notas de un estudiante
void redimensionarNotas(Estudiante* est, int nuevaCantidad);

// Muestra el estado actual del heap (para depuracion)
void mostrarEstadoMemoria(const SistemaAcademico* sys);

#endif
