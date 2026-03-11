#include "historial.h"
#include "interfaz.h"
#include "utilidades.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ============================================================
//   MODULO: Historial de operaciones
// ============================================================

// Agrega un registro al vector con fecha y hora
void historialAgregar(Historial* h, const string& accion) {
    string entrada = "[" + obtenerFechaHora() + "]  " + accion;
    h->registros.push_back(entrada);   // << push_back al vector >>
}

// Muestra todos los registros del vector
void historialMostrar(const Historial* h) {
    linea('=');
    cout << "\n  HISTORIAL DE OPERACIONES\n";
    linea('=');
    cout << "\n";

    if (h->registros.empty()) {        // << .empty() del vector >>
        cout << "  [!] No hay operaciones registradas aun.\n";
        return;
    }

    cout << "  Total de operaciones: " << h->registros.size() << "\n\n";
    linea('-');
    cout << "\n";

    // Recorrer el vector con indice
    for (int i = 0; i < (int)h->registros.size(); i++) {
        cout << "  " << setw(3) << right << (i + 1) << ".  "
             << h->registros[i] << "\n";   // << acceso por indice >>
    }

    cout << "\n";
    linea('=');
    cout << "\n";
}

// Limpia todos los registros del vector
void historialLimpiar(Historial* h) {
    h->registros.clear();              // << .clear() del vector >>
    cout << "\n  [OK] Historial limpiado.\n";
}
