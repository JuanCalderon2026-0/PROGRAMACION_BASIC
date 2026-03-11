#include <iostream>
using namespace std;

bool estaOrdenado(int arreglo[], int tamano) {
    for (int i = 0; i < tamano - 1; i++) {
        if (arreglo[i] > arreglo[i+1]) {
            return false;
        }
    }
    return true;
}
int main() {
    int n;
    cout << "Cantidad de elementos: ";
    cin >> n;
    int lista[n];
    for (int i = 0; i < n; i++) {
        cout << "Valor " << i << ": ";
        cin >> lista[i];
    }
    if (estaOrdenado(lista, n)) {
        cout << "El arreglo esta ordenado de forma ascendente." << endl;
    } else {
        cout << "El arreglo no esta ordenado." << endl;
    }
    return 0;
}