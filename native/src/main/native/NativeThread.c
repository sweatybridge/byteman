#include <jni.h>
#include <fcntl.h>
#include <unistd.h>
#include <syscall.h>
#include "NativeThread.h"

JNIEXPORT jint JNICALL
Java_org_jboss_byteman_rule_helper_Helper_currentNativeId(JNIEnv *env, jobject obj) {
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
