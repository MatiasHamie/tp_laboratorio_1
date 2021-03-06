/*
*********************************************
*       TRABAJO PRACTICO NRO 2              *
*       Desarrollo de funciones             *
*   Materia: Laboratorio de programacion 1  *
*   Alumno: Hamie Matias                    *
*   Curso: 1 'G'                            *
*                                           *
*********************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

//Libreria con funciones obligatorias y extras
#include "arrayEmployees.h"
#include "validaciones.h"

/*
    Declaro las palabras EMPTY para el valor 1
    y OCCUPIED para el valor 0 las cuales seran
    utilizadas para validar empleados dados de alta
*/
#define EMPTY 1
#define OCCUPIED 0

int initEmployees(Employee* employees, int lengthEmp){
    for(int i=0;i<lengthEmp;i++){
        employees[i].isEmpty=EMPTY;
    }
    return 0;
}

void hardcodeEmployees(Employee* employees, int lengthEmp){
    Employee auxEmp[12]={
//    ID    Name      LastName    Salary  Sector  IsEmpty
    {1092,"Matias",   "Hamie",    25000,    1,       0},
    {1123,"Juan",     "Diaz",     25124,    2,       0},
    {1241,"Martin",   "Fernandez",25123,    1,       0},
    {1232,"Sabrina",  "Carrasco", 27918,    3,       0},
    {1541,"Alejandra","Salerno",  30000,    1,       0},
    {1142,"Marcos",   "Riso",     21023,    2,       0},
    {1985,"Jesica",   "Gauto",    41020,    4,       0},
    {2003,"Nicolas",  "Pardo",    40123,    5,       0},
    {2010,"Bruno",    "Mujica",   33653,    2,       0},
    {1405,"Sol",      "Munoz",    23053,    4,       0},
    {3001,"Federico", "Vitali",   23123,    3,       0},
    {2999,"Alberto",  "Riobo",    23633,    5,       0},
    };

    for(int i=0;i<12;i++){
        employees[i]=auxEmp[i];
    }
}

void hardcodeSectors(Sectors* sectors,int lengthSec){
    Sectors auxSectors[]={
    {1,"RRHH"},
    {2,"Finanzas"},
    {3,"Telecom."},
    {4,"Sistemas"},
    {5,"Gerencia"},
    };

    for(int i=0;i<lengthSec;i++){
        sectors[i]=auxSectors[i];
    }
}

int mainMenu(){
    int option;
    char auxOption[3];

    system("cls");
    printf("*** MENU ABM TP 2 ***\n\n");
    printf("1- Alta empleado\n");
    printf("2- Modificacion empleado\n");
    printf("3- Baja empleado\n");
    printf("4- Informes\n");
    printf("5- Salir\n\n");
    printf("Ingrese option: ");
    scanf("%s",auxOption);

    if(isInt(auxOption)==0){
        printf("Ingrese solo numeros..!!");
        system("pause");
    }else{
        option=atoi(auxOption);
    }

    return option;
}

int addEmployee(Employee* employees, int lengthEmp, int id, char name[],char lastName[],float salary,int sector, Sectors* sectors, int lengthSec){
    int validation=0;
    int index;

    index=findEmptyIndex(employees,lengthEmp);

    employees[index].id=id;
    strcpy(employees[index].name,name);
    strcpy(employees[index].lastName,lastName);
    employees[index].salary=salary;
    employees[index].sector=sector;
    employees[index].isEmpty=OCCUPIED;

    system("cls");
    printf("*** EMPLEADO A DAR DE ALTA ***\n\n");
    printf("%8s %12s %12s %12s %12s\n", "Sector", "Legajo", "Apellido", "Nombre", "Sueldo");
    printf("%8s %12s %12s %12s %12s\n", "------", "------", "--------", "------", "------");
    printEmployee(employees[index],sectors,lengthSec);

    printf("\nEmpleado dado de alta de forma satisfactoria..!!\n\n");

    return validation;
}

int getRandomId(Employee* employees, int lengthEmp, int* requestedRandomId){
    int firstRandomId=1000;
    int index;
    int validation=-1;

    index=findEmptyIndex(employees,lengthEmp);

    if(index>=0){
        *requestedRandomId=firstRandomId+index;
        validation=0;
    }
    return validation;
}

int findEmptyIndex(Employee* employees, int lengthEmp){
    int index=-1;

    for(int i=0;i<lengthEmp;i++){
        if(employees[i].isEmpty==1){
            index=i;
            break;
        }
    }
    return index;
}

