
#ifndef STATE_H
#define STATE_H
enum comm_state_t {
    WAIT,
    START,
    CMD_DLE,
    DATA,
    DATA_DLE,
    END_BYTE,
    ERROR
};


#endif /*STATE_H*/
