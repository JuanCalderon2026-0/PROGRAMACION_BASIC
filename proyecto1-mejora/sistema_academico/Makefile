# ============================================================
#   Makefile - Sistema Academico Profesional v3.0
# ============================================================

CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET   = sistema_academico

# Lista de todos los archivos objeto
OBJS = main.o \
       interfaz.o \
       validacion.o \
       utilidades.o \
       busqueda.o \
       memoria.o \
       estudiantes.o \
       reportes.o \
       archivos.o \
       historial.o

# Regla principal: compilar el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo ""
	@echo "  [OK] Compilacion exitosa: ./$(TARGET)"
	@echo ""

# Reglas de compilacion por modulo
main.o:         main.cpp definiciones.h interfaz.h memoria.h estudiantes.h reportes.h archivos.h
	$(CXX) $(CXXFLAGS) -c main.cpp

interfaz.o:     interfaz.cpp interfaz.h utilidades.h
	$(CXX) $(CXXFLAGS) -c interfaz.cpp

validacion.o:   validacion.cpp validacion.h
	$(CXX) $(CXXFLAGS) -c validacion.cpp

utilidades.o:   utilidades.cpp utilidades.h definiciones.h interfaz.h
	$(CXX) $(CXXFLAGS) -c utilidades.cpp

busqueda.o:     busqueda.cpp busqueda.h definiciones.h
	$(CXX) $(CXXFLAGS) -c busqueda.cpp

memoria.o:      memoria.cpp memoria.h definiciones.h interfaz.h
	$(CXX) $(CXXFLAGS) -c memoria.cpp

estudiantes.o:  estudiantes.cpp estudiantes.h interfaz.h validacion.h utilidades.h busqueda.h memoria.h
	$(CXX) $(CXXFLAGS) -c estudiantes.cpp

reportes.o:     reportes.cpp reportes.h interfaz.h utilidades.h busqueda.h
	$(CXX) $(CXXFLAGS) -c reportes.cpp

archivos.o:     archivos.cpp archivos.h memoria.h definiciones.h
	$(CXX) $(CXXFLAGS) -c archivos.cpp

historial.o:    historial.cpp historial.h utilidades.h interfaz.h
	$(CXX) $(CXXFLAGS) -c historial.cpp

# Limpiar archivos objeto y ejecutable
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "  [OK] Limpieza completada."

# Compilar y ejecutar directamente
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
