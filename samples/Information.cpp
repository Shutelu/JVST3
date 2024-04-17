#include<stdio.h>
#include<jni.h> 
#include<iostream>
#include"samples_App.h"

//Nous retournons un type jint qui est la somme de a et b de type jint
JNIEXPORT jint JNICALL Java_samples_App_printCalcul(JNIEnv *env, jclass cls, jint a, jint b)
{
    printf("Java_samples_App_printCalcul\n");
    return a + b;
}

//Nous retournons un type jstring qui est le message "Hello from C++"
JNIEXPORT jstring JNICALL Java_samples_App_printName(JNIEnv *env, jclass cls, jstring name)
{
    //Nous récupérons le nom de la personne
    const char *str = env->GetStringUTFChars(name, 0);
    printf("Java_samples_App_printName\n");
    printf("Name: %s\n", str);

    //Nous concaténons le message "Monsieur " avec le nom de la personne
    std::string greeting = "Monsieur ";
    greeting += str;

    //Nous libérons la mémoire
    env->ReleaseStringUTFChars(name, str);

    //Nous retournons le message
    return env->NewStringUTF(greeting.c_str());
}