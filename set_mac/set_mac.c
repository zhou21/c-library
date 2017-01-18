#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/sockios.h>
#include <netinet/in.h>

#define ARPHRD_ETHER    1 
char up_ether[64] = "";
char down_ether[64] = "";

int macAddrSet(char * ether, char* mac)  
{  
    struct ifreq temp;  
    struct sockaddr* addr;  
  
    int fd = 0;  
    int ret = -1;  
      
    if((0 != getuid()) && (0 != geteuid()))  
        return -1;  
    if((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)  
    {  
        return -1;  
    }  
  
    strcpy(temp.ifr_name, ether);  
    addr = (struct sockaddr*)&temp.ifr_hwaddr;  
      
    addr->sa_family = ARPHRD_ETHER;  
    memcpy(addr->sa_data, (char *)mac, 6);  
      
    ret = ioctl(fd, SIOCSIFHWADDR, &temp);  
	perror("ioctl-mac");
    close(fd);  
    return ret;  
}

int update_ip_and_eth(char *ether, char * mac)
{
	int ok = macAddrSet(ether, mac);
	system(down_ether);	
	sleep(2);
	system(up_ether);
	return ok;	
}

int main(int agrc, char *agrv[])
{
	if (agrc <= 1){
		printf("<sorry you have not input new mac>\n");
		return -1;
	}
	char *ether = agrv[1];
	sprintf(up_ether, "ifconfig %s up",ether);
	sprintf(down_ether, "ifconfig %s down",ether);
	
	char mac[] = {2,12,41,28,178,61};
	int i = 0;
		mac[5]++;
		int ok = update_ip_and_eth(ether, mac);	
		printf("<It 's ok?>: %d\n", ok);
		mac[5]++;
		ok = update_ip_and_eth(ether, mac);	
		printf("<It 's ok?>: %d\n", ok);
		mac[5]++;
		ok = update_ip_and_eth(ether, mac);	
		printf("<It 's ok?>: %d\n", ok);
		mac[5]++;
		ok = update_ip_and_eth(ether, mac);	
		printf("<It 's ok?>: %d\n", ok);
}  
