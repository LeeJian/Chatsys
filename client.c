
#include<stdio.h> 			/* perror */
#include<stdlib.h>			/* exit	*/
#include<sys/types.h>		/* WNOHANG */
#include<sys/wait.h>		/* waitpid */
#include<string.h>			/* memset */
#include<pthread.h>

#include "common.h"
#include "chatsys.h"

/* œÓÊÕÏûÏ¢µÄÏß³Ì */
void * MsgProcessThread();

int main()
{
    char str[MAX_NUM_STR];
    char str1[MAX_NUM_STR]; /*保留姓名*/
	 char str2[MAX_NUM_STR];
	char str3[5] = "EXIT";
    int i = 0;
    pthread_t pid;
    tChatSysMsg Msg;
    /* login as client*/
    int i4ClientConnId = CspInit(INIT_AS_CLIENT);
    if(i4ClientConnId == FAILURE)
    {
		Debug("CspInit failure!\n"); 
		exit(0);
    }
    /* µÇÂœ */
	printf("Input your name>>");
	fgets(str,MAX_NUM_STR,stdin);
	Msg.Connfd = i4ClientConnId;
	Msg.Version = CHAT_SYS_VERSION;
	Msg.MsgType	= MT_LOGIN_MSG;
	memcpy(Msg.Msg,str,strlen(str));
	memcpy(str1,str,strlen(str));
	str1[sizeof(str)-1]='\0';
	/*memcpy(Msg.name,str,strlen(str));*/
	Msg.MsgLen	= strlen(Msg.Msg);
	CspSend(&Msg);
	/* ŽŽœšœÓÊÕÏûÏ¢µÄÏß³Ì */
	if(pthread_create(&pid, NULL,(void*)MsgProcessThread, NULL) != SUCCESS)
	{
		perror("pthread_create"); 
	}
	/* Ö÷³ÌÐò */
	while(1)
	{
			printf(">>");
			for(i=0;i<MAX_NUM_STR;i++)
				str[i]='\0';
			for(i=0;i<MAX_NUM_STR;i++)
				str2[i]='\0';
			fgets(str,MAX_NUM_STR,stdin);
			int m = strcmp(str,"EXIT\n");
			/*printf("m:%d\n",m);*/
			if(m == 0)
			{
				Msg.Connfd = i4ClientConnId;
				Msg.Version = CHAT_SYS_VERSION;
				Msg.MsgType	= MT_LOGOUT_MSG;
				memcpy(str2,str1,strlen(str1));	
				str2[sizeof(str2)-1] = ':';
				strcat(str2,str);
				/*str2[sizeof(str2)] = '\0';*/
				memcpy(Msg.Msg,str2,strlen(str2));
				Msg.MsgLen	= strlen(str2);			
				Msg.Msg[Msg.MsgLen-1]='\0';
				/*memcpy(Msg.name,str,strlen(str));*/
				CspSend(&Msg); 
				continue ;
			}
			Msg.Connfd = i4ClientConnId;
			Msg.Version = CHAT_SYS_VERSION;
			Msg.MsgType	= MT_CHAT_MSG;
			memcpy(str2,str1,strlen(str1));	
			str2[sizeof(str2)-1] = ':';
			strcat(str2,str);
			/*str2[sizeof(str2)] = '\0';*/
			memcpy(Msg.Msg,str2,strlen(str2));
			Msg.MsgLen	= strlen(str2);			
			Msg.Msg[Msg.MsgLen-1]='\0';
			/*memcpy(Msg.name,str,strlen(str));*/
			CspSend(&Msg); 
	}    
	return SUCCESS;

}
/* œÓÊÕÏûÏ¢µÄÏß³Ì */
void * MsgProcessThread()
{
	while(1)
	{
		
	       tChatSysMsg RspMsg;
		CspRecv(&RspMsg);
		RspMsg.Msg[RspMsg.MsgLen]='\0';
		/*printf("Recv from %s :%s\n",RspMsg.name,RspMsg.Msg); */
		printf("Recv:%s\n",RspMsg.Msg); 
		printf("---------------------\n");
		Debug2("RspMsg.Connfd:%d\n",RspMsg.Connfd);
		Debug2("RspMsg.Version:%d\n",RspMsg.Version);
	       Debug2("RspMsg.MsgType:%d\n",RspMsg.MsgType);
		Debug2("RspMsg.SerialNumber:%d\n",RspMsg.SerialNumber);
		Debug2("RspMsg.MsgLen:%d\n",RspMsg.MsgLen);
		/*RspMsg.Msg[RspMsg.MsgLen-1]='\0';
		Debug2("RspMsg.Msg:%s\n",RspMsg.Msg); 
		printf("Recv:%s",RspMsg.Msg);  */
	 }
}
