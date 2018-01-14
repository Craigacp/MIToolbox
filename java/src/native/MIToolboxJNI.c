/*******************************************************************************
** MIToolboxJNI.c - a JNI wrapper for MIToolbox
**
**
** Initial Version - 14/01/2018
** Author - Adam Pocock
** 
** Part of MIToolbox
**
** Please check www.github.com/Craigacp/MIToolbox for updates.
** 
**  Copyright 2010-2018 Adam Pocock, The University Of Manchester
**  www.cs.manchester.ac.uk
**
**  This file is part of MIToolbox, licensed under the 3-clause BSD license.
*******************************************************************************/
#include <jni.h>
#include <stdlib.h>
#include <MIToolbox/Entropy.h>
#include <MIToolbox/RenyiEntropy.h>
#include <MIToolbox/WeightedEntropy.h>
#include <MIToolbox/MutualInformation.h>
#include <MIToolbox/RenyiMutualInformation.h>
#include <MIToolbox/WeightedMutualInformation.h>
#include "craigacp_mitoolbox_MIToolbox.h"

jint throwOutOfMemoryError(JNIEnv *env, char *message)
{
    jclass exClass;
    char *className = "java/lang/OutOfMemoryError";

    exClass = (*env)->FindClass(env, className);

    return (*env)->ThrowNew(env, exClass, message);
}

/*
 * Class:     craigacp_mitoolbox_MIToolbox
 * Method:    hx
 * Signature: ([I)D
 */
JNIEXPORT jdouble JNICALL Java_craigacp_mitoolbox_MIToolbox_checkedhx
  (JNIEnv * env, jclass clazz, jintArray javaX) {
    jint *x;
    jsize length;
    double h;
    
    /* Extract a C array for the input */
    x = (*env)->GetIntArrayElements(env, javaX, NULL);
    if (x == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input");
    }
    length = (*env)->GetArrayLength(env, javaX);

    h = calcEntropy((uint*)x,length);

    (*env)->ReleaseIntArrayElements(env, javaX, x, JNI_ABORT);

    return h;
}

/*
 * Class:     craigacp_mitoolbox_MIToolbox
 * Method:    hxcondy
 * Signature: ([I[I)D
 */
JNIEXPORT jdouble JNICALL Java_craigacp_mitoolbox_MIToolbox_checkedhxcondy
  (JNIEnv * env, jclass clazz, jintArray javaX, jintArray javaY) {
    jint *x;
    jint *y;
    jsize length;
    double h;
    
    /* Extract a C array for the input */
    x = (*env)->GetIntArrayElements(env, javaX, NULL);
    if (x == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input X");
    }
    y = (*env)->GetIntArrayElements(env, javaY, NULL);
    if (y == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input Y");
    }
    length = (*env)->GetArrayLength(env, javaX);

    h = calcConditionalEntropy((uint*)x,(uint*)y,length);

    (*env)->ReleaseIntArrayElements(env, javaX, x, JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env, javaY, y, JNI_ABORT);

    return h;
}

/*
 * Class:     craigacp_mitoolbox_MIToolbox
 * Method:    hxy
 * Signature: ([I[I)D
 */
JNIEXPORT jdouble JNICALL Java_craigacp_mitoolbox_MIToolbox_checkedhxy
  (JNIEnv * env, jclass clazz, jintArray javaX, jintArray javaY) {
    jint *x;
    jint *y;
    jsize length;
    double h;
    
    /* Extract a C array for the input */
    x = (*env)->GetIntArrayElements(env, javaX, NULL);
    if (x == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input X");
    }
    y = (*env)->GetIntArrayElements(env, javaY, NULL);
    if (y == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input Y");
    }
    length = (*env)->GetArrayLength(env, javaX);

    h = calcJointEntropy((uint*)x,(uint*)y,length);

    (*env)->ReleaseIntArrayElements(env, javaX, x, JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env, javaY, y, JNI_ABORT);

    return h;
}

/*
 * Class:     craigacp_mitoolbox_MIToolbox
 * Method:    mi
 * Signature: ([I[I)D
 */
JNIEXPORT jdouble JNICALL Java_craigacp_mitoolbox_MIToolbox_checkedmi
  (JNIEnv * env, jclass clazz, jintArray javaX, jintArray javaY) {
    jint *x;
    jint *y;
    jsize length;
    double h;
    
    /* Extract a C array for the input */
    x = (*env)->GetIntArrayElements(env, javaX, NULL);
    if (x == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input X");
    }
    y = (*env)->GetIntArrayElements(env, javaY, NULL);
    if (y == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input Y");
    }
    length = (*env)->GetArrayLength(env, javaX);

    h = calcMutualInformation((uint*)x,(uint*)y,length);

    (*env)->ReleaseIntArrayElements(env, javaX, x, JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env, javaY, y, JNI_ABORT);

    return h;
}

/*
 * Class:     craigacp_mitoolbox_MIToolbox
 * Method:    cmi
 * Signature: ([I[I[I)D
 */
