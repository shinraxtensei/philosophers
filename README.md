# philosophers

# threads_mutex(mandatory)

- pthread_create :

```c
- function starts a new thread in the calling
       process 
- On success, pthread_create() returns 0; on error, it returns an
       error number, and the contents of *thread are undefined.
```

- pthread_join

```c
 - The pthread_join() function waits for the thread specified by
       thread to terminate.  If that thread has already terminated, then
       pthread_join() returns immediately.  The thread specified by
       thread must be joinable.

```

- pthread_detach :

```c
 - Thepthread_detach() function marks the thread identified by
thread as detached.  When a detached thread terminates, its
       resources are automatically released back to the system without
       the need for another thread to join with the terminated thread.

       Attempting to detach an already detached thread results in
       unspecified behavior.
- On success, pthread_detach() returns 0; on error, it returns an
       error number.
```

- pthread_mutex_init :

```c
The pthread_mutex_init() function initialises the mutex referenced by mutex with attributes specified by attr. If attr is NULL, the default mutex attributes are used; the effect is the same as passing the address of a default mutex attributes object. Upon successful initialisation, the state of the mutex becomes initialised and unlocked.
```

- pthread_mutex_destroy:

```c
The pthread_mutex_destroy() function shall destroy the mutex object referenced by mutex; the mutex object becomes, in effect, uninitialized. An implementation may cause pthread_mutex_destroy() to set the object referenced by mutex to an invalid value. A destroyed mutex object can be reinitialized using pthread_mutex_init(); the results of otherwise referencing the object after it has been destroyed are undefined.
```

- pthread_mutex_lock:

```c
The mutex object referenced by mutex is locked by calling pthread_mutex_lock(). If the mutex is already locked, the calling thread blocks until the mutex becomes available. This operation returns with the mutex object referenced by mutex in the locked state with the calling thread as its owner.
```

- pthread_mutex_unlock :

```c
The mutex object referenced by mutex shall be locked by calling pthread_mutex_lock(). If the mutex is already locked, the calling thread shall block until the mutex becomes available. This operation shall return with the mutex object referenced by mutex in the locked state with the calling thread as its owner.
```

---

# approach

> in order for you to pass this project u have to prevent all deadlock ocurrences from happening ,
> 
> 
> so what is dead-lock ? when two procceces / threads try to acces  the same memory (critical section) the operating system calls the dispatcher that stops that from happening by interupting one the the threads until the first one finishes its execution (context switch ...) , for not getting into details  , sometimes somthing strange happends called dead lock and its basacaly a state when all threads are stopped by the opperating system and no can acces the critical section 
> 
> the goal of the dining philosophers problem is to demoonstrate that problem .
> 
> there is alot of algoriths to stop the dead-lock from happening like (***Prevention , Avoidance, Detection and Recovery, Ignorance***) “check this [https://bigpel66.oopy.io/library/42/inner-circle/9](https://bigpel66.oopy.io/library/42/inner-circle/9)”
> 
> so lets get to how to prevent the philosophers from dying 
> 
> all u have to do is to make it that the philosophers will not eat at the same time cause if that happends  the dead lock will occure (every philosopher will take his fork and the other philosopher’s fork that is beside him at the end  ... so some will not be able to eat cause they dont have two fork so they will die ) so one way to sort this problem is to make sure that one philosopher will eat and the next one will not , the next next will eat and so on  to clarify more u can make it that all the odd philosophers will eat and after that. the even ones will eat. and so on  in this way everyone will eat .
> 

---

# steps for u to step in the steps of this project

- parsing
    - check if the args are all digits. and all the other errors that must be handled
    - take all the args and convert them to numbers
    - init your struct with the args and everything you’ll need
    - 
- threads creation
    - create  the threads with pthread_create
    - make a routine (function) for each action (sleeping, eating, thinking)
    - with every action you should lock with pthread_mutex_lock the mutex of the thread and another thread’s mutex that is beside him (on his right or left it depends on how u see life)
    - dont forget to unlock the mutex after every rountine’s end with pthread_mutex_unlock
    
- threads joining
    - join all the threads with pthread_join
        - and last this is to free everything and ur done
    - and also u shoudl free everything leaks are not healthy for ur health
- the tracker
    - did u think that’s the end  helll no ,
    - u need a monitor to check if any philos died. it should be a thread too

# bonus

## semaphores functions

- sem_open
    
    ```c
    sem_open() creates a new POSIX semaphore or opens an existing
           semaphore.  The semaphore is identified byname.
    ```
    

- sem_close
    
    ```c
    sem_close() closes the named semaphore referred to bysem,
           allowing any resources that the system has allocated to the
           calling process for this semaphore to be freed.
    
    ```
    
- sem_post

```c
sem_post() increments (unlocks) the semaphore pointed to bysem.
       If the semaphore's value consequently becomes greater than zero
```

- sem_wait

```
sem_wait() decrements (locks) the semaphore pointed to bysem.
       If the semaphore's value is greater than zero
```

- sem_unlink

```
sem_unlink() removes the named semaphore referred to byname.
       The semaphore name is removed immediately.  The semaphore is
       destroyed once all other processes that have the semaphore open
       close it.

```

> for the bonus part we will work with semaphores , and each philo will be a proccess wich means the we dont have to deal with mutual exclusion and we should not be affraid of two philos accessing the same memory ,  its pretty straightforward  every fork is a semaphore value. (if there is 5 forks then the semaphore will be iniinitialized with that same value). and the first philo to take the fork will be the first to eat . after this we can do somthing about the prioritie of who should eat and should not based on how many times each philo has ate.
>
