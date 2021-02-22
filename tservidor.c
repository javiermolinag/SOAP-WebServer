#include "soapH.h"
#include "trabajo.nsmap"
#include "frozen.h"
#include <time.h>

int main(void) 
{
  struct soap soap;
  soap_init(&soap);
  int master = soap_bind(&soap, "localhost", 8080, 100);
  if (master < 0) 
  {
     soap_print_fault(&soap, stderr);
     exit(-1);
  }
  fprintf(stderr, "Waiting for client request\n");
  while(1) 
  {
     int client = soap_accept(&soap);
     if (client < 0) 
     {
        soap_print_fault(&soap, stderr);
	exit(-2);
     }
     soap_serve(&soap);
     soap_end(&soap);
  }
}

int ns__testParser(struct soap *soap, int id, char *desc, char *info, struct getParserResponse *resp)
{
  clock_t start = clock();

  char *fecha; 
  int posicion;
  float valor_total;
  char *muestras;

  json_scanf(info, strlen(info), "{fecha: %Q, posicion: %d, valor_total: %f, muestras: %Q}", &fecha, &posicion, &valor_total, &muestras);

  printf("---------------INFORMACION RECIBIDA---------------\n");
  printf("ID: %d \n",id);
  printf("descripcion: %s \n",desc);
  printf("Cadena JSON:\n");
  printf("   fecha: %s \n", fecha);
  printf("   posicion: %d \n",posicion);
  printf("   valor_total: %f \n",valor_total);
  printf("   muestras: %s\n\n", muestras);

  //msg generation (JSON)
  char *msgv = malloc(sizeof(char) * 31); 
  snprintf(msgv,(int)(sizeof(char) * 31), "{Operacion-finalizada-ID: %d.}", id);
  resp->msg = msgv;
  //status generation
  int edoMuestras = strlen(muestras)%8;
  char *muestraDec = malloc(sizeof(char) * 11); 
  char *muestraHex = malloc(sizeof(char) * 9); 
  int convert;
  int totMuestras = strlen(muestras)/8;

  if(edoMuestras != 0)
     resp->status = 2;
  else
  {
     resp->status = 0;
     for(int i=0;i<totMuestras;i++)
     {
        strncpy(muestraHex, muestras+i*8, 8);
        convert = strtol(muestraHex, NULL, 16);
        printf("Muestra HEX %d: %s\n",i+1,muestraHex);
        printf("Muestra DEC %d: %d\n",i+1,convert);
     }
  }
  clock_t stop = clock();
  //ts generation
  resp->ts = (float)(stop - start) * 1000.0 / CLOCKS_PER_SEC;

  return SOAP_OK;
}


















