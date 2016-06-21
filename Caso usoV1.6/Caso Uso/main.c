#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "claretlib.h"
#include "ArrayList.h"
#include "Employee.h"



eEmployee* loadEmployee(ArrayList* pList);


int main()
{
    ArrayList* arrayListC=al_newArrayList();
    ArrayList* DeleteHistory=al_newArrayList();
    ArrayList* Backup=al_newArrayList();
    eEmployee* employeeAux;
    int id=0;
    int auxInt;
    int option;
    char continueDo='s';
//    loadCant(arrayListC);
    loadFile(arrayListC,"Nomina.dat");
    loadFile(DeleteHistory,"Exempl.dat");

//   loader(arrayListC);
    do
    {
        getInt(&option,"######CASO DE USO ARRAYLIST###\n\n1-Agregar un empleado\n2-Modificar empleado\n3-Eliminar empleado"
               "\n4-Tamaño de la nomina\n5-Informes\n6-Salir"
               "\n10-Salir\noption:","Opcion no valida\n",1,8);
        switch(option)
        {
        case 1:
            employeeAux=loadEmployee(arrayListC);
            auxInt=findByName(DeleteHistory,employeeAux->name,employeeAux->lastName);
            if(auxInt==-1)
            {
                id++;
                if(al_add(arrayListC,(void*)employeeAux))
                {
                    id--;
                }
            }
            else
            {
                getInt(&option,"\nEl empleado ya pertenecia a la empresa, desea agregarlo nuevamente?? \n1-Si\n2-No","Error opcion no valida",1,2);
                switch(option)
                {
                case 1:
                    employeeAux=(ArrayList*)arrayListC->get(DeleteHistory,auxInt);
                    al_push(arrayListC,(employeeAux->id-1),(void*)employeeAux);
                    al_remove(DeleteHistory,auxInt);
                    break;
                case 2:
                    id++;
                    if(al_add(arrayListC,(void*)employeeAux))
                    {
                        id--;
                    }
                }
                break;
            }
            break;
        case 2:
            modifyEmployee(arrayListC);
            break;
        case 3:
            deleteEmployee(arrayListC,DeleteHistory);
            break;
        case 4:
            printf("\n\n@@@@@@@@ HISTORIAL @@@@@@@\n\n");
            PrintEmployees(DeleteHistory);
            break;
        case 5:
            informes(arrayListC);
            break;
        case 6:
            continueDo='n';
            saveToFileActive(arrayListC,"Nomina.dat");
            saveToFileActive(DeleteHistory,"Exempl.dat");
            break;
        case 7:

            break;
        case 8:
            al_push(arrayListC,2,loadEmployee(arrayListC));

            break;

        default:
            break;
        }


    }
    while(continueDo!='n');
//    saveCant(arrayListC);


    return 0;
}

/** \brief Crea un nuevo empleado
 *
 * \param id int Recibe el numero de id del empleado
 * \param name[] char nombre del empleado
 * \param lastName[] charapellido del empleado
 * \param salary float salario del empleado
 * \return eEmployee* devuelve un puntero a estructura eEmployee
 *
 */
eEmployee* newEmployee(int id, char name[],char lastName[],float salary)
{
    eEmployee* returnAux = NULL;
    eEmployee* pEmployee = malloc(sizeof(eEmployee));

    if(pEmployee != NULL)
    {
        pEmployee->id = id;
        strcpy(pEmployee->name,name);
        strcpy(pEmployee->lastName,lastName);
        pEmployee->salary = salary;
        pEmployee->isEmpty = 0;
        returnAux = pEmployee;
    }

    return returnAux;

}


/** \brief SOlicita los datos para un nuevo empleado
 *
 * \param pList ArrayList*  Recibe el arraylist del cual se usaran algunos datos como el size
 * \return eEmployee* devuelve un empleado para que el mismo se cargue con newEmployee
 *
 */
eEmployee* loadEmployee(ArrayList* pList)
{
    eEmployee* returnAux=NULL;
    char name[20];
    char lastName[20];
    float salary;
//    int a=*(id);
    if(pList!=NULL)
    {


        if(getString(name,"Ingrese el nombre:",1,20)!=-1&&getString(lastName,"Ingrese apellido: ",1,20)!=-1)
        {
            printf("Ingrese el sueldo: ");
            scanf("%f",&salary);
            returnAux=newEmployee(pList->size+1,name,lastName,salary);

        }
    }
    return returnAux;
}

/** \brief Recibe un empleado y si no es NULL lo imprime
 *
 * \param employee eEmployee* Puntero a empleado el cual se mostrara por pantalla
 * \return int retorna 0 si el puntero no es NULL y -1 si lo es
 *
 */
int printEmployee(eEmployee* employee)
{
    int returmAux=-1;
    if(employee!=NULL)
    {
        printf("\nNumero de empleado:%d\nNombre:%s\nApellido:%s\nSueldo:%2.f\n\n\n",employee->id,employee->name,employee->lastName,employee->salary);
        returmAux=0;
    }
    return returmAux;
}

