# WebServer project 

## 1.- Webserver using C in Linux environment using SOAP protocol

methods to be implemented are: 

ws_testParser
ws_testReport

## 2.- Define the postgres Database to record the information handled by the webserver
(hint, use GOOGLE CLOUD) 

## 3.- Deliver web service definition file  (wsdl)

### ws_testParser

REQUEST:

id - Integer type value to identify the data group 
desc - Description, character string. 
info - JSON type string with the following fields 

	{
	"fecha" : event date in format "aaaa-mm-dd hh:mm:ss"
	"posicion" : Numeric value of type integer 
	"valor_total" : float type numeric value 
	"muestras" : string with hexadecimal values, where there are n 4-byte integers. 
	Example with 3 values. "001231A700F23BA700D23CA7"
	}

RESPONSE:

status - integer (0 - success, 1 - future date, 2 - error in samples )
msg - JSON string 
ts - Floating with the processing start time in seconds.milliseconds 

Process to do:

A. Process each message through a thread 
B. Interpret the received values and display on the screen. 
C. Each of the "sample" values must be shown in hexadecimal and decimal format. 
D. Insert the information in the DB 
E. When interpreting the samples include a 5-second waiting time between each value.

### ws_testReport

REQUEST

id - Integer type value 

RESPONSE

info - JSON type string with the following data 

	{
	"estado" : 0 - exists, 1 - No information exists
	"descripcion" : Description associated with the identifier 
	"fecha" : Event registration date 
	"posicion" : place value 
	"promedio" : Average of samples sent 
	"total" : Integer with the number of associated samples 
	"muestras" : [
	{
	"hexadecimal" : "Value in hexadecimal format",
	"decimal" : sample integer value
	},
	...
	{
	"hexadecimal" : "Value in hexadecimal format",
	"decimal" : sample integer value
	}
	]
	}

Process to do:

A. Report the information corresponding to the identifier received 