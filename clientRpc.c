/* clientRpc.c for cs454 a2
 *
 */

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "rpc.h"

#define CNERR -12

int clientConnect(char * addr, char * port) {
   int status, sockfd;
   struct addrinfo hints;
   struct addrinfo *servinfo;  // will point to the results

   memset(&hints, 0, sizeof hints); // make sure the struct is empty
   hints.ai_family = AF_UNSPEC;        // don't care IPv4 or IPv6
   hints.ai_socktype = SOCK_STREAM; // TCP structeam sockets

   if( status = getaddrinfo(addr, port, &hints, &servinfo) != 0) { 
      printf("\nCannot get server info."); 
      return -2; 
   }
   sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
   if( connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
      printf("\nconnection failed!\nsockfd:%d\n", sockfd); 
      return -3;
   }
               
   return sockfd;
}

int rpcCall(char * name, int * argTypes, void ** args) {

   //get binder address
   char * binderPort = getenv("BINDER_PORT");
   char * binderAddr = getenv("BINDER_ADDRESS");
   printf("Binder Address: %s\nBinder Port: %s\n", binderPort, binderAddr);

   //connect to binder, send LOC_REQUEST
   int sfd = clientConnect(binderAddr, binderPort);
   if(sfd < 0) { printf("connection error %d\n", sfd); return CNERR;}


   return 0;
}

int rpcTerminate(){

   return 0;
}



