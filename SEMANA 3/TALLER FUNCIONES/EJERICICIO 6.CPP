#include <iostream>
using namespace std;

int obtenerMinimo(int arreglo[], int tamano) {
    int min = arreglo[0];
    for (int i = 1; i < tamano; i++) {
        if (arreglo[i] < min) {
            min = arreglo[i]; 
        }
    }
    return min;
}
int main() {
    int n;
    cout << "Cantidad de datos: ";
    cin >> n;
    int datos[n];
    for (int i = 0; i < n; i++) {
        cout << "Valor " << i << ": ";
        cin >> datos[i];
    }
    cout << "El valor minimo es: " << obtenerMinimo(datos, n) << endl;
    return 0;
}
