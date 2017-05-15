#include <jni.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "NativeThread.h"

JNIEXPORT jint JNICALL
Java_org_jboss_byteman_rule_helper_Helper_currentNativeId(JNIEnv *env, jobject obj) {
    int fd;
    jint tid;

    fd = open("/dev/kagent", O_RDONLY);
    if (fd < 0) {
        return 0;
    }
    tid = ioctl(fd, 0);

    close(fd);
    return tid;
}
