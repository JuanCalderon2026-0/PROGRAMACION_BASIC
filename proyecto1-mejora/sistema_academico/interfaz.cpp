#include "interfaz.h"
#include "utilidades.h"
#include <iostream>
#include <limits>
using namespace std;

// ============================================================
//   MODULO: Interfaz
// ============================================================

void linea(char c, int n) {
    for (int i = 0; i < n; i++) cout << c;
}

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    cout << "\n";
    linea('-');
    cout << "\n  Presione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void mostrarBanner() {
    cout << "\n";
    linea('*');
    cout << "\n";
    cout << "  ****   SISTEMA ACADEMICO PROFESIONAL v3.0   ****\n";
    cout << "  *                                              *\n";
    cout << "  *   Structs | Punteros | Modular | Dinamico   *\n";
    cout << "  *                                              *\n";
    linea('*');
    cout << "\n\n";
    // Frase aleatoria (viene del modulo utilidades)
    cout << "  " << obtenerFraseAleatoria() << "\n";
}

void mostrarMenu() {
    cout << "\n";
    linea('=');
    cout << "\n";
    cout << "                    MENU PRINCIPAL\n";
    linea('=');
    cout << "\n\n";
    cout << "   [1]  Registrar Nuevo Estudiante\n";
    cout << "   [2]  Ver Fichas de Estudiantes\n";
    cout << "   [3]  Ingresar / Actualizar Notas\n";
    cout << "   [4]  Ver Promedios\n";
    cout << "   [5]  Ranking Academico\n";
    cout << "   [6]  Editar Datos de Estudiante\n";
    cout << "   [7]  Eliminar Estudiante\n";
    cout << "   [8]  Estadisticas del Sistema\n";
    cout << "   [9]  Guardar y Salir\n\n";
    linea('-');
    cout << "\n  >>> Seleccione una opcion: ";
}
