#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "Ingresa dos numeros: ";
    cin >> a >> b;

    if (a > b)
        cout << a << " es mayor";
    else if (b > a)
        cout << b << " es mayor";
    else
        cout << "Son iguales";

    return 0;
}
