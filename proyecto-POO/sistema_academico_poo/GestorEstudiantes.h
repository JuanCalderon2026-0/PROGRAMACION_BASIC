#ifndef GESTOR_ESTUDIANTES_H
#define GESTOR_ESTUDIANTES_H

#include "SistemaAcademico.h"
#include "Historial.h"

// ============================================================
//   CLASE: GestorEstudiantes
//   Coordina las operaciones CRUD sobre el sistema.
//   Concepto POO: Relacion entre clases (USA-UN SistemaAcademico),
//                 Encapsulamiento, Abstraccion
// ============================================================
class GestorEstudiantes {
private:
    SistemaAcademico& sistema;   // referencia: USA-UN SistemaAcademico
    Historial&        historial; // referencia: USA-UN Historial

public:
    // Constructor con referencias
    GestorEstudiantes(SistemaAcademico& sis, Historial& hist);

    void registrar();
    void mostrarFichas() const;
    void ingresarNotas();
    void editar();
    void eliminar();
    void buscarPorNombre() const;
};

#endif
