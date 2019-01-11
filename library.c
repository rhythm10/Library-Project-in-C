#include <my_global.h>
#include <mysql.h>
#include<conio.h>

void show_error(MYSQL *con);
void addbooks(void);
int connection(void);
void addusers(void);
void fetchdata(void);
void searchbooks(void);
void editbooks(void);
void advancedsearch(void);
void database_connect(void);
void searchname(void);
void searchauthor(void);
void searchid(void);
void deletebook(void);
void searchprice(void);
void searchquantity(void);
void searchrack(void);
void advanc_search_byname(void);
void generic_search(char *);
void issue_books(void);

void show_error(MYSQL *con) 
{
  
   fprintf(stderr, "%s\n", mysql_error(con));
   mysql_close(con);
   exit(1);
}

struct books
{
    int id;
    char name[20];
    char author[20];
    int quantity;
    int price;
    int rack_no;   
}a;

char choice;

MYSQL *con = NULL;
#define MAX_STRING 1000
char query[MAX_STRING] = {0};


int main(int argc, char **argv)
{ 
    printf("Welcome to the Library Management Software\n");
    printf("Please Enter your Credential to Login(username/Password)\n");


    con = mysql_init(NULL);

    if (con == NULL) 
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    
    if (mysql_real_connect(con, "localhost", "rhythm", "password", NULL, 0, NULL, CLIENT_MULTI_STATEMENTS) == NULL) 
        show_error(con);

    char username[20],password[20];
    printf("Enter UserName : ");
    scanf("%s",username);
    printf("\nEnter Password : ");
    scanf("%s",password);

    snprintf(query, MAX_STRING, "SELECT username,password FROM library.users WHERE username = '%s' AND password = '%s'", username, password);
    
    if (mysql_query(con, query))
        show_error(con);


    MYSQL_RES *result = mysql_store_result(con);
  
    if (result->row_count == 0) 
    {
        fprintf(stdout, "%s\n", "Incorrect UserName or Password.");
    }
    else
    {
        database_connect();
    }
    

}

void database_connect(void)
{
    if (mysql_query(con, "CREATE DATABASE IF NOT EXISTS library;"))
    show_error(con);
  
    if(mysql_query(con, "USE library;"))
    show_error(con);
  
    if(mysql_query(con, "CREATE TABLE IF NOT EXISTS books(ID int(8) AUTO_INCREMENT,Name char(30),Author char(30),Quantity int(5),Price int(5), Rack_no int(5), PRIMARY KEY(ID));"))
    show_error(con);

    while(1)
    {
        printf("\n\nWhat do you want to do : \n");
        printf("1). Add Users\n");
        printf("2). Add Books Details \n");
        printf("3). Show Books Details \n");
        printf("4). Search Books\n");
        printf("5). Edit Book Details\n");
        printf("6). Issue Books\n");
        printf("7). Delete Particular Book\n");
        printf("8). Exit\n");
        printf("\nEnter a Choice : ");


        switch(getchar())
        {
            case '1':
                addusers();
                break;

            case '2':
                addbooks();
                break;
        
            case '3':
                fetchdata();
                break;

            case '4':
                searchbooks();
                break;

            case '5':
                editbooks();
                break;

            case '6':
                issue_books();
                break;

            case '7':
                deletebook();
                break;

            case '8':
                exit(0);

            default:
                printf("\nPlease Enter Correct Input\n");
                break;
        }
    }
}

void addusers(void)
{
    char username[30],password[20],fullname[30],users[10]= "user",user;
    printf("\nEnter Username : ");
    scanf("%s",username);
    printf("Enter Password : ");
    scanf("%s",password);
    printf("Enter Full Name : ");
    scanf("%s",fullname);
    //users[] = "user";
    printf("%s",users);

    snprintf(query, MAX_STRING, "INSERT INTO users(username,password,fullname,registered_date,role) VALUES ('%s','%s','%s',curdate(),'user')" , username,password,fullname);

    if(mysql_query(con, query))
    show_error(con);
}

