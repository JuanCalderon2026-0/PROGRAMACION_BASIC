#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "SistemaAcademico.h"

// ============================================================
//   CLASE: Archivos
//   Gestiona la persistencia de datos en disco.
//   Concepto POO: Abstraccion, Clases con metodos estaticos
// ============================================================
class Archivos {
public:
    static void guardarDatos(const SistemaAcademico& sys);
    static void cargarDatos (SistemaAcademico& sys);
};

#endif
