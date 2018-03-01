
#Plans for program flow:

* Poll GPS for data once a second using `poll()` in `polling.c`, which automatically handles UART busses, and updates screen after each data packet returns
* refresh screen on button press, but not while data is being sent or received. (If it is, we just update page number and it will write automatically when the uart finishes)
* Perhaps make UART reads start a watchdog timer that will interrupt between UART reads if it took too long to find the packet we wanted
