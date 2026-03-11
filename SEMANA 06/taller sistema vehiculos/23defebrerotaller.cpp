#include <iostream>
#include <vector>
using namespace std;
class Vehiculo {
protected:
    int id;
    float velocidad;

public:
    Vehiculo(int id, float velocidad) {
        this->id = id;
        this->velocidad = velocidad;
    }

    virtual void moverse() = 0;
    virtual void mostrarInfo() {
        cout << "ID: " << id << endl;
        cout << "Velocidad: " << velocidad << " km/h" << endl;
    }

    virtual ~Vehiculo() {}

    friend class Reporte; 
};

class Auto : public Vehiculo {
private:
    string combustible;

public:
    Auto(int id, float velocidad, string combustible)
        : Vehiculo(id, velocidad) {
        this->combustible = combustible;
    }

    void moverse() override {
        cout << "El Auto se mueve por carretera." << endl;
    }

    void mostrarInfo() override {
        Vehiculo::mostrarInfo();
        cout << "Combustible: " << combustible << endl;
    }
};
class Drone : public Vehiculo {
private:
    float altitud;

public:
    Drone(int id, float velocidad, float altitud)
        : Vehiculo(id, velocidad) {
        this->altitud = altitud;
    }

    void moverse() override {
        cout << "El Drone vuela por el aire." << endl;
    }

    void mostrarInfo() override {
        Vehiculo::mostrarInfo();
        cout << "Altitud máxima: " << altitud << " metros" << endl;
    }
};
class Camion : public Vehiculo {
private:
    float capacidadCarga;

public:
    Camion(int id, float velocidad, float capacidadCarga)
        : Vehiculo(id, velocidad) {
        this->capacidadCarga = capacidadCarga;
    }

    void moverse() override {
        cout << "El Camion transporta carga pesada." << endl;
    }

    void mostrarInfo() override {
        Vehiculo::mostrarInfo();
        cout << "Capacidad de carga: " << capacidadCarga << " toneladas" << endl;
    }
};
template <typename T>
T calcularEficiencia(T consumo, T distancia) {
    return distancia / consumo;
}
class Reporte {
public:
    static void generarReporte(Vehiculo* v) {
        cout << "\n--- REPORTE ---" << endl;
        cout << "ID (acceso directo): " << v->id << endl;
        cout << "Velocidad (acceso directo): " << v->velocidad << endl;
    }
};
int main() {

    vector<Vehiculo*> flota;
    flota.push_back(new Auto(1, 120, "Gasolina"));
    flota.push_back(new Drone(2, 80, 500));
    flota.push_back(new Camion(3, 90, 20));

    cout << "\n=== P DINAMICO ===\n";

    for (Vehiculo* v : flota) {
        v->moverse();
        v->mostrarInfo();
        Reporte::generarReporte(v);
        cout << "------------------\n";
    }
    cout << "\n=== ESTATICO ===\n";
    cout << "Eficiencia: "
         << calcularEficiencia(10.0, 200.0) << endl;
    for (Vehiculo* v : flota) {
        delete v;
    }

    return 0;
}
