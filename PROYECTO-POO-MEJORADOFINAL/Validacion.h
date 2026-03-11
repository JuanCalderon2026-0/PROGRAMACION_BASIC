#ifndef VALIDACION_H
#define VALIDACION_H

#include <string>
#include "Excepciones.h"
using namespace std;

// ============================================================
//   CLASE: Validacion
//   Valida entradas del usuario y lanza excepciones si son invalidas.
//
//   Conceptos POO (nuevos):
//     - Uso de throw para lanzar excepciones personalizadas
//     - try-catch en los metodos de lectura
//     - Buenas practicas: separar validacion de la UI
// ============================================================
class Validacion {
public:
    // Valida que un nombre contenga solo letras y espacios
    static bool esNombreValido(const string& s);

    // Valida que una cadena contenga solo digitos
    static bool esSoloDigitos(const string& s);

    // Lee un entero con validacion de rango
    static int   leerEntero(const string& prompt, int minVal, int maxVal);

    // Lee un float con validacion de rango
    static float leerFloat(const string& prompt, float minVal, float maxVal);

    // Lee un texto con funcion de validacion personalizada
    static string leerTexto(const string& prompt,
                             bool (*validar)(const string&),
                             const string& msgError);

    // ----------------------------------------------------------
    //   Metodos que lanzan excepciones (throw)
    //   Concepto: uso de throw para senalar errores formalmente
    //   en lugar de retornar booleanos o codigos de error.
    //   El llamador debe usar try-catch para manejarlas.
    // ----------------------------------------------------------
    static void validarCodigo(const string& codigo);
    static void validarNombre(const string& nombre);
    static void validarNota(float valor);
    static void validarGrado(int grado);
};

#endif
