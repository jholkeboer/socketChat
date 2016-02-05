# Jack Holkeboer
# Oregon State University
# cs372
# Project 1
# holkeboj@onid.oregonstate.edu

import sys
import socket

print 'Welcome to the socketChat client.'

# get server hostname, port number, and handle from user
host = raw_input('Enter the server\'s hostname: ').strip()
port = raw_input('Enter the server\'s port number: ')
if port.isdigit():
    port = int(port)
else:
    print 'Port was not a valid number. Exiting.'
    sys.exit()
handle = raw_input('').strip()

# # create socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # print 'Attempting connection to host %s on port %d ...' % [host,port]
    host_ip = socket.gethostbyname(host)
    sock.connect((host_ip, port))
    # sock.connect((socket.gethostbyname(host), port))
except socket.gaierror:
    print 'Could not find host. Exiting.'
    sys.exit()


    