// ======================================================
// SISTEMA ACADEMICO PROFESIONAL - INTERFAZ MEJORADA
// Version con ASCII art compatible con todos los terminales
// ======================================================

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ctime>
#include <cctype>
#include <iomanip>

using namespace std;

// ================= CONSTANTES =================
const int MAX_ESTUDIANTES = 50;
const int MAX_NOTAS = 5;
const int MIN_GRADO = 1;
const int MAX_GRADO = 5;
const int MIN_NOTA = 0;
const int MAX_NOTA = 20;
const int LONGITUD_CODIGO = 10;

// ================= PROTOTIPOS =================

void cargarDatos(string[], string[], int[],
                 string[], string[], string[],
                 float[][MAX_NOTAS], int[],
                 int&);

void guardarDatos(string[], string[], int[],
                  string[], string[], string[],
                  float[][MAX_NOTAS], int[],
                  int);

void registrarEstudiante(string[], string[], int[],
                         string[], string[], string[],
                         int&);

void mostrarEstudiantes(string[], string[], int[],
                        string[], string[], string[],
                        float[][MAX_NOTAS], int[],
                        int);

void ingresarNotas(string[], float[][MAX_NOTAS], int[], int);
void calcularPromedios(string[], float[][MAX_NOTAS], int[], int);
void mostrarRanking(string[], string[], float[][MAX_NOTAS], int[], int);
void editarEstudiante(string[], string[], int[], string[], int);
void eliminarEstudiante(string[], string[], int[], string[], string[], 
                        string[], float[][MAX_NOTAS], int[], int&);

// Funciones auxiliares
bool codigoExiste(string[], string, int);
float calcularPromedio(float[], int);
string obtenerFechaHora();
string formatearNumero(int);
void pausar();
void limpiarPantalla();
void mostrarBanner();
void mostrarLinea(char, int);

// ================== MAIN ======================

int main() {

    string codigos[MAX_ESTUDIANTES];
    string nombres[MAX_ESTUDIANTES];
    int grados[MAX_ESTUDIANTES];
    string cursos[MAX_ESTUDIANTES];
    string profesores[MAX_ESTUDIANTES];
    string fechaRegistro[MAX_ESTUDIANTES];
    float notas[MAX_ESTUDIANTES][MAX_NOTAS];
    int cantidadNotas[MAX_ESTUDIANTES] = {0};
    int cantidadEstudiantes = 0;

    int opcion;

    cargarDatos(codigos, nombres, grados,
                cursos, profesores, fechaRegistro,
                notas, cantidadNotas,
                cantidadEstudiantes);

    do {
        limpiarPantalla();
        mostrarBanner();

        cout << "\n";
        mostrarLinea('=', 60);
        cout << "\n";
        cout << "                    MENU PRINCIPAL\n";
        mostrarLinea('=', 60);
        cout << "\n\n";
        
        cout << "  [1] Registrar Estudiante\n";
        cout << "  [2] Mostrar Fichas de Estudiantes\n";
        cout << "  [3] Ingresar Notas\n";
        cout << "  [4] Calcular Promedios\n";
        cout << "  [5] Mostrar Ranking\n";
        cout << "  [6] Editar Estudiante\n";
        cout << "  [7] Eliminar Estudiante\n";
        cout << "  [8] Guardar y Salir\n\n";
        
        mostrarLinea('-', 60);
        cout << "\n  >>> Seleccione una opcion: ";

        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n  [X] ERROR: Entrada invalida. Intente nuevamente.\n";
            pausar();
            continue;
        }

        limpiarPantalla();

        switch (opcion) {

            case 1:
                registrarEstudiante(codigos, nombres, grados,
                                    cursos, profesores, fechaRegistro,
                                    cantidadEstudiantes);
                pausar();
                break;

            case 2:
                mostrarEstudiantes(codigos, nombres, grados,
                                   cursos, profesores, fechaRegistro,
                                   notas, cantidadNotas,
                                   cantidadEstudiantes);
                pausar();
                break;

            case 3:
                ingresarNotas(codigos, notas,
                              cantidadNotas, cantidadEstudiantes);
                pausar();
                break;

            case 4:
                calcularPromedios(codigos, notas,
                                  cantidadNotas, cantidadEstudiantes);
                pausar();
                break;

            case 5:
                mostrarRanking(codigos, nombres,
                               notas, cantidadNotas,
                               cantidadEstudiantes);
                pausar();
                break;

            case 6:
                editarEstudiante(codigos, nombres, grados, cursos,
                                cantidadEstudiantes);
                pausar();
                break;

            case 7:
                eliminarEstudiante(codigos, nombres, grados, cursos,
                                  profesores, fechaRegistro, notas,
                                  cantidadNotas, cantidadEstudiantes);
                pausar();
                break;

            case 8:
                guardarDatos(codigos, nombres, grados,
                             cursos, profesores, fechaRegistro,
                             notas, cantidadNotas,
                             cantidadEstudiantes);
                limpiarPantalla();
                mostrarBanner();
                cout << "\n\n";
                mostrarLinea('=', 60);
                cout << "\n      DATOS GUARDADOS CORRECTAMENTE\n";
                cout << "      GRACIAS POR USAR EL SISTEMA\n";
                cout << "      HASTA PRONTO!\n";
                mostrarLinea('=', 60);
                cout << "\n\n";
                break;

            default:
                cout << "\n  [X] ERROR: Opcion invalida. Seleccione entre 1 y 8.\n";
                pausar();
        }

    } while (opcion != 8);

    return 0;
}

