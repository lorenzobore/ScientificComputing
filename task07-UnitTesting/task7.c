#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <math.h> 
#include <float.h>
#include <stdlib.h>
#include <stdio.h>

#define CU_ASSERT_ALMOST_EQUAL(val1, val2, epsilon) \
    CU_ASSERT(fabs((val1) - (val2)) < (epsilon))


int N;


float multiplication(float a, float x){
    return a * x;
}

void test_multiplication(void)
{
    CU_ASSERT(multiplication(0,1) == 0);
    CU_ASSERT(multiplication(1,0) == 0);
    CU_ASSERT_ALMOST_EQUAL(multiplication(3.,0.1),0.3,FLT_EPSILON);
    CU_ASSERT_ALMOST_EQUAL(multiplication(-3.,0.1),-0.3,FLT_EPSILON);

}

float sum(float b, float y){
    return b + y;
}

void test_sum(void)
{
    CU_ASSERT(sum(0,1) == 1);
    CU_ASSERT(sum(-1,1) == 0);
    CU_ASSERT_ALMOST_EQUAL(sum(0.3,7.1),7.4,FLT_EPSILON);
    CU_ASSERT_ALMOST_EQUAL(sum(-0.3,-7.1),-7.4,FLT_EPSILON);

}

float single_daxpy(float a, float x, float y){
    return sum(multiplication(a,x),y); //*x + y;
}

void test_single_daxpy(void){

    CU_ASSERT(single_daxpy(0,1,0)==0);
    CU_ASSERT(single_daxpy(1,0,0)==0);
    CU_ASSERT(single_daxpy(1,1,0)==1);
    CU_ASSERT(single_daxpy(1,1,1)==2);

    CU_ASSERT(single_daxpy(-1,1,0)==-1);
    CU_ASSERT(single_daxpy(-1,1,1)==0);

    CU_ASSERT_ALMOST_EQUAL(single_daxpy(3,0.1,7.1),7.4,FLT_EPSILON);
    CU_ASSERT_ALMOST_EQUAL(single_daxpy(-3,0.1,-7.1),-7.4,FLT_EPSILON);

}

float* vector_daxpy(float a, float* x, float* y,int N){

    float *result = (float*) malloc(N * sizeof(float)); 
    for (int i=0;i<N;i++){
        result[i] = sum(multiplication(a,x[i]),y[i]);
    }
    return result;
}

void test_vector_daxpy(void){

    // Test with variable N
    float a=3;
    float *x = (float*) malloc(N * sizeof(float));
    float *y = (float*) malloc(N * sizeof(float));
    float *result = (float*) malloc(N * sizeof(float));

    //initialize vectors
    for (int i=0;i<N;i++){
        x[i] = 0.1;
        y[i] = 7.1;
    }

    //perform test
    int i;
    for (i=0;i<N;i++){
        result[i] = *vector_daxpy(a,x,y,N);
        CU_ASSERT_ALMOST_EQUAL(result[i],7.4, FLT_EPSILON);
    }
    CU_ASSERT(i==N);
    free(x);
    free(y);
    free(result);

}

int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("AddTestSuite", 0, 0);
    CU_add_test(suite, "test of multiplication()", test_multiplication);
    CU_add_test(suite, "test of sum()", test_sum);
    CU_add_test(suite, "test of single_daxpy()", test_single_daxpy);


    CU_pSuite new_suite = CU_add_suite("ParametrizedSuite", NULL, NULL);
    N=10;
    CU_add_test(new_suite, "test of vector_daxpy(N=10)", test_vector_daxpy);
    N=100;
    CU_add_test(new_suite, "test of vector_daxpy(N=10)", test_vector_daxpy);
    N=1000;
    CU_add_test(new_suite, "test of vector_daxpy(N=10)", test_vector_daxpy);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}