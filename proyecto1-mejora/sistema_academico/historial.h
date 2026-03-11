#ifndef HISTORIAL_H
#define HISTORIAL_H

#include <string>
#include <vector>
using namespace std;

// ============================================================
//   MODULO: Historial de operaciones
//   Usa vector<string> para registrar cada accion del usuario
// ============================================================

struct Historial {
    vector<string> registros;   // << vector de strings >>
};

void historialAgregar  (Historial* h, const string& accion);
void historialMostrar  (const Historial* h);
void historialLimpiar  (Historial* h);

#endif
