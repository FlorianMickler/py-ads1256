#!/usr/bin/env python

import socket
import ads1256
import struct

TCP_IP = '192.168.1.104'
TCP_PORT = 5005

TCP_PACK_SIZE = 150
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
	#outMsg = ""
	outBin = ""
	
	for i in range(TCP_PACK_SIZE):
		data1 = ads1256.read_channel(2)
		data2 = ads1256.read_channel(3)
		if data1 == 0 or data2 == 0:
			print "ZERO %s %s"%(data1,data2)
		#data3 = ads1256.read_channel(4) -> We need only 2
		#Append data to the outgoing message
		#outMsg = outMsg + "%s,%s:"%(data1,data2)
		outBin = outBin + struct.pack('!ii', data1, data2)
		
	
	#print "sending :", outMsg
	#Send aggregated data
	#conn.send(outMsg)
	conn.send(outBin)
	

ads1256.stop()
conn.close()