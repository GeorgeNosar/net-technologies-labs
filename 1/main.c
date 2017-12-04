#include <pcap.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <errno.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netinet/if_ether.h> 
#include <ctype.h>

void Callback(u_char *args, const struct pcap_pkthdr* pkthdr, const u_char* 
	packet) 
{ 
	int i=0; 
	static int count=0; 

	printf("Packet Number: %d\n", ++count);           
	printf("Packet Size: %d\n", pkthdr->len); 
	printf("Packet Data:\n");                              
	for(i=0;i<pkthdr->len;i++) { 
		if(isprint(packet[i]))           
			printf("%c ",packet[i]);      
		else 
			printf(" . "); 
		if((i%16==0 && i!=0) || i==pkthdr->len-1) 
			printf("\n"); 
	}
}

int main(int argc,char **argv) 
{ 
	int i;
	char *dev; 
	char errbuf[PCAP_ERRBUF_SIZE]; 
	pcap_t* descr; 
	const u_char *packet; 
	struct bpf_program fp;
	bpf_u_int32 maskp;        
	bpf_u_int32 netp;        

	if(argc != 2){
		printf("Enter filter as argument");
		return 1;
	} 

	dev = pcap_lookupdev(errbuf); 
	
	if(dev == NULL) {
		printf("No device");
		return 2;
	} 

	pcap_lookupnet(dev, &netp, &maskp, errbuf); 

	descr = pcap_open_live(dev, BUFSIZ, 1,-1, errbuf); 
	if(descr == NULL) {
		printf("Promiscuous mode error");
		return 3;
	} 

	if(pcap_compile(descr, &fp, argv[1], 0, netp) == -1) {
		printf("Filter compiling error\n");
		return 4;
	} 

	if(pcap_setfilter(descr, &fp) == -1) {
		printf("Setting filter error\n");
		return 5;
	} 

	pcap_loop(descr, -1, Callback, NULL); 

	return 0; 
}
