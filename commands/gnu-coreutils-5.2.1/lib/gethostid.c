/* Implements gethostid() for Minix. Do it via tcp, because opening 
 * the ip device fails if not root. Apparently hostid must always 
 * succeed, so if fetching the ip fails, we use id = 0 and hopefully 
 * we're not on a network. 
 */
#include <config.h>

#ifdef _MINIX
# include <sys/types.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <unistd.h>
# include <net/hton.h>
# include <net/gen/in.h>
# include <net/gen/netdb.h>
# include <net/netlib.h>
# include <net/gen/tcp.h>
# include <net/gen/tcp_io.h>

int gethostid() {
    int id, tcpfd, rv;
    nwio_tcpconf_t tcpconf;

    /* Do not query getenv("TCP_DEVICE"), because the id must be the same
     * on a host, even if running multiple tcp servers.
     */ 
    tcpfd = open(TCP_DEVICE, O_RDONLY);
    if (tcpfd >= 0) {
        rv = ioctl(tcpfd, NWIOGTCPCONF, &tcpconf);
        if (rv != -1) {
            id = ntohl(tcpconf.nwtc_locaddr);
        } else {
            id = 0;
        }
        close(tcpfd);
    } else {
        id = 0;
    }
    return id;
}

#endif /* _MINIX */
