#ifndef DESPIKE_INC_H
#define DESPIKE_INC_H

#ifdef __cplusplus
extern "C" {
#endif

int DES_despike9( int num , float *vec , float *wks );
int DES_despike25( int num , float *vec , float *wks );
float qmed_float( int n , float * ar );

#ifdef __cplusplus
}
#endif

#endif