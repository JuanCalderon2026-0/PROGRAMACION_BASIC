#include <iostream>
using namespace std;
int main() {
    float gastos[7];
    float total = 0, promedio;
    int mayores = 0;
cout<<"indique los gastos" << endl ;
    for(int i=0;i<7;i++){
        cin >> gastos[i];
        total = total + gastos[i];
    }

    promedio = total / 7;

    for(int i=0;i<7;i++){
        if(gastos[i] > promedio){
            mayores = mayores + 1;
        }
    }

    cout << "Total: " << total << endl;
    cout << "Promedio: " << promedio << endl;
    cout << "Mayores al promedio: " << mayores;
return 0;
}