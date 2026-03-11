#ifndef NOTA_H
#define NOTA_H

#include <iostream>
using namespace std;

// ============================================================
//   CLASE: Nota
//
//   Conceptos POO nuevos:
//     - Sobrecarga de operadores aritmeticos (+)
//     - Sobrecarga de operadores relacionales (==, <)
//     - Sobrecarga del operador de salida (<<)
//   Permite operar con objetos Nota de forma natural:
//       Nota a + Nota b  =>  nueva Nota con valor sumado
//       Nota a < Nota b  =>  comparacion por valor
//       cout << nota     =>  salida formateada
// ============================================================
class Nota {
private:
    int   bimestre;
    float valor;

public:
    // Constructores
    Nota();
    Nota(int bimestre, float valor);

    // Getters
    int   getBimestre() const;
    float getValor()    const;

    // Setters
    void setBimestre(int b);
    void setValor(float v);

    // --------------------------------------------------------
    //   SOBRECARGA DE OPERADORES ARITMETICOS
    //   Concepto: operator overloading — permite usar + con objetos
    //   Caso de uso: sumar dos notas para obtener el total
    // --------------------------------------------------------
    Nota operator+(const Nota& otra) const;

    // --------------------------------------------------------
    //   SOBRECARGA DE OPERADORES RELACIONALES
    //   Concepto: comparar objetos con < y ==
    //   Caso de uso: ordenar notas, verificar igualdad
    // --------------------------------------------------------
    bool operator<(const Nota& otra)  const;
    bool operator==(const Nota& otra) const;
    bool operator>(const Nota& otra)  const;

    // --------------------------------------------------------
    //   SOBRECARGA DEL OPERADOR DE SALIDA <<
    //   Concepto: friend function para acceder a atributos privados
    //   Caso de uso: cout << nota  imprime la nota formateada
    // --------------------------------------------------------
    friend ostream& operator<<(ostream& os, const Nota& nota);
};

#endif
