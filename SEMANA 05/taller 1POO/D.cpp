#include <iostream>
#include <string>
class Celular {
private:
    std::string marca;
    std::string modelo;
    int bateria;
public:
    // 1 Constructor por defecto
    Celular() : marca("Desconocida"), modelo("Generico"), bateria(100) {}

    // 2 Constructor con 2 parámetrosmarca y modelo
    Celular(std::string marca, std::string modelo) : marca(marca), modelo(modelo), bateria(100) {}

    // 3 Constructor con 3 parámetros validación de batería
    Celular(std::string marca, std::string modelo, int bateria) {
        this->marca = marca;
        this->modelo = modelo;
        // Validación: si la batería es mayor a 100 o menor a 0 se ajusta
        if (bateria > 100) this->bateria = 100;
        else if (bateria < 0) this->bateria = 0;
        else this->bateria = bateria;
    }
    void mostrarInfo() {
        std::cout << "Celular: " << marca << " " << modelo << " | Bateria: " << bateria << "%" << std::endl;
    }
};
int main() {
    // 4 Creación de los 3 objetos
    Celular c1;                          // Usa el constructor por defect
    Celular c2("Samsung", "S24");        // Usa el de 2 parámetros
    Celular c3("Apple", "iPhone 15", 85); // Usa el de 3 parámetros
    std::cout << "--- Informacion de Celulares ---" << std::endl;
    c1.mostrarInfo();
    c2.mostrarInfo();
    c3.mostrarInfo();
    return 0;
}
//¿Por qué es útil tener constructores sobrecargados?

//Es útil porque ofrece flexibilidad al programador
//Permite crear objetos incluso cuando no se tienen todos los datos disponibles en ese momento