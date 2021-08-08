#include <stdio.h>
#include <string.h>

int main()
{
    char c1[50],c2[50],c3[50];
    scanf ("%s\n%s\n%s", &c1,&c2,&c3);

    if((strcmp(c1,"vertebrado")==0) && (strcmp(c2,"ave")==0) && (strcmp(c3,"carnivoro")==0))
        printf("aguia\n");
    else if((strcmp(c1,"vertebrado")==0) && (strcmp(c2,"ave")==0) && (strcmp(c3,"onivoro")==0))
        printf("pomba\n");
    else if((strcmp(c1,"vertebrado")==0) && (strcmp(c2,"mamifero")==0) && (strcmp(c3,"onivoro")==0))
        printf("homem\n");
    else if((strcmp(c1,"vertebrado")==0) && (strcmp(c2,"mamifero")==0) && (strcmp(c3,"herbivoro")==0))
        printf("vaca\n");
    else if((strcmp(c1,"invertebrado")==0) && (strcmp(c2,"inseto")==0) && (strcmp(c3,"hematofago")==0))
        printf("pulga\n");
    else if((strcmp(c1,"invertebrado")==0) && (strcmp(c2,"inseto")==0) && (strcmp(c3,"herbivoro")==0))
        printf("lagarta\n");
    else if((strcmp(c1,"invertebrado")==0) && (strcmp(c2,"anelideo")==0) && (strcmp(c3,"hematofago")==0))
        printf("sanguessuga\n");
    else if((strcmp(c1,"invertebrado")==0) && (strcmp(c2,"anelideo")==0) && (strcmp(c3,"onivoro")==0))
        printf("minhoca\n");

    return 0;
}
