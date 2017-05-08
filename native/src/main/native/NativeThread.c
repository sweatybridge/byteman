#include <jni.h>
#include <syscall.h>
#include "NativeThread.h"

JNIEXPORT jint JNICALL
Java_org_jboss_byteman_rule_helper_Helper_currentNativeId(JNIEnv *env, jobject obj) {
    jint tid = syscall(__NR_gettid);
    return tid;
}
