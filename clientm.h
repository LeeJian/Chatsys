#ifndef _MACRO_H_
#define _MACRO_H_
#include<stdio.h> 			/* perror */
#include<stdlib.h>			/* exit	*/
#include<sys/types.h>		/* WNOHANG */
#include<sys/wait.h>		/* waitpid */
#include<string.h>			/* memset */
#include<pthread.h>

#include "common.h"
#include "chatsys.h"


typedef struct UserList
{
	int ufd;
	int num;
	char name[MAX_NUM_STR];
}uList;

int Dcilent(tChatSysMsg *Msg);
int AddUserToList(int Connfd,char* Msg,int MsgLen);
int SendMsgToAllUsers(tChatSysMsg *Msg);


#endif