// ======================================================
// FUNCIONES DE INTERFAZ
// ======================================================

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void mostrarBanner() {
    cout << "\n";
    mostrarLinea('*', 60);
    cout << "\n";
    cout << "  *****  SISTEMA ACADEMICO PROFESIONAL  *****\n";
    cout << "  *                                          *\n";
    cout << "  *         GESTION DE ESTUDIANTES           *\n";
    cout << "  *                                          *\n";
    mostrarLinea('*', 60);
}

void mostrarLinea(char caracter, int longitud) {
    for (int i = 0; i < longitud; i++) {
        cout << caracter;
    }
}

void pausar() {
    cout << "\n";
    mostrarLinea('-', 60);
    cout << "\n  Presione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ======================================================
// REGISTRAR ESTUDIANTE
// ======================================================

void registrarEstudiante(string codigos[], string nombres[], int grados[],
                         string cursos[], string profesores[],
                         string fechaRegistro[],
                         int &cantidadEstudiantes)
{
    if (cantidadEstudiantes >= MAX_ESTUDIANTES) {
        cout << "\n  [X] ERROR: Limite de " << MAX_ESTUDIANTES 
             << " estudiantes alcanzado.\n";
        return;
    }

    int i = cantidadEstudiantes;
    string codigo;
    bool valido;

    mostrarLinea('=', 60);
    cout << "\n";
    cout << "           REGISTRO DE NUEVO ESTUDIANTE\n";
    mostrarLinea('=', 60);
    cout << "\n\n";

    // ============ CODIGO (10 DIGITOS, SIN DUPLICADOS) ============
    do {
        valido = true;
        cout << "  Codigo (" << LONGITUD_CODIGO << " digitos): ";
        cin >> codigo;

        if (codigo.length() != LONGITUD_CODIGO) {
            cout << "  [X] El codigo debe tener exactamente " 
                 << LONGITUD_CODIGO << " digitos.\n\n";
            valido = false;
            continue;
        }

        for (int j = 0; j < codigo.length(); j++) {
            if (!isdigit(codigo[j])) {
                cout << "  [X] El codigo solo puede contener digitos.\n\n";
                valido = false;
                break;
            }
        }

        if (valido && codigoExiste(codigos, codigo, cantidadEstudiantes)) {
            cout << "  [X] Este codigo ya esta registrado. Use otro.\n\n";
            valido = false;
        }

    } while (!valido);

    codigos[i] = codigo;
    cin.ignore();

    // ============ NOMBRE (SOLO LETRAS Y ESPACIOS) ============
    string nombre;

    do {
        valido = true;
        cout << "  Nombre completo: ";
        getline(cin, nombre);

        if (nombre.empty()) {
            cout << "  [X] El nombre no puede estar vacio.\n\n";
            valido = false;
            continue;
        }

        for (int j = 0; j < nombre.length(); j++) {
            if (!isalpha(nombre[j]) && nombre[j] != ' ') {
                cout << "  [X] El nombre solo puede contener letras y espacios.\n\n";
                valido = false;
                break;
            }
        }

    } while (!valido);

    nombres[i] = nombre;

    // ============ GRADO (1 A 5) ============
    do {
        cout << "  Grado (" << MIN_GRADO << "-" << MAX_GRADO << "): ";
        cin >> grados[i];

        if (cin.fail() || grados[i] < MIN_GRADO || grados[i] > MAX_GRADO) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [X] Debe ingresar un numero entre " << MIN_GRADO 
                 << " y " << MAX_GRADO << ".\n\n";
            grados[i] = 0;
        }

    } while (grados[i] < MIN_GRADO || grados[i] > MAX_GRADO);

    cin.ignore();

    // ============ SELECCION DE CURSO (1-8) ============
    int opcionCurso;

    cout << "\n";
    mostrarLinea('-', 60);
    cout << "\n               SELECCIONE EL CURSO\n";
    mostrarLinea('-', 60);
    cout << "\n\n";
    cout << "  [1] Matematica\n";
    cout << "  [2] Comunicacion\n";
    cout << "  [3] Historia\n";
    cout << "  [4] Educacion para el Trabajo\n";
    cout << "  [5] Religion\n";
    cout << "  [6] Educacion Fisica\n";
    cout << "  [7] Desarrollo Personal\n";
    cout << "  [8] Ingles\n\n";

    do {
        cout << "  >>> Opcion (1-8): ";
        cin >> opcionCurso;

        if (cin.fail() || opcionCurso < 1 || opcionCurso > 8) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [X] Debe seleccionar un numero entre 1 y 8.\n\n";
            opcionCurso = 0;
        }

    } while (opcionCurso < 1 || opcionCurso > 8);

    cin.ignore();

    // Asignación automática de curso y profesor
    switch (opcionCurso) {
        case 1:
            cursos[i] = "Matematica";
            profesores[i] = "Sofia Martinez Gonzalez";
            break;
        case 2:
            cursos[i] = "Comunicacion";
            profesores[i] = "Edwin Ramirez Lopez";
            break;
        case 3:
            cursos[i] = "Historia";
            profesores[i] = "Maximo Torres Ruiz";
            break;
        case 4:
            cursos[i] = "Educacion para el Trabajo";
            profesores[i] = "Lucas Fernandez Moreno";
            break;
        case 5:
            cursos[i] = "Religion";
            profesores[i] = "Isabella Morales Castro";
            break;
        case 6:
            cursos[i] = "Educacion Fisica";
            profesores[i] = "Mateo Castillo Jimenez";
            break;
        case 7:
            cursos[i] = "Desarrollo Personal";
            profesores[i] = "Camila Herrera Sanchez";
            break;
        case 8:
            cursos[i] = "Ingles";
            profesores[i] = "Sebastian Vargas Ortiz";
            break;
    }

    // Registro de fecha y hora
    fechaRegistro[i] = obtenerFechaHora();

    cantidadEstudiantes++;

    cout << "\n";
    mostrarLinea('=', 60);
    cout << "\n  [OK] ESTUDIANTE REGISTRADO EXITOSAMENTE!\n";
    mostrarLinea('=', 60);
    cout << "\n\n";
    cout << "  Codigo:   " << codigo << "\n";
    cout << "  Nombre:   " << nombre << "\n";
    cout << "  Curso:    " << cursos[i] << "\n";
    cout << "  Profesor: " << profesores[i] << "\n";
    cout << "  Fecha:    " << fechaRegistro[i] << "\n";
}

