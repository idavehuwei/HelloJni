#include "HelloJni.h"
#include <stdio.h>
#include <string.h>

JNIEXPORT jstring JNICALL Java_HelloJni_getStringFromCStatic(JNIEnv * env, jclass clz){
    return (*env)->NewStringUTF(env, "C String static");
}

JNIEXPORT jstring JNICALL Java_HelloJni_getStringFromCNonStatic(JNIEnv * env, jobject obj){
    return (*env)->NewStringUTF(env, "C string non static");
}

JNIEXPORT jstring JNICALL Java_HelloJni_accessField(JNIEnv * env, jobject obj){
    jclass jclz = (*env)->GetObjectClass(env, obj);
    jfieldID fid = (*env)->GetFieldID(env, jclz, "key", "Ljava/lang/String;");
    jstring jstr = (*env)->GetObjectField(env, obj, fid);
    char* c_str = (*env)->GetStringUTFChars(env, jstr, NULL);
    char text[30] = "solarex";
    strcat(text, c_str);
    jstring new_str = (*env)->NewStringUTF(env, text);
    (*env)->SetObjectField(env, obj, fid, new_str);
    (*env)->ReleaseStringChars(env, new_str, c_str);
    return new_str;
}

JNIEXPORT void JNICALL Java_HelloJni_accessStaticField(JNIEnv * env, jobject obj){
    jclass jclz = (*env)->GetObjectClass(env, obj);
    jfieldID fid = (*env)->GetStaticFieldID(env, jclz, "count", "I");
    jint count = (*env)->GetStaticIntField(env, jclz, fid);
    count++;
    (*env)->SetStaticIntField(env, jclz, fid, count);
}

JNIEXPORT void JNICALL Java_HelloJni_accessMethod(JNIEnv * env, jobject obj){
    jclass jclz = (*env)->GetObjectClass(env, obj);
    jmethodID mid = (*env)->GetMethodID(env, jclz, "getRandomInt", "(I)I");
    jint random = (*env)->CallIntMethod(env, obj, mid, 200);
    printf("C random = %d\n", random);
}

JNIEXPORT void JNICALL Java_HelloJni_accessStaticMethod(JNIEnv * env, jobject obj){
    jclass jclz = (*env)->GetObjectClass(env, obj);
    jmethodID mid = (*env)->GetStaticMethodID(env, jclz, "getUUID","()Ljava/lang/String;");
    jstring uuid = (*env)->CallStaticObjectMethod(env, jclz, mid);
    char * uuid_c = (*env)->GetStringUTFChars(env, uuid, NULL);
    printf("uuid_c : %s\n", uuid_c);
    char filename[100];
    sprintf(filename, "%s.txt", uuid_c);
    printf("filename : %s\n", filename);

    FILE *fp = fopen(filename, "w");
    fputs("Solarex", fp);
    fclose(fp);
    printf("write file success\n");
}