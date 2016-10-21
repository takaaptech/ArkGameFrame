// -------------------------------------------------------------------------
//    @FileName         :    NFCDataList.h
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-03-01
//    @Module           :    NFCDataList
//
// -------------------------------------------------------------------------

#ifndef NFC_DATALIST_H
#define NFC_DATALIST_H

#include "NFIDataList.h"
#include "NFComm/NFPluginModule/NFGUID.h"

class NFCDataList: public NFIDataList
{
public:
    NFCDataList();

    NFCDataList(const std::string& str, const std::string& strSplit);

    NFCDataList(const NFCDataList& src);
    NFCDataList(const NFIDataList& src);

    virtual ~NFCDataList();

    // ���
    virtual bool Append(const NFIDataList& src);
    virtual bool Append(const NFIDataList& src, const int start, const int count);

    // ���
    virtual bool Append(const NFIDataList::TData& TData);

    // ���
    virtual void Clear();

    // �Ƿ�Ϊ��
    virtual bool IsEmpty() const;

    // ��������
    virtual int GetCount() const;

    // �ϲ�
    virtual bool Concat(const NFIDataList& src);

    //////////////////////////////////////////////////////////////////////////
    const NF_SHARE_PTR<NFIDataList::TData> GetStack(const int index) const;

    // ��������
    virtual TDATA_TYPE Type(const int index) const;
    int TypeInt(const int index) const;
    //�������ͼ��
    virtual bool TypeEx(const  int nType, ...) const;

    virtual bool Split(const std::string& strData, const std::string& strSplit);

    virtual bool Add(const NFINT64 value);
    virtual bool Add(const double value);
    virtual bool Add(const std::string& value);
    virtual bool Add(const NFGUID& value);
    virtual bool Add(const Point3D& value);

    virtual bool Set(const int index, const NFINT64 value);
    virtual bool Set(const int index, const double value);
    virtual bool Set(const int index, const std::string& value);
    virtual bool Set(const int index, const NFGUID& value);
    virtual bool Set(const int index, const Point3D& value);

    // �������
    virtual NFINT64 Int(const int index) const;
    virtual double Double(const int index) const;
    virtual std::string StringValEx(const int index) const;
    virtual const std::string& String(const int index) const;
    virtual const NFGUID& Object(const int index) const;
    virtual const Point3D& Point(const int index) const;

    virtual bool ToString(std::string& str, const std::string& strSplit) const;

protected:
    void AddStatck();
    void InnerAppendEx(const NFIDataList& src, const int start, const int end);
    bool ValidIndex(int index) const;
};

#endif