//
//  main.c
//  NetworkStorm
//
//  Created by Chris Cooper on 11-09-21.
//  Copyright 2011 Chris Cooper. All rights reserved.
//

#include <stdio.h>
#include <pcap.h>

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
    /* Print its length */
    printf("Jacked a packet with length of [%d]\n", header.len);
    /* And close the session */
    pcap_close(handle);
    return(0);
}

void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    
}
