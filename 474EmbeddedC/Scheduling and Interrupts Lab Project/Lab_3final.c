/**Lab_3final.c
 *@file Lab_3final.c
 *  @author Kevin Barreto
 *  @author Jesse Butler
 *  @date   24-Feb-2022
 *  @brief  Lab 3 - Interrupts and Schedulers
 *
 *  Utilizes three different scheduler types to control various external devices.\n
 *  Schedulers used: Round Robin, Synchronized Round Robin with ISR, and Data-Driven Scheduler.\n
 *  Devices used: LED, Speaker, 4-Digit 7-Segmented Display.\n
 *  To test any of the six required configurations, simply set the variable demo_number to the desired value.\n
 *
 */

#include <stdio.h>

const int demo_number = 6;
// Demo number (1-6)
// Sets scheduler_type and controls running tasks
//  1: T1, T2 with RR scheduler
//  2: T1, T2 with SRRI scheduler
//  3: T1, T2 with DDS scheduler
//  4: T1, T2, T3 with SRRI scheduler
//  5: T4 with DDS scheduler
//  6: T5 with DDS scheduler, allows T5 to start and stop
//     additional tasks.

// Global timing variables
unsigned int counter = 0;
unsigned int flagCounter = 0;
unsigned long current_time;
unsigned long last_time;


enum scheduler_type{RR,SRRI,DDS} scheduler;
enum task_state{READY = 2, RUNNING = 3, SLEEPING = 4, DEAD = 5};
enum sFlag_state{PENDING, DONE} sFlag;

#define LED_PIN         3       // Used to set DDR and Port for LED
#define LED_DELAY       250     // On-time for LED in ms
#define RR_period       1000    // RR total period in ms;
unsigned long start_t;          // Variables to keep track of time (no Timer/Counter >:( )
unsigned long stop_t;
unsigned long temp;
unsigned long RR_start_t;
unsigned long RR_stop_t = 0;

// Speaker output setup
#define SPEAKER     3     // Speaker bit number. Used to set DDR and Port
#define PRTIM4      4     // bit number. set to LOW to enable Timer/Counter4
#define COM4A0      6     // bit number. sets Compare Output Mode for channel A
#define WGM42       3     // bit number. sets Waverform Generation mode in TCCRnB
#define CS40        0     // bit number. sets prescaler/ clock source

#define D4  27303  //293 Hz
#define E4  24316  //329 Hz
#define C4  30651  //261 Hz
#define C3  61538  //130 Hz
#define G3  40816  //196 Hz
#define REST 0
#define REST_COUNT 4

const long int melody[] = { D4, E4, C4, C3, G3 };
unsigned int note_index = 0;


// 7-seg Pins and Segments
#define DIG_COUNT       4             // total 7-seg units
#define DIG_ORDER       3210          // display order, used for smile setting
#define SEG_COUNT       7             // segments on display units
#define INTEGERS        10            // digits in base-10. for clarity.
#define DDRB_PINS       0b00001111    // 7-seg display digits, 1 goes on 53, 4 goes on 50
#define DDRL_PINS       0b11111111    // pin 1 of the 7-seg goes on 49. pin 11 goes on 42
#define PORTL_CLEAR     0b00000000    // keeps display from flashing on startup
#define PORTB_CLEAR     0b00001111    // keeps display from flashing on startup

#define DIG1            0b00001110
#define DIG2            0b00001101
#define DIG3            0b00001011
#define DIG4            0b00000111

#define H0              0b11101011
#define H1              0b00101000
#define H2              0b01110011
#define H3              0b01111010
#define H4              0b10111000
#define H5              0b11011010
#define H6              0b11011011
#define H7              0b01101000
#define H8              0b11111011
#define H9              0b11111000

#define F1              293
#define F2              329
#define F3              261
#define F4              130
#define F5              196

#define S1              0b00000000
#define S2              0b10001010
#define S3              0b00100011
#define S4              0b00000000

