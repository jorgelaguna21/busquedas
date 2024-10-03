
#include <iostream>
#include <string>

// Definición de la clase persona
class persona {
public:
    std::string nombre;
    std::string carrera;
    int materiasAprobadas;
    float promedioGeneral;

    persona();  // Constructor por defecto
    persona(std::string n, std::string c, int materias, float promedio);  // Constructor con parámetros
    void operator=(const persona& x);  // Sobrecarga del operador de asignación

    friend std::ostream& operator<<(std::ostream& o, const persona& p);  // Sobrecarga del operador <<
    friend std::istream& operator>>(std::istream& o, persona& p);  // Sobrecarga del operador >>
};

// Implementación de la clase persona
persona::persona() : nombre("Jorge"), carrera("sin especificar"), materiasAprobadas(0), promedioGeneral(0.0) {}

persona::persona(std::string n, std::string c, int materias, float promedio)
    : nombre(n), carrera(c), materiasAprobadas(materias), promedioGeneral(promedio) {}

void persona::operator=(const persona& x) {
    nombre = x.nombre;
    carrera = x.carrera;
    materiasAprobadas = x.materiasAprobadas;
    promedioGeneral = x.promedioGeneral;
}

std::ostream& operator<<(std::ostream& o, const persona& p) {
    o << "Nombre: " << p.nombre << "\t Carrera: " << p.carrera
      << "\t Materias Aprobadas: " << p.materiasAprobadas
      << "\t Promedio General: " << p.promedioGeneral << std::endl;
    return o;
}

std::istream& operator>>(std::istream& o, persona& p) {
    std::cout << "\n Inserta nombre: ";
    o >> p.nombre;
    std::cout << "\n Inserta carrera: ";
    o >> p.carrera;
    std::cout << "\n Inserta total de materias aprobadas: ";
    o >> p.materiasAprobadas;
    std::cout << "\n Inserta promedio general: ";
    o >> p.promedioGeneral;
    return o;
}

// Definición de la clase Cola
class Cola {
private:
    static const int TAM = 100;  // Tamaño máximo de la cola
    persona datos[TAM];  // Arreglo de personas
    int frente = 0;  // Índice del frente de la cola
    int fin = -1;  // Índice del final de la cola

public:
    bool vacia() const;  // Verifica si la cola está vacía
    bool llena() const;  // Verifica si la cola está llena
    void enqueue(const persona& elem);  // Agrega un elemento a la cola
    persona dequeue();  // Retira un elemento de la cola

    bool elimina(int pos);  // Elimina un elemento en una posición específica
    int inserta(const persona& elem, int pos);  // Inserta un elemento en una posición específica
    int buscarSolicitud(const std::string& nombre) const;  // Busca una solicitud en la cola

    friend std::ostream& operator<<(std::ostream& o, const Cola& L);  // Sobrecarga del operador <<
};

// Implementación de la clase Cola
bool Cola::vacia() const {
    return frente > fin;
}

bool Cola::llena() const {
    return fin == TAM - 1;
}

void Cola::enqueue(const persona& elem) {
    if (llena()) {
        std::cout << "\n La cola está llena" << std::endl;
    } else {
        fin++;
        datos[fin] = elem;
    }
}

persona Cola::dequeue() {
    if (vacia()) {
        std::cout << "\n La cola está vacía" << std::endl;
        return persona();  // Devuelve una persona por defecto en caso de cola vacía
    } else {
        persona elem = datos[frente];
        frente++;
        return elem;
    }
}

bool Cola::elimina(int pos) {
    if (vacia() || pos < 0 || pos > fin) {
        std::cout << "\n error de eliminación";
        return true;
    }
    int i = pos;
    while (i < fin) {
        datos[i] = datos[i +  1];
        i++;
    }
    fin--;
    return false;
}

int Cola::inserta(const persona& elem, int pos) {
    if (llena() || pos < 0 || pos > fin + 1) {
        std::cout << "\n Error de inserción";
        return 0;
    }
    int i = fin + 1;
    while (i > pos) {
        datos[i] = datos[i - 1];
        i--;
    }
    datos[pos] = elem;
    fin++;
    return 1;
}

int Cola::buscarSolicitud(const std::string& nombre) const {
    int izq = frente;
    int der = fin;
    while (izq <= der) {
        int centro = (izq + der) / 2;
        if (datos[centro].nombre == nombre) {
            return centro;
        } else if (datos[centro].nombre < nombre) {
            izq = centro + 1;
        } else {
            der = centro - 1;
        }
    }
    return -1; // No se encontró la solicitud
}

std::ostream& operator<<(std::ostream& o, const Cola& L) {
    int i = L.frente;
    std::cout << "\n";
    while (i <= L.fin) {
        o << L.datos[i];
        i++;
    }
    return o;
}

// Función main
int main() {
    Cola colaSolicitudes;
    int opcion;
    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Dar de alta la solicitud de un alumno" << std::endl;
        std::cout << "2. Elaborar una constancia" << std::endl;
        std::cout << "3. Buscar una solicitud" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: // Dar de alta la solicitud de un alumno
                {
                    persona nuevoAlumno;
                    std::cin >> nuevoAlumno;
                    colaSolicitudes.enqueue(nuevoAlumno);
                    std::cout << "Solicitud de constancia encolada correctamente." << std::endl;
                }
                break;

            case 2: // Elaborar una constancia
                if (!colaSolicitudes.vacia()) {
                    persona alumnoAtendido = colaSolicitudes.dequeue();
                    std::cout << "Elaborando constancia para el siguiente alumno:" << std::endl;
                    std::cout << alumnoAtendido << std::endl;
                } else {
                    std::cout << "No hay solicitudes pendientes." << std::endl;
                }
                break;

            case 3: // Buscar una solicitud
                {
                    std::string nombreBuscar;
                    std::cout << "Ingrese el nombre del alumno a buscar: ";
                    std::cin.ignore(); // Ignorar el salto de línea
                    std::getline(std::cin, nombreBuscar);

                    int posicion = colaSolicitudes.buscarSolicitud(nombreBuscar);
                    if (posicion != -1) {
                        std::cout << "La solicitud del alumno se encuentra en la posicion " << posicion + 1 << std::endl;
                        std::cout << "Hay " << posicion << " solicitudes pendientes antes de la de este alumno." << std::endl;
                    } else {
                        std::cout << "No se encontró la solicitud del alumno." << std::endl;
                    }
                }
                break;

            case 4: // Salir
                std::cout << "Saliendo del programa." << std::endl;
                break;

            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
                break;
        }

    } while (opcion != 4);

    return 0;
}
