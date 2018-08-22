//************************************************************************//
//			HEADER FILES USED IN PROJECT          		  //
//************************************************************************//

#include<iostream.h>
#include<fstream.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<process.h>
#include<time.h>

//************************************************************************//
//			CLASS USED IN PROJECT				  //
//************************************************************************//

class player
{       int age,gameid,score,pscore,hscore;
	char name[20], title[4];
	char gender;
  public:           	//PUBLIC SECTION STARTS HERE
	player()    //CONSTRUCTOR
	{	age=0;
		gameid=0;
		score=0;pscore=0;
		strcpy(name,"ANONYMOUS");
		strcpy(title," ");
		gender=' ';
	}
	int getgid()
	{	return gameid;
	}
	int getscore()
	{	return score;
	}
	void reset()
	{	score=0;
	}
	void change(int ps)
	{	if(ps>score)
			score=ps;
		pscore=ps;
	}
	int gameplay();
	void result(int);
	int create_player();
	void show_player();
	void show_all();
	void modify_player();
};//CLASS ENDS HERE

//************************************************************************//
//			GLOBAL DECLARATION OF fstream and class OBJECTS   //
//************************************************************************//

player profile;
fstream file, tempfile;

//************************************************************************//
//			FUNCTIONS USED IN PROJECT		          //
//************************************************************************//

//************************************************************************//
//			CLASS FUNCTIONS				          //
//************************************************************************//

//************************************************************************//
//			FUNCTION FOR GAMEPLAY				  //
//************************************************************************//

int player::gameplay()
{       pscore=0;
	int randsv[100];
	char ans;
	char ques[100][300],sol[100];
	ifstream qfile("pques.txt");
	for(int i=0;i<100;i++)
	{	qfile.getline(ques[i],300,'$');
	}
	ifstream afile("pans.txt");
	for(i=0;i<100;i++)
	{	afile>>sol[i];
	}
	time_t r;
	unsigned int seedvalue=(unsigned)time(&r);
	srand(seedvalue);
	for(i=0;i<100;i++)
	{       getch();
		clrscr();
		randsv[i]=rand()%99;
		if(i>0)
		{	for(int j=0;j<i;j++)
				if(randsv[i]==randsv[j])
					randsv[i]=rand()%99;
		}
		cout<<"\nHere is your question no. "<<i+1;
		cout<<"\n\n"<<ques[randsv[i]]<<endl;
		cout<<"\nANS> ";
		cin>>ans;
		if(islower(ans))
			ans=toupper(ans);
		if(ans==sol[randsv[i]])
		{	cout<<"\nCorrect answer ! ";
			pscore++;
			cout<<"\nYour Score is "<<pscore;
			if(score<pscore)
				score=pscore;
		}
		else
		{	cout<<"\nWrong answer ! ";
			getch();
			if(score<pscore)
				score=pscore;
			result(i);
			return(pscore);
		}
	}
	result(i);
	afile.close();
	qfile.close();
	return(pscore);
}

//************************************************************************//
//			FUNCTION TO SHOW RESULT				  //
//************************************************************************//

void player::result(int i)
{       clrscr();
	show_player();
	cout<<"\nRecent Played Game Score : "<<pscore;
	cout<<"\nNo. of Correct Answers given : "<<i;
}

//************************************************************************//
//			FUNCTION TO CREATE GAME PROFILE			  //
//************************************************************************//

int gamerid()
{	int gid[100];
	time_t r;
	unsigned int seedvalue=(unsigned)time(&r);
	srand(seedvalue);
	for(int i=0;i<100;i++)
	{	gid[i]=rand()%99;
		if(i>0)
		{	for(int j=0;j<i;j++)
			{	if(gid[i]==gid[j])
					gid[i]=rand()%99;
				else
				     return gid[i];
			}
		}
	}
	return 0;
}

