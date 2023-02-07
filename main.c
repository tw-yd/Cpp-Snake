#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>

#define U 1
#define D 2
#define L 3
#define R 4                        //蛇的狀態 U：上 D:下 L:左 R:右
typedef struct snake               //蛇身的一個節點
{
	int x;                        //節點的x座標
	int y;                        //節點的y座標
	struct snake *next;           //蛇身的下一個節點
}snake;
int score=0,add=10;              //總得分和每吃一次食物的得分
int highscore=0;                 //最高分
int status,sleeptime=200;        //蛇前進狀態，每次執行的時間間隔
snake *head,*food;               //蛇頭指標，食物指標
snake *q;                        //遍歷蛇時用的指標
int endgamestatus=0;             //遊戲結束時的狀態
HANDLE hOut;                      //控制檯控制程式碼
void gotoxy(int x,int y);
int color(int c);
void printsnake();
void wlcome();
void createmap();
void scoreandtips();
void initsnake();
void createfood();
int biteself();
void cantcrosswall();
void speedup();
void speeddown();
void snakemove();
void keyboardcontrol();
void lostdraw();
void endgame();
void choose();
void file_out();
void file_in();
void explation();

main()
{
    system("mode con cols=100 lines=30");
    printsnake();
    wlcome();
    file_out();
    keyboardcontrol();
    endgame();
}

 void gotoxy(int x,int y)//設定遊標位置
{COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c); //定位遊標的位置
}

int color(int c)//設定顏色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
    return 0;
}
void printsnake()//列印字元蛇
{
 	gotoxy(2,5);
	color(3);
	printf("姓名：張小艾");

	gotoxy(2,6);
	color(3);
	printf("學號：1910101099");

	gotoxy(35,1);
 	color(6);
 	printf("/^\\/^\\");

 	gotoxy(34,2);
 	printf("|_| o|");

 	gotoxy(33,2);
 	color(2);
 	printf("_");

 	gotoxy(25,3);
 	color(12);
 	printf("\\/");

 	gotoxy(31,3);
 	color(2);
 	printf("/");

 	gotoxy(37,3);
 	color(6);
 	printf("\\_/");

 	gotoxy(41,3);
 	color(10);
 	printf(" \\");

 	gotoxy(26,4);
 	color(12);
 	printf("\\____");

 	gotoxy(32,4);
 	printf("_________");

 	gotoxy(31,4);
 	color(2);
 	printf("|");

 	gotoxy(43,4);
 	color(10);
 	printf("\\");

 	gotoxy(32,5);
 	color(2);
 	printf("\\_______");

 	gotoxy(44,5);
 	color(10);
 	printf("\\");

 	gotoxy(39,6);
 	printf("|    |              \\");

 	gotoxy(38,7);
 	printf("/    /                \\");

 	gotoxy(37,8);
 	printf("/    /               \\ \\");

 	gotoxy(35,9);
 	printf("/    /                \\ \\");

 	gotoxy(34,10);
 	printf(" /   /                  \\  \\");

 	gotoxy(33,11);
 	printf("/    /        _----_        \\  \\");

 	gotoxy(32,12);
 	printf("/    /         _-~   ~-_        |  |");

 	gotoxy(31,13);
 	printf("(     (     _-~    _--_    ~-_     _/ |");

 	gotoxy(32,14);
 	printf("\\    ~-____-~    _-~    ~-_    ~-_-~ /");

 	gotoxy(33,15);
 	printf("~-_         _-~        ~-_       _-~");

 	gotoxy(35,16);
 	printf("~--____-~                ~-___-~");
}

 void wlcome()//歡迎介面
 {int n;
 int i,j=1;
 gotoxy(43,18);
 color(11);
 printf("貪吃蛇大作戰");
 color(14);
 for(i=20;i<=26;i++)
    {
    	for(j=27;j<=74;j++)
    	{
    		gotoxy(j,i);
    		if(i==20||i==26)
    		{
    			printf("-");
			}
			else if(j==27||j==74)
			{
				printf("|");
			}
		}
	}
	color(12);
	gotoxy(35,22);
	printf("1.開始遊戲");
	gotoxy(55,22);
	printf("2.遊戲說明");
	gotoxy(35,24);
	printf("3.退出遊戲");
	gotoxy(29,27);
	color(3);
	printf("請選擇1 2 3\n");
	color(14);
	scanf("%d",&n);
	switch(n)
	{
	 case 1:
	 	system("cls");//清屏
	 createmap();
	 initsnake();
	 createfood();
	 keyboardcontrol();
	 break;
	 case 2:
	 	explation();
        break;
    break;
    case 3:
        exit(0);
    break;
    }
}
void createmap()//建立地圖
{
	int i,j;
	for(i=0;i<58;i+=2)
	{
		gotoxy(i,0);
		color(5);
	    printf("□");
	    gotoxy(i,26);
		printf("□");
	}
	for(i=0;i<26;i++)
	{
		gotoxy(0,i);
	    printf("□");
	    gotoxy(56,i);
		printf("□");
	}
	for(i=2;i<56;i+=2)
	{
		for(j=1;j<26;j++)
		{
			gotoxy(i,j);
		    color(3);
		    printf("■\n\n");
		}

	}
}
 void scoreandtips()//遊戲介面右側的得分和小提示
 {
 	file_out();
 	gotoxy(64,4);
 	color(11);
 	printf("*最高紀錄*: %d",highscore);
 	gotoxy(64,8);
 	color(14);
 	printf("得分: %d ",score);
 	color(13);
 	gotoxy(73,11);
 	printf("小提示");
	gotoxy(60,13);
 	color(6);
 	printf("+---------------------+");
 	gotoxy(60,25);
 	printf("+---------------------+");
 	color(3);
 	gotoxy(64,14);
 	printf("每個食物得分：%d分",add);
 	gotoxy(64,16);
 	printf("不能穿牆，不能咬到自己");
 	gotoxy(64,18);
 	printf("用↑↓←→分別控制蛇的移動");
 	gotoxy(64,20);
 	printf("F1為加速，F2為減速");
 	gotoxy(64,22);
 	printf("space: 暫停遊戲");
 	gotoxy(64,24);
 	printf("ESC:退出遊戲");
}
void file_out()//開啟檔案記錄最高分
{
	FILE *fp;
	fp=fopen("save.txt","a+");
	fscanf(fp,"%d",&highscore);
	fclose(fp);
}

