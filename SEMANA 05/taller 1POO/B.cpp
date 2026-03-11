#include <iostream>
#include <string>

using namespace std;

class Celular {
private: //atributos ahora son privados 
    string marca;
    string modelo;
    int bateria;
public:
    // Constructor simple para inicializar datos
    Celular(string m, string mod, int bat) {
        marca = m;
        modelo = mod;
        setBateria(bat); // Usamos el setter para validar   
    }
    // Getters
    string getMarca() const { return marca; }
    string getModelo() const { return modelo; }
    int getBateria() const { return bateria; }
    // Setters con validación 
    void setBateria(int b) {
        if (b >= 0 && b <= 100) {
            bateria = b;
        } else {
            cout << "Error: Valor de bateria invalido." << endl;
            bateria = 0; //defecto en caso de error
        }
    }
    void mostrarInfo() {
        cout << "Celular: " << marca << " " << modelo << " | Bateria: " << bateria << "%" << endl;
    }
};

int main() {
    // Prueba de la clase 
    Celular miCel("Xiaomi", "Redmi Note 13", 150); // Intento de 150% 
    miCel.mostrarInfo();

    return 0;
}
//¿Qué problema evita el encapsulamiento?
//Evita que los datos del objeto sean modificados con valores incorrectos
//Por ejemploimpide que alguien asigne una batería de -20$ o 500 asegurando que el objeto siempre funcione con información válida