// ======================================================
// MOSTRAR ESTUDIANTES
// ======================================================

void mostrarEstudiantes(string codigos[], string nombres[], int grados[],
                        string cursos[], string profesores[],
                        string fechaRegistro[],
                        float notas[][MAX_NOTAS], int cantidadNotas[],
                        int cantidadEstudiantes)
{
    if (cantidadEstudiantes == 0) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }

    mostrarLinea('=', 60);
    cout << "\n";
    cout << "              FICHAS DE ESTUDIANTES\n";
    mostrarLinea('=', 60);
    cout << "\n";

    for (int i = 0; i < cantidadEstudiantes; i++) {

        cout << "\n";
        mostrarLinea('-', 60);
        cout << "\n  ESTUDIANTE #" << (i + 1) << "\n";
        mostrarLinea('-', 60);
        cout << "\n";
        cout << "  Codigo:     " << codigos[i] << "\n";
        cout << "  Nombre:     " << nombres[i] << "\n";
        cout << "  Grado:      " << grados[i] << " de Secundaria\n";
        cout << "  Curso:      " << cursos[i] << "\n";
        cout << "  Profesor:   " << profesores[i] << "\n";
        cout << "  Registrado: " << fechaRegistro[i] << "\n";

        if (cantidadNotas[i] > 0) {
            cout << "  Notas:      ";
            for (int j = 0; j < cantidadNotas[i]; j++) {
                cout << fixed << setprecision(1) << notas[i][j];
                if (j < cantidadNotas[i] - 1) cout << " | ";
            }
            cout << "\n";
            
            float promedio = calcularPromedio(notas[i], cantidadNotas[i]);
            cout << "  Promedio:   " << fixed << setprecision(2) << promedio;
            
            if (promedio >= 14) {
                cout << " [APROBADO]";
            } else if (promedio >= 11) {
                cout << " [RECUPERACION]";
            } else {
                cout << " [DESAPROBADO]";
            }
            cout << "\n";
        } else {
            cout << "  Notas:      Sin notas registradas\n";
        }

        mostrarLinea('-', 60);
    }
}

