/////////////////////////////////////////////////
//     Created and Edited      		            //
//         Last Edited 12 Nov 2019              //
//                                             //
/////////////////////////////////////////////////
#include "./include/header.h"
#include "./include/declaration.h"
#include "./include/global.h"
#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Appenders/ColorConsoleAppender.h>
using namespace plog;
extern int fd;
int main(int argc, char* argv[]) {

//	signal(SIGINT,handler_1);

	////////////////////////  Starting Loging Service ////////////////////////////////
	plog_util((char*) "100000000"); //100MB

	LOG_IF(debug,bug) << __func__ << "---->Start" << endl;

	read_config();

	/////// This Thread is responsible to Generate Alert files in SMS_SENDER directory//////////
	pthread_create(&thread_id[1], NULL, database, (void*) NULL);
	pthread_join(thread_id[1], &join);

	LOG_IF(debug,bug) << __func__ << "---->End" << endl;
	return 0;
}





////////////////////////////////Below function for close and plog_util///////////////////////////
void handler_1(int sigNo)
{
	cout<<"Interrupt Generated Signal No "<<sigNo<<endl;

	return;
}

int plog_util(char *argv)
{	
	int size=0;
	sscanf(argv,"%d",&size);
	LOG_IF(info,bug)<<"Given log file size in byte is ------->"<<size<<endl;	
	static RollingFileAppender<TxtFormatter> fileAppender("./include/log/sms_log.txt",size, 4); // Create the 1st appender.
	static ColorConsoleAppender<TxtFormatter> consoleAppender; // Create the 2nd appender.
	init(debug, &fileAppender).addAppender(&consoleAppender);// Initialize the logger with the both appenders.
	return 0;
}



int close_connection(int fd)
{
        LOG_IF(debug,bug)<<__func__<<"---->Start"<<endl;

	if(tcsetattr(fd,TCSANOW,&orignal_flag)!=0)
	{
		LOG_IF(error,bug)<<"tcsetattr failed to set old config"<<strerror(errno)<<endl;
	}

	if(close(fd)!=0)
	{
        	LOG_IF(error,bug)<<"Port fd failed to close"<<strerror(errno)<<endl;
	}

        LOG_IF(debug,bug)<<__func__<<"---->End"<<endl;

	return TRUE;
}

