
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "reversi.h"
#include "initreversi.h"

#define ERREUR_ALLOCATION_MEMOIRE 1

//donne automatiquement une couleur aux joueurs
int affectationcouleur(int nbj, joueur *tabjoueurs)
{
  switch(nbj){
    case 1 : tabjoueurs[1].couleur=vert;return(0);
    case 2 : tabjoueurs[2].couleur=rouge;break;
    case 3 : tabjoueurs[3].couleur=bleu;break;
    case 4 : tabjoueurs[4].couleur=orange;break;
    case 5 : tabjoueurs[5].couleur=violet;break;
    case 6 : tabjoueurs[6].couleur=jaune;break;
  }
  return(affectationcouleur(nbj-1,tabjoueurs));
}

//renvoie le tableau de joueurs
joueur *initJoueurs(int nbjoueurs)
{
  int nbj=nbjoueurs;

  joueur *tabjoueurs=malloc(sizeof(joueur)*nbjoueurs);
  if(tabjoueurs==NULL){
    free(tabjoueurs);
    exit(ERREUR_ALLOCATION_MEMOIRE);
  }
  affectationcouleur(nbj,tabjoueurs);
  return(tabjoueurs);
}

//initialisation du tableau de directions
fleche *initrose()
{
  fleche *rose;

  //tableau de directions predefinies
  const direction
  nord={0,-1},
  sud={0,1},
  est={1,0},
  ouest={-1,0},
  nordest={1,-1},
  nordouest={-1,-1},
  sudest={1,1},
  sudouest={-1,1};

  rose=malloc(sizeof(fleche)*8);
  rose[0].dir=nord;
  rose[1].dir=sud;
  rose[2].dir=est;
  rose[3].dir=ouest;
  rose[4].dir=nordest;
  rose[5].dir=sudouest;
  rose[6].dir=nordouest;
  rose[7].dir=sudest;
  return rose;
}

void depart2(cellule **plateau, int x, int y, color a, color b)
{
  plateau[x][y].couleur=plateau[x+1][y+1].couleur=a;
  plateau[x+1][y].couleur=plateau[x][y+1].couleur=b;
  plateau[x][y].contenu=plateau[x+1][y+1].contenu=plateau[x+1][y].contenu=plateau[x][y+1].contenu=pion;
  plateau[x][y].age=plateau[x+1][y+1].age=plateau[x+1][y].age=plateau[x][y+1].age=1;
}

void depart3(cellule **plateau, int x, int y, color a, color b, color c)
{
  plateau[x][y].couleur=plateau[x+1][y+1].couleur=plateau[x+2][y+2].couleur=a;
  plateau[x][y+1].couleur=plateau[x+1][y+2].couleur=plateau[x+2][y].couleur=b;
  plateau[x][y+2].couleur=plateau[x+1][y].couleur=plateau[x+2][y+1].couleur=c;
  plateau[x][y].contenu=plateau[x+1][y+1].contenu=plateau[x+2][y+2].contenu=plateau[x][y+1].contenu=plateau[x+1][y+2].contenu=plateau[x+2][y].contenu=plateau[x][y+2].contenu=plateau[x+1][y].contenu=plateau[x+2][y+1].contenu=pion;
  plateau[x][y].age=plateau[x+1][y+1].age=plateau[x+2][y+2].age=plateau[x][y+1].age=plateau[x+1][y+2].age=plateau[x+2][y].age=plateau[x][y+2].age=plateau[x+1][y].age=plateau[x+2][y+1].age=1;
}

//retourne 1 s'il n'y a pas de pion autour
int ras(cellule **plateau, int x, int y, fleche *rose, int N)
{
  direction dir;
  for(int i=0;i<8;i++){
    dir=rose[i].dir;
    if(checkbords(x,y,dir,N)){
      if(plateau[x+dir.hori][y+dir.verti].contenu==pion){
      return(0);
      }
    }
  }
  return(1);
}

//initialisation du age de jeu
cellule **initplateau(int *N, int nbjoueurs, joueur *tabjoueurs, fleche *rose)
{
  int randomX,randomY,nbbombes,i,j,nbmaxbombes;
  cellule **plateau,cell;
  srand(time(NULL));

  system("clear");

      printf("TEST1");

  switch(nbjoueurs){
    case 2 : *N=6;nbmaxbombes=20;break;
    case 3 : *N=9;nbmaxbombes=56;break;
    case 4 : *N=11;nbmaxbombes=57;break;
    case 5 : *N=13;nbmaxbombes=83;break;
    case 6 : *N=13;nbmaxbombes=69;break;
  }

  printf("TEST2\n");

  plateau=malloc(*N*sizeof(cellule*));
  if(plateau==NULL){
    exit(ERREUR_ALLOCATION_MEMOIRE);
  }

  printf("TEST3\n");

  for(i=0;i<*N;i++){
    plateau[i]=malloc(*N*sizeof(cellule));
    if(plateau[i]==NULL){
      for(j=i-1;j>=0;j--){
        free(plateau[j]);
      }
      free(plateau);
      exit(ERREUR_ALLOCATION_MEMOIRE);
    }
    for(j=0;j<*N;j++){
      plateau[i][j].contenu=vide;
      plateau[i][j].age=0;
    }
  }

  printf("TEST4\n");




  switch(nbjoueurs){
    case 2 : depart2(plateau,2,2,vert,rouge);
    case 3 : depart3(plateau,3,3,vert,rouge,bleu);
    case 4 : depart2(plateau,2,2,vert,rouge);
             depart2(plateau,2,7,bleu,orange);
             depart2(plateau,7,7,vert,rouge);
             depart2(plateau,7,2,bleu,orange);
    case 5 : depart2(plateau,2,2,vert,rouge);
             depart3(plateau,2,8,bleu,orange,violet);
             depart2(plateau,9,9,vert,rouge);
             depart3(plateau,8,2,bleu,orange,violet);
    case 6 : depart3(plateau,2,2,vert,rouge,bleu);
             depart3(plateau,2,8,orange,violet,jaune);
             depart3(plateau,8,8,vert,rouge,bleu);
             depart3(plateau,8,2,orange,violet,jaune);
  }

  do{
    printf("Combien de bombes voulez-vous ? (maximum %d)\n",nbmaxbombes);
    scanf("%d",&nbbombes);
  }while(nbbombes>nbmaxbombes);
  for(int i=1;i<=nbbombes;i++){
    do{
      randomX=rand()%*N;
      randomY=rand()%*N;
      cell=plateau[randomX][randomY];
    }while(cell.contenu==pion || cell.contenu==bombe || !ras(plateau,randomX,randomY,rose,*N));
    plateau[randomX][randomY].contenu=bombe;
  }
  printf("INIT PLATEAU TERMINE\n");
  return(plateau);
}

//desallouage d'un plateau
int terminate(cellule **plateau, fleche *rose, int N)
{
  for(int i=N-1;i>=0;i--){
    free(plateau[i]);
  }
  free(plateau);
  free(rose);
  return(0);
}
