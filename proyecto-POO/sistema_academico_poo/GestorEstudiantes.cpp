#include "GestorEstudiantes.h"
#include "Interfaz.h"
#include "Validacion.h"
#include "Utilidades.h"
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

    // --- Codigo ---
    string codigo;
    while (true) {
        cout << "  Codigo (" << LONGITUD_CODIGO << " digitos): ";
        cin >> codigo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if ((int)codigo.length() != LONGITUD_CODIGO) {
            cout << "  [X] El codigo debe tener " << LONGITUD_CODIGO << " digitos.\n\n";
            continue;
        }
        if (!Validacion::esSoloDigitos(codigo)) {
            cout << "  [X] Solo puede contener digitos.\n\n";
            continue;
        }
        if (sistema.codigoExiste(codigo)) {
            cout << "  [X] Ese codigo ya esta registrado.\n\n";
            continue;
        }
        break;
    }

    // --- Nombre ---
    string nombre = Validacion::leerTexto(
        "  Nombre completo: ",
        Validacion::esNombreValido,
        "Solo letras y espacios."
    );

    // --- Grado ---
    int grado = Validacion::leerEntero("  Grado (1-5): ", MIN_GRADO, MAX_GRADO);

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

    Estudiante* est = sistema.buscarPorCodigo(codigo);
    if (est == nullptr) {
        cout << "\n  [X] Estudiante no encontrado.\n";
        return;
    }

    cout << "\n  [OK] Estudiante: " << est->getNombre() << "\n\n";

    int cantidad = Validacion::leerEntero(
        "  Cuantas notas desea ingresar (1-4): ", 1, MAX_NOTAS
    );

    // Limpiar notas anteriores y agregar las nuevas
    est->limpiarNotas();
    for (int j = 0; j < cantidad; j++) {
        ostringstream prompt;
        prompt << "  Nota Bimestre " << (j + 1) << " (0-20): ";
        float val = Validacion::leerFloat(prompt.str(), MIN_NOTA, MAX_NOTA);
        est->agregarNota(Nota(j + 1, val));
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

    Estudiante* est = sistema.buscarPorCodigo(codigo);
    if (est == nullptr) {
        cout << "\n  [X] Estudiante no encontrado.\n";
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
            string nn = Validacion::leerTexto(
                "  Nuevo nombre: ", Validacion::esNombreValido,
                "Solo letras y espacios."
            );
            est->setNombre(nn);
            cout << "\n  [OK] Nombre actualizado.\n";
            break;
        }
        case 2: {
            est->setGrado(Validacion::leerEntero(
                "  Nuevo grado (1-5): ", MIN_GRADO, MAX_GRADO
            ));
            cout << "\n  [OK] Grado actualizado.\n";
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

    Estudiante* est = sistema.buscarPorCodigo(codigo);
    if (est == nullptr) {
        cout << "\n  [X] Estudiante no encontrado.\n";
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

    // Devuelve vector<Estudiante*> — uso de clase relacionada
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
        Estudiante* e = resultados[i];
        cout << "  [" << (i+1) << "] "
             << setw(8)  << left << e->getCodigo()
             << " | " << setw(24) << left << e->getNombre()
             << " | Grado " << e->getGrado()
             << " | " << e->getCurso().getNombre() << "\n";
    }

    historial.agregar("[" + Utilidades::obtenerFechaHora() +
                      "]  Busqueda \"" + busq + "\": " +
                      to_string((int)resultados.size()) + " resultado(s)");
}
