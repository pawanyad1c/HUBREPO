#include "include/header.h"
#include "include/declaration.h"
/*int re_birth(int fd)
{
	write_to_modem(fd,( char*)"\x1B");
	read_resp(fd);
	sleep(1);
	write_to_modem(fd,( char*)"\x1A");
	read_resp(fd);
	sleep(1);
	sprintf(cmd,"AT+CMGF=1\r");
	write_to_modem(fd,cmd);
	read_resp(fd);
	return 0;
}
*/

/*int check_AT(int fd)
{	
	int wret,count=0;
	LOG_IF(debug,bug)<<__func__<<"---->Start"<<endl;	

	LOG_IF(info,bug) <<" Sending AT Command "<<endl;
	sprintf(cmd,"AT\r");
	wret=write_and_check(fd,cmd);

	if(wret > 0)
	{
		for (;;)
		{
			LOG_IF(info,bug)<<"AT Try "<<count<<endl;
			if(read_resp(fd) > 0)
			{
				if(strstr(readbuf,"OK") != NULL)
				{
					LOG_IF(debug,bug)<<__func__<<"---->End"<<endl;
					return 0;
				}
				else
				{
					LOG_IF(debug,bug)<<__func__<<" Failed to get OK respone retrying "<<endl;
					re_birth(fd);
					return -1;
				}
			}
			else
			{
				LOG_IF(warning,bug)<<"read_resp returning 0"<<endl;
				return -1;
			}
		}
	}
	else
	{
		LOG_IF(warning,bug) <<"Write returning -1 "<<endl;
		return -1;
	}
}

int open_and_set_flag()
{
	int fd = -1, counter = 0;


retry:  fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);

	counter = 0;
	if (fd < 3)
	{
		LOG_IF(error,bug) << "Failed To Open Port error no ->" << errno<< " and type of error -->" << strerror(errno) << " retrying "<< endl;
		sleep(2);
		counter++;
		if (counter == 20)
		{
			LOG_IF(error,bug)<<"unable to open modem so terminating"<<endl;
			exit(0);
		}
		goto retry;
	}
	else PLOG_IF(info,bug) << "Port Open Succesfully with fd " << fd << endl;
	//// Reading config.txt file Which Containing Sensors File name and their receipt neme////////
	read_config();
	////// Setting Flag for serial comunication  with Struct termios      ////////
	counter = 0;
	while (set_termios_flag(fd) == FALSE)
	{

		LOG_IF(error,bug)<<"set_termios_flag is unsuccesfully retrying"<<endl;
		counter++;
		if (counter == 20)
		{
			counter = 0;
			close_connection(fd); //End connection
			goto retry;
		}
	}
	////// Giving GSM Module For Attention(in Listen Mode) also call this when GSM Hang up and  no geting   Respone  ///////
	counter = 0;
	while (check_AT(fd) == FALSE)
	{
		counter++;
		if (counter == 5)
		{
			counter = 0;
			close_connection(fd); //End connection
			goto retry;
		}
	}

	/////// set GSM Modem in text mode and Gsm Encoding //////////////////////////////
	counter = 0;
	while (set_msg_env(fd) == FALSE)
	{
		counter++;
		if (counter == 20)
		{
			counter = 0;
			close_connection(fd); //End connection
			goto retry;
		}
	}
	return fd;
}
*/
int  recent_file(const char* Alert_name,string data)
{	
	LOG_IF(debug,bug)<<__func__<<"--->Start"<<endl;

	send_to(Alert_name,data.c_str());
	fflush(stdout);
	data.clear();

	LOG_IF(debug,bug)<<__func__<<"--->End"<<endl;
	return 0;
}