void initsnake()
{
 	snake *tail;
 	int i;
 	tail=(snake*)malloc(sizeof(snake));
 	tail->x=24;
 	tail->y=5;
 	tail->next=NULL;
 	for(i=1;i<=4;i++)
 	{
 		head=(snake*)malloc(sizeof(snake));
 		head->next=tail;
 		head->x=24+2*i;
 		head->y=5;
 		tail=head;
	 }
	 while(tail!=NULL)
	 {gotoxy(tail->x,tail->y);
	  color(14);
	  printf("★");                   //蛇身由★組成
	  tail=tail->next;
	 }
}
void createfood()//隨機出現食物
{
   snake *food_1;
   srand((unsigned)time(NULL));
   food_1=(snake*)malloc(sizeof(snake));
   while((food_1->x%2!=0))
   {
   	 food_1->x=rand()%52+2;
	}
   food_1->y=rand()%24+1;
   q=head;
   while(q->next==NULL)
   {
   	  if(q->x==food_1->x&&q->y==food_1->y)
   	  {
   	  	free(food_1);
   	  	createfood();
	  }
	  q=q->next;
   }
   gotoxy(food_1->x,food_1->y);
   food=food_1;
   color(12);
   printf("@");
}

int biteself()
{
	snake *self;                //定義self為蛇身上除蛇頭以外的節點
	self=head->next;
	while(self!=NULL)
	{
		if(self->x==head->x&&self->y==head->y)
		{
			return 1;
		}
		self=self->next;
	}
	return 0;
}

void cantcrosswall()
{
	if(head->x==0||head->x==56||head->y==0||head->y==26)
	{
		endgamestatus=1;
		endgame();
	}
}

void speedup()//加速
{
	if(sleeptime>=50)
	{
		sleeptime=sleeptime-10;
		add=add+2;
	 }
}

