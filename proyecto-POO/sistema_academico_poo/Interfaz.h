#ifndef INTERFAZ_H
#define INTERFAZ_H

// ============================================================
//   CLASE: Interfaz
//   Gestiona la presentacion visual del sistema.
//   Concepto POO: Abstraccion, Clases con metodos estaticos
// ============================================================
class Interfaz {
public:
    static void linea(char c = '=', int n = 62);
    static void limpiarPantalla();
    static void pausar();
    static void mostrarBanner();
    static void mostrarMenu();
};

#endif
