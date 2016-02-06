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
        sock.send(msg)
        msg = raw_input("%s> " % handle)
except socket.gaierror:
    print 'Could not find host. Exiting.'
    sys.exit()


    