#include "estudiantes.h"
#include "interfaz.h"
#include "validacion.h"
#include "utilidades.h"
#include "busqueda.h"
#include "memoria.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
using namespace std;

// ============================================================
//   MODULO: Gestion de Estudiantes (CRUD)
// ============================================================

// ------------------------------------------------------------------
// Registrar: crea un Estudiante en el heap y lo agrega al sistema
// ------------------------------------------------------------------
void registrarEstudiante(SistemaAcademico* sys) {
    linea('=');
    cout << "\n";
    cout << "          REGISTRO DE NUEVO ESTUDIANTE\n";
    linea('=');
    cout << "\n\n";

    // Sugerencia aleatoria
    cout << "  [*] Codigo sugerido al azar: "
         << generarCodigoAleatorio() << "\n\n";

    // Crear el Estudiante en el heap
    Estudiante* nuevo = crearEstudiante();

    // --- Codigo ---
    while (true) {
        cout << "  Codigo (" << LONGITUD_CODIGO << " digitos): ";
        cin >> nuevo->codigo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if ((int)nuevo->codigo.length() != LONGITUD_CODIGO) {
            cout << "  [X] El codigo debe tener "
                 << LONGITUD_CODIGO << " digitos.\n\n";
            continue;
        }
        if (!esSoloDigitos(nuevo->codigo)) {
            cout << "  [X] Solo puede contener digitos.\n\n";
            continue;
        }
        if (codigoExiste(sys, nuevo->codigo)) {
            cout << "  [X] Ese codigo ya esta registrado.\n\n";
            continue;
        }
        break;
    }

    // --- Nombre ---
    nuevo->nombre = leerTexto(
        "  Nombre completo: ",
        esNombreValido,
        "Solo letras y espacios."
    );

    // --- Grado ---
    nuevo->grado = leerEntero("  Grado (1-5): ", MIN_GRADO, MAX_GRADO);

    // --- Curso ---
    mostrarMenuCursos();
    int opCurso = leerEntero("  >>> Opcion (1-8): ", 1, TOTAL_CURSOS);
    nuevo->curso = tablaCursos[opCurso - 1];

    // --- Notas: SIN asignar todavia (nullptr) ---
    nuevo->notas          = nullptr;
    nuevo->cantidadNotas  = 0;
    nuevo->capacidadNotas = 0;

    nuevo->fechaRegistro  = obtenerFechaHora();
    nuevo->activo         = true;

    // Agregar al sistema (expande la lista si es necesario)
    agregarEstudiante(sys, nuevo);

    cout << "\n";
    linea('=');
    cout << "\n  [OK] ESTUDIANTE REGISTRADO EXITOSAMENTE!\n";
    linea('=');
    cout << "\n";
    cout << "  Codigo  : " << nuevo->codigo          << "\n";
    cout << "  Nombre  : " << nuevo->nombre          << "\n";
    cout << "  Grado   : " << nuevo->grado           << " de Secundaria\n";
    cout << "  Curso   : " << nuevo->curso.nombre    << "\n";
    cout << "  Profesor: " << nuevo->curso.profesor  << "\n";
    cout << "  Fecha   : " << nuevo->fechaRegistro   << "\n";
}

// ------------------------------------------------------------------
// Mostrar ficha individual (helper interno)
// ------------------------------------------------------------------
static void mostrarFicha(const Estudiante* e, int numero) {
    cout << "\n";
    linea('-');
    cout << "\n  ESTUDIANTE #" << numero << "\n";
    linea('-');
    cout << "\n";
    cout << "  Codigo    : " << e->codigo            << "\n";
    cout << "  Nombre    : " << e->nombre            << "\n";
    cout << "  Grado     : " << e->grado             << " de Secundaria\n";
    cout << "  Curso     : " << e->curso.nombre      << "\n";
    cout << "  Profesor  : " << e->curso.profesor    << "\n";
    cout << "  Registrado: " << e->fechaRegistro     << "\n";

    if (e->cantidadNotas > 0) {
        cout << "  Notas     : ";
        // Recorrer notas con puntero
        const Nota* nptr = e->notas;
        for (int j = 0; j < e->cantidadNotas; j++, nptr++) {
            cout << "B" << nptr->bimestre << ":"
                 << fixed << setprecision(1) << nptr->valor;
            if (j < e->cantidadNotas - 1) cout << "  |  ";
        }
        float prom = calcularPromedio(e->notas, e->cantidadNotas);
        cout << "\n  Promedio  : " << fixed << setprecision(2) << prom
             << "  " << etiquetaEstado(prom) << "\n";
    } else {
        cout << "  Notas     : Sin notas registradas.\n";
    }
}

// ------------------------------------------------------------------
// Mostrar todos los estudiantes
// ------------------------------------------------------------------
void mostrarEstudiantes(const SistemaAcademico* sys) {
    if (sys->cantidad == 0) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }

    linea('=');
    cout << "\n  FICHAS DE ESTUDIANTES\n";
    linea('=');

    int numero = 1;
    // Recorrer con puntero a puntero
    Estudiante* const* ptr = sys->lista;
    for (int i = 0; i < sys->cantidad; i++, ptr++) {
        if (*ptr != nullptr && (*ptr)->activo)
            mostrarFicha(*ptr, numero++);
    }

    cout << "\n";
    linea('=');
    cout << "\n  Total: " << (numero - 1) << " estudiante(s).\n";
}

