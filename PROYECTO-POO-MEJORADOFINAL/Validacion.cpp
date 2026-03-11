#include "Validacion.h"
#include "definiciones.h"
#include <iostream>
#include <limits>
#include <cctype>
using namespace std;

bool Validacion::esNombreValido(const string& s) {
    if (s.empty()) return false;
    for (int i = 0; i < (int)s.length(); i++) {
        char c = s[i];
        if (!isalpha((unsigned char)c) && c != ' ')
            return false;
    }
    return true;
}

bool Validacion::esSoloDigitos(const string& s) {
    if (s.empty()) return false;
    for (int i = 0; i < (int)s.length(); i++) {
        if (!isdigit((unsigned char)s[i]))
            return false;
    }
    return true;
}

int Validacion::leerEntero(const string& prompt, int minVal, int maxVal) {
    int valor;
    while (true) {
        cout << prompt;
        cin >> valor;
        if (!cin.fail() && valor >= minVal && valor <= maxVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [X] Ingrese un numero entre " << minVal
             << " y " << maxVal << ".\n\n";
    }
}

float Validacion::leerFloat(const string& prompt, float minVal, float maxVal) {
    float valor;
    while (true) {
        cout << prompt;
        cin >> valor;
        if (!cin.fail() && valor >= minVal && valor <= maxVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [X] Ingrese un valor entre " << minVal
             << " y " << maxVal << ".\n\n";
    }
}

string Validacion::leerTexto(const string& prompt,
                              bool (*validar)(const string&),
                              const string& msgError) {
    string texto;
    while (true) {
        cout << prompt;
        getline(cin, texto);
        if (validar(texto)) return texto;
        cout << "  [X] " << msgError << "\n\n";
    }
}

// ============================================================
//   METODOS QUE LANZAN EXCEPCIONES (throw)
//
//   Concepto: en lugar de retornar true/false, estos metodos
//   lanzan (throw) una excepcion personalizada si la validacion
//   falla. El llamador debe envolverlos en try-catch.
//
//   Buena practica: separar la validacion formal (que lanza
//   excepciones) de la lectura interactiva (que reintenta).
// ============================================================

void Validacion::validarCodigo(const string& codigo) {
    // throw CodigoInvalidoException si el formato es incorrecto
    if ((int)codigo.length() != LONGITUD_CODIGO || !esSoloDigitos(codigo))
        throw CodigoInvalidoException(codigo);
}

void Validacion::validarNombre(const string& nombre) {
    // throw NombreInvalidoException si contiene caracteres invalidos
    if (!esNombreValido(nombre))
        throw NombreInvalidoException(nombre);
}

void Validacion::validarNota(float valor) {
    // throw NotaFueraDeRangoException si esta fuera de [0, 20]
    if (valor < MIN_NOTA || valor > MAX_NOTA)
        throw NotaFueraDeRangoException(valor);
}

void Validacion::validarGrado(int grado) {
    // throw GradoInvalidoException si no esta en [1, 5]
    if (grado < MIN_GRADO || grado > MAX_GRADO)
        throw GradoInvalidoException(grado);
}
