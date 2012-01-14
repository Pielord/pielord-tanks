/*

*/

#include <inttypes.h>

//Default string len.
#define TANK_STR_LEN 256

//Used for 'packet_id'.
enum __attribute__((packed)) tank_packet_type {
    TANK_MAP_INFO,
    TANK_MAP_UPDATE,
    TANK_ACTION,
};
//Could add ERROR packet so it's possible to send some error messages
//back before closing connection. At the moment connection is just
//dropped if any error is encountered.

//Used for 'action_id'.
enum __attribute__((packed)) tank_packet_type {
    TANK_MOVE_UP,
    TANK_MOVE_DOWN,
    TANK_MOVE_LEFT,
    TANK_MOVE_RIGHT
};

//MAP_INFO packet. Sent by server when client joins the server.
struct __attribute__((packed)) tank_packet_map_info {
    enum tank_packet_type packet_id;
    
    uint16_t map_size_x;
    uint16_t map_size_x;
    //Not used.
    //uint8_t map_name[TANK_STR_LEN];
};

//MAP_UPDATE packet. Sent by server periodically.
struct __attribute__((packed)) tank_packet_map_update {
    enum tank_packet_type packet_id;
        
    uint32_t size;
    uint8_t data[];
};

//ACTION packet. Sent by client when player makes action.
struct __attribute__((packed)) lobby_packet_info {
    enum tank_packet_type packet_id;
    enum tank_action_type action_id;
    //Extra params?
};
