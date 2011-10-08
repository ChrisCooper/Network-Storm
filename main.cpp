//
//  main.c
//  NetworkStorm
//
//  Created by Chris Cooper on 11-09-21.
//  Copyright 2011 Chris Cooper. All rights reserved.
//

#include <stdio.h>
#include <pcap.h>

//For htonl()
#include <netinet/in.h>

void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

int main (int argc, const char * argv[]) {
    
    char errbuf[PCAP_ERRBUF_SIZE];
    
    char device[] = "en1";
    
    printf("Device: %s\n", device);
    
    //Filter expression
//    char filter_exp[] = "port 23";
    char filter_exp[] = "port 53";
    
    //Compiled filter expression
    struct bpf_program fp;
    
    //Netmask of sniffing device
    bpf_u_int32 mask;
    
    //IP of sniffing device
    bpf_u_int32 net;
    
    if (pcap_lookupnet(device, &net, &mask, errbuf) == -1) {
        fprintf(stderr, "Can't get netmask for device %s\n", device);
        net = 0;
        mask = 0;
    }
    
    //pcap_t *pcap_open_live(char *device,
    //int snaplen, - maximum number of bytes to be captured by pcap
    //int promisc, - promiscuous or not
    //int to_ms, - timeout length
    //char *ebuf)
    pcap_t *handle = pcap_open_live(device, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", device, errbuf);
        return(2);
    }
    if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return(2);
    }
    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return(2);
    }
    
    //Packed header
    struct pcap_pkthdr header;
    
    //Actual packet
    const u_char *packet;
    
    /* Grab a packet */
    packet = pcap_next(handle, &header);
    
    char *packet_point = (char*)&header;
    
    /* Print its length */
    for (unsigned int i = 0; i < sizeof(pcap_pkthdr); i++) {
        printf("%c ", *(packet_point + i) & 0xFF);
    }
    
    printf("\n");
    
    for (unsigned int i = 0; i < sizeof(pcap_pkthdr); i++) {
        printf("%d ", *(packet_point + i) & 0xFF);
    }
    
    printf("\nJacked a packet with length of [%u][%u]\n", ntohl(header.len), header.len);
    /* And close the session */
    pcap_close(handle);
    return(0);
}

void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    
}





//IP Header
/*struct nread_ip {
 u_int8_t        ip_vhl;          // header length, version    
#define IP_V(ip)    (((ip)->ip_vhl & 0xf0) >> 4)
#define IP_HL(ip)   ((ip)->ip_vhl & 0x0f)
u_int8_t        ip_tos;          // type of service           
u_int16_t       ip_len;          // total length              
u_int16_t       ip_id;           // identification            
u_int16_t       ip_off;          // fragment offset field     
#define IP_DF 0x4000                 // dont fragment flag        
#define IP_MF 0x2000                 // more fragments flag       
#define IP_OFFMASK 0x1fff            // mask for fragmenting bits 
u_int8_t        ip_ttl;          // time to live              
u_int8_t        ip_p;            // protocol                  
u_int16_t       ip_sum;          // checksum                  
struct  in_addr ip_src, ip_dst;  // source and dest address   
};*/


//TCP Header
/*
struct nread_tcp {
    u_short th_sport; /* source port            
    u_short th_dport; /* destination port       
    tcp_seq th_seq;   /* sequence number        
    tcp_seq th_ack;   /* acknowledgement number
#if BYTE_ORDER == LITTLE_ENDIAN
    u_int th_x2:4,    /* (unused)    
th_off:4;         /* data offset 
#endif
#if BYTE_ORDER == BIG_ENDIAN
    u_int th_off:4,   /* data offset 
th_x2:4;          /* (unused)    
#endif
    u_char th_flags;
#define TH_FIN 0x01
#define TH_SYN 0x02
#define TH_RST 0x04
#define TH_PUSH 0x08
#define TH_ACK 0x10
#define TH_URG 0x20
#define TH_ECE 0x40
#define TH_CWR 0x80
    u_short th_win; /* window 
    u_short th_sum; /* checksum 
    u_short th_urp; /* urgent pointer 
};*/
