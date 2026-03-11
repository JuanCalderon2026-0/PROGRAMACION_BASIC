#include "validacion.h"
#include <iostream>
#include <limits>
#include <cctype>
using namespace std;

// ============================================================
//   MODULO: Validacion
// ============================================================

bool esNombreValido(const string& s) {
    if (s.empty()) return false;
    for (int i = 0; i < (int)s.length(); i++) {
        char c = s[i];
        if (!isalpha((unsigned char)c) && c != ' ')
            return false;
    }
    return true;
}

bool esSoloDigitos(const string& s) {
    if (s.empty()) return false;
    for (int i = 0; i < (int)s.length(); i++) {
        if (!isdigit((unsigned char)s[i]))
            return false;
    }
    return true;
}

int leerEntero(const string& prompt, int minVal, int maxVal) {
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

float leerFloat(const string& prompt, float minVal, float maxVal) {
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

string leerTexto(const string& prompt,
                 bool (*validar)(const string&),
                 const string& msgError)
{
    string texto;
    while (true) {
        cout << prompt;
        getline(cin, texto);
        if (validar(texto)) return texto;
        cout << "  [X] " << msgError << "\n\n";
    }
}
