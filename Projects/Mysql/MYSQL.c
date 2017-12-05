
//gcc -Wall main.c -o out 'mysql_config --cflags' 'mysql_config --libs'

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

#define DATABASE_NAME  "login"
#define DATABASE_USERNAME "root"
#define DATABASE_PASSWORD "raspberry"


int mysql_connect (void);
void mysql_disconnect (void);
int mysql_read(void);
int mysql_write(void);
int mysql_create(void);
int mysql_login(void);
MYSQL *mysql1;


int main(int argc, char **argv)
{
	
	int opc='_';
	//--MENU
	while(1){
	printf("\n\nSelect Option\n1 - Login\n2 - Create User\n3 - Show Database\n4 - Exit\n\n> ");
	scanf("%d",&opc);
	
	if(mysql_connect()<0)
		return -1;
	
	if (opc == 1){
		getchar();
			mysql_login();

	}else if(opc == 2){
		getchar();
		mysql_create();
	}else if(opc == 3){
		getchar();
		mysql_read();
	}else if(opc == 4){
		break;
	}else{
		printf("OTRO\n");
	}
	
}
	
	
	mysql_disconnect();
	return 0;
}


int mysql_create(void){
    char user[200];
    char pass[200];
    char add[200];
    char phn[200];
    char email[200];
    char type[2];
	

	printf("\nCREATE USER \n");
		printf("\nUSER: \n> ");
        fgets(user,200,stdin);
        user[strlen(user) - 1] = 0;
        printf("\nPASSWORD: \n> ");
        fgets(pass,200,stdin);
        pass[strlen(pass) - 1] = 0;
        printf("\nADDRESS: \n> ");
        fgets(add,200,stdin);
        add[strlen(add) - 1] = 0;
        printf("\nPHONE: \n> ");
        fgets(phn,200,stdin);
        phn[strlen(phn) - 1] = 0;
        printf("\nEMAIL: \n> ");
        fgets(email,200,stdin);
        email[strlen(email) - 1] = 0;
        printf("\nTYPE: \n1 - Admin\n2 - User\n3 - Super User\n\n> ");
        fgets(type,200,stdin);
        type[strlen(type) - 1] = 0;
        
    
        char str[200]="";
        strcat(str,"INSERT into users (user, password,address,phone,email, type) values ('");
        strcat(str,user);
        strcat(str,"','");
        strcat(str,pass);
        strcat(str,"','");
        strcat(str,add);
        strcat(str,"','");
        strcat(str,phn);
        strcat(str,"','");
        strcat(str,email);
        strcat(str,"',");
        strcat(str,type);
        strcat(str,")");
        
        
        if(mysql1 != NULL){
        if (mysql_query(mysql1, str))
        {
            printf("Error %s\n", mysql_error(mysql1));
            return -1;
        }
	}
	//printf("Insert successful \n");
	mysql_read();
	return 1;
		
}

int mysql_login(void){
	//TODOS   char qerty[]="SELECT users.user AS User, users.password AS Pass,type.type AS Type FROM users  JOIN type ON (users.type = type.id) GROUP BY users.id;";
	//UNO char qerty[]="SELECT users.user AS User, users.password AS Pass,type.type AS Type FROM users  JOIN type ON (users.type = type.id) WHERE user='rr' AND password='rr';";
	
	int num_rows=0;
	char user[200];
    char pass[200];
	

	printf("\nLOGIN \n");
		printf("\nUSER: \n> ");
        fgets(user,200,stdin);
        user[strlen(user) - 1] = 0;
        printf("\nPASSWORD: \n> ");
        fgets(pass,200,stdin);
        pass[strlen(pass) - 1] = 0;
	
	char str[200]="";
        strcat(str,"SELECT users.user AS User,users.address AS Address,users.phone AS Phone,users.email AS Email,type.type AS Type FROM users  JOIN type ON (users.type = type.id) WHERE user='");
        strcat(str,user);
        strcat(str,"' AND password='");
        strcat(str,pass);
        strcat(str,"';");
        
	if (!mysql_query(mysql1, str))
        {
        	MYSQL_RES *result = mysql_store_result(mysql1);
        	if (result != NULL)
        	{
        		//Get the number of columns
        		num_rows = mysql_num_rows(result);
        		int num_fields = mysql_num_fields(result);
			printf("------------------------------------------\n");
        		MYSQL_ROW row;			//An array of strings
        		while( (row = mysql_fetch_row(result)) )
        		{
        			if(num_fields >= 5)
        			{
        				char *value_name = row[0];
        				char *value_add = row[1];
        				char *value_phn = row[2];
        				char *value_email = row[3];
        				char *value_type = row[4];

        				printf( "User:%s\nAddress:%s\nPhone:%s\nEmail:%s\nType:%s\n", value_name,value_add,value_phn,value_email,value_type);
        	        }
        		}
        		printf("------------------------------------------\n");
   	            mysql_free_result(result);
        	}
        	else
				return -1;
        }
     else
		return -1;
	return num_rows;
}

int mysql_read(void){
	int num_rows=0;
	 if (!mysql_query(mysql1, "SELECT * FROM users"))
        {
        	MYSQL_RES *result = mysql_store_result(mysql1);
        	if (result != NULL)
        	{
        		//Get the number of columns
        		num_rows = mysql_num_rows(result);
        		int num_fields = mysql_num_fields(result);
			printf("-------------------------------------------------------\n");
        		MYSQL_ROW row;			//An array of strings
        		while( (row = mysql_fetch_row(result)) )
        		{
        			if(num_fields >= 6)
        			{
        				char *value_id = row[0];
        				char *value_name = row[1];
        				char *value_pass = row[2];
        				char *value_add = row[3];
        				char *value_phone = row[4];
        				char *value_email= row[5];
        				char *value_type= row[6];

        				printf( "ID:%s, User:%s, Password:%s,Address:%s,Phone:%s,Email:%s Type:%s \n", value_id,value_name,value_pass,value_add,value_phone,value_email,value_type);
        	        }
        		}
        		printf("-------------------------------------------------------\n");
   	            mysql_free_result(result);
        	}
        	else
				return -1;
        }
     else
		return -1;
	return num_rows;
}

int mysql_write(void){
	 char query[]="INSERT INTO users (user, password,address,phone,email, type) VALUES ('Juanello','250125Esteban',3);";
	 if(mysql1 != NULL){
        if (mysql_query(mysql1, query))
        {
            printf("Error %s\n", mysql_error(mysql1));
            return -1;
        }
	}
	printf("Insert successful \n");
	return 1;
}

int mysql_connect (void)
{
    //initialize MYSQL object for connections
	mysql1 = mysql_init(NULL);

    if(mysql1 == NULL)
    {
        printf("Error: %s\n", mysql_error(mysql1));
        return -1;
    }

    //Connect to the database
    if(mysql_real_connect(mysql1, "localhost", DATABASE_USERNAME, DATABASE_PASSWORD, DATABASE_NAME, 0, NULL, 0) == NULL)
    {
    	printf("Error:%s\n", mysql_error(mysql1));
    	return -1;
    }
    else
    {
        //printf("Database connection successful.\n");
    }
    
    return 1;
}

void mysql_disconnect (void)
{
    mysql_close(mysql1);
    //printf( "Disconnected from database.\n");
}
