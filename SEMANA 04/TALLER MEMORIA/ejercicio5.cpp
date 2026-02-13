#include <iostream>
#include <vector>
using namespace std;
int main() {
    int f, c;
    cout << "Filas: "; cin >> f;
    cout << "Columnas: "; cin >> c;
    vector<vector<int> > matriz(f, vector<int>(c)); 

    // aca se llena la matriz
    for(int i = 0; i < f; i++) {
        for(int j = 0; j < c; j++) {
            cout << "Dato [" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
        }
    }

    // Imprimir y Reto Extra
    cout << "TABLA RESULTANTE:" << endl;
    for(int i = 0; i < f; i++) {
        int sumaFila = 0;
        for(int j = 0; j < c; j++) {
            cout << matriz[i][j] << "\t";
            sumaFila += matriz[i][j];
        }
        cout << "| Suma Fila: " << sumaFila << endl;
    }

    return 0;
}
