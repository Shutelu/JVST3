#include<stdio.h>
#include<jni.h> 
#include<iostream>
#include"samples_App.h"

JNIEXPORT jint JNICALL Java_samples_App_printCalcul(JNIEnv *env, jclass cls, jint a, jint b)
{
    printf("Java_samples_App_printCalcul\n");
    return a + b;
}

JNIEXPORT jstring JNICALL Java_samples_App_printName(JNIEnv *env, jclass cls, jstring name)
{
    const char *str = env->GetStringUTFChars(name, 0);
    printf("Java_samples_App_printName\n");
    printf("Name: %s\n", str);
    env->ReleaseStringUTFChars(name, str);
    return env->NewStringUTF("Hello from C++");
}