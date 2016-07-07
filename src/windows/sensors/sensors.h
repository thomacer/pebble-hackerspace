#pragma once

typedef enum {
    temperature,
    door_locked,
    barometer,
    radiation,
    humidity,
    beverage_supply,
    power_consumption,
    wind,
    network_connections,
    account_balance,
    total_member_count,
    people_now_present,
} t_sensors;

typedef struct {
    t_sensors type;
    int32_t value;
    char* location;
    char* name;
    char* description;
} Sensor;
