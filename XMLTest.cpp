#include <gtest/gtest.h>
#include "XMLWriter.h"
#include "StringDataSink.h"
#include "XMLReader.h"
#include "StringDataSource.h"

TEST(XMLReader, ReadEntity){
	// Test 1
	auto InputStream = std::make_shared<CStringDataSource>("<example attr=\"Hello World\"></example>");
	CXMLReader Reader(InputStream);
	SXMLEntity E;

	EXPECT_TRUE(Reader.ReadEntity(E));
	EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
	EXPECT_EQ(E.AttributeValue("attr"), "Hello World");

	EXPECT_TRUE(Reader.ReadEntity(E));
	EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);


	// Test 2
	auto InputStream1 = std::make_shared< CStringDataSource >("<jpop attr=\"Ado's 1st song\"></jpop>");
    CXMLReader Reader1(InputStream1);
    SXMLEntity E1;

	EXPECT_TRUE(Reader1.ReadEntity(E1));
    EXPECT_EQ(E1.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E1.AttributeValue("attr"), "Ado's 1st song");
    EXPECT_TRUE(Reader1.ReadEntity(E1));
    EXPECT_EQ(E1.DType, SXMLEntity::EType::EndElement);


	// Test 3 (multiple attributes)
	auto InputStream2 = std::make_shared< CStringDataSource >("<music track1=\"Mii-Channel-Music\" track2=\"Wii-Sports-Music\"></music>");
    CXMLReader Reader2(InputStream2);
    SXMLEntity E2;

    EXPECT_TRUE(Reader2.ReadEntity(E2));
    EXPECT_EQ(E2.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E2.AttributeValue("track1"), "Mii-Channel-Music");
	EXPECT_EQ(E2.AttributeValue("track2"), "Wii-Sports-Music");
    EXPECT_TRUE(Reader2.ReadEntity(E2));
    EXPECT_EQ(E2.DType, SXMLEntity::EType::EndElement);
	EXPECT_FALSE(Reader2.ReadEntity(E2));

	// Test 4 (character data)
	auto InputStream3 = std::make_shared< CStringDataSource >("<music>Mii Channel Music</music>");
    CXMLReader Reader3(InputStream3);
    SXMLEntity E3;

    EXPECT_TRUE(Reader3.ReadEntity(E3));
    EXPECT_EQ(E3.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E3.DNameData, "music");
	EXPECT_TRUE(Reader3.ReadEntity(E3));
	EXPECT_EQ(E3.DType, SXMLEntity::EType::CharData);
    EXPECT_EQ(E3.DNameData, "Mii Channel Music");

	// Test 5 (skipcdata)

    auto InputStream4 = std::make_shared< CStringDataSource >("<music>Mii Channel Music</music>");
    CXMLReader Reader4(InputStream4);
    SXMLEntity E4;

    EXPECT_TRUE(Reader4.ReadEntity(E4));
    EXPECT_EQ(E4.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E4.DNameData, "music");
	EXPECT_TRUE(Reader4.ReadEntity(E4, true));
	EXPECT_EQ(E4.DType, SXMLEntity::EType::EndElement);
}