const int display_pins[DIG_COUNT] = {DIG1,DIG2,DIG3,DIG4};
const byte digit_vals[INTEGERS] = {H0,H1,H2,H3,H4,H5,H6,H7,H8,H9};
const int freq_vals[] = {F1,F2,F3,F4,F5};
const byte smile_vals[DIG_COUNT] = {S1,S2,S3,S4};

enum seg {UPCOUNT,DOWNCOUNT,FREQ,SMILE} disp;
int seg_num;
int target_num;
int counter_ticks;

// typedef to make function pointer arrays easily
typedef void(*fptr)();

// Task Control Block
#define TASK_NAME_LIMIT 20
typedef struct TCB{
  fptr task;
  unsigned int ID_code;
  enum task_state state;
  char task_name[TASK_NAME_LIMIT];
  unsigned int run_count;
  unsigned int sleep_delay;
} TCB;

// Scheduler
#define SCHEDULE_SIZE 10
int current_index = 0;
int task_count;

//ISR ENABLE/Clock Setup
#define PRTIM0      5 // bit number in PRR0 to enable Timer/Counter 0
#define DDR5        5 // bit number in DDRG reg
#define PORT5_NUM   5 // bit number in PORTG reg
#define COM0B0      4 // bit number in TCCR0A Control reg. Compare Match Output Mode
#define WGM01       1 // bit number in TCCR0A. WGM mode
#define CS02        2 // bit number in TCCR0B. Clock Select and Prescale

#define OCIE0B      2 // bit number in TIMSK0 (Interrupt Mask Register). Enable Output Compare Match B Interrupt
                      // Additional info: Interrupt vector is TIMER0_COMPB_vect . use ISR(-vector-){} to define ISR function
#define I_BIT       7 // bit number in SREG (Status Register). Global Interrupt Enable. Set to enable
#define DELTA_T     2 // clock tick

// Function Prototypes
void task1();
void task2();
void task3();
void task4();
void task5();
void task_start(struct TCB *task);
void task_self_quit();
void set_digit(int num, byte arr[]);
void sleep_474(int ms);
void counterTimer();
void schedule_sync();
unsigned int bit_set(unsigned int reg, int bitnum);
unsigned int bit_clear(unsigned int reg, int bitnum);
unsigned int bit_toggle(unsigned int reg, int bitnum);
unsigned int bit_check(unsigned int reg, int bitnum);


#define MAX_TASK_COUNT 10
#define NULL_ID 9999
fptr tp1 = &task1;
fptr tp2 = &task2;
fptr tp3 = &task3;
fptr tp4 = &task4;
fptr tp5 = &task5;
fptr tpss = &schedule_sync;
fptr timerPointer = &counterTimer;

TCB tcb1 = { tp1, 1001, READY, "LED toggle", 0, 0};
TCB tcb2 = { tp2, 2001, READY, "Play Music", 0, 0};
TCB tcb3 = { tp3, 3001, READY, "7-Seg Display", 0, 0};
TCB tcb4 = { tp4, 4001, READY, "Music and Display", 0, 0};
TCB tcb5 = { tp5, 5001, READY, "LightsMusicAction", 0, 0};
TCB tcbTimer = { timerPointer, 2002, READY, "TimerCounter", 0,0};
TCB tcbNULL = { NULL, NULL_ID, DEAD, "NULL", 0, 0 };

TCB tcbList[MAX_TASK_COUNT] = {tcbNULL,tcbNULL,tcbNULL};
TCB tcbDead[MAX_TASK_COUNT] = {tcbNULL,tcbNULL,tcbNULL};
TCB tcbTemp[MAX_TASK_COUNT] = {tcbNULL,tcbNULL,tcbNULL};

fptr sched[SCHEDULE_SIZE];
enum task_state state_array[MAX_TASK_COUNT];
int task_delay[MAX_TASK_COUNT];

