/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class OpalMessageParam : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal OpalMessageParam(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(OpalMessageParam obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~OpalMessageParam() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          OPALPINVOKE.delete_OpalMessageParam(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public string commandError {
    set {
      OPALPINVOKE.OpalMessageParam_commandError_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalMessageParam_commandError_get(swigCPtr);
      return ret;
    } 
  }

  public OpalParamGeneral general {
    set {
      OPALPINVOKE.OpalMessageParam_general_set(swigCPtr, OpalParamGeneral.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_general_get(swigCPtr);
      OpalParamGeneral ret = (cPtr == IntPtr.Zero) ? null : new OpalParamGeneral(cPtr, false);
      return ret;
    } 
  }

  public OpalParamProtocol protocol {
    set {
      OPALPINVOKE.OpalMessageParam_protocol_set(swigCPtr, OpalParamProtocol.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_protocol_get(swigCPtr);
      OpalParamProtocol ret = (cPtr == IntPtr.Zero) ? null : new OpalParamProtocol(cPtr, false);
      return ret;
    } 
  }

  public OpalParamRegistration registrationInfo {
    set {
      OPALPINVOKE.OpalMessageParam_registrationInfo_set(swigCPtr, OpalParamRegistration.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_registrationInfo_get(swigCPtr);
      OpalParamRegistration ret = (cPtr == IntPtr.Zero) ? null : new OpalParamRegistration(cPtr, false);
      return ret;
    } 
  }

  public OpalStatusRegistration registrationStatus {
    set {
      OPALPINVOKE.OpalMessageParam_registrationStatus_set(swigCPtr, OpalStatusRegistration.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_registrationStatus_get(swigCPtr);
      OpalStatusRegistration ret = (cPtr == IntPtr.Zero) ? null : new OpalStatusRegistration(cPtr, false);
      return ret;
    } 
  }

  public OpalParamSetUpCall callSetUp {
    set {
      OPALPINVOKE.OpalMessageParam_callSetUp_set(swigCPtr, OpalParamSetUpCall.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_callSetUp_get(swigCPtr);
      OpalParamSetUpCall ret = (cPtr == IntPtr.Zero) ? null : new OpalParamSetUpCall(cPtr, false);
      return ret;
    } 
  }

  public string callToken {
    set {
      OPALPINVOKE.OpalMessageParam_callToken_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalMessageParam_callToken_get(swigCPtr);
      return ret;
    } 
  }

  public OpalStatusIncomingCall incomingCall {
    set {
      OPALPINVOKE.OpalMessageParam_incomingCall_set(swigCPtr, OpalStatusIncomingCall.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_incomingCall_get(swigCPtr);
      OpalStatusIncomingCall ret = (cPtr == IntPtr.Zero) ? null : new OpalStatusIncomingCall(cPtr, false);
      return ret;
    } 
  }

  public OpalParamAnswerCall answerCall {
    set {
      OPALPINVOKE.OpalMessageParam_answerCall_set(swigCPtr, OpalParamAnswerCall.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_answerCall_get(swigCPtr);
      OpalParamAnswerCall ret = (cPtr == IntPtr.Zero) ? null : new OpalParamAnswerCall(cPtr, false);
      return ret;
    } 
  }

  public OpalStatusUserInput userInput {
    set {
      OPALPINVOKE.OpalMessageParam_userInput_set(swigCPtr, OpalStatusUserInput.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_userInput_get(swigCPtr);
      OpalStatusUserInput ret = (cPtr == IntPtr.Zero) ? null : new OpalStatusUserInput(cPtr, false);
      return ret;
    } 
  }

  public OpalStatusMessageWaiting messageWaiting {
    set {
      OPALPINVOKE.OpalMessageParam_messageWaiting_set(swigCPtr, OpalStatusMessageWaiting.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_messageWaiting_get(swigCPtr);
      OpalStatusMessageWaiting ret = (cPtr == IntPtr.Zero) ? null : new OpalStatusMessageWaiting(cPtr, false);
      return ret;
    } 
  }

  public OpalStatusLineAppearance lineAppearance {
    set {
      OPALPINVOKE.OpalMessageParam_lineAppearance_set(swigCPtr, OpalStatusLineAppearance.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_lineAppearance_get(swigCPtr);
      OpalStatusLineAppearance ret = (cPtr == IntPtr.Zero) ? null : new OpalStatusLineAppearance(cPtr, false);
      return ret;
    } 
  }

  public OpalStatusCallCleared callCleared {
    set {
      OPALPINVOKE.OpalMessageParam_callCleared_set(swigCPtr, OpalStatusCallCleared.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_callCleared_get(swigCPtr);
      OpalStatusCallCleared ret = (cPtr == IntPtr.Zero) ? null : new OpalStatusCallCleared(cPtr, false);
      return ret;
    } 
  }

  public OpalParamCallCleared clearCall {
    set {
      OPALPINVOKE.OpalMessageParam_clearCall_set(swigCPtr, OpalParamCallCleared.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_clearCall_get(swigCPtr);
      OpalParamCallCleared ret = (cPtr == IntPtr.Zero) ? null : new OpalParamCallCleared(cPtr, false);
      return ret;
    } 
  }

  public OpalStatusMediaStream mediaStream {
    set {
      OPALPINVOKE.OpalMessageParam_mediaStream_set(swigCPtr, OpalStatusMediaStream.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_mediaStream_get(swigCPtr);
      OpalStatusMediaStream ret = (cPtr == IntPtr.Zero) ? null : new OpalStatusMediaStream(cPtr, false);
      return ret;
    } 
  }

  public OpalParamSetUserData setUserData {
    set {
      OPALPINVOKE.OpalMessageParam_setUserData_set(swigCPtr, OpalParamSetUserData.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_setUserData_get(swigCPtr);
      OpalParamSetUserData ret = (cPtr == IntPtr.Zero) ? null : new OpalParamSetUserData(cPtr, false);
      return ret;
    } 
  }

  public OpalParamRecording recording {
    set {
      OPALPINVOKE.OpalMessageParam_recording_set(swigCPtr, OpalParamRecording.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_recording_get(swigCPtr);
      OpalParamRecording ret = (cPtr == IntPtr.Zero) ? null : new OpalParamRecording(cPtr, false);
      return ret;
    } 
  }

  public OpalStatusTransferCall transferStatus {
    set {
      OPALPINVOKE.OpalMessageParam_transferStatus_set(swigCPtr, OpalStatusTransferCall.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_transferStatus_get(swigCPtr);
      OpalStatusTransferCall ret = (cPtr == IntPtr.Zero) ? null : new OpalStatusTransferCall(cPtr, false);
      return ret;
    } 
  }

  public OpalStatusIVR ivrStatus {
    set {
      OPALPINVOKE.OpalMessageParam_ivrStatus_set(swigCPtr, OpalStatusIVR.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_ivrStatus_get(swigCPtr);
      OpalStatusIVR ret = (cPtr == IntPtr.Zero) ? null : new OpalStatusIVR(cPtr, false);
      return ret;
    } 
  }

  public OpalPresenceStatus presenceStatus {
    set {
      OPALPINVOKE.OpalMessageParam_presenceStatus_set(swigCPtr, OpalPresenceStatus.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_presenceStatus_get(swigCPtr);
      OpalPresenceStatus ret = (cPtr == IntPtr.Zero) ? null : new OpalPresenceStatus(cPtr, false);
      return ret;
    } 
  }

  public OpalInstantMessage instantMessage {
    set {
      OPALPINVOKE.OpalMessageParam_instantMessage_set(swigCPtr, OpalInstantMessage.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalMessageParam_instantMessage_get(swigCPtr);
      OpalInstantMessage ret = (cPtr == IntPtr.Zero) ? null : new OpalInstantMessage(cPtr, false);
      return ret;
    } 
  }

  public OpalMessageParam() : this(OPALPINVOKE.new_OpalMessageParam(), true) {
  }

}
