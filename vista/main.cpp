#define _HAS_STD_BYTE 0
#include <iostream>
#include <limits>
#include <regex>
#include <string>
#include <ctime>
#include "Estudiante.h"
using namespace std;

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

// Prototipos de funciones auxiliares de validación
bool validarCodigo(const string& codigo, int id_actual = -1);
bool validarNombresApellidos(const string& texto, bool esNombre);
bool validarDireccion(const string& direccion);
bool validarTelefono(const string& telefonoStr);
bool validarFechaNacimiento(const string& fecha);
bool validarIdTipoSangre(int id_tipo_sangre);
bool existeCodigoEnBD(const string& codigo, int id_excluir = -1);
bool existeTipoSangreEnBD(int id_tipo_sangre);

// Prototipo de listado
void listarTodosLosEstudiantes();

int main() {
    int opcion;
    do {
        cout << "\n==============================\n";
        cout << "   MENU PRINCIPAL - ESTUDIANTES\n";
        cout << "==============================\n";
        cout << "1. Insertar nuevo estudiante\n";
        cout << "2. Buscar estudiante por ID\n";
        cout << "3. Actualizar datos de estudiante\n";
        cout << "4. Eliminar estudiante\n";
        cout << "5. Listar todos los estudiantes\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
        case 1: {
            string codigo, nombres, apellidos, direccion, telefonoStr, fecha_nacimiento;
            int id_tipo_sangre;
            bool datosValidos = true;

            cout << "\n--- INSERTAR ESTUDIANTE ---\n";

            // --- Código ---
            do {
                cout << "Codigo (formato E001, max 4 caracteres): ";
                getline(cin, codigo);
                if (!validarCodigo(codigo)) {
                    cout << "Error: Codigo invalido o duplicado. Debe ser E001, E002, etc. Max 4 caracteres.\n";
                    datosValidos = false;
                }
                else {
                    datosValidos = true;
                    break;
                }
            } while (true);

            // --- Nombres ---
            do {
                cout << "Nombres (solo letras y espacios, max 60): ";
                getline(cin, nombres);
                if (!validarNombresApellidos(nombres, true)) {
                    cout << "Error: Nombres invalidos. Solo letras y espacios, max 60 caracteres.\n";
                }
                else break;
            } while (true);

            // --- Apellidos ---
            do {
                cout << "Apellidos (solo letras y espacios, max 60): ";
                getline(cin, apellidos);
                if (!validarNombresApellidos(apellidos, false)) {
                    cout << "Error: Apellidos invalidos. Solo letras y espacios, max 60 caracteres.\n";
                }
                else break;
            } while (true);

            // --- Dirección ---
            do {
                cout << "Direccion (max 100 caracteres, sin caracteres peligrosos): ";
                getline(cin, direccion);
                if (!validarDireccion(direccion)) {
                    cout << "Error: Direccion invalida (vacia o contiene caracteres peligrosos).\n";
                }
                else break;
            } while (true);

            // --- Teléfono ---
            do {
                cout << "Telefono (8 digitos, solo numeros): ";
                getline(cin, telefonoStr);
                if (!validarTelefono(telefonoStr)) {
                    cout << "Error: Telefono invalido. Deben ser exactamente 8 digitos numericos.\n";
                }
                else break;
            } while (true);

            // --- Fecha de nacimiento ---
            do {
                cout << "Fecha nacimiento (AAAA-MM-DD): ";
                getline(cin, fecha_nacimiento);
                if (!validarFechaNacimiento(fecha_nacimiento)) {
                    cout << "Error: Fecha invalida (formato AAAA-MM-DD, fecha real, no futura).\n";
                }
                else break;
            } while (true);

            // --- Tipo de sangre ---
            do {
                cout << "ID Tipo Sangre (numero existente en catalogo): ";
                cin >> id_tipo_sangre;
                cin.ignore();
                if (!validarIdTipoSangre(id_tipo_sangre)) {
                    cout << "Error: ID de tipo de sangre no existe en la tabla tipos_sangre.\n";
                }
                else break;
            } while (true);

            // Si todas las validaciones pasan, crear estudiante
            Estudiante e(nombres, apellidos, direccion, stoi(telefonoStr), fecha_nacimiento,
                id_tipo_sangre, codigo, 0);
            e.crear();
            e.leer();
            break;
        }

        case 2: {
            int id;
            cout << "\n--- BUSCAR ESTUDIANTE ---\n";
            cout << "Ingrese el ID a buscar: ";
            cin >> id;
            cin.ignore();
            Estudiante e;
            e.setId_estudiante(id);
            e.leer();
            break;
        }

        case 3: {
            int id;
            string codigo, nombres, apellidos, direccion, telefonoStr, fecha_nacimiento;
            int id_tipo_sangre;

            cout << "\n--- ACTUALIZAR ESTUDIANTE ---\n";
            cout << "ID del estudiante a modificar: ";
            cin >> id;
            cin.ignore();

            // --- Código (validando unicidad excluyendo el propio ID) ---
            do {
                cout << "Nuevo codigo (formato E001): ";
                getline(cin, codigo);
                if (!validarCodigo(codigo, id)) {
                    cout << "Error: Codigo invalido o ya existe en otro registro.\n";
                }
                else break;
            } while (true);

            // --- Nombres ---
            do {
                cout << "Nuevos nombres: ";
                getline(cin, nombres);
                if (!validarNombresApellidos(nombres, true)) {
                    cout << "Error: Nombres invalidos.\n";
                }
                else break;
            } while (true);

            // --- Apellidos ---
            do {
                cout << "Nuevos apellidos: ";
                getline(cin, apellidos);
                if (!validarNombresApellidos(apellidos, false)) {
                    cout << "Error: Apellidos invalidos.\n";
                }
                else break;
            } while (true);

            // --- Dirección ---
            do {
                cout << "Nueva direccion: ";
                getline(cin, direccion);
                if (!validarDireccion(direccion)) {
                    cout << "Error: Direccion invalida.\n";
                }
                else break;
            } while (true);

            // --- Teléfono ---
            do {
                cout << "Nuevo telefono (8 digitos): ";
                getline(cin, telefonoStr);
                if (!validarTelefono(telefonoStr)) {
                    cout << "Error: Telefono invalido.\n";
                }
                else break;
            } while (true);

            // --- Fecha nacimiento ---
            do {
                cout << "Nueva fecha nacimiento (AAAA-MM-DD): ";
                getline(cin, fecha_nacimiento);
                if (!validarFechaNacimiento(fecha_nacimiento)) {
                    cout << "Error: Fecha invalida.\n";
                }
                else break;
            } while (true);

            // --- Tipo sangre ---
            do {
                cout << "Nuevo ID tipo sangre: ";
                cin >> id_tipo_sangre;
                cin.ignore();
                if (!validarIdTipoSangre(id_tipo_sangre)) {
                    cout << "Error: Tipo de sangre no existe.\n";
                }
                else break;
            } while (true);

            Estudiante e;
            e.setId_estudiante(id);
            e.setCodigo(codigo);
            e.setNombres(nombres);
            e.setApellidos(apellidos);
            e.setDireccion(direccion);
            e.setTelefono(stoi(telefonoStr));
            e.setFecha_nacimiento(fecha_nacimiento);
            e.setId_tipo_sangre(id_tipo_sangre);
            e.actualizar();
            e.leer();
            break;
        }

        case 4: {
            int id;
            cout << "\n--- ELIMINAR ESTUDIANTE ---\n";
            cout << "ID del estudiante a eliminar: ";
            cin >> id;
            cin.ignore();
            Estudiante e;
            e.setId_estudiante(id);
            e.borrar();
            cout << "Despues de la eliminacion:\n";
            e.leer();
            break;
        }

        case 5:
            cout << "\n--- LISTADO DE TODOS LOS ESTUDIANTES ---\n";
            listarTodosLosEstudiantes();
            break;

        case 6:
            cout << "Saliendo del programa...\n";
            break;

        default:
            cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 6);

    return 0;
}

