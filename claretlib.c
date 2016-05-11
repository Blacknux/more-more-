#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "claretlib.h"
#include "lib.h"

#define TAM 5
void prueba(void)
{

    int i;
    int a=0;
    int numerito[TAM];

    for(i=0; i<TAM; i++)
    {
        a=getInt((numerito+i),"Ingrese un numero: ","Solo numeros entre el 0 y el 2300\n",0,2300);

        if (a==-1)
        {
            i--;
        }
    }
    for(i=0; i<TAM; i++)
    {
        printf("La %d Ingresada es: %d\n",i+1,numerito[i]);
    }


}

/**
*
*
*
*/

int getString(char *input,char* message,int intMin,int intMax )
{
    char auxChar[4096];
    int retorno=-1;

    if(input!=NULL&& intMin>=0)
    {
        printf("%s",message);
        setbuf(stdin,NULL);
        gets(auxChar);
        if(strlen(auxChar)<intMax &&strlen(auxChar)>intMin )
        {
            strcpy(input,auxChar);
            retorno=0;
        }
        else
        {
            if(strlen(auxChar)<intMin)
            {
                printf("muy cort@\n");
            }
            if(strlen(auxChar)>intMax)
            {
                printf("muy larg@\n");
            }

            //printf( "%s",errorMessage);
        }
    }
    return retorno;

}


/**
*
*
*
*/

int getLetters(char* input,char* messageInput,char* eMessage,int lengthMin,int lengthMax)
{
    int retorno=-1;
    int i;
    int getstFlag=0;
    int strleng;
    char auxChar[4096];


    if(input!=NULL && lengthMin>0)
    {
        setbuf(stdin,NULL);
        getstFlag=getString(auxChar,messageInput,lengthMin,lengthMax);
        strleng=strlen(auxChar);

        for(i=0; i<strleng; i++)
        {
            if(getstFlag==-1)
            break;
            if(/*(strleng>lengthMin)&&*/(auxChar[i]>='a'&& auxChar[i]<='z')||(auxChar[i]>='A'&&auxChar[i]<='Z'))
            {

                 strcpy(input,auxChar);
                retorno=0;
                break;

            }
            else
            {
                printf("%s",eMessage);
                break;

            }

        }
    }
    return retorno;
}

/**
*
*
*
*/

int getNumbers(char* input,char* messageInput,char* eMessage,int lengthMin,int lengthMax)
{
    int retorno=-1;
    int i;
    int getstFlag=0;
    int strleng;
    char auxChar[4096];


    if(input!=NULL && lengthMin>0)
    {
        setbuf(stdin,NULL);
        getstFlag=getString(auxChar,messageInput,lengthMin,lengthMax);
        strleng=strlen(auxChar);

        for(i=0; i<strleng; i++)
        {
            if(getstFlag==-1)
            break;
            if(/*(strleng>lengthMin)&&*/(auxChar[i]>='0'&& auxChar[i]<='9'))
            {

                 strcpy(input,auxChar);
                retorno=0;

            }
            else
            {
                printf("%s",eMessage);
                break;

            }

        }
    }
    return retorno;
}

/**
*
*
*
*/
int getMail(char* input,char* messageInput,char* eMessage,int lengthMin,int lengthMax)
{
    int retorno=-1;
    int i;
    int getstFlag=0;
    int strleng;
    int countAt=0;
    int countDot=0;
    char auxChar[4096];


    if(input!=NULL && lengthMin>0)
    {
        setbuf(stdin,NULL);
        getstFlag=getString(auxChar,messageInput,lengthMin,lengthMax);
        strleng=strlen(auxChar);

        for(i=0; i<strleng; i++)
        {
            if(getstFlag==-1)
            {
                break;
            }
            if(/*(strleng>lengthMin)&&*/(auxChar[i]>='0'&& auxChar[i]<='9')||(auxChar[i]>='a'&& auxChar[i]<='z')||(auxChar[i]>='A'&&auxChar[i]<='Z')||(auxChar[i]=='@'|| auxChar[i]=='.'))
            {
                strcpy(input,auxChar);
                if(auxChar[i]=='@')
                {
                    countAt++;
                }
                if(auxChar[i]=='.')
                {
                    countDot++;
                }
            }
            else
            {
                printf("%s",eMessage);
                break;
            }
        }// END FOR
        if(countAt==1&&countDot>=1)
        {
            retorno=0;
        }
        else
        {
            printf("%s",eMessage);
        }
    }
    return retorno;
}