#define TCB2_SHORT_SLEEP 1000;
#define TCB2_LONG_SLEEP  4000;
#define SMILE_TIMER      3000;
unsigned int last_DDS_timer;
int active_task = 0;
int tcb2quitNext = 0;
int final_countdown = 0;




/**
*   @brief setup()
*
*   Sets initial conditions based on chosen demo number.
*   @param demo_number Selects scheduler.
*   @param scheduler Selects tasks, lists, arrays, and ports to use.
*
*
*/
void setup() {
    switch(demo_number){
        case 1:
            scheduler = RR;
            break;
        case 2:
            scheduler = SRRI;
            task_count = 2;
            break;
        case 3:
            scheduler = DDS;
            task_count = 2;
            last_DDS_timer = 0;
            tcbList[0] = tcb1;
            tcbList[1] = tcb2;
            tcbList[2] = tcbNULL;
            break;
        case 4:
            scheduler = SRRI;
            task_count = 3;
            disp = UPCOUNT;
            break;
        case 5:
            scheduler = DDS;
            disp = FREQ;
            task_count = 2;
            last_DDS_timer = 0;
            tcbList[0] = tcb2;
            tcbList[1] = tcb3;
            tcbList[2] = tcbNULL;
            break;
        case 6:
            scheduler = DDS;
            tcbList[0] = tcb1;
            tcbList[1] = tcb2;
            tcbList[2] = tcb3;
            last_DDS_timer = 0;
            task_count = 3;
            break;
        default:
            scheduler = RR;
            break;
    }

    // 7-Seg port for output
    if (scheduler != RR){
      DDRL  = DDRL_PINS;      // 7-Seg display segs
      PORTL = PORTL_CLEAR;    // 7-Seg display segs
      DDRB  = DDRB_PINS;      // 7-Seg display digits
      PORTB = PORTB_CLEAR;    // 7-Seg display digits
    }

    // LED port for output
    DDRE  = bit_set(DDRE,LED_PIN);
    PORTE = bit_clear(PORTH, LED_PIN);

    // Speaker port for output
    PRR1 = bit_clear(PRR1,PRTIM4);
    TCCR4A = 0;
    TCCR4B = 0;
    TCCR4A = bit_set(TCCR4A,COM4A0);
    TCCR4B = bit_set(TCCR4B,WGM42);
    TCCR4B = bit_set(TCCR4B,CS40);
    DDRH = bit_set(DDRH, SPEAKER);

    // Scheduler setups
    switch(scheduler){
        case RR:
            // hi c:
            break;
        case SRRI:
            // SETUP ISR
            PRR0 = bit_clear(PRR0,PRTIM0);        // Enable Timer/Counter 0
            TCCR0A = 0;                           // Initialize control registers
            TCCR0B = 0;
            TCCR0A = bit_set(TCCR0A,COM0B0);      // Set Output Compare Match mode to Toggle
            TCCR0A = bit_set(TCCR0A,WGM01);       // Set WGM mode to CTC
            TCCR0B = bit_set(TCCR0B,CS02);        // Set clock prescale to 256 (Lowest prescale 8bit timer and 2ms "tick")
            OCR0A = 125;
            OCR0B = 125;                          // Compare Match reg value (2ms or 500Hz)
            TIMSK0 = bit_set(TIMSK0,OCIE0B);      // Enable Output Compare Match B Interrupt

            SREG = bit_set(SREG,I_BIT);           // Enable Global Interrupts

            DDRG = bit_set(DDRG,DDR5);            // Pin 4 on Arduino board (OC0B).
            PORTG = bit_set(PORTG,PORT5_NUM);     // Set pin HIGH

            sFlag = PENDING;                      // Set synchronizer flag

            // Prepare schedule, states, and delays.
            for(int j =0; j<SCHEDULE_SIZE; j++){
              sched[j] = NULL;
              state_array[j] = NULL;
              task_delay[j] = 0;
            }
            if(demo_number == 2){
              sched[0] = tp1;
              sched[1] = tp2;
              sched[2] = tpss;
            }
            if(demo_number == 4){
              sched[0] = tp1;
              sched[1] = tp2;
              sched[2] = tp3;
              sched[3] = tpss;
            }
            for (int i = 0; i < task_count; i++){
              state_array[i] = READY;
              task_delay[i] = 0;
            }
            break;
        case DDS:
              for (int i = 0; i < task_count; i++){
                tcbList[i].state = READY;
                tcbList[i].sleep_delay = 0;
                tcbList[i].run_count = 0;
              }
            break;
    }
}

