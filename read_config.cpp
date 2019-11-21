#include "include/header.h"
#include "include/declaration.h"
inline int wrong_mob_no(struct sms scheck,char* check)
{
	LOG_IF(warning,bug)<<"Error in config.txt file see for Sensor "<<scheck.sensor_name<<" this --->"<<check<<" mobile No must be 13 Digit "<<"--->do Handling "<<endl;
		                exit(1);
}
int setsubstr(string s)
{
/*   // this command has to handle for wrong mobile no */
	//LOG_IF(debug,bug)<<__func__<<"---->Start"<<endl;
	int i=0;
	size_t pos = 0;
	string token;
	string delimiter="::";

	if((pos = s.find(delimiter)))
	{
		token = s.substr(0, pos);
		strcpy(obj[nol].sensor_name,token.c_str());
		s.erase(0, pos + delimiter.length());

	}
	while ((pos = s.find(delimiter)) != string::npos)
	{
		
		token = s.substr(0, pos);
//		if(strlen(token.c_str())==13)
//		{
			strcpy(obj[nol].mob_no[i],token.c_str());
			i++;
			s.erase(0, pos + delimiter.length());
//		}
//		else wrong_mob_no(obj[nol],(char*)token.c_str());

	}
//	if(strlen(s.c_str())!=13)
//	{
//		wrong_mob_no(obj[nol],(char*)s.c_str());
//	}
//	else{

		strcpy(obj[nol].mob_no[i],s.c_str());
		i++;
		obj[nol].t_mob_no=i;
//	}
	//LOG_IF(debug,bug)<<__func__<<"---->Start"<<endl;
	return 0;
}


int read_config()
{
	LOG_IF(debug,bug) << __func__ << "---->Start"<<endl;

	string line;
	fstream file("config.txt");//It should be in current directory
	if (file.is_open())
	{

		while (file.good())
		{
			getline(file, line);
			setsubstr(line);
			nol++;
		}
		file.close();
	}
	else LOG_IF(error,bug) << "Unable to open config.txt file"<<endl;

	/*if (bug == 1)
	{
		for (int k = 0; k < nol - 1; k++)
		{
			cout << "sensor_name is ---->" << obj[k].sensor_name << endl;

			for (int z = 0; z<obj[k].t_mob_no; z++)
			{
				cout << "total mob no "<<obj[k].t_mob_no<<" and mob no's is " << obj[k].mob_no[z] << endl;
			}
		}
	}*/
	LOG_IF(debug,bug) << __func__ << "---->End"<<endl;

	return 0;

}
