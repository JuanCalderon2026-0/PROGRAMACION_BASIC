#include <iostream>
using namespace std;
bool esOpcionValida(int opcion, int min, int max) {
    if (opcion >= min && opcion <= max) {
        return true;
    } else {
        return false;
    }
}
int main() {
    int op;
    cout << "--- MENU ---\n1. Agregar\n2. Listar\n3. Salir\nSeleccione: ";
    cin >> op;
    if (esOpcionValida(op, 1, 3)) {
        cout << "Accion permitida." << endl;
    } else {
        cout << "Error: Opcion fuera del rango permitido." << endl;
    }
    return 0;
}