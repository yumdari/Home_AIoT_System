#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>
#include <errno.h>
#include <sys/types.h>

static char *host = "localhost";
static char *user = "phpmyadmin";
static char *pass = "kcci";
static char *dbname = "Motor";

#include <wiringPi.h>

#define BUFSIZE 8192

#define TCP_PORT 5000

int srcSocket;
int dstSocket;

struct sockaddr_in s_addr;
struct sockaddr_in c_addr;
socklen_t len;
int n;

char textdata[11]="01234567890";
char buf1[BUFSIZE];
char buf2[BUFSIZE];

void server_init(){
	if((srcSocket = socket(AF_INET,SOCK_STREAM,0))<0){
		perror("socket error");
		exit(EXIT_FAILURE);
	}

	int on = 1;
	printf("Server Started\n");
	setsockopt(srcSocket,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

	memset((char*)&s_addr,0,sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_port = htons(TCP_PORT);

	if(bind(srcSocket,(struct sockaddr*)&s_addr,sizeof(s_addr))<0){
		perror("bind");
		exit(EXIT_FAILURE);
	}

	listen(srcSocket,5);

	len=sizeof(dstSocket);

}

void server_main(){
	if((dstSocket=accept(srcSocket,(struct sockaddr*)&c_addr,&len))<0){
		perror("accept error");
		exit(EXIT_FAILURE);
	}
	printf("connected from '%s'\n",inet_ntoa(s_addr.sin_addr));
}

int main(){
	server_init();
	MYSQL *conn;
//	MYSQL *con;
	MYSQL_RES *res_ptr;
	MYSQL_ROW sqlrow;

	int res;
	int ins=0;

	conn = mysql_init(NULL);
//	con = mysql_init(NULL);
	int sql_index, flag = 0;
	char in_sql[200] = {0};

	if(!(mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0)))
	{
		fprintf(stderr, "error:%s[%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}
	else
		printf("Connection Successful!\n");

	while(1){
		res = mysql_query(conn, "select Motorvalue from MotorControl order by ID DESC LIMIT 1");

		server_main();


		if(!res)
		{
			res_ptr = mysql_store_result(conn);
			if(res_ptr){
				while((sqlrow=mysql_fetch_row(res_ptr)))
				{
					strcpy(buf2,sqlrow[0]);
				}
			}
		}
		else(fprintf(stderr, "insert error %d: %s\n", mysql_errno(conn), mysql_error(conn)));

		memset(buf1,0,sizeof(buf1));
		recv(srcSocket,buf1,sizeof(buf1),0);
		printf("%s\n",buf1);

//		memset(buf2, 0, sizeof(buf2));
//		strcpy(buf2, "hello");
//		strcpy(buf2, sqlrow[0]);
		send(dstSocket,buf2,sizeof(buf2),0);
		printf("%s\n", buf2);
		//delay(2000);

		sprintf(in_sql, "insert into MotorControl(ID,CURTIME, CURDATE, Motorvalue) values (null, curtime(), curdate(), %d)", 0);
		ins = mysql_query(conn, in_sql);
		delay(1000);
		close(dstSocket);
	}
close(srcSocket);

return EXIT_SUCCESS;
}
