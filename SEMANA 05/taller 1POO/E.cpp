    #include <iostream>
#include <string>
using namespace std;
//Parte A
class Persona {
private:
    string nombre;
    int edad;
public:
    // Getters y Setters con validación
    void setNombre(string nombre) { this->nombre = nombre; }
    string getNombre() const { return nombre; }
    void setEdad(int edad) {
        if (edad >= 0) { // Validación: edad no negativa 
            this->edad = edad;
        } else {
            cout << "Error: La edad no puede ser negativa. Se asignará 0." << endl;
            this->edad = 0;
        }
    }
    int getEdad() const { return edad; }
    void mostrar() {
        cout << "Nombre: " << nombre << ", Edad: " << edad << endl;
    }
};
// Parte B
class Estudiante : public Persona { // Herencia
private:
    string carrera;
public:
    void setCarrera(string carrera) { this->carrera = carrera; }
    string getCarrera() const { return carrera; }
    void estudiar() {
        cout << getNombre() << " esta estudiando " << carrera << "." << endl;
    }
};
class Profesor : public Persona { // Herencia
private:
    string materia;
public:
    void setMateria(string materia) { this->materia = materia; }
    string getMateria() const { return materia; }
    void ensenar() {
        cout << getNombre() << " esta ensenando la materia: " << materia << "." << endl;
    }
};
// PRUIEBAS
int main() {
    // Prueba de la estudiante
    Estudiante est;
    est.setNombre("Ana Garcia");
    est.setEdad(20);
    est.setCarrera("Ingenieria de Sistemas");
    est.mostrar();
    est.estudiar();
    cout << "---------------------------" << endl;
    // Prueba Profe
    Profesor prof;
    prof.setNombre("Carlos Lopez");
    prof.setEdad(45);
    prof.setMateria("Programacion C++");
    prof.mostrar();
    prof.ensenar();
    return 0;
}
//¿Qué atributos y métodos comparten Estudiante y Profesor gracias a Persona?
//Gracias a la herencia de la clase Persona, tanto Estudiante como Profesor comparten los siguientes elementos: