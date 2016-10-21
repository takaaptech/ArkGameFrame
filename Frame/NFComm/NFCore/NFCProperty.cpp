// -------------------------------------------------------------------------
//    @FileName         :    NFCProperty.cpp
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-03-01
//    @Module           :    NFCProperty
//
// -------------------------------------------------------------------------

#include "NFCProperty.h"
#include <complex>

NFCProperty::NFCProperty()
{
    mbPublic = false;
    mbPrivate = false;
    mbSave = false;
    mbCache = false;

    mSelf = NULL_GUID;
    eType = TDATA_UNKNOWN;

    msPropertyName = "";
}

NFCProperty::NFCProperty(const NFGUID& self, const std::string& strPropertyName, const TDATA_TYPE varType)
{
    mbPublic = false;
    mbPrivate = false;
    mbSave = false;
    mbCache = false;

    mstrRelationValue = "";

    mSelf = self;

    msPropertyName = strPropertyName;
    eType = varType;
}

NFCProperty::~NFCProperty()
{
    for(TPROPERTYCALLBACKEX::iterator iter = mtPropertyCallback.begin(); iter != mtPropertyCallback.end(); ++iter)
    {
        iter->reset();
    }

    mtPropertyCallback.clear();
    mxData.reset();
}

void NFCProperty::SetValue(const NFIDataList::TData& xData)
{
    if(eType != xData.GetType())
    {
        return;
    }

    if(xData.IsNullValue())
    {
        return;
    }

    if(nullptr == mxData)
    {
        mxData = NF_SHARE_PTR<NFIDataList::TData>(NF_NEW NFIDataList::TData(xData));
    }

    NFCDataList::TData oldValue;
    oldValue = *mxData;

    mxData->variantData = xData.variantData;

    NFCDataList::TData newValue;
    newValue = *mxData;

    OnEventHandler(oldValue, newValue);
}

void NFCProperty::SetValue(const NFIProperty* pProperty)
{
    SetValue(pProperty->GetValue());
}

const NFIDataList::TData& NFCProperty::GetValue() const
{
    if(nullptr != mxData)
    {
        return *mxData;
    }

    return NULL_TDATA;
}

const std::string&  NFCProperty::GetKey() const
{
    return msPropertyName;
}

const bool NFCProperty::GetSave() const
{
    return mbSave;
}

const bool NFCProperty::GetPublic() const
{
    return mbPublic;
}

const bool NFCProperty::GetPrivate() const
{
    return mbPrivate;
}

const bool NFCProperty::GetCache() const
{
    return mbCache;
}

const std::string& NFCProperty::GetRelationValue() const
{
    return mstrRelationValue;
}

void NFCProperty::SetSave(bool bSave)
{
    mbSave = bSave;
}

void NFCProperty::SetPublic(bool bPublic)
{
    mbPublic = bPublic;
}

void NFCProperty::SetPrivate(bool bPrivate)
{
    mbPrivate = bPrivate;
}

void NFCProperty::SetCache(bool bCache)
{
    mbCache = bCache;
}

void NFCProperty::SetRelationValue(const std::string& strRelationValue)
{
    mstrRelationValue = strRelationValue;
}

NFINT64 NFCProperty::GetInt() const
{
    if(nullptr == mxData)
    {
        return 0;
    }

    return mxData->GetInt();
}

double NFCProperty::GetDouble() const
{
    if(nullptr == mxData)
    {
        return 0.0;
    }

    return mxData->GetDouble();
}

const std::string& NFCProperty::GetString() const
{
    if(nullptr == mxData)
    {
        return NULL_STR;
    }

    return mxData->GetString();
}

const NFGUID& NFCProperty::GetObject() const
{
    if(nullptr == mxData)
    {
        return NULL_GUID;
    }

    return mxData->GetObject();
}

const Point3D& NFCProperty::GetPoint() const
{
    if(nullptr == mxData)
    {
        return NULL_POINT;
    }

    return mxData->GetPoint();
}

void NFCProperty::RegisterCallback(const PROPERTY_EVENT_FUNCTOR_PTR& cb)
{
    mtPropertyCallback.push_back(cb);
}

