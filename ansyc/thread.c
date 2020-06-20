#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>


static void *
my_thread_a (void * arg)
{
    char *  s[2];
    int     i;

    // misuse the 'void *' parameter for passing an integer...
    // s[0] =  *((char *) (arg) + 1   );
    s[0]=  *((char **) (arg + 0)); //hrere there is a double pointer because array of char
    printf ("%lx thread-a start s = %s\n", pthread_self(), s[0]);
    
    /* Guarantees that thread resources are deallocated upon return */
    if (pthread_detach (pthread_self ()) != 0)
    {
        perror ("pthread_detach(a)");
    }

    // // do the work
    // for (i = 0; i < 5; i++)
    // {
    //     usleep (s);
    //     printf ("%lx thread-a loop  i=%d\n", pthread_self(), i);
    // }
    
    printf ("%lx thread-a exit\n", pthread_self());
    return (NULL);
}


static void *
my_thread_b (void * arg)
{
    int     s;
    int     i;
    s = (int) arg;
    
    printf ("%lx THREAD-B START s=%d\n", pthread_self(), s);
    
    if (pthread_detach (pthread_self ()) != 0)
    {
        perror ("pthread_detach(b)");
    }
    
    for (i = 8; i > 0; i--)
    {
        usleep (s);
        printf ("%lx THREAD-B LOOP  i=%d\n", pthread_self(), i);
    }
    
    printf ("%lx THREAD-B EXIT\n", pthread_self());
    return (NULL);
}



int main (void)
{
    pthread_t   thread_a;
    pthread_t   thread_b;
    int count;
    count =  1500;

    char * ptr[2];
    ptr[0]= "thierry";
    ptr[1] = "aime"; 
   
    printf("%s \n", ptr[0]);
    printf("%s \n", ptr[1]);
    printf ("%lx main     start\n", pthread_self());
    /* creating the threads */
    // misuse the 'void *' parameter for passing an integer...
    if (pthread_create (&thread_a, NULL, my_thread_a, (void *) ptr) != 0)
    {
        perror ("pthread_create(a)");
    }

    printf(" \n \n thread id is %d \n \n ", thread_a);
    pthread_join(thread_a, NULL); 
    // if (pthread_create (&thread_b, NULL, my_thread_b, (void *) 300) != 0)
    // {
    //     perror ("pthread_create(b)");
    // }
    // printf ("%lx main     waiting...\n", pthread_self());
    // sleep (5);
    // printf ("%lx main     exit\n", pthread_self());
    return (0);
}