/**
*   @brief loop()
*
*   Main body of the program. Loops through tasks based on scheduler selection.
*   @param scheduler Selects tasks to run based on given demo number
*   @param RR Round Robin Scheduler - repeats task1 and task2
*   @param SRRI Synchronized Round Robin with ISR - synchronizes tasks every 2ms with an interrupt vector
*   @param DDS Data-Driven Scheduler - Uses list of task control block to schedule tasks
*   @see task1()
*   @see task2()
*   @see task3()
*   @see task4()
*   @see task5()
*   @see ISR()
*   @see counterTimer()
*
*/
void loop() {
  switch (scheduler){
    case RR:
        RR_start_t = millis();
        task1();
        task2();
        while ((RR_stop_t - RR_start_t) < LED_DELAY){
            RR_stop_t = (millis());
        }
        task1();
        while((RR_stop_t - RR_start_t) < RR_period){
            RR_stop_t = (millis());
        }
        break;
    case SRRI:
        if((state_array[current_index] == READY) ){
            sched[current_index]();
            current_index++;
        }
        else if((state_array[current_index] == SLEEPING)){
            current_index++;
        }
        else if(current_index == task_count){
            sched[current_index]();
        }
        break;
    case DDS:
        switch(demo_number){
            case 3:
                while(1){
                    for (int i = 0; i < task_count; i++){
                        active_task = i;
                        if (tcbList[i].ID_code != NULL_ID){
                            if (tcbList[i].state == READY){
                                tcbList[i].state = RUNNING;
                                tcbList[i].task();
                            }
                        }
                    }
                    counterTimer();
                }
                break;
            case 5:
                task4();
                break;
            case 6:
                task5();
                break;
        }
        break;
  }
}

/**
*   @brief task1()
*
*   Blinks an LED on for 250ms and off for 750ms of every second.\n
*   Behavior differs based on the selected scheduler.\n
*   RR - Only toggles the LED. Timing is handled externally.\n
*   SRRI - After toggling the LED, checks its state and sleeps for the correct amount of time.\n
*   DDS - After toggling, sets its state to sleeping, increments its run count, and sets its sleep delay to the correct value.\n
*   @see bit_check()
*   @see bit_toggle()
*
*
*/
void task1(){
  PORTE = bit_toggle(PORTE,LED_PIN);
  if(scheduler == SRRI){
        if (bit_check(PORTE,LED_PIN)){
          sleep_474(250);
        } else {
          sleep_474(750);
        }
  }
  else if (scheduler == DDS){
        tcbList[active_task].state = SLEEPING;
        tcbList[active_task].run_count++;
        if (bit_check(PORTE,LED_PIN)){
          tcbList[active_task].sleep_delay = (25);
        } else {
          tcbList[active_task].sleep_delay = (75);
        }
  }
}