int player::create_player()
{       int flag=0;
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\t\t\tTO CREATE A NEW GAME PROFILE\t";
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\nEnter Player Name : ";
	gets(name);
	cout<<"\nEnter Age (Age>=14) : ";
	cin>>age;
	if(age<14)
	{       flag=1;
		cout<<"\nYou are Underage for the game!!";
		cout<<"\nCould not create player profile!";
		return flag;
	}
	cout<<"\nEnter Gender (M/F/T) : ";
	cin>>gender;
	gender=toupper(gender);
	cout<<"\n\nPLAYER PROFILE CREATED SUCCESSFULLY...";
	gameid=gamerid();
	cout<<"\nYour GAMEID will be : "<<gameid;
	score=0;pscore=0;
	return flag;
}

//************************************************************************//
//			FUNCTION TO SHOW GAME PROFILE    		  //
//************************************************************************//

void player::show_player()
{	cout<<"\nGame ID : "<<gameid;
	cout<<"\nPlayer Name : "<<name;
	cout<<"\nAge : "<<age;
	cout<<"\nGender : "<<gender;
	cout<<"\nHigh Score : "<<score;
}

//************************************************************************//
//			FUNCTION TO SHOW ALL GAME PROFILES		  //
//************************************************************************//

void player::show_all()
{	cout<<gameid<<"  \t"<<name<<"\t\t "<<age<<"\t   "<<gender<<"\t  \t"<<score<<"\t\t  "<<pscore<<endl;
	cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-";
}

//************************************************************************//
//			FUNCTION TO SHOW HIGHEST SCORER			  //
//************************************************************************//

void disp_high()
{       int hscore=0;
	int hscor[100],hgameid,i=0;
	file.open("player.dat",ios::in);
	while(!(file.read((char*)&profile,sizeof(profile))))
	{       cout<<"AAAAAAAAAAAAAAAAAAA";
		hscor[i]=profile.getscore();
		if(hscor[i]>hscore)
		{       cout<<"BBBBBBBBBBBBBBBBBB";
			hscore=hscor[i];
			hgameid=profile.getgid();
		}
		i++;
	}
	while(!(file.read((char*)&profile,sizeof(profile))))
	{       cout<<"CCCCCCCCCCCCCCCCCC";
		if(hgameid==profile.getgid())
		{       cout<<"DDDDDDDDDDDDDDDDDD";
			profile.show_player();
			break;
		}
	}
	cout<<"EEEEEEEEEEEEEE";
}

//************************************************************************//
//			FUNCTION TO MODIFY A PROFILE IN FILE		  //
//************************************************************************//

void player::modify_player()
{       int ag,pts;
	char gen=' ',nm[20]=" ";
	cout<<"\n\nEnter New Details of Player\n";
	cout<<"\nModify Player Name (Enter '.' to retain old one) : ";
	gets(nm);
	cout<<"\nModify Gender of Player (Press '.' to retain old one) : ";
	cin>>gen;
	gen=toupper(gen);
	cout<<"\nModify Age (Age>=14)(Press -1 to retain old one) : ";
	cin>>ag;
	if(strcmp(nm,".")!=0)
		strcpy(name,nm);
	if(gen!='.')
	{	gender=gen;
	}
	if(ag!=-1)
		age=ag;
}

//************************************************************************//
//				GLOBAL FUNCTIONS			  //
//************************************************************************//

void intro();
void select(int);
void game_intro();
void game();
void write_player();
void display_player();
void display_all();
void display_high();
void reset_score();
void reset_game();
void modify_profile();
void delete_player();
void finish();

//************************************************************************//
//                  	    FUNCTION FOR GAMEPLAY			  //
//************************************************************************//

void game()
{	int id,pscore,pos,found=1;
	file.open("player.dat",ios::in|ios::out|ios::binary,ios::nocreate);
	if(!file)
	{	cout<<"\nERROR!!! No Profile Found in File";
		cout<<"\n\nRESOLVE :- ";
		cout<<"\nGo to Main Menu to Create a Profile";
		return;
	}
	cout<<"\n\nEnter Game ID : ";
	cin>>id;
	cout<<"\n\nPLAYER DETAILS\n";
	while(file.read((char*)&profile,sizeof(profile)) && found==1)
	{	if(id==profile.getgid())
		{       found=0;
			profile.show_player();
			pscore=profile.gameplay();
			profile.change(pscore);
			pos=-1*sizeof(profile);
			file.seekp(pos,ios::cur);
			file.write((char*)&profile,sizeof(profile));
		}
	}
	file.close();
	if(found==1)
		cout<<"\nProfile Not Found in File...";
}
//************************************************************************//
//                      FUNCTION TO WRITE GAME PROFILE			  //
//************************************************************************//

