#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <regex>
#include <map>
using namespace std;
class EntidadNoEncontrada : public runtime_error {
public:
    EntidadNoEncontrada(const string& msg) : runtime_error(msg) {}
};
class Persona {
protected:
    string nombre;

public:
    Persona(string n) : nombre(n) {}
    virtual void mostrar() const {
        cout << "Nombre: " << nombre << endl;
    } };

class EntradaHistoria {
public:
    string fecha;
    string nota;

    EntradaHistoria(string f, string n) : fecha(f), nota(n) {}};

class HistoriaClinica {
    vector<EntradaHistoria> entradas;

public:
    void agregarEntrada(string fecha, string nota) {
        entradas.push_back(EntradaHistoria(fecha, nota));
    } };
class Paciente : public Persona {
    string dni;
    int edad;
    string telefono;
    HistoriaClinica historia;
public:
    Paciente(string n, string d, int e, string t)
        : Persona(n), dni(d), edad(e), telefono(t) {}

    string getDNI() const { return dni; }
    void mostrar() const override {
        cout << "Paciente: " << nombre << " DNI: " << dni << endl;
    } };
class Doctor : public Persona {
    string codigo;
    string especialidad;
    double tarifa;

public:
    Doctor(string n, string c, string e, double t)
        : Persona(n), codigo(c), especialidad(e), tarifa(t) {}

    string getCodigo() const { return codigo; }
    string getEspecialidad() const { return especialidad; }
    void mostrar() const override {
        cout << "Doctor: " << nombre << " Especialidad: " << especialidad << endl;
    }
};
class Cita {
    int id;
    Paciente* paciente;
    Doctor* doctor;
    string fecha;
    string hora;
    string motivo;
    bool activa;
public:
    Cita(int i, Paciente* p, Doctor* d, string f, string h, string m)
        : id(i), paciente(p), doctor(d), fecha(f), hora(h), motivo(m), activa(true) {}

    int getId() const { return id; }
    string getFecha() const { return fecha; }
    string getHora() const { return hora; }
    Doctor* getDoctor() const { return doctor; }
    Paciente* getPaciente() const { return paciente; }
    void cancelar() { activa = false; }
    bool estaActiva() const { return activa; }
    void mostrar() const {
        cout << "Cita ID: " << id
             << " Paciente: ";
        paciente->mostrar();
        cout << "Doctor: ";
        doctor->mostrar();
        cout << "Fecha: " << fecha << " Hora: " << hora << endl;
    } };
class Clinica {
    vector<unique_ptr<Paciente>> pacientes;
    vector<unique_ptr<Doctor>> doctores;
    vector<unique_ptr<Cita>> citas;
    int contadorCitas = 1;

public:

    void registrarPaciente(string dni, string nombre, int edad, string telefono) {

        if(!regex_match(dni, regex("[0-9]{8}")))
            throw invalid_argument("DNI invalido");

        if(edad < 0 || edad > 120)
            throw invalid_argument("Edad invalida");

        if(!regex_match(telefono, regex("[0-9]{9}")))
            throw invalid_argument("Telefono invalido");

        pacientes.push_back(make_unique<Paciente>(nombre,dni,edad,telefono));
    }

    void registrarDoctor(string codigo,string nombre,string esp,double tarifa){

        if(tarifa<=0)
            throw invalid_argument("Tarifa invalida");

        doctores.push_back(make_unique<Doctor>(nombre,codigo,esp,tarifa));
    }

    Paciente* buscarPaciente(string dni){

        for(auto& p:pacientes)
            if(p->getDNI()==dni)
                return p.get();

        throw EntidadNoEncontrada("Paciente no encontrado");
    }

    Doctor* buscarDoctor(string codigo){

        for(auto& d:doctores)
            if(d->getCodigo()==codigo)
                return d.get();

        throw EntidadNoEncontrada("Doctor no encontrado");
    }

