#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
    //Need to choose the best alloc size to reach max sum_allocated

    const size_t KB = 1014;
    const size_t MB = 1024 * KB;
    const size_t GB = 1024 * MB;
    const size_t TB = 1024 * GB;
    const size_t ALLOC_SIZE = 128 * TB;
    printf("%zu \n",ALLOC_SIZE);
    size_t allock_block = ALLOC_SIZE<<20;
    unsigned long long sum_allocated = 0;
    while(sum_allocated < ALLOC_SIZE){
        //Run on MacOS, so MAP_ANON instead of MAP_ANONIMUOS
        if(mmap(0, allock_block, PROT_WRITE | PROT_READ, MAP_PRIVATE|MAP_ANON, -1, 0) != MAP_FAILED){
            sum_allocated+=allock_block;
        } else {
            allock_block /= 1<<5;
        }

    }
    printf("allocated virt mem bytes: %llu \n", sum_allocated);


    return EXIT_SUCCESS;
}

