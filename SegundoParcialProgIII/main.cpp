//Incluyo todos los headers y la librerias.
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Headers/Lista.h"
#include "Headers/HashMap.h"
#include "Headers/Casos.h"
#include "Headers/Provincias.h"

using namespace std;

void Estadisticas(string); //Funcion que se encarga de desarrollar los puntos para -estad

void QuickSortProvincia(Provincia[], int, int);//Quicksort específico para Clase Provincia;

void QuickSortCasos(Casos[], int, int);//Quicksort específico para Clase Casos;

void
P_CasosOFallecidos(string, int, int);//Funcion que se encarga de desarrollar los puntos para -p_casos[n] y -p_muertes[n]

void Casos_CUI(string, string fecha); //Funcion que se encarga de desarrollar los puntos para -casos_cui[fecha]

void Casos_Edad(string, int);//Funcion que se encarga de desarrollar los puntos para -casos_edad[anios]


int main(int argc, char **argv) {
    int provinciaTotal = 0; //Contador por defecto para el numero de provincias
    string fecha = "2019-01-01"; //Una fecha "Por defecto" para luego poder comparar
    string path = argv[argc - 1]; //El path siempre se envía como último argumento
    //Reviso que argumentos me envian y de acuerdo a eso vamos a trabajar
    for (int i = 1; i < argc - 1; i++) {
        string arg = argv[i]; //creo un nuevo string para poder ir controlando los argumentos
        if (arg == "-estad") {//controlamos -estad
            Estadisticas(path);//llamamos a la función encargada de las estadisticas
        } else {
            if (arg == "-p_casos") {//controlamos -p_casos
                try {
                    provinciaTotal = stoi(argv[i + 1]); //El numero de provincias tiene que ser siempre el argumento que le sigue a "-p_casos", por eso reviso con i+1
                    i++;//si encuentro un numero de provincias, no necesito revisar el argumento siguiente poruqe ya sé que se trata de este numero, por lo que lo salteo
                }
                catch (...) {
                    provinciaTotal = 24;//en caso de no sea un numero el argumento que sigue, muestro las 23 provincias y CABA
                }
                P_CasosOFallecidos(path, provinciaTotal, 1);// Llamo a la funcion que se encarga de -p_casos, bajo la situacion de contagiados y no de fallecidos
            } else {
                if (arg == "-p_muertes") {
                    //repito el proceso de -p_casos
                    try {
                        provinciaTotal = stoi(argv[i + 1]);
                        i++;
                    }
                    catch (...) {
                        provinciaTotal = 24;
                    }
                    P_CasosOFallecidos(path, provinciaTotal, 2);// Llamo a la funcion que se encarga de -p_casos, bajo la situacion de fallecidos y no de contagiados
                } else {
                    if (arg == "-casos_cui") {
                        if (argv[i + 1][0] == '2') { // Reviso si el argumento siguiente a -casos_cui es una fecha, solo funciona para fechas mayores o iguales al 2000
                            fecha = argv[i + 1];
                            i++;
                        }
                        Casos_CUI(path, fecha);//Llamo a la funcion encargada de -casos_cui
                    } else {
                        if (arg == "-casos_edad") {
                            int edad = 0;// auxiliar para la edad
                            try {
                                edad = stoi(argv[i + 1]);
                                i++;
                            }
                            catch (...) {
                                throw "error"; //estan obligados a pasarme una edad, pero igualmente lo controlo
                            }
                            Casos_Edad(path, edad);//Llamo a la función encargadad de -casos_edad
                        } else {
                            cout << "Argumento erroneo";//muestro mensaje por pantalla en caso de que algun argumento sea erroneo
                        }
                    }
                }
            }

        }
    }
    cout<<"La tarea finalizó"<<endl;//Un simple mensaje para que no termine con "Process finished with exit code 0"
    return 0;//Finalizo el programa
}


