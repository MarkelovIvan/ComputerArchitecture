// hello2.c
#include <linux/module.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("Markelov Ivan");
MODULE_DESCRIPTION("Hello2 Module");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int num_of_greet = 1;
module_param(num_of_greet, uint, 0444);
MODULE_PARM_DESC(num_of_greet, "Number of times 'Hello, World!' string will be printed");

static int __init hello2_init(void) {
    int i;

    if (num_of_greet == 0 || (num_of_greet >= 5 && num_of_greet <= 10))
        pr_warn("Number is 0 or in range [5, 10]\n");

    if (num_of_greet > 10) {
        pr_err("Number is too big\n");
        return -EINVAL;
    }

    for (i = 0; i < num_of_greet; i++) {
        print_hello();
    }

    return 0;
}

static void __exit hello2_exit(void) {
    pr_info("Hello2 module unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