void addbooks(void)
{
    printf("Insert values(Name,Author,Quantity,Price,Rack no.) into books.\n");
    
    printf("Name : ");
    scanf("%s",a.name);
    //printf("entered one is %s\n", a.name);
      
    printf("Author : ");
    scanf("%s",a.author);
    //printf("entered one is %s\n", a.author);
      
    printf("Quantity : ");
    scanf("%d",&a.quantity);
    //printf("entered one is %d\n", a.quantity);
      
    printf("Price : ");
    scanf("%d",&a.price);
    //printf("entered one is %d\n", a.price);
      
    printf("Rack No : ");
    scanf("%d",&a.rack_no);
    //printf("entered one is %d\n", a.rack_no);
        
    snprintf(query, MAX_STRING, "INSERT INTO books(Name, Author, Quantity, Price, Rack_no) VALUES ('%s', '%s', %d, %d, %d)", a.name, a.author, a.quantity, a.price, a.rack_no);
    printf("Query made is : %s\n", query);

    if(mysql_query(con, query))
    show_error(con);

    printf("Do you want to Enter More Records(Y/N) : ");
    
    scanf(" %c", &choice);
    
    if(choice == 'y' || choice == 'Y')
    {
        addbooks();
    }
}

void fetchdata()
{
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }   
  
    if (mysql_query(con, "SELECT * FROM books")) 
    {
        show_error(con);
    }
  
    MYSQL_RES *result = mysql_store_result(con);
  
    if (result == NULL) 
    {
        fprintf(stdout, "%s\n", "Currently there are no books in the library");
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    MYSQL_FIELD *field;

    while((field = mysql_fetch_field(result)))
    {
        printf("%-14s", field->name);
    }
    printf("\n");

    while ((row = mysql_fetch_row(result))) 
    { 
        for(int i = 0; i <= num_fields; i++) 
        { 
            printf("%-14s", row[i]); 
        } 
            printf("\n"); 
    }
  
    mysql_free_result(result);
    mysql_close(con);
    exit(0);
}

void issue_books(void)
{
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
}

void searchbooks()
{
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    printf("1). Search using Name\n");
    printf("2). Advanced Search\n");
    printf("Enter your Choice : ");
    int choose=0;
    scanf("%d",&choose);

    switch(choose)
    {
        case 1:
        {
            searchname();
        }

        case 2:
        {
            advancedsearch();
        }

        default:
        {
            printf("Enter Correct Choice\n");
            searchbooks();
        }    

    }
}

void advancedsearch()
{
    printf("\n1). Search using ID : \n");
    printf("2). Search using Author Name : \n");
    printf("3). Search using Quantity : \n");
    printf("4). Search using Price : \n");
    printf("5). Search using Rack No. \n");
    printf("6). Search using Book Name. \n");
    printf("7). Exit\n");
    printf("\nEnter your Choice : ");
    int choose;
    scanf("%d",&choose);

    switch(choose)
    {
        case 1:
            searchid();
        case 2:
            searchauthor();
        case 3:
            searchquantity();
        case 4:
            searchprice();
        case 5:
            searchrack();
        case 6:
            advanc_search_byname();
        case 7:
            exit(0);
        default:
            printf("Enter Correct Choice");
            break;

    }
}

void searchname()
{
    
    printf("Enter Book Name : ");
    char name[100];
    scanf("%s",name);
    
    snprintf(query, MAX_STRING, "SELECT * FROM books WHERE Name = '%s'", name);

    if (mysql_query(con, query)) 
    {
        show_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);
    
    if (result->row_count == 0) 
    {
        fprintf(stdout, "%s\n", "There is no book in the library matching the entered name.");
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) 
    { 
        for(int i = 0; i <= num_fields; i++) 
        { 
            printf("%s ", row[i]); 
        } 
        printf("\n"); 
    }

    mysql_free_result(result);
    mysql_close(con);
    exit(0);
    
}


void advanc_search_byname(void)
{
    printf("Enter Book Name : ");
    char name[100];
    scanf("%s",name);
    
    snprintf(query, MAX_STRING, "SELECT * FROM books WHERE Name LIKE '%%%s%%'", name);
    generic_search(query);
}

void searchid(void)
{

    printf("Enter ID  : ");
    int id;
    scanf("%d",&id);

    snprintf(query, MAX_STRING, "SELECT * FROM books WHERE ID LIKE '%%%d%%'", id);

    generic_search(query);

}

