#include <iostream>
#include <string>
using namespace std;
// 1) Crea una clase llamada Celular con los atributos
class Celular {
public:
    string marca;
    string modelo;
    int bateria;
// 3) Crea un método mostrarInfo() que imprima la informació
    void mostrarInfo() {
                cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Bateria: " << bateria << "%" << endl;
        cout << "--------------------" << endl;
    }
};
int main() {
    // 2) Crea 2 objetos (cel1 y cel2) con valores distintos 
    Celular cel1;
    cel1.marca = "Samsung";
    cel1.modelo = "Galaxy S23";
    cel1.bateria = 85;
    Celular cel2;
    cel2.marca = "Apple";
    cel2.modelo = "iPhone 15";
    cel2.bateria = 92;

    // 4) Llama mostrarInfo() para los 2 objetos
    cout << "Informacion del primer celular:" << endl;
    cel1.mostrarInfo();

    cout << "Informacion del segundo celular:" << endl;
    cel2.mostrarInfo();

    return 0;
}
//¿Qué significa decir que un objeto es una “instancia” de una clase?
// Significa que la clase es la idea o el diseño (como un molde de galletas) 
//y el objeto es el producto real que creas con ese molde una galleta con sabor 
//y forma específica , el objeto ocupa un espacio real en la memoria de la computadora con sus propios datos.