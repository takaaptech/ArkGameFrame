// -------------------------------------------------------------------------
//    @FileName         :    NFIRecordManager.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-12-17
//    @Module           :    NFIRecordManager
//
// -------------------------------------------------------------------------

#ifndef NFI_RECORDMANAGER_H
#define NFI_RECORDMANAGER_H

#include "NFIRecord.h"
#include "NFMap.h"

class NFIRecordManager
    : public NFMapEx<std::string, NFIRecord>
{
public:
    virtual ~NFIRecordManager() {}

    virtual NF_SHARE_PTR<NFIRecord> AddRecord(const NFGUID& self, const std::string& strRecordName, const NF_SHARE_PTR<NFIDataList>& TData, const NF_SHARE_PTR<NFIDataList>& tagData, const int nRows) = 0;
    virtual const NFGUID& Self() = 0;
    //////////////////////////////////////////////////////////////////////////

    virtual bool SetRecordInt(const std::string& strRecordName, const int nRow, const int nCol, const NFINT64 nValue) = 0;
    virtual bool SetRecordFloat(const std::string& strRecordName, const int nRow, const int nCol, const double dwValue) = 0;
    virtual bool SetRecordString(const std::string& strRecordName, const int nRow, const int nCol, const std::string& strValue) = 0;
    virtual bool SetRecordObject(const std::string& strRecordName, const int nRow, const int nCol, const NFGUID& obj) = 0;
    virtual bool SetRecordPoint(const std::string& strRecordName, const int nRow, const int nCol, const Point3D& value) = 0;

    virtual bool SetRecordInt(const std::string& strRecordName, const int nRow, const std::string& strColTag, const NFINT64 value) = 0;
    virtual bool SetRecordFloat(const std::string& strRecordName, const int nRow, const std::string& strColTag, const double value) = 0;
    virtual bool SetRecordString(const std::string& strRecordName, const int nRow, const std::string& strColTag, const std::string& value) = 0;
    virtual bool SetRecordObject(const std::string& strRecordName, const int nRow, const std::string& strColTag, const NFGUID& value) = 0;
    virtual bool SetRecordPoint(const std::string& strRecordName, const int nRow, const std::string& strColTag, const Point3D& value) = 0;

    virtual NFINT64 GetRecordInt(const std::string& strRecordName, const int nRow, const int nCol) = 0;
    virtual double GetRecordFloat(const std::string& strRecordName, const int nRow, const int nCol) = 0;
    virtual const std::string& GetRecordString(const std::string& strRecordName, const int nRow, const int nCol) = 0;
    virtual const NFGUID& GetRecordObject(const std::string& strRecordName, const int nRow, const int nCol) = 0;
    virtual const Point3D& GetRecordPoint(const std::string& strRecordName, const int nRow, const int nCol) = 0;

    virtual NFINT64 GetRecordInt(const std::string& strRecordName, const int nRow, const std::string& strColTag) = 0;
    virtual double GetRecordFloat(const std::string& strRecordName, const int nRow, const std::string& strColTag) = 0;
    virtual const std::string& GetRecordString(const std::string& strRecordName, const int nRow, const std::string& strColTag) = 0;
    virtual const NFGUID& GetRecordObject(const std::string& strRecordName, const int nRow, const std::string& strColTag) = 0;
    virtual const Point3D& GetRecordPoint(const std::string& strRecordName, const int nRow, const std::string& strColTag) = 0;
    //////////////////////////////////////////////////////////////////////////
};


#endif
