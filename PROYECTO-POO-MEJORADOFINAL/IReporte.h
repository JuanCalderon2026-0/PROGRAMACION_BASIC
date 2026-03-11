#ifndef IREPORTE_H
#define IREPORTE_H

// ============================================================
//   INTERFAZ: IReporte
//
//   En C++ no existe la palabra clave "interface" como en Java.
//   Se simula con una clase abstracta pura: todos sus metodos
//   son virtuales puros (= 0) y no tiene atributos de datos.
//
//   Concepto POO:
//     - Interfaz abstracta pura (todos los metodos = 0)
//     - Polimorfismo via puntero IReporte*
//     - Separacion de contrato (que hace) vs implementacion (como)
//     - SistemaAcademico implementa esta interfaz (herencia publica)
// ============================================================
class IReporte {
public:
    virtual ~IReporte() {}

    // Contrato: cualquier clase que implemente IReporte
    // DEBE definir estos cuatro metodos.
    virtual void mostrarFichas()       const = 0;
    virtual void mostrarPromedios()    const = 0;
    virtual void mostrarRanking()      const = 0;
    virtual void mostrarEstadisticas() const = 0;
};

#endif
