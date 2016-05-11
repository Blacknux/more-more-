#ifndef __CLARETCOMMENT
#define __CLARETCOMMENT
typedef struct
{
    int id;
    char comment[1500];
    char nickUser[50];
    int contLike;
    int isEmpty;


}Ecomment;
#endif // __EARRAY

#ifndef __CLARETUSER
#define __CLARETUSER
typedef struct
{
    char name[20];
    char nick[20];
    char password[50];
    char mail[50];
    int isEmpty;
} EUser;
#endif // __EARRAY


#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

int initArray(EUser* struc,int cant,int value);
 int initArrayComm(Ecomment* struc,int cant,int value);
 int checkByString(EUser* struc,int cant,char* strToCheck );
 int addItemStrings(EUser* struc,int cant,char* message,int IsEmptyValue,int *UID);
 int findEmptyUser(EUser* struc,int cant, int value,int printFull);
 int findEmptyc(Ecomment* struc,int cant, int value,int printFull);

#endif // LIB_H_INCLUDED
