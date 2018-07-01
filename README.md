# socket_c_UDP
udp socket in c , simple sender and receiver



**_compile_**

server
---------------
gcc udpServer.c -o server

Client
---------------
gcc udpclient.c -o client


**_RUN**


server
---------------
./server

client
---------------
./client localhost 7777



**NOTE**
we use port 7777, you can change it. Read that source code, you will understand. 

Client take two command line argument, <hostname> <port>
  
./client localhost 7777

localhost is host name.
7777 is the PORT uses during udp connection.



Thank you
- Adhir Ch Mondal