void speeddown()//減速
{
	if(sleeptime<350)
	{
		sleeptime=sleeptime+30;
		add=add-2;
		if(sleeptime==350)
		{
			add=1;
		}
	 }
}

 void snakemove()//控制方向
{
	snake *nexthead;
	cantcrosswall();
	nexthead=(snake*)malloc(sizeof(snake));
	if(status==U)//上
	{
		nexthead->x=head->x;         //向上前進時，x不變，y-1
		nexthead->y=head->y-1;
		nexthead->next=head;
		head=nexthead;
		q=head;
		//如果下一個位置上有食物，下一個位置的座標和食物座標相同
		if(nexthead->x==food->x&&nexthead->y==food->y)
		{
			while(q!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("★");
				q=q->next;
			}
			score=score+add;
			speedup();
			createfood();
		}
	else
	{
		while(q->next->next!=NULL)//如果沒有遇見食物
		      {
		      	gotoxy(q->x,q->y);
				color(14);
				printf("★");
				q=q->next;
			  }
  //經過上面的迴圈 ，q指向蛇尾，蛇尾的下一步就是蛇走過去的位置
		      gotoxy(q->next->x,q->next->y);
			  color(3);
			  printf("■");//恢復走過的位置
			  free(q->next);
			  q->next=NULL;
		 }

	 }
  if(status==D)
  {
        nexthead->x=head->x;         //向下前進時，x不變，y+1
		nexthead->y=head->y+1;
		nexthead->next=head;
		head=nexthead;
		q=head;
		//如果下一個位置上有食物，下一個位置的座標和食物座標相同
		if(nexthead->x==food->x&&nexthead->y==food->y)
		{
			while(q!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("★");
				q=q->next;
			}
			score=score+add;
			speedup();
			createfood();
		}
	else
	{
		while(q->next->next!=NULL)//如果沒有遇見食物
		      {
		      	gotoxy(q->x,q->y);
				color(14);
				printf("★");
				q=q->next;
			  }
  //經過上面的迴圈 ，q指向蛇尾，蛇尾的下一步就是蛇走過去的位置
		      gotoxy(q->next->x,q->next->y);
			  color(3);
			  printf("■");//恢復走過的位置
			  free(q->next);
			  q->next=NULL;
		 }
	}
 if(status==L)//左
   {
   	    nexthead->x=head->x-2;         //向左前進時，x不變，y+1
		nexthead->y=head->y;
		nexthead->next=head;
		head=nexthead;
		q=head;
		//如果下一個位置上有食物，下一個位置的座標和食物座標相同
		if(nexthead->x==food->x&&nexthead->y==food->y)
		{
			while(q!=NULL)
			{
				gotoxy(q->x,q->y);     //食物變成蛇身上的一部分
				color(14);
				printf("★");
				q=q->next;
			}
			score=score+add;
			speedup();
			createfood();
		}
	else
	{
		while(q->next->next!=NULL)//如果沒有遇見食物
		      {
		      	gotoxy(q->x,q->y);
				color(14);
				printf("★");
				q=q->next;
			  }
  //經過上面的迴圈 ，q指向蛇尾，蛇尾的下一步就是蛇走過去的位置
		      gotoxy(q->next->x,q->next->y);
			  color(3);
			  printf("■");//恢復走過的位置
			  free(q->next);
			  q->next=NULL;
		 }
   }
  if(status==R)
  {
  	    nexthead->x=head->x+2;         //向上前進時，x不變，y-1
		nexthead->y=head->y;
		nexthead->next=head;
		head=nexthead;
		q=head;
		//如果下一個位置上有食物，下一個位置的座標和食物座標相同
		if(nexthead->x==food->x&&nexthead->y==food->y)
		{
			while(q!=NULL)
			{
				gotoxy(q->x,q->y);
				color(14);
				printf("★");
				q=q->next;
			}
			score=score+add;
			speedup();
			createfood();
		}
	else
	{
		while(q->next->next!=NULL)//如果沒有遇見食物
		      {
		      	gotoxy(q->x,q->y);
				color(14);
				printf("★");
				q=q->next;
			  }
  //經過上面的迴圈 ，q指向蛇尾，蛇尾的下一步就是蛇走過去的位置
		      gotoxy(q->next->x,q->next->y);
			  color(3);
			  printf("■");//恢復走過的位置
			  free(q->next);
			  q->next=NULL;
		 }
}
  if(biteself()==1)
  {
  	endgamestatus=2;
  	endgame();
  }
}
void keyboardcontrol()
{
	status=R;
	while(1)
	{
		scoreandtips();
 //GetAsyncKeyState函數用來判斷函數呼叫指定虛擬鍵的狀態
    if(GetAsyncKeyState(VK_UP)&&status!=D)
	  {
	  	status=U;
	   }
	   else if(GetAsyncKeyState(VK_DOWN)&&status!=U)
	  {
	  	status=D;
	   }
	   else if(GetAsyncKeyState(VK_LEFT)&&status!=R)
	  {
	  	status=L;
	   }
	   else if(GetAsyncKeyState(VK_RIGHT)&&status!=L)
	  {
	  	status=R;
	   }
	   if(GetAsyncKeyState(VK_SPACE))
	   {
	       while(1)
	        {
	//呼叫sleep函數，令程序停止，直到達到其中設定的引數時間
			   Sleep(300);
			   if(GetAsyncKeyState(VK_SPACE))
			   {
			   	  break;
				}
			}
	   }
	   else if(GetAsyncKeyState(VK_ESCAPE))
	   {
	   	    endgamestatus=3;
	   	    break;
	   }
	   else if(GetAsyncKeyState(VK_F1))
	   {
	   	    speedup();
	   }
	   else if(GetAsyncKeyState(VK_F2))
	   {
	   	    if(sleeptime<350)
	   	     {
	   	     	sleeptime=sleeptime+30;
	   	     	add=add-2;
	   	     	if(sleeptime==350)
	   	     	{
	   	     		add=1;
				}
	   	    }
	   }
	   Sleep(sleeptime);
	   snakemove();
	}
}

