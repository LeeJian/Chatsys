#include"clientm.h"

uList user[MAX_NUM_STR];
int i = 0;


int AddUserToList(int Connfd,char* Msg,int MsgLen)
{
	Msg[MsgLen-1]='\0';
	printf("User:%s Login!!!\n",Msg);	
	/*将用户加入用户列表*/
	if( i <= MAX_NUM_STR && user[i].ufd == 0)/*最大在线用户数*/
	{
		user[i].ufd = Connfd;
		
		user[i].num++;
		memcpy(user[i].name,Msg,sizeof(Msg));
		i++;
		
	}
	else
	{
		i = 0;
		if( i <= MAX_NUM_STR && user[i].ufd == 0)/*最大在线用户数*/
		{
			user[i].ufd = Connfd;
		
			user[i].num++;
			memcpy(user[i].name,Msg,sizeof(Msg));
			i++;
		
		}
	}
}
int Dcilent(tChatSysMsg *Msg)
{
	int j;
	for(j = 0 ; j < MAX_NUM_STR; j ++)
	{
		if(user[j].ufd == Msg->Connfd)
		{
			user[j].ufd = 0;
			break;
		}
	}
	return 0;
}
int SendMsgToAllUsers(tChatSysMsg *Msg)
{
	tChatSysMsg SMsg;
	int j = 0;
	int temp = 0;
	 /*发送用户姓名，但是无法将姓名转发，除非修改消息结构*/
	/*for(j ; j < i; j++)   
	{	
		if(user[j].ufd == Msg->Connfd)
		{
			temp = j;
		}
	}*/
	for(j ; j < MAX_NUM_STR; j++)
	{
	
		/*printf("j=%d\n",j);
		
		printf("name:%s\n",user[j].name);
		printf("ufd:%d\n",user[j].ufd);
		printf("connfd:%d\n",Msg->Connfd);
		printf("name:%s\n",user[temp].name);*/
		if(user[j].name != NULL&&(user[j].ufd - Msg->Connfd)!=0)
		{
			SMsg.Version = CHAT_SYS_VERSION;
			SMsg.MsgType	= MT_CHAT_MSG;
			SMsg.MsgLen	= strlen(Msg->Msg);			
			SMsg.Msg[SMsg.MsgLen-1]='\0';
			memcpy(SMsg.Msg,Msg->Msg,sizeof(Msg->Msg));
			/*memcpy(SMsg.name,user[temp].name,sizeof(user[temp].name));*/
			SMsg.Connfd = user[j].ufd;
/*printf("--------------\n");

printf("M:%s\n",SMsg.Msg);
printf("connfd:%d\n",SMsg.Connfd);
printf("L:%d\n",SMsg.MsgLen);
printf("--------------\n");*/
			CspSend(&SMsg);
		}
		
	}
}