void Estadisticas(string path) {
    fstream fin;
    fin.open(path, ios::in);
    float Contagiados = 0, Fallecidos = 0;
    float cantcasos = 0;
    //Establezco dos Arrays para así poder contar la cantidad de Casos
    double EdadConfirmado[10];//0-9/10-19/20-29/30-39/40-49/50-59/60-69/70-79/80-89/90-99
    double EdadFallecido[10];//0-9/10-19/20-29/30-39/40-49/50-59/60-69/70-79/80-89/90-99
    Casos casos;
    for (int k = 0; k < 10; k++) {//Igualo a cero todas las posiciones de los array a fin de evitar basura
        EdadConfirmado[k] = 0;
        EdadFallecido[k] = 0;
    }
    if (fin.fail()) {
        cout << "No se pudo abrir el csv" << endl;
    } else {
        string line;
        getline(fin, line);
        while (getline(fin, line)) {
            casos.ProcesarDato(line);//Este es un método que reemplaza todos los valores de la clase, de esta forma solo ocupo lugar para un objeto de clase que voy sobreescribiendo
            cantcasos++;//aumento el contador de casos, sin importar si finalmente fue contagiado o no
            if (casos.clasificacion() == "Confirmado") {
                Contagiados++;//Ahora aumento el numero de contagiados
                if (casos.Anios_Meses() == "Meses") {
                    EdadConfirmado[0]++;
                } else {
                    EdadConfirmado[casos.edad() / 10]++;//aumento en 1 el contador para la respectiva edad (10/10= 1 ||19/10=1.9=1 por ser int)
                }
            } else {
                if (casos.fallecido() == "SI") {
                    Fallecidos++; // aumento el numero de fallecidos
                    if (casos.Anios_Meses() == "Meses") {
                        EdadFallecido[0]++;
                    } else {
                        EdadFallecido[casos.edad() / 10]++;//aumento en 1 el contador para la respectiva edad
                    }
                }
            }
        }
    }
    float PorcentajeFallecidos = ((Fallecidos / Contagiados) * 100), PorcentajeContagiados = ((Contagiados / cantcasos) * 100);//creo dos variables para los porcentajes
    //Muestra de Datos
    cout << "Cantidad total de muestras: " << cantcasos << endl;
    cout << "Cantidad total de contagiados: " << Contagiados << endl;
    cout << "Cantidad total de fallecidos: " << Fallecidos << endl;
    cout << "Porcentaje de Contagiados: " << PorcentajeContagiados << "%" << endl;
    cout << "Porcentaje de Fallecidos respecto de Contagiados: " << PorcentajeFallecidos << "%" << endl;
    cout << "La cantidad de Contagiados:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "Entre " << i * 10 << " y " << (i * 10) + 9 << " anios es: " << EdadConfirmado[i] << endl;
    }
    cout << "La cantidad de Fallecidos:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "Entre " << i * 10 << " y " << (i * 10) + 9 << " anios es: " << EdadFallecido[i] << endl;
    }
}

void P_CasosOFallecidos(string path, int numprovincias, int situacion) {//Es para -pcasosedad
    const string ListaProvincias[] = {"CABA", "Buenos Aires", "Catamarca", "Chaco", "Chubut", "Córdoba", " Corrientes",
                                      "Entre Ríos", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones",
                                      "Neuquén", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe",
                                      "Santiago del Estero", "Tierra del Fuego", "Tucumán"};
    Provincia ProvinciasContagiado[24];
    Provincia ProvinciasFallecido[24];
    for (int i = 0; i < 24; i++) {
        ProvinciasContagiado[i] = Provincia(ListaProvincias[i], 0);
        ProvinciasFallecido[i] = Provincia(ListaProvincias[i], 0);
    }
    fstream fin;
    fin.open(path, ios::in);
    Casos casos;
    if (fin.fail()) {
        cout << "No se pudo abrir el csv" << endl;
    } else {
        string line;
        getline(fin, line);
        while (getline(fin, line)) {
            casos.ProcesarDato(line);
            if (situacion == 1) {
                if (casos.clasificacion() == "Confirmado") {
                    for (int k = 0; k < 24; k++) {
                        if (casos.provincia() == ProvinciasContagiado[k].getNombre()) {
                            ProvinciasContagiado[k].IncrementarContador();
                            break;
                        }
                    }
                }
            } else {
                if (casos.fallecido() == "SI") {
                    casos.ProcesarDato(line);
                    for (int k = 0; k < 24; k++) {
                        if (casos.provincia() == ProvinciasFallecido[k].getNombre()) {
                            ProvinciasFallecido[k].IncrementarContador();
                            break;
                        }
                    }
                }
            }
        }
        if (situacion == 1) {
            QuickSortProvincia(ProvinciasContagiado, 0, 23);
            cout << "Casos confirmados por provincias: " << endl;
            for (int i = 0; i < numprovincias; i++) {
                cout << ProvinciasContagiado[i] << endl;
            }
        } else {
            QuickSortProvincia(ProvinciasFallecido, 0, 23);
            cout << "Casos fallecidos por Provincia: " << endl;
            for (int i = 0; i < numprovincias; i++) {
                cout << ProvinciasFallecido[i] << endl;
            }
        }
    }
}