/**
*
*
*
*/

int getPhone(char* input,char* messageInput,char* eMessage,int lengthMin,int lengthMax)
{
    int retorno=-1;
    int i;
    int getstFlag=0;
    int strleng;
    int countSymbol=0;
    char auxChar[4096];


    if(input!=NULL && lengthMin>0)
    {
        setbuf(stdin,NULL);
        getstFlag=getString(auxChar,messageInput,lengthMin,lengthMax);
        strleng=strlen(auxChar);

        for(i=0; i<strleng; i++)
        {
            if(getstFlag==-1)
            {
                break;
            }
            if(/*(strleng>lengthMin)&&*/(auxChar[i]>='0'&& auxChar[i]<='9')||(auxChar[i]=='-'))
            {
                strcpy(input,auxChar);
                if(auxChar[i]=='-')
                {
                    countSymbol++;
                }

            }
            else
            {
                printf("%s",eMessage);
                break;
            }
        }// END FOR
        if(countSymbol==1)
        {
            retorno=0;
        }
        else
        {
            printf("%s",eMessage);
        }
    }
    return retorno;
}


int getInt(int* input,char message[], char errorMessage[],int lowLimitRange,int hiLimitRange)
{
    char aux[4096];
    int retorno=-1;
    int intAux;

    printf("%s", message);
    setbuf(stdin,NULL);
    gets(aux);

    if ( strcmp(aux,"0\0")==0)
    {
        intAux = atoi(aux);
        retorno = 0;
        *input = intAux;

    }
    else
    {
        intAux = atoi(aux);
        if(intAux != 0)
        {
            if(intAux > lowLimitRange && intAux < hiLimitRange )
            {
                retorno = 0;
                *input = intAux;
            }
            else
            {
                printf("%s", errorMessage);
            }
        }
        else
        {
            printf("%s", errorMessage);
        }

    }



    return retorno;

}



/**
*\brief Convierte en mayuscula la primera letra de cada nombre incluyendo nombre compuestos.
*\param struc array a utilizar
*\param Largo del array
*\return Devuelve 0 si termino OK o -1 si no pudo realizar la tarea.
*/

int firstUpper(EUser* struc, int cant)
{
    int i;
    int j;
    int retorno = -1;


    if(struc != NULL && cant > 0 )
    {
        for (i=0;i<cant;i++)
        {
            for(j=0;j<strlen(struc[i].name);j++)
            {
                if(0 == j || struc[i].name[j]==' ')
                {
                    struc[i].name[j]=toupper(struc[i].name[j]);

                }
                if(struc[i].name[j]==' ')
                {
                    struc[i].name[j+1]=toupper(struc[i].name[j+1]);

                }


            }
        }
        retorno=0;
    }
    return retorno;
    }



    int findEmptyUser(EUser* struc,int cant, int value,int printFull)
{
    int i;
    int retorno=-1;
    if(struc!=NULL && cant>0)
    {
        for (i=0; i<cant; i++)
        {
            if(struc[i].isEmpty==value)
            {
                retorno=i;
                break;
            }
        }
        if (retorno==-1 && printFull==1)
            printf("No hay lugar");
    }
    return retorno;

}

/**
*\brief Recibe una puntero a char y pone la primer letra en mayusculas
*\param char* strToUpper Cadena a ser modificada
*\param int cant Tamaño de la cadena para ser recorrida
*\return si pudo realizar la tarea devuelve 0 si no -1
*/


int firstUpperString(char* strToUpper, int cant)
{
    int i;
//    int j;
    int retorno = -1;

    if(strToUpper != NULL && cant > 0 )
    {
        for (i=0; i<cant; i++)
        {
            if(0 == i /*|| strToUpper[i][j]==' '*/)
            {
                strToUpper[i]=toupper(strToUpper[i]);
            }
            else if(strToUpper[i]==' ')
            {
                strToUpper[i+1]=toupper(strToUpper[i+1]);
            }
        }
        retorno=0;
    }
    return retorno;
}