void write_player()
{	file.open("player.dat",ios::out|ios::app);
	int flag=profile.create_player();
	if(flag!=1)
		file.write((char*)&profile,sizeof(profile));
	file.close();
}

//************************************************************************//
//			FUNCTION TO DISPLAY GAME PROFILE	          //
//************************************************************************//

void display_player()
{       int id,found=1;
	file.open("player.dat",ios::in|ios::binary|ios::nocreate);
	if(!file)
	{	cout<<"\nERROR!!! No Profile Found in File";
		cout<<"\n\nRESOLVE :- ";
		cout<<"\nGo to Main Menu to Create a Profile";
		return;
	}
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\t\t\tTO DISPLAY DETAILS OF A GAME PROFILE";
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\n\nEnter Game ID : ";
	cin>>id;
	cout<<"\n\nPLAYER DETAILS\n";
	while(file.read((char*)&profile,sizeof(profile)) && found==1)
	{	if(profile.getgid()==id)
		{	found=0;
			profile.show_player();
		}
	}
	file.close();
	if(found==1)
		cout<<"\n\nProfile Not Found in File !!!";
}

//************************************************************************//
//		FUNCTION TO DISPLAY ALL GAME PROFILES   		  //
//************************************************************************//

void display_all()
{	file.open("player.dat",ios::in|ios::binary|ios::nocreate);
	if(!file)
	{	cout<<"\nERROR!!! No Profile Found in File";
		cout<<"\n\nRESOLVE :- ";
		cout<<"\nGo to Main Menu to Create a Profile";
		return;
	}
	cout<<"\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=";
	cout<<"\t\t\tGAME PLAYER LIST";
	cout<<"\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=";
	cout<<"\n\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-";
	cout<<"GameID \tName\t \tAge\tGender\t   High Score\t    \tLast Score";
	cout<<"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n";
	while (file.read((char*)&profile,sizeof(profile)))
	{	profile.show_all();
	}
	file.close();
}

//************************************************************************//
//		FUNCTION TO DISPLAY HIGHEST SCORE                         //
//************************************************************************//

void display_high()
{	file.open("player.dat",ios::in|ios::out|ios::binary);
	if(!file)
	{	cout<<"\nERROR!!! No Profile Found in File";
		cout<<"\n\nRESOLVE :- ";
		cout<<"\nGo to Main Menu to Create a Profile";
		return;
	}
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\t\t\tTO DISPLAY DETAILS OF HIGHEST SCORER";
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	disp_high();
}

//************************************************************************//
//		FUNCTION TO RESET SCORE OF A PROFILE			  //
//************************************************************************//

void reset_score()
{	char ch;
	int id,pos,found=1;
	file.open("player.dat",ios::in|ios::out|ios::nocreate);
	if(!file)
	{	cout<<"\nERROR!!! No Profile Found in File";
		cout<<"\n\nRESOLVE :- ";
		cout<<"\nGo to Main Menu to Create a Profile";
		return;
	}
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\t\t\tTO RESET SCORE OF PLAYER";
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\n\nEnter GameID of the Player whose Score is to be Reset : ";
	cin>>id;
	while(file.read((char*)&profile,sizeof(profile)) && found==1)
	{	if(profile.getgid()==id)
		{       found=0;
			profile.show_player();
			cout<<"\n\nAre you sure, you want to reset the score ? (y/n) : ";
			cin>>ch;
			if(ch=='y'||ch=='Y')
			{	profile.reset();
			}
			pos=-1*sizeof(profile);
			file.seekp(pos,ios::cur);
			file.write((char*)&profile,sizeof(profile));
		}
	}
	file.close();
	if(ch=='n'&&found==0)
		cout<<"\nReset Aborted Successfully";
	if(found==1)
		cout<<"\nProfile Not Found in File !!!";
	if(ch=='y'&&found==0)
		cout<<"\n\nScore Reset Successfully...";
}