unsigned int miHF(string provincia) {
    const string ListaProvincias[] = {"Buenos Aires", "CABA", "Catamarca", "Chaco", "Chubut", "Córdoba", " Corrientes",
                                      "Entre Ríos", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones",
                                      "Neuquén", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe",
                                      "Santiago del Estero", "Tierra del Fuego", "Tucumán", "Sin Provincia"};
    for (int i = 0; i < 25; i++) {
        if (provincia == ListaProvincias[i]) {
            return i;
        }
    }
}

void Casos_Edad(string path, int anios) {
    const string ListaProvincias[] = {"Buenos Aires", "CABA", "Catamarca", "Chaco", "Chubut", "Córdoba", " Corrientes",
                                      "Entre Ríos", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones",
                                      "Neuquén", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe",
                                      "Santiago del Estero", "Tierra del Fuego", "Tucumán", "Sin Provincia"};
    HashMap<string, Casos> HashCasos(25, miHF);
    Casos casos;
    fstream fin;
    fin.open(path, ios::in);
    HashEntry<string, Casos> *aux;
    if (fin.fail()) {
        cout << "No se pudo abrir el csv" << endl;
    } else {
        string line;
        getline(fin, line);
        while (getline(fin, line)) {
            casos.ProcesarDato(line);
            if (casos.Anios_Meses() == "Años" && casos.edad() == anios && casos.clasificacion() == "Confirmado") {
                HashCasos.put(casos.provincia(), casos);
            }
        }
        for (int i = 0; i < 25; i++) {
            try {
                aux = HashCasos.get(ListaProvincias[i]);
                cout << "La lista de la provincia: " << ListaProvincias[i] << endl;
                while (aux != nullptr) {
                    cout << aux->getData() << endl;
                    aux = aux->getnext();
                }
            } catch (int e) {
                cout << "La Provincia: " << ListaProvincias[i] << " esta vacia" << endl;
            }
        }
    }
}


void Casos_CUI(string path, string fecha) {
    Lista<Casos> ListaCUI;
    Casos casos;
    fstream fin;
    fin.open(path, ios::in);
    if (fin.fail()) {
        cout << "No se pudo abrir el csv" << endl;
    } else {
        string line;
        getline(fin, line);
        while (getline(fin, line)) {
            casos.ProcesarDato(line);
            if (casos.Cui() == "SI" && casos.Fecha_CUI() > fecha) {
                ListaCUI.insertarPrimero(casos);
            }
        }
        Casos ArrayCasos[ListaCUI.getTamanio()];
        for (int i = 0; i < ListaCUI.getTamanio(); i++) {
            ArrayCasos[i] = ListaCUI.getDato(i);
        }
        QuickSortCasos(ArrayCasos, 0, ListaCUI.getTamanio());
        cout << "Casos mayores a " << fecha << " en orden:" << endl;
        for (int i = 0; i < ListaCUI.getTamanio(); i++) {
            if (ArrayCasos[i] > fecha) {
                cout << ArrayCasos[i] << endl;
            }
        }
    }
}


void QuickSortProvincia(Provincia a[], int primero, int ultimo) {
    int i, j, central;
    Provincia pivote, aux;
    central = (primero + ultimo) / 2;
    pivote = a[central];
    i = primero;
    j = ultimo;
    do {
        while (a[i] > pivote) i++;
        while (a[j] < pivote) j--;
        if (i <= j) {
            aux = a[i];
            a[i] = a[j];
            a[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);
    if (primero < j) QuickSortProvincia(a, primero, j); // mismo proceso con sublista izqda
    if (i < ultimo) QuickSortProvincia(a, i, ultimo); // mismo proceso con sublista drcha
}

void QuickSortCasos(Casos a[], int primero, int ultimo) {
    int i, j, central;
    Casos pivote, aux;
    central = (primero + ultimo) / 2;
    pivote = a[central];
    i = primero;
    j = ultimo;
    do {
        while (a[i] < pivote) i++;
        while (a[j] > pivote) j--;
        if (i <= j) {
            aux = a[i];
            a[i] = a[j];
            a[j] = aux;
            i++;
            j--;
        }
    } while (i <= j);
    if (primero < j)
        QuickSortCasos(a, primero, j); // mismo proceso con sublista izqda
    if (i < ultimo)
        QuickSortCasos(a, i, ultimo); // mismo proceso con sublista drcha
}

