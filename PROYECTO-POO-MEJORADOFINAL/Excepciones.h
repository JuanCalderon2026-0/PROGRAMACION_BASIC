#ifndef EXCEPCIONES_H
#define EXCEPCIONES_H

// ============================================================
//   EXCEPCIONES PERSONALIZADAS — Sistema Academico v3.0
//
//   Conceptos POO:
//     - Herencia de std::exception
//     - Clases de excepcion personalizadas
//     - Uso de what() virtual
//     - Jerarquia de excepciones propias
//     - Excepciones avanzadas (herencia entre ellas)
// ============================================================

#include <exception>
#include <string>
using namespace std;

// ============================================================
//   CLASE BASE: ExcepcionSistema
//   Hereda de std::exception — raiz de todas las excepciones
//   del sistema academico.
//   Concepto: Herencia de std::exception, override de what()
// ============================================================
class ExcepcionSistema : public exception {
protected:
    string mensaje;
public:
    explicit ExcepcionSistema(const string& msg) : mensaje(msg) {}
    virtual ~ExcepcionSistema() throw() {}

    // Sobreescritura del metodo virtual what() de std::exception
    // Concepto: Polimorfismo, override de metodo heredado
    virtual const char* what() const throw() override {
        return mensaje.c_str();
    }
};

// ============================================================
//   Excepcion: CodigoInvalidoException
//   Lanzada cuando el codigo de estudiante tiene formato incorrecto
//   Concepto: Excepcion personalizada derivada de ExcepcionSistema
// ============================================================
class CodigoInvalidoException : public ExcepcionSistema {
public:
    explicit CodigoInvalidoException(const string& codigo)
        : ExcepcionSistema("Codigo invalido: '" + codigo +
                           "'. Debe tener 5 digitos numericos.") {}
};

// ============================================================
//   Excepcion: CodigoDuplicadoException
//   Lanzada cuando se intenta registrar un codigo ya existente
// ============================================================
class CodigoDuplicadoException : public ExcepcionSistema {
public:
    explicit CodigoDuplicadoException(const string& codigo)
        : ExcepcionSistema("El codigo '" + codigo +
                           "' ya esta registrado en el sistema.") {}
};

// ============================================================
//   Excepcion: NombreInvalidoException
//   Lanzada cuando el nombre contiene caracteres no permitidos
// ============================================================
class NombreInvalidoException : public ExcepcionSistema {
public:
    explicit NombreInvalidoException(const string& nombre)
        : ExcepcionSistema("Nombre invalido: '" + nombre +
                           "'. Solo se permiten letras y espacios.") {}
};

// ============================================================
//   Excepcion: NotaFueraDeRangoException
//   Lanzada cuando una nota no esta en el rango [0, 20]
//   Concepto: Excepcion con datos adicionales (valor ingresado)
// ============================================================
class NotaFueraDeRangoException : public ExcepcionSistema {
private:
    float valorIngresado;
public:
    explicit NotaFueraDeRangoException(float val)
        : ExcepcionSistema("Nota fuera de rango: " + to_string(val) +
                           ". Debe estar entre 0.0 y 20.0."),
          valorIngresado(val) {}

    float getValorIngresado() const { return valorIngresado; }
};

// ============================================================
//   Excepcion: EstudianteNoEncontradoException
//   Lanzada cuando se busca un estudiante que no existe
// ============================================================
class EstudianteNoEncontradoException : public ExcepcionSistema {
public:
    explicit EstudianteNoEncontradoException(const string& codigo)
        : ExcepcionSistema("Estudiante con codigo '" + codigo +
                           "' no encontrado en el sistema.") {}
};

// ============================================================
//   Excepcion: ArchivoException
//   Lanzada cuando hay errores de lectura/escritura en archivos
//   Concepto: Excepcion especializada para operaciones de E/S
// ============================================================
class ArchivoException : public ExcepcionSistema {
public:
    explicit ArchivoException(const string& nombreArchivo, const string& operacion)
        : ExcepcionSistema("Error de archivo (" + operacion +
                           "): No se pudo acceder a '" + nombreArchivo + "'.") {}
};

// ============================================================
//   Excepcion: GradoInvalidoException
//   Lanzada cuando el grado no esta en el rango permitido [1,5]
// ============================================================
class GradoInvalidoException : public ExcepcionSistema {
public:
    explicit GradoInvalidoException(int grado)
        : ExcepcionSistema("Grado invalido: " + to_string(grado) +
                           ". Debe ser entre 1 y 5.") {}
};

#endif
