#include "soapH.h"
#include "trabajo.nsmap"
#include <time.h>
#include "frozen.h"

const char server[] = "http://127.0.0.1:8080";

int main(int argc, char **argv)
{
  struct soap *soap = soap_new1(SOAP_XML_INDENT);
  struct getParserResponse resp;
  srand(time(NULL));
  
  //id generation
  int id = rand() % 9 + 1;   
  //desc generation
  char *desc = malloc(sizeof(char) * 33); 
  snprintf(desc,(int)(sizeof(char) * 33), "Informacion de identificador %d.", id);
  //fecha
  char fecha[19]; 
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(fecha,"%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  //posicion
  int posicion = rand() % 100 + 1;
  //valor_total
  float valor_total = (rand() % 100 + 1)/((rand() % 10 + 1)+0.1);
  //muestras
  unsigned int numDec;
  int totMuestras = rand() % 9 + 1;
  char *muestras = malloc(sizeof(char) * totMuestras * 8 + 2);
  int maxValue = 0;
  sprintf(muestras, '\0');
  for (int i=0;i<totMuestras;i++)
    {
    numDec = rand() % 4294967294 + 1;
    sprintf(muestras, "%s%08x", muestras,numDec);
    }
  /*Agregamos ruido a muestras para tener diferente status en servidor*/
  int probabilidad = rand() % 9 + 1;
  if(probabilidad > 8)
  {
     sprintf(muestras, "%s%x", muestras,probabilidad);
  }

  //JSON string generation -> (fecha - posicion - valor_total - muestras)
  char *info = malloc(sizeof(char) * 19 + sizeof(int) + sizeof(float) + sizeof(char) * totMuestras * 8 + 75);
  struct json_out out = JSON_OUT_BUF(info, (int)(sizeof(char) * 19 + sizeof(int) + sizeof(float) + sizeof(char) * totMuestras * 8 + 75));
  json_printf(&out, "{fecha: %Q, posicion: %d, valor_total: %f, muestras: %Q}", fecha, posicion, valor_total, muestras);

  printf("---------------INFORMACION ENVIADA---------------\n");
  printf("ID: %d \n",id);
  printf("descripcion: %s \n",desc);
  printf("Cadena JSON:\n");
  printf("   fecha: %s \n", fecha);
  printf("   posicion: %d \n",posicion);
  printf("   valor_total: %f \n",valor_total);
  printf("   muestras: %s\n",muestras);
  printf("tot muestras: %d\n",totMuestras);

  soap_call_ns__testParser(soap, server, "", id, desc, info, &resp);
  if (soap->error)
    soap_print_fault(soap, stderr);
  else
    {
    printf("---------------INFORMACION RECIBIDA---------------\n");
    printf("   status: %d\n", resp.status);
    printf("   msg: %s\n", resp.msg);
    printf("   ts: %g\n", resp.ts);
    printf("---------------------------------------------------------------------\n");
    }
  soap_destroy(soap);
  soap_end(soap);
  soap_free(soap);
  return 0;
}
