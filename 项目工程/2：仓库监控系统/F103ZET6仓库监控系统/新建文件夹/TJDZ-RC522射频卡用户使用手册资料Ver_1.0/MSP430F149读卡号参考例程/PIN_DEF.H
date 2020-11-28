
//***************************************************************************//
//                                                                           //
//                       ���Ź��ܶ���                                        //
//                                                                           //
//***************************************************************************//

#define LED_RED                BIT0  // P2.0 �������
#define LED_GRE                BIT0  // P2.0 �̵�����
#define RF_LPCTL               BIT3  // P2.3 ��Ƶ�����߿��� ------RST   
#define RF_SS                  BIT7  // p2.7 ��Ƶ���ӻ�ѡ��(SS)---SDA
#define RF_SCLK                BIT6  // p2.6 ��Ƶ������ʱ�����(SCLK)
#define RF_DATA_OUT            BIT5  // p2.5 ��Ƶ���������(MOSI)
#define RF_DATA_IN             BIT1  // p2.1 ��Ƶģ������(MISO) 

//****************************************************************************
//                                                                           *
//                           �����궨��                                      *
//                                                                           *
//****************************************************************************

//------------------------------- RC522������ ------------------------------//
//#define    RF_POWER_ON             P8OUT &=~RF_PCTL                      // ��Ƶģ���ϵ�
//#define    RF_POWER_OFF            P8OUT |= RF_PCTL                      // ��Ƶģ���µ�
#define    RF_POWER_ON             _NOP()                                // ��Ƶģ���ϵ�
#define    RF_POWER_OFF            _NOP()                                // ��Ƶģ���µ�
#define    RED_LED_ON              P2OUT &=~LED_RED                      // �������
#define    RED_LED_OFF             P2OUT |= LED_RED                      // ���Ϩ��
#define    GRE_LED_ON              P2OUT &=~LED_GRE                      // �̵�����
#define    GRE_LED_OFF             P2OUT |= LED_GRE                      // �̵�Ϩ��

#define    RF_SLEEP                P2OUT &=~RF_LPCTL                     // ��Ƶģ�黽��
#define    RF_WAKEUP               P2OUT |= RF_LPCTL                     // ��Ƶģ������
#define    SCLK_HIGH               P2OUT |= RF_SCLK                      // ����ʱ���ø�
#define    SCLK_LOW                P2OUT &=~RF_SCLK                      // ����ʱ���õ�
#define    DATA_OUT_HIGH           P2OUT |= RF_DATA_OUT                  // �����ø�
#define    DATA_OUT_LOW            P2OUT &=~RF_DATA_OUT                  // �����õ�
#define    SS_HIGH                 P2OUT |= RF_SS                        // �ӻ�ѡ����Ч
#define    SS_LOW                  P2OUT &=~RF_SS                        // �ӻ�ѡ����Ч
#define    DATA_IN                 P2IN  &  RF_DATA_IN                   // ��������

#define    NSS522_1                P2OUT |= RF_SS                        // �ӻ�ѡ����Ч       
#define    NSS522_0                P2OUT &=~RF_SS                        // �ӻ�ѡ����Ч
#define    SCK522_1                P2OUT |= RF_SCLK                      // ����ʱ���ø�
#define    SCK522_0                P2OUT &=~RF_SCLK                      // ����ʱ���õ�
#define    SI522_1                 P2OUT |= RF_DATA_OUT                  // �����ø�        
#define    SI522_0                 P2OUT &=~RF_DATA_OUT                  // �����õ�        
#define    SO522                 ((P2IN  &  RF_DATA_IN)>>1)              // ��������
#define    RST522_1                P2OUT |= RF_LPCTL
#define    RST522_0                P2OUT &=~RF_LPCTL


//------------------------------ �������  ---------------------------------------//
#define    SUCCESS                    0
#define    FAILURE                    1
#define    CRC_ERROR                  2
