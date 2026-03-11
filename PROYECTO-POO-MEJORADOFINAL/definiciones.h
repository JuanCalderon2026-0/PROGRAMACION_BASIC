#ifndef DEFINICIONES_H
#define DEFINICIONES_H

// ============================================================
//   DEFINICIONES GLOBALES — Sistema Academico v3.0
//
//   Conceptos POO:
//     - enum class (tipado fuerte, ambito propio)
//     - enum tradicional para compatibilidad
//     - Constantes globales del sistema
// ============================================================

#include <string>
using namespace std;

// ============================================================
//   ENUM CLASS: EstadoAcademico
//   Representa el estado de un estudiante segun su promedio.
//
//   Concepto: enum class (C++11) — ambito controlado,
//             seguridad de tipos, evita colisiones de nombres.
//   Diferencia con enum tradicional:
//     - enum:       if (x == APROBADO)      <- sin ambito
//     - enum class: if (x == EstadoAcademico::APROBADO) <- con ambito
// ============================================================
enum class EstadoAcademico {
    APROBADO,       // Promedio >= 14.0
    RECUPERACION,   // Promedio entre 11.0 y 13.9
    DESAPROBADO,    // Promedio < 11.0
    SIN_NOTAS       // Sin notas registradas
};

// ============================================================
//   ENUM CLASS: MenuOpcion
//   Representa las opciones del menu principal.
//
//   Concepto: enum class con valores enteros asignados,
//             uso con switch para control de flujo.
//             Reemplaza constantes magicas (1, 2, 3...)
//             mejorando legibilidad y mantenimiento.
// ============================================================
enum class MenuOpcion {
    REGISTRAR        = 1,
    VER_FICHAS       = 2,
    INGRESAR_NOTAS   = 3,
    VER_PROMEDIOS    = 4,
    RANKING          = 5,
    EDITAR           = 6,
    ELIMINAR         = 7,
    ESTADISTICAS     = 8,
    BUSCAR           = 9,
    HISTORIAL        = 10,
    GUARDAR_SALIR    = 11
};

// ============================================================
//   ENUM: NivelError  (enum tradicional — sin ambito)
//   Concepto: Comparacion enum tradicional vs enum class.
//   El enum tradicional expone sus valores directamente
//   al espacio de nombres, lo que puede causar colisiones.
//   Se mantiene aqui como referencia didactica.
// ============================================================
enum NivelError {
    ERROR_LEVE    = 0,
    ERROR_MEDIO   = 1,
    ERROR_CRITICO = 2
};

// ---- Constantes del sistema ----
const int    LONGITUD_CODIGO = 5;
const int    MIN_GRADO       = 1;
const int    MAX_GRADO       = 5;
const int    MAX_NOTAS       = 4;
const float  MIN_NOTA        = 0.0f;
const float  MAX_NOTA        = 20.0f;
const int    TOTAL_CURSOS    = 8;
const string ARCHIVO_DATOS   = "datos.txt";

#endif
