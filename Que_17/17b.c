/*
===========================================================================================================================
Name : 17b.c
Author : Harshal Purohit
Description : Write a program to simulate online ticket reservation. Implement write lock
		Write a program to open a file, store a ticket number and exit. Write a separate program, to
		open the file, implement write lock, read the ticket number, increment the number and print
		the new ticket number then close the file.
Date: 22nd Aug, 2024.
===========================================================================================================================
*/


#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
	int ticketno;
	int fm = open("ticket.txt", O_WRONLY);
	printf("Enter the ticket number to  stored:\n");
	scanf("%d", &ticketno);
	write(fm, &ticketno, sizeof(ticketno));
	printf("Ticket number stored succesfully\n");
	close(fm);
	return 0;
}
