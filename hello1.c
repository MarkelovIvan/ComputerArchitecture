// hello1.c
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include "hello1.h"

MODULE_AUTHOR("Markelov Ivan");
MODULE_DESCRIPTION("Hello1 Module");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(event_list_head);

void print_hello(void) {
    struct event_list *element = kmalloc(sizeof(struct event_list), GFP_KERNEL);

    if (!element) {
        pr_err("Memory allocation failed for event_list\n");
        return;
    }

    element->event_time = ktime_get();
    list_add_tail(&element->list, &event_list_head);

    pr_info("Hello, World!\n");
}
EXPORT_SYMBOL(print_hello);

static void cleanup_events(void) {
    struct event_list *md, *tmp;

    list_for_each_entry_safe(md, tmp, &event_list_head, list) {
        pr_info("Time: %lld\n", md->event_time);
        list_del(&md->list);
        kfree(md);
    }
}

static int __init hello1_init(void) {
    pr_info("Hello1 module loaded\n");
    return 0;
}

static void __exit hello1_exit(void) {
    cleanup_events();
    pr_info("Hello1 module unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
