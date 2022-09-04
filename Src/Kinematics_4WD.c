/**************************************************************************
�ļ��汾������� V1.0
�ļ����ܣ�
1��4WD�˶�ѧ��⺯��
2��4WD�˶�ѧ���⺯��
**************************************************************************/
#include "Kinematics_4WD.h"
#include "ShareWare.h"

/**************************************************************************
�������ܣ�4WD�˶�ѧ��⺯��
��ڲ����������˶�ѧ�ṹ�����
����  ֵ��ͨ�����복������ٶ�����ٶȼ����4�������ת��
**************************************************************************/
void Kinematics_4WD_CalculateRPM(Kinematics_Struct *Kinematics)
{
	float linear_vel_x_mins;
	float angular_vel_z_mins;
	float tangential_vel;
	float x_rpm;
	float tan_rpm;

	//convert m/s to m/min
	linear_vel_x_mins = Kinematics->Linear_X * 60;

	//convert rad/s to rad/min
	angular_vel_z_mins = Kinematics->Angular_Z * 60;

	tangential_vel = (float)angular_vel_z_mins * (((float)FR_WHEELS_DISTANCE / 2) + ((float)LR_WHEELS_DISTANCE / 2));

	x_rpm = (float)linear_vel_x_mins / WHEEL_CIRCUMFERENCE;
	tan_rpm = (float)tangential_vel / WHEEL_CIRCUMFERENCE;

	//calculate for the target motor RPM and direction
	Kinematics->M1_RPM = x_rpm - tan_rpm;//M1���Ŀ��ת��
	Kinematics->M2_RPM = x_rpm + tan_rpm;//M2���Ŀ��ת��	
	Kinematics->M3_RPM = x_rpm - tan_rpm;//M3���Ŀ��ת��
	Kinematics->M4_RPM = x_rpm + tan_rpm;//M4���Ŀ��ת��
}

/**************************************************************************
�������ܣ�4WD�˶�ѧ���⺯��
��ڲ����������ٶȽṹ�������4WD���ת�ٽṹ�����
����  ֵ��ͨ������4�������ת�ټ������������ٶ�����ٶ�
**************************************************************************/
void Kinematics_4WD_GetVelocities(Kinematics_Struct *Kinematics)
{
	float average_rps_x;
	float average_rps_a;

	//convert average revolutions per minute to revolutions per second
	average_rps_x = (float)((float)(Kinematics->M1_RPM + Kinematics->M2_RPM + Kinematics->M3_RPM + Kinematics->M4_RPM) / 4) / 60; // RPM
	Kinematics->Linear_X = average_rps_x * WHEEL_CIRCUMFERENCE; // m/s

	//convert average revolutions per minute to revolutions per second
	average_rps_a = (float)((float)(-Kinematics->M1_RPM + Kinematics->M2_RPM - Kinematics->M3_RPM + Kinematics->M4_RPM) / 4) / 60;
	Kinematics->Angular_Z =  (float)(average_rps_a * WHEEL_CIRCUMFERENCE) / (((float)FR_WHEELS_DISTANCE / 2) + ((float)LR_WHEELS_DISTANCE / 2)); //  rad/s
}
