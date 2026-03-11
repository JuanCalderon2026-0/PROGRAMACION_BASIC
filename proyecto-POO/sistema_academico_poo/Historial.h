#ifndef HISTORIAL_H
#define HISTORIAL_H

#include <string>
#include <vector>
using namespace std;

// ============================================================
//   CLASE: Historial
//   Registra cada operacion del usuario usando vector<string>.
//   Concepto POO: Encapsulamiento, Clases y objetos
// ============================================================
class Historial {
private:
    vector<string> registros;   // vector de strings

public:
    Historial();

    void agregar(const string& accion);
    void mostrar() const;
    void limpiar();

    int  getCantidad() const;
    bool estaVacio()   const;
};

#endif
