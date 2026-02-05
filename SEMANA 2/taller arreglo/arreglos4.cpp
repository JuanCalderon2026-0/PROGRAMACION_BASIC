#include <iostream>
using namespace std;

int main() {

    int n;
    cout << "Cuantos dias? ";
    cin >> n;

int a[100];
        int actual = 0;
    int mayor = 0;


    // ENTRADA
    for(int i=0; i<n; i++){
        cout << "Dia " << i+1 << ": ";
        cin >> a[i];
    }

    // PROCESO
    for(int i=0; i<n; i++){

        if(a[i] > 0){
            actual++;          // aca se suma la racha
        }
        else{
            actual = 0;        // se reinicia la racha por un dia malo
        }

        if(actual > mayor){
            mayor = actual;    // guarda la mayor
        }
    }

    cout << "Mayor racha positiva: " << mayor << " dias";

    return 0;
}

