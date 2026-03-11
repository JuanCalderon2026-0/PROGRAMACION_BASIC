#include <iostream>
using namespace std;

int sumarArreglo(int arr[], int tam) {
    int suma = 0; // Acumulador
    for(int i = 0; i < tam; i++) {
        suma += arr[i];
    }
    return suma;
}

int main() {
    int n;
    cout << "Cuantos elementos tiene el arreglo? ";
    cin >> n;
    int datos[n];

    for(int i = 0; i < n; i++) {
        cout << "Ingrese valor " << i + 1 << ": ";
        cin >> datos[i];
    }

    cout << "La suma total es: " << sumarArreglo(datos, n) << endl;
    return 0;
}
