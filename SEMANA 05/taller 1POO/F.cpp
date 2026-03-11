#include <iostream>
#include <string>
using namespace std;
class Persona {
private:
    string nombre;
    int edad;
public:
    //tus getters/setters y mostrar
    void setNombre(string nombre) { this->nombre = nombre; }
    string getNombre() const { return nombre; }
    void setEdad(int edad) { this->edad = (edad >= 0) ? edad : 0; }
    
    // 1 Método virtual en la clase base
    virtual void rol() { 
        cout << "Soy una persona." << endl; 
    }
    
    virtual ~Persona() {}
};
class Estudiante : public Persona {
public:
    // 2Sobrescribir rol para Estudiante
    void rol() override { 
        cout << "Soy estudiante." << endl; 
    }
};

class Profesor : public Persona {
public:
    // 3 Sobrescribir rol para Profesor
    void rol() override { 
        cout << "Soy profesor." << endl; 
    }
};

int main() {
    // 4 Arreglo de punteros de tipo Persona*
    Persona* grupo[2]; 

    // Guardamos un Estudiante y un Profesor en el arregl
    grupo[0] = new Estudiante();
    grupo[1] = new Profesor();

    // 5 Recorrer el arreglo y llamar a rol
    cout << "--- Demostración de Polimorfismo ---" << endl;
    for(int i = 0; i < 2; i++) {
        grupo[i]->rol(); // Ejecuta el método correcto de la clase derivada
    }

    // Limpieza de memoria
    delete grupo[0];
    delete grupo[1];

    return 0;
}
//¿Qué ventaja da el polimorfismo?
//El polimorfismo permite que un programa sea escalable y flexible. Su principal
 //ventaja es que permite escribir código que trabaje con una clase base (como Persona) 
 //y que este funcione automáticamente con cualquier clase nueva que herede de ella