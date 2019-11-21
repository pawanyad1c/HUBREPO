struct sms
{
        char sensor_name[50];
        char mob_no[10][15];
        int t_mob_no;
};
struct sqldata
{
        char train_no[20], 
	     rake[25],
	     coach_id[20],
              coach[20],
              next_stn[20],
              dist[20],
              alert[50],
	      lat_long[50],
             time[30];
        int last;
	int Status;
        //int lat,lon;
};


int check_AT(int);
int set_msg_env(int);

int re_birth(int);
int plog_util(char *);
int send_msg( char*,  const char*);
int send_to( const char* ,  const char* );
int recent_file( const char*,string);
int read_config();
void *database(void*);
void handler_1(int);
extern int sms_close(void);

#define BUFSIZE 500
#define PATH_MAX 100

extern struct termios  orignal_flag;
extern struct sms obj[20];//each array is showing type of sensor to mob no and no of mob
extern char readbuf[BUFSIZE];//reading resp comming from gsm modem
extern const char c;//just for adding " in AT command
extern char cmd[200];//using by sprintf and finally making a single command to send
extern char path[100];//name of sensor file which will create in SMS_SENSOR directory
extern pthread_t thread_id[4];
extern int bug; 
extern int nol;
extern struct sqldata sqld;
extern int interrupt_flag;
////////////////////////// Using In database.cpp and distance.cpp /////////////////////////

