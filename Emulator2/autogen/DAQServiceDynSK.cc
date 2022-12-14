// This file is generated by omniidl (C++ backend) - omniORB_4_2. Do not edit.

#include "DAQService.hh"

OMNI_USING_NAMESPACE(omni)

static const char* _0RL_dyn_library_version = omniORB_4_2_dyn;

static ::CORBA::TypeCode::_Tracker _0RL_tcTrack(__FILE__);

static CORBA::PR_structMember _0RL_structmember_NameValue[] = {
  {"name", CORBA::TypeCode::PR_string_tc(0, &_0RL_tcTrack)},
  {"value", CORBA::TypeCode::PR_string_tc(0, &_0RL_tcTrack)}
};

#ifdef _0RL_tc_NameValue
#  undef _0RL_tc_NameValue
#endif
static CORBA::TypeCode_ptr _0RL_tc_NameValue = CORBA::TypeCode::PR_struct_tc("IDL:NameValue:1.0", "NameValue", _0RL_structmember_NameValue, 2, &_0RL_tcTrack);

const CORBA::TypeCode_ptr _tc_NameValue = _0RL_tc_NameValue;






static CORBA::TypeCode_ptr _0RL_tc_NVList = CORBA::TypeCode::PR_alias_tc("IDL:NVList:1.0", "NVList", CORBA::TypeCode::PR_sequence_tc(0, _0RL_tc_NameValue, &_0RL_tcTrack), &_0RL_tcTrack);


const CORBA::TypeCode_ptr _tc_NVList = _0RL_tc_NVList;

static const char* _0RL_enumMember_DAQLifeCycleState[] = { "LOADED", "CONFIGURED", "RUNNING", "PAUSED" };
static CORBA::TypeCode_ptr _0RL_tc_DAQLifeCycleState = CORBA::TypeCode::PR_enum_tc("IDL:DAQLifeCycleState:1.0", "DAQLifeCycleState", _0RL_enumMember_DAQLifeCycleState, 4, &_0RL_tcTrack);
const CORBA::TypeCode_ptr _tc_DAQLifeCycleState = _0RL_tc_DAQLifeCycleState;

static const char* _0RL_enumMember_DAQCommand[] = { "CMD_CONFIGURE", "CMD_START", "CMD_STOP", "CMD_UNCONFIGURE", "CMD_PAUSE", "CMD_RESUME", "CMD_NOP" };
static CORBA::TypeCode_ptr _0RL_tc_DAQCommand = CORBA::TypeCode::PR_enum_tc("IDL:DAQCommand:1.0", "DAQCommand", _0RL_enumMember_DAQCommand, 7, &_0RL_tcTrack);
const CORBA::TypeCode_ptr _tc_DAQCommand = _0RL_tc_DAQCommand;

static const char* _0RL_enumMember_DAQDone[] = { "UNDONE", "DONE" };
static CORBA::TypeCode_ptr _0RL_tc_DAQDone = CORBA::TypeCode::PR_enum_tc("IDL:DAQDone:1.0", "DAQDone", _0RL_enumMember_DAQDone, 2, &_0RL_tcTrack);
const CORBA::TypeCode_ptr _tc_DAQDone = _0RL_tc_DAQDone;

static const char* _0RL_enumMember_CompStatus[] = { "COMP_WORKING", "COMP_FINISHED", "COMP_WARNING", "COMP_FATAL" };
static CORBA::TypeCode_ptr _0RL_tc_CompStatus = CORBA::TypeCode::PR_enum_tc("IDL:CompStatus:1.0", "CompStatus", _0RL_enumMember_CompStatus, 4, &_0RL_tcTrack);
const CORBA::TypeCode_ptr _tc_CompStatus = _0RL_tc_CompStatus;

