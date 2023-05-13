#ifndef __DISTANCE_H__
#define __DISTANCE_H__

#include <math.h>
#include "stdint.h"
#define M_PI 3.14159265358979323846


float to_rad(float deg);
float to_deg(float ang);
float compute_distance_haversine(float lat1, float lon1, float lat2, float lon2);
float compute_distance_vincenty(float lat1, float lon1, float lat2, float lon2);

#endif