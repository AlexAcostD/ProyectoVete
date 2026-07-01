#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

#include "propietarios.h"
#include "mascotas.h"
#include "consultas.h"
#include "vacunas.h"
#include "facturacion.h"
using namespace std;
bool login(const char* username, const char* contraseña){
    char contraseña_correcta[] = "1234";
    char USERNAME_correcta[]="PC1-IS";
    if (strcmp(username, USERNAME_correcta) == 0 && strcmp(contraseña, contraseña_correcta) == 0) {
        return true;
    } else {
        return false;
    }
}

void menuRegistrarPropietario(){
    Propietario propietario;
    char dni[9];
    char nombres[100];
    char direccion[100];
    char telefono[20];
    char correo[100];

    cout << "\n=== REGISTRAR PROPIETARIO ===\n";

    cout << "DNI: ";
    cin >> dni;
    cin.ignore();
    cout << "Nombres: ";
    cin.getline(nombres, 100);
    cout << "Direccion: ";
    cin.getline(direccion, 100);
    cout << "Telefono: ";
    cin.getline(telefono, 20);
    cout << "Correo: ";
    cin.getline(correo, 100);

    if (registrarPropietario(&propietario,dni,nombres,direccion,telefono,correo)){
                    cout << "Propietario registrado." << endl;
    }else{
                    cout << "Error al registrar propietario." << endl;
    }
    listarPropietarios();

}

void menuRegistrarMascotas()
{
    Mascota mascota;

    char codigo[20];
    char nombre[100];
    char especie[50];
    char raza[50];
    char sexo;
    int edad;
    float peso;
    char color[50];
    char fechaNac[20];
    char dniProp[9];


    cout << "\n=== REGISTRAR MASCOTA ===\n";

    cout << "Codigo de mascota: ";
    cin >> codigo;

    cin.ignore();

    cout << "Nombre: ";
    cin.getline(nombre, 100);

    cout << "Especie: ";
    cin.getline(especie, 50);

    cout << "Raza: ";
    cin.getline(raza, 50);

    cout << "Sexo (M/H): ";
    cin >> sexo;

    cout << "Edad: ";
    cin >> edad;

    cout << "Peso: ";
    cin >> peso;

    cin.ignore();

    cout << "Color: ";
    cin.getline(color, 50);

    cout << "Fecha nacimiento (dd/mm/aaaa): ";
    cin.getline(fechaNac, 20);

    cout << "DNI del propietario: ";
    cin.getline(dniProp, 9);



    if(registrarMascota(
            &mascota,
            codigo,
            nombre,
            especie,
            raza,
            sexo,
            edad,
            peso,
            color,
            fechaNac,
            dniProp))
    {
        cout << "\nMascota registrada correctamente.\n";
    }
    else
    {
        cout << "\nError al registrar mascota.\n";
        cout << "Verifique que el codigo no exista y que el propietario este registrado.\n";
    }


    listarMascotas();
}

int main(){
    int opcion;
    char USERNAME[20];
    char contraseña[20];
    cout << "===== SISTEMA DE GESTION VETERINARIA =====" << endl;
    cout << "Ingrese su USERNAME: ";
    cin >> USERNAME;    
    cout << "Ingrese su contraseña: ";
    cin >> contraseña;  

    if (login(USERNAME, contraseña)){
        cout << "Login exitoso." << endl;
    }
    else
    {
        cout << "Login fallido. Saliendo..." << endl;
        return 0;
    }

    do
    {
        cout << "\n===== MENU PRINCIPAL =====" << endl;
        cout << "1. Registrar Propietario" << endl;
        cout << "2. Registrar Mascota" << endl;
        cout << "3. Registrar Consultas Medicas" << endl;
        cout << "4. Registrar Vacuna" << endl;
        cout << "5. Emitir Comprobante de Pago" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
            {
                menuRegistrarPropietario(); 
                break;
            }

            case 2:
                menuRegistrarMascotas();
                break;

            case 3:
                cout << "Registrar Consulta" << endl;
                break;

            case 4:
                cout << "Registrar Vacuna" << endl;
                break;

            case 5:
                cout << "Emitir Comprobante" << endl;
                
                
                break;
            case 0:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opcion no valida." << endl;
        }

    } while (opcion != 0);

    return 0;
}