CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET  = sistema_academico

SRCS    = main.cpp \
          Nota.cpp \
          Curso.cpp \
          Persona.cpp \
          Estudiante.cpp \
          SistemaAcademico.cpp \
          GestorEstudiantes.cpp \
          Historial.cpp \
          Interfaz.cpp \
          Utilidades.cpp \
          Validacion.cpp \
          Archivos.cpp

OBJS    = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
