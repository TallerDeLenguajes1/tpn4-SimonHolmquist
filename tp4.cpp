#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define forn(i,n) for(int i=0;i<n;i++)
#define MAX 200

using namespace std;

struct Tarea{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
};

struct Nodo{
    Tarea T;
    Nodo *Siguiente;
};
 
void imprimirTitulo(char *s)
{
    int n = strlen(s)+4;
    cout<<'\n';
    forn(i,n) cout<<'*';
    cout<<"\n* "<<s<<" *\n";
    forn(i,n) cout<<'*';
    cout<<"\n\n";
}
void poner(Nodo **Tareas, Tarea nuevaTarea)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Tarea));
    nuevo->T = nuevaTarea;
    nuevo->Siguiente = *Tareas;
    *Tareas = nuevo;
}

Tarea sacar(Nodo **Tareas)
{
    Tarea aSacar = (*Tareas)->T;
    *Tareas = (*Tareas)->Siguiente;
    return aSacar;
}

void cargarTareas(Nodo **Tareas, int cantidadTareas)
{
    imprimirTitulo("Carga de tareas");
    forn(i, cantidadTareas)
    {
        Tarea nuevaTarea;
        cout<<"Tarea N°"<<i+1<<'\n';
        nuevaTarea.TareaID = i+1;
        nuevaTarea.Duracion = rand()%91+10;
        nuevaTarea.Descripcion = (char *)malloc(200*sizeof(char));
        cout<<"Por favor, ingrese la descripción de la tarea: ";
        cin.getline(nuevaTarea.Descripcion, 200);
        fflush(stdin);
        poner(Tareas, nuevaTarea);
    }
    imprimirTitulo("Tareas cargadas correctamente");
}

void mostrarTarea(Tarea aMostrar)
{
    cout<<"\nTarea ID: "<<aMostrar.TareaID<<'\n';
    cout<<"Descripción: "<<aMostrar.Descripcion<<'\n';
    cout<<"Duración: "<<aMostrar.Duracion<<'\n';
}

void checkeoDeTareas(Nodo **TareasPendientes, Nodo **TareasRealizadas)
{
    imprimirTitulo("Checkeo de tareas");
    int opcion;
    Nodo *pendientes = NULL;
    while(*TareasPendientes != NULL)
    {
        opcion = 0;
        mostrarTarea((*TareasPendientes)->T);
        cout<<"¿La tarea fue realizada? Elija la opción.\n1. SI\n2. NO\n";
        cin>>opcion;
        while(opcion!=1 && opcion!=2)
        {
            cout<<"La opción ingresada es incorrecta. Ingrese nuevamente.\n1. SI\n2. NO\n";
            cin>>opcion;
        }
        if(opcion == 1) poner(TareasRealizadas, sacar(TareasPendientes));
        else poner(&pendientes, sacar(TareasPendientes));
    }
    *TareasPendientes = pendientes;   
    imprimirTitulo("Tareas checkeadas correctamente");
}

void listarTareas(Nodo **Tareas)
{
    Nodo *aux = *Tareas;
    while(aux != NULL)
    {
        mostrarTarea(aux->T);
        aux = aux->Siguiente;
    }
}

Nodo* BusquedaPorPalabra(Nodo **Tareas)
{   
    imprimirTitulo("Busqueda por palabra clave");
    char *palabraClave = (char *)malloc(sizeof(char)*200);
    cout<<"Ingrese palabra clave: ";
    cin>>palabraClave;
    char *pos;
    Nodo *aux = *Tareas;
    while(aux != NULL)
    {
        pos = strstr(aux->T.Descripcion, palabraClave);
        if(pos != NULL){
            printf("Tarea encontrada.\n");
            return aux;
        }
        aux = aux->Siguiente;
    }
    return aux;
}

Nodo* BusquedaPorId(Nodo **Tareas)
{
    imprimirTitulo("Busqueda por ID");
    int TareaID;
    cout<<"Ingrese ID: ";
    cin>>TareaID;
    Nodo *aux = *Tareas;
    while(aux != NULL)
    {
        if(aux->T.TareaID == TareaID)
        {
            printf("Tarea encontrada.\n");
            return aux;
        }
        aux = aux->Siguiente;
    }
    cout<<"La tarea buscada no fue encontrada.\n";
    return aux;
}

int main(int argc, char const *argv[]){
    srand(time(0));
    imprimirTitulo("Módulo ToDo");
    int cantidadTareas;
    cout<<"Ingrese la cantidad de Tareas a cargar\n";
    cin>>cantidadTareas;
    fflush(stdin);
    Nodo *TareasPendientes = NULL;
    Nodo *TareasRealizadas = NULL;
    cargarTareas(&TareasPendientes, cantidadTareas);
    checkeoDeTareas(&TareasPendientes, &TareasRealizadas);
    imprimirTitulo("Tareas Realizadas");
    listarTareas(&TareasRealizadas);
    imprimirTitulo("Tareas Pendientes");
    listarTareas(&TareasPendientes);
    Nodo* tareaBuscada;
    tareaBuscada = BusquedaPorPalabra(&TareasPendientes);
    if(tareaBuscada != NULL) mostrarTarea(tareaBuscada->T);
    tareaBuscada = BusquedaPorId(&TareasPendientes);
    if(tareaBuscada != NULL) mostrarTarea(tareaBuscada->T);
    getchar();
    return 0;
}
