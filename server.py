import socket
import sys
from thread import *

HOST = ''   # Symbolic name meaning all available interfaces
PORT = 8878 # Arbitrary non-privileged port

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'

try:
    s.bind((HOST, PORT))
except socket.error , msg:
    print 'Bind failed. Error Code : ' + str(msg[0]) + ' Message ' + msg[1]
    sys.exit()

print 'Socket bind complete'

s.listen(10)
print 'Socket now listening'

#function for handling connections. This will be used to create threads
def clientthread(conn):
#now keep talking with the client
    conn.send ('Welcome to the server. Type something and hit enter\n') #send only takes string

    while 1:
        #wait to accept a connection - blocking call

        data = conn.recv(1024)
        reply = 'OK...' + data
        if data[0:2] == '!q':
            break
        if not data:
            break
        if data[0:8] == '!sendall':
            for cons in myConns:
                cons.sendall(data[8:]);

        conn.sendall(reply)

    #came out of loop
    conn.close()
#now keep talking with the client
myConns = []

while 1:
    #wait to accept a connection - blocking call
    conn, addr = s.accept()
    print 'Connected with ' + addr[0] + ':' + str(addr[1])
    myConns.append(conn)


    #start new thread takes 1st argument as a function name to be run, second is the tuple of arguments
    start_new_thread(clientthread, (conn,))

s.close()