int NFCProperty::OnEventHandler(const NFIDataList::TData& oldVar, const NFIDataList::TData& newVar)
{
    if(mtPropertyCallback.size() <= 0)
    {
        return 0;
    }

    TPROPERTYCALLBACKEX::iterator it = mtPropertyCallback.begin();
    TPROPERTYCALLBACKEX::iterator end = mtPropertyCallback.end();
    for(it; it != end; ++it)
    {
        //NFIDataList����:��������OLD����ֵ��NEW����ֵ, ARG����(pKernel,self)
        (**it)(mSelf, msPropertyName, oldVar, newVar);
    }

    return 0;
}

bool NFCProperty::SetInt(const NFINT64 value)
{
    if(eType != TDATA_INT)
    {
        return false;
    }

    if(nullptr == mxData)
    {
        //�����ǿվ�����Ϊû���ݣ�������û���ݵľͲ�����
        if(0 == value)
        {
            return false;
        }

        mxData = NF_SHARE_PTR<NFIDataList::TData>(NF_NEW NFIDataList::TData(TDATA_INT));
        mxData->SetInt(0);
    }

    if(value == mxData->GetInt())
    {
        return false;
    }

    NFCDataList::TData oldValue;
    oldValue = *mxData;

    mxData->SetInt(value);

    OnEventHandler(oldValue, *mxData);

    return true;
}

bool NFCProperty::SetDouble(const double value)
{
    if(eType != TDATA_DOUBLE)
    {
        return false;
    }

    if(nullptr == mxData)
    {
        //�����ǿվ�����Ϊû���ݣ�������û���ݵľͲ�����
        if(IsZeroDouble(value))
        {
            return false;
        }

        mxData = NF_SHARE_PTR<NFIDataList::TData>(NF_NEW NFIDataList::TData(TDATA_DOUBLE));
        mxData->SetDouble(NULL_DOUBLE);
    }

    if(IsZeroDouble(value - mxData->GetDouble()))
    {
        return false;
    }

    NFCDataList::TData oldValue;
    oldValue = *mxData;

    mxData->SetDouble(value);

    OnEventHandler(oldValue, *mxData);

    return true;
}

bool NFCProperty::SetString(const std::string& value)
{
    if(eType != TDATA_STRING)
    {
        return false;
    }

    if(nullptr == mxData)
    {
        //�����ǿվ�����Ϊû���ݣ�������û���ݵľͲ�����
        if(value.empty())
        {
            return false;
        }

        mxData = NF_SHARE_PTR<NFIDataList::TData>(NF_NEW NFIDataList::TData(TDATA_STRING));
        mxData->SetString(NULL_STR);
    }

    if(value == mxData->GetString())
    {
        return false;
    }

    NFCDataList::TData oldValue;
    oldValue = *mxData;

    mxData->SetString(value);

    OnEventHandler(oldValue, *mxData);

    return true;
}

bool NFCProperty::SetObject(const NFGUID& value)
{
    if(eType != TDATA_OBJECT)
    {
        return false;
    }

    if(nullptr == mxData)
    {
        //�����ǿվ�����Ϊû���ݣ�������û���ݵľͲ�����
        if(value.IsNull())
        {
            return false;
        }

        mxData = NF_SHARE_PTR<NFIDataList::TData>(NF_NEW NFIDataList::TData(TDATA_OBJECT));
        mxData->SetObject(NULL_GUID);
    }

    if(value == mxData->GetObject())
    {
        return false;
    }

    NFCDataList::TData oldValue;
    oldValue = *mxData;

    mxData->SetObject(value);

    OnEventHandler(oldValue, *mxData);

    return true;
}

bool NFCProperty::SetPoint(const Point3D& value)
{
    if(eType != TDATA_POINT)
    {
        return false;
    }

    if(nullptr == mxData)
    {
        //�����ǿվ�����Ϊû���ݣ�������û���ݵľͲ�����
        if(value.IsNull())
        {
            return false;
        }

        mxData = NF_SHARE_PTR<NFIDataList::TData>(NF_NEW NFIDataList::TData(TDATA_POINT));
        mxData->SetPoint(NULL_POINT);
    }

    if(value == mxData->GetPoint())
    {
        return false;
    }

    NFCDataList::TData oldValue;
    oldValue = *mxData;

    mxData->SetPoint(value);

    OnEventHandler(oldValue, *mxData);

    return true;
}

bool NFCProperty::Changed() const
{
    return !(GetValue().IsNullValue());
}

const TDATA_TYPE NFCProperty::GetType() const
{
    return eType;
}

const bool NFCProperty::GeUsed() const
{
    if(nullptr == mxData)
    {
        return true;
    }

    return false;
}

