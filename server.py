#!/usr/bin/env python

import socket
import ads1256

TCP_IP = '192.168.1.104'
TCP_PORT = 5005
BUFFER_SIZE = 20  # Normally 1024, but we want fast response

#Start the ADC
ads1256.start("1","2d5")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)

print "Wait for client..."
#Wait for a connection
conn, addr = s.accept()
print 'Connection address:', addr
while 1:
	#data = conn.recv(BUFFER_SIZE)
	#if not data: break
	#print "received data:", data
	
	data = ads1256.read_channel(2)
	#print "sending :", data
	
	conn.send(str(data) + ":")
	

ads1256.stop()
conn.close()