// ======================================================
// INGRESAR NOTAS
// ======================================================

void ingresarNotas(string codigos[], float notas[][MAX_NOTAS],
                   int cantidadNotas[], int cantidadEstudiantes)
{
    if (cantidadEstudiantes == 0) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }

    string codigo;
    
    mostrarLinea('=', 60);
    cout << "\n";
    cout << "                 INGRESO DE NOTAS\n";
    mostrarLinea('=', 60);
    cout << "\n\n";
    cout << "  Ingrese codigo del estudiante: ";
    cin >> codigo;

    for (int i = 0; i < cantidadEstudiantes; i++) {

        if (codigos[i] == codigo) {

            cout << "\n  [OK] Estudiante encontrado: " << codigo << "\n\n";

            int cantidad;

            // ============ VALIDAR CANTIDAD DE NOTAS (1-5) ============
            do {
                cout << "  Cuantas notas desea ingresar (1-" << MAX_NOTAS << "): ";
                cin >> cantidad;

                if (cin.fail() || cantidad < 1 || cantidad > MAX_NOTAS) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "  [X] Debe ingresar un numero entre 1 y " << MAX_NOTAS << ".\n\n";
                    cantidad = 0;
                }

            } while (cantidad < 1 || cantidad > MAX_NOTAS);

            cantidadNotas[i] = cantidad;

            cout << "\n";

            // ============ VALIDAR CADA NOTA (0-20, PERMITE DECIMALES) ============
            for (int j = 0; j < cantidadNotas[i]; j++) {

                float nota;

                do {
                    cout << "  Nota #" << (j + 1) << " (" << MIN_NOTA << "-" 
                         << MAX_NOTA << "): ";
                    cin >> nota;

                    if (cin.fail() || nota < MIN_NOTA || nota > MAX_NOTA) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "  [X] La nota debe estar entre " << MIN_NOTA 
                             << " y " << MAX_NOTA << ".\n\n";
                        nota = -1;
                    }

                } while (nota < MIN_NOTA || nota > MAX_NOTA);

                notas[i][j] = nota;
            }

            float promedio = calcularPromedio(notas[i], cantidadNotas[i]);

            cout << "\n";
            mostrarLinea('=', 60);
            cout << "\n  [OK] NOTAS REGISTRADAS CORRECTAMENTE\n";
            mostrarLinea('=', 60);
            cout << "\n";
            cout << "  Promedio calculado: " << fixed << setprecision(2) 
                 << promedio << "\n";
            return;
        }
    }

    cout << "\n  [X] ERROR: Estudiante no encontrado.\n";
}

