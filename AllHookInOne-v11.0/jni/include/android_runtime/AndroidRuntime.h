/*
 * Copyright (C) 2005 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//

#ifndef _RUNTIME_ANDROID_RUNTIME_H
#define _RUNTIME_ANDROID_RUNTIME_H


namespace android {

class AndroidRuntime
{
public:
    AndroidRuntime();
    virtual ~AndroidRuntime();

    enum StartMode {
        Zygote,
        SystemServer,
        Application,
        Tool,
    };

    /**
     * Register a set of methods in the specified class.
     */
    static int registerNativeMethods(JNIEnv* env,
        const char* className, const JNINativeMethod* gMethods, int numMethods);

    /**
     * Find a class, with the input either of the form
     * "package/class" or "package.class".
     */
    static jclass findClass(JNIEnv* env, const char* className);

    int addVmArguments(int argc, const char* const argv[]);

    void start(const char *classname, const char* options);

    static AndroidRuntime* getRuntime();

    /**
     * This gets called after the VM has been created, but before we
     * run any code. Override it to make any FindClass calls that need
     * to use CLASSPATH.
     */
    virtual void onVmCreated(JNIEnv* env);

    /**
     * This gets called after the JavaVM has initialized.  Override it
     * with the system's native entry point.
     */
    virtual void onStarted() = 0;

    /**
     * This gets called after the JavaVM has initialized after a Zygote
     * fork. Override it to initialize threads, etc. Upon return, the
     * correct static main will be invoked.
     */
    virtual void onZygoteInit() {};


    /**
     * Called when the Java application exits.  The default
     * implementation calls exit(code).
     */
    virtual void onExit(int code);


    /** return a pointer to the VM running in this process */
    static JavaVM* getJavaVM() { return mJavaVM; }

    /** return a pointer to the JNIEnv pointer for this thread */
    static JNIEnv* getJNIEnv();

    /** return a new string corresponding to 'className' with all '.'s replaced by '/'s. */
    static char* toSlashClassName(const char* className);

private:
    static int startReg(JNIEnv* env);
    void parseExtraOpts(char* extraOptsBuf);
    int startVm(JavaVM** pJavaVM, JNIEnv** pEnv);

    /* JNI JavaVM pointer */
    static JavaVM* mJavaVM;

    static int javaThreadShell(void* args);
};

}

#endif
