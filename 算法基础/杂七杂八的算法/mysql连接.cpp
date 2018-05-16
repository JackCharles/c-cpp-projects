#include <iostream>
#include <string>
#include "mysql.h"
#pragma comment(lib, "libmysql.lib")

using namespace std;

int main()
{
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_real_connect(&mysql, "localhost", "root", "root", "web_test", 3306, NULL, 0);
	mysql_set_character_set(&mysql, "gbk");

	//mysql_query(&mysql, "insert into users values(3,'ffffffff','ffdfgsfgsdfgsdfg')");
	MYSQL_STMT *stmt;
	MYSQL_BIND bind[3];

	memset(bind, 0, sizeof(bind));
	stmt = mysql_stmt_init(&mysql);
	char *sql = "insert into users values(?,?,?)";
	int a = mysql_stmt_prepare(stmt, sql, strlen(sql));
	int id = 4;
	bind[0].buffer_type = MYSQL_TYPE_SHORT;
	bind[0].buffer_length = sizeof(id);
	bind[0].buffer = &id;

	bind[1].buffer_type = MYSQL_TYPE_VARCHAR;
	bind[1].buffer_length = 5;
	bind[1].buffer = "1234";

	bind[2].buffer_type = MYSQL_TYPE_VARCHAR;
	bind[2].buffer_length = 7;
	bind[2].buffer = "123456";

	if (mysql_stmt_bind_param(stmt, bind))
		cerr << "bind error: " << mysql_stmt_error(stmt) << endl;
	if (mysql_stmt_execute(stmt))
		cerr << "excute statment error: " << mysql_stmt_error(stmt) << endl;

	mysql_query(&mysql, "select * from users");
	MYSQL_RES *res = mysql_store_result(&mysql);

	MYSQL_ROW row;
	while (row = mysql_fetch_row(res))
	{
		cout << row[0] << "   " << row[1] << "   " << row[2]<<endl;
	}

	mysql_free_result(res);
	mysql_close(&mysql);

	return 0;
}