// ======================================================
// CALCULAR PROMEDIOS
// ======================================================

void calcularPromedios(string codigos[], float notas[][MAX_NOTAS],
                       int cantidadNotas[], int cantidadEstudiantes)
{
    if (cantidadEstudiantes == 0) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }

    mostrarLinea('=', 60);
    cout << "\n";
    cout << "            PROMEDIOS DE ESTUDIANTES\n";
    mostrarLinea('=', 60);
    cout << "\n\n";

    bool hayNotasRegistradas = false;

    for (int i = 0; i < cantidadEstudiantes; i++) {

        if (cantidadNotas[i] == 0)
            continue;

        hayNotasRegistradas = true;

        float promedio = calcularPromedio(notas[i], cantidadNotas[i]);

        cout << "  Codigo: " << setw(12) << left << codigos[i]
             << " | Promedio: " << fixed << setprecision(2) << setw(6) << promedio;

        if (promedio >= 14) {
            cout << " [APROBADO]";
        } else if (promedio >= 11) {
            cout << " [RECUPERACION]";
        } else {
            cout << " [DESAPROBADO]";
        }

        cout << "\n";
    }

    if (!hayNotasRegistradas) {
        cout << "  [!] Ningun estudiante tiene notas registradas.\n";
    }
}

// ======================================================
// MOSTRAR RANKING
// ======================================================

void mostrarRanking(string codigos[], string nombres[],
                    float notas[][MAX_NOTAS], int cantidadNotas[],
                    int cantidadEstudiantes)
{
    if (cantidadEstudiantes == 0) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }

    mostrarLinea('=', 60);
    cout << "\n";
    cout << "               RANKING ACADEMICO\n";
    mostrarLinea('=', 60);
    cout << "\n";

    // Crear arreglos para ordenar
    string nombresCopia[MAX_ESTUDIANTES];
    string codigosCopia[MAX_ESTUDIANTES];
    float promedios[MAX_ESTUDIANTES];
    int contador = 0;

    // Copiar solo estudiantes con notas
    for (int i = 0; i < cantidadEstudiantes; i++) {
        if (cantidadNotas[i] > 0) {
            nombresCopia[contador] = nombres[i];
            codigosCopia[contador] = codigos[i];
            promedios[contador] = calcularPromedio(notas[i], cantidadNotas[i]);
            contador++;
        }
    }

    if (contador == 0) {
        cout << "\n  [!] Ningun estudiante tiene notas registradas.\n";
        return;
    }

    // Ordenamiento burbuja (de mayor a menor)
    for (int i = 0; i < contador - 1; i++) {
        for (int j = 0; j < contador - i - 1; j++) {
            if (promedios[j] < promedios[j + 1]) {
                // Intercambiar promedios
                float tempProm = promedios[j];
                promedios[j] = promedios[j + 1];
                promedios[j + 1] = tempProm;

                // Intercambiar nombres
                string tempNom = nombresCopia[j];
                nombresCopia[j] = nombresCopia[j + 1];
                nombresCopia[j + 1] = tempNom;

                // Intercambiar códigos
                string tempCod = codigosCopia[j];
                codigosCopia[j] = codigosCopia[j + 1];
                codigosCopia[j + 1] = tempCod;
            }
        }
    }

    // Mostrar ranking ordenado
    cout << "\n";
    cout << "  +------+------------+----------------------+-----------+\n";
    cout << "  | Pos. |   Codigo   |       Nombre         | Promedio  |\n";
    cout << "  +------+------------+----------------------+-----------+\n";

    for (int i = 0; i < contador; i++) {
        cout << "  | " << setw(4) << right << (i + 1) << " | ";
        cout << setw(10) << left << codigosCopia[i] << " | ";
        
        string nombreCorto = nombresCopia[i];
        if (nombreCorto.length() > 20) {
            nombreCorto = nombreCorto.substr(0, 17) + "...";
        }
        cout << setw(20) << left << nombreCorto << " | ";
        cout << setw(9) << right << fixed << setprecision(2) << promedios[i] << " |\n";
    }

    cout << "  +------+------------+----------------------+-----------+\n";

    // Mostrar medallas
    if (contador >= 1) {
        cout << "\n";
        mostrarLinea('*', 60);
        cout << "\n  *** PRIMER LUGAR: " << nombresCopia[0] 
             << " (" << fixed << setprecision(2) << promedios[0] << ")\n";
    }
    if (contador >= 2) {
        cout << "  **  SEGUNDO LUGAR: " << nombresCopia[1] 
             << " (" << fixed << setprecision(2) << promedios[1] << ")\n";
    }
    if (contador >= 3) {
        cout << "  *   TERCER LUGAR: " << nombresCopia[2] 
             << " (" << fixed << setprecision(2) << promedios[2] << ")\n";
        mostrarLinea('*', 60);
    }
}

