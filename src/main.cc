#ifndef _ENTANGLE_NO_MAIN

#include "src/entangle_client.h"

int main() {
        entangle::EntangleClient b = entangle::EntangleClient("localhost", 8000);
        return(0);
}

#endif
