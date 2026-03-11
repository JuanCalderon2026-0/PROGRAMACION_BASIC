#ifndef NOTA_H
#define NOTA_H

// ============================================================
//   CLASE: Nota
//   Encapsula la informacion de una nota bimestral.
//   Concepto POO aplicado: Encapsulamiento, Constructores
// ============================================================
class Nota {
private:
    int   bimestre;   // 1 al 4
    float valor;      // 0.0 a 20.0

public:
    // Constructor por defecto
    Nota();

    // Constructor con parametros
    Nota(int bimestre, float valor);

    // Getters
    int   getBimestre() const;
    float getValor()    const;

    // Setters
    void setBimestre(int b);
    void setValor(float v);
};

#endif
