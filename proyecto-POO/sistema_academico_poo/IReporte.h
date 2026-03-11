#ifndef IREPORTE_H
#define IREPORTE_H

// ============================================================
//   CLASE ABSTRACTA: IReporte
//   Simula una interfaz de reportes (patron Interface en C++).
//   Concepto POO: Clases abstractas, metodos virtuales puros,
//                 Interfaces en C++, Polimorfismo
// ============================================================
class IReporte {
public:
    virtual ~IReporte() {}

    // Metodos puramente virtuales — deben implementarse en clases derivadas
    virtual void mostrarPromedios()    const = 0;
    virtual void mostrarRanking()      const = 0;
    virtual void mostrarEstadisticas() const = 0;
};

#endif
