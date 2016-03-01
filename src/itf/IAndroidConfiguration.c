/*
 * Copyright (C) 2010 The Android Open Source Project
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

/* AndroidConfiguration implementation */

#include "sles_allinclusive.h"
#include <SLES/OpenSLES_Android.h>

static SLresult IAndroidConfiguration_SetConfiguration(SLAndroidConfigurationItf self,
        const SLchar *configKey,
        const void *pConfigValue,
        SLuint32 valueSize)
{
    SL_ENTER_INTERFACE

    // object-specific code will check that valueSize is large enough for the key
    if (NULL == configKey || NULL == pConfigValue || valueSize == 0) {
        result = SL_RESULT_PARAMETER_INVALID;

    } else {
        IAndroidConfiguration *thiz = (IAndroidConfiguration *) self;
        interface_lock_exclusive(thiz);

        // route configuration to the appropriate object
        switch (IObjectToObjectID((thiz)->mThis)) {
        case SL_OBJECTID_AUDIORECORDER:
            SL_LOGV("SetConfiguration issued for AudioRecorder key=%s valueSize=%u",
                    configKey, valueSize);
            result = android_audioRecorder_setConfig((CAudioRecorder *) thiz->mThis, configKey,
                    pConfigValue, valueSize);
            break;
        case SL_OBJECTID_AUDIOPLAYER:
            SL_LOGV("SetConfiguration issued for AudioPlayer key=%s valueSize=%u",
                    configKey, valueSize);
            result = android_audioPlayer_setConfig((CAudioPlayer *) thiz->mThis, configKey,
                    pConfigValue, valueSize);
            break;
        default:
            result = SL_RESULT_FEATURE_UNSUPPORTED;
            break;
        }

        interface_unlock_exclusive(thiz);
    }

    SL_LEAVE_INTERFACE
}


static SLresult IAndroidConfiguration_GetConfiguration(SLAndroidConfigurationItf self,
        const SLchar *configKey,
        SLuint32 *pValueSize,
        void *pConfigValue)
{
    SL_ENTER_INTERFACE

    // non-NULL pValueSize is required, but a NULL pConfigValue is allowed, so
    // that we can report the actual value size without returning the value itself
    if (NULL == configKey || NULL == pValueSize) {
        result = SL_RESULT_PARAMETER_INVALID;
    } else {
        IAndroidConfiguration *thiz = (IAndroidConfiguration *) self;
        interface_lock_exclusive(thiz);

        // route configuration request to the appropriate object
        switch (IObjectToObjectID((thiz)->mThis)) {
        case SL_OBJECTID_AUDIORECORDER:
            result = android_audioRecorder_getConfig((CAudioRecorder *) thiz->mThis, configKey,
                    pValueSize, pConfigValue);
            break;
        case SL_OBJECTID_AUDIOPLAYER:
            result = android_audioPlayer_getConfig((CAudioPlayer *) thiz->mThis, configKey,
                    pValueSize, pConfigValue);
        default:
            result = SL_RESULT_FEATURE_UNSUPPORTED;
            break;
        }

        interface_unlock_exclusive(thiz);
    }

    SL_LEAVE_INTERFACE
}

/*
 * Native Routing API
 */

/*
 * Acquires a Java AudioRouting object (interface implementation) which can be used to control
 * the routing of the associated native player or recorder. Note that the Java Routing object
 * can not be acquired until the AudioTrack  or AudioRecorder associated with the
 * SLAndroidConfigurationItf has been realized (i.e. SLPlayItf::realize() or
 * SLRecordItf::realize() has been called).
 * Parameters:
 *   self   An SLAndroidConfigurationItf obtained from either an OpenSL ES AudioPlayer
 *          or AudioRecorder.
 *   j_env  The Java Environment pointer (passed in to the calling JNI function).
 *   pObject    Points to the jobject to receive the acquired AudioRouting interface
 *          implementation.
 * Returns SL_RESULT_SUCCESS is the AudioRouting is acquired, SL_RESULT_PARAMETER_INVALID if
 *   there is a problem with the arguments causing the function to fail,
 *   SL_RESULT_PRECONDITIONS_VIOLATED it the AudioPlayer or AudioRecorder object associated
 *   with the ConfigurationItf has not been realized.
 */