TEST(XMLWriter, WriteEntity){
    // Test 1
	auto OutputStream = std::make_shared<CStringDataSink>();
	CXMLWriter Writer(OutputStream);

	Writer.WriteEntity({SXMLEntity::EType::StartElement, "example", {{"attr","Hello World"}, {"hi", "ok"}}});
	Writer.Flush();

	EXPECT_EQ(OutputStream->String(), "<example attr=\"Hello World\" hi=\"ok\"></example>");

	// Test 2 (multiple entities)
	auto OutputStream1 = std::make_shared<CStringDataSink>();
	CXMLWriter Writer1(OutputStream1);
	EXPECT_TRUE(Writer1.WriteEntity({SXMLEntity::EType::StartElement, "example", {{"attr","Hello World"}}}));
	EXPECT_TRUE(Writer1.WriteEntity({SXMLEntity::EType::StartElement, "example2", {{"attr","Hello World"}}}));
	EXPECT_TRUE(Writer1.WriteEntity({SXMLEntity::EType::StartElement, "example3", {{"attr'","Hello World"}, {"attr>", "&"}}}));
	EXPECT_TRUE(Writer1.WriteEntity({SXMLEntity::EType::CharData, "text&"}));
	EXPECT_TRUE(Writer1.WriteEntity({SXMLEntity::EType::EndElement, "example3"}));
	EXPECT_TRUE(Writer1.WriteEntity({SXMLEntity::EType::CompleteElement, "examplecomplete", {{"attr","Hello World"}}}));

	std::string ExpectedString = "<example attr=\"Hello World\"><example2 attr=\"Hello World\"><example3 attr&apos;=\"Hello World\" attr&gt;=\"&amp;\">text&amp;</example3><examplecomplete attr=\"Hello World\"/>";
	EXPECT_EQ(OutputStream1->String(), ExpectedString);

	// Flush to close example2 and example
	EXPECT_TRUE(Writer1.Flush());
	ExpectedString = "<example attr=\"Hello World\"><example2 attr=\"Hello World\"><example3 attr&apos;=\"Hello World\" attr&gt;=\"&amp;\">text&amp;</example3><examplecomplete attr=\"Hello World\"/></example2></example>";
	EXPECT_EQ(OutputStream1->String(), ExpectedString);
}

TEST(XMLReader, SimpleReadingTest){
	auto InputStream = std::make_shared<CStringDataSource>("<kpop attr=\"IU Songs Slaps!\"></kpop>");
    CXMLReader Reader(InputStream);
    SXMLEntity E;

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E.AttributeValue("attr"), "IU Songs Slaps!");

    EXPECT_TRUE(Reader.ReadEntity(E));
    EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);

    auto InputStream1 = std::make_shared< CStringDataSource >("<jpop attr=\"Ado's 1st song\"></jpop>");
    CXMLReader Reader1(InputStream1);
    SXMLEntity E1;

    EXPECT_TRUE(Reader1.ReadEntity(E1));
    EXPECT_EQ(E1.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E1.AttributeValue("attr"), "Ado's 1st song");
    EXPECT_TRUE(Reader1.ReadEntity(E1));
    EXPECT_EQ(E1.DType, SXMLEntity::EType::EndElement);

    auto InputStream2 = std::make_shared< CStringDataSource >("<music track1=\"Mii-Channel-Music\" track2=\"Wii-Channel-Music\"></music>");
    CXMLReader Reader2(InputStream2);
    SXMLEntity E2;

    EXPECT_TRUE(Reader2.ReadEntity(E2));
    EXPECT_EQ(E2.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(E2.AttributeValue("track1"), "Mii-Channel-Music");
    EXPECT_EQ(E2.AttributeValue("track2"), "Wii-Channel-Music");
    EXPECT_TRUE(Reader2.ReadEntity(E2));
    EXPECT_EQ(E2.DType, SXMLEntity::EType::EndElement);


    auto InputStream3 = std::make_shared< CStringDataSource > ("<note>Hello World</note>");
    CXMLReader Reader3(InputStream3);
    SXMLEntity E3;

    EXPECT_TRUE(Reader3.ReadEntity(E3));
    EXPECT_EQ(E3.DType, SXMLEntity::EType::StartElement);

    EXPECT_TRUE(Reader3.ReadEntity(E3));
    EXPECT_EQ(E3.DType, SXMLEntity::EType::CharData);

    EXPECT_TRUE(Reader3.ReadEntity(E3));
    EXPECT_EQ(E3.DType, SXMLEntity::EType::EndElement);
}

TEST(XMLWriter, SimpleWritingTest){
    
	auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "sanity", {{"attr","I'm losing it!"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "sanity", {}}));
    EXPECT_EQ(OutputStream->String(), "<sanity attr=\"I&apos;m losing it!\"></sanity>");

    auto OutputStream1 = std::make_shared<CStringDataSink>();
    CXMLWriter Writer1(OutputStream1);
    EXPECT_TRUE(Writer1.WriteEntity({SXMLEntity::EType::StartElement, "nums", {{"numbers","123456"}}}));
    EXPECT_TRUE(Writer1.WriteEntity({SXMLEntity::EType::EndElement, "nums", {}}));
    EXPECT_EQ(OutputStream1->String(), "<nums numbers=\"123456\"></nums>");
}

