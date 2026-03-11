CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET   = sistema_academico
OBJS     = main.o Persona.o Estudiante.o Curso.o Nota.o \
           SistemaAcademico.o GestorEstudiantes.o Historial.o \
           Archivos.o Interfaz.o Validacion.o Utilidades.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
