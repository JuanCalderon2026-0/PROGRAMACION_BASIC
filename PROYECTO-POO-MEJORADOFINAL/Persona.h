#ifndef PERSONA_H
#define PERSONA_H

#include <string>
using namespace std;

// ============================================================
//   CLASE ABSTRACTA: Persona
//   Clase base que modela a cualquier persona del sistema.
//   Concepto POO: Abstraccion, Herencia, Clases abstractas,
//                 Metodos virtuales puros, Encapsulamiento
// ============================================================
class Persona {
protected:
    string codigo;
    string nombre;

public:
    // Constructor por defecto
    Persona();

    // Constructor con parametros
    Persona(const string& codigo, const string& nombre);

    // Destructor virtual (necesario para herencia correcta)
    virtual ~Persona();

    // Getters
    string getCodigo() const;
    string getNombre() const;

    // Setters
    void setCodigo(const string& c);
    void setNombre(const string& n);

    // Metodo virtual puro — obliga a las clases derivadas a implementarlo
    // Concepto: Polimorfismo, Metodos virtuales, Clases abstractas
    virtual void mostrarInfo() const = 0;

    // Metodo virtual con implementacion base (puede ser sobreescrito)
    virtual string getTipo() const;
};

#endif
