//gsoap ns service name:	trabajo
//gsoap ns service location:	http://localhost/trabajo
//gsoap ns service namespace:	trabajo
//gsoap ns schema namespace:	trabajo
//gsap ns service executable: gsoap

//gsoap ns service method: ws__testParser
struct getParserResponse{int status; char *msg; float ts;};
int ns__testParser(int id, char *desc, char *info, struct getParserResponse *r);
