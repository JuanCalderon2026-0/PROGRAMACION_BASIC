#ifndef SISTEMAACADEMICO_H
#define SISTEMAACADEMICO_H

#include "Estudiante.h"
#include "IReporte.h"
#include "Excepciones.h"
#include <vector>
using namespace std;

// ============================================================
//   CLASE: SistemaAcademico
//   Implementa IReporte (interfaz abstracta pura)
//
//   Conceptos POO:
//     - Implementacion de interfaz (IReporte)
//     - Uso de excepciones: buscarPorCodigoSeguro lanza excepcion
//     - Polimorfismo via puntero IReporte*
// ============================================================
class SistemaAcademico : public IReporte {
private:
    vector<Estudiante*> estudiantes;

    int contarConNotas() const;

public:
    SistemaAcademico();
    ~SistemaAcademico();

    // Gestion
    void        agregarEstudiante(Estudiante* est);
    bool        eliminarEstudiante(const string& codigo);
    bool        codigoExiste(const string& codigo) const;

    // Busqueda tradicional (retorna nullptr si no encuentra)
    Estudiante* buscarPorCodigo(const string& codigo) const;
    Estudiante* buscarPorNombre(const string& nombre) const;

    // ----------------------------------------------------------
    //   Busqueda con excepcion (throw)
    //   Concepto: en lugar de retornar nullptr, lanza
    //   EstudianteNoEncontradoException — el llamador usa try-catch
    // ----------------------------------------------------------
    Estudiante* buscarPorCodigoSeguro(const string& codigo) const;

    // Busqueda multiple
    vector<Estudiante*> buscarTodos(const string& nombre) const;

    // Acceso
    int         getCantidad()    const;
    Estudiante* getEstudiante(int i) const;

    // Implementaciones de IReporte (interfaz abstracta pura)
    // Concepto: Polimorfismo — estas funciones se llaman via IReporte*
    void mostrarFichas()      const override;
    void mostrarPromedios()   const override;
    void mostrarRanking()     const override;
    void mostrarEstadisticas() const override;

    void mostrarEstadoMemoria() const;
};

#endif
