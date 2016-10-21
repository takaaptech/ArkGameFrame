// -------------------------------------------------------------------------
//    @FileName         :    NFIKernelModule.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-12-15
//    @Module           :    NFIKernelModule
//
// -------------------------------------------------------------------------

#ifndef NFI_KERNEL_MODULE_H
#define NFI_KERNEL_MODULE_H

#include <iostream>
#include <string>
#include <functional>
#include "NFIModule.h"
#include "NFComm/NFCore/NFIObject.h"
#include "NFComm/NFPluginModule/NFGUID.h"

class NFIKernelModule
    : public NFIModule
{

public:

    template<typename BaseType>
    bool AddHeartBeat(const NFGUID self, const std::string& strHeartBeatName, BaseType* pBase, int (BaseType::*handler)(const NFGUID&, const std::string&, const float, const int), const float fTime, const int nCount)
    {
        NF_SHARE_PTR<NFIObject> pObject = GetObject(self);
        if(pObject.get())
        {
            return pObject->AddHeartBeat(strHeartBeatName, pBase, handler, fTime, nCount);
        }

        return false;
    }

    virtual bool FindHeartBeat(const NFGUID& self, const std::string& strHeartBeatName) = 0;

    virtual bool RemoveHeartBeat(const NFGUID& self, const std::string& strHeartBeatName) = 0;

    template<typename BaseType>
    bool AddRecordCallBack(const NFGUID& self, const std::string& strRecordName, BaseType* pBase, int (BaseType::*handler)(const NFGUID&, const RECORD_EVENT_DATA&, const NFIDataList::TData&, const NFIDataList::TData&))
    {
        NF_SHARE_PTR<NFIObject> pObject = GetObject(self);
        if(pObject.get())
        {
            return pObject->AddRecordCallBack(strRecordName, pBase, handler);
        }

        return false;
    }

    template<typename BaseType>
    bool AddPropertyCallBack(const NFGUID& self, const std::string& strPropertyName, BaseType* pBase, int (BaseType::*handler)(const NFGUID&, const std::string&, const NFIDataList::TData&, const NFIDataList::TData&))
    {
        NF_SHARE_PTR<NFIObject> pObject = GetObject(self);
        if(pObject.get())
        {
            return pObject->AddPropertyCallBack(strPropertyName, pBase, handler);
        }

        return false;
    }

    ////////////////event//////////////////////////////////////////////////////////
    template<typename BaseType>
    bool AddEventCallBack(const NFGUID& self, const int nEventID, BaseType* pBase, int (BaseType::*handler)(const NFGUID&, const int, const NFIDataList&))
    {
        EVENT_PROCESS_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        EVENT_PROCESS_FUNCTOR_PTR functorPtr(new EVENT_PROCESS_FUNCTOR(functor));
        return AddEventCallBack(self, nEventID, functorPtr);
    }

    template<typename BaseType>
    bool AddClassCallBack(const std::string& strClassName, BaseType* pBase, int (BaseType::*handler)(const NFGUID&, const std::string&, const CLASS_OBJECT_EVENT, const NFIDataList&))
    {
        CLASS_EVENT_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        CLASS_EVENT_FUNCTOR_PTR functorPtr(new CLASS_EVENT_FUNCTOR(functor));
        return AddClassCallBack(strClassName, functorPtr);
    }

    virtual bool DoEvent(const NFGUID& self, const std::string& strClassName, CLASS_OBJECT_EVENT eEvent, const NFIDataList& valueList) = 0;
    virtual bool DoEvent(const NFGUID& self, const int nEventID, const NFIDataList& valueList) = 0;

    //////////////////////////////////////////////////////////////////////////
    //ֻ������ģ��ע�ᣬ�ص�����ͬ���������¼�,���е�����󶼻�ص�
    template<typename BaseType>
    bool RegisterCommonClassEvent(BaseType* pBase, int (BaseType::*handler)(const NFGUID&, const std::string&, const CLASS_OBJECT_EVENT, const NFIDataList&))
    {
        CLASS_EVENT_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        CLASS_EVENT_FUNCTOR_PTR functorPtr(new CLASS_EVENT_FUNCTOR(functor));
        return RegisterCommonClassEvent(functorPtr);
    }

    //ֻ������ģ��ע�ᣬ�ص�����ͬ�����������¼�,���е������Զ���ص�
    template<typename BaseType>
    bool RegisterCommonPropertyEvent(BaseType* pBase, int (BaseType::*handler)(const NFGUID&, const std::string&, const NFIDataList::TData&, const NFIDataList::TData&))
    {
        PROPERTY_EVENT_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        PROPERTY_EVENT_FUNCTOR_PTR functorPtr(new PROPERTY_EVENT_FUNCTOR(functor));
        return RegisterCommonPropertyEvent(functorPtr);
    }

    //ֻ������ģ��ע�ᣬ�ص�����ͬ����������¼�,���е������ص�
    template<typename BaseType>
    bool RegisterCommonRecordEvent(BaseType* pBase, int (BaseType::*handler)(const NFGUID&, const RECORD_EVENT_DATA&, const NFIDataList::TData&, const NFIDataList::TData&))
    {
        RECORD_EVENT_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
        RECORD_EVENT_FUNCTOR_PTR functorPtr(new RECORD_EVENT_FUNCTOR(functor));
        return RegisterCommonRecordEvent(functorPtr);
    }
    /////////////////////////////////////////////////////////////////
    virtual bool IsContainer(const NFGUID& self) = 0;
    virtual bool ExistContainer(const int nContainerIndex) = 0;

    virtual NF_SHARE_PTR<NFIObject> GetObject(const NFGUID& ident) = 0;
    virtual NF_SHARE_PTR<NFIObject> CreateObject(const NFGUID& self, const int nSceneID, const int nGroupID, const std::string& strClassName, const std::string& strConfigIndex, const NFIDataList& arg) = 0;

    virtual bool DestroyObject(const NFGUID& self) = 0;
    virtual bool DestroyAll() = 0;
    //////////////////////////////////////////////////////////////////////////
    virtual bool FindProperty(const NFGUID& self, const std::string& strPropertyName) = 0;

    virtual bool SetPropertyInt(const NFGUID& self, const std::string& strPropertyName, const NFINT64 value) = 0;
    virtual bool SetPropertyDouble(const NFGUID& self, const std::string& strPropertyName, const double value) = 0;
    virtual bool SetPropertyString(const NFGUID& self, const std::string& strPropertyName, const std::string& value) = 0;
    virtual bool SetPropertyObject(const NFGUID& self, const std::string& strPropertyName, const NFGUID& value) = 0;
    virtual bool SetPropertyPoint(const NFGUID& self, const std::string& strPropertyName, const Point3D& value) = 0;

    virtual NFINT64 GetPropertyInt(const NFGUID& self, const std::string& strPropertyName) = 0;
    virtual double GetPropertyDouble(const NFGUID& self, const std::string& strPropertyName) = 0;
    virtual const std::string& GetPropertyString(const NFGUID& self, const std::string& strPropertyName) = 0;
    virtual const NFGUID& GetPropertyObject(const NFGUID& self, const std::string& strPropertyName) = 0;
    virtual const Point3D& GetPropertyPoint(const NFGUID& self, const std::string& strPropertyName) = 0;
    //////////////////////////////////////////////////////////////////////////
    virtual NF_SHARE_PTR<NFIRecord> FindRecord(const NFGUID& self, const std::string& strRecordName) = 0;
    virtual bool ClearRecord(const NFGUID& self, const std::string& strRecordName) = 0;

    virtual bool SetRecordInt(const NFGUID& self, const std::string& strRecordName, const int nRow, const int nCol, const NFINT64 value) = 0;
    virtual bool SetRecordDouble(const NFGUID& self, const std::string& strRecordName, const int nRow, const int nCol, const double value) = 0;
    virtual bool SetRecordString(const NFGUID& self, const std::string& strRecordName, const int nRow, const int nCol, const std::string& value) = 0;
    virtual bool SetRecordObject(const NFGUID& self, const std::string& strRecordName, const int nRow, const int nCol, const NFGUID& value) = 0;
    virtual bool SetRecordPoint(const NFGUID& self, const std::string& strRecordName, const int nRow, const int nCol, const Point3D& value) = 0;

    virtual bool SetRecordInt(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag, const NFINT64 value) = 0;
    virtual bool SetRecordDouble(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag, const double value) = 0;
    virtual bool SetRecordString(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag, const std::string& value) = 0;
    virtual bool SetRecordObject(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag, const NFGUID& value) = 0;
    virtual bool SetRecordPoint(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag, const Point3D& value) = 0;

    virtual NFINT64 GetRecordInt(const NFGUID& self, const std::string& strRecordName, const int nRow, const int nCol) = 0;
    virtual double GetRecordDouble(const NFGUID& self, const std::string& strRecordName, const int nRow, const int nCol) = 0;
    virtual const std::string& GetRecordString(const NFGUID& self, const std::string& strRecordName, const int nRow, const int nCol) = 0;
    virtual const NFGUID& GetRecordObject(const NFGUID& self, const std::string& strRecordName, const int nRow, const int nCol) = 0;
    virtual const Point3D& GetRecordPoint(const NFGUID& self, const std::string& strRecordName, const int nRow, const int nCol) = 0;

    virtual NFINT64 GetRecordInt(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag) = 0;
    virtual double GetRecordDouble(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag) = 0;
    virtual const std::string& GetRecordString(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag) = 0;
    virtual const NFGUID& GetRecordObject(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag) = 0;
    virtual const Point3D& GetRecordPoint(const NFGUID& self, const std::string& strRecordName, const int nRow, const std::string& strColTag) = 0;
    ////////////////////////////////////////////////////////////////
    virtual bool SwitchScene(const NFGUID& self, const int nTargetSceneID, const int nTargetGroupID, const float fX, const float fY, const float fZ, const float fOrient, const NFIDataList& arg) = 0;

    virtual bool CreateScene(const int nSceneID) = 0;
    virtual bool DestroyScene(const int nSceneID) = 0;

    virtual int GetOnLineCount() = 0;
    virtual int GetMaxOnLineCount() = 0;
    virtual int GetSceneOnLineCount(const int nSceneID) = 0;
    virtual int GetSceneOnLineCount(const int nSceneID, const int nGroupID) = 0;
    virtual int GetSceneOnLineList(const int nSceneID, NFIDataList& var) = 0;

    virtual int RequestGroupScene(const int nSceneID) = 0;
    virtual bool ReleaseGroupScene(const int nSceneID, const int nGroupID) = 0;
    virtual bool ExitGroupScene(const int nSceneID, const int nGroupID) = 0;

    virtual bool GetGroupObjectList(const int nSceneID, const int nGroupID, NFIDataList& list) = 0;
    virtual int GetObjectByProperty(const int nSceneID, const std::string& strPropertyName, const NFIDataList& valueArg, NFIDataList& list) = 0;

    virtual void Random(int nStart, int nEnd, int nCount, NFIDataList& valueList) = 0;
    virtual bool LogInfo(const NFGUID ident) = 0;

protected:
    virtual bool AddEventCallBack(const NFGUID& self, const int nEventID, const EVENT_PROCESS_FUNCTOR_PTR& cb) = 0;
    virtual bool AddClassCallBack(const std::string& strClassName, const CLASS_EVENT_FUNCTOR_PTR& cb) = 0;


protected:

    //ֻ������ģ��ע�ᣬ�ص�����ͬ���������¼�,���е�����󶼻�ص�
    virtual bool RegisterCommonClassEvent(const CLASS_EVENT_FUNCTOR_PTR& cb) = 0;

    //ֻ������ģ��ע�ᣬ�ص�����ͬ�����������¼�,���е������Զ���ص�
    virtual bool RegisterCommonPropertyEvent(const PROPERTY_EVENT_FUNCTOR_PTR& cb) = 0;

    //ֻ������ģ��ע�ᣬ�ص�����ͬ����������¼�,���е������ص�
    virtual bool RegisterCommonRecordEvent(const RECORD_EVENT_FUNCTOR_PTR& cb) = 0;
};

#endif
