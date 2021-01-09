#include <czmq.h>

int main() {
    zsock_t *push = zsock_new_push("inproc://example");

    return 0;
}