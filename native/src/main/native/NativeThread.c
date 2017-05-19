#include <jni.h>
#include <fcntl.h>
#include <unistd.h>
#include <syscall.h>
#include "NativeThread.h"

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT jint JNICALL
Java_org_jboss_byteman_rule_helper_Helper_currentNativeId(JNIEnv *env, jclass obj) {
    int fd;
    char *buf;
    jint tid = 0;

    fd = open("/var/log/host/kagent", O_RDONLY);
    if (fd < 0) {
        return 0;
    }

    tid = read(fd, buf, 0);

    close(fd);
    return tid;
}

JNIEXPORT void JNICALL
Java_org_jboss_byteman_rule_helper_Helper_printTrace(JNIEnv *env, jclass obj, jstring trace) {
    int fd;
    const char *buf;
    size_t len;
    int rc;

    fd = open("/var/log/host/kagent", O_RDWR);
    if (fd < 0) {
        return;
    }

    buf = (*env)->GetStringUTFChars(env, trace, NULL);
    len = (*env)->GetStringUTFLength(env, trace);

    rc = write(fd, buf, len);
    if (rc < 0) {
        return;
    }

    close(fd);
}
#ifdef __cplusplus
}
#endif
