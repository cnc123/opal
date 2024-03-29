/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class OpalProductDescription : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal OpalProductDescription(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(OpalProductDescription obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~OpalProductDescription() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          OPALPINVOKE.delete_OpalProductDescription(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public string vendor {
    set {
      OPALPINVOKE.OpalProductDescription_vendor_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalProductDescription_vendor_get(swigCPtr);
      return ret;
    } 
  }

  public string name {
    set {
      OPALPINVOKE.OpalProductDescription_name_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalProductDescription_name_get(swigCPtr);
      return ret;
    } 
  }

  public string version {
    set {
      OPALPINVOKE.OpalProductDescription_version_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalProductDescription_version_get(swigCPtr);
      return ret;
    } 
  }

  public uint t35CountryCode {
    set {
      OPALPINVOKE.OpalProductDescription_t35CountryCode_set(swigCPtr, value);
    } 
    get {
      uint ret = OPALPINVOKE.OpalProductDescription_t35CountryCode_get(swigCPtr);
      return ret;
    } 
  }

  public uint t35Extension {
    set {
      OPALPINVOKE.OpalProductDescription_t35Extension_set(swigCPtr, value);
    } 
    get {
      uint ret = OPALPINVOKE.OpalProductDescription_t35Extension_get(swigCPtr);
      return ret;
    } 
  }

  public uint manufacturerCode {
    set {
      OPALPINVOKE.OpalProductDescription_manufacturerCode_set(swigCPtr, value);
    } 
    get {
      uint ret = OPALPINVOKE.OpalProductDescription_manufacturerCode_get(swigCPtr);
      return ret;
    } 
  }

  public OpalProductDescription() : this(OPALPINVOKE.new_OpalProductDescription(), true) {
  }

}
