#include <iostream>
using namespace std;
int* crearArreglo(int n) {
    // Reservar memoria con new[]
    int* temp = new int[n]; 
    //  Llenar el arreglo con números pares (2, 4, 6, ...)
    for(int i = 0; i < n; i++) {
        temp[i] = (i + 1) * 2; 
    }
    // Retornar el puntero
    return temp; 
}
int main() {
    int n = 5; // Ejemplo con 5 numeros 

    // Llamar la función
    int* miArreglo = crearArreglo(n); 

    // Imprimir los elementos
    cout << "Arreglo de pares: ";
    for(int i = 0; i < n; i++) {
        cout << miArreglo[i] << " ";
    }
    cout << endl;

    // Liberar la memoria con delete[]
    delete[] miArreglo; 

    return 0;
}