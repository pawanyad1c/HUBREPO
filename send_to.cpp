#include "include/header.h"
#include "include/declaration.h"



int send_to(const char *p, const char* sms_data)
{
	LOG_IF(debug,bug)<< __func__ <<"---->Start"<<endl;
	int i, j,send_ret=0;
	//////   No of For Loop Decided By No Of Sensor we have in config.txt   ////////
	for(i =0 ; i<nol-1;i++)
	{
		if(strcmp(p,obj[i].sensor_name)==0)
		{
			//printf("%s == %s\n",p,obj[i].sensor_name);
			break;
		}
		else if(i == nol-2)
		{
			LOG_IF(error,bug)<<" File Mapping is Failed to any sensor Name ----------->do Handling "<<endl;
			return 0;
		}
	}
	///// No of For Loop Decided by Sensor's data send to multiple no as in config.txt      ////////
	if(obj[i].t_mob_no!=0)
	{
		// sprintf(cmd,"AT+CMMS=2");
		//write_to_modem(fd,cmd);
		for(j=0;j<obj[i].t_mob_no;j++)
		{
			usleep(10000);
			send_ret=send_msg(obj[i].mob_no[j],sms_data);
			if(send_ret==0)
			{
				sleep(1);
				j=j-1;
			}
		}

	}
	else  LOG_IF(warning,bug)<<"Mobile No Not Available Corresponding to this Sensor "<<obj[i].sensor_name<<"--->do Handling"<<endl;


	LOG_IF(debug,bug)<<__func__<<"---->End"<<endl;

	return 0;

}

