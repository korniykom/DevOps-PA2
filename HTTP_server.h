#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

int CreateHTTPserver(); // Declaration of the function

// Declare the functions sendGETresponse and sendPUTresponse here
void sendGETresponse(int fdSocket, char strFilePath[], char strResponse[]);
void sendPUTresponse(int fdSocket, char strFilePath[], char strBody[], char strResponse[]);

// HTTP Headers
extern char HTTP_200HEADER[];
extern char HTTP_201HEADER[];
extern char HTTP_404HEADER[];
extern char HTTP_400HEADER[];

#endif // HTTP_SERVER_H
