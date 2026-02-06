#include <iostream>
using namespace std;

float calcularPromedio(float notas[], int cantidad) {
    float suma = 0;
    for (int i = 0; i < cantidad; i++) {
        suma += notas[i];
    }
    return suma / cantidad;
}

int main() {
    int numNotas;
    cout << "Ingrese la cantidad de notas: ";
    cin >> numNotas;

    float listaNotas[numNotas];
    for (int i = 0; i < numNotas; i++) {
        cout << "Nota " << i + 1 << ": ";
        cin >> listaNotas[i];
    }
    cout << "El promedio de las notas es: " << calcularPromedio(listaNotas, numNotas) << endl;

    return 0;
}