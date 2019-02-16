#!/usr/bin/env python

import socket
import ads1256
import struct
import datetime

TCP_IP = '192.168.1.104'
TCP_PORT = 5005

TCP_PACK_SIZE = 200
TCP_SAMPLE_SIZE = 8

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
	outBin = ""
	
	for i in range(TCP_PACK_SIZE):
		t1 = datetime.datetime.now()
		data = ads1256.read_all_channels()
		t3 = datetime.datetime.now()
		
		print "%s "%(t3-t1)
		
		if data[2] == 0 or data[3] == 0:
			print "ZERO %s %s"%(data[2],data[3])
		
		#Append data to the outgoing message
		outBin = outBin + struct.pack('!ii', data[2], data[3])
		
	
	#Send aggregated data
	conn.send(outBin)
	

ads1256.stop()
conn.close()