//************************************************************************//
//			FUNCTION TO RESET GAME				  //
//************************************************************************//

void reset_game()
{       char ch;
	file.open("player.dat",ios::in|ios::out|ios::nocreate);
	if(!file)
	{	cout<<"\nERROR!!! No Profile Found in File";
		cout<<"\n\nRESOLVE :- ";
		cout<<"\nGo to Main Menu to Create a Profile";
		return;
	}
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\t\t\tTO RESET GAME";
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\n\nAre you sure, you want to rest the game completely ? (y/n) : ";
	cin>>ch;
	if(ch=='y'||ch=='Y')
	{	remove("player.dat");
		cout<<"\nGAME RESET SUCCESSFULLY...";
	}
	else
	{	cout<<"\nRESET ABORTED SUCCESSFULLY...";
		file.write((char*)&profile,sizeof(profile));
	}
}

//************************************************************************//
//		FUNCTION TO MODIFY A PROFILE IN FILE		          //
//************************************************************************//

void modify_profile()
{	int id,pos,found=1;
	file.open("player.dat",ios::in|ios::out|ios::nocreate);
	if(!file)
	{	cout<<"\nERROR!!! No Profile Found in File";
		cout<<"\n\nRESOLVE :- ";
		cout<<"\nGo to Main Menu to Create a Profile";
		return;
	}
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\t\t\tTO MODIFY DETAILS OF A PLAYER";
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\n\nEnter the GameID of Player whose details is to be modified : ";
	cin>>id;
	while(file.read((char*)&profile,sizeof(profile)) && found==1)
	{
		if(profile.getgid()==id)
		{       found=0;
			profile.show_player();
			profile.modify_player();
			pos=-1*sizeof(profile);
			file.seekp(pos,ios::cur);
			file.write((char*)&profile,sizeof(profile));
			cout<<"\n\nProfile Updated Successfully...";
		}
	}
	file.close();
	if(found==1)
		cout<<"\nProfile Not Found in File !!!";
}

//************************************************************************//
//		FUNCTION TO DELETE A PROFILE FROM FILE	       	          //
//************************************************************************//

void delete_player()
{       int id,found=1;
	char confirm='n';
	file.open("player.dat",ios::in|ios::binary|ios::app|ios::nocreate);
	tempfile.open("temp.dat",ios::out|ios::binary|ios::app);
	if(!file)
	{	cout<<"\nERROR!!! No Profile Found in File";
		cout<<"\n\nRESOLVE :- ";
		cout<<"\nGo to Main Menu to Create a Profile";
		return;
	}
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\n\tTO DELETE A PLAYER PROFILE";
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\n\nEnter GameID of the Player whose Record is to be Deleted : ";
	cin>>id;
	while(file.read((char*)&profile,sizeof(profile)))
	{	if(profile.getgid()==id)
		{       found=0;
			profile.show_player();
			cout<<"\n\nAre you sure, you want to Delete this Profile? (y/n) : ";
			profile.reset();
			cin>>confirm;
			if(confirm=='n')
				tempfile.write((char*)&profile,sizeof(profile));
		}
		else
			tempfile.write((char*)&profile,sizeof(profile));
	}
	file.close();
	tempfile.close();
	if(confirm=='n'&&found==0)
		cout<<"\nDeletion Aborted Successfully";
	if(found==1)
		cout<<"\nRecord Not Found in File !!!";
	if(confirm=='y'&&found==0)
		cout<<"\nRecord Deleted Successfully...";
	remove("player.dat");
	rename("temp.dat","player.dat");
}

//************************************************************************//
//			INTRODUCTORY FUNCTION			          //
//************************************************************************//

