#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "claretlib.h"
#include "lib.h"

#define TAM_user 5
#define TAM_comment 500
int modifyItemByStr(EUser* struc,int cant,char* idToModify);
int checkById(Ecomment* struc, int cant,int idToCheck);
int oneLike(Ecomment *struc,int cant);
//

int main()
{
    //prueba();
    int i;
    int option;
    int UID=1;
    int CID=1;
    int flagCommOn=-1;
    EUser user[TAM_user];
    Ecomment comment[1500];
    EUser DatosUser[2]= {{"Nahuel","Nah","30998992","nah@mio.com",0,29},{"Nahuel","Zlo","30998asdffs","nahssssssss@mio.com",0,5}};
    //Ecomment DatosComment[2]= {{1,"Hola coment 1","Nah",2,0},{2,"Hola coment 2","Nah",1,0}};
    char seguir='s';
    char itemdel[233];
    char nickChange[233];
    char nickDel[233];
    int checkdelete;
    int auxiliar;
    int flagUser=-1;
//    int flagComment=-1;


    initArray(user,TAM_user,1);
    initArrayComm(comment,1500,1);

    for(i=0; i<2; i++)
    {
        user[i]=DatosUser[i];
    }
//    for(i=0; i<2; i++)
//    {
//        comment[i]=DatosComment[i];
//    }

    do
    {
        printf("\n1-ADD User\n2-Modificar User\n3-DEL User\n4-New Comment\n5-Like It\n6-INFO\n7-Listarcoments\n8-EXIT\n");
        option=0;
        getInt(&option,"","Solo entre 1 y 5",0,61);
        firstUpper(user,5);
        switch(option)
        {
        case 1:
            if(addItemStrings(user,TAM_user,"Ingrese el nick del usuario: ",1,UID)!=-1)
            {
                UID++;
                flagUser=0;
            }
            break;
        case 2:
            getString(nickChange,"Ingrese el nick del usuario a modificar: ",2,20);
            modifyItemByStr(user,TAM_user,nickChange);
//            getInt(&auxiliar,"Ingrese el id a modificar: ","Error",0,100);
//            modifyItemById(user,5,auxiliar);
            break;
        case 3:
            getString(nickChange,"Ingrese el nick del usuario a borrar: ",2,20);
            deletItemString(user,TAM_user,nickChange);

//            getString(itemdel,"Ingrese el nombre a eliminar: ",1,20);
//            firstUpperString(itemdel,20);
//           checkdelete= deletItemString(user,5,itemdel);
//           if (checkdelete==-1)
//           printf("Error en borrado reintente");
            break ;
        case 4:
            if(flagUser!=-1)
            {
            if( addItemStringsComm(user,comment,1500,1,&CID)!=-1)
            {
                flagCommOn =0;
            }
            }
            else
            {
                printf("No se pueden ingresar comentarios se necesita usuarios registardos\n");
            }

            break;
        case 5:
            if(flagUser!=-1&&flagCommOn!=-1 )
            {
            oneLike(comment,1500);
            }
            else
            {
                printf("No se pueden ingresar comentarios se necesita usuarios registardos o comentarios registrados\n");
            }
            break;
        case 6:
            if (flagCommOn!=-1)
            {
                maxComent(user,5);
                maxlike(comment,1500,1);
                promLike(comment,1500);
            }
            else
            {
                printf("Nose ingresaron comentarios\n");
            }
            break;
        case 7:
            listCommentsSorting(comment,1500);
            break;
        case 8:
            //savArrayStructToFile(user,5);
            seguir='n';
            break;
        case 36:
            system("clear");
            for(i=0; i<5; i++)
            {
                if(user[i].isEmpty==0)
                {
                    //printf("\n\nPersona Nro-%d\n",i+1);
                    printf("Nick: %s\nNombre: %s\nmail: %s\nPassword: %s\nLikes: %d\n",user[i].nick, user[i].name,user[i].mail,user[i].password);
                }
            }
            printf("Presione una tecla pra continuar....");
            getchar();
            system("clear");
            break;
        case 25:
//            for(i=0; i<5; i++)
//            {
//                comment[i].id=i+1;
//                comment[i].isEmpty=0;
//            }
            for(i=0; i<1500; i++)
            {
                if(comment[i].isEmpty==0)
                {
                    printf("\nID: %d\nComentario:\n%s\n\tAutor: %s\nLikeit: %d\n",comment[i].id,comment[i].comment,comment[i].nickUser,comment[i].contLike);
                }
                else
                {
                    break;
                }
            }
            break;
        }

    }
    while(seguir!='n');
    return 0;
}

