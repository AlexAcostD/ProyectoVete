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
                        listarPropietarios();
    }else{
                    cout << "Error al registrar propietario." << endl;
    }


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

do
{
    cout << "Sexo (M/H): ";
    cin >> sexo;
    sexo = toupper(sexo);
    if (sexo != 'M' && sexo != 'H')
    {
        cout << "Error. Solo puede ingresar M o H.\n";}
} while (sexo != 'M' && sexo != 'H');


while (true)
{
    cout << "Edad: ";
    if (cin >> edad && edad >= 0)
    { break;}
    cout << "Error. Ingrese una edad valida.\n";
    cin.clear();
    cin.ignore(1000, '\n');
}

while (true)
{
    cout << "Peso: ";
    if (cin >> peso && peso > 0)
    {break;}
    cout << "Error. Ingrese un peso valido.\n";
    cin.clear();
    cin.ignore(1000, '\n');
}
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
         listarMascotas();
    }
    else
    {
        cout << "\nError al registrar mascota.\n";
        cout << "Verifique que el codigo no exista y que el propietario este registrado.\n";
    }


}

void menuRegistrarConsulta()
{
    RecetaMedica receta;
    Consulta consulta;

    char codMascota[10];
    char codVeterinario[10];
    char motivo[100];
    char diagnostico[150];
    char observaciones[150];

    cout << "\n=== REGISTRAR CONSULTA MEDICA ===\n";

    cout << "Codigo Mascota: ";
    cin >> codMascota;

    cout << "Codigo Veterinario: ";
    cin >> codVeterinario;

    cin.ignore();

    cout << "Motivo: ";
    cin.getline(motivo,100);

    cout << "Diagnostico: ";
    cin.getline(diagnostico,150);

    cout << "\n=== RECETA ===\n";

    cout << "Medicamento: ";
    cin.getline(receta.medicamento,50);

    cout << "Dosis: ";
    cin.getline(receta.dosis,30);

    cout << "Frecuencia: ";
    cin.getline(receta.frecuencia,30);

    cout << "Observaciones: ";
    cin.getline(observaciones,150);

    consulta = registrarConsultaMedica(
        codMascota,
        codVeterinario,
        motivo,
        diagnostico,
        receta,
        observaciones
    );

    cout << "\nConsulta registrada correctamente.\n";
}

void menuAplicarVacuna()
{
    char codigoMascota[10];
    char nombreVacuna[30];

    int edad;
    float peso;

    cout << "\n=== APLICAR VACUNA ===\n";

    cout << "Codigo Mascota: ";
    cin >> codigoMascota;

    cin.ignore();

    cout << "Nombre Vacuna: ";
    cin.getline(nombreVacuna,30);



    if(
        aplicarVacuna(
            codigoMascota,
            nombreVacuna
        )
    )
    {
        cout << "\nVacuna aplicada correctamente.\n";
    }
    else
    {
        cout << "\nNo fue posible aplicar la vacuna.\n";
    }
}

void menuEmitirComprobante()
{
    ComprobantePago comprobante;

    char numero[20];
    char dni[9];
    char detalle[100];

    float monto;

    cout << "\n=== EMITIR COMPROBANTE ===\n";

    cout << "Numero Comprobante: ";
    cin >> numero;

    cout << "DNI Cliente: ";
    cin >> dni;

    cin.ignore();

    cout << "Detalle: ";
    cin.getline(detalle,100);

    cout << "Monto: ";
    cin >> monto;

    comprobante = emitirComprobante(
        numero,
        dni,
        detalle,
        monto
    );

    if(strlen(comprobante.numeroComprobante) == 0)
    {
        cout << "\nError al emitir comprobante.\n";
    }
    else
    {
        cout << "\nComprobante emitido correctamente.\n";
    }
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
        cout << "2. Listar Propietario" << endl;
        cout << "3. Registrar Mascota" << endl;
        cout << "4. Listar Mascota" << endl;
        cout << "5. Registrar Consultas Medicas" << endl;
        cout << "6. Registrar Vacuna" << endl;
        cout << "7. Emitir Comprobante de Pago" << endl;

        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                menuRegistrarPropietario(); 
                break;
            case 2:
                listarPropietarios();
                break;
            case 3:
                menuRegistrarMascotas();
                break;
            case 4:
                listarMascotas();
                break;
            case 5:
                menuRegistrarConsulta();
                break;
            case 6:
                menuAplicarVacuna();
                break;
            case 7:
                menuEmitirComprobante();
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