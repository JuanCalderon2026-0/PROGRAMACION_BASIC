#include "GestorEstudiantes.h"
#include "Interfaz.h"
#include "Validacion.h"
#include "Utilidades.h"
#include "Excepciones.h"
#include "definiciones.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;

// ============================================================
//   IMPLEMENTACION: GestorEstudiantes
// ============================================================

GestorEstudiantes::GestorEstudiantes(SistemaAcademico& sis, Historial& hist)
    : sistema(sis), historial(hist) {}

// ---- Registrar nuevo estudiante ----
void GestorEstudiantes::registrar() {
    Interfaz::linea('=');
    cout << "\n";
    cout << "          REGISTRO DE NUEVO ESTUDIANTE\n";
    Interfaz::linea('=');
    cout << "\n\n";

    cout << "  [*] Codigo sugerido al azar: "
         << Utilidades::generarCodigoAleatorio() << "\n\n";

    // --------------------------------------------------------
    //   MANEJO DE EXCEPCIONES: try-catch con multiples catch
    //   Concepto: cada tipo de excepcion se captura por separado,
    //   permitiendo un mensaje de error especifico por caso.
    //   El bloque catch(ExcepcionSistema&) captura cualquier
    //   excepcion del sistema como red de seguridad.
    // --------------------------------------------------------

    // --- Codigo ---
    string codigo;
    while (true) {
        cout << "  Codigo (" << LONGITUD_CODIGO << " digitos): ";
        cin >> codigo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try {
            // Lanza CodigoInvalidoException si formato incorrecto
            Validacion::validarCodigo(codigo);

            // Lanza CodigoDuplicadoException si ya existe
            if (sistema.codigoExiste(codigo))
                throw CodigoDuplicadoException(codigo);

            break;  // Sin excepcion: codigo valido

        } catch (const CodigoDuplicadoException& e) {
            cout << "  [X] " << e.what() << "\n\n";
        } catch (const CodigoInvalidoException& e) {
            cout << "  [X] " << e.what() << "\n\n";
        } catch (const ExcepcionSistema& e) {
            // catch general para cualquier excepcion del sistema
            cout << "  [X] " << e.what() << "\n\n";
        }
    }

    // --- Nombre ---
    string nombre;
    while (true) {
        cout << "  Nombre completo: ";
        getline(cin, nombre);
        try {
            // Lanza NombreInvalidoException si nombre invalido
            Validacion::validarNombre(nombre);
            break;
        } catch (const NombreInvalidoException& e) {
            cout << "  [X] " << e.what() << "\n\n";
        }
    }

    // --- Grado ---
    int grado;
    while (true) {
        grado = Validacion::leerEntero("  Grado (1-5): ", MIN_GRADO, MAX_GRADO);
        try {
            // Lanza GradoInvalidoException si fuera de rango
            Validacion::validarGrado(grado);
            break;
        } catch (const GradoInvalidoException& e) {
            cout << "  [X] " << e.what() << "\n\n";
        }
    }

    // --- Curso ---
    Utilidades::mostrarMenuCursos();
    int opCurso = Validacion::leerEntero("  >>> Opcion (1-8): ", 1, TOTAL_CURSOS);
    Curso curso = tablaCursos[opCurso - 1];

    // Crear el objeto Estudiante en el heap y agregarlo al sistema
    Estudiante* nuevo = new Estudiante(codigo, nombre, grado, curso,
                                       Utilidades::obtenerFechaHora());
    sistema.agregarEstudiante(nuevo);
    historial.agregar("[" + Utilidades::obtenerFechaHora() + "]  Estudiante registrado");

    cout << "\n";
    Interfaz::linea('=');
    cout << "\n  [OK] ESTUDIANTE REGISTRADO EXITOSAMENTE!\n";
    Interfaz::linea('=');
    cout << "\n";
    cout << "  Codigo  : " << nuevo->getCodigo()              << "\n";
    cout << "  Nombre  : " << nuevo->getNombre()              << "\n";
    cout << "  Grado   : " << nuevo->getGrado()               << " de Secundaria\n";
    cout << "  Curso   : " << nuevo->getCurso().getNombre()   << "\n";
    cout << "  Profesor: " << nuevo->getCurso().getProfesor() << "\n";
    cout << "  Fecha   : " << nuevo->getFechaRegistro()       << "\n";
}