JNIEXPORT jdouble JNICALL Java_craigacp_mitoolbox_MIToolbox_checkedcmi
  (JNIEnv * env, jclass clazz, jintArray javaX, jintArray javaY, jintArray javaZ) {
    jint *x;
    jint *y;
    jint *z;
    jsize length;
    double h;
    
    /* Extract a C array for the input */
    x = (*env)->GetIntArrayElements(env, javaX, NULL);
    if (x == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input X");
    }
    y = (*env)->GetIntArrayElements(env, javaY, NULL);
    if (y == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input Y");
    }
    z = (*env)->GetIntArrayElements(env, javaZ, NULL);
    if (z == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input Z");
    }
    length = (*env)->GetArrayLength(env, javaX);

    h = calcConditionalMutualInformation((uint*)x,(uint*)y,(uint*)z,length);

    (*env)->ReleaseIntArrayElements(env, javaX, x, JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env, javaY, y, JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env, javaZ, z, JNI_ABORT);

    return h;
}

/*
 * Class:     craigacp_mitoolbox_MIToolbox
 * Method:    renyiEntropy
 * Signature: (D[I)D
 */
JNIEXPORT jdouble JNICALL Java_craigacp_mitoolbox_MIToolbox_checkedRenyiEntropy
  (JNIEnv * env, jclass clazz, jdouble alpha, jintArray javaX) {
    jint *x;
    jsize length;
    double h;
    
    /* Extract a C array for the input */
    x = (*env)->GetIntArrayElements(env, javaX, NULL);
    if (x == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input");
    }
    length = (*env)->GetArrayLength(env, javaX);

    h = calcRenyiEntropy(alpha,(uint*)x,length);

    (*env)->ReleaseIntArrayElements(env, javaX, x, JNI_ABORT);

    return h;
}

/*
 * Class:     craigacp_mitoolbox_MIToolbox
 * Method:    renyiJointEntropy
 * Signature: (D[I[I)D
 */
JNIEXPORT jdouble JNICALL Java_craigacp_mitoolbox_MIToolbox_checkedRenyiJointEntropy
  (JNIEnv * env, jclass clazz, jdouble alpha, jintArray javaX, jintArray javaY) {
    jint *x;
    jint *y;
    jsize length;
    double h;
    
    /* Extract a C array for the input */
    x = (*env)->GetIntArrayElements(env, javaX, NULL);
    if (x == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input X");
    }
    y = (*env)->GetIntArrayElements(env, javaY, NULL);
    if (y == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input Y");
    }
    length = (*env)->GetArrayLength(env, javaX);

    h = calcJointRenyiEntropy(alpha,(uint*)x,(uint*)y,length);

    (*env)->ReleaseIntArrayElements(env, javaX, x, JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env, javaY, y, JNI_ABORT);

    return h;
}

/*
 * Class:     craigacp_mitoolbox_MIToolbox
 * Method:    renyiMI
 * Signature: (D[I[I)D
 */
JNIEXPORT jdouble JNICALL Java_craigacp_mitoolbox_MIToolbox_checkedRenyiMI
  (JNIEnv * env, jclass clazz, jdouble alpha, jintArray javaX, jintArray javaY) {
    jint *x;
    jint *y;
    jsize length;
    double h;
    
    /* Extract a C array for the input */
    x = (*env)->GetIntArrayElements(env, javaX, NULL);
    if (x == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input X");
    }
    y = (*env)->GetIntArrayElements(env, javaY, NULL);
    if (y == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input Y");
    }
    length = (*env)->GetArrayLength(env, javaX);

    h = calcRenyiMIDivergence(alpha,(uint*)x,(uint*)y,length);

    (*env)->ReleaseIntArrayElements(env, javaX, x, JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env, javaY, y, JNI_ABORT);

    return h;
}

/*
 * Class:     craigacp_mitoolbox_MIToolbox
 * Method:    whx
 * Signature: ([I[D)D
 */
JNIEXPORT jdouble JNICALL Java_craigacp_mitoolbox_MIToolbox_checkedwhx
  (JNIEnv * env, jclass clazz, jintArray javaX, jdoubleArray javaWeights) {
    jint *x;
    jdouble *w;
    jsize length;
    double h;
    
    /* Extract a C array for the input */
    x = (*env)->GetIntArrayElements(env, javaX, NULL);
    if (x == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input");
    }
    w = (*env)->GetDoubleArrayElements(env, javaWeights, NULL);
    if (w == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input weights");
    }
    length = (*env)->GetArrayLength(env, javaX);

    h = calcWeightedEntropy((uint*)x,w,length);

    (*env)->ReleaseIntArrayElements(env, javaX, x, JNI_ABORT);
    (*env)->ReleaseDoubleArrayElements(env, javaWeights, w, JNI_ABORT);

    return h;
}

/*
 * Class:     craigacp_mitoolbox_MIToolbox
 * Method:    whxcondy
 * Signature: ([I[I[D)D
 */