// ======================================================
// EDITAR ESTUDIANTE
// ======================================================

void editarEstudiante(string codigos[], string nombres[], int grados[],
                     string cursos[], int cantidadEstudiantes)
{
    if (cantidadEstudiantes == 0) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }

    string codigo;
    
    mostrarLinea('=', 60);
    cout << "\n";
    cout << "               EDITAR ESTUDIANTE\n";
    mostrarLinea('=', 60);
    cout << "\n\n";
    cout << "  Ingrese codigo del estudiante: ";
    cin >> codigo;

    for (int i = 0; i < cantidadEstudiantes; i++) {
        if (codigos[i] == codigo) {
            cout << "\n  [OK] Estudiante encontrado.\n";
            cout << "  Nombre actual: " << nombres[i] << "\n\n";
            
            cin.ignore();
            
            string nuevoNombre;
            bool valido;
            
            do {
                valido = true;
                cout << "  Nuevo nombre (Enter para mantener): ";
                getline(cin, nuevoNombre);
                
                if (nuevoNombre.empty()) {
                    cout << "\n  [OK] Nombre sin cambios.\n";
                    return;
                }
                
                for (int j = 0; j < nuevoNombre.length(); j++) {
                    if (!isalpha(nuevoNombre[j]) && nuevoNombre[j] != ' ') {
                        cout << "  [X] El nombre solo puede contener letras y espacios.\n\n";
                        valido = false;
                        break;
                    }
                }
                
            } while (!valido);
            
            nombres[i] = nuevoNombre;
            
            cout << "\n";
            mostrarLinea('=', 60);
            cout << "\n  [OK] ESTUDIANTE ACTUALIZADO CORRECTAMENTE\n";
            mostrarLinea('=', 60);
            cout << "\n";
            return;
        }
    }
    
    cout << "\n  [X] ERROR: Estudiante no encontrado.\n";
}

// ======================================================
// ELIMINAR ESTUDIANTE
// ======================================================

void eliminarEstudiante(string codigos[], string nombres[], int grados[],
                       string cursos[], string profesores[], string fechaRegistro[],
                       float notas[][MAX_NOTAS], int cantidadNotas[],
                       int &cantidadEstudiantes)
{
    if (cantidadEstudiantes == 0) {
        cout << "\n  [!] No hay estudiantes registrados.\n";
        return;
    }

    string codigo;
    
    mostrarLinea('=', 60);
    cout << "\n";
    cout << "              ELIMINAR ESTUDIANTE\n";
    mostrarLinea('=', 60);
    cout << "\n\n";
    cout << "  [!] ADVERTENCIA: Esta accion no se puede deshacer.\n\n";
    cout << "  Ingrese codigo del estudiante: ";
    cin >> codigo;

    for (int i = 0; i < cantidadEstudiantes; i++) {
        if (codigos[i] == codigo) {
            cout << "\n  [OK] Estudiante encontrado: " << nombres[i] << "\n\n";
            
            char confirmacion;
            cout << "  Confirma eliminacion? (S/N): ";
            cin >> confirmacion;
            
            if (confirmacion != 'S' && confirmacion != 's') {
                cout << "\n  [OK] Operacion cancelada.\n";
                return;
            }
            
            // Desplazar todos los elementos
            for (int j = i; j < cantidadEstudiantes - 1; j++) {
                codigos[j] = codigos[j + 1];
                nombres[j] = nombres[j + 1];
                grados[j] = grados[j + 1];
                cursos[j] = cursos[j + 1];
                profesores[j] = profesores[j + 1];
                fechaRegistro[j] = fechaRegistro[j + 1];
                cantidadNotas[j] = cantidadNotas[j + 1];
                
                for (int k = 0; k < MAX_NOTAS; k++) {
                    notas[j][k] = notas[j + 1][k];
                }
            }
            
            cantidadEstudiantes--;
            
            cout << "\n";
            mostrarLinea('=', 60);
            cout << "\n  [OK] ESTUDIANTE ELIMINADO CORRECTAMENTE\n";
            mostrarLinea('=', 60);
            cout << "\n";
            return;
        }
    }
    
    cout << "\n  [X] ERROR: Estudiante no encontrado.\n";
}

