#include "Historial.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Funcion auxiliar (declarada aqui para no depender de utilidades)
static void lineaH(char c = '=', int n = 62) {
    for (int i = 0; i < n; i++) cout << c;
}

Historial::Historial() {}

void Historial::agregar(const string& accion) {
    registros.push_back(accion);
}

void Historial::mostrar() const {
    lineaH('=');
    cout << "\n  HISTORIAL DE OPERACIONES\n";
    lineaH('=');
    cout << "\n";

    if (registros.empty()) {
        cout << "  [!] No hay operaciones registradas aun.\n";
        return;
    }

    cout << "  Total de operaciones: " << registros.size() << "\n\n";
    lineaH('-');
    cout << "\n";

    for (int i = 0; i < (int)registros.size(); i++) {
        cout << "  " << setw(3) << right << (i + 1) << ".  "
             << registros[i] << "\n";
    }

    cout << "\n";
    lineaH('=');
    cout << "\n";
}

void Historial::limpiar() {
    registros.clear();
    cout << "\n  [OK] Historial limpiado.\n";
}

int  Historial::getCantidad() const { return (int)registros.size(); }
bool Historial::estaVacio()   const { return registros.empty();     }