JNIEXPORT jdouble JNICALL Java_craigacp_mitoolbox_MIToolbox_checkedwhxcondy
  (JNIEnv * env, jclass clazz, jintArray javaX, jintArray javaY, jdoubleArray javaWeights) {
    jint *x;
    jint *y;
    jdouble *w;
    jsize length;
    double h;
    
    /* Extract a C array for the input */
    x = (*env)->GetIntArrayElements(env, javaX, NULL);
    if (x == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input X");
    }
    y = (*env)->GetIntArrayElements(env, javaY, NULL);
    if (y == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input Y");
    }
    w = (*env)->GetDoubleArrayElements(env, javaWeights, NULL);
    if (w == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input weights");
    }
    length = (*env)->GetArrayLength(env, javaX);

    h = calcWeightedConditionalEntropy((uint*)x,(uint*)y,w,length);

    (*env)->ReleaseIntArrayElements(env, javaX, x, JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env, javaY, y, JNI_ABORT);
    (*env)->ReleaseDoubleArrayElements(env, javaWeights, w, JNI_ABORT);

    return h;
}

/*
 * Class:     craigacp_mitoolbox_MIToolbox
 * Method:    whxy
 * Signature: ([I[I[D)D
 */
JNIEXPORT jdouble JNICALL Java_craigacp_mitoolbox_MIToolbox_checkedwhxy
  (JNIEnv * env, jclass clazz, jintArray javaX, jintArray javaY, jdoubleArray javaWeights) {
    jint *x;
    jint *y;
    jdouble *w;
    jsize length;
    double h;
    
    /* Extract a C array for the input */
    x = (*env)->GetIntArrayElements(env, javaX, NULL);
    if (x == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input X");
    }
    y = (*env)->GetIntArrayElements(env, javaY, NULL);
    if (y == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input Y");
    }
    w = (*env)->GetDoubleArrayElements(env, javaWeights, NULL);
    if (w == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input weights");
    }
    length = (*env)->GetArrayLength(env, javaX);

    h = calcWeightedJointEntropy((uint*)x,(uint*)y,w,length);

    (*env)->ReleaseIntArrayElements(env, javaX, x, JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env, javaY, y, JNI_ABORT);
    (*env)->ReleaseDoubleArrayElements(env, javaWeights, w, JNI_ABORT);

    return h;
}

/*
 * Class:     craigacp_mitoolbox_MIToolbox
 * Method:    wmi
 * Signature: ([I[I[D)D
 */
JNIEXPORT jdouble JNICALL Java_craigacp_mitoolbox_MIToolbox_checkedwmi
  (JNIEnv * env, jclass clazz, jintArray javaX, jintArray javaY, jdoubleArray javaWeights) {
    jint *x;
    jint *y;
    jdouble *w;
    jsize length;
    double h;
    
    /* Extract a C array for the input */
    x = (*env)->GetIntArrayElements(env, javaX, NULL);
    if (x == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input X");
    }
    y = (*env)->GetIntArrayElements(env, javaY, NULL);
    if (y == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input Y");
    }
    w = (*env)->GetDoubleArrayElements(env, javaWeights, NULL);
    if (w == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input weights");
    }
    length = (*env)->GetArrayLength(env, javaX);

    h = calcWeightedMutualInformation((uint*)x,(uint*)y,w,length);

    (*env)->ReleaseIntArrayElements(env, javaX, x, JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env, javaY, y, JNI_ABORT);
    (*env)->ReleaseDoubleArrayElements(env, javaWeights, w, JNI_ABORT);

    return h;
}

/*
 * Class:     craigacp_mitoolbox_MIToolbox
 * Method:    wcmi
 * Signature: ([I[I[I[D)D
 */
JNIEXPORT jdouble JNICALL Java_craigacp_mitoolbox_MIToolbox_checkedwcmi
  (JNIEnv * env, jclass clazz, jintArray javaX, jintArray javaY, jintArray javaZ, jdoubleArray javaWeights) {
    jint *x;
    jint *y;
    jint *z;
    jdouble *w;
    jsize length;
    double h;
    
    /* Extract a C array for the input */
    x = (*env)->GetIntArrayElements(env, javaX, NULL);
    if (x == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input X");
    }
    y = (*env)->GetIntArrayElements(env, javaY, NULL);
    if (y == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input Y");
    }
    z = (*env)->GetIntArrayElements(env, javaZ, NULL);
    if (z == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input Z");
    }
    w = (*env)->GetDoubleArrayElements(env, javaWeights, NULL);
    if (w == NULL) {
        throwOutOfMemoryError(env, "Could not allocate array to hold the input weights");
    }
    length = (*env)->GetArrayLength(env, javaX);

    h = calcWeightedConditionalMutualInformation((uint*)x,(uint*)y,(uint*)z,w,length);

    (*env)->ReleaseIntArrayElements(env, javaX, x, JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env, javaY, y, JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env, javaZ, z, JNI_ABORT);
    (*env)->ReleaseDoubleArrayElements(env, javaWeights, w, JNI_ABORT);

    return h;
}

