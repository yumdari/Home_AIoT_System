#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <string.h>

#include <netdb.h>
#include <mysql/mysql.h>
#include <errno.h>
#include <sys/types.h>
#include <wiringPi.h>

#define BUF_SIZE 100
#define MAX_CLNT 256
#define TCP_PORT 5000

void *handle_clnt(void *arg);
void send_msg(char *msg, int len);
void error_handling(char *msg);

static char *host = "localhost";
static char *user = "phpmyadmin";
static char *pass = "kcci";
static char *dbname = "Momstouch";

int clnt_cnt =0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;


//int pre_value=100;

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_sz;
	pthread_t t_id;
	if(argc!=2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	pthread_mutex_init(&mutx, NULL);
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);

	int on=1;
	setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

	memset(&serv_adr, 0, sizeof(serv_adr));
	memset(&clnt_adr, 0, sizeof(clnt_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");

	while(1)
	{
		clnt_adr_sz=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

		pthread_mutex_lock(&mutx);	
		if(clnt_cnt == MAX_CLNT)
		{
			clnt_cnt = 0;
		}
		clnt_socks[clnt_cnt++]=clnt_sock;
		pthread_mutex_unlock(&mutx);

		pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
		pthread_detach(t_id);
		printf("Connected client IP: %s  fd: %d \n", inet_ntoa(clnt_adr.sin_addr),clnt_sock);
	}

	close(serv_sock);
	return 0;
}

void *handle_clnt(void *arg)
{
	int clnt_sock=*((int*)arg);
	int str_len=0, i;
	int index=0;
	char msg[BUF_SIZE];

	while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0)
	{
		send_msg(msg, str_len);
		memset(msg,0,sizeof(msg));	
	}

	pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_cnt; i++)
	{
		if(clnt_sock==clnt_socks[i])
		{
			while(i++<clnt_cnt-1)
				clnt_socks[i]=clnt_socks[i+1];
			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutx);
	close(clnt_sock);
	return NULL;
}

void send_msg(char *msg, int len)
{
	int i=0;
	char *result="";
	char *parsing[5]={""};
	int res=0;

	MYSQL *conn;
	MYSQL_RES *res_ptr;
    MYSQL_ROW sqlrow;
	
	int Gas_Motor=0, Temp=0, Humidity=0, Led1=0,Led2=0,Led3=0,Finger=0,Cam=0;
	int ins=0;
	int k;
	int j=0;

	char Transmit[200] = "";
	char Alarm[200] = "";
	int Alarm_send = 3;
//	char msg2[BUF_SIZE];

	conn = mysql_init(NULL);
	char in_sql[200] = {0};

	if(!(mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0)))
    {
        fprintf(stderr, "error:%s[%d]\n", mysql_error(conn), mysql_errno(conn));
        exit(1);
    }
    else
        //printf("Connection Successful!");

//parsing

	memset(parsing,0,sizeof(parsing));
	memset(in_sql,0,sizeof(in_sql));
	result = strtok(msg, ":");
	while(result!=NULL)
	{
		parsing[j++]=result;
		result = strtok(NULL, ":");
	}
	if(!(strcmp(parsing[0], "PRO")))
	{
		Temp = atoi(parsing[1]);
		Humidity = atoi(parsing[2]);
		sprintf(in_sql, "update Sensing set Temp = %d, Humidity = %d", Temp, Humidity);
		ins = mysql_query(conn, in_sql);
	}
	if(!(strcmp(parsing[0], "GAS")))
	{
		Gas_Motor = atoi(parsing[1]);
		sprintf(in_sql, "update Sensing set Gas_Motor = %d", Gas_Motor);
		ins = mysql_query(conn, in_sql);
	}

	//ESP
	if(!(strcmp(parsing[0], "ESP")))
	{
		Finger = atoi(parsing[1]);
		sprintf(in_sql, "update Sensing set Alarm = %d", Finger);
		ins = mysql_query(conn, in_sql);
		Finger = 0;
	}
	//ESP end
	
	if(!(strcmp(parsing[0], "LED")))
	{
		Led1 = atoi(parsing[1]);
		Led2 = atoi(parsing[2]);
		Led3 = atoi(parsing[3]);
		sprintf(in_sql, "update Sensing set Led1 = %d, Led2 = %d, Led3 = %d", Led1, Led2, Led3);
		ins = mysql_query(conn, in_sql);	
	}
	//Cam
	if(!(strcmp(parsing[0], "CAM")))
	{
		Cam = atoi(parsing[1]);
		sprintf(in_sql, "update Sensing set Alarm = %d", Cam);
		ins = mysql_query(conn, in_sql);
		Cam = 0;
	}
	//Cam end

//parsing end

//Select
	pthread_mutex_lock(&mutx);
	res = mysql_query(conn, "SELECT Temp, Humidity, Gas_Motor, Led1, Led2, Led3, Alarm FROM Sensing");
	memset(Transmit,0,sizeof(Transmit));
	memset(Alarm,0,sizeof(Alarm));
	strcat(Transmit, "Sensor/");
	strcat(Alarm, "ALERT/");
	if(!res)
	{
		res_ptr = mysql_store_result(conn);
		if(res_ptr)
		{
			while((sqlrow = mysql_fetch_row(res_ptr)))
			{
//				printf("%10s %10s %10s %10s\n", sqlrow[0], sqlrow[1], sqlrow[2], sqlrow[3]);
				for(int ss = 0; ss<6; ss++)
				{
					strcat(Transmit,sqlrow[ss]);
					if(ss!=5)
						strcat(Transmit,"/");
				}
				Alarm_send=atoi(sqlrow[6]); //0:얼굴 1:택배 2:지문
				strcat(Alarm,sqlrow[6]);
			}
		}
	}
	pthread_mutex_unlock(&mutx);
//Select end

//Write start
	pthread_mutex_lock(&mutx);
	for(i=0;i<clnt_cnt; i++)
	{
		if(Alarm_send==0)	//얼굴
		{
			write(clnt_socks[i], Alarm, 50);
			printf("%s\n", Alarm);
		}
		else if(Alarm_send==1)	//택배
		{
			write(clnt_socks[i], Alarm, 50);
			printf("%s\n", Alarm);
		}
		else if(Alarm_send==2)	//지문
		{
			write(clnt_socks[i], Alarm, 50);
			printf("%s\n", Alarm);
		}
		else if(Alarm_send==3) //그외
		{
			write(clnt_socks[i], Transmit, 150);
			printf("%s\n", Transmit);
		}
	}
	sprintf(in_sql, "update Sensing set Alarm = %d", 3);
	Alarm_send=3;
	ins = mysql_query(conn, in_sql);	
	pthread_mutex_unlock(&mutx);
//Write end

}

void error_handling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