void lostdraw()
{
	system("cls");
	int i,j;
	gotoxy(17,5);
	color(11);
	printf("+------------------------");

	gotoxy(35,5);
	color(14);
	printf("o00o");

    gotoxy(39,5);
	color(11);
	printf("----------");

	gotoxy(48,5);
	color(14);
	printf("---");

	gotoxy(51,5);
	color(11);
	printf("----------");

	gotoxy(61,5);
	color(14);
	printf("o00o");

	gotoxy(65,5);
	color(11);
	printf("-----------------+");

	for(i=6;i<=19;i++)
	{
		gotoxy(17,i);
	    printf("|");
	    gotoxy(82,i);
	    printf("|");
		}
		gotoxy(17,20);
		printf("+----------------------------------");

		gotoxy(52,20);
		color(11);
		printf("-----------------------------+");
 }

  void endgame()
  {
  	system("cls");
  	if(endgamestatus==1)
  	{
  		lostdraw();
  		gotoxy(35,9);
  		color(12);
  		printf("對不起，您撞到牆了。遊戲結束！");
	  }
	  else if(endgamestatus==2)
	  {
	  	lostdraw();
	  	gotoxy(35,9);
	  	color(12);
	  	printf("對不起，您咬到自己了。遊戲結束！");
	   }
	  else if(endgamestatus==3)
	  {
	  	lostdraw();
	  	gotoxy(40,9);
	  	color(12);
	  	printf("您結束了遊戲。");
	   }
	  	gotoxy(43,12);
	  	color(13);
	  	printf("您的得分是 %d",score);
	  	if(score>=highscore)
		  {
		  	color(10);
		  	gotoxy(33,16);
		  	printf("創新紀錄啦！你真棒！！！");
			file_in();
		   }
	choose();
  }
  void file_in()//將最高分儲存到檔案中
  {
  	FILE *fp;
  	fp=fopen("save.txt","w+");//以讀寫的方式建立檔案
  	fprintf(fp,"%d",score);
  	fclose(fp);
  }
  void choose()
  {
  	int n;
  	gotoxy(25,23);
  	color(12);
  	printf("重玩一局-------1");
	gotoxy(52,23);
	printf("不玩了，退出-------2");
	gotoxy(46,25);
  	color(11);
  	printf("選擇：");
  	scanf("%d",&n);
  	switch(n)
  	{
  		case 1:
  			system("cls");
  			score=0;
  			sleeptime=200;
  			add=10;
  			printsnake();
  			wlcome();
  			break;
  		case 2:
  			exit(0);
  			break;
  		default:
  			gotoxy(35,27);
  			color(12);
  			printf("您輸入有誤，請重新輸入");
  			system("pause >nul");//按任意鍵
			endgame();
			choose();
			break;
	  }
   }
  void explation()
  {
  	int i,j=1;
  	system("cls");
  	color(13);
  	gotoxy(44,3);
  	printf("遊戲說明");
	 color(2);
	 for(i=6;i<=22;i++)
	 {
	 	for(j=20;j<=75;j++)
	 	{
	 		gotoxy(j,i);
	 		if(i==6||i==22)printf("=");
	 		else if(j==20||j==75)printf("||");
		 }
	  }
	  color(3);
	  gotoxy(30,8);
	  printf("1、不能穿牆，不能咬到自己");
	  color(3);
	  gotoxy(30,8);
	  printf("1、不能穿牆，不能咬到自己");
	  color(10);
	  gotoxy(30,11);
	  printf("2、用↑↓←→分別控制蛇的移動");
	  color(14);
	  gotoxy(30,14);
	  printf("3、F1為加速，F2為減速");
	  color(11);
	  gotoxy(30,17);
	  printf("4、按空格鍵暫停遊戲，再按空格鍵繼續");
	  color(4);
	  gotoxy(30,20);
	  printf("5、ESC：退出遊戲，space：暫停遊戲");
	  getch();//按任意鍵返回主介面
	  system("cls");
	  printsnake();
	  wlcome();
}
