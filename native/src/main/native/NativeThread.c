#include <jni.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "NativeThread.h"

JNIEXPORT jint JNICALL
Java_org_jboss_byteman_rule_helper_Helper_currentNativeId(JNIEnv *env, jobject obj) {
    int fd;
    jint tid = 0;

    fd = open("/var/log/host/kagent", O_RDONLY);
    if (fd < 0) {
        tid = errno;
    }

    return tid;
}
