#include <stdio.h>
#include <math.h>
#include <stm32f4xx.h>
#include "SVM_rbf_Iris.h"

static double accuracy = 0;
int stringCompare(const char *s1, const char *s2);
double rbf(const double x1[], const double x2[]);
double poly(const double x1[], const double x2[]);
void get_gram(const double x1[NUM_FEATURES], double x3[NUM_TRAINING_SAMPLES]);
void preprocess(double sample[]);
int predict(const double sample[]);



	

int stringCompare(const char *s1, const char *s2) {
    while (*s1 && *s2 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

double rbf(const double x1[], const double x2[])
{

    double sum = 0.0;
    for (int i = 0; i < NUM_FEATURES; ++i)
    {
        double diff = x1[i] - x2[i];
        sum += diff * diff;
    }
    return exp(-GAMMA * sqrt(sum));
}

double poly(const double x1[], const double x2[])
{
    double result = A;
    for (int i = 0; i < NUM_FEATURES; ++i)
    {
        result += x1[i] * x2[i];
    }
    return pow(result, B);
}

void get_gram(const double x1[NUM_FEATURES], double x3[NUM_TRAINING_SAMPLES])
{
    if(stringCompare("rbf",kernel)==0){
        for (int i = 0; i < NUM_TRAINING_SAMPLES; i++)
        {
            x3[i] = rbf(x1, X_train[i]);
        }
    }
    else if(stringCompare("poly",kernel)==0){
        for (int i = 0; i < NUM_TRAINING_SAMPLES; i++)
        {
            x3[i] = poly(x1, X_train[i]);
        }
    }
}




void preprocess(double sample[])
{
    for (int i = 0; i < NUM_FEATURES; i++)
    {
        sample[i] = (sample[i] - mean[i]) / std_dev[i];
    }
}

int predict(const double sample[])
{

    double scores[NUM_CLASSES];
    if (stringCompare("linear", kernel) != 0)
    {
        double x3[NUM_TRAINING_SAMPLES];
        get_gram(sample, x3);
        for (int i = 0; i < NUM_CLASSES; i++)
        {
            scores[i] = 0.0;
            for (int j = 0; j < NUM_TRAINING_SAMPLES; j++)
            {
                scores[i] += weights[i][j] * x3[j];
            }
            scores[i] += bias[i];
        }
    }

    else
    {
        for (int i = 0; i < NUM_CLASSES; i++)
        {
            scores[i] = 0.0;
            for (int j = 0; j < NUM_FEATURES; j++)
            {
                scores[i] += weights[i][j] * sample[j];
            }
            scores[i] += bias[i];
        }
    }

    double max_score = scores[0];
    int max_idx = 0;
    for (int i = 1; i < NUM_CLASSES; i++)
    {
        if (scores[i] > max_score)
        {
            max_score = scores[i];
            max_idx = i;
        }
    }

    return max_idx;
}

int main()
{
    int n_samples = sizeof(X_test) / sizeof(X_test[0]);
    double* sample = X_test[0];
    accuracy=0;
    for (int i = 0; i < n_samples; i++)
    {
        sample = X_test[i];
        preprocess(sample);
        int prediction = predict(sample);
        char* pred_class = classes[prediction];
        char* real_class = y_test[i];
        if(stringCompare(pred_class, real_class)==0){
            accuracy++;
        }
    }

    accuracy/=n_samples;
		accuracy*=100;
    printf("Accuracy: %lf", accuracy);
		printf("Kernel: %s",kernel);
		printf("Dataset: %s",dataset);
    return 0;
}