/**
*   @brief task2()
*
*   Plays music from "Close Encounters" at specified intervals.\n
*   Behavior differs based on the selected scheduler.\n
*   RR - Cycles through the notes and then pauses for four note counts before starting over. Timing is handled externally.\n
*   SRRI - Cycles through the notes, sleeping for one second between notes and four seconds at the end of the tune.\n
*   DDS - Cycles through notes, sets its status to sleeping, sets its sleep delay to one second between notes and four seconds between tunes.
*   During task4 and task5, controls the condition of task3. During task5, halts under designated conditions.
*   @param note_index Current note to play in song
*   @param melody[] Contains the notes to play
*   @see bit_check()
*   @see bit_toggle()
*   @see task3()
*   @see task4()
*   @see task5()
*
*/
void task2(){
    if (tcb2quitNext){
      if ( tcbList[active_task].run_count == 2){
        final_countdown = 300;
        disp = DOWNCOUNT;
      }
      note_index = 0;
      tcb2quitNext = 0;
      task_self_quit();
      return;
    }
    if (note_index >= (sizeof(melody)/sizeof(melody[0]))){
        switch(scheduler){
          case RR:
            if (note_index == ((sizeof(melody)/sizeof(melody[0])) + REST_COUNT)){
              note_index = 0;
            }
            else {
              PORTH = bit_clear(PORTH,SPEAKER);
              OCR4A = REST;
              PORTH = bit_set(PORTH,SPEAKER);
              note_index++;
              return;
            }
            break;
          case SRRI:
            PORTH = bit_clear(PORTH,SPEAKER);
            OCR4A = REST;
            PORTH = bit_set(PORTH,SPEAKER);
            note_index = 0;
            sleep_474(4000);
            return;
            break;
          case DDS:
            tcbList[active_task].state = SLEEPING;
            tcbList[active_task].sleep_delay = 400;
            if (demo_number == 5){
              disp = DOWNCOUNT;
            }
            PORTH = bit_clear(PORTH,SPEAKER);
            OCR4A = REST;
            PORTH = bit_set(PORTH,SPEAKER);
            note_index = 0;
            if (demo_number == 6){
              disp = DOWNCOUNT;
              if ((tcbList[active_task].run_count >= 1)){
                  tcb2quitNext = 1;
              }
            }
            tcbList[active_task].run_count++;
            return;
            break;
        }
    }
    //TCNT4 = 0;
    PORTH = bit_clear(PORTH,SPEAKER);
    OCR4A = melody[note_index];
    PORTH = bit_set(PORTH,SPEAKER);
    note_index++;
    if(scheduler == SRRI){
        sleep_474(1000);
    }
    if(scheduler ==  DDS){
        disp = FREQ;
        tcbList[active_task].state = SLEEPING;
        tcbList[active_task].sleep_delay = 100;
    }
}

/**
*   @brief task3()
*
*   Controls a 4-digit 7-segmented display.
*   @param disp Condition display is in.\n UPCOUNT - used in SRRI scheduler to count 100ms increments.\n DOWNCOUNT - used in DDS scheduler to count down the sleep time of task2 as well as
*   the time between task2 halting and restarting.\n FREQ - used in DDS scheduler to display the frequency of the note currently being played by task 2.\n SMILE - used in DDS scheduler to display a
*   smile on the 7-segmented display for a brief period before halting.
*   @param seg_num Number that must be displayed on the 7-segmented display.
*   @see counterTimer()
*   @see set_digit()
*   @see task_start()
*   @see task_self_quit()
*   @see task2()
*   @see task4()
*   @see task5()
*
*/
void task3(){
    switch(disp){
        case UPCOUNT:
            counterTimer();
            counter_ticks = counter/10;
            seg_num = counter_ticks;
            set_digit(seg_num,digit_vals);
            break;
        case DOWNCOUNT:
            if (final_countdown){
              seg_num = final_countdown/10;
              final_countdown--;
              if ((final_countdown == 0) && (tcbDead[1].run_count == 2)){
                task_start(&(tcbDead[1]));
                final_countdown = 400;
                return;
              } else if (final_countdown == 0){
                disp = SMILE;
                final_countdown = 200;
                return;
              }
            }
            else {
              seg_num = tcbList[active_task-1].sleep_delay/10;
            }
            set_digit(seg_num,digit_vals);
            break;
        case FREQ:
            seg_num = freq_vals[note_index];
            set_digit(seg_num,digit_vals);
            break;
        case SMILE:
            seg_num = DIG_ORDER;
            set_digit(seg_num, smile_vals);
            final_countdown--;
            if (final_countdown <= 0){
              task_self_quit();
            }
            break;
    }
}

