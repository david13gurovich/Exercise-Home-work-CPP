/* // Client side implementation of UDP client-server model  */
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT    8080 
#define MAXLINE 1024 

#define MAAYAN_IP "10.1.0.223"  

/* gd udp_client_clock.c -o test_clock.out */

const size_t UID_SIZE =  8;
const size_t BLOCK_INDEX_SIZE = 8;
const size_t DATA_SIZE = 4096;
const size_t TIME_STRING_SIZE = 100;
const size_t MAX_MSG_SIZE = 5050;

const char READ_MSG_TYPE  = 0;
const char WRITE_MSG_TYPE = 1;
const char CLOCK_MSG_TYPE = 'c';
struct MinionClockReplyMsg
{
    unsigned char           type;
    unsigned char           uid[8];
    unsigned char           status;
    char                    timeStr[100];
};

int main() 
{ 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *ClientClockMsg = "c"; 
    struct sockaddr_in servaddr; 
    socklen_t len;
    int n; 
    int broadcastEnable=1;
    int ret;
    struct MinionClockReplyMsg *clockReplyMsg = NULL;
  
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 ) 
    { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    ret = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
    if (-1 == ret)
    {
        perror("setsockopt");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr)); 
      
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    if(inet_pton(AF_INET, MAAYAN_IP, &servaddr.sin_addr) <= 0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        perror("inet_pton");
        return -1; 
    }    

    sendto(sockfd, (const char *)ClientClockMsg, strlen(ClientClockMsg), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
    
    printf("Client sending: %s \n", ClientClockMsg ); 
        
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  MSG_WAITALL, 
                        (struct sockaddr *) &servaddr, &len); 
    clockReplyMsg = (struct MinionClockReplyMsg *)buffer;
    printf("Server sent type: %c\n", clockReplyMsg->type); 
    printf("Server sent type: %s\n", clockReplyMsg->timeStr); 
    printf("Server msg len: n=%d \n",n);        
    close(sockfd); 
    
    return 0; 
} 