#include <iostream>
#include <string>
using namespace std;
// 1)  Vehiculo
class Vehiculo {
protected: // Permite que las clases hijas accedan directamente si es necesario
    string marca;
    int velocidadMax;
public:
    // Constructor con inicialización
    Vehiculo(string m, int v) : marca(m), velocidadMax(v) {}
    // Getters y Setters
    void setMarca(string marca) { this->marca = marca; }
    string getMarca() const { return marca; }
    
    void setVelocidadMax(int v) { this->velocidadMax = v; }
    int getVelocidadMax() const { return velocidadMax; }
    virtual void mostrarInfo() {
        cout << "Marca: " << marca << ", Vel. Max: " << velocidadMax << " km/h" << endl;
    }
};
// 2) : Carro
class Carro : public Vehiculo {
private:
    int puertas;
public:
    // Constructor que llama al de la base
    Carro(string m, int v, int p) : Vehiculo(m, v), puertas(p) {}

    void mostrarInfo() override {
        Vehiculo::mostrarInfo(); // Reutilizamos el método de la base
        cout << "Puertas: " << puertas << endl;
    }
};
// 3)Moto
class Moto : public Vehiculo {
private:
    int cilindraje;
public:
    Moto(string m, int v, int c) : Vehiculo(m, v), cilindraje(c) {}

    void mostrarInfo() override {
        Vehiculo::mostrarInfo();
        cout << "Cilindraje: " << cilindraje << "cc" << endl;
    }
};
int main() {
    Carro miCarro("Toyota", 180, 4);
    Moto miMoto("Yamaha", 150, 250);

    cout << "--- Datos del Carro ---" << endl;
    miCarro.mostrarInfo();

    cout << "\n--- Datos de la Moto ---" << endl;
    miMoto.mostrarInfo();
    return 0;
}
//¿Por qué la herencia reduce repetición de código?
//La herencia permite definir los atributos y comportamientos comunes (como marca y velocidadMax) en un solo lugar
//Evita duplicidad: No tienes que escribir el mismo código de setMarca o getMarca dentro de Carro y Moto por separado.
//Mantenimiento: Si decides cambiar cómo se guarda la marca, solo lo haces en Vehiculo y automáticamente 
//se actualiza en todos sus derivados