#include "Utilidades.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

// Tabla global de cursos con su profesor asignado
Curso tablaCursos[] = {
    Curso("Matematica",                "Sofia Martinez Gonzalez"),
    Curso("Comunicacion",              "Edwin Ramirez Lopez"),
    Curso("Historia",                  "Maximo Torres Ruiz"),
    Curso("Educacion para el Trabajo", "Lucas Fernandez Moreno"),
    Curso("Religion",                  "Isabella Morales Castro"),
    Curso("Educacion Fisica",          "Mateo Castillo Jimenez"),
    Curso("Desarrollo Personal",       "Camila Herrera Sanchez"),
    Curso("Ingles",                    "Sebastian Vargas Ortiz")
};
const int TOTAL_CURSOS = 8;

string Utilidades::obtenerFraseAleatoria() {
    const string frases[] = {
        "\"El conocimiento es poder.\" - Francis Bacon",
        "\"Educacion es el arma mas poderosa.\" - N. Mandela",
        "\"Aprender es un tesoro que sigue a su dueno.\"",
        "\"La educacion cambia el mundo.\"",
        "\"Cada dia es una nueva oportunidad de aprender.\"",
        "\"La constancia es la clave del exito academico.\"",
        "\"Estudia hoy, lidera manana.\"",
        "\"El esfuerzo de hoy es el exito de manana.\""
    };
    return frases[rand() % 8];
}

string Utilidades::generarCodigoAleatorio() {
    string cod = "";
    for (int i = 0; i < 5; i++)
        cod += to_string(rand() % 10);
    return cod;
}

string Utilidades::obtenerFechaHora() {
    time_t ahora = time(0);
    tm* ltm = localtime(&ahora);
    ostringstream oss;
    oss << (ltm->tm_mday < 10 ? "0" : "") << ltm->tm_mday << "/"
        << ((ltm->tm_mon + 1) < 10 ? "0" : "") << (ltm->tm_mon + 1) << "/"
        << (1900 + ltm->tm_year) << " "
        << (ltm->tm_hour < 10 ? "0" : "") << ltm->tm_hour << ":"
        << (ltm->tm_min  < 10 ? "0" : "") << ltm->tm_min;
    return oss.str();
}

string Utilidades::etiquetaEstado(float promedio) {
    if (promedio >= 14.0f) return "[APROBADO]";
    if (promedio >= 11.0f) return "[RECUPERACION]";
    return "[DESAPROBADO]";
}

void Utilidades::mostrarMenuCursos() {
    // Funcion local para linea (evita dependencia circular)
    auto linea = [](char c, int n){ for(int i=0;i<n;i++) cout<<c; };
    cout << "\n";
    linea('-', 62);
    cout << "\n                SELECCIONE EL CURSO\n";
    linea('-', 62);
    cout << "\n\n";
    for (int i = 0; i < TOTAL_CURSOS; i++) {
        cout << "  [" << (i + 1) << "] "
             << setw(28) << left << tablaCursos[i].getNombre()
             << "Prof. " << tablaCursos[i].getProfesor() << "\n";
    }
    cout << "\n";
}