/**
*   @brief setDigit()
*
*   Sets the digits of the 7-segment display to those
*   that coincide with the given array.
*   @param num Value that must be represented on the display
*   @param arr[] Array containing the values from which to pull segment settings
*   @see task3()
*   @see task4()
*   @see task5()
*
*
*/
void set_digit(int num, const byte arr[]){
  int target_num;
  for (int i = 0; i < DIG_COUNT; i++){
    target_num = num%INTEGERS;
    num /= INTEGERS;
    //delayMicroseconds(DISPLAY_DELAY);
    PORTB = display_pins[i];
    PORTL = arr[target_num];
  }
}

/**
*   @brief task4()
*
*   Runs task2 and task3 according to their task state and increments the counter for task 3.
*   @see counterTimer()
*   @see task2()
*   @see task3()
*
*
*/
void task4(){
    while(1){
        for (int i = 0; i < task_count; i++){
            active_task = i;
            if (tcbList[i].ID_code != NULL_ID){
                if (tcbList[i].state == READY){
                    tcbList[i].state = RUNNING;
                    tcbList[i].task();
                }
            }
        }
        counterTimer();
    }
}

/**
*   @brief task5()
*
*   Controls task control blocks 1, 2, and 3 based on their task states.\n
*   Task 1 - Runs continuously, blinking on for 250ms and off for 750ms of every second.\n
*   Task 2 - Plays melody twice before halting, then once more after restarted by task 3.\n
*   Task 3 - Displays melody of current note being played by task 2 while it is active.
*   While task 2 is paused, displays the remaining time in 100ms increments until it restarts.
*   After task 2 is permanently halted, briefly displays a smile on the display before halting.\n
*   @see counterTimer()
*   @see task1()
*   @see task2()
*   @see task3()
*   @see task_start()
*   @see task_self_quit()
*
*
*/
void task5(){
    while(1){
        for (int i = 0; i < task_count; i++){
            active_task = i;
            if (tcbList[i].ID_code != NULL_ID){
                if (tcbList[i].state == READY){
                    tcbList[i].state = RUNNING;
                    tcbList[i].task();
                }
            }
        }
        counterTimer();
    }
}

/**
*   @brief ISR()
*
*   Sets synchronizer flag sFlag to trigger synchronizer
*   @see schedule_sync()
*   @see sleep_474()
*
*/
ISR(TIMER0_COMPB_vect){
  // Called at each clock "tick"
  sFlag = DONE;
}

/**
*   @brief schedule_sync()
*
*   Synchronizes tasks in the SRRI scheduler when ISR triggers sFlag to DONE.\n
*   Updates task sleep timers and status on synchronize ticks.\n
*   @see ISR()
*   @see sleep_474()
*
*/
void schedule_sync(){
  if(sFlag == PENDING){
    return;
  }
  if (sFlag == DONE){
    // update sleep time of all tasks
    // wake up any tasks that have a sleep time of 0
    flagCounter++;
    counter = flagCounter / 5;
    for(int i = 0;i<task_count;i++){
      if(state_array[i] == SLEEPING){
        task_delay[i] = task_delay[i] - DELTA_T;    // decrement sleep delay value by 2ms for all SLEEPING tasks
        if(task_delay[i] < DELTA_T){                // Update status to READY after delay value reaches zero
            state_array[i] = READY;
        }
      }
    }
    current_index = 0;
    sFlag = PENDING;
    return;
  }
}

