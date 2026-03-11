#include "busqueda.h"
#include <cctype>
#include <vector>
using namespace std;

// ============================================================
//   MODULO: Busqueda
// ============================================================

// ------------------------------------------------------------------
// Recorre la lista con ARITMETICA DE PUNTEROS y devuelve el puntero
// al Estudiante que tiene el codigo buscado.
// Retorna nullptr si no lo encuentra.
// ------------------------------------------------------------------
Estudiante* buscarPorCodigo(SistemaAcademico* sys, const string& codigo) {
    Estudiante** ptr = sys->lista;      // puntero a puntero
    for (int i = 0; i < sys->cantidad; i++, ptr++) {
        if (*ptr != nullptr && (*ptr)->activo && (*ptr)->codigo == codigo)
            return *ptr;               // devuelve puntero al Estudiante
    }
    return nullptr;
}

// ------------------------------------------------------------------
// Busca por nombre (coincidencia parcial, ignorando mayusculas)
// ------------------------------------------------------------------
Estudiante* buscarPorNombre(SistemaAcademico* sys, const string& nombre) {
    string busq = nombre;
    for (int i = 0; i < (int)busq.size(); i++)
        busq[i] = tolower((unsigned char)busq[i]);

    Estudiante** ptr = sys->lista;
    for (int i = 0; i < sys->cantidad; i++, ptr++) {
        if (*ptr == nullptr || !(*ptr)->activo) continue;

        string nom = (*ptr)->nombre;
        for (int j = 0; j < (int)nom.size(); j++)
            nom[j] = tolower((unsigned char)nom[j]);

        if (nom.find(busq) != string::npos)
            return *ptr;
    }
    return nullptr;
}

// ------------------------------------------------------------------
// Verifica si ya existe un codigo en el sistema
// ------------------------------------------------------------------
bool codigoExiste(const SistemaAcademico* sys, const string& codigo) {
    Estudiante* const* ptr = sys->lista;
    for (int i = 0; i < sys->cantidad; i++, ptr++) {
        if (*ptr != nullptr && (*ptr)->activo && (*ptr)->codigo == codigo)
            return true;
    }
    return false;
}

// ------------------------------------------------------------------
// Busca TODOS los estudiantes cuyo nombre contenga el texto buscado
// Devuelve un vector<Estudiante*> con todos los coincidentes
// ------------------------------------------------------------------
vector<Estudiante*> buscarTodos(SistemaAcademico* sys, const string& nombre) {
    vector<Estudiante*> resultados;    // << vector de punteros >>

    string busq = nombre;
    for (int i = 0; i < (int)busq.size(); i++)
        busq[i] = tolower((unsigned char)busq[i]);

    Estudiante** ptr = sys->lista;
    for (int i = 0; i < sys->cantidad; i++, ptr++) {
        if (*ptr == nullptr || !(*ptr)->activo) continue;

        string nom = (*ptr)->nombre;
        for (int j = 0; j < (int)nom.size(); j++)
            nom[j] = tolower((unsigned char)nom[j]);

        if (nom.find(busq) != string::npos)
            resultados.push_back(*ptr);  // << push_back al vector >>
    }

    return resultados;                 // << retorna el vector >>
}

// ------------------------------------------------------------------
// Cuenta estudiantes activos con al menos una nota
// ------------------------------------------------------------------
int contarConNotas(const SistemaAcademico* sys) {
    int cont = 0;
    Estudiante* const* ptr = sys->lista;
    for (int i = 0; i < sys->cantidad; i++, ptr++) {
        if (*ptr != nullptr && (*ptr)->activo && (*ptr)->cantidadNotas > 0)
            cont++;
    }
    return cont;
}
