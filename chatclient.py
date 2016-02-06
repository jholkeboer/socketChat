# Jack Holkeboer
# Oregon State University
# cs372
# Project 1
# holkeboj@onid.oregonstate.edu

import sys
import socket

# check for argument
if len(sys.argv) != 3:
    print "Usage: python chatclient.py [host] [port number"
    sys.exit()

host = sys.argv[1]
port = int(sys.argv[2])
print 'Welcome to the socketChat client.'

# get handle
handle = raw_input('Choose your handle: ')

# create socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # get host and connect socket
    host_ip = socket.gethostbyname(host)
    sock.connect((host_ip, port))
    
    msg = raw_input("%s> " % handle)

    while (msg != '\quit'):
        # send message
        if len(msg) <= 500:
            sock.send("%s> %s" % (handle,msg))
        else:
            print 'Your message was too long. Maximum 500 characters.'
            
        # wait to receive message
        print '[waiting for response...]'
        response = sock.recv(512)
        if "\quit" in response:
            print "Received quit signal. Closing connection."
            sys.exit()
        print response

        # input new message to send
        msg = raw_input("%s> " % handle)
    
    # react to \quit message
    print "Closing Connection."
    
    # send \quit to server
    sock.send("\quit")
except socket.gaierror:
    print 'Could not find host. Exiting.'
    sys.exit()


    