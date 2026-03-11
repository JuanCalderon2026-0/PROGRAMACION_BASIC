#include <iostream>
#include <string>
using namespace std;
class Celular {
private:
    string marca;
    string modelo;
    int bateria;
public:
    // Constructor para inicializar
    Celular(string marca, string modelo, int bateria) {
        this->marca = marca;
        this->modelo = modelo;
        this->setBateria(bateria);
}
   // 1) Setters con parámetros del mismo nombre que el atribut
    // 2) Uso de this-> para diferenciar this->marca= atributo, marca= parámetro)
    void setMarca(string marca) {
        this->marca = marca; 
    }
    void setModelo(string modelo) {
        this->modelo = modelo;
    }
    void setBateria(int bateria) {
        if (bateria >= 0 && bateria <= 100) {
            this->bateria = bateria;
        } else {
            cout << "Error: Bateria invalida." << endl;
        }
    }
    void mostrarInfo() {
        cout << "Celular: " << marca << " " << modelo << " | Bateria: " << bateria << "%" << endl;
    }
};
int main() {
    // 3) Prueba de que el programa sigue funcionando
    Celular miCel("Samsung", "S24", 95);
    miCel.mostrarInfo();
    miCel.setMarca("Apple");
    miCel.setModelo("iPhone 15");
    miCel.mostrarInfo();
    return 0;
}
//¿Qué pasaría si no usas this-> cuando el nombre del parámetro y el atributo son iguales?

//cuando el parámetro y el atributo se llaman igual y no usas this->, ocurre una ocultación de variable
 // donde el compilador le da prioridad al parámetro por ser el ámbito más cercano
 // Al escribir una instrucción como x = x; el programa simplemente 
 //asigna el valor del parámetro a sí mismo provocando un error de lógica donde el atributo de la clase 
 //nunca se actualiza y el objeto no guarda los cambios, aunque el código compile sin errores de sintaxis