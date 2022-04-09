#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct my_time
{
  int minutes;
  int seconds;
} my_time_t;

/* jump over the hh in mm:ss */
char * next_field(char * str)
{
  while (*str && *str++ != ':');
  return str;
}

/* validate the given time (note: quite if negative minutes or seconds) */
void validate_time(my_time_t *time)
{
  if (time->seconds < 0 || time->minutes < 0) {
    fprintf(stderr, "Error: invalid input (negative time).");
    exit(1);
  } // exit if the time is negative
  else if (time->seconds > 60) {
    time->minutes += time->seconds / 60;
    time->seconds %= 60;
  } // fix time
}

/* parse commande line argument. In that case the argument should be mm:ss */
my_time_t parse_cmdln_option(char *opt)
{
  my_time_t requested_time = { .minutes = 0, .seconds = 0 };
  requested_time.minutes = atoi(opt);
  opt = next_field(opt);
  requested_time.seconds = atoi(opt);
  validate_time(&requested_time);
  return requested_time;
}

/* display the current state of the timer */
void display_menu(my_time_t time)
{
  system("clear");
  printf("+-------+\n");
  printf("| %d%d:%d%d |\n", time.minutes / 10, time.minutes % 10,
	 time.seconds / 10, time.seconds % 10);
  printf("+-------+\n");
}

/* increment the given timer */
void inc_timer(my_time_t *time)
{
  if (time->seconds < 59)
    time->seconds++;
  else {
    time->seconds = 0;
    time->minutes++;
  }
}

/* compare 2 given timer */
static inline int finish(my_time_t to_wait, my_time_t passed)
{ return (to_wait.minutes == passed.minutes && to_wait.seconds == passed.seconds); }

int main(int argc, char *argv[])
{
  my_time_t passed_time = { .minutes = 0, .seconds = 0 };
  my_time_t waiting_delay = { .minutes = 99, .seconds = 59 }; // max time amount by default
  struct timespec one_second = {1,0};

  if (argc == 2) // parse input if recquired
    waiting_delay = parse_cmdln_option(argv[1]);

  if (argc < 3) {
    while (!finish(waiting_delay, passed_time)) {
      display_menu(passed_time);
      nanosleep(&one_second, NULL);
      inc_timer(&passed_time);
    }
  } else {
    fprintf(stderr, "Error: invalid input.");
  }
  system("clear");
  printf("end!\n");
  return 0;
}
