#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<termios.h>
#include<unistd.h>
#include<ctype.h>
#include<conio.h>

void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void searchbooks(void);
void issuebooks(void);
void editbooks(void);
void viewbooks(void);
void password();
void closeapplication(void);
int t(void);
int getdata();
int checkid(int);

FILE *fs , *ft , *fp; //global files

int s;
char findbook;
char opassword[10]={"codewithc"}; //for password

char categories[][20]= {"Computer","Electronics","Mehanical","Civil","Aerospace"};

struct books
{
	int id;
	char stname[20]; //student name
	char name[20]; //book name
	char author[20];
	int quantity;
	float Price;
	int count;
	int rackno;
};
struct books a;

int main()
{
	password(); //for passwword confirmation
}
void password(void)
{
	int s,i=0;
	char pass[15],ch=0;
	printf("\n");
	for(i=0;i<25;i++)
	{
		printf("*");
	}

	printf("Password Protected");

	for(i=0;i<25;i++)
	{
		printf("*");
	}
	printf("\n\nEnter password to access Library as Administrator : \n");
	i=0;
	while(ch != 10) //10 is ascii value for enter
	{
		ch = getch(); //getch used for input
		if(ch != 10)
		{
			printf("*");
			pass[i] = ch;
			i++;
		}
	}
	pass[i]='\0';
	if(strcmp(pass,opassword) == 0) //for comparison
	{
		printf("\n\t\t\tPassword match\n");
		printf("\t\tPress any key to countinue!!!!\n");
		getch();
		mainmenu();
	}
	else
	{
		printf("\nIncorrect Password\n");
		getch();
		password();
	}
}

void mainmenu(void)
{
	int i;

	printf("\n");
	for(i=0;i<25;i++)
	{
		printf("*");
	}
	printf("MAIN MENU");
	for(i=0;i<25;i++)
	{
		printf("*");
	}
	printf("\n\n1. Add Books");
	printf("\n2. Delete Books");
	printf("\n3. Search  Books");
	printf("\n4. View Book List");
	printf("\n5. Edit Books");
	printf("\n6. Issue Books");
	printf("\n7. Close Whole Program");

	printf("\nEnter Your Choice : ");
	switch(getchar())
	{
		case '1':
		addbooks();
		break;

		case '2':
		deletebooks();
		break;

		case '3':
		searchbooks();
		break;

		case '4':
		viewbooks();
		break;

		case '5':
		editbooks();
		break;

		case '6':
		issuebooks();
		break;

		case '7':
		printf("\n\t\t\tLibrary Management System");
		printf("\n\t\tHope you are Satisfied with our Service\n\n");
		exit(0);

		default:
		{
			printf("\nEnter Correct Option");
			mainmenu();
			break;
		}

	}

}

void addbooks()
{
	int i=0;
	printf("\n");
	for(i=0;i<21;i++)
	{
		printf("*");
	}
	printf("Select Categories");
	for(i=0;i<21;i++)
	{
		printf("*");
	}

	printf("\n\n1. Computer");
	printf("\n2. Electronics");
	printf("\n3. Mechanical");
	printf("\n4. Civil");
	printf("\n5. Aerospace");
	printf("\n6. Back to Main Menu");

	printf("\nEnter your Choice : ");
	scanf("%d",&s);
	if(s==6)
	{
		mainmenu();
	}
	fp=fopen("book.dat","ab+"); //this will create or open book name file
	if(getdata()==1) //1 means new book details have been entered
	{
	
		fseek(fp,0,SEEK_END);
		fwrite(&a,sizeof(a),1,fp);
		fclose(fp);
		printf("\nRecord is saved Succesfully!!!\n");
		printf("Do you want to save more records (Y/N)");
		if(getch()=='Y' || getch()=='y')
		{
			addbooks();
		}
		else
		{
			mainmenu();
		}
	}
}