void intro()
{	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"*\t\t\t\tQUIZ\t\t\t\t\t       *";
	cout<<"*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
	cout<<">>\t\t\t\t\t\t\t\t\t      >>>>\t\tMADE BY : ABHINAV DUBEY and KUNAL KUMAR\t\t\t      >>";
	cout<<">>\t\t\t\t\t\t\t\t\t      >>>>\t\tCLASS   : 12 SCIENCE (NON-MEDICAL) \t\t\t      >>";
	cout<<">>\t\t\t\t\t\t\t\t\t      >>>>\t\tSCHOOL  : DEEPANSHU PUBLIC SCHOOL \t\t\t      >>";
	cout<<">>\t\t\t\t\t\t\t\t\t      >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
	getch();
}//INTRODUCTORY FUNCTION ENDS HERE

//************************************************************************//
//			GAME INTRODUCTORY FUNCTION			  //
//************************************************************************//

void game_intro()
{	clrscr();
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\t\t\t\tGAME INTRODUCTION";
	cout<<"\n*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=";
	cout<<"\n\nThis Game consists of 100 questions. Each correct answer will give you 1 point ";
	cout<<" and any incorrect answer will lead to sudden elimination.";
	cout<<"\nEvery question will have 4 options. Correct option must be choose by only A,B,C or D";
	cout<<" (Uppercase can be ignored)";
	cout<<"\n\nPress any button to go to Main Menu.";
	getch();
}//GAME INTRODUCTORY FUNCTION ENDS HERE

//************************************************************************//
//			FUNCTION TO SELECT OPTIONS			  //
//************************************************************************//

void select(int opt)
{	clrscr();
	switch(opt)
	{	case 1 : game();
			 getch();
			 break;
		case 2 : game_intro();
			 getch();
			 break;
		case 3 : write_player();
			 getch();
			 break;
		case 4 : display_player();
			 getch();
			 break;
		case 5 : display_all();
			 getch();
			 break;
		case 6 : display_high();
			 getch();
			 break;
		case 7 : reset_score();
			 getch();
			 break;
		case 8 : reset_game();
			 getch();
			 break;
		case 9 : modify_profile();
			 getch();
			 break;
		case 10 : delete_player();
			 getch();
			 break;
		case 11 : finish();
			  getch();
			  exit(0);

		default : cout<<"\n\tInvalid Option !!!";
			  cout<<"\n\tEXITING....";
			  finish();
			  getch();
			  exit(1);
	}
}//SELECTION FUNCTION ENDS HERE

//************************************************************************//
//				FINISHING FUNCTION			  //
//************************************************************************//

void finish()
{       clrscr();
	cout<<"\n\n\t\tTHANKS FOR PLAYING\n";
	cout<<"\n\n\t\tCREDITS - ABHINAV DUBEY and KUNAL KUMAR";
	cout<<"\n\t\tCLASS   - 12 SCIENCE (NON-MEDICAL)";
	cout<<"\n\t\tSCHOOL  - DEEPANSHU PUBLIC SCHOOL";
}

//************************************************************************//
//			  	MAIN FUNCTION			          //
//************************************************************************//

void main()
{	clrscr();
	intro();
	game_intro();
	int opt;
	do{	clrscr();
		cout<<"\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-";
		cout<<"*\t\t\t\tMAIN MENU\t\t\t\t       *";
		cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-";
		cout<<"\n\n\n\t1>>   PLAY GAME";
		cout<<"\n\t2>>   HELP";
		cout<<"\n\t3>>   CREATE PLAYER PROFILE";
		cout<<"\n\t4>>   SHOW PlAYER PROFILE";
		cout<<"\n\t5>>   SHOW SCORECARD";
		cout<<"\n\t6>>   SHOW HIGHEST SCORE";
		cout<<"\n\t7>>   RESET SCORE";
		cout<<"\n\t8>>   RESET GAME";
		cout<<"\n\t9>>   MODIFY PLAYER PROFILE";
		cout<<"\n\t10>>  DELETE PlAYER PROFILE";
		cout<<"\n\t11>>  EXIT";
		cout<<"\n\n\tSelect Option (1 to 11)";
		cout<<"\n\n\tEnter Your Choice : ";
		cin>>opt;
		select(opt);
	}while(opt!=11);
	finish();
	getch();
}//MAIN FUNCTION ENDS HERE

//*************************************************************************//
//			PROJECT ENDS HERE				   //
//*************************************************************************//

