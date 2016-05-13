//
//  Constants.h
//  FlappyBird
//
//  Created by Fumiya Amano on 2016/05/12.
//
//

#ifndef Constants_h
#define Constants_h

static const float GRAVITY_ACCEL        = -1000.0f;
static const float JUMP_SPEED           = 300.0f;
static const float OBSTACLE_MIN_Y       = 200.0f;
static const float OBSTACLE_MAX_Y       = 400.0f;
static const float OBSTACLE_TIME_SPAN   = 1.35f;
static const float OBSTACLE_LIMIT       = 5;
static const float OBSTACLE_INIT_X      = 300.0f;
static const float SCROLL_SPEED_X       = 120.0f;

static float Lerp(float fStart, float fEnd, float fPercent)
{
    return fStart + ((fEnd - fStart) * fPercent);
}

#endif /* Constants_h */