void deletebooks(void)
{
	int id;
	while(1)
	{
		int findbook,t;
		printf("Enter the book ID to Delete : ");
		scanf("%d",&id);
		fp = fopen("book.dat","wb+");
		rewind(fp);
		while(fread(&a,sizeof(a),1,fp)==1);
		{
			if(a.id==id)
			{
				printf("\nBook is Available\n");
				printf("Book name is %s",a.name);
				printf("\nAuthor is  %s",a.author);
				findbook = 't';
			}
		}
		if(findbook != 't')
		{
			printf("\nNo book is Found. Error!!!");
			mainmenu();
		}
		if(findbook == 't')
		{
			printf("\nDo you want to delete it (Y/N) ?");
			if(getch()=='y' || getch()=='Y')
			{
				ft = fopen("test.dat","wb+");
				rewind(fp);
				while(fread(&a,sizeof(a),1,fp)==1)
				{
					if(a.id != id)
					{
						fseek(ft,0,SEEK_CUR);
						fwrite(&a,sizeof(a),1,ft);
					}
				}
				fclose(ft);
				remove("book.dat");
				rename("test.dat","book.dat");
				fp = fopen("Book.dat","rb+");
				if(findbook=='t')
				{
					printf("Record is successfully deleted");
				}
				else
				{ 
					mainmenu();
				}
				fclose(fp);

			}
		}
	}
}
void searchbooks()
{
	int i,d,t,ch;
	for(i=0;i<20;i++)
	{
		printf("*");
	}
	printf("Search Books");
	for(i=0;i<20;i++)
	{
		printf("*");
	}
	printf("\n\n1. Search Book by Id :");
	printf("\n2. Search Book by Name : ");
	printf("\nEnter your Choice : ");
	fp = fopen("book.dat","rb+");
	ch = getchar();
	switch(ch)
	{
		case '1':
		{
			int i,n;
			printf("\n");
			for(i=0;i<16;i++)
			{
				printf("*");
			}
			printf("Search Book by Id");
			for(i=0;i<16;i++)
			{
				printf("*");
			}
			printf("\n\nEnter Book ID : ");
			scanf("%d",&d);
			while(fread(&a,sizeof(a),1,fp)==1)
			{
				if(a.id==d)
				{
					printf("\nThe book is Available");
					printf("\nID : %d",a.id);
					printf("\nName : %s",a.name);
					printf("\nAuthor : %s ",a.author);
					printf("\nQantity : %d ",a.quantity);
					printf("\nPrice : Rs.%.2f",a.Price);
					printf("\nRack No : %d ",a.rackno);
					findbook = t;
				}
			} 
			if(findbook != t)
			{
				printf("\nNo Record Found");
			}
			printf("\nTry another search?(Y/N)");
			if(getch()=='y' || getch()=='Y')
			{
				searchbooks();
			}
			else
			{
				mainmenu();
			}
			break;
		}	
		case '2':
		{
			int  i,d=0;
			char s[10];
			printf("\n");
			for(i=0;i<20;i++)
			{
				printf("*");
			}
			printf("Search Book by Name");
			for(i=0;i<20;i++)
			{
				printf("*");
			}
			printf("\nEnter Book Name : ");
			scanf("%s",s);
			while(fread(&a,sizeof(a),1,fp)==1)
			{
				if(strcmp(a.name,(s))==0) 
				{
					printf("\nThe Book is available");
					printf("\nID:%d",a.id);
					printf("\nName:%s",a.name);
					printf("\nAuthor:%s",a.author);
					printf("\nQantity:%d",a.quantity);		
					printf("\nPrice:Rs.%.2f",a.Price);
					printf("\nRack No:%d ",a.rackno);
					printf("\n");
					d++;
				}
			}
			if(d==0)
			{
				printf("\nNo Record Found");
			}
			printf("\nTry another search?(Y/N)");
			if(getch()=='y' || getch()=='Y')
			{
				searchbooks();
			}
			else
			{
				mainmenu();
			}
		}
		break;

		default:
		{
			printf("\nEnter Correct Choice either 1 or 2: ");
			searchbooks();
			break;
		}
	}
}
void viewbooks()
{

	int i=0,j=0;
	printf("*********************************Book List*****************************\n");
	printf("        ID     BOOK NAME    AUTHOR      QTY    PRICE     RackNo ");
	fp=fopen("book.dat","rb+");
	while(fread(&a,sizeof(a),1,fp)==1)
	{
		printf("\n\t%d",a.id);
		printf("\t%s",a.name);
		printf("\t    %s",a.author);
		printf("\t %d",a.quantity);
		printf("\t%.2f",a.Price);
		printf("\t   %d",a.rackno);
		printf("\n");
		i=i+a.quantity;
	}
	printf("\nTotal Books =%d\n",i);
	fclose(fp);
	printf("\nPress Enter for Main Menu otherwise Exit ");
	if(getch()==10)
	{
		mainmenu();
	}
	else
		exit(0);
}
void editbooks(void) 
{
int c=0,i;
int d,e;
	for(i=0;i<16;i++)
	{
	  printf("*");
	}
	printf("Edit Books Section");
	for(i=0;i<16;i++)
	{
	  printf("*");
	}
	char another='y';
	while(another=='y')
	{
		printf("Enter Book Id to be edited:");
		scanf("%d",&d);
		fp=fopen("book.dat","rb+");
		while(fread(&a,sizeof(a),1,fp)==1)
		{
			if(checkid(d)==0)
			{
				printf("\nThe book is availble");
				printf("\nThe Book ID:%d",a.id);
				printf("\nEnter new name:");
				scanf("%s",a.name);
				printf("\nEnter new Author:");
				scanf("%s",a.author);
				printf("\nEnter new quantity:");
				scanf("%d",&a.quantity);
				printf("\nEnter new price:");
				scanf("%f",&a.Price);
				printf("\nEnter new rackno:");
				scanf("%d",&a.rackno);
				printf("\nThe record is modified");
				fseek(fp,ftell(fp)-sizeof(a),0); //explain me this
				fwrite(&a,sizeof(a),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)	
			{
				printf("\nNo record found");
			}
			printf("\nModify another Record?(Y/N)\n");
			another=getch();
			if(another == 'y' || 'Y')
			{
				searchbooks();
			}
			else
			{
				mainmenu();
			}
		}	
	}
}
void issuebooks(void)
{
	int t,i;
	for(i=0;i<18;i++)
	{
		printf("*");
	}
	printf("Issue Section");
	for(i=0;i<18;i++)
	{
		printf("*");
	}	
	printf("\n\n1. Issue a Book");
	printf("\n2. View Issued Book");
	printf("\n3. Search Issued Book");
	printf("\n4. Remove Issued Book");
	printf("\nEnter a Choice:");
	switch(getch())
	{
		case '1':  
		{
			int c=0;
			char another='y';
			while(another=='y')
			{
				for(i=0;i<18;i++)
				{
					printf("*");
				}
				printf("Issue Book section");
				for(i=0;i<18;i++)
				{
					printf("*");
				}
				printf("\nEnter the Book Id : ");
				scanf("%d",&t);
				fp=fopen("book.dat","rb");
				fs=fopen("Issue.dat","ab+");
				if(checkid(t)==0) 
				{
					printf("\nThe book record is available");
					printf("\nThere are %d unissued books in library ",a.quantity);
					printf("\nThe name of book is %s",a.name);
					printf("\nEnter student name:");
					scanf("%s",a.stname);
		
					printf("The BOOK of ID %d is issued",a.id);
			
					fseek(fs,sizeof(a),SEEK_END);
					fwrite(&a,sizeof(a),1,fs);
					fclose(fs);
					c=1;
				}
				if(c==0)
				{
					printf("No record found");
				}
				printf("Issue any more(Y/N):");
				another=getch();
				fclose(fp);
			}
		break;
		}
		case '2':
		{
			int j=4;
			printf("\n");
			for(i=0;i<18;i++)
			{
				printf("*");
			}
			printf("Issued book list");
			for(i=0;i<18;i++)
			{
				printf("*");
			}
			printf("\nSTUDENT NAME    CATEGORY    ID    BOOK NAME  ");
			fs=fopen("Issue.dat","rb");
			while(fread(&a,sizeof(a),1,fs)==1)
			{
				printf("\n%s",a.stname);
				printf("\n%s",categories[s-1]);
				printf("\n%d",a.id);
				printf("\n%s",a.name);
				j++;
			}
			fclose(fs);
		}
		break;
		case '3':  
		{
			int p,c=0;
			char another='y';
			while(another=='y')
			{
				printf("Enter Book ID:");
				scanf("%d",&p);
				fs=fopen("Issue.dat","rb");
				while(fread(&a,sizeof(a),1,fs)==1)
				{
					if(a.id==p)
					{
						issuebooks();
						printf("Press any key.......");
						getch();
						c=1;
					}
				}
				fclose(fs);
				if(c==0)
				{
					printf("No Record Found");
				}
				printf("Try Another Search?(Y/N)");
				another=getch();
			}
		}
		break;
		case '4':  //remove issued books from list
		{	
			int b;
			FILE *fg;  //declaration of temporary file for delete
			char another='y';
			while(another=='y' || 'Y')
			{
				printf("Enter book id to remove:");
				scanf("%d",&b);
				fs=fopen("Issue.dat","rb+");
				while(fread(&a,sizeof(a),1,fs)==1)
				{
					if(a.id==b)
					{
						issuebooks();
						findbook='t';
					}
					if(findbook=='t')
					{	
						printf("Do You Want to Remove it?(Y/N)");
						if(getch()=='y' || 'Y')
						{
							fg=fopen("record.dat","wb+");
							rewind(fs);
							while(fread(&a,sizeof(a),1,fs)==1)
							{	
								if(a.id!=b)
								{
									fseek(fs,0,SEEK_CUR);
									fwrite(&a,sizeof(a),1,fg);
								}
							}
							fclose(fs);
						fclose(fg);
						}
						remove("Issue.dat");
						rename("record.dat","Issue.dat");
						printf("The issued book is removed from list");
					}
				}
				if(findbook!='t')
				{
					printf("No Record Found");
				}
			}
			printf("Delete any more?(Y/N)");
			another=getch();
		}
		default:
		printf("\aWrong Entry!!");
		getch();
		issuebooks();
		break;
	}
}

int getdata()
{
	int t,i;
	printf("\n");
	for(i=0;i<16;i++)
	{
		printf("*");
	}
	printf("Enter the Information Below");
	for(i=0;i<16;i++)
	{
		printf("*");
	}
	printf("*");
	printf("\nCategory [%s]\n",categories[s-1]);
	printf("\nEnter Book ID : ");
	scanf("%d",&t);

	if(checkid(t) == 0) //if book id exist
	{
		printf("\nThe book id Already Exists\n");
		printf("Press Any key to go to addbooks\n");
		getch();
  		addbooks();
	}
	else
	{
		a.id = t;
		printf("\nBook Name : ");
		scanf("%s",a.name);
		printf("\nAuthor Name : ");
		scanf("%s",a.author);
		printf("\nQuantity:");
		scanf("%d",&a.quantity);
		printf("\nPrice:");
		scanf("%f",&a.Price);
		printf("\nRack No:");
		scanf("%d",&a.rackno);
		return 1;
	}
}

int checkid(int t)
{
	rewind(fp); //for  taking cursor at first
	while(fread(&a,sizeof(a),1,fp)==1)
	if(a.id==t)
	{
		return 0; //0 is matcch found
	}
		return 1;
}
int getch (void)
{
    int ch;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
