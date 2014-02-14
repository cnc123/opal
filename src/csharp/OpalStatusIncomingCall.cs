/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class OpalStatusIncomingCall : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal OpalStatusIncomingCall(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(OpalStatusIncomingCall obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~OpalStatusIncomingCall() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          OPALPINVOKE.delete_OpalStatusIncomingCall(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public string callToken {
    set {
      OPALPINVOKE.OpalStatusIncomingCall_callToken_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusIncomingCall_callToken_get(swigCPtr);
      return ret;
    } 
  }

  public string localAddress {
    set {
      OPALPINVOKE.OpalStatusIncomingCall_localAddress_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusIncomingCall_localAddress_get(swigCPtr);
      return ret;
    } 
  }

  public string remoteAddress {
    set {
      OPALPINVOKE.OpalStatusIncomingCall_remoteAddress_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusIncomingCall_remoteAddress_get(swigCPtr);
      return ret;
    } 
  }

  public string remotePartyNumber {
    set {
      OPALPINVOKE.OpalStatusIncomingCall_remotePartyNumber_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusIncomingCall_remotePartyNumber_get(swigCPtr);
      return ret;
    } 
  }

  public string remoteDisplayName {
    set {
      OPALPINVOKE.OpalStatusIncomingCall_remoteDisplayName_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusIncomingCall_remoteDisplayName_get(swigCPtr);
      return ret;
    } 
  }

  public string calledAddress {
    set {
      OPALPINVOKE.OpalStatusIncomingCall_calledAddress_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusIncomingCall_calledAddress_get(swigCPtr);
      return ret;
    } 
  }

  public string calledPartyNumber {
    set {
      OPALPINVOKE.OpalStatusIncomingCall_calledPartyNumber_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusIncomingCall_calledPartyNumber_get(swigCPtr);
      return ret;
    } 
  }

  public OpalProductDescription product {
    set {
      OPALPINVOKE.OpalStatusIncomingCall_product_set(swigCPtr, OpalProductDescription.getCPtr(value));
    } 
    get {
      IntPtr cPtr = OPALPINVOKE.OpalStatusIncomingCall_product_get(swigCPtr);
      OpalProductDescription ret = (cPtr == IntPtr.Zero) ? null : new OpalProductDescription(cPtr, false);
      return ret;
    } 
  }

  public string alertingType {
    set {
      OPALPINVOKE.OpalStatusIncomingCall_alertingType_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusIncomingCall_alertingType_get(swigCPtr);
      return ret;
    } 
  }

  public string protocolCallId {
    set {
      OPALPINVOKE.OpalStatusIncomingCall_protocolCallId_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusIncomingCall_protocolCallId_get(swigCPtr);
      return ret;
    } 
  }

  public string referredByAddress {
    set {
      OPALPINVOKE.OpalStatusIncomingCall_referredByAddress_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusIncomingCall_referredByAddress_get(swigCPtr);
      return ret;
    } 
  }

  public string redirectingNumber {
    set {
      OPALPINVOKE.OpalStatusIncomingCall_redirectingNumber_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusIncomingCall_redirectingNumber_get(swigCPtr);
      return ret;
    } 
  }

  public OpalStatusIncomingCall() : this(OPALPINVOKE.new_OpalStatusIncomingCall(), true) {
  }

}