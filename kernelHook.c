#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/icmp.h>
#include <linux/netdevice.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>

static struct nf_hook_ops pre_hook;
static struct nf_hook_ops post_hook;

static unsigned int watch_in(void *priv,
                             struct sk_buff *skb,
                             const struct nf_hook_state *state) {
    printk("watch_in!\n");
    return NF_ACCEPT;
}

static unsigned int watch_out(void *priv,
                              struct sk_buff *skb,
                              const struct nf_hook_state *state) {
    printk("watch_out!\n");
    return NF_ACCEPT;
}

int init_module(void) {
    pre_hook.hook = watch_in;
    pre_hook.pf = PF_INET;
    pre_hook.hooknum = NF_INET_PRE_ROUTING;
    pre_hook.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &pre_hook);


    post_hook.hook = watch_out;
    post_hook.pf = PF_INET;
    post_hook.hooknum = NF_INET_POST_ROUTING;
    post_hook.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &post_hook);
    printk(KERN_INFO "init_module\n");
    return 0;
}

void cleanup_module(void) {
    nf_unregister_net_hook(&init_net, &pre_hook);
    nf_unregister_net_hook(&init_net, &post_hook);
    printk(KERN_INFO "cleanup_module\n");
}