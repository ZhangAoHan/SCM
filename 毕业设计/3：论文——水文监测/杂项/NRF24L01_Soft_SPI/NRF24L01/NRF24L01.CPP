#include <NRF24L01.h> 
extern unsigned char TX_ADDRESS[TX_ADR_WIDTH];
extern unsigned char RX_ADDRESS[TX_ADR_WIDTH];
extern unsigned char rx_buf[TX_PLOAD_WIDTH];
extern unsigned char tx_buf[TX_PLOAD_WIDTH];
extern unsigned char channel; 
//----------------------------------------------------------------------------------------------
// Function: init_io();
// Description:
// flash led one time,chip enable(ready to TX or RX Mode),
// Spi disable,Spi clock line init high
//----------------------------------------------------------------------------------------------

void NRF_Init()
{
    pinMode(CE,  OUTPUT);
    pinMode(SCK_PIN, OUTPUT);
    pinMode(CSN, OUTPUT);
    pinMode(MOSI_PIN,  OUTPUT);
    pinMode(MISO_PIN, INPUT);
    pinMode(IRQ, INPUT);
    digitalWrite(IRQ, 0);
    digitalWrite(CE, 0);    // chip enable
    digitalWrite(CSN, 1);   // Spi disable        
} 
//----------------------------------------------------------------------------------------------
// Function: SPI_RW();
// 
// Description:
// Writes one unsigned char to nRF24L01, and return the unsigned char read
// from nRF24L01 during write, according to SPI protocol
//----------------------------------------------------------------------------------------------
unsigned char SPI_RW(unsigned char Byte)
{
    unsigned char i;
    for(i=0;i<8;i++)    // output 8-bit
    {
        if(Byte&0x80)
        {
            digitalWrite(MOSI_PIN, 1);
        }
        else
        {
            digitalWrite(MOSI_PIN, 0);
        }
        digitalWrite(SCK_PIN, 1);
        Byte <<= 1;    // shift next bit into MSB..
        if(digitalRead(MISO_PIN) == 1)
        {
            Byte |= 1;    // capture current MISO bit
        }
        digitalWrite(SCK_PIN, 0);
    }
    return(Byte);    // return read unsigned char
}
//----------------------------------------------------------------------------------------------
 
//----------------------------------------------------------------------------------------------
// Function: SPI_RW_Reg();
// 
// Description:
// Writes value 'value' to register 'reg'
//----------------------------------------------------------------------------------------------
unsigned char SPI_RW_Reg(unsigned char reg, unsigned char value)
{
    unsigned char status;
    digitalWrite(CSN, 0);    // CSN low, init SPI transaction
    status = SPI_RW(reg);    // select register
    SPI_RW(value);           // and write value to it..
    digitalWrite(CSN, 1);    // CSN high again
    return(status);          // return nRF24L01 status unsigned char
}
//----------------------------------------------------------------------------------------------
 
//----------------------------------------------------------------------------------------------
// Function: SPI_Read();
// 
// Description:
// Read one unsigned char from nRF24L01 register, 'reg'
//----------------------------------------------------------------------------------------------
unsigned char SPI_Read(unsigned char reg)
{
    unsigned char reg_val;
    digitalWrite(CSN, 0);    // CSN low, initialize SPI communication...
    SPI_RW(reg);             // Select register to read from..
    reg_val = SPI_RW(0);     // ..then read register value
    digitalWrite(CSN, 1);    // CSN high, terminate SPI communication 
    return(reg_val);         // return register value
}
//----------------------------------------------------------------------------------------------
 
//----------------------------------------------------------------------------------------------
// Function: SPI_Read_Buf();
// 
// Description:
// Reads 'unsigned chars' #of unsigned chars from register 'reg'
// Typically used to read RX payload, Rx/Tx address
//----------------------------------------------------------------------------------------------
unsigned char SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
    unsigned char status,i;
    digitalWrite(CSN, 0);       // Set CSN low, init SPI tranaction
    status = SPI_RW(reg);       // Select register to write to and read status unsigned char
    for(i=0;i<bytes;i++)
    {
        pBuf[i] = SPI_RW(0);    // Perform SPI_RW to read unsigned char from nRF24L01//这个地方以前给pBuf[i]写成了pBuf
    }
    digitalWrite(CSN, 1);       // Set CSN high again
    return(status);             // return nRF24L01 status unsigned char
}
//----------------------------------------------------------------------------------------------
 
//----------------------------------------------------------------------------------------------
// Function: SPI_Write_Buf();
// 
// Description:
// Writes contents of buffer '*pBuf' to nRF24L01
// Typically used to write TX payload, Rx/Tx address
//----------------------------------------------------------------------------------------------
unsigned char SPI_Write_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
    unsigned char status,i;
    digitalWrite(CSN, 0);    // Set CSN low, init SPI tranaction
    status = SPI_RW(reg);    // Select register to write to and read status unsigned char
    for(i=0;i<bytes; i++)    // then write all unsigned char in buffer(*pBuf)
    {
        SPI_RW(*pBuf++);
    }
    digitalWrite(CSN, 1);    // Set CSN high again
    return(status);          // return nRF24L01 status unsigned char
}
//----------------------------------------------------------------------------------------------
 
