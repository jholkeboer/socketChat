# Jack Holkeboer
# Oregon State University
# cs372
# Project 1
# holkeboj@onid.oregonstate.edu

import sys
import socket


if len(sys.argv) != 3:
    print "Usage: python chatclient.py [host] [port number"
    sys.exit()

host = sys.argv[1]
port = int(sys.argv[2])
print 'Welcome to the socketChat client.'
handle = raw_input('Choose your handle: ')

# create socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # print 'Attempting connection to host %s on port %d ...' % [host,port]
    host_ip = socket.gethostbyname(host)
    sock.connect((host_ip, port))
    
    msg = raw_input("%s> " % handle)
    while (msg != '\quit'):
        # send message
        if len(msg) <= 500:
            sock.send("%s> " % handle + msg)
        else:
            print 'Your message was too long. Maximum 500 characters.'
            
        # wait to receive message
        print '[waiting for response...]'
        response = sock.recv(512)
        if response.endswith("\quit"):
            sock.shutdown(socket.SHUT_RDWR)
            sock.close()
            print "Received quit signal. Closing connection."
            sys.exit()
        print response
        
        # input new message to send
        msg = raw_input("%s> " % handle)
    print "Closing Connection."
    sock.send("\quit")
except socket.gaierror:
    print 'Could not find host. Exiting.'
    sys.exit()


    