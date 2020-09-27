#include <InCANceivable.h>
#include <mcp_can.h>

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

int verbose=1;

void MCP2515_ISR()
{
    CANflagRecv=1;
}

void InCANceivable_setup()
{
 CANConfigureMasks();
} 

void CANConfigureMasks()
{
 // Nasty hardwre knowledge required here (read the MCP2515 chip data sheet)  
 // there are two filter banks;  filter bank 0 has 2 masks 
 // filter bank 1 has 4 masks.  I *think* that design idea was that you could 
 // actually buffer two messages in hardware  -- the example code available online 
 // does not implement that.  We really only need to listen to two families of ID's
 // the zero address for broadcast and the robot controller (RoboRio) 
 // The way this works it given an ID on the wire, apply the mask, then see if what is
 // left matches a filter. 

  CAN.init_Mask(0,FRC_EXT,FRC_DEVICE_MASK | FRC_MANUFACT_MASK); // accept based on DEVICE AND MANUFACTURER
  CAN.init_Mask(1,FRC_EXT,0);  // turn off input filter bank 1 entirely
  CAN.init_Filt(0,FRC_EXT,0); // accept the broadcast device
  CAN.init_Filt(1,FRC_EXT,RIO_MASK); // accept data from the RIO
  // CAN.init_Filt(2 and up are on Mask 1) 
}

void InCANceivable_msg_dump(unsigned long canId)
{
    // just dumping the message 
    Serial.println("-----------------------------");
    Serial.println("CAN Bus ID binary dump: ");
    for (unsigned long int mask = 0x80000000; mask; mask >>= 1) {
      Serial.print(mask&canId?'1':'0');
    }
    Serial.println();
    Serial.println("10987654321098765432109876543210");
    Serial.println(" 3         2         1");
    Serial.print("Length of data received: ");
    Serial.println(CANlen); 
    for(int i = 0; i<CANlen; i++)    // print the data
      {
	Serial.print(CANbuf[i], HEX);
	Serial.print("\t");
      }
    Serial.println();
    Serial.println("FRC-specific deconstruction");
    Serial.print("Device type: ");
    Serial.print((canId >> FRC_DEVICE_SHIFT) & FRC_DEVICE_MASK, HEX);
    Serial.print(" Manufacurer Number: ");
    Serial.println((canId >> FRC_MANUFACT_SHIFT) & FRC_MANUFACT_MASK, HEX); 
    Serial.print("ClassNum: ");
    Serial.print((canId >> FRC_CLASS_SHIFT) & FRC_CLASS_MASK, HEX);
    Serial.print(" ClassIndex: ");
    Serial.print((canId >> FRC_CLINDEX_SHIFT) & FRC_CLINDEX_MASK, HEX);
    Serial.print(" Device Instance Number: ");
    Serial.println((canId >> FRC_DEVNUM_SHIFT) & FRC_DEVNUM_MASK ,HEX);
}


char messageCheck(unsigned long int *canId)
{
  *canId = 0;
  int ret=0;
  if(CANflagRecv)
    {
      if (canRunning==0)
	{
	  canRunning=1;
	  CAN.readMsgBuf(&CANlen,CANbuf);
	  // drain the buffer;
	  // effective of  discarding the first message in CAN subsystem
	}
	else
	  { 
	    *canId=CAN.getCanId();
	    CAN.readMsgBuf(&CANlen,CANbuf);
	    CANflagRecv=0; 
	    if (FRC_CAN_isBroadcast(*canId))
	      {
                if (verbose)
		  {
		    Serial.println("--BROADCAST MESSAGE BEING HANDLED --");
		    Serial.println(*canId, HEX);
		  } 
		FRC_CAN_handleBroadcast(*canId);
	      }
	    else
	      {
                ret=1;
	      }
	  }
    }
  return(ret);
}