// ---- Mostrar fichas ----
void GestorEstudiantes::mostrarFichas() const {
    sistema.mostrarFichas();
    historial.agregar("[" + Utilidades::obtenerFechaHora() + "]  Fichas consultadas");
}

// ---- Ingresar notas ----
void GestorEstudiantes::ingresarNotas() {
    if (sistema.getCantidad() == 0) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }

    Interfaz::linea('=');
    cout << "\n  INGRESO DE NOTAS\n";
    Interfaz::linea('=');
    cout << "\n\n  Ingrese codigo del estudiante: ";

    string codigo;
    cin >> codigo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // --------------------------------------------------------
    //   MANEJO DE EXCEPCION: EstudianteNoEncontradoException
    //   Concepto: el metodo lanza la excepcion, aqui se captura
    //   con catch especifico y se muestra el mensaje de what()
    // --------------------------------------------------------
    Estudiante* est = nullptr;
    try {
        est = sistema.buscarPorCodigoSeguro(codigo);
    } catch (const EstudianteNoEncontradoException& e) {
        cout << "\n  [X] " << e.what() << "\n";
        return;
    }

    cout << "\n  [OK] Estudiante: " << est->getNombre() << "\n\n";

    int cantidad = Validacion::leerEntero(
        "  Cuantas notas desea ingresar (1-4): ", 1, MAX_NOTAS
    );

    // --------------------------------------------------------
    //   MANEJO DE EXCEPCION en notas: NotaFueraDeRangoException
    //   Concepto: try-catch dentro de un bucle — si la nota es
    //   invalida, se captura la excepcion y se repite la entrada.
    //   Buena practica: el flujo normal no se mezcla con errores.
    // --------------------------------------------------------
    est->limpiarNotas();
    for (int j = 0; j < cantidad; j++) {
        while (true) {
            ostringstream prompt;
            prompt << "  Nota Bimestre " << (j + 1) << " (0-20): ";
            float val = Validacion::leerFloat(prompt.str(), MIN_NOTA, MAX_NOTA);
            try {
                Validacion::validarNota(val);
                est->agregarNota(Nota(j + 1, val));
                break;
            } catch (const NotaFueraDeRangoException& e) {
                cout << "  [X] " << e.what() << "\n\n";
            }
        }
    }

    float prom = est->calcularPromedio();
    cout << "\n";
    Interfaz::linea('=');
    cout << "\n  [OK] NOTAS REGISTRADAS\n";
    Interfaz::linea('=');
    cout << "\n  Promedio: " << fixed << setprecision(2)
         << prom << "  " << Utilidades::etiquetaEstado(prom) << "\n";

    historial.agregar("[" + Utilidades::obtenerFechaHora() + "]  Notas ingresadas");
}

