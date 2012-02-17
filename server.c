
#include<stdio.h> 			/* perror */
#include<stdlib.h>			/* exit	*/
#include<sys/types.h>		/* WNOHANG */
#include<sys/wait.h>		/* waitpid */
#include<string.h>			/* memset */
#include<pthread.h>

#include "common.h"
#include "chatsys.h"

#include"clientm.h"

int main() 
{
	
	tChatSysMsg Msg;
	
	Debug("Server Start...\n");
	/*server init*/
	if(CspInit(INIT_AS_SERVER)!= SUCCESS)
		Debug("CspInit failure!\n");
	while(true)
	{
		CspRecv(&Msg);
		Debug2("Msg.Connfd:%d\n",Msg.Connfd);
	 	Debug2("Msg.Version:%d\n",Msg.Version);
		Debug2("Msg.MsgType:%d\n",Msg.MsgType);
		Debug2("Msg.SerialNumber:%d\n",Msg.SerialNumber);
		Debug2("Msg.MsgLen:%d\n",Msg.MsgLen);
		Msg.Msg[Msg.MsgLen-1]='\0';
		Debug2("Msg.Msg:%s\n",Msg.Msg);	
	        /*login msg*/
		if(Msg.MsgType	== MT_LOGIN_MSG)
		{
			AddUserToList(Msg.Connfd,Msg.Msg,Msg.MsgLen);	
			continue;
		}
		/*chat msg*/
		else if(Msg.MsgType	== MT_CHAT_MSG)	
		{
		    printf("Msg.Msg:%s\n",Msg.Msg);
		    SendMsgToAllUsers(&Msg);
			continue;
			
		}
		else if(Msg.MsgType == MT_LOGOUT_MSG)
		{
			
			printf("client %d exit\n",Msg.Connfd);
			/*Dcilent(&Msg);*/
			continue;
		}
	}
	CspShut();
	
}