// --------------------------------------------------------------
//  IMPLEMENTACIÓN DE LAS FUNCIONES DE VALIDACIÓN
// --------------------------------------------------------------

bool validarCodigo(const string& codigo, int id_actual) {
    // 1. No vacío
    if (codigo.empty()) return false;
    // 2. Máximo 4 caracteres
    if (codigo.length() > 4) return false;
    // 3. Formato EXXX (expresión regular)
    regex pattern("^E[0-9]{3}$");
    if (!regex_match(codigo, pattern)) return false;
    // 4. No duplicado (excepto el mismo id en actualización)
    return !existeCodigoEnBD(codigo, id_actual);
}

bool validarNombresApellidos(const string& texto, bool esNombre) {
    if (texto.empty()) return false;
    if (texto.length() > 60) return false;
    // Solo letras (incluyendo ñ, Ñ, acentos) y espacios
    regex pattern("^[A-Za-záéíóúÁÉÍÓÚñÑ ]+$");
    return regex_match(texto, pattern);
}

bool validarDireccion(const string& direccion) {
    if (direccion.empty()) return false;
    if (direccion.length() > 100) return false;
    // Evitar caracteres peligrosos para SQL: ' " ; -- etc.
    if (direccion.find('\'') != string::npos ||
        direccion.find('"') != string::npos ||
        direccion.find(';') != string::npos ||
        direccion.find("--") != string::npos) {
        return false;
    }
    return true;
}

