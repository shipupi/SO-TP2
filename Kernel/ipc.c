#include <stdint.h>



int ipc_create (char * id, uint64_t size) {



	return 1;
}


uint32_t jenkins_one_at_a_time_hash(char *key, int len)
{
    uint32_t hash, i;
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}