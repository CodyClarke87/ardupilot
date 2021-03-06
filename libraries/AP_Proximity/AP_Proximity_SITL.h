#pragma once

#include "AP_Proximity.h"
#include "AP_Proximity_Backend.h"
#if CONFIG_HAL_BOARD == HAL_BOARD_SITL
#include <SITL/SITL.h>
#include <AC_Fence/AC_PolyFence_loader.h>

class AP_Proximity_SITL : public AP_Proximity_Backend
{

public:
    // constructor
    AP_Proximity_SITL(AP_Proximity &_frontend, AP_Proximity::Proximity_State &_state);

    // get distance in meters in a particular direction in degrees (0 is forward, clockwise)
    // returns true on successful read and places distance in distance
    bool get_horizontal_distance(float angle_deg, float &distance) const override;

    // update state
    void update(void) override;

private:
    SITL::SITL *sitl;
    Vector2l *fence;
    AP_Int8 *fence_count;
    uint32_t last_load_ms;
    AC_PolyFence_loader fence_loader;
    Location current_loc;
    
    void load_fence(void);
};
#endif // CONFIG_HAL_BOARD
