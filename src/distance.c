#include "../inc/distance.h"

const float EARTH_R = 6378137;
const float EARTH_f = 1.0 / 298.257223563;  //EARTH_FLATTENING

float to_deg(float ang) {
    int deg = ang / 100;
    float min = ang - deg * 100;
    return (deg + min / 60);
}


float to_rad(float deg) {
    return to_deg(deg) * M_PI / 180.0;
}


/*      Destination Using Haversine      */
// 1 -----> Destination , 2 -----> Current
float compute_distance_haversine(float lat1, float lon1, float lat2, float lon2) {

    float diff_lat = to_rad(lat1) - to_rad(lat2);
    float diff_lon = to_rad(lon1) - to_rad(lon2);
    float a = sin(diff_lat / 2) * sin(diff_lat / 2) + cos(to_rad(lat1)) * cos(to_rad(lat2)) * sin(diff_lon / 2) * sin(diff_lon / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return EARTH_R * c;
}

/*      Destination Using Vincenty      */
// 1 -----> Destination , 2 -----> Current
float compute_distance_vincenty(float lat1, float lon1, float lat2, float lon2) {

    float b = 6356752.314245;
    float L = to_rad(lon2 - lon1);
    float U1 = atan((1 - EARTH_f) * tan(to_rad(lat1)));
    float U2 = atan((1 - EARTH_f) * tan(to_rad(lat2)));
    float sinU1 = sin(U1), cosU1 = cos(U1);
    float sinU2 = sin(U2), cosU2 = cos(U2);
    float lambda = L, lambdaP, iterLimit = 100;
    float cosSqAlpha, sigma, cos2SigmaM, uSq, A, B, deltaSigma;

    do {
        float sinLambda = sin(lambda), cosLambda = cos(lambda);
        float sinSigma = sqrt((cosU2 * sinLambda) * (cosU2 * sinLambda) + (cosU1 * sinU2 - sinU1 * cosU2 * cosLambda) * (cosU1 * sinU2 - sinU1 * cosU2 * cosLambda));

        if (sinSigma == 0) return 0;
        else {
            float cosSigma = sinU1 * sinU2 + cosU1 * cosU2 * cosLambda;
            float sinAlpha = cosU1 * cosU2 * sinLambda / sinSigma;
            sigma = atan2(sinSigma, cosSigma);
            cosSqAlpha = 1 - sinAlpha * sinAlpha;
            cos2SigmaM = cosSigma - 2 * sinU1 * sinU2 / cosSqAlpha;

            if (isnan(cos2SigmaM))cos2SigmaM = 0;
            else {
                float C = EARTH_f / 16 * cosSqAlpha * (4 + EARTH_f * (4 - 3 * cosSqAlpha));
                lambdaP = lambda;
                lambda = L + (1 - C) * EARTH_f * sinAlpha * (sigma + C * sinSigma * (cos2SigmaM + C * cosSigma * (-1 + 2 * cos2SigmaM * cos2SigmaM)));
            }
        }
    } while (fabs(lambda - lambdaP) > 1e-12 && --iterLimit > 0);

    uSq = cosSqAlpha * (EARTH_R * EARTH_R - b * b) / (b * b);
    A = 1 + uSq / 16384 * (4096 + uSq * (-768 + uSq * (320 - 175 * uSq)));
    B = uSq / 1024 * (256 + uSq * (-128 + uSq * (74 - 47 * uSq)));
    deltaSigma = B * sin(sigma) * (cos2SigmaM + B / 4 * (cos(sigma) * (-1 + 2 * cos2SigmaM * cos2SigmaM) - B / 6 * cos2SigmaM * (-3 + 4 * sin(sigma) * sin(sigma)) * (-3 + 4 * cos2SigmaM * cos2SigmaM)));

    return b * A * (sigma - deltaSigma);
}