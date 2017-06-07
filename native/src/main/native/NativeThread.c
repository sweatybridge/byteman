#include <jni.h>
#include <fcntl.h>
#include <unistd.h>
#include <syscall.h>
#include "NativeThread.h"

int fd;

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT jint JNICALL
Java_org_jboss_byteman_rule_helper_Helper_currentNativeId(JNIEnv *env, jclass obj) {
    char *buf;
    jint tid = 0;

    // should only be called once, otherwise resource leak
    fd = open("/var/log/host/kagent", O_RDWR);
    if (fd < 0) {
        return 0;
    }

    tid = read(fd, buf, 0);

    return tid;
}

JNIEXPORT void JNICALL
Java_org_jboss_byteman_rule_helper_Helper_printTrace(JNIEnv *env, jclass obj, jstring trace) {
    const char *buf;
    size_t len;
    int rc;

    buf = (*env)->GetStringUTFChars(env, trace, NULL);
    len = (*env)->GetStringUTFLength(env, trace);

    rc = write(fd, buf, len);
    // fd will be automatically closed on program exit
}
#ifdef __cplusplus
}
#endif
