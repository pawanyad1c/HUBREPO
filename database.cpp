#include"include/header.h"
#include"include/declaration.h"
sqlite3 *db;
inline int checkrc(int rc,const char* from)
{
	if( rc !=SQLITE_OK)
		return -1;

	else
	{
		LOG_IF(info,bug)<<from<<" Successfull"<<endl;
	}
	return 0;
}
static int callback4(void *self, int argc, char **argv, char **cno)
{

	return 0;
}
int write_to_file()
{
	LOG_IF(debug,bug)<<__func__<<"--->Start"<<endl;

	string data="";

	////////////////////////////////////////Preparing Text MSG //////////////////////////////////////////	
	data = data+"Train: "+sqld.train_no +
			"\nRake: "+sqld.rake +
			"\nCoachID: " +sqld.coach_id +
			"\nCoach: " + sqld.coach +
			"\nNext stn: " + sqld.next_stn +
			"\nDist: " + sqld.dist +
			"\nLoc: " +sqld.lat_long +
			"\n" + sqld.alert +
			"\nTime: " + sqld.time;
	/////////////////////////////////////////Writing to file//////////////////////////////////////////////////////
	if(strlen(sqld.train_no)<4||data.length()<110||data.length()>160)
	{
		LOG_IF(error,bug)<<"Data is incomplete returning -1 len is "<<data.length()<<endl;
		return -1;
	}
	//////////////////////////////////send function calling //////////////////////////////////////////////////////
	else if(recent_file((const char* )"WATER_LEVEL.txt",data)==-1)
	{
		LOG_IF(error,bug)<<"recent_file returnnig -1 becoz of read ret -1"<<endl;
	}

	LOG_IF(debug,bug)<<__func__<<"--->End"<<endl;

	return 0;
}
int timedate()
{
	time_t T= time(NULL);
	struct  tm tm = *localtime(&T);

	sprintf(sqld.time,"%02d/%02d/%02d %02d:%02d\n",tm.tm_mday, tm.tm_mon+1, (tm.tm_year+1900)%100,tm.tm_hour, tm.tm_min);
	printf("time is %s\n",sqld.time);

	return 0;
}
static int callback3(void *self, int argc, char **argv, char **cno)
{
	sqld.Status=atoi(argv[10]);
	if(sqld.Status==0)
	{

		memset(sqld.alert,'\0',sizeof(sqld.alert));

		strncpy(sqld.train_no,argv[1],5);
		strcpy(sqld.coach_id,argv[2]);
		strcpy(sqld.next_stn,argv[3]);
		strcpy(sqld.dist,argv[4]);
		strcpy(sqld.lat_long,argv[5]);

		strcpy(sqld.rake,"12225/12226-1");

		if(!strcmp(argv[8],"LOW"))
			strcpy(sqld.alert,"Alert: WATER LEVEL IS LOW");

		else if(!strcmp(argv[8],"MEDIUM"))
			strcpy(sqld.alert,"Event: WATER LEVEL IS MEDIUM");

		else if(!strcmp(argv[8],"HIGH"))
			strcpy(sqld.alert,"Event: WATER LEVEL IS FULL");

		strcpy(sqld.coach,argv[9]);

		printf("tarin no %s  and   %s\n",sqld.train_no,argv[1]);//train no
		printf("coach_id %s  and   %s\n",sqld.coach_id,argv[2]);//coachid
		printf("next_stn %s  and   %s\n",sqld.next_stn,argv[3]);//nxt stn
		printf("distance %s  and   %s\n",sqld.dist,argv[4]);//distance
		printf("lat_lan  %s  and   %s\n",sqld.lat_long,argv[5]);//lat_log
		//printf("date_time %s and   %s\n",sqld.dateargv[6]);//date_time
		//printf(" %s\n",argv[7]);//alarmtype

		printf("alarm status %s and  %s\n",sqld.alert,argv[7]);//alarm status
		printf(" coach    %s   and  %s\n",sqld.coach,argv[8]);//coach
	}
	return 0;
}

void* database(void *port)
{
	LOG_IF(debug,bug)<< __func__ <<"---->Start"<<endl;

	const char *sql,* self = "Callback function called";
	char *zErrMsg = 0, repeat[30]="-1";
	int rc=0, time_counter=180;

	/* Open database */
	while(true)
	{

		sleep(1);

		retry:
		memset(&sqld,'\0',sizeof(struct sqldata));
		rc = sqlite3_open("/opt/Bitcomm_Piccu/Piccu_backend/Route.db", &db);
		if(checkrc(rc,"Open Database")==-1)
		{

			LOG_IF(error,bug)<<"Can't open database: Retrying  Error is "<< sqlite3_errmsg(db)<<endl;
			sleep(1);
			goto retry ;
					
		}

		///////////////////* Create SQL statement *////////////////////////////////////////////////////////
		sql= "SELECT * FROM SMS_table ORDER BY rowid desc LIMIT 1";
		rc = sqlite3_exec(db, sql, callback3 , (void*)self, &zErrMsg);
		if(checkrc(rc,"Select exe")==-1)
		{
			LOG_IF(error,bug)<<"select command failed : Retrying  Error is "<< sqlite3_errmsg(db)<<endl;
			if((sqlite3_close(db))!=SQLITE_OK)
			{LOG_IF(error,bug)<<" Failed to close db. Error is " <<endl;}

			sleep(1);
			goto retry ;
		}
		if(strcmp(repeat,sqld.alert)==0||sqld.Status!=0)
		{	
			if((sqlite3_close(db))!=SQLITE_OK)
			{LOG_IF(error,bug)<<" Failed to close db. Error is " <<endl;}
			LOG_IF(info,bug)<<"Data Repeating In SMS Table Please Wait Looking for New"<<endl;
			sleep(20);//600
			continue;
		}
		else
		{

			again:	sql="UPDATE SMS_table set Status = 1 order BY rowid desc LIMIT 1";
			rc = sqlite3_exec(db, sql, callback4, (void*)self, &zErrMsg);
			if(checkrc(rc,"Update exe")==-1)
			{
				LOG_IF(error,bug)<<"Failed to Update status in DB, Error is "<< sqlite3_errmsg(db)<<endl;
				sleep(2);
				goto again;
			}
			if((sqlite3_close(db))!=SQLITE_OK)
			{LOG_IF(error,bug)<<" Failed to close db. " <<endl;}

			strcpy(repeat,sqld.alert);
			timedate();
			write_to_file();
			while(time_counter)
			{
				sleep(10);
				LOG_IF(info,bug)<<" Time Counter Running Upto 30 min sec " <<endl;
				time_counter--;
			}
			time_counter=180;
		}
	}

	LOG_IF(debug,bug)<< __func__ <<"---->End"<<endl;

	return 0;
}
/*
   int main()
   {
   plog_util((char*) "100000000"); //100MB

   int a=3;
   database(&a);

   return 0;
   }
 */