bool validarTelefono(const string& telefonoStr) {
    if (telefonoStr.empty()) return false;
    // Verificar que todos sean dígitos
    for (char c : telefonoStr) {
        if (!isdigit(c)) return false;
    }
    // Longitud exacta de 8 dígitos (ajustable)
    return telefonoStr.length() == 8;
}
bool validarFechaNacimiento(const string& fecha) {
    regex pattern("^([0-9]{4})-([0-9]{2})-([0-9]{2})$");
    smatch match;
    if (!regex_match(fecha, match, pattern)) return false;

    int anio = stoi(match[1]);
    int mes = stoi(match[2]);
    int dia = stoi(match[3]);

    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;

    int diasPorMes[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (mes == 2) {
        bool bisiesto = (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
        if (bisiesto) diasPorMes[1] = 29;
    }
    if (dia > diasPorMes[mes - 1]) return false;

    // Obtener fecha actual de forma segura
    time_t t = time(nullptr);
    struct tm fechaActual;
    localtime_s(&fechaActual, &t);  // Usar localtime_s

    int anioActual = fechaActual.tm_year + 1900;
    int mesActual = fechaActual.tm_mon + 1;
    int diaActual = fechaActual.tm_mday;

    if (anio > anioActual) return false;
    if (anio == anioActual && mes > mesActual) return false;
    if (anio == anioActual && mes == mesActual && dia > diaActual) return false;

    return true;
}
bool validarIdTipoSangre(int id_tipo_sangre) {
    // Validar que sea un número positivo y exista en la tabla tipos_sangre
    if (id_tipo_sangre <= 0) return false;
    return existeTipoSangreEnBD(id_tipo_sangre);
}

// --------------------------------------------------------------
//  FUNCIONES QUE DEBES IMPLEMENTAR EN LA LÓGICA DE BD
// --------------------------------------------------------------

bool existeCodigoEnBD(const string& codigo, int id_excluir) {
    // Esta función debe consultar la base de datos para verificar si
    // ya existe un estudiante con el mismo código (excepto el que tiene id_excluir).
    // Retorna true si existe, false si no.
    // Ejemplo (con SQLite, MySQL, etc.):
    // SELECT COUNT(*) FROM estudiantes WHERE codigo = ? AND id_estudiante != ?
    // Si el conteo > 0 → existe.
    // Por ahora, placeholder:
    return false;  // Cambiar por consulta real
}

bool existeTipoSangreEnBD(int id_tipo_sangre) {
    // Consultar la tabla tipos_sangre:
    // SELECT COUNT(*) FROM tipos_sangre WHERE id_tipo_sangre = ?
    // Retorna true si existe.
    return true;  // Cambiar por consulta real
}

void listarTodosLosEstudiantes() {
    Estudiante e;
    e.leer();
}