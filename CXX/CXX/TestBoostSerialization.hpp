#pragma once


#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


class BoostSerializationDemoEquipBase
{
public:
	BoostSerializationDemoEquipBase(int id = 0, const std::wstring &str = L"")
		: m_ID(id), m_Name(str) {}
	virtual ~BoostSerializationDemoEquipBase()
	{
	}
	void SetID(int id)
	{
		m_ID = id;
	}
	void SetName(const std::wstring &str)
	{
		m_Name = str;
	}
	int GetID() const
	{
		return m_ID;
	}
	std::wstring GetName() const
	{
		return m_Name;
	}
private:
	int m_ID;
	std::wstring m_Name;

	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & m_ID;
		ar & m_Name;
	}
};

BOOST_CLASS_VERSION(BoostSerializationDemoEquipBase, 0)
//BOOST_SERIALIZATION_ASSUME_ABSTRACT(BoostSerializationDemoEquipBase);

class BoostSerializationDemoImport : public BoostSerializationDemoEquipBase
{
public:
	typedef std::vector<int> IDList;
	BoostSerializationDemoImport(int id = 0, const std::wstring &str = L"")
		: BoostSerializationDemoEquipBase(id, str) {}
	virtual ~BoostSerializationDemoImport()
	{
	}
	void PushStream(int id)
	{
		m_Streams.push_back(id);
	}
private:
	IDList m_Streams;

	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<BoostSerializationDemoEquipBase>(*this);
		ar & m_Streams;
	}
};

BOOST_CLASS_VERSION(BoostSerializationDemoImport, 0)
BOOST_CLASS_EXPORT_GUID(BoostSerializationDemoImport, "BoostSerializationDemoImport")

class BoostSerializationDemoDesign
{
public:
	typedef boost::shared_ptr<BoostSerializationDemoEquipBase> EquipPtr;
	typedef std::vector<EquipPtr> EquipList;
	BoostSerializationDemoDesign(const std::wstring &str = L"")
		: m_DesignName(str) {}
	~BoostSerializationDemoDesign() {}
	void SetDesignName(const std::wstring &str)
	{
		m_DesignName = str;
	}
	std::wstring GetDesignName() const
	{
		return m_DesignName;
	}
	void PushEquip(const EquipPtr &equip)
	{
		m_EquipList.push_back(equip);
	}
private:
	std::wstring m_DesignName;
	EquipList m_EquipList;

	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive &ar, const unsigned int version)
	{
		ar & m_DesignName;
		ar & m_EquipList;
	}
};

BOOST_CLASS_VERSION(BoostSerializationDemoDesign, 0)













































void TestBoostSerialization()
{
	BoostSerializationDemoImport *p1 = new BoostSerializationDemoImport(1, L"Equip 1");
	p1->PushStream(1001);
	p1->PushStream(1002);
	BoostSerializationDemoImport *p2 = new BoostSerializationDemoImport(2, L"Equip 2");
	p2->PushStream(2001);
	p2->PushStream(2002);
	BoostSerializationDemoDesign design(L"TestDesign");
	design.PushEquip(BoostSerializationDemoDesign::EquipPtr(p1));
	design.PushEquip(BoostSerializationDemoDesign::EquipPtr(p2));

	std::string fileName("data.txt");

	std::ofstream fout(fileName.c_str());
	boost::archive::text_oarchive oa(fout);
	oa << design;
	fout.close();

	std::ifstream fin(fileName.c_str());
	boost::archive::text_iarchive ia(fin);
	BoostSerializationDemoDesign design2(L"New  Design");
	ia >> design2;
	fin.close();
}