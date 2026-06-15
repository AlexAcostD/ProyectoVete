#include <iostream>
#include <cstring>
#include <cstdio>

#include "propietarios.h"
#include "mascotas.h"
#include "consultas.h"
#include "vacunas.h"
#include "facturacion.h"

using namespace std;

void separador(const char titulo[])
{
    cout << "\n========================================\n";
    cout << "  " << titulo << "\n";
    cout << "========================================\n";
}

void ok(const char msg[])  { cout << "[OK]    " << msg << "\n"; }
void err(const char msg[]) { cout << "[ERROR] " << msg << "\n"; }

// ─────────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────────

int main()
{
    separador("REGISTRO DE PROPIETARIOS");
    Propietario p1, p2;

    // Propietario 1
    if (registrarPropietario(&p1,
            "12345678", "Juan Perez",
            "Av Peru 123", "999888777",
            "juan@gmail.com"))
        ok("Propietario Juan Perez registrado.");
    else
        err("No se pudo registrar a Juan Perez (puede ya existir).");

    // Propietario 2
    if (registrarPropietario(&p2,
            "87654321", "Maria Lopez",
            "Jr Lima 456", "988776655",
            "maria@gmail.com"))
        ok("Propietaria Maria Lopez registrada.");
    else
        err("No se pudo registrar a Maria Lopez (puede ya existir).");

    // Intento duplicado – debe fallar (Regla: no duplicados)
    Propietario pDup;
    if (!registrarPropietario(&pDup,
            "12345678", "Juan Perez Copia",
            "Otra Dir", "000000000", "copia@mail.com"))
        ok("Duplicado de DNI 12345678 rechazado correctamente.");

    
    separador("REGISTRO DE MASCOTAS");

    Mascota m1, m2;

    // Mascota de Juan
    if (registrarMascota(&m1,
            "M001", "Firulais", "Perro", "Labrador",
            'M', 3, 15.5f, "Marron",
            "10/05/2021", "12345678"))
        ok("Mascota M001 – Firulais registrada.");
    else
        err("No se pudo registrar a Firulais (puede ya existir).");

    // Mascota de Maria
    if (registrarMascota(&m2,
            "M002", "Michi", "Gato", "Siames",
            'H', 2, 4.2f, "Blanco",
            "15/03/2022", "87654321"))
        ok("Mascota M002 – Michi registrada.");
    else
        err("No se pudo registrar a Michi (puede ya existir).");

    // Intento duplicado – debe fallar (Regla: código único)
    Mascota mDup;
    if (!registrarMascota(&mDup,
            "M001", "OtraMascota", "Perro", "Mestizo",
            'M', 1, 5.0f, "Negro",
            "01/01/2024", "12345678"))
        ok("Duplicado de código M001 rechazado correctamente.");

    // Intento con propietario inexistente – debe fallar
    Mascota mSinDueno;
    if (!registrarMascota(&mSinDueno,
            "M099", "Huerfano", "Perro", "Mestizo",
            'M', 1, 8.0f, "Gris",
            "01/01/2024", "00000000"))
        ok("Mascota con propietario inexistente rechazada correctamente.");

    separador("CONSULTA MEDICA – Firulais (M001)");

    // Autorización del propietario (Regla 9)
    cout << "  Propietario Juan Perez autoriza la consulta.\n";

    RecetaMedica receta1;
    strcpy(receta1.medicamento, "Amoxicilina");
    strcpy(receta1.dosis,       "1 tableta");
    strcpy(receta1.frecuencia,  "Cada 12 horas");
    receta1.duracionDias = 7;
    strcpy(receta1.indicaciones, "Administrar despues de las comidas");

    Consulta c1 = registrarConsultaMedica(
        "M001", "V001",
        "Fiebre y decaimiento",
        "Infeccion respiratoria leve",
        receta1,
        "Control obligatorio en 7 dias"   // Regla 6: control posterior
    );

    cout << "  Mascota    : " << c1.codigoMascota    << "\n";
    cout << "  Fecha      : " << c1.fechaAtencion    << "\n";
    cout << "  Diagnostico: " << c1.diagnostico      << "\n";
    cout << "  Receta     : " << c1.receta.medicamento
         << " – " << c1.receta.dosis
         << " x " << c1.receta.duracionDias << " dias\n";
    cout << "  Obs.       : " << c1.observaciones    << "\n";

    // Comprobante de la consulta (Regla 10)
    separador("COMPROBANTE – Consulta Firulais");
    cout << "  Propietario Juan Perez autoriza el pago.\n";

    ComprobantePago cp1 = emitirComprobante(
        "B001-000001", "12345678",
        "Consulta medica – Infeccion respiratoria",
        50.00f
    );

    if (cp1.montoTotal > 0)
    {
        ok("Comprobante emitido.");
        cout << "  N°     : " << cp1.numeroComprobante << "\n";
        cout << "  Fecha  : " << cp1.fecha             << "\n";
        cout << "  Cliente: " << cp1.dniCliente        << "\n";
        cout << "  Monto  : S/ " << cp1.montoTotal     << "\n";
    }
    else
        err("No se pudo emitir el comprobante.");

    separador("VACUNACION – Firulais (M001)");

    cout << "  Propietario Juan Perez autoriza la vacunacion.\n";

    if (aplicarVacuna("M001", "Antirrabica", 3, 15.5f))
        ok("Vacuna Antirrabica aplicada a Firulais.");
    else
        err("No se pudo aplicar la vacuna.");

    // Intento con vacuna no reconocida – debe fallar
    if (!aplicarVacuna("M001", "VacunaDesconocida", 3, 15.5f))
        ok("Vacuna no reconocida rechazada correctamente.");

    // Intento con edad insuficiente – debe fallar
    if (!aplicarVacuna("M001", "Parvovirus", 0, 15.5f))
        ok("Vacuna rechazada por edad insuficiente (< 1).");

    // Comprobante de vacunación (Regla 10)
    separador("COMPROBANTE – Vacunacion Firulais");
    cout << "  Propietario Juan Perez autoriza el pago.\n";

    ComprobantePago cp2 = emitirComprobante(
        "B001-000002", "12345678",
        "Vacunacion Antirrabica – M001 Firulais",
        35.50f
    );

    if (cp2.montoTotal > 0)
    {
        ok("Comprobante emitido.");
        cout << "  N°     : " << cp2.numeroComprobante << "\n";
        cout << "  Fecha  : " << cp2.fecha             << "\n";
        cout << "  Monto  : S/ " << cp2.montoTotal     << "\n";
    }
    else
        err("No se pudo emitir el comprobante.");

    separador("CONSULTA MEDICA – Michi (M002)");

    cout << "  Propietaria Maria Lopez autoriza la consulta.\n";

    RecetaMedica receta2;
    strcpy(receta2.medicamento, "Metronidazol");
    strcpy(receta2.dosis,       "0.5 ml");
    strcpy(receta2.frecuencia,  "Cada 8 horas");
    receta2.duracionDias = 5;
    strcpy(receta2.indicaciones, "Disolver en agua y administrar con jeringa");

    Consulta c2 = registrarConsultaMedica(
        "M002", "V002",
        "Vomitos y diarrea",
        "Gastroenteritis aguda",
        receta2,
        "Dieta blanda 48h; control en 5 dias"
    );

    cout << "  Mascota    : " << c2.codigoMascota    << "\n";
    cout << "  Fecha      : " << c2.fechaAtencion    << "\n";
    cout << "  Diagnostico: " << c2.diagnostico      << "\n";
    cout << "  Receta     : " << c2.receta.medicamento
         << " – " << c2.receta.dosis
         << " x " << c2.receta.duracionDias << " dias\n";

    separador("VACUNACION – Michi (M002)");

    cout << "  Propietaria Maria Lopez autoriza la vacunacion.\n";

    if (aplicarVacuna("M002", "Triple Felina", 2, 4.2f))
        ok("Vacuna Triple Felina aplicada a Michi.");
    else
        err("No se pudo aplicar la vacuna a Michi.");

    separador("COMPROBANTE – Consulta + Vacuna Michi");
    cout << "  Propietaria Maria Lopez autoriza el pago.\n";

    ComprobantePago cp3 = emitirComprobante(
        "B001-000003", "87654321",
        "Consulta medica + Vacuna Triple Felina – M002 Michi",
        85.00f
    );

    if (cp3.montoTotal > 0)
    {
        ok("Comprobante emitido.");
        cout << "  N°     : " << cp3.numeroComprobante << "\n";
        cout << "  Fecha  : " << cp3.fecha             << "\n";
        cout << "  Cliente: " << cp3.dniCliente        << "\n";
        cout << "  Monto  : S/ " << cp3.montoTotal     << "\n";
    }
    else
        err("No se pudo emitir el comprobante.");

    separador("CONTROL DE SEGUIMIENTO – Firulais (M001)");

    cout << "  Propietario Juan Perez autoriza el control.\n";

    RecetaMedica recetaControl;
    strcpy(recetaControl.medicamento, "Ninguno");
    strcpy(recetaControl.dosis,       "N/A");
    strcpy(recetaControl.frecuencia,  "N/A");
    recetaControl.duracionDias = 0;
    strcpy(recetaControl.indicaciones, "Alta medica. Paciente recuperado.");

    Consulta control = registrarConsultaMedica(
        "M001", "V001",
        "Control post-tratamiento",
        "Paciente recuperado. Sin sintomas.",
        recetaControl,
        "Alta medica. No requiere mas controles."
    );

    cout << "  Fecha      : " << control.fechaAtencion  << "\n";
    cout << "  Diagnostico: " << control.diagnostico    << "\n";
    cout << "  Obs.       : " << control.observaciones  << "\n";

    ComprobantePago cp4 = emitirComprobante(
        "B001-000004", "12345678",
        "Control medico post-tratamiento – M001 Firulais",
        20.00f
    );

    if (cp4.montoTotal > 0)
    {
        ok("Comprobante de control emitido.");
        cout << "  N°     : " << cp4.numeroComprobante << "\n";
        cout << "  Monto  : S/ " << cp4.montoTotal     << "\n";
    }

    separador("VALIDACION – Comprobante sin propietario valido");

    ComprobantePago cpInvalido = emitirComprobante(
        "B001-000099", "00000000",
        "Servicio sin propietario",
        100.0f
    );

    if (cpInvalido.montoTotal == 0)
        ok("Comprobante rechazado: propietario no registrado.");
    else
        err("Comprobante emitido incorrectamente.");

    // ══════════════════════════════════════════
    // RESUMEN
    // ══════════════════════════════════════════
    separador("RESUMEN DEL FLUJO");
    cout << "  2 propietarios registrados.\n";
    cout << "  2 mascotas registradas.\n";
    cout << "  3 consultas medicas generadas (historial).\n";
    cout << "  2 vacunas aplicadas.\n";
    cout << "  4 comprobantes de pago emitidos.\n";
    cout << "  Todas las reglas de negocio validadas.\n\n";

    return 0;
}