static SLresult IAndroidConfiguration_AcquireJavaAudioRouting(SLAndroidConfigurationItf self,
        JNIEnv *j_env, jobject *pObject)
{
    SL_ENTER_INTERFACE

    if (j_env == NULL || self == NULL || pObject == NULL) {
        result =  SL_RESULT_PARAMETER_INVALID;
    } else {
        IObject *thisObject = InterfaceToIObject((IAndroidConfiguration *) self);

        switch (IObjectToObjectID(thisObject)) {
        case SL_OBJECTID_AUDIOPLAYER:
        {
            // Get the constructor for (Java) AudioTrackRoutingProxy
            jclass clsAudioTrackRoutingProxy =
                    j_env->FindClass("android/media/AudioTrackRoutingProxy");
            jmethodID midAudioTrackRoutingProxy_ctor =
                j_env->GetMethodID(clsAudioTrackRoutingProxy, "<init>", "(J)V");

            IAndroidConfiguration* configItf = (IAndroidConfiguration*)self; // Get internal struct
            IObject* configObj = configItf->mThis;              // get corresponding object
            CAudioPlayer* player = (CAudioPlayer*)configObj;    // get the native player

            // Make sure the player has been realized.
            if (player->mObject.mState != SL_OBJECT_STATE_REALIZED) {
                result = SL_RESULT_PRECONDITIONS_VIOLATED;
                SL_LOGE("Error creating routing object - Player not realized.");
            } else {
                android::AudioTrack* pAudioTrack = player->mAudioTrack.get();
                if (pAudioTrack == NULL) {
                    result = SL_RESULT_INTERNAL_ERROR;
                } else {
                    *pObject = j_env->NewObject(clsAudioTrackRoutingProxy,
                                                midAudioTrackRoutingProxy_ctor,
                                                (uintptr_t)pAudioTrack /*audioTrackObjInLong*/);
                    if (j_env->ExceptionCheck()) {
                        SL_LOGE("Java exception creating player routing object.");
                        result = SL_RESULT_INTERNAL_ERROR;
                    } else {
                        result = SL_RESULT_SUCCESS;
                    }
                }
            }
        }
            break;

        case SL_OBJECTID_AUDIORECORDER:
        {
            // Get the constructor for (Java) AudioRecordRoutingProxy
            jclass clsAudioRecordRoutingProxy =
                    j_env->FindClass("android/media/AudioRecordRoutingProxy");
            jmethodID midAudioRecordRoutingProxy_ctor =
                j_env->GetMethodID(clsAudioRecordRoutingProxy, "<init>", "(J)V");

            IAndroidConfiguration* configItf = (IAndroidConfiguration*)self; // Get internal struct
            IObject* configObj = configItf->mThis;                  // get corresponding object
            CAudioRecorder* recorder = (CAudioRecorder*)configObj;  // get the native recorder

            // Make sure the recorder has been realized.
            if (recorder->mObject.mState != SL_OBJECT_STATE_REALIZED) {
                result = SL_RESULT_PRECONDITIONS_VIOLATED;
                SL_LOGE("Error creating routing object - Recorder not realized.");
            } else {
                android::AudioRecord* pAudioRecord = recorder->mAudioRecord.get();
                if (pAudioRecord == NULL) {
                    result = SL_RESULT_INTERNAL_ERROR;
                } else {
                    *pObject =
                            j_env->NewObject(clsAudioRecordRoutingProxy,
                                             midAudioRecordRoutingProxy_ctor,
                                             (uintptr_t)pAudioRecord /*audioRecordObjInLong*/);
                    if (j_env->ExceptionCheck()) {
                        SL_LOGE("Java exception creating recorder routing object.");
                        result = SL_RESULT_INTERNAL_ERROR;
                    } else {
                        result = SL_RESULT_SUCCESS;
                    }
                }
            }
        }
            break;

        default:
            result = SL_RESULT_PARAMETER_INVALID;
            break;
        }
    }

    SL_LEAVE_INTERFACE
}

static const struct SLAndroidConfigurationItf_ IAndroidConfiguration_Itf = {
    IAndroidConfiguration_SetConfiguration,
    IAndroidConfiguration_GetConfiguration,
    IAndroidConfiguration_AcquireJavaAudioRouting
};

void IAndroidConfiguration_init(void *self)
{
    IAndroidConfiguration *thiz = (IAndroidConfiguration *) self;
    thiz->mItf = &IAndroidConfiguration_Itf;
}
