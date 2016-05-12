#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "claretlib.h"
#include "lib.h"

/**
*\brief Pide los datos para agregar un itema  una array se valida que haya lugar
*   y que el dato no exista a travès de un campo char*
*\param EUser* struc, puntero a array de estructuras donde se va a cargar el nuevo ITEM
*\param int cant, Tamaño de la array
*\param char* message, recibe un puntero a char para recibir el texto a imprimir en la primer solicitud de datos
*\param int IsEmptyValue Parametro de tipo Int que posee el valor con el cual se debe buscar si hay un lugar
*\return
*/


int addItemStrings(EUser* struc,int cant,char* message,int IsEmptyValue,int *UID)
{
    int retorno=-1;
    int indice,exist;
    char auxChar[4096];
    if(struc!=NULL&& cant >0)
    {
        indice=findEmptyUser(struc,cant,IsEmptyValue,1);
        if(indice!=-1)
        {
            if(getString(auxChar,message,2,120)!=-1)
            {

                firstUpperString(auxChar,11);
                //printf("\n\n%s\n\n", auxChar);
                exist=checkByString(struc,cant,auxChar);
                /** Si el indice existe y el valor del isEmpty es distinto del que se pasa por parametro
                    entonces el usuario existe*/
                if(exist!=-1 && struc[exist].isEmpty!=IsEmptyValue)
                {
                    printf("Usuario registrado\n");
                }
                else
                {
                    strcpy(struc[indice].nick,auxChar);
                    if((getLetters(struc[indice].name,"Ingrese su nombre: ","Error Solo letras y no mayor a 20\n",2,20)!=-1)&&
                            (getMail(struc[indice].mail,"Ingrese su mail: ","Error en formato de mail, Ej: Nahuel@mail.com",6,50)!=-1)&&(getString(struc[indice].password,"Ingrese su password: ",2,50)!=-1))//Dan ok recien ahi cambiamos el valor de is Empty
                    {
                        struc[indice].isEmpty=0;



                        retorno=0;
                    }
                }
            }
            else
            printf("Error en nick");
        }
    }
    return retorno;


}


int checkByString(EUser* struc,int cant,char* strToCheck )
{
    {
        int i;
        int retorno=-1;
        if(struc!=NULL && cant>0)
        {
            for (i=0; i<cant; i++)
            {
                if(strcmp(struc[i].nick,strToCheck)==0 )
                {
                    retorno=i;
                    break;
                }
            }
        }
        return retorno;
    }


}

int initArray(EUser* struc,int cant,int value)
{
    int i;
    int retorno=-1;
    if(struc!=NULL && cant > 0)
    {
        for (i=0; i<cant; i++)
        {
            struc[i].isEmpty=value;
            struc[i].cantComment=0;
        }
        retorno=0;
    }
    return retorno;
}

int initArrayComm(Ecomment* struc,int cant,int value)
{
    int i;
    int retorno=-1;
    if(struc!=NULL && cant > 0)
    {
        for (i=0; i<cant; i++)
        {
            struc[i].isEmpty=value;
        }
        retorno=0;
    }
    return retorno;
}


int modifyItemByStr(EUser* struc,int cant,char* idToModify)
{
    int indextoM;
    int retorno= -1;
    char name[20];
    char mail[50];
    char password[50];

    int optionChange;

    firstUpperString(idToModify,cant);
    if(struc!=NULL&& cant >0)
    {
        indextoM=checkByString(struc,cant,idToModify);
        if(indextoM!=-1&&struc[indextoM].isEmpty==0)
        {
            do{
            getInt(&optionChange,"1-Cambiar su clave\n2-Cambiar su nombre\n3-Cambiar su password\n4-Finalizar cambios\nOpcion:","Error opcion no valida",0,5);
            switch(optionChange)
            {
            case 1:
                if(getString(password,"Ingrese su password: ",2,50)!=-1)
                {
                    strcpy(struc[indextoM].password,password);
                }
                break;
            case 2:
                if(getLetters(&name,"Ingrese su nombre: ","Error Solo letras y no mayor a 20\n",2,20)!=-1)
                {
                    strcpy(struc[indextoM].name,name);
                }
                break;
            case 3:
                if(getMail(&mail,"Ingrese su mail: ","Error en formato de mail, Ej: Nahuel@mail.com",6,50)!=-1)
                {
                    strcpy(struc[indextoM].mail,mail);
                }
                break;
                case 4:

                break;
            }
            }while (optionChange!=4);
            retorno=0;
        }
    }
    return retorno;
}


int deletItemString(EUser* struc,int cant,char* strToDel)
{
    int retorno=-1;
    int indexToDelete;
firstUpperString(strToDel,strlen(strToDel));
    if(struc!=NULL&& cant >0)
    {
        indexToDelete=checkByString(struc,cant,strToDel);
        printf("el indice es %d \n",indexToDelete);
        if(indexToDelete!=-1&&struc[indexToDelete].isEmpty==0)
        {
            struc[indexToDelete].isEmpty=1;
            retorno=0;
        }
    }
    return retorno;
}
