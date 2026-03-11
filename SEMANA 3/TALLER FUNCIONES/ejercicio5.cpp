#include <iostream>
using namespace std;

int obtenerMaximo(int arreglo[], int tamano) {
    int max = arreglo[0];
    for (int i = 1; i < tamano; i++) {
        if (arreglo[i] > max) {
            max = arreglo[i];
        }
    }
    return max;
}
int main() {
    int n;
    cout << "Ingrese el tamano del arreglo: ";
    cin >> n;
    int datos[n];

    for (int i = 0; i < n; i++) {
        cout << "Elemento " << i << ": ";
        cin >> datos[i];
    }
    cout << "El valor maximo es: " << obtenerMaximo(datos, n) << endl;
    return 0;
}
