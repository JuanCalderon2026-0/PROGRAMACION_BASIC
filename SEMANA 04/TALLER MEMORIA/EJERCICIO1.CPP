#include <iostream>
using namespace std;
int main() {
    int n;
    cout << "Ingrese el tamaño n del arreglo: "; cin >> n;
    int* arr = new int[n];

    float suma = 0;
    for(int i = 0; i < n; i++) {
        cout << "Valor " << i+1 << ": "; cin >> arr[i];
        suma += arr[i];

    }
    cout << "Arreglo: ";
    for(int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\nPromedio: " << (suma / n) << endl;
    delete[] arr;

    return 0;

} 
