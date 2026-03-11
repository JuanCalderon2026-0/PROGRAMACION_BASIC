#ifndef GESTORESTUDIANTES_H
#define GESTORESTUDIANTES_H

#include "SistemaAcademico.h"
#include "Historial.h"

// ============================================================
//   CLASE: GestorEstudiantes
//   Maneja las operaciones CRUD sobre estudiantes.
//
//   Conceptos POO (nuevos):
//     - Uso de try-catch para capturar excepciones personalizadas
//     - Manejo diferenciado con multiples catch
//     - Flujo seguro: operaciones criticas protegidas
// ============================================================
class GestorEstudiantes {
private:
    SistemaAcademico& sistema;
    Historial&        historial;

public:
    GestorEstudiantes(SistemaAcademico& sis, Historial& hist);

    void registrar();
    void mostrarFichas() const;
    void ingresarNotas();
    void editar();
    void eliminar();
    void buscarPorNombre() const;
};

#endif
