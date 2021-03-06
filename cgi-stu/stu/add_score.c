#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

char * headname="head.html";
char * footname="footer.html";

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char name[32] = "\0";
	char scoreId[32] = "\0";
	char cno[32]="\0";
	char score[16]="\0";
	int status = 0;

	status = cgiFormString("name",  name, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get name error!\n");
		return 1;
	}



	status = cgiFormString("scoreId",  scoreId, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get scoreId error!\n");
		return 1;
	}

	status = cgiFormString("cno",  cno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get cno error!\n");
		return 1;
	}

	status = cgiFormString("score", score, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get score error!\n");
		return 1;
	}
	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "lyy", 3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

strcpy(sql, "create table score(id int not null primary key, name varchar(20) not null, cno int not null ,score int not null)");
if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
{
  if (ret!= 1)
  {
    fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
    mysql_close(db);
    return -1;
  }
}


sprintf(sql, "insert into score values(%d, '%s', %d, %d)", atoi(scoreId), name, atoi(cno), atoi(score));
if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
{
  fprintf(cgiOut, "%s\n", mysql_error(db));
  mysql_close(db);
  return -1;
}

	fprintf(cgiOut, "add score ok!\n");
	mysql_close(db);
	return 0;
}
