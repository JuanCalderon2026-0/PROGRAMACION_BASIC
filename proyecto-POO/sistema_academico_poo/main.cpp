// ============================================================
//   SISTEMA ACADEMICO PROFESIONAL v3.0 — VERSION POO
//   main.cpp — Punto de entrada del programa
//
//   Estructura de clases:
//     Persona (abstracta)
//       └── Estudiante
//     IReporte (interfaz abstracta)
//       └── SistemaAcademico
//     Nota, Curso, Historial, GestorEstudiantes,
//     Archivos, Interfaz, Validacion, Utilidades
// ============================================================

#include "definiciones.h"
#include "Interfaz.h"
#include "SistemaAcademico.h"
#include "GestorEstudiantes.h"
#include "Historial.h"
#include "Archivos.h"
#include "Utilidades.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand((unsigned int)time(0));

    // Objetos principales del sistema (en el stack; gestionan su propio heap)
    SistemaAcademico sistema;
    Historial        historial;
    GestorEstudiantes gestor(sistema, historial);  // USA-UN SistemaAcademico y Historial

    // Cargar datos previos y registrar inicio
    Archivos::cargarDatos(sistema);
    historial.agregar("[" + Utilidades::obtenerFechaHora() + "]  Sistema iniciado");

    int opcion;

    do {
        Interfaz::limpiarPantalla();
        Interfaz::mostrarBanner();
        Interfaz::mostrarMenu();

        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n  [X] Entrada invalida.\n";
            Interfaz::pausar();
            continue;
        }

        Interfaz::limpiarPantalla();

        switch (opcion) {
            case 1:
                gestor.registrar();
                Interfaz::pausar(); break;
            case 2:
                gestor.mostrarFichas();
                Interfaz::pausar(); break;
            case 3:
                gestor.ingresarNotas();
                Interfaz::pausar(); break;
            case 4:
                // Llamada polimorfica via puntero IReporte*
                // Concepto: Polimorfismo en tiempo de ejecucion
                sistema.mostrarPromedios();
                historial.agregar("[" + Utilidades::obtenerFechaHora() + "]  Promedios consultados");
                Interfaz::pausar(); break;
            case 5:
                sistema.mostrarRanking();
                historial.agregar("[" + Utilidades::obtenerFechaHora() + "]  Ranking consultado");
                Interfaz::pausar(); break;
            case 6:
                gestor.editar();
                Interfaz::pausar(); break;
            case 7:
                gestor.eliminar();
                Interfaz::pausar(); break;
            case 8:
                sistema.mostrarEstadisticas();
                cout << "\n";
                sistema.mostrarEstadoMemoria();
                historial.agregar("[" + Utilidades::obtenerFechaHora() + "]  Estadisticas consultadas");
                Interfaz::pausar(); break;
            case 9:
                gestor.buscarPorNombre();
                Interfaz::pausar(); break;
            case 10:
                historial.mostrar();
                Interfaz::pausar(); break;
            case 11:
                Archivos::guardarDatos(sistema);
                historial.agregar("[" + Utilidades::obtenerFechaHora() + "]  Datos guardados - Sistema cerrado");
                Interfaz::limpiarPantalla();
                Interfaz::mostrarBanner();
                cout << "\n\n";
                Interfaz::linea('=');
                cout << "\n  DATOS GUARDADOS. HASTA PRONTO!\n";
                Interfaz::linea('=');
                cout << "\n\n";
                break;
            default:
                cout << "\n  [X] Opcion invalida (1-11).\n";
                Interfaz::pausar();
        }

    } while (opcion != 11);

    // El destructor de SistemaAcademico libera toda la memoria automaticamente
    return 0;
}