/**
*\brief Pide los datos de login al usuario y si son correctos agrega un item a  una array se valida que haya lugar
*   y que el dato no exista a travès de un campo int
*\param Ecomment* struc, puntero a array de estructuras donde se va a cargar el nuevo ITEM
*\param EUser* struc, puntero a array de estructuras donde se va a cargar el nuevo ITEM
*\param int cant, Tamaño de la array
*\param char* message, recibe un puntero a char para recibir el texto a imprimir en la primer solicitud de datos
*\param int IsEmptyValue Parametro de tipo Int que posee el valor con el cual se debe buscar si hay un lugar
*\return
*/


int addItemStringsComm(EUser* userArray,Ecomment* struc,int cant,int IsEmptyValue,int *CID)
{
    int retorno=-1;
    int indice,exist;
    char auxChar[4096];
    char user[20];
    char pass[50];
    int commentID;
    int indiceUser;

    if(struc!=NULL&& cant >0)
    {
        indice=findEmptyc(struc,cant,IsEmptyValue,1);
        getLetters(user,"Ingrese su Nick: ","Solo letras\n",2,20);
        getString(pass,"Ingrese su password: ",4,50);
        firstUpperString(user,strlen(user));
        indiceUser=checkUser(userArray,TAM_user,user,pass);
        if(indice!=-1 && indiceUser!=-1)
        {
            getInt(&commentID,"Ingrese el id del comentario: ","Error id duera de rango o formato\n",0,TAM_comment);
            if(checkById(struc,TAM_comment,commentID)==-1)
            {
                struc[indice].id=commentID;
                if(getString(struc[indice].comment,"Ingrese su comentario.\n",2,1500)!=-1)
                {

                    strcpy(struc[indice].nickUser,userArray[indiceUser].nick);
                    strcpy(struc[indice].userName,userArray[indiceUser].name);
                    struc[indice].isEmpty=0;
                    userArray[indiceUser].cantComment++;
                    retorno=0;
                }
            }

            else
            {
                if(indice==-1)
                {
                    printf("No hay mas lugar para comentarios\n");
                }
                else
                {
                    printf("Usuario o Password equivocada");
                }
            }
        }
    }
    return retorno;


}



int checkUser(EUser* struc,int cant,char *nick,char *Pass)
{
    int i;
    int retorno=-1;
    if(struc!=NULL&& cant >0)
    {

        firstUpperString(nick,strlen(nick));
        for (i=0; i<cant; i++)
        {
            if(strcmp(nick,struc[i].nick)==0)
            {
                if(strcmp(Pass,struc[i].password)==0)
                {
                    retorno=i;
                    break;
                }
                else
                {
                    printf("Error en el password\n");
                    break;
                }
            }
//            else
//            {
//                printf("Usuario inexistente");
//                break;
//            }

        }
    }
    return retorno;
}


int checkById(Ecomment* struc, int cant,int idToCheck)
{
    int i;
    int retorno=-1;
    if(struc!=NULL && cant>0)
    {
        for (i=0; i<cant; i++)
        {
            if (struc[i].id==idToCheck )
            {
                retorno=i;
                break;
            }
        }
    }
    return retorno;
}

