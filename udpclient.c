#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFSIZE 1024

void error(char *msg) {
    perror(msg);
    exit(0);
}
struct node{
    float battery;
    float dc,cpu,storage;
    float acc;
};
float calculate_score()
{
    float bat=0,dc=0,cpu=0,st=0;
    int num_node;
    scanf("%d",&num_node);
    struct node a[num_node];
    for(int i=0;i<num_node;i++){
        a[i].acc=0;
        printf("Enter Node information for Node : %d\n",i+1);
        printf("Battery : ");
        scanf("%f",&a[i].battery);
        bat+=a[i].battery;
        printf("DC : ");
        scanf("%f",&a[i].dc);
        dc+=a[i].dc;
        printf("CPU : ");
        scanf("%f",&a[i].cpu);
        cpu+=a[i].cpu;
        printf("Storage : ");
        scanf("%f",&a[i].storage);
        st+=a[i].storage;
    }   
    for(int i=0;i<num_node;i++){
        a[i].acc+=((a[i].battery*100)/bat)*3;
        a[i].acc+=((a[i].dc*100)/dc)*5;
        a[i].acc+=((a[i].cpu*100)/cpu)*6;
        a[i].acc+=((a[i].storage*100)/st)*8;
    }
    for(int i=0;i<num_node;i++){
        a[i].acc/=1000;
    }
    int node_name = 0;float node_val=0;
    for(int i=0;i<num_node;i++){
        if (a[i].acc>node_val){
            node_name = i;
            node_val = a[i].acc;
        }
    }
    float res = node_name+1 + ((1-node_val)/100);
    return res;
}
int main(int argc, char **argv) {
    int sockfd, portno, n;
    int serverlen;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char *hostname;
    char buf[BUFSIZE];
    if (argc != 3) {
       fprintf(stderr,"usage: %s <hostname> <port>  --ye format maintain karna paregya\n", argv[0]);
       exit(0);
    }
    hostname = argv[1];
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
        error("tera system me problem he.. server open nahi ho raha he.. ");

    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR: Koie server nahi mila  %s iss naam ka\n", hostname);
        exit(0);
    }

    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
	  (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);
    bzero(buf, BUFSIZE);
    //while(1){
        float s =  calculate_score();
        char buffer[64];
int ret = snprintf(buffer, sizeof buffer, "%f", s);
if (ret < 0) {
    return EXIT_FAILURE;
}
if (ret >= sizeof buffer) {
    printf(" Result truncated ho gaya.. aab toh resize karna paregya");
}


        fgets(buf, BUFSIZE, stdin);

    serverlen = sizeof(serveraddr);

    n = sendto(sockfd, buffer, strlen(buffer), 0, &serveraddr, serverlen);
    if (n < 0) 
      error("problem ho gaya bhai.. ");    
    //}
    return 0;
}
