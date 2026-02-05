#include <iostream>
using namespace std;

int main() {

    int n;
    cout << "Cantidad de estudiantes: ";
    cin >> n;

    int a[50][5];
    int totalAula = 0;
    int suma=0;

    for(int i=0; i<n; i++){
        cout << "Estudiante " << i+1 << endl;

        for(int j=0; j<5; j++){
            cout << "Dia " << j+1 << " (1=asistio, 0=no): ";
            cin >> a[i][j];
        }
    }
    cout << "RESULTADOS";

    for(int i=0; i<n; i++){

        suma = 0;

        for(int j=0; j<5; j++){
            suma = suma + a[i][j];
        }

        cout << "Estudiante " << i+1 << " asistencias: " << suma << endl;

        if(suma == 5){
            cout << "Asistencia perfecta" << endl;
        }

        totalAula = totalAula + suma;
    }

    cout << "Total de asistencias del aula: " << totalAula << endl;

    return 0;
}
