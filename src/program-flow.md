
#Plans for program flow:

* Poll GPS for data once a second, which automatically handles UART busses, and update screen after each data packet returns
* refresh screen on button press, but not while data is being sent or received. (If it is, we just update page number and it will write automatically when the uart finishes)
