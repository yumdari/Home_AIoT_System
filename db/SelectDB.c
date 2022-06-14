#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <wiringPi.h>


static char *host = "localhost";
static char *user = "phpmyadmin";
static char *pass = "kcci";
static char * dbname = "Motor";

//void finish_with_error(MYSQL *conn){
//	fprintf(stderr, "%s\n",mysql_error(conn));
//	mysql_close(conn);
//	exit(1);
//}

int main()
{
	MYSQL *conn;
	MYSQL_RES *res_ptr;
	MYSQL_ROW sqlrow;

	int res;

	conn = mysql_init(NULL);
	int sql_index, flag = 0;
	char in_sql[200] = {0};


	if(!(mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0)))
	{
		fprintf(stderr, "error:%s[%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}
	else
		printf("Connection Successful!\n");
	
	while(1)
	{
		res = mysql_query(conn, "select Motorvalue from MotorControl order by ID DESC LIMIT 1");

		if(!res)
		{
			res_ptr = mysql_store_result(conn);
			if(res_ptr){
	//			printf("Retrived %lu rows\n", (unsigned long)mysql_num_rows(res_ptr));
				while((sqlrow=mysql_fetch_row(res_ptr)))
				{
					printf("%s\n", sqlrow[0]);
					delay(500);
				}
			}
		}
		else
			fprintf(stderr, "insert error %d: %s\n", mysql_errno(conn), mysql_error(conn));

//		mysql_free_result(res_ptr);
//		mysql_close(conn);
//		return EXIT_SUCCESS;
	}
}
