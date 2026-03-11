#ifndef DEFINICIONES_H
#define DEFINICIONES_H

#include <string>
using namespace std;

// ============================================================
//   CONSTANTES DEL SISTEMA
// ============================================================
const int   CAP_INICIAL    = 5;     // capacidad inicial (crece dinamicamente)
const int   MAX_NOTAS      = 4;     // maximo de notas por bimestre
const int   MIN_GRADO      = 1;
const int   MAX_GRADO      = 5;
const float MIN_NOTA       = 0.0f;
const float MAX_NOTA       = 20.0f;
const int   LONGITUD_CODIGO = 5;
const string ARCHIVO_DATOS = "datos.txt";

// ============================================================
//   STRUCT: Nota individual (bimestral)
// ============================================================
struct Nota {
    int   bimestre;   // 1 al 4
    float valor;      // 0.0 a 20.0
};

// ============================================================
//   STRUCT: Informacion de un curso
// ============================================================
struct Curso {
    string nombre;
    string profesor;
};

// ============================================================
//   STRUCT: Datos completos de un Estudiante
//   Las notas son un arreglo DINAMICO (puntero)
// ============================================================
struct Estudiante {
    string codigo;
    string nombre;
    int    grado;
    Curso  curso;             // struct anidado

    Nota*  notas;             // << puntero dinamico >>
    int    cantidadNotas;     // cuantas notas tiene actualmente
    int    capacidadNotas;    // cuantas puede guardar sin realocar

    string fechaRegistro;
    bool   activo;
};

// ============================================================
//   STRUCT: Contenedor principal del sistema
//   lista es un arreglo DINAMICO de punteros a Estudiante
// ============================================================
struct SistemaAcademico {
    Estudiante** lista;    // << puntero a punteros >> (arreglo dinamico)
    int          cantidad;
    int          capacidad;
};

#endif
