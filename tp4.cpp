#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define forn(i,n) for(int i=0;i<n;i++)
#define MAX 200

using namespace std;

struct Tarea
{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}; 

void imprimirTitulo(char *s)
{
    int n = strlen(s)+4;
    forn(i,n) cout<<'*';
    cout<<"\n* "<<s<<" *\n";
    forn(i,n) cout<<'*';
    cout<<"\n\n";
}

void cargarTareas(Tarea **Tareas, int cantidadTareas)
{
    imprimirTitulo("Carga de tareas");
    forn(i, cantidadTareas)
    {
        Tareas[i] = (Tarea *)malloc(sizeof(Tarea));
        cout<<"Tarea N°"<<i+1<<'\n';
        Tareas[i]->TareaID = i+1;
        Tareas[i]->Duracion = rand()%91+10;
        Tareas[i]->Descripcion = (char *)malloc(200*sizeof(char));
        cout<<"Por favor, ingrese la descripción de la tarea: ";
        cin.getline(Tareas[i]->Descripcion, 200);
        fflush(stdin);
    }
    imprimirTitulo("Tareas cargadas correctamente");
}

void mostrarTarea(Tarea aMostrar)
{
    cout<<"\nTarea ID: "<<aMostrar.TareaID<<'\n';
    cout<<"Descripción: "<<aMostrar.Descripcion<<'\n';
    cout<<"Duración: "<<aMostrar.Duracion<<'\n';
}

void checkeoDeTareas(Tarea **TareasPendientes, Tarea **TareasRealizadas, int cantidadTareas)
{
    imprimirTitulo("Checkeo de tareas");
    int opcion;
    forn(i, cantidadTareas)
    {
        opcion = 0;
        mostrarTarea(*TareasPendientes[i]);
        cout<<"¿La tarea fue realizada? Elija la opción.\n1. SI\n2. NO\n";
        cin>>opcion;
        while(opcion!=1 && opcion!=2)
        {
            cout<<"La opción ingresada es incorrecta. Ingrese nuevamente.\n1. SI\n2. NO\n";
            cin>>opcion;
        }
        if(opcion == 1)
        {
            TareasRealizadas[i] = TareasPendientes[i];
            TareasPendientes[i] = NULL;
        }
        else TareasRealizadas[i] = NULL;
    }
    imprimirTitulo("Tareas checkeadas correctamente");
}

void listarTareas(Tarea **Tareas, int cantidadTareas)
{
    forn(i, cantidadTareas)
    {
        if(Tareas[i] != NULL) mostrarTarea(*Tareas[i]);
    }
}

Tarea* BusquedaPorPalabra(Tarea **Tareas, int cantidadTareas)
{   
    imprimirTitulo("Busqueda por palabra clave");
    char *palabraClave = (char *)malloc(sizeof(char)*200);
    cout<<"Ingrese palabra clave: ";
    cin>>palabraClave;
    char *pos;
    forn(i, cantidadTareas)
    {
        if(Tareas[i] != NULL)
        {
            pos = strstr(Tareas[i]->Descripcion, palabraClave);
            if(pos != NULL){
                printf("Tarea encontrada.\n");
                return Tareas[i];
            }
        }
    }
    cout<<"La tarea buscada no fue encontrada.\n";
    return NULL;
}

Tarea* BusquedaPorId(Tarea **Tareas, int cantidadTareas)
{
    imprimirTitulo("Busqueda por ID");
    int TareaID;
    cout<<"Ingrese ID: ";
    cin>>TareaID;
    forn(i, cantidadTareas)
    {
        if(Tareas[i] != NULL)
        {
            if(Tareas[i]->TareaID == TareaID)
            {
                printf("Tarea encontrada.\n");
                return Tareas[i];
            }
        }
    }
    cout<<"La tarea buscada no fue encontrada.\n";
    return NULL;
}

int main(int argc, char const *argv[]){
    srand(time(0));
    imprimirTitulo("Módulo ToDo");
    int cantidadTareas;
    cout<<"Ingrese la cantidad de Tareas a cargar\n";
    cin>>cantidadTareas;
    fflush(stdin);
    Tarea **TareasPendientes = (Tarea **)malloc(cantidadTareas*sizeof(Tarea*));
    Tarea **TareasRealizadas = (Tarea **)malloc(cantidadTareas*sizeof(Tarea*));
    cargarTareas(TareasPendientes, cantidadTareas);
    checkeoDeTareas(TareasPendientes, TareasRealizadas, cantidadTareas);
    imprimirTitulo("Tareas Realizadas");
    listarTareas(TareasRealizadas, cantidadTareas);
    imprimirTitulo("Tareas Pendientes");
    listarTareas(TareasPendientes, cantidadTareas);
    Tarea *tareaBuscada = (Tarea *)malloc(sizeof(Tarea));
    tareaBuscada = BusquedaPorPalabra(TareasPendientes, cantidadTareas);
    if(tareaBuscada != NULL) mostrarTarea(*tareaBuscada);
    tareaBuscada = BusquedaPorId(TareasPendientes, cantidadTareas);
    if(tareaBuscada != NULL) mostrarTarea(*tareaBuscada);
    free(TareasPendientes);
    free(TareasRealizadas);
    getchar();
    return 0;
}
