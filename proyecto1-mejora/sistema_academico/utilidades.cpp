#include "utilidades.h"
#include "interfaz.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

// ============================================================
//   MODULO: Utilidades
// ============================================================

// Tabla global de cursos con su profesor asignado
Curso tablaCursos[] = {
    {"Matematica",                "Sofia Martinez Gonzalez"},
    {"Comunicacion",              "Edwin Ramirez Lopez"},
    {"Historia",                  "Maximo Torres Ruiz"},
    {"Educacion para el Trabajo", "Lucas Fernandez Moreno"},
    {"Religion",                  "Isabella Morales Castro"},
    {"Educacion Fisica",          "Mateo Castillo Jimenez"},
    {"Desarrollo Personal",       "Camila Herrera Sanchez"},
    {"Ingles",                    "Sebastian Vargas Ortiz"}
};
const int TOTAL_CURSOS = 8;

// ------------------------------------------------------------------
// Frases motivacionales: se elige una al azar cada vez que se llama
// ------------------------------------------------------------------
string obtenerFraseAleatoria() {
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

// ------------------------------------------------------------------
// Genera un codigo de 5 digitos aleatorio como sugerencia
// ------------------------------------------------------------------
string generarCodigoAleatorio() {
    string cod = "";
    for (int i = 0; i < LONGITUD_CODIGO; i++)
        cod += to_string(rand() % 10);
    return cod;
}

// ------------------------------------------------------------------
// Fecha y hora actual formateada
// ------------------------------------------------------------------
string obtenerFechaHora() {
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

// ------------------------------------------------------------------
// Calcula el promedio recorriendo con PUNTERO
// ------------------------------------------------------------------
float calcularPromedio(const Nota* notas, int cantidad) {
    if (cantidad == 0) return 0.0f;
    float suma = 0.0f;
    const Nota* ptr = notas;          // puntero para iterar
    for (int i = 0; i < cantidad; i++, ptr++)
        suma += ptr->valor;
    return suma / cantidad;
}

// ------------------------------------------------------------------
// Etiqueta de aprobacion segun promedio peruano
// ------------------------------------------------------------------
string etiquetaEstado(float promedio) {
    if (promedio >= 14.0f) return "[APROBADO]";
    if (promedio >= 11.0f) return "[RECUPERACION]";
    return "[DESAPROBADO]";
}

// ------------------------------------------------------------------
// Muestra el menu de seleccion de curso en pantalla
// ------------------------------------------------------------------
void mostrarMenuCursos() {
    cout << "\n";
    linea('-');
    cout << "\n                SELECCIONE EL CURSO\n";
    linea('-');
    cout << "\n\n";
    for (int i = 0; i < TOTAL_CURSOS; i++) {
        cout << "  [" << (i + 1) << "] "
             << setw(28) << left << tablaCursos[i].nombre
             << "Prof. " << tablaCursos[i].profesor << "\n";
    }
    cout << "\n";
}
