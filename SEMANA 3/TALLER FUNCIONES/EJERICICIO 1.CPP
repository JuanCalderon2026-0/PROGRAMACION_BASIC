#include <iostream>
using namespace std;

// Función para determinar el mayor de dos números
int obtenerMayor(int n1, int n2) {
    if (n1 > n2) {
        return n1;
    } else {
        return n2;
    }
}

int main() {
    int num1, num2;
int mayor;
    cout << "Ingrese el primer numero: ";
    cin >> num1;
    cout << "Ingrese el segundo numero: ";
    cin >> num2;

    // se llama a la función y muestra de resultado
     mayor = obtenerMayor(num1, num2);
    cout << "El numero mayor es: " << mayor << endl;
    return 0;
}