static CORBA::PR_structMember _0RL_structmember_FatalErrorStatus[] = {
  {"fatalTypes", CORBA::TypeCode::PR_long_tc()},
  {"errorCode", CORBA::TypeCode::PR_long_tc()},
  {"description", CORBA::TypeCode::PR_string_tc(0, &_0RL_tcTrack)}
};

#ifdef _0RL_tc_FatalErrorStatus
#  undef _0RL_tc_FatalErrorStatus
#endif
static CORBA::TypeCode_ptr _0RL_tc_FatalErrorStatus = CORBA::TypeCode::PR_struct_tc("IDL:FatalErrorStatus:1.0", "FatalErrorStatus", _0RL_structmember_FatalErrorStatus, 3, &_0RL_tcTrack);

const CORBA::TypeCode_ptr _tc_FatalErrorStatus = _0RL_tc_FatalErrorStatus;


static CORBA::PR_structMember _0RL_structmember_Status[] = {
  {"comp_name", CORBA::TypeCode::PR_string_tc(0, &_0RL_tcTrack)},
  {"state", _0RL_tc_DAQLifeCycleState},
  {"event_size", CORBA::TypeCode::PR_ulonglong_tc()},
  {"comp_status", _0RL_tc_CompStatus}
};

#ifdef _0RL_tc_Status
#  undef _0RL_tc_Status
#endif
static CORBA::TypeCode_ptr _0RL_tc_Status = CORBA::TypeCode::PR_struct_tc("IDL:Status:1.0", "Status", _0RL_structmember_Status, 4, &_0RL_tcTrack);

const CORBA::TypeCode_ptr _tc_Status = _0RL_tc_Status;


const CORBA::TypeCode_ptr _tc_DAQService = CORBA::TypeCode::PR_interface_tc("IDL:DAQService:1.0", "DAQService", &_0RL_tcTrack);

