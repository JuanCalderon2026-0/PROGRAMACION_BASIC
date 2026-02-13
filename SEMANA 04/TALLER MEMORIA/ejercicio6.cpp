#include <iostream>
using namespace std;

int main() {
    int capacidad = 2;
    int tamano = 0;
    int* arr = new int[capacidad];
    int num;
    cout << "Ingrese numeros (-1 para terminar):" << endl;
    while (cin >> num && num != -1) {
        if (tamano == capacidad) {
            capacidad *= 2; 
            int* nuevoArr = new int[capacidad];
            for (int i = 0; i < tamano; i++) {
                nuevoArr[i] = arr[i];
            }
            delete[] arr;
            arr = nuevoArr;
            cout << " Capacidad aumentada a: " << capacidad << endl;
        }
        arr[tamano] = num;
        tamano++;
    }
    cout <<"Numeros guardados: ";
    for (int i = 0; i < tamano; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    delete[] arr; 
    return 0;
}