std::string NFCProperty::ToString()
{
    std::string strData;
    const TDATA_TYPE eType = GetType();
    switch(eType)
    {
    case TDATA_INT:
        strData = lexical_cast<std::string> (GetInt());
        break;
    case TDATA_DOUBLE:
        strData = lexical_cast<std::string> (GetDouble());
        break;
    case TDATA_STRING:
        strData = GetString();
        break;
    case TDATA_OBJECT:
        strData = GetObject().ToString();
        break;
    case TDATA_POINT:
        strData = GetPoint().ToString();
        break;
    default:
        strData = NULL_STR;
        break;
    }

    return strData;
}

bool NFCProperty::FromString(const std::string& strData)
{
    const TDATA_TYPE eType = GetType();
    bool bRet = false;
    switch(eType)
    {
    case TDATA_INT:
        {
            NFINT64  nValue = 0;
            bRet = NF_StrTo(strData, nValue);
            SetInt(nValue);
        }
        break;

    case TDATA_DOUBLE:
        {
            double  dValue = 0;
            bRet = NF_StrTo(strData, dValue);
            SetDouble(dValue);
        }
        break;

    case TDATA_STRING:
        {
            SetString(strData);
            bRet = true;
        }
        break;
    case TDATA_OBJECT:
        {
            NFGUID xID;

            bRet = xID.FromString(strData);
            SetObject(xID);
        }
        break;
    case TDATA_POINT:
        {
            Point3D xPoint;
            bRet = xPoint.FromString(strData);
            SetPoint(xPoint);
        }
        break;
    default:
        break;
    }

    return bRet;
}

bool NFCProperty::DeSerialization()
{
    bool bRet = false;

    const TDATA_TYPE eType = GetType();
    if(eType == TDATA_STRING && nullptr != mxData && !mxData->IsNullValue())
    {
        NFCDataList xDataList;
        const std::string& strData = mxData->GetString();

        xDataList.Split(strData.c_str(), ";");
        if(xDataList.GetCount() <= 0)
        {
            return bRet;
        }

        NFCDataList xTemDataList;
        xTemDataList.Split(xDataList.String(0).c_str(), ",");
        const int nSubDataLength = xTemDataList.GetCount();

        if(xDataList.GetCount() == 1 && nSubDataLength == 1)
        {
            //most of property value only one value
            return bRet;
        }

        if(nullptr == mxEmbeddedList)
        {
            mxEmbeddedList = NF_SHARE_PTR<NFList<std::string>>(NF_NEW NFList<std::string>());
        }
        else
        {
            mxEmbeddedList->ClearAll();
        }

        for(int i = 0; i < xDataList.GetCount(); ++i)
        {
            if(xDataList.String(i).empty())
            {
                NFASSERT(0, strData, __FILE__, __FUNCTION__);
            }

            mxEmbeddedList->Add(xDataList.String(i));
        }



        ////////////////////////////////////////

        if(nSubDataLength < 2 || nSubDataLength > 2)
        {
            return bRet;
        }

        if(nullptr == mxEmbeddedMap)
        {
            mxEmbeddedMap = NF_SHARE_PTR<NFMapEx<std::string, std::string>>(NF_NEW NFMapEx<std::string, std::string>());
        }
        else
        {
            mxEmbeddedMap->ClearAll();
        }

        for(int i = 0; i < xDataList.GetCount(); ++i)
        {
            NFCDataList xTemDataList;
            const std::string& strTemData = xDataList.String(i);
            xTemDataList.Split(strTemData.c_str(), ",");
            {
                if(xTemDataList.GetCount() != nSubDataLength)
                {
                    NFASSERT(0, strTemData, __FILE__, __FUNCTION__);
                }

                const std::string& strKey = xTemDataList.String(0);
                const std::string& strValue = xTemDataList.String(1);

                if(strKey.empty() || strValue.empty())
                {
                    NFASSERT(0, strTemData, __FILE__, __FUNCTION__);
                }

                mxEmbeddedMap->AddElement(strKey, NF_SHARE_PTR<std::string>(NF_NEW std::string(strValue)));
            }
        }

        bRet = true;
    }

    return bRet;
}

const NF_SHARE_PTR<NFList<std::string>> NFCProperty::GetEmbeddedList() const
{
    return this->mxEmbeddedList;
}

const NF_SHARE_PTR<NFMapEx<std::string, std::string>> NFCProperty::GetEmbeddedMap() const
{
    return this->mxEmbeddedMap;
}
