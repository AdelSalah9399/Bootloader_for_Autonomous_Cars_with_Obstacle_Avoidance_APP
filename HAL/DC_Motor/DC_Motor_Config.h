#ifndef _MOTOR_CONFIG_H_
#define _MOTOR_CONFIG_H_


/*configure the frequency of driving the DC motors*/
#define Motor_Frequency			(u32)50

/*configure L298 Ena, ENb timer chanels*/
#define L298_EnaChanel          Chanel_1
#define L298_EnbChanel          Chanel_2

/*configure L298 Ena, ENb pins*/
#define L298_EnaPin             PIN6
#define L298_EnbPin             PIN7

/*configure L298 In1, In2, In3, In4 port*/
#define L298_InPort            	GPIOB
#define L298_InPortClk          AHB1_GPIOB

/*configure L298 In1, In2, In3, In4 pins*/
#define L298_In1Pin             PIN5
#define L298_In2Pin             PIN6
#define L298_In3Pin             PIN7
#define L298_In4Pin             PIN8


#endif
