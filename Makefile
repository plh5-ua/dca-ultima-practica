# Nombre del compilador
CXX = g++

# Flags del compilador
CXXFLAGS = -Wall -Wextra -std=c++17

# Archivo fuente
SRC = codigo.cpp

# Archivo ejecutable
OUTPUT = codigo

# Regla por defecto
all: $(OUTPUT)

# Regla para compilar el ejecutable
$(OUTPUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SRC)

# Regla para limpiar archivos generados
clean:
	rm -f $(OUTPUT)

# Phony targets (no se asocian a archivos reales)
.PHONY: all clean
