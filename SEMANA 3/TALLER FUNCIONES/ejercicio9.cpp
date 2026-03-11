#include <iostream>
using namespace std;
bool buscarValor(int arreglo[], int tamano, int buscado) {
    for (int i = 0; i < tamano; i++) {
        if (arreglo[i] == buscado) {
            return true;
        }
    }
    return false;
}

int main() {
    int datos[] = {10, 25, 30, 45, 50};
    int valor;

    cout << "Valor a buscar en el sistema: ";
    cin >> valor;

    if (buscarValor(datos, 5, valor)) {
        cout << "El valor existe en el arreglo." << endl;
    } else {
        cout << "El valor no fue encontrado." << endl;
    }
    return 0;
}