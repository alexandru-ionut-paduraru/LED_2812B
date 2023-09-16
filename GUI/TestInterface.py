import SerialCOM
import json
import os
import time

class RGB_LED:
    __key_order=['green', 'red', 'blue']
    def __init__(self, **params):
        if params.get('red'):
            self.red=params['red']
        else:
            self.red=0

        if params.get('green'):
            self.green=params['green']
        else:
            self.green=0
        
        if params.get('blue'):
            self.blue=params['blue']
        else:
            self.blue=0
    
    def GRB_encode_4B(self):
        """ 
        This function returns the concoding 
        of RGB colors over 4 bytes each, in GRB order 
            Each 4 bits in ret_array will encode one bit of the original color byte
        """
        zero_mask=0b0100
        one_mask=0b0110

        ret_array=[0]*12
        color_index=0
        color_dict=self.__dict__
        for key in self.__key_order: #for each color
            for bit in range(7,-1,-1):
                dest_index=color_index*4+((7-bit)//2)
                if (color_dict[key]>>bit)&0x01:
                    
                    ret_array[dest_index]|=(one_mask<<(4*((8-bit)%2)))
                else:
                    ret_array[dest_index]|=(zero_mask<<(4*((8-bit)%2)))
            color_index+=1
        return(ret_array)

if __name__=="__main__":
    LED_NO=61
    LED_Array=[]
    LED_encoded=[0]*(LED_NO*12)
    
    for i in range(0,LED_NO):
        LED_Array.append(RGB_LED(red=0, green=0, blue=0))
    
    
    

    #Get available COM ports
    SerialCOM.check_com_ports()
    print(f'=====================================')
    print(f'Available Ports:')
    print(f'-------------------------------------')
    port_index=0
    for port in SerialCOM.com_ports:
        print(f'{port_index} - {port}')
    print(f'-------------------------------------')
    if len(SerialCOM.com_ports)==1:
        COM_Port_index=0
    else:
        COM_Port_index=int(input(f'Chose COM port by index = '))
    print(f'Selected port in {SerialCOM.com_ports[COM_Port_index]}')

    ####################################################################
    ####################################################################
    
            
            
    ####################################################################

    # open the connection
    SerialCOM.py_com_connect(SerialCOM.com_ports[COM_Port_index])
    print(f'Connected to device {SerialCOM.InfoString}')

    #Send data over serial connection
    if SerialCOM.ser.is_open:
        if SerialCOM.GetToken():
            data_length=len(LED_encoded)
            CMD_String=f'w0,0,{(data_length>>8)&0xFF},{data_length&0xFF}\r'
            print(CMD_String.encode('UTF-8'))
            if SerialCOM.sendString(CMD_String)==-1: 
                print(f'Failed to send data')
            [res, received_string]=SerialCOM.receiveString()
            if (res==-1): 
                print(f'Failed to receive data')
            if received_string[0]=='X':
                print("Data update sequence - Command Error")
            else:
                received_string=received_string[1:] #take out first character
                print(received_string)
                #convert the content to a byte list
                try:
                    pass
                except Exception as e:
                    print(e)
                    print("Write data error")

            LED_Array[0].red=255
            for i in range(0,LED_NO+4):
                LED_encoded=[]
                for LED in LED_Array:
                    LED_encoded=LED_encoded+LED.GRB_encode_4B()
                #time.sleep(0.1)
                SerialCOM.setCommandReg(0, 1)
                time.sleep(0.05)

                #SerialCOM.ser.flush()
                #print(bytes(LED_encoded))
                for byte_val in bytes(LED_encoded):
                    #print(byte_val)
                    SerialCOM.ser.write([byte_val])

                #set next led config
                if(i<LED_NO):
                    LED_Array[i].red=255
                    if i-1>=0: LED_Array[i-1].red=150
                    if i-2>=0: LED_Array[i-2].red=50
                    if i-3>=0: LED_Array[i-3].red=5
                    if i-4>=0: LED_Array[i-4].red=0
                    
                else:
                    if i-1<LED_NO-1: LED_Array[i-1].red=150
                    if i-2<LED_NO-1: LED_Array[i-2].red=50
                    if i-3<LED_NO-1: LED_Array[i-3].red=5
                    if i-4<LED_NO-1: LED_Array[i-4].red=0

            time.sleep(1)
            LED_Array[LED_NO-1].green=255
            LED_Array[LED_NO-1].red=0
            for i in range(LED_NO-1, -1-4, -1):
                LED_encoded=[]
                for LED in LED_Array:
                    LED_encoded=LED_encoded+LED.GRB_encode_4B()
                #time.sleep(0.1)
                SerialCOM.setCommandReg(0, 1)
                #time.sleep(0.1)

                #SerialCOM.ser.flush()
                #print(bytes(LED_encoded))
                for byte_val in bytes(LED_encoded):
                    #print(byte_val)
                    SerialCOM.ser.write([byte_val])

                #set next led config
                if(i>=0):
                    LED_Array[i].green=255
                    if i+1<LED_NO: LED_Array[i+1].green=150
                    if i+2<LED_NO: LED_Array[i+2].green=50
                    if i+3<LED_NO: LED_Array[i+3].green=5
                    if i+4<LED_NO: LED_Array[i+4].green=0
                else:
                    if i+1>0: LED_Array[i+1].green=150
                    if i+2>0: LED_Array[i+2].green=50
                    if i+3>0: LED_Array[i+3].green=5
                    if i+4>0: LED_Array[i+4].green=0

            SerialCOM.ReleaseToken()

    # SerialCOM.py_com_disconnect()
    #print([bin(val) for val in LED_encoded])