//----------------------------------------------------------------------------------------------
// Function: TX_Mode();
// 
// Description:
// This function initializes one nRF24L01 device to
// TX mode, set TX address, set RX address for auto.ack,
// fill TX payload, select RF channel, datarate & TX pwr.
// PWR_UP is set, CRC(2 unsigned chars) is enabled, & PRIM:TX.
// 
// ToDo: One high pulse(>10us) on CE will now send this
// packet and expext an acknowledgment from the RX device.
//----------------------------------------------------------------------------------------------
void NRF_SeTxMode()
{
    digitalWrite(CE, 0);
    SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // Writes TX_Address to nRF24L01
    SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // RX_Addr0 same as TX_Adr for Auto.Ack
    SPI_RW_Reg(WRITE_REG + EN_AA, 0x00);      // Enable Auto.Ackipe0  0x01
    SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  // Enable Pipe0 0x01
    SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0x00); // 500us + 86us, 10 retrans... 0x1a
    SPI_RW_Reg(WRITE_REG + RF_CH, channel);        // Select RF channel 默认33
    SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x27);   // TX_PWR:0dBm, Datarate:2Mbps, LNA:HCURR
    SPI_RW_Reg(WRITE_REG + CONFIG, 0x0a);     // Set PWR_UP bit, enable CRC(2 unsigned chars) & Prim:TX. MAX_RT & TX_DS enabled.. 0x0e
    digitalWrite(CE, 1);
    //delayMicroseconds(20);
    //digitalWrite(CE, 0);
}
//----------------------------------------------------------------------------------------------
 
//----------------------------------------------------------------------------------------------
void NRF_Send(unsigned char *buf_tx)
{
    SPI_Write_Buf(WR_TX_PLOAD,buf_tx,TX_PLOAD_WIDTH);//以前这个地方直接发了tx_buf这样会导致用NRF_send函数无法发出自己定义的值
    //unsigned char sta = SPI_Read(STATUS);
    //debug use
    //Serial.print("status = ");
    //Serial.println(sta,HEX);
    //if(sta & TX_DS)  //BIT5
        //SPI_RW_Reg(FLUSH_TX,0x00);
    //if(sta & MAX_RT)
        //SPI_RW_Reg(FLUSH_TX,0x00);
    //unsigned char fifo_sta = SPI_Read(FIFO_STATUS);
    //debuf use
    //Serial.print("fifo_status = ");
    //Serial.println(fifo_sta,HEX);
    //SPI_RW_Reg(WRITE_REG+STATUS,sta);    // clear RX_DR or TX_DS or MAX_RT interrupt flag
}
//----------------------------------------------------------------------------------------------
 
//----------------------------------------------------------------------------------------------
unsigned char NRF_CheckAck()
{
    unsigned char sta = SPI_Read(STATUS);
    if(sta & TX_DS)  //BIT5
    {
        SPI_RW_Reg(FLUSH_TX,0x00);
        SPI_RW_Reg(WRITE_REG+STATUS,0xff);
        return(0);
    }
    if(sta & MAX_RT)
    {        
        SPI_RW_Reg(FLUSH_TX,0);
        SPI_RW_Reg(WRITE_REG+STATUS,0xff);
        return(0);
    }
    else
        return(1);
}
//----------------------------------------------------------------------------------------------
 
//----------------------------------------------------------------------------------------------
// Function: RX_Mode();
// 
// Description:
// This function initializes one nRF24L01 device to
// RX Mode, set RX address, writes RX payload width,
// select RF channel, datarate & LNA HCURR.
// After init, CE is toggled high, which means that
// this device is now ready to receive a datapacket.
//----------------------------------------------------------------------------------------------
void NRF_SetRxMode()
{
    digitalWrite(CE, 0);
    SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, RX_ADDRESS, TX_ADR_WIDTH);   // Use the same address on the RX device as the TX device
	SPI_RW_Reg(WRITE_REG + SETUP_AW, 0x03);
    SPI_RW_Reg(WRITE_REG + EN_AA, 0x00);                               // Enable Auto.Ackipe0 0x01
    SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);                           // Enable Pipe0
    SPI_RW_Reg(WRITE_REG + RF_CH, channel);                                 // Select RF channel 40
    SPI_RW_Reg(WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);                  // Select same RX payload width as TX Payload width
    SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x27);                            // TX_PWR:0dBm, Datarate:2Mbps, LNA:HCURR 0x07
    SPI_RW_Reg(WRITE_REG + CONFIG, 0x0b);                              // Set PWR_UP bit, enable CRC(2 unsigned chars) & Prim:RX. RX_DR enabled.. 0x0f

    digitalWrite(CE, 1);                                               // Set CE pin high to enable RX device
}
//----------------------------------------------------------------------------------------------
 
//----------------------------------------------------------------------------------------------
unsigned char NRF_Receive(unsigned char *buf_rx)
{
    unsigned char sta = SPI_Read(STATUS);
    //debug use
    //Serial.print("status = ");
    //Serial.println(sta,HEX);
    unsigned char rx_state = sta & RX_DR;  //BIT4
    if(rx_state)
    {
        SPI_Read_Buf(RD_RX_PLOAD, rx_buf, TX_PLOAD_WIDTH);             // read playload to rx_buf         
        SPI_RW_Reg(FLUSH_RX,0);       // clear RX_FIFO  
        SPI_RW_Reg(WRITE_REG+STATUS,sta);                             // clear RX_DR or TX_DS or MAX_RT interrupt flag
        return 1;
    }
    else
        return 0;
}
//----------------------------------------------------------------------------------------------
 
 
