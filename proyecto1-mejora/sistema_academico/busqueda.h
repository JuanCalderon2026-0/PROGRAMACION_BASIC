#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include "definiciones.h"
#include <string>
#include <vector>
using namespace std;

// ============================================================
//   MODULO: Busqueda (retorna punteros a Estudiante)
// ============================================================

// Busca por codigo → devuelve puntero al Estudiante o nullptr
Estudiante* buscarPorCodigo(SistemaAcademico* sys, const string& codigo);

// Busca por nombre (coincidencia parcial) → devuelve puntero o nullptr
Estudiante* buscarPorNombre(SistemaAcademico* sys, const string& nombre);

// Busca TODOS los que coincidan con el nombre → devuelve vector de punteros
vector<Estudiante*> buscarTodos(SistemaAcademico* sys, const string& nombre);

// Verifica si el codigo ya existe
bool codigoExiste(const SistemaAcademico* sys, const string& codigo);

// Cuenta cuantos estudiantes tienen notas registradas
int contarConNotas(const SistemaAcademico* sys);

#endif
