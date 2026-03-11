#ifndef SISTEMA_ACADEMICO_H
#define SISTEMA_ACADEMICO_H

#include "IReporte.h"
#include "Estudiante.h"
#include <vector>
#include <string>
using namespace std;

// ============================================================
//   CLASE: SistemaAcademico — implementa IReporte
//
//   Hereda de la clase abstracta IReporte e implementa
//   todos sus metodos virtuales puros.
//
//   Conceptos POO:
//     - Herencia de clase abstracta (IReporte)
//     - Polimorfismo (implementa metodos virtuales)
//     - Encapsulamiento
//     - Relacion TIENE-MUCHOS Estudiante* (vector de punteros)
//     - Memoria dinamica con destructor
// ============================================================
class SistemaAcademico : public IReporte {
private:
    vector<Estudiante*> estudiantes;   // relacion: TIENE-MUCHOS Estudiante

public:
    // Constructor
    SistemaAcademico();

    // Destructor: libera todos los Estudiante* del vector
    ~SistemaAcademico() override;

    // ---- Gestion de estudiantes ----
    void        agregarEstudiante(Estudiante* est);
    bool        eliminarEstudiante(const string& codigo);
    bool        codigoExiste(const string& codigo) const;

    // ---- Busqueda ----
    Estudiante* buscarPorCodigo(const string& codigo) const;
    Estudiante* buscarPorNombre(const string& nombre) const;
    vector<Estudiante*> buscarTodos(const string& nombre) const;

    // ---- Acceso ----
    int         getCantidad()    const;
    Estudiante* getEstudiante(int i) const;

    // ---- Implementacion de IReporte (polimorfismo) ----
    void mostrarPromedios()    const override;
    void mostrarRanking()      const override;
    void mostrarEstadisticas() const override;

    // ---- Extra ----
    void mostrarFichas()       const;
    void mostrarEstadoMemoria() const;

    int  contarConNotas() const;
};

#endif
