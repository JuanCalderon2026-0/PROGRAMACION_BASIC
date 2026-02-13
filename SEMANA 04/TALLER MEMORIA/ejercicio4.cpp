#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cout << "Ingrese el tamaño n del arreglo: "; 
    cin >> n;
    // Sustituye a new int[n]
    vector<int> v(n); 
    // Llenar el vector
    for(int i = 0; i < n; i++) {
        cout << "Valor " << i+1 << ": "; 
        cin >> v[i];
    }
    // Mostrar el vector
    cout << "Contenido del vector: ";
    for(int i = 0; i < n; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    // NO se necesita delete. El vector libera la memoria solo no como en el new
    return 0;
}