int findEmployeeById(Employee* employees, int lengthEmp,int id){
    int index=-1;

    for(int i=0;i<lengthEmp;i++){
        if(employees[i].id==id){
            index=i;
        }
    }
    return index;
}

int removeEmployee(Employee* employees, int lengthEmp, Sectors* sectors, int lengthSec){
    int idEmployee;
    int validation=0;
    int index;
    char confirm;

    printEmployees(employees,lengthEmp,sectors,lengthSec);
    printf("Ingrese legajo del empleado a eliminar: ");
    scanf("%d",&idEmployee);

    index=findEmployeeById(employees,lengthEmp,idEmployee);

    if(index==-1){
        printf("No se ha encontrado al empleado\n");
        system("pause");
        validation=-1;
    }else{
        system("cls");
        printf("*** EMPLEADO A ELIMINAR ***\n\n");
        printf("%8s %12s %12s %12s %12s\n", "Sector", "Legajo", "Apellido", "Nombre", "Sueldo");
        printf("%8s %12s %12s %12s %12s\n", "------", "------", "--------", "------", "------");
        printEmployee(employees[index],sectors,lengthSec);
        printf("Confirma eliminacion?\n");
        fflush(stdin);
        printf("Ingrese s/n: ");
        scanf("%c",&confirm);

        if(confirm=='s'){
            employees[index].isEmpty=EMPTY;
            validation=0;
            printf("\nEmpleado eliminado de forma satisfactoria..!!\n\n");
        }else{
            validation=-1;
        }
    }
    return validation;
}

int modifyMenu(){
    int option;

    system("cls");
    printf("Que desea modificar?\n");
    printf("1- Nombre\n");
    printf("2- Apellido\n");
    printf("3- Salario\n");
    printf("4- Sector\n");

    printf("Ingrese opcion: ");
    scanf("%d",&option);

    return option;
}

int modifyEmployee(Employee* employees, int lengthEmp, Sectors* sectors, int lengthSec){
    int validation=0;
    int index;
    int option;
    int idEmployee;

    printEmployees(employees,lengthEmp,sectors,lengthSec);
    printf("Ingrese legajo del empleado a modificar: ");
    scanf("%d",&idEmployee);

    index=findEmployeeById(employees,lengthEmp,idEmployee);

    if(index==-1){
        printf("No se ha encontrado al empleado\n");
        validation=-1;
    }else{
        option=modifyMenu();

        switch(option){
            case 1:
                modifyNameEmployee(employees,lengthEmp,sectors,lengthSec,index);
                break;
            case 2:
                modifyLastNameEmployee(employees,lengthEmp,sectors,lengthSec,index);
                break;
            case 3:
                modifySalaryEmployee(employees,lengthEmp,sectors,lengthSec,index);
                break;
            case 4:
                modifySectorEmployee(employees,lengthEmp,sectors,lengthSec,index);
                break;
            default:
                printf("Opcion Invalida\n");
                break;
        }
    }
    return validation;
}

int modifyNameEmployee(Employee* employees, int lengthEmp, Sectors* sectors, int lengthSec, int index){
    char auxName[51];
    char confirm;
    int validation;

    validation=getString(auxName,"Ingrese el NUEVO nombre del empleado","Nombre invalido, cantidad de caracteres [min 2 - max 50]",2,50);

    if(validation==1){
        system("cls");

        printf("*** EMPLEADO A MODIFICAR ***\n\n");
        printf("%8s %12s %12s %12s %12s\n", "Sector", "Legajo", "Apellido", "Nombre", "Sueldo");
        printf("%8s %12s %12s %12s %12s\n", "------", "------", "--------", "------", "------");
        printEmployee(employees[index],sectors,lengthSec);

        printf("Confirma NUEVO nombre: %s? s/n\n",auxName);
        fflush(stdin);
        scanf("%c",&confirm);

        if(confirm=='s'){
            strcpy(employees[index].name,auxName);
            validation=0;
        }else{
            validation=-1;
        }
    }else{
        validation=-1;
    }
    return validation;
}

int modifyLastNameEmployee(Employee* employees, int lengthEmp, Sectors* sectors, int lengthSec, int index){
    char auxLastName[51];
    char confirm;
    int validation;

    validation=getString(auxLastName,"Ingrese el NUEVO apellido del empleado","Apellido invalido, cantidad de caracteres [min 2 - max 50]",2,50);

    if(validation==1){
        system("cls");

        printf("*** EMPLEADO A MODIFICAR ***\n\n");
        printf("%8s %12s %12s %12s %12s\n", "Sector", "Legajo", "Apellido", "Nombre", "Sueldo");
        printf("%8s %12s %12s %12s %12s\n", "------", "------", "--------", "------", "------");
        printEmployee(employees[index],sectors,lengthSec);

        printf("Confirma NUEVO apellido: %s? s/n\n",auxLastName);
        fflush(stdin);
        scanf("%c",&confirm);

        if(confirm=='s'){
            strcpy(employees[index].lastName,auxLastName);
            validation=0;
        }else{
            validation=-1;
        }
    }else{
        validation=-1;
    }

    return validation;
}

int modifySalaryEmployee(Employee* employees, int lengthEmp, Sectors* sectors, int lengthSec, int index){
    float auxSalary;
    int validation;
    char confirm;

    validation=getFloat(&auxSalary,"Ingrese el NUEVO salario del empleado","Salario invalido, rango [min 1 - max 999999]",1,100000);

    if(validation==1){
        system("cls");

        printf("*** EMPLEADO A MODIFICAR ***\n\n");
        printf("%8s %12s %12s %12s %12s\n", "Sector", "Legajo", "Apellido", "Nombre", "Sueldo");
        printf("%8s %12s %12s %12s %12s\n", "------", "------", "--------", "------", "------");
        printEmployee(employees[index],sectors,lengthSec);

        printf("Confirma NUEVO salario: %.2f? s/n\n",auxSalary);
        fflush(stdin);
        scanf("%c",&confirm);

        if(confirm=='s'){
            employees[index].salary=auxSalary;
            validation=0;
        }else{
            validation=-1;
        }
    }else{
        validation=-1;
    }

    return validation;
}

int modifySectorEmployee(Employee* employees, int lengthEmp, Sectors* sectors, int lengthSec, int index){
    int auxIdSector=0;
    int validation;
    char confirm;

    printf("AUXILIAR SECTORS ID (le mando a): %d\n\n",auxIdSector);
    validation=chooseSector(&auxIdSector,"Elija el NUEVO sector al que pertenece el empleado","Opcion invalida, rango [0-5]",0,5,sectors,lengthSec);

    if(validation==1){
        system("cls");

        printf("*** EMPLEADO A MODIFICAR ***\n\n");
        printf("%8s %12s %12s %12s %12s\n", "Sector", "Legajo", "Apellido", "Nombre", "Sueldo");
        printf("%8s %12s %12s %12s %12s\n", "------", "------", "--------", "------", "------");
        printEmployee(employees[index],sectors,lengthSec);

        printf("AUXILIAR SECTORS ID(recibo): %d\n\n",auxIdSector);
        printf("Confirma NUEVO sector: %s? s/n\n",sectors[auxIdSector-1].description);
        fflush(stdin);
        scanf("%c",&confirm);

        if(confirm=='s'){
            employees[index].sector=auxIdSector;
            validation=0;
        }else{
            validation=-1;
        }
    }else{
        validation=-1;
    }
    return validation;
}

int sortingMenu(Employee* employees, int lengthEmp){
    int order;

    system("cls");
    printf("Ordenar [A-Z] o [Z-A]\n");
    printf("1- [A-Z]\n");
    printf("2- [Z-A]\n");
    printf("\nIngrese opcion: ");
    scanf("%d",&order);

    sortEmployeesByName(employees,lengthEmp,order);

    return order;
}

int sortEmployeesByName(Employee* employees, int lengthEmp, int order){
    int sortingOk=0;

    for(int i=0;i<lengthEmp-1;i++){
        for(int j=i+1;j<lengthEmp;j++){
            if(employees[i].isEmpty==OCCUPIED){
                if(order==1){
                    if(employees[i].sector>employees[j].sector){
                        bubbleSorting(employees,lengthEmp,i,j);
                    }else{
                        if((employees[i].sector==employees[j].sector)&&(stricmp(employees[i].lastName,employees[j].lastName)>0)){
                            bubbleSorting(employees,lengthEmp,i,j);
                        }
                    }
                }else if(order==2){
                    if(employees[i].sector<employees[j].sector){
                        bubbleSorting(employees,lengthEmp,i,j);
                    }else{
                        if((employees[i].sector==employees[j].sector)&&(stricmp(employees[i].lastName,employees[j].lastName)<0)){
                            bubbleSorting(employees,lengthEmp,i,j);
                        }
                    }
                }
            }
        }
    }

    return sortingOk;
}