// ------------------------------------------------------------------
// Ingresar notas: asigna (o re-asigna) memoria dinamica de notas
// ------------------------------------------------------------------
void ingresarNotas(SistemaAcademico* sys) {
    if (sys->cantidad == 0) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }

    linea('=');
    cout << "\n  INGRESO DE NOTAS\n";
    linea('=');
    cout << "\n\n  Ingrese codigo del estudiante: ";

    string codigo;
    cin >> codigo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Buscar con puntero
    Estudiante* est = buscarPorCodigo(sys, codigo);

    if (est == nullptr) {
        cout << "\n  [X] Estudiante no encontrado.\n";
        return;
    }

    cout << "\n  [OK] Estudiante: " << est->nombre << "\n\n";

    int cantidad = leerEntero(
        "  Cuantas notas desea ingresar (1-4): ", 1, MAX_NOTAS
    );

    // MEMORIA DINAMICA: crear o re-crear el arreglo de notas
    redimensionarNotas(est, cantidad);

    // Llenar notas usando puntero
    Nota* nptr = est->notas;
    for (int j = 0; j < cantidad; j++, nptr++) {
        nptr->bimestre = j + 1;
        ostringstream prompt;
        prompt << "  Nota Bimestre " << (j + 1) << " (0-20): ";
        nptr->valor = leerFloat(prompt.str(), MIN_NOTA, MAX_NOTA);
        est->cantidadNotas++;
    }

    float prom = calcularPromedio(est->notas, est->cantidadNotas);
    cout << "\n";
    linea('=');
    cout << "\n  [OK] NOTAS REGISTRADAS\n";
    linea('=');
    cout << "\n  Promedio: " << fixed << setprecision(2)
         << prom << "  " << etiquetaEstado(prom) << "\n";
}

// ------------------------------------------------------------------
// Editar: nombre, grado o curso del estudiante
// ------------------------------------------------------------------
void editarEstudiante(SistemaAcademico* sys) {
    if (sys->cantidad == 0) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }

    linea('=');
    cout << "\n  EDITAR ESTUDIANTE\n";
    linea('=');
    cout << "\n\n  Ingrese codigo del estudiante: ";

    string codigo;
    cin >> codigo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Estudiante* est = buscarPorCodigo(sys, codigo);

    if (est == nullptr) {
        cout << "\n  [X] Estudiante no encontrado.\n";
        return;
    }

    cout << "\n  [OK] Encontrado: " << est->nombre << "\n\n";
    cout << "  [1] Cambiar nombre\n";
    cout << "  [2] Cambiar grado\n";
    cout << "  [3] Cambiar curso\n";
    cout << "  [4] Cancelar\n\n";

    int op = leerEntero("  >>> Opcion: ", 1, 4);

    switch (op) {
        case 1: {
            string nn = leerTexto(
                "  Nuevo nombre: ", esNombreValido,
                "Solo letras y espacios."
            );
            est->nombre = nn;
            cout << "\n  [OK] Nombre actualizado.\n";
            break;
        }
        case 2: {
            est->grado = leerEntero("  Nuevo grado (1-5): ", MIN_GRADO, MAX_GRADO);
            cout << "\n  [OK] Grado actualizado.\n";
            break;
        }
        case 3: {
            mostrarMenuCursos();
            int oc = leerEntero("  >>> Opcion (1-8): ", 1, TOTAL_CURSOS);
            est->curso = tablaCursos[oc - 1];
            cout << "\n  [OK] Curso actualizado: " << est->curso.nombre << "\n";
            break;
        }
        case 4:
            cout << "\n  [OK] Cancelado.\n";
    }
}

// ------------------------------------------------------------------
// Eliminar: libera la memoria del Estudiante y reorganiza la lista
// ------------------------------------------------------------------
void eliminarEstudiante(SistemaAcademico* sys) {
    if (sys->cantidad == 0) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }

    linea('=');
    cout << "\n  ELIMINAR ESTUDIANTE\n";
    linea('=');
    cout << "\n\n  [!] Esta accion libera la memoria del estudiante.\n\n";
    cout << "  Ingrese codigo del estudiante: ";

    string codigo;
    cin >> codigo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Buscar el indice del estudiante
    int indice = -1;
    for (int i = 0; i < sys->cantidad; i++) {
        if (sys->lista[i] != nullptr &&
            sys->lista[i]->activo &&
            sys->lista[i]->codigo == codigo)
        {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        cout << "\n  [X] Estudiante no encontrado.\n";
        return;
    }

    cout << "\n  [OK] Encontrado: " << sys->lista[indice]->nombre << "\n\n";
    cout << "  Confirmar eliminacion? (S/N): ";

    char conf;
    cin >> conf;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (conf != 'S' && conf != 's') {
        cout << "\n  [OK] Cancelado.\n";
        return;
    }

    // Liberar la memoria del Estudiante (y sus notas)
    liberarEstudiante(sys->lista[indice]);

    // Desplazar punteros con aritmetica de punteros
    Estudiante** actual    = sys->lista + indice;
    Estudiante** siguiente = actual + 1;

    for (int i = indice; i < sys->cantidad - 1; i++, actual++, siguiente++)
        *actual = *siguiente;     // desplaza el puntero

    *(sys->lista + sys->cantidad - 1) = nullptr;
    sys->cantidad--;

    cout << "\n";
    linea('=');
    cout << "\n  [OK] ESTUDIANTE ELIMINADO Y MEMORIA LIBERADA\n";
    linea('=');
    cout << "\n";
}
