// hello1.h
#ifndef HELLO1_H
#define HELLO1_H

struct event_list {
    struct list_head list;
    ktime_t event_time;
};

void print_hello(void);

#endif // HELLO1_H
