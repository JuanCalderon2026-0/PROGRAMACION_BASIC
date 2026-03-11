#ifndef VALIDACION_H
#define VALIDACION_H

#include <string>
using namespace std;

// ============================================================
//   CLASE: Validacion
//   Centraliza la validacion de entradas del usuario.
//   Concepto POO: Abstraccion, Clases con metodos estaticos
// ============================================================
class Validacion {
public:
    static bool   esNombreValido(const string& s);
    static bool   esSoloDigitos(const string& s);
    static int    leerEntero(const string& prompt, int minVal, int maxVal);
    static float  leerFloat (const string& prompt, float minVal, float maxVal);
    static string leerTexto (const string& prompt,
                             bool (*validar)(const string&),
                             const string& msgError);
};

#endif
