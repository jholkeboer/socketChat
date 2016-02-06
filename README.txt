socketChat: Python chat client and C++ chat server
By Jack Holkeboer
Oregon State cs372
Tested on flip.engr.oregonstate.edu

Compile the server like this:
g++ -o chatserve chatserve.cpp

Run the server like this, passing port as argument:
./chatserve [port number]

Enter your handle on the server.

Then launch the client like this:
python chatclient.py [hostname] [port number]

Enter the handle on the client.

Client must send first message.  After that they alternate.

NOTE:
If you are running on flip, be sure to pass the correct host.
For example, if chatserve is running on flip2.engr.oregonstate.edu,
use that as the host.


EXAMPLE:
(on flip2.engr.oregonstate.edu)
g++ -o chatserve chatserve.cpp
./chatserve 20200

(on flip1.engr.oregonstate.edu)
python chatclient.py flip2.engr.oregonstate.edu 20200