    void agendarCita(string dni,string codDoc,string fecha,string hora,string motivo){

        Paciente* p=buscarPaciente(dni);
        Doctor* d=buscarDoctor(codDoc);

        for(auto& c:citas){
            if(c->getDoctor()==d && c->getFecha()==fecha && c->getHora()==hora)
                throw runtime_error("Cita duplicada");
        }

        citas.push_back(make_unique<Cita>(contadorCitas++,p,d,fecha,hora,motivo));
    }

    void cancelarCita(int id){

        for(auto& c:citas){
            if(c->getId()==id){
                c->cancelar();
                return;
            }
        }

        throw runtime_error("Cita no existe");
    }

    void listarCitasPaciente(string dni){

        Paciente* p=buscarPaciente(dni);

        for(auto& c:citas)
            if(c->getPaciente()==p && c->estaActiva())
                c->mostrar();
    }

    void listarCitasDoctor(string codigo){

        Doctor* d=buscarDoctor(codigo);

        for(auto& c:citas)
            if(c->getDoctor()==d && c->estaActiva())
                c->mostrar();
    }

    const vector<unique_ptr<Cita>>& getCitas() const{
        return citas;
    }
};

class Reporte{

public:

    static void generarPorEspecialidad(const Clinica& c){

        map<string,int> conteo;

        for(auto& cita : c.getCitas()){

            string esp = cita->getDoctor()->getEspecialidad();
            conteo[esp]++;
        }

        cout<<"Reporte por especialidad"<<endl;

        for(auto& p:conteo)
            cout<<p.first<<" : "<<p.second<<" citas"<<endl;
    }
};

int main(){

    Clinica clinica;
    int opcion;

    do{

        cout<<"\n--- CLINICA SALUD+ ---\n";
        cout<<"1 Registrar paciente\n";
        cout<<"2 Registrar doctor\n";
        cout<<"3 Agendar cita\n";
        cout<<"4 Cancelar cita\n";
        cout<<"5 Listar citas por paciente\n";
        cout<<"6 Listar citas por doctor\n";
        cout<<"7 Reporte por especialidad\n";
        cout<<"8 Salir\n";

        cin>>opcion;

        try{

            if(opcion==1){

                string dni,nombre,telefono;
                int edad;

                cout<<"DNI: "; cin>>dni;
                cout<<"Nombre: "; cin>>nombre;
                cout<<"Edad: "; cin>>edad;
                cout<<"Telefono: "; cin>>telefono;

                clinica.registrarPaciente(dni,nombre,edad,telefono);
            }

            else if(opcion==2){

                string cod,nombre,esp;
                double tarifa;

                cout<<"Codigo: "; cin>>cod;
                cout<<"Nombre: "; cin>>nombre;
                cout<<"Especialidad: "; cin>>esp;
                cout<<"Tarifa: "; cin>>tarifa;

                clinica.registrarDoctor(cod,nombre,esp,tarifa);
            }

            else if(opcion==3){

                string dni,cod,fecha,hora,motivo;

                cout<<"DNI paciente: "; cin>>dni;
                cout<<"Codigo doctor: "; cin>>cod;
                cout<<"Fecha YYYY-MM-DD: "; cin>>fecha;
                cout<<"Hora HH:MM: "; cin>>hora;
                cout<<"Motivo: "; cin>>motivo;

                clinica.agendarCita(dni,cod,fecha,hora,motivo);
            }

            else if(opcion==4){

                int id;
                cout<<"ID cita: ";
                cin>>id;

                clinica.cancelarCita(id);
            }

            else if(opcion==5){

                string dni;
                cout<<"DNI paciente: ";
                cin>>dni;

                clinica.listarCitasPaciente(dni);
            }

            else if(opcion==6){

                string cod;
                cout<<"Codigo doctor: ";
                cin>>cod;

                clinica.listarCitasDoctor(cod);
            }

            else if(opcion==7){

                Reporte::generarPorEspecialidad(clinica);
            }

            else if(opcion!=8){

                throw out_of_range("Opcion invalida");
            }

        }
        catch(exception& e){

            cout<<"Error: "<<e.what()<<endl;
        }

    }while(opcion!=8);
}