static void _0RL_NameValue_marshal_fn(cdrStream& _s, void* _v)
{
  NameValue* _p = (NameValue*)_v;
  *_p >>= _s;
}
static void _0RL_NameValue_unmarshal_fn(cdrStream& _s, void*& _v)
{
  NameValue* _p = new NameValue;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_NameValue_destructor_fn(void* _v)
{
  NameValue* _p = (NameValue*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const NameValue& _s)
{
  NameValue* _p = new NameValue(_s);
  _a.PR_insert(_0RL_tc_NameValue,
               _0RL_NameValue_marshal_fn,
               _0RL_NameValue_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, NameValue* _sp)
{
  _a.PR_insert(_0RL_tc_NameValue,
               _0RL_NameValue_marshal_fn,
               _0RL_NameValue_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, NameValue*& _sp)
{
  return _a >>= (const NameValue*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const NameValue*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_NameValue,
                    _0RL_NameValue_unmarshal_fn,
                    _0RL_NameValue_marshal_fn,
                    _0RL_NameValue_destructor_fn,
                    _v)) {
    _sp = (const NameValue*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_NVList_marshal_fn(cdrStream& _s, void* _v)
{
  NVList* _p = (NVList*)_v;
  *_p >>= _s;
}
static void _0RL_NVList_unmarshal_fn(cdrStream& _s, void*& _v)
{
  NVList* _p = new NVList;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_NVList_destructor_fn(void* _v)
{
  NVList* _p = (NVList*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const NVList& _s)
{
  NVList* _p = new NVList(_s);
  _a.PR_insert(_0RL_tc_NVList,
               _0RL_NVList_marshal_fn,
               _0RL_NVList_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, NVList* _sp)
{
  _a.PR_insert(_0RL_tc_NVList,
               _0RL_NVList_marshal_fn,
               _0RL_NVList_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, NVList*& _sp)
{
  return _a >>= (const NVList*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const NVList*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_NVList,
                    _0RL_NVList_unmarshal_fn,
                    _0RL_NVList_marshal_fn,
                    _0RL_NVList_destructor_fn,
                    _v)) {
    _sp = (const NVList*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_DAQLifeCycleState_marshal_fn(cdrStream& _s, void* _v)
{
  DAQLifeCycleState* _p = (DAQLifeCycleState*)_v;
  *_p >>= _s;
}
static void _0RL_DAQLifeCycleState_unmarshal_fn(cdrStream& _s, void*& _v)
{
  DAQLifeCycleState* _p = (DAQLifeCycleState*)_v;
  *_p <<= _s;
}

void operator<<=(::CORBA::Any& _a, DAQLifeCycleState _s)
{
  _a.PR_insert(_0RL_tc_DAQLifeCycleState,
               _0RL_DAQLifeCycleState_marshal_fn,
               &_s);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, DAQLifeCycleState& _s)
{
  return _a.PR_extract(_0RL_tc_DAQLifeCycleState,
                       _0RL_DAQLifeCycleState_unmarshal_fn,
                       &_s);
}

static void _0RL_DAQCommand_marshal_fn(cdrStream& _s, void* _v)
{
  DAQCommand* _p = (DAQCommand*)_v;
  *_p >>= _s;
}
static void _0RL_DAQCommand_unmarshal_fn(cdrStream& _s, void*& _v)
{
  DAQCommand* _p = (DAQCommand*)_v;
  *_p <<= _s;
}

void operator<<=(::CORBA::Any& _a, DAQCommand _s)
{
  _a.PR_insert(_0RL_tc_DAQCommand,
               _0RL_DAQCommand_marshal_fn,
               &_s);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, DAQCommand& _s)
{
  return _a.PR_extract(_0RL_tc_DAQCommand,
                       _0RL_DAQCommand_unmarshal_fn,
                       &_s);
}

static void _0RL_DAQDone_marshal_fn(cdrStream& _s, void* _v)
{
  DAQDone* _p = (DAQDone*)_v;
  *_p >>= _s;
}
static void _0RL_DAQDone_unmarshal_fn(cdrStream& _s, void*& _v)
{
  DAQDone* _p = (DAQDone*)_v;
  *_p <<= _s;
}

void operator<<=(::CORBA::Any& _a, DAQDone _s)
{
  _a.PR_insert(_0RL_tc_DAQDone,
               _0RL_DAQDone_marshal_fn,
               &_s);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, DAQDone& _s)
{
  return _a.PR_extract(_0RL_tc_DAQDone,
                       _0RL_DAQDone_unmarshal_fn,
                       &_s);
}

static void _0RL_CompStatus_marshal_fn(cdrStream& _s, void* _v)
{
  CompStatus* _p = (CompStatus*)_v;
  *_p >>= _s;
}
static void _0RL_CompStatus_unmarshal_fn(cdrStream& _s, void*& _v)
{
  CompStatus* _p = (CompStatus*)_v;
  *_p <<= _s;
}

void operator<<=(::CORBA::Any& _a, CompStatus _s)
{
  _a.PR_insert(_0RL_tc_CompStatus,
               _0RL_CompStatus_marshal_fn,
               &_s);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, CompStatus& _s)
{
  return _a.PR_extract(_0RL_tc_CompStatus,
                       _0RL_CompStatus_unmarshal_fn,
                       &_s);
}

static void _0RL_FatalErrorStatus_marshal_fn(cdrStream& _s, void* _v)
{
  FatalErrorStatus* _p = (FatalErrorStatus*)_v;
  *_p >>= _s;
}
static void _0RL_FatalErrorStatus_unmarshal_fn(cdrStream& _s, void*& _v)
{
  FatalErrorStatus* _p = new FatalErrorStatus;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_FatalErrorStatus_destructor_fn(void* _v)
{
  FatalErrorStatus* _p = (FatalErrorStatus*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const FatalErrorStatus& _s)
{
  FatalErrorStatus* _p = new FatalErrorStatus(_s);
  _a.PR_insert(_0RL_tc_FatalErrorStatus,
               _0RL_FatalErrorStatus_marshal_fn,
               _0RL_FatalErrorStatus_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, FatalErrorStatus* _sp)
{
  _a.PR_insert(_0RL_tc_FatalErrorStatus,
               _0RL_FatalErrorStatus_marshal_fn,
               _0RL_FatalErrorStatus_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, FatalErrorStatus*& _sp)
{
  return _a >>= (const FatalErrorStatus*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const FatalErrorStatus*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_FatalErrorStatus,
                    _0RL_FatalErrorStatus_unmarshal_fn,
                    _0RL_FatalErrorStatus_marshal_fn,
                    _0RL_FatalErrorStatus_destructor_fn,
                    _v)) {
    _sp = (const FatalErrorStatus*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_Status_marshal_fn(cdrStream& _s, void* _v)
{
  Status* _p = (Status*)_v;
  *_p >>= _s;
}
static void _0RL_Status_unmarshal_fn(cdrStream& _s, void*& _v)
{
  Status* _p = new Status;
  *_p <<= _s;
  _v = _p;
}
static void _0RL_Status_destructor_fn(void* _v)
{
  Status* _p = (Status*)_v;
  delete _p;
}

void operator<<=(::CORBA::Any& _a, const Status& _s)
{
  Status* _p = new Status(_s);
  _a.PR_insert(_0RL_tc_Status,
               _0RL_Status_marshal_fn,
               _0RL_Status_destructor_fn,
               _p);
}
void operator<<=(::CORBA::Any& _a, Status* _sp)
{
  _a.PR_insert(_0RL_tc_Status,
               _0RL_Status_marshal_fn,
               _0RL_Status_destructor_fn,
               _sp);
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, Status*& _sp)
{
  return _a >>= (const Status*&) _sp;
}
::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, const Status*& _sp)
{
  void* _v;
  if (_a.PR_extract(_0RL_tc_Status,
                    _0RL_Status_unmarshal_fn,
                    _0RL_Status_marshal_fn,
                    _0RL_Status_destructor_fn,
                    _v)) {
    _sp = (const Status*)_v;
    return 1;
  }
  return 0;
}

static void _0RL_DAQService_marshal_fn(cdrStream& _s, void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  omniObjRef::_marshal(_o, _s);
}
static void _0RL_DAQService_unmarshal_fn(cdrStream& _s, void*& _v)
{
  omniObjRef* _o = omniObjRef::_unMarshal(DAQService::_PD_repoId, _s);
  _v = _o;
}
static void _0RL_DAQService_destructor_fn(void* _v)
{
  omniObjRef* _o = (omniObjRef*)_v;
  if (_o)
    omni::releaseObjRef(_o);
}

void operator<<=(::CORBA::Any& _a, DAQService_ptr _o)
{
  DAQService_ptr _no = DAQService::_duplicate(_o);
  _a.PR_insert(_tc_DAQService,
               _0RL_DAQService_marshal_fn,
               _0RL_DAQService_destructor_fn,
               _no->_PR_getobj());
}
void operator<<=(::CORBA::Any& _a, DAQService_ptr* _op)
{
  _a.PR_insert(_tc_DAQService,
               _0RL_DAQService_marshal_fn,
               _0RL_DAQService_destructor_fn,
               (*_op)->_PR_getobj());
  *_op = DAQService::_nil();
}

::CORBA::Boolean operator>>=(const ::CORBA::Any& _a, DAQService_ptr& _o)
{
  void* _v;
  if (_a.PR_extract(_tc_DAQService,
                    _0RL_DAQService_unmarshal_fn,
                    _0RL_DAQService_marshal_fn,
                    _0RL_DAQService_destructor_fn,
                    _v)) {
    omniObjRef* _r = (omniObjRef*)_v;
    if (_r)
      _o = (DAQService_ptr)_r->_ptrToObjRef(DAQService::_PD_repoId);
    else
      _o = DAQService::_nil();
    return 1;
  }
  return 0;
}

