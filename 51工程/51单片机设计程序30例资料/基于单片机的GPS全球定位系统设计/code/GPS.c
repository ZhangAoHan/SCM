unsigned char data data_item=0
unsigned int rece_num=0

	
/*****************************************************************************************
*�������ƣ�void receive()interrupt 4
*�������ܣ�ʱ����ȡ
*��ں�������
*���ں�������
*****************************************************************************************/		
void receive()interrupt 4  //�����ж�
{
	unsigned char temp;
	RI=0;
	temp=SBUF;
	rece_num++;
	
	switch (data_item)
		{
			case 0:  if(temp==$)
					        data_item++;
					     break;
		  case 1:  if(temp=='G')
		  	          data_item++;
		  	       else
		  	       	  data_item=0;
		  	       break;
		  case 2:  if(temp=='P')
		  	          data_item++;
		  	       else
		  	       	  data_item=0;
		  	       break;
		  case 3:  if(temp=='R')
		  	          data_item++;
		  	       else
		  	       	  data_item=0;
		  	       break;	  
		  case 4:  if(temp=='M')
		  	          data_item++;
		  	       else
		  	       	  data_item=0;
		  	       break;	  
		  case 5:  if(temp=='C')
		  	          data_item++;
		  	       else
		  	       	  data_item=0;
		  	       break;	
		  case 6:  if(temp==',')
		  	         {
		  	         	data_item++;
		  	          g_Ptr=0;
		  	          g_Class=0;
		  	          g_DataVari=1;	
		  	         }
		  	       else
		  	       	  data_item=0;
		  	       break;	
		  case 7:  if(temp==',')
		  	         {
		  	          g_Ptr=0;
		  	          g_Class++;
		  	          break;	
		  	         }
		  	       if(temp=='$')
		  	         {
		  	          data_item=1;
		  	          break;	
		  	         }
		  	       switch(g_Class)
		  	       {
		  	       	case 0:             //��ȡʱ������
		  	       		      if(g_Ptr<6)
		  	       		      	g_DisTime[g_Ptr++]=temp;
		  	       		      break;	
		  	       }
		  default:
		  	       break;			       
		  	        
		}	
	
}