// ======================================================
// FUNCIONES AUXILIARES
// ======================================================

bool codigoExiste(string codigos[], string codigo, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        if (codigos[i] == codigo) {
            return true;
        }
    }
    return false;
}

float calcularPromedio(float notas[], int cantidad) {
    if (cantidad == 0) return 0.0;
    
    float suma = 0;
    for (int i = 0; i < cantidad; i++) {
        suma += notas[i];
    }
    
    return suma / cantidad;
}

string obtenerFechaHora() {
    time_t ahora = time(0);
    tm *ltm = localtime(&ahora);

    return formatearNumero(ltm->tm_mday) + "/" +
           formatearNumero(1 + ltm->tm_mon) + "/" +
           to_string(1900 + ltm->tm_year) + " " +
           formatearNumero(ltm->tm_hour) + ":" +
           formatearNumero(ltm->tm_min);
}

string formatearNumero(int num) {
    if (num < 10) {
        return "0" + to_string(num);
    }
    return to_string(num);
}

// ======================================================
// CARGAR DATOS
// ======================================================

void cargarDatos(string codigos[], string nombres[], int grados[],
                 string cursos[], string profesores[],
                 string fechaRegistro[],
                 float notas[][MAX_NOTAS], int cantidadNotas[],
                 int &cantidadEstudiantes)
{
    ifstream archivo("datos.txt");

    if (!archivo) {
        return;
    }

    archivo >> cantidadEstudiantes;
    archivo.ignore();

    for (int i = 0; i < cantidadEstudiantes; i++) {

        archivo >> codigos[i];
        archivo.ignore();

        getline(archivo, nombres[i]);
        archivo >> grados[i];
        archivo.ignore();

        getline(archivo, cursos[i]);
        getline(archivo, profesores[i]);
        getline(archivo, fechaRegistro[i]);

        archivo >> cantidadNotas[i];

        for (int j = 0; j < cantidadNotas[i]; j++)
            archivo >> notas[i][j];
        
        archivo.ignore();
    }

    archivo.close();
}

// ======================================================
// GUARDAR DATOS
// ======================================================

void guardarDatos(string codigos[], string nombres[], int grados[],
                  string cursos[], string profesores[],
                  string fechaRegistro[],
                  float notas[][MAX_NOTAS], int cantidadNotas[],
                  int cantidadEstudiantes)
{
    ofstream archivo("datos.txt");

    if (!archivo) {
        cout << "  [X] ERROR: No se pudo guardar los datos.\n";
        return;
    }

    archivo << cantidadEstudiantes << endl;

    for (int i = 0; i < cantidadEstudiantes; i++) {

        archivo << codigos[i] << endl;
        archivo << nombres[i] << endl;
        archivo << grados[i] << endl;
        archivo << cursos[i] << endl;
        archivo << profesores[i] << endl;
        archivo << fechaRegistro[i] << endl;
        archivo << cantidadNotas[i] << endl;

        for (int j = 0; j < cantidadNotas[i]; j++)
            archivo << notas[i][j] << " ";

        archivo << endl;
    }

    archivo.close();
}