/** \brief imprime una array de empleados dentro de una arraylist
 *
 * \param list ArrayList* arraylist a recorrer
 * \return int -1 si la lista es null y 0 si no lo es
 *
 */
int  PrintEmployees(ArrayList* list)
{
    int returnAux=-1;
    int i;
    eEmployee* Aux;
    if(list!=NULL)
    {
        for(i=0; i<list->size; i++)
        {
//        Aux=*((list->pElements)+i); /**NO PUEDO VER EL ULTIMO EMPLEADO HAY ALGO MAL EN EL PUSH**/
            printEmployee(*((list->pElements)+i));
//        printf("%x Puntero ",*((list->pElements)+i));
        }
        returnAux=0;
    }
    return returnAux;

}

/** \brief Elimina un empleado de la lista de empleados actuales y los agrega a un historial de exempleados
 *
 * \param pList ArrayList* array de donde se eliminara el empleado
 * \param historyDel ArrayList* array de exempleados donde se guardara el empleado eliminado
 * \return int  en caso de que ambas arrays no sean distintas de  NULL retorna 0, caso contrario -1
 *
 */
int deleteEmployee(ArrayList* pList,ArrayList* historyDel)
{
    int option;
    char continueDo='s';
    int indexAux;
    eEmployee* mostrar=NULL;
    int returnAux=-1;
    system("cls");
    if(pList!=NULL && historyDel!=NULL)
    {
      if(!getInt(&indexAux,"ingrese el legajo del usuario a eliminar","Error usuario no existente",0,pList->size))
      {
          mostrar=(eEmployee*)pList->pop(pList,indexAux-1);
        al_add(historyDel,((void*) mostrar));
        printf("\nUsuario eliminado\n");
        system("pause");

      }
      returnAux=0;
    }
    return returnAux;

}


/** \brief Carga 4 empleados para caso de prueba inicial
 *
 * \param pList ArrayList* array donde se caragran los empleados
 * \return void
 *
 */
void loader(ArrayList* pList)
{
    pList->add(pList,newEmployee(1,"nahuel","Claret",2334689.5));
    pList->add(pList,newEmployee(2,"Sheldom","Cooper",22.5));
    pList->add(pList,newEmployee(3,"Barney","Stinson",25542.5));
    pList->add(pList,newEmployee(4,"Pedro","Picapiedra",2992.5));
    pList->size=4;
}


/** \brief compara empleados por su salario
 *
 * \param pEmployeeA void* empleado a comparar 1
 * \param pEmployeeB void*  empleado a comparar 2
 * \return int si salario del 1er empleado es mayor al del segundo 1
 *             si salario del 1er empleado es menor al del segundo -1
 *             si salario del 1er empleado es igual al del segundo 0
 */
int compareEmployee(void* pEmployeeA,void* pEmployeeB)
{
    if(((eEmployee*)pEmployeeA)->salary > ((eEmployee*)pEmployeeB)->salary)
    {
        return 1;
    }
    if(((eEmployee*)pEmployeeA)->salary < ((eEmployee*)pEmployeeB)->salary)
    {
        return -1;
    }
    return 0;
}

///** \brief Muestra una lista acomodada por sueldo ascendente
// *
// * \param pList ArrayList* array de donde sacara los datos de los empleados
// * \return int 0 si pList distinto de NULL -1 si es NULL
// *
// */
//int mostrarEmpPorSueldo(ArrayList* pList)
//{
//    int returnAux=-1;
//    ArrayList* aux;
//    if(pList!=NULL)
//    {
//        aux=pList->clone(pList);
//        aux->sort((void*)aux,compareEmployee,0);
//        PrintEmployees(aux);
//        free(aux);
//        returnAux=0
//    }
//    return returnAux;
//}

/** \brief carga una array de empleados desde un archivo binario
 *
 * \param pList ArrayList* array a cargar
 * \param file char* nombre del archivo binario donde  se encuentran los datos
 * \return int si file, pList, Auxiliar y bin distintos de NULL 0 si no -1
 *
 */
int loadFile(ArrayList* pList,char* file)
{
    FILE* bin;
    int retorno=-1;
    bin=fopen(file,"rb");
    eEmployee* Auxiliar=(eEmployee*)malloc(sizeof(eEmployee));
    if(pList!=NULL && file!=NULL && Auxiliar!=NULL && bin!=NULL)
    {
            if(bin==NULL)
    {
        printf("\nError en la apertura del archivo\nPresione una tecla para continuar....\n");
        getchar();
    }
    else
    {
        while(!feof(bin))
        {
            Auxiliar=(eEmployee*)malloc(sizeof(eEmployee));
            fread(Auxiliar,sizeof(eEmployee),1,bin);
            if(!feof(bin))
                {
                    pList->add(pList,Auxiliar);
                }
//                free(Auxiliar);
        }
        retorno=0;
            fclose(bin);
    }
    }
    return retorno;
}

/** \brief guarda los datos de una lista de empleados en un archivo binario
 *
 * \param pList ArrayList* Array de donde toma lso datos
 * \param file char* nombre del archivo a guardar
 * \return int -1 si file, pList o bin son NULL y 0 si los 3 ok
 *
 */
int saveToFileActive(ArrayList *pList,char* file)
{
    FILE* bin;
    int retorno=-1;
    int i=0;
    int lenAux;
    eEmployee* aux;
    bin=fopen(file,"r+b");
    if(bin==NULL)
    {
        bin=fopen(file,"w+b");
        if(bin==NULL)
        {
            printf("Error en el guardado del archivo.");
        }
    }
        if(pList!=NULL && file != NULL && bin != NULL)
        {
            lenAux=pList->len(pList);
    while(i<lenAux)
    {
        aux=*((pList->pElements)+i);
        if(!fwrite(*((pList->pElements)+i),sizeof(eEmployee),1,bin))
            printf("OK");
        i++;
    }

    retorno=0;
    fclose(bin);
    printf("Guardado OK\n");
        }
    return retorno;
}




/** \brief Imprime una serie de informes
 *          1- Imprime nomina ocmpleta
 *          2- solicita desde y hasta e imprime una sublista de empleados por legajo
 *          3 imprime listado por sueldo < o >
 *
 * \param pList ArrayList* array de donde se obtendran los datos
 * \return int
 *
 */
int informes(ArrayList* pList)
{
    int option;
    int from;
    int to;
    int returnAux=-1;
    int order;
    ArrayList* ArrayAux=al_newArrayList();
if(pList!=NULL && ArrayAux!=NULL )
{
    getInt(&option,"\n1-Imprimir Nomina\n2-Imprimir Sub-Nomina\n3-Imprimir listado por sueldo\n4-Salir\nOption:","Error Opcion no valida",1,4);

    switch(option)
    {
    case 1:
        PrintEmployees(pList);
        break;
    case 2:
        if(!getInt(&from,"Ingrese desde que legajo:","Error Legajo mayor a los empleados en nomina...\n",0,pList->size)&&
        getInt(&to,"Ingrese hasta que legajo:","Error Legajo mayor a los empleados en nomina...\n",0,pList->size))
        {
            ArrayAux=al_subList(pList,from-1,to);
            PrintEmployees(ArrayAux);
            al_deleteArrayList(ArrayAux);
        }


        break;
    case 3:
        if(!getInt(&order,"\n1-Mostrar Nomina por sueldo de mayor a menor\n2-Mostrar Nomina por sueldo de menor a mayor\nOption:","Error",1,2))
        {
            switch(order)
            {
            case 1:
                ArrayAux=pList->clone(pList);
                pList->sort(ArrayAux,compareEmployee,0);
                PrintEmployees(ArrayAux);
                pList->deleteArrayList(ArrayAux);
                break;
            case 2:
                ArrayAux=pList->clone(pList);
                pList->sort(ArrayAux,compareEmployee,1);
                PrintEmployees(ArrayAux);
                pList->deleteArrayList(ArrayAux);
                break;

            }
        }
        break;
    case 4:
        break;
    }
    returnAux=0;
}
return returnAux;
}

int findByName(ArrayList* pList,char* nameToFind,char* lastNameToFind)
{
    int retorno =-1;
    int i;

    eEmployee* employeeAux;
    if(pList!=NULL)
    {
        for (i=0;i< pList->len(pList);i++)
        {
            employeeAux=(*((pList->pElements)+i));
            if(stricmp(nameToFind,employeeAux->name)==0)
            {
                if(stricmp(lastNameToFind,employeeAux->lastName)==0)
                {
                    retorno=i;
                }
            }
        }
    }
    return retorno;
}


int modifyEmployee(ArrayList* pList)
{
    int i;
    int retorno=-1;
    int option;
    char auxname[20];
    char auxAuxName[20];
    char* auxLastName;
    float auxSalary;
    eEmployee* AuxEmployee;
    int auxId;

    if(pList!=NULL)
    {
        if(!getInt(&auxId,"Ingrese el legajo del empleado:","Error",1,pList->size))
        {
            for(i=0;i<pList->size;i++)
            {
                    AuxEmployee=*((pList->pElements)+i);
                    if(AuxEmployee->id==auxId)
                    {
                        do
                        {
                            getInt(&option,"\n1-Cambiar nombre\n2-Cambiar apellido\n3-Cambiar salario\n4-Salir","Opcion no valida",1,4);
                            switch(option)
                            {
                            case 1:
                                fflush(stdin);
                                if(-1!=getString(auxname,"Ingrese el nombre: ",1,20))
                                {
                                    printEmployee(AuxEmployee);
                                    printf("%s",&auxname);
                                    strcpy(AuxEmployee->name,auxname);
                                }
                                break;
                            case 2:
                                fflush(stdin);
                                if(-1!=getString(auxLastName,"Ingrese el apellido: ",1,20))
                                {
                                    strcpy(AuxEmployee->lastName,auxLastName);
                                }
                                break;
                            case 3:
                                printf("Ingrese el salario:");
                                if(!scanf("%f",&auxSalary))
                                {
                                    AuxEmployee->salary=auxSalary;
                                }
                            }
                        }while (option!=4);
                        retorno=0;
                    }
            }
        }
    }
}