/**
*   @brief sleep_474()
*
*   Controls a 4-digit 7-segmented display
*   @param ms Time in milliseconds that the current task must sleep
*   @see task1()
*   @see task2()
*   @see task3()
*   @see ISR()
*   @see schedule_sync()
*
*
*/
void sleep_474(int ms){
    if(ms > 0){
      task_delay[current_index] = ms - DELTA_T;
      state_array[current_index] = SLEEPING;
    }
}

/**
*   @brief task_self_quit()
*
*   Allows a task control block to halt itself.
*   @see task_start()
*   @see task5()
*
*
*/
void task_self_quit(){
    for (int i = 0; i < task_count; i++){
      if (tcbList[i].state == RUNNING){
        tcbTemp[0] = tcbList[i];
        tcbTemp[1] = tcbDead[i];
        tcbTemp[0].state = DEAD;
        tcbDead[i] = tcbTemp[0];
        tcbList[i] = tcbTemp[1];
        return;
      }
    }
}

/**
*   @brief task_start()
*
*   Revives the selected task control block.\n
*   Must be called by a task other than itself
*   @param task Function pointer to desired task control block to revive
*   @see task_self_quit()
*   @see task5()
*
*
*/
void task_start(struct TCB *task){
    for (int i = 0; i < task_count; i++){
      if (tcbDead[i].ID_code == (*task).ID_code){
        tcbTemp[0] = tcbDead[i];
        tcbTemp[1] = tcbList[i];
        tcbTemp[0].state = READY;
        tcbTemp[0].run_count++;
        tcbTemp[0].sleep_delay = 0;
        tcbList[i] = tcbTemp[0];
        tcbDead[i] = tcbTemp[1];
        return;
      }
    }
}

/**
*   @brief counterTimer()
*
*   Increments a global counter every 100ms.\n
*   @param scheduler When scheduler is set to DDS, all task control block sleep and status variables are updated.
*
*/
void counterTimer(){
  current_time = millis();

  if ((current_time - last_time) >= 10){
      last_time = current_time;
      counter++;
      Serial.println(counter);
      if (scheduler == DDS){
      for (int i = 0; i < task_count; i++){
        if (tcbList[i].sleep_delay != 0){
          tcbList[i].sleep_delay--;
        }
        if (tcbList[i].sleep_delay == 0 && tcbList[i].state != DEAD){
          tcbList[i].state = READY;
        }
      }
      }
  }
}


/**
*   @brief bit_set()
*
*   Sets a particular bit
*   @param reg Desired register from which to set the chosen bit
*   @param bitnum Desired bit to set the status of
*   @return Returns the value of the register with the newly set bit
*
*
*/
unsigned int bit_set(unsigned int reg,int bitnum){
  reg = reg | (1<<bitnum);
  return reg;
}

/**
*   @brief bit_clear()
*
*   Clears a particular bit
*   @param reg Desired register from which to clear the chosen bit
*   @param bitnum Desired bit to set the status of
*   @return Returns the value of the register with the newly cleared bit
*
*/
unsigned int bit_clear(unsigned int reg, int bitnum){
  return reg = reg & ~(1<<bitnum);
}

/**
*   @brief bit_toggle()
*
*   Toggles a particular bit
*   @param reg Desired register from which to toggle the chosen bit
*   @param bitnum Desired bit to toggle the status of
*   @return Returns the value of the register with the newly toggled bit
*
*
*/
unsigned int bit_toggle(unsigned int reg, int bitnum){
  return reg = reg ^ (1<<bitnum);
}

/**
*   @brief bit_check()
*
*   Checks whether a particular bit is set
*   @param reg Desired register from which to check the chosen bit
*   @param bitnum Desired bit to check the status of
*   @param checked_bit Current value of selected bit.
*   @return Returns checked_bit, an integer representative of the status of the selected bit in the selected register.
*
*/
unsigned int bit_check(unsigned int reg, int bitnum){
  int checked_bit = (reg>>bitnum) & 1;
  return checked_bit;
}
