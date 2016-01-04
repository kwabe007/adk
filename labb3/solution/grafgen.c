/*
  Användning:
    grafgen nx ny p [slumpfrö]

    där nx och ny är heltal och p är flyttal mellan 0 och 1.
    Om parametern slumpfrö (positivt heltal) anges så används detta värde,
    annars används den inbyggda klockan som slumpfrö.

    
  Gör:
    Genererar en bipartit G = (X,Y,E) där
    X = {1, 2, ..., nx}    
    Y = {nx+1, nx+2, ..., nx+ny}
    E bildas genom att ta med kant (i,j) med sannolikhet p
    
  Utdata:
    Skriver på stdout.
    En rad med värdet på nx
    En rad med värdet på ny
    En rad med värdet på |E|
    |E| rader med de utvalda kanterna

*/

#include <stdlib.h>
#include <stdio.h>

#define MAX_LONG 0x7FFFFFFF

#define KANT_BUF_STORLEK 500

struct kant
{
  unsigned int x, y;
};

typedef struct kant KANT;

struct lnk 
{
  int antal_kanter;
  KANT kanter[KANT_BUF_STORLEK];
  struct lnk *next;
};

typedef struct lnk  LANK;



void laegg_till_kant( LANK **sista, 
		     unsigned int i, 
		     unsigned int j)
{
  LANK *tmp;
  
  if ((*sista)->antal_kanter == KANT_BUF_STORLEK ) 
    {
      tmp = (LANK *) malloc( sizeof( LANK ) );
      tmp->next = NULL;
      tmp->antal_kanter = 0;
      (*sista)->next = tmp;
      *sista = tmp;
    }
  
  ((*sista)->kanter[ (*sista)->antal_kanter ]).x = i;
  ((*sista)->kanter[ (*sista)->antal_kanter ]).y = j;
  ((*sista)->antal_kanter)++;
}

  
  

void meddela_anvandning() 
{
  fprintf( stderr, "Usage: grafgen nx ny p [slumfrö]\n" );
}


void main(int argc, char *argv[]) 
{

  unsigned int antal_x_noder, antal_y_noder, i, j;
  unsigned long slumpfro;
  float kant_prob;
  LANK *kantlista;
  LANK *sist_i_kantlista;
  LANK *tmp;
  unsigned int antal_kanter;
  

  kantlista = (LANK *) malloc( sizeof(LANK) );
  kantlista->next = NULL;
  kantlista->antal_kanter = 0;  
  sist_i_kantlista = kantlista;
  
  antal_kanter = 0;
  
  if (argc < 4 || argc > 5 ) {
    meddela_anvandning();
    exit(1);
  }
  

  if ( sscanf( argv[1], "%ud", &antal_x_noder ) == 0 ) {
    meddela_anvandning();
    exit(1);
  }
 
  if ( sscanf( argv[2], "%ud", &antal_y_noder ) == 0 ) {
    meddela_anvandning();
    exit(1);
  }
  
  if ( sscanf( argv[3], "%f", &kant_prob ) == 0 
       || kant_prob < 0 
       || kant_prob > 1) {
    meddela_anvandning();
    exit(1);
  }
 

  if ( argc == 5 ) {
    if ( sscanf( argv[4], "%ul", &slumpfro ) == 0 ) {
      meddela_anvandning();
      exit(1);
    }
  }
  else
    slumpfro = time( NULL );

  

  srandom( slumpfro );
  
  for ( i = 1; i <= antal_x_noder; i++ )
    for ( j = 1; j <= antal_y_noder; j++ )
      if ( kant_prob * MAX_LONG > random() )
	{
	  laegg_till_kant(&sist_i_kantlista,i,j+antal_x_noder);
	  antal_kanter++;
	}
  
  printf( "%u\n", antal_x_noder );
  printf( "%u\n", antal_y_noder );
  printf( "%u\n", antal_kanter );

  
  for ( tmp = kantlista; tmp != NULL; tmp = tmp->next )
    for ( i = 0; i < tmp->antal_kanter; i++ )
      printf( "%u %u\n", (tmp->kanter[i]).x, (tmp->kanter[i]).y );
  
  
}