int oneLike(Ecomment *struc,int cant)
{
    int retorno=-1;
    int id;
    int indiceComment;
    if(struc!=NULL&& cant >0)
    {
        getInt(&id,"Ingrese el id del comentario: ","Error solo numero de 1 -1500",0,1500);
        indiceComment=checkById(struc,cant,id);
        if(indiceComment!=-1)
        {
            struc[indiceComment].contLike++;
            retorno =0;
        }
    }
    return retorno;
}

void maxComent(EUser *struc,int cant,int commentOn)
{
    int i,j;
    int mayor;
    char User[20];
    int flag=-1;
    if(struc!=NULL&& cant >0)
    {
        for(i=0; i< cant; i++)
        {

            if(struc[i].isEmpty!=1)
            {
                if(flag==-1)
                {
                    mayor=struc[i].cantComment;
                    strcpy(User,struc[i].nick);
                    flag=0;
                }
                else
                {
                    if(mayor<struc[i].cantComment)
                    {
                        mayor=struc[i].cantComment;
                        strcpy(User,struc[i].nick);
                    }
                }
                printf("El usuario con mas me comentarios  es: %s con %d comentarios.\n",User,mayor);


            }
            else
            {
                printf("Aun no se ingresaron comentarios\n");
                break;
            }
        }

    }
}


void maxlike(Ecomment *struc,int cant,int flagShowComment)
{
    int i,j;
    int mayor;
    int idComment;
    int flag=-1;
    char comment[150];
    if(struc!=NULL&& cant >0)
    {
        for(i=0; i< cant; i++)
        {
            if(struc[i].isEmpty!=1)
            {
                if(flag==-1)
                {
                    mayor=struc[i].contLike;
                    idComment=struc[i].id;
                    strcpy(comment,struc[i].comment);
                    flag=0;
                }
                else
                {
                    if(mayor<struc[i].contLike)
                    {
                        mayor=struc[i].contLike;
                        idComment=struc[i].id;
                        strcpy(comment,struc[i].comment);
                    }
                }
                printf("El comentario con mas me gusta es el de ID: %d con %d me gusta.\n",idComment,mayor);
                if(flagShowComment==1)
                {
                    printf("%s\n",comment);

                }
            }
            else
            {
                printf("Aun no se ingresaron comentarios\n");
                break;
            }
        }

    }
}

int promLike(Ecomment *struc,int cant)
{
    int i;
    int acumLikes=0;
    int contComment=0;


    for(i=0; i<cant; i++)
    {
        if(struc[i].isEmpty!=1)
        {
            acumLikes+=struc[i].contLike;
            contComment++;
        }
    }
    //printf ("La cantidad de likes total es: %d y la cantidad de comentarios: %d\n",acumLikes,contComment);
    printf("El promedio de likes es: %d",acumLikes/contComment);


}


int listCommentsSorting(Ecomment *comments,int cant)
{
    int i,j;
    Ecomment AuxSwap;
    for (i=0; i<cant-1; i++)
    {
        for(j=i+1; j<cant; j++)
        {
            if(comments[i].isEmpty==0)
            {
                if(strcmp(comments[i].userName,comments[j].userName)==0)
                {
                    if(strcmp(comments[i].nickUser,comments[j].nickUser)>0)
                    {
                        AuxSwap=comments[i];
                        comments[i]=comments[j];
                        comments[j]=AuxSwap;
                    }
                }
                else
                {
                    if(strcmp(comments[i].userName,comments[j].userName)<0)
                    {
                        AuxSwap=comments[i];
                        comments[i]=comments[j];
                        comments[j]=AuxSwap;

                    }

                }

            }
        }
    }
    for(i=0;i<cant;i++)
    {
        if(comments[i].isEmpty==0)
            {
        printf("Comentario: %s\n\t\t likes: %d\n",comments[i].comment,comments[i].contLike);
        }
    }
    return 0;
}



