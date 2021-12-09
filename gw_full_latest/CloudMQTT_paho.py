#!/usr/bin/env python
# -*- coding: utf-8 -*-

import paho.mqtt.client as mqtt
import re
import sys

#don't generate pyc (no compilation of imported module) so change in key_* file can be done dynamically
sys.dont_write_bytecode = True

# get key definition from external file to ease
# update of cloud script in the future
import key_MQTT

MQTT_port=''
mqttc=None

try:
	key_MQTT.source_list
except AttributeError:
	key_MQTT.source_list=[]


def send_data(data, src, nomenclatures, tdata):

	global mqttc
	i=0
	
	if data[0]=='':
		data[0]=key_MQTT.project_name

	if data[1]=='':
		data[1]=key_MQTT.organization_name
			
	while i < len(data)-2:

		if nomenclatures=='':
			topic = data[0]+'/'+data[1]+'/'+src
		else:		
			topic = data[0]+'/'+data[1]+'/'+src+'/'+nomenclatures[i]

		print "CloudMQTT: will send \'{}\' to topic {}".format(data[i+2],topic)
		mqttInfo = mqttc.publish(topic,data[i+2])

		if(mqttInfo.rc == mqtt.MQTT_ERR_SUCCESS):
		    print 'MQTT: publish success'
		elif(mqttInfo.rc == mqtt.MQTT_NO_CONN):
		    print 'MQTT: publish command failed, client not connected'
		elif(mqttInfo.rc == mqtt.MQTT_ERR_QUEUE_SIZE):
		    print 'MQTT: publish command failed, message neither queued nor sent'

		i += 1


def MQTT_uploadData(nomenclatures, data, src, tdata):

    global mqttc
    mqttc = mqtt.Client()
	
    if MQTT_port=='':
        mqttc.connect(MQTT_server)
    else:
        mqttc.connect(MQTT_server, port=MQTT_port)

    mqttc.loop_start()
	
    print("MQTT: publishing")
    send_data(data, src, nomenclatures, tdata)

    mqttc.loop_stop()
    mqttc.disconnect()

def main(ldata, pdata, rdata, tdata, gwid):

	# this is common code to process packet information provided by the main gateway script (i.e. post_processing_gw.py)
	# these information are provided in case you need them
	arr = map(int,pdata.split(','))
	dst=arr[0]
	ptype=arr[1]				
	src=arr[2]
	seq=arr[3]
	datalen=arr[4]
	SNR=arr[5]
	RSSI=arr[6]
	
	#LoRaWAN packet
	if dst==256:
		src_str="0x%0.8X" % src
	else:
		src_str=str(src)	

	if (src_str in key_MQTT.source_list) or (len(key_MQTT.source_list)==0):
	
       		global MQTT_server
		global MQTT_port
		
		# check if ':' separator is present that would indicate a custom MQTT port number
		if key_MQTT.MQTT_server.count(':')>0:
			server_port=re.split(':',key_MQTT.MQTT_server)
			MQTT_server=server_port[0]
			MQTT_port=' -p '+server_port[1]
		else:
           		MQTT_server=key_MQTT.MQTT_server
			MQTT_port=''			

		#LoRaWAN (so encrypted packet) -> ptype & 0x40 == 0x40 or ptype & 0x80 == 0x80
		#or encapsulated encrypted -> ptype & 0x04 == 0x04
		if ptype & 0x40 == 0x40 or ptype & 0x80 == 0x80 or ptype & 0x04 == 0x04:
			nomenclatures = ''
			data=['','']
			data.append(ldata)		
			MQTT_uploadData(nomenclatures, data, key_MQTT.sensor_name+src_str, tdata)
		else:
						
			# this part depends on the syntax used by the end-device
			# we use: TC/22.4/HU/85...
			#
			# but we accept also a_str#b_str#TC/22.4/HU/85... to indicate a project and organization
			# or simply 22.4 in which case, the nomemclature will be DEF
				
			# get number of '#' separator
			nsharp=ldata.count('#')
			nslash=0
				
			# no separator
			if nsharp==0:
				# will use default project and organisation name
				data=['','']

				# get number of '/' separator on ldata
				nslash = ldata.count('/')
				
				# contains ['', '', "s1", s1value, "s2", s2value, ...]
				data_array = data + re.split("/", ldata)		
			else:
				data_array = re.split("#", ldata)
		
				# only 1 separator
				if nsharp==1:
					# insert '' to indicate default project
					# as we assume that the only parameter indicate the organisation name
					data_array.insert(0,'');
					# if the length is greater than 2
					if len(data_array[1])<3:
						data_array[1]=''	

				# we have 2 separators
				if nsharp==2:
					# if the length of a fields is greater than 2 then we take it into account
					if len(data_array[0])<3: 
						data_array[0]=''				
					if len(data_array[1])<3:
						data_array[1]=''
									
				# get number of '/' separator on data_array[2]
				# because ldata may contain '/' 
				nslash = data_array[2].count('/')
	
				# then reconstruct data_array
				data_array=[data_array[0],data_array[1]]+re.split("/", data_array[2])
				
				# at the end data_array contains
				# ["project", "organisation_name", "s1", s1value, "s2", s2value, ...]
		
			# just in case we have an ending CR or 0
			data_array[len(data_array)-1] = data_array[len(data_array)-1].replace('\n', '')
			data_array[len(data_array)-1] = data_array[len(data_array)-1].replace('\0', '')	
																		
			nomenclatures = []
			# data to send
			data = []
			data.append(data_array[0]) #project (if '' default)
			data.append(data_array[1]) #organization name (if '' default)
		
			if nslash==0:
				# old syntax without nomenclature key, so insert only one key
				# we use DEF
				nomenclatures.append("DEF")
				data.append(data_array[2])
			else:
				# completing nomenclatures and data
				i=2
				while i < len(data_array)-1 :
					nomenclatures.append(data_array[i])
					data.append(data_array[i+1])
					i += 2

			#here we append the device's address to get for instance UPPA_Sensor2
			#if packet come from a LoRaWAN device with 4-byte devAddr then we will have for instance UPPA_Sensor01020304
			#where the devAddr is expressed in hex format		
			MQTT_uploadData(nomenclatures, data, key_MQTT.sensor_name+src_str, tdata)
	else:
		print "Source is not is source list, not sending with CloudMQTT.py"				

if __name__ == "__main__":
	main(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5])
