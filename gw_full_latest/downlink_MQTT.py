#!/usr/bin/env python
# -*- coding: utf-8 -*-

import paho.mqtt.client as mqtt
import os
import re
import datetime

import key_MQTT
_downlink_file = "downlink/downlink.txt"

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Downlink MQTT : Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("$SYS/#")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print("Downlink MQTT: Message received\n{} -> {}".format(msg.topic, msg.payload))
    if msg.topic==downlink_topic:
        f = open(os.path.expanduser(_downlink_file),"w")
        #write to downlink.txt file
        #json.dump(both,f)
        f.write(msg.payload+'\n')
        f.close()
        #self._log(
        #    'mqtt_pull: Write {} to {} {}', json.dumps(both), _downlink_file, datetime.datetime.now().isoformat())
        print('mqtt_pull: Write \'{}\' to {} {}'.format(msg.payload, _downlink_file, datetime.datetime.now().isoformat()))             

def main():

    if key_MQTT.MQTT_server.count(':')>0:
        server_port=re.split(':',key_MQTT.MQTT_server)
        MQTT_server=server_port[0]
        MQTT_port=server_port[1]
    else:
        MQTT_server=key_MQTT.MQTT_server
        MQTT_port=''			

    global downlink_topic
    downlink_topic = "{}/{}/{}".format(key_MQTT.project_name, key_MQTT.organization_name, key_MQTT.downlink_topic)

    mqttc = mqtt.Client()
    mqttc.on_connect = on_connect
    mqttc.on_message = on_message

    if MQTT_port=='':
        mqttc.connect(MQTT_server)
    else:
        mqttc.connect(MQTT_server, port=MQTT_port)

    res = mqttc.subscribe(downlink_topic)
    print "topic : ",downlink_topic
    print "MQTT_server :",MQTT_server
    print "MQTT_port :",MQTT_port
    if res == mqtt.MQTT_ERR_SUCCESS:
        print "Downlink MQTT: Successfully subscribe to downlink topic \'{}\'".format(downlink_topic)
    elif res == mqtt.MQTT_ERR_NO_CONN:
        raise Exception("Downlink MQTT: Error while subscribing to topic, client not connected")
    #else:
     #   raise Exception("Downlink MQTT: Error while subscribing to topic")
    
    mqttc.loop_forever()

if __name__ == "__main__":
    main()
