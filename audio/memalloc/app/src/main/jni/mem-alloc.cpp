#include <pthread.h>
#include <jni.h>
#include <cassert>
#include "android_debug.h"

static const uint32_t  BIG_BUFFER_COUNT = 4;
static const uint32_t   SMALL_BUFFER_COUNT = 60;
class Engine {
 public:
    uint32_t  bigMemSize_;
    uint32_t  smallMemSize_;
    uint8_t   *buffers_[64];
    volatile bool on;
    Engine();
    ~Engine();
    void AllocMemory();
    void ReleaseMemory();
};

void Engine::AllocMemory() {
    for (uint32_t i = 0; i < BIG_BUFFER_COUNT; i++) {
        buffers_[i] = new uint8_t[bigMemSize_];
        assert(buffers_[i]);
    }

    for (uint32_t i = 0; i < SMALL_BUFFER_COUNT; i++) {
        buffers_[i + BIG_BUFFER_COUNT] = new uint8_t[bigMemSize_];
        assert(buffers_[i + BIG_BUFFER_COUNT]);
    }
}

void Engine::ReleaseMemory() {
    for (uint32_t i = 0; i < BIG_BUFFER_COUNT; i++) {
        delete [] buffers_[i];
    }

    for (uint32_t i = 0; i < SMALL_BUFFER_COUNT; i++) {
        delete [] buffers_[i + BIG_BUFFER_COUNT];
    }
}

Engine::Engine() {
        bigMemSize_  = 128 * 64;
        smallMemSize_= 128;
        memset(buffers_, 0, sizeof(buffers_));
        AllocMemory();
}

Engine::~Engine() {
    ReleaseMemory();
}

static Engine engine;

extern "C" {
    JNIEXPORT jboolean JNICALL
    Java_com_google_sample_memalloc_MainActivity_startTest(JNIEnv *env, jclass type);

    JNIEXPORT jboolean JNICALL
    Java_com_google_sample_memalloc_MainActivity_stopTest(JNIEnv *env, jclass type);
};

void* TestMain(void  *ctx) {
    Engine  *tstEngine = static_cast<Engine*> (ctx);

    assert(tstEngine);
    timespec waitTime;
    memset(&waitTime, 0, sizeof(waitTime));
    waitTime.tv_nsec = 5 * 1000;

    while (tstEngine->on) {
        tstEngine->ReleaseMemory();
        tstEngine->AllocMemory();
        nanosleep(&waitTime, NULL);
    }

    return NULL;
}
JNIEXPORT jboolean JNICALL
Java_com_google_sample_memalloc_MainActivity_startTest(JNIEnv *env, jclass type) {
    pthread_t       threadInfo_;
    pthread_attr_t  threadAttr_;

    engine.on = true;
    pthread_attr_init(&threadAttr_);
    pthread_attr_setdetachstate(&threadAttr_, PTHREAD_CREATE_DETACHED);
    int result = pthread_create(&threadInfo_, &threadAttr_, TestMain, static_cast<void*>(&engine));
    assert(!result);
    return (result == 0 ? JNI_TRUE : JNI_FALSE);
}

JNIEXPORT jboolean JNICALL
Java_com_google_sample_memalloc_MainActivity_stopTest(JNIEnv *env, jclass type) {
    engine.on = false;
    return JNI_TRUE;
}