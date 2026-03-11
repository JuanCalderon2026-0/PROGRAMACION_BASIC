#ifndef VALIDACION_H
#define VALIDACION_H

#include <string>
using namespace std;

// ============================================================
//   MODULO: Validacion de entradas del usuario
// ============================================================

bool esNombreValido(const string& s);
bool esSoloDigitos(const string& s);

int    leerEntero(const string& prompt, int minVal, int maxVal);
float  leerFloat (const string& prompt, float minVal, float maxVal);
string leerTexto (const string& prompt,
                  bool (*validar)(const string&),
                  const string& msgError);

#endif