void searchauthor(void)
{
        printf("Enter Author Name : ");
        char author[20];
        scanf("%s",author);

        snprintf(query, MAX_STRING, "SELECT * FROM books WHERE Author LIKE '%%%s%%'", author);

        generic_search(query);
}

void searchprice(void)
{
        printf("Enter Price for Search : ");
        int price;
        scanf("%d",&price);

        snprintf(query, MAX_STRING, "SELECT * FROM books WHERE Price LIKE '%%%d%%'", price);

        generic_search(query);

}

void searchrack(void)
{

    printf("Enter Rack No. Search : ");
    int rackno;
    scanf("%d",&rackno);

    snprintf(query, MAX_STRING, "SELECT * FROM books WHERE Rack_no LIKE '%%%d%%'", rackno);
    generic_search(query);
}

void searchquantity(void)
{
        printf("Enter Quantity for Search : ");
        int quantity;
        scanf("%d",&quantity);

        snprintf(query, MAX_STRING, "SELECT * FROM books WHERE Quantity LIKE '%%%d%%'", quantity);

        generic_search(query);
}



void generic_search(char * query)
{
        if (mysql_query(con, query)) 
        {
            show_error(con);
        }

        MYSQL_RES *result = mysql_store_result(con);
  
        if (result->row_count == 0) 
        {
            fprintf(stdout, "%s\n", "There is no book in the library matching the entered Criteria.");
        }

        int num_fields = mysql_num_fields(result);

        MYSQL_ROW row;
  
        while ((row = mysql_fetch_row(result))) 
        { 
            for(int i = 0; i <= num_fields; i++) 
            { 
                printf("%s ", row[i]); 
            } 
            printf("\n"); 
        }
  
        mysql_free_result(result);
        mysql_close(con);
        exit(0);

}

void editbooks(void)
{
    printf("Enter Book ID  : ");
    int id;
    scanf("%d",&id);

    snprintf(query, MAX_STRING, "SELECT * FROM books WHERE ID = %d", id);

    if (mysql_query(con, query)) 
    {
        show_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result->row_count == 0) 
    {
        fprintf(stdout, "%s\n", "There is no book in the library matching the entered ID.");
    }

    int num_fields = mysql_num_fields(result);
    printf("%s\n", "Current Book Details: ");  
    MYSQL_FIELD *field;

    while((field = mysql_fetch_field(result)))
    {
        printf("%20s", field->name);
    }
    printf("\n");
    MYSQL_ROW row;



    while ((row = mysql_fetch_row(result))) 
    { 
        for(int i = 0; i <= num_fields; i++) 
        { 
            printf("%20s", row[i]); 
        } 
        printf("\n"); 
    }

    printf("\nEnter new Book Details : \n\n");
    printf("Insert new values(Name,Author,Quantity,Price,Rack no.) into books.\n");
    
    printf("Name : ");
    scanf("%s",a.name);
    //printf("entered one is %s\n", a.name);
      
    printf("Author : ");
    scanf("%s",a.author);
    //printf("entered one is %s\n", a.author);
      
    printf("Quantity : ");
    scanf("%d",&a.quantity);
    //printf("entered one is %d\n", a.quantity);
      
    printf("Price : ");
    scanf("%d",&a.price);
    //printf("entered one is %d\n", a.price);
      
    printf("Rack No : ");
    scanf("%d",&a.rack_no);
    //printf("entered one is %d\n", a.rack_no);
        
    snprintf(query, MAX_STRING, "UPDATE books SET Name = '%s', Author = '%s', Quantity = %d, Price = %d, Rack_no = %d WHERE ID = %d", a.name, a.author, a.quantity, a.price, a.rack_no,id);
    printf("Record Successfully Updated");

    if(mysql_query(con, query))
    show_error(con);

    mysql_free_result(result);
    mysql_close(con);
    exit(0);
}

void deletebook()
{
    printf("\nEnter Book ID to Delete Particular Book : ");
    int bookid;
    scanf("%d",&bookid);

    snprintf(query, MAX_STRING, "DELETE from books WHERE ID = %d",bookid);
    printf("Book has been Deleted Successfully\n");

    if(mysql_query(con, query))
    show_error(con);

}