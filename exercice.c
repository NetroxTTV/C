#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float tableau(float* table) {
    for (int i = 0; i < 10; i++) {
        table[i] = 5;
        printf("%f\n", table[i]);

    }
}

int main() 
{
    /*{
        float* f1 = 5;
        float f2;

        float* pf = 0;

        pf = &f1;

        *pf = 10;

        printf("%f", *pf);

        pf = &f2;
        *pf = 20;

        printf("\n%f", *pf);
    }*/

    /*{
        float* pf1 = (float*)malloc(sizeof(float)); 
        float* pf2 = (float*)malloc(sizeof(float));
        float* pfTemp = (float*)malloc(sizeof(float));

        *pf1 = 5.0f;
        *pf2 = 7.0f;

        *pfTemp = *pf1;
        *pf1 = *pf2;
        *pf2 = *pfTemp;

        printf("\npfTemp = %f", *pfTemp);
        printf("\npf1 = %f", *pf1);
        printf("\npf2 = %f", *pf2);

        free(pf2);
        free(pf1);
        free(pfTemp);
        
        return 0;
    }*/
    {
        {
            float* tf = (float*)malloc(sizeof(float) * 10);
            for (int i = 0; i < 10; i++) {
                tf[i] = 0;
                printf("%f\n", tf[i]);
            }
            tableau(tf);
        }
        
    }

    
}
