#include <iostream>
#include <string>
#include <cstdlib> 
#include <cstring> 
#include <unistd.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
void Exception(const string & why, const int exitCode ) 
{
    cout << "ErrorCode:"<<exitCode <<endl<< why << endl;
    exit(exitCode);
}
int main()
{

    
    sockaddr_in * SA = new (sockaddr_in);
    SA->sin_family = AF_INET; 
    SA->sin_port = 0;         
    SA->sin_addr.s_addr = 0;

    
    sockaddr_in * RA = new (sockaddr_in);
    RA->sin_family = AF_INET;     
    RA->sin_port = htons(13);  
    RA->sin_addr.s_addr = inet_addr("82.179.90.12"); 

    
    char *buffer = new char[4096];
    strcpy(buffer,"WHATS DATE AND TIME");   
    int msgLen = strlen(buffer);      

   
    int mySocket = socket(AF_INET, SOCK_DGRAM, 0); 
    if (mySocket == -1) {
        close(mySocket);
        Exception("Error open socket",11);
    }
    
    int rc = bind(mySocket,(const sockaddr *) SA, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        Exception("Error bind socket with local address",12);
    }

    
    rc = connect(mySocket, (const sockaddr*) RA, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        Exception("Error connect socket with remote server.", 13);
    }

    
    rc = send(mySocket, buffer, msgLen, 0);
    if (rc == -1) {
        close(mySocket);
        Exception("Error send message", 14);
    }
    cout << " send: " << buffer << endl;

    
    rc = recv(mySocket, buffer, 4096, 0);
    if (rc == -1) {
        close(mySocket);
        Exception("Error receive answer.", 15);
    }
    buffer[rc] = '\0'; 
    cout << " receive: " << buffer; 
    
    close(mySocket);

    delete SA;
    delete RA;
    delete[] buffer;
    return 0;
}