// -------------------------------------------------------------------------
//    @FileName         :    NFCProperty.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-03-01
//    @Module           :    NFCProperty
//
// -------------------------------------------------------------------------

#ifndef NFC_PROPERTY_H
#define NFC_PROPERTY_H

#include "NFDefine.h"
#include "NFMap.h"
#include "NFList.h"
#include "NFCDataList.h"
#include "NFIProperty.h"

class NFCProperty : public NFIProperty
{
private:
    NFCProperty();

public:
    NFCProperty(const NFGUID& self, const std::string& strPropertyName, const TDATA_TYPE varType);

    virtual ~NFCProperty();

    virtual void SetValue(const NFIDataList::TData& TData);
    virtual void SetValue(const NFIProperty* pProperty);

    virtual bool SetInt(const NFINT64 value);
    virtual bool SetDouble(const double value);
    virtual bool SetString(const std::string& value);
    virtual bool SetObject(const NFGUID& value);
    virtual bool SetPoint(const Point3D& value);

    virtual NFINT64 GetInt() const;
    virtual double GetDouble() const;
    virtual const std::string& GetString() const;
    virtual const NFGUID& GetObject() const;
    virtual const Point3D& GetPoint() const;

    virtual const TDATA_TYPE GetType() const;
    virtual const bool GeUsed() const;
    virtual const std::string& GetKey() const;
    virtual const bool GetSave() const;
    virtual const bool GetPublic() const;
    virtual const bool GetPrivate() const;
    virtual const bool GetCache() const;
    virtual const std::string& GetRelationValue() const;

    virtual void SetSave(bool bSave);
    virtual void SetPublic(bool bPublic);
    virtual void SetPrivate(bool bPrivate);
    virtual void SetCache(bool bCache);
    virtual void SetRelationValue(const std::string& strRelation);

    virtual const NFIDataList::TData& GetValue() const;
    virtual const NF_SHARE_PTR<NFList<std::string>> GetEmbeddedList() const;
    virtual const NF_SHARE_PTR<NFMapEx<std::string, std::string>> GetEmbeddedMap() const;

    virtual bool Changed() const;

    virtual std::string ToString();
    virtual bool FromString(const std::string& strData);
    virtual bool DeSerialization();

    virtual void RegisterCallback(const PROPERTY_EVENT_FUNCTOR_PTR& cb);

private:
    int OnEventHandler(const NFIDataList::TData& oldVar, const NFIDataList::TData& newVar);

private:
    typedef std::vector<PROPERTY_EVENT_FUNCTOR_PTR> TPROPERTYCALLBACKEX;
    TPROPERTYCALLBACKEX mtPropertyCallback;

    NFGUID mSelf;
    std::string msPropertyName;//������취��������͹���
    std::string mstrRelationValue;
    TDATA_TYPE eType;//ֻ���ڲ�����ָ���ʱ���������ж�����--Ϊ��Լ�ڴ�

    NF_SHARE_PTR<NFIDataList::TData> mxData;
    NF_SHARE_PTR<NFMapEx<std::string, std::string>> mxEmbeddedMap;
    NF_SHARE_PTR<NFList<std::string>> mxEmbeddedList;

    bool mbPublic;
    bool mbPrivate;
    bool mbSave;
    bool mbCache;
};

#endif