void bubbleSorting(Employee* employees, int length, int i, int j){
    Employee auxEmp;

    auxEmp=employees[i];
    employees[i]=employees[j];
    employees[j]=auxEmp;
}

int printEmployees(Employee* employees, int lengthEmp, Sectors* sectors, int lengthSec){
    system("cls");
    printf("*** LISTA DE EMPLEADOS ACTIVOS EN EL SISTEMA ***\n\n");
    printf("%8s %12s %12s %12s %12s\n", "Sector", "Legajo", "Apellido", "Nombre", "Sueldo");
    printf("%8s %12s %12s %12s %12s\n", "------", "------", "--------", "------", "------");

    for(int i=0;i<lengthEmp;i++){
        if(employees[i].isEmpty==OCCUPIED){
            printEmployee(employees[i],sectors,lengthSec);
        }
    }
    return 0;
}

int printEmployee(Employee employee, Sectors* sectors, int lengthSec){
    int index;

    index=getSectorDescription(employee.sector,sectors,lengthSec);

    printf("%8s %12d %12s %12s %12.2f\n", sectors[index].description, employee.id, employee.lastName, employee.name, employee.salary);

    return 0;
}

int chooseSector(int* input,char message[],char eMessage[], int lowLimit, int hiLimit, Sectors* sectors, int lengthSec){
    int todoOk=0;
    int isInteger=0;
    int numeroValidado=0;
    char auxNum[10]={'0'};

    system("cls");
    printSectors(sectors,lengthSec);
    printf("\n%s : ", message);
    scanf("%s", auxNum);
    isInteger=isInt(auxNum);

    if(isInteger){
        numeroValidado=atoi(auxNum);
        if(numeroValidado<lowLimit || numeroValidado>hiLimit){
            printf("%s : ", eMessage);
            scanf("%s", auxNum);
            todoOk=-1;
        }else{
            *input=numeroValidado;
            todoOk=1;
        }
    }else{
        printf("Ingrese solo numeros!\n");
        todoOk=-1;
    }
    return todoOk;
}

int getSectorDescription(int idEmployee, Sectors* sectors, int lengthSec){
    int index=-1;

    for(int i=0;i<lengthSec;i++){
        if(idEmployee==sectors[i].id){
            index=i;
            break;
        }
    }
    return index;
}

void printSectors(Sectors* sectors, int lengthSec){
    system("cls");
    printf("*** SECTORES ***\n\n");
    for(int i=0;i<lengthSec;i++){
        if(sectors[i].id>0){
            printf("%d %4s\n",sectors[i].id, sectors[i].description);
        }
    }
}

int reportsMenu(){
    int option;

    system("cls");
    printf("*** MENU de Informes *** \n\n");
    printf("1- Lista de empleados por orden alfabetico\n");
    printf("2- Lista de total y promedio de salarios\n");
    printf("\nIngrese opcion: ");
    scanf("%d",&option);

    return option;
}

int reports(Employee* employees, int lengthEmp, Sectors* sectors, int lengthSec){

    int validation=0;

    switch(reportsMenu()){
        case 1:
            sortingMenu(employees,lengthEmp);
            printf("*** EMPLEADOS ORDENADOS ALFABETICAMENTE ***\n\n");
            printEmployees(employees,lengthEmp,sectors,lengthSec);
            break;
        case 2:
            reportsSalary(employees,lengthEmp);
            break;
        default:
            printf("Opcion invalida..!!");
            system("pause");
            validation=-1;
            break;
    }
    return validation;
}

void reportsSalary(Employee* employees, int lengthEmp){

float promedioSueldos=0;
float acumuladorSueldos=0;
int contadorSuperaPromedio=0;
int contadorEmpleados=0;

    for(int i=0;i<lengthEmp;i++){
        if(employees[i].isEmpty==OCCUPIED){
           acumuladorSueldos+=employees[i].salary;
            contadorEmpleados++;
        }
    }

    promedioSueldos=acumuladorSueldos/contadorEmpleados;

    for(int i=0;i<lengthEmp;i++){
        if(employees[i].isEmpty==OCCUPIED){
            if(employees[i].salary>promedioSueldos){
                contadorSuperaPromedio++;
            }
        }
    }

    system("cls");
    printf("*** INFORME ***\n\n");
    printf("TOTAL sueldos: %.2f\n\n",acumuladorSueldos);
    printf("PROMEDIO sueldos: %.2f\n\n",promedioSueldos);
    printf("Cant. Emp. que superan el promedio: %d\n\n",contadorSuperaPromedio);
}

