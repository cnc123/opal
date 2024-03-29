/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class OpalParamRecording : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal OpalParamRecording(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(OpalParamRecording obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~OpalParamRecording() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          OPALPINVOKE.delete_OpalParamRecording(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public string callToken {
    set {
      OPALPINVOKE.OpalParamRecording_callToken_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalParamRecording_callToken_get(swigCPtr);
      return ret;
    } 
  }

  public string file {
    set {
      OPALPINVOKE.OpalParamRecording_file_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalParamRecording_file_get(swigCPtr);
      return ret;
    } 
  }

  public uint channels {
    set {
      OPALPINVOKE.OpalParamRecording_channels_set(swigCPtr, value);
    } 
    get {
      uint ret = OPALPINVOKE.OpalParamRecording_channels_get(swigCPtr);
      return ret;
    } 
  }

  public string audioFormat {
    set {
      OPALPINVOKE.OpalParamRecording_audioFormat_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalParamRecording_audioFormat_get(swigCPtr);
      return ret;
    } 
  }

  public string videoFormat {
    set {
      OPALPINVOKE.OpalParamRecording_videoFormat_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalParamRecording_videoFormat_get(swigCPtr);
      return ret;
    } 
  }

  public uint videoWidth {
    set {
      OPALPINVOKE.OpalParamRecording_videoWidth_set(swigCPtr, value);
    } 
    get {
      uint ret = OPALPINVOKE.OpalParamRecording_videoWidth_get(swigCPtr);
      return ret;
    } 
  }

  public uint videoHeight {
    set {
      OPALPINVOKE.OpalParamRecording_videoHeight_set(swigCPtr, value);
    } 
    get {
      uint ret = OPALPINVOKE.OpalParamRecording_videoHeight_get(swigCPtr);
      return ret;
    } 
  }

  public uint videoRate {
    set {
      OPALPINVOKE.OpalParamRecording_videoRate_set(swigCPtr, value);
    } 
    get {
      uint ret = OPALPINVOKE.OpalParamRecording_videoRate_get(swigCPtr);
      return ret;
    } 
  }

  public OpalVideoRecordMixMode videoMixing {
    set {
      OPALPINVOKE.OpalParamRecording_videoMixing_set(swigCPtr, (int)value);
    } 
    get {
      OpalVideoRecordMixMode ret = (OpalVideoRecordMixMode)OPALPINVOKE.OpalParamRecording_videoMixing_get(swigCPtr);
      return ret;
    } 
  }

  public OpalParamRecording() : this(OPALPINVOKE.new_OpalParamRecording(), true) {
  }

}
