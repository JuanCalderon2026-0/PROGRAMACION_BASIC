// ============================================================
//   SISTEMA ACADEMICO PROFESIONAL v3.0 — VERSION POO
//   main.cpp — Punto de entrada del programa
//
//   Estructura de clases:
//     Persona (abstracta)
//       └── Estudiante
//     IReporte (interfaz abstracta pura)
//       └── SistemaAcademico
//     Nota, Curso, Historial, GestorEstudiantes,
//     Archivos, Interfaz, Validacion, Utilidades
//
//   Temas POO cubiertos:
//     - Clases y objetos, Herencia, Polimorfismo
//     - Encapsulamiento, Abstraccion
//     - Clases abstractas e Interfaces (IReporte)
//     - Metodos virtuales y override
//     - Excepciones personalizadas (try-catch, throw)
//     - Sobrecarga de operadores (+, <, ==, <<)
//     - enum class (EstadoAcademico, MenuOpcion)
//     - enum tradicional (NivelError)
//     - Memoria dinamica (new / delete)
// ============================================================

#include "definiciones.h"
#include "Interfaz.h"
#include "SistemaAcademico.h"
#include "GestorEstudiantes.h"
#include "Historial.h"
#include "Archivos.h"
#include "Utilidades.h"
#include "IReporte.h"
#include "Excepciones.h"
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
    GestorEstudiantes gestor(sistema, historial);

    // ----------------------------------------------------------
    //   USO DE INTERFAZ VIA PUNTERO (IReporte*)
    //   Concepto: Polimorfismo en tiempo de ejecucion.
    //   IReporte* apunta a SistemaAcademico, pero el llamador
    //   solo conoce la interfaz — no la implementacion concreta.
    //   Las llamadas se resuelven en tiempo de ejecucion (enlace dinamico).
    // ----------------------------------------------------------
    IReporte* reporte = &sistema;

    // Cargar datos previos y registrar inicio
    Archivos::cargarDatos(sistema);
    historial.agregar("[" + Utilidades::obtenerFechaHora() + "]  Sistema iniciado");

    int opcionInt;

    do {
        Interfaz::limpiarPantalla();
        Interfaz::mostrarBanner();
        Interfaz::mostrarMenu();

        cin >> opcionInt;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n  [X] Entrada invalida.\n";
            Interfaz::pausar();
            continue;
        }

        Interfaz::limpiarPantalla();

        // ----------------------------------------------------------
        //   ENUM CLASS MenuOpcion en switch
        //   Concepto: el entero ingresado se convierte a MenuOpcion
        //   usando static_cast. El switch usa valores del enum class
        //   con su ambito (MenuOpcion::REGISTRAR, etc.).
        //   Mejora la legibilidad vs usar numeros magicos (1, 2, 3...).
        // ----------------------------------------------------------
        MenuOpcion opcion = static_cast<MenuOpcion>(opcionInt);

        // ----------------------------------------------------------
        //   MANEJO DE EXCEPCION en el bucle principal
        //   Concepto: try-catch general que atrapa cualquier
        //   ExcepcionSistema no capturada en niveles inferiores.
        //   Buena practica: el programa nunca termina abruptamente
        //   por una excepcion no manejada.
        // ----------------------------------------------------------
        try {
            switch (opcion) {
                case MenuOpcion::REGISTRAR:
                    gestor.registrar();
                    Interfaz::pausar(); break;

                case MenuOpcion::VER_FICHAS:
                    gestor.mostrarFichas();
                    Interfaz::pausar(); break;

                case MenuOpcion::INGRESAR_NOTAS:
                    gestor.ingresarNotas();
                    Interfaz::pausar(); break;

                case MenuOpcion::VER_PROMEDIOS:
                    // Llamada polimorfica via puntero IReporte*
                    // Concepto: Polimorfismo en tiempo de ejecucion
                    reporte->mostrarPromedios();
                    historial.agregar("[" + Utilidades::obtenerFechaHora() + "]  Promedios consultados");
                    Interfaz::pausar(); break;

                case MenuOpcion::RANKING:
                    reporte->mostrarRanking();
                    historial.agregar("[" + Utilidades::obtenerFechaHora() + "]  Ranking consultado");
                    Interfaz::pausar(); break;

                case MenuOpcion::EDITAR:
                    gestor.editar();
                    Interfaz::pausar(); break;

                case MenuOpcion::ELIMINAR:
                    gestor.eliminar();
                    Interfaz::pausar(); break;

                case MenuOpcion::ESTADISTICAS:
                    reporte->mostrarEstadisticas();
                    cout << "\n";
                    sistema.mostrarEstadoMemoria();
                    historial.agregar("[" + Utilidades::obtenerFechaHora() + "]  Estadisticas consultadas");
                    Interfaz::pausar(); break;

                case MenuOpcion::BUSCAR:
                    gestor.buscarPorNombre();
                    Interfaz::pausar(); break;

                case MenuOpcion::HISTORIAL:
                    historial.mostrar();
                    Interfaz::pausar(); break;

                case MenuOpcion::GUARDAR_SALIR:
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

        } catch (const ExcepcionSistema& e) {
            // Captura cualquier excepcion del sistema no manejada antes
            cout << "\n  [!] Error del sistema: " << e.what() << "\n";
            Interfaz::pausar();
        } catch (const exception& e) {
            // Captura excepciones estandar de C++ (std::exception)
            cout << "\n  [!] Error estandar: " << e.what() << "\n";
            Interfaz::pausar();
        }

    } while (opcionInt != static_cast<int>(MenuOpcion::GUARDAR_SALIR));

    // El destructor de SistemaAcademico libera toda la memoria automaticamente
    return 0;
}