// ---- Editar estudiante ----
void GestorEstudiantes::editar() {
    if (sistema.getCantidad() == 0) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }

    Interfaz::linea('=');
    cout << "\n  EDITAR ESTUDIANTE\n";
    Interfaz::linea('=');
    cout << "\n\n  Ingrese codigo del estudiante: ";

    string codigo;
    cin >> codigo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Estudiante* est = nullptr;
    try {
        est = sistema.buscarPorCodigoSeguro(codigo);
    } catch (const EstudianteNoEncontradoException& e) {
        cout << "\n  [X] " << e.what() << "\n";
        return;
    }

    cout << "\n  [OK] Encontrado: " << est->getNombre() << "\n\n";
    cout << "  [1] Cambiar nombre\n";
    cout << "  [2] Cambiar grado\n";
    cout << "  [3] Cambiar curso\n";
    cout << "  [4] Cancelar\n\n";

    int op = Validacion::leerEntero("  >>> Opcion: ", 1, 4);

    switch (op) {
        case 1: {
            // try-catch para validar nuevo nombre
            string nn;
            while (true) {
                cout << "  Nuevo nombre: ";
                getline(cin, nn);
                try {
                    Validacion::validarNombre(nn);
                    est->setNombre(nn);
                    cout << "\n  [OK] Nombre actualizado.\n";
                    break;
                } catch (const NombreInvalidoException& e) {
                    cout << "  [X] " << e.what() << "\n\n";
                }
            }
            break;
        }
        case 2: {
            int ng = Validacion::leerEntero("  Nuevo grado (1-5): ", MIN_GRADO, MAX_GRADO);
            try {
                Validacion::validarGrado(ng);
                est->setGrado(ng);
                cout << "\n  [OK] Grado actualizado.\n";
            } catch (const GradoInvalidoException& e) {
                cout << "\n  [X] " << e.what() << "\n";
            }
            break;
        }
        case 3: {
            Utilidades::mostrarMenuCursos();
            int oc = Validacion::leerEntero("  >>> Opcion (1-8): ", 1, TOTAL_CURSOS);
            est->setCurso(tablaCursos[oc - 1]);
            cout << "\n  [OK] Curso actualizado: " << est->getCurso().getNombre() << "\n";
            break;
        }
        case 4:
            cout << "\n  [OK] Cancelado.\n";
    }
    historial.agregar("[" + Utilidades::obtenerFechaHora() + "]  Datos editados");
}

// ---- Eliminar estudiante ----
void GestorEstudiantes::eliminar() {
    if (sistema.getCantidad() == 0) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }

    Interfaz::linea('=');
    cout << "\n  ELIMINAR ESTUDIANTE\n";
    Interfaz::linea('=');
    cout << "\n\n  [!] Esta accion libera la memoria del estudiante.\n\n";
    cout << "  Ingrese codigo del estudiante: ";

    string codigo;
    cin >> codigo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Estudiante* est = nullptr;
    try {
        est = sistema.buscarPorCodigoSeguro(codigo);
    } catch (const EstudianteNoEncontradoException& e) {
        cout << "\n  [X] " << e.what() << "\n";
        return;
    }

    cout << "\n  [OK] Encontrado: " << est->getNombre() << "\n\n";
    cout << "  Confirmar eliminacion? (S/N): ";
    char conf;
    cin >> conf;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (conf != 'S' && conf != 's') {
        cout << "\n  [OK] Cancelado.\n";
        return;
    }

    sistema.eliminarEstudiante(codigo);

    cout << "\n";
    Interfaz::linea('=');
    cout << "\n  [OK] ESTUDIANTE ELIMINADO Y MEMORIA LIBERADA\n";
    Interfaz::linea('=');
    cout << "\n";

    historial.agregar("[" + Utilidades::obtenerFechaHora() + "]  Estudiante eliminado");
}

// ---- Buscar por nombre ----
void GestorEstudiantes::buscarPorNombre() const {
    Interfaz::linea('=');
    cout << "\n  BUSQUEDA POR NOMBRE\n";
    Interfaz::linea('=');
    cout << "\n\n  Ingrese nombre (o parte del nombre): ";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string busq;
    getline(cin, busq);

    // Devuelve vector<Estudiante*> — uso del operador << sobrecargado
    vector<Estudiante*> resultados = sistema.buscarTodos(busq);

    cout << "\n";
    Interfaz::linea('-');

    if (resultados.empty()) {
        cout << "\n  [!] No se encontraron estudiantes con ese nombre.\n";
        historial.agregar("[" + Utilidades::obtenerFechaHora() +
                          "]  Busqueda sin resultados: \"" + busq + "\"");
        return;
    }

    cout << "\n  Resultados encontrados: " << resultados.size()
         << "  para: \"" << busq << "\"\n\n";

    for (int i = 0; i < (int)resultados.size(); i++) {
        // Uso del operador << sobrecargado de Estudiante
        cout << "  [" << (i+1) << "] " << *resultados[i] << "\n";
    }

    historial.agregar("[" + Utilidades::obtenerFechaHora() +
                      "]  Busqueda \"" + busq + "\": " +
                      to_string((int)resultados.size()) + " resultado(s)");
}
