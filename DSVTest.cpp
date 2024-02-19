#include <gtest/gtest.h>
#include "DSVWriter.h"
#include "StringDataSink.h"
#include "DSVReader.h"
#include "StringDataSource.h"

TEST(DSVWriter, WriteRow) {
	    std::vector <std::string> read;

	auto TestDataSink = std::make_shared<CStringDataSink>();
	CDSVWriter Writer(TestDataSink, ',');
	read = {"", "a", "", ""};
	EXPECT_EQ(Writer.WriteRow(read), true);
	EXPECT_EQ(TestDataSink->String(), ",a,,");
}

TEST(DSVReader, ReadRow){
	std::vector <std::string> read;
	std::vector <std::string> results;

	// "abc" hi,12,83 --> {"abc hi", "12", "83"}
	auto TestDataSource = std::make_shared<CStringDataSource>("\"abc\" hi,12,83");
	CDSVReader Reader(TestDataSource, ',');
	read = {};
	results = {"abc hi", "12", "83"};
	Reader.ReadRow(read);
	EXPECT_EQ(read, results);


	//,a,, --> {"", "a", "", ""} {"",""}
	auto TestDataSource2 = std::make_shared<CStringDataSource>(",a,,\n,");
	CDSVReader Reader2(TestDataSource2, ',');
	read = {};
	results = {"", "a", "", ""};
	Reader2.ReadRow(read);
	EXPECT_EQ(read, results);
	
	read = {};
	results = {"", ""};
	Reader2.ReadRow(read);
	EXPECT_EQ(read, results);


	//a,b,c\n\n,\n\n1,2,3 --> {"a", "b", "c"} {""} {"", ""} {""} {"1", "2", "3"}
	auto TestDataSource3 = std::make_shared<CStringDataSource>("a,b,c\n\n,\n\n1,2,3");
	CDSVReader Reader3(TestDataSource3, ',');
	read = {};
	results = {"a","b","c"};
	Reader3.ReadRow(read);
	EXPECT_EQ(read, results);

	read = {};
	results = {""};
	Reader3.ReadRow(read);
	EXPECT_EQ(read, results);

	read = {};
	results = {"", ""};
	Reader3.ReadRow(read);
	EXPECT_EQ(read, results);

	read = {};
	results = {""};
	Reader3.ReadRow(read);
	EXPECT_EQ(read, results);

	read = {};
	results = {"1", "2", "3"};
	Reader3.ReadRow(read);
	EXPECT_EQ(read, results);

	//1,2,3\n
	auto TestDataSource4 = std::make_shared<CStringDataSource>("1,2,3\n");
	CDSVReader Reader4(TestDataSource4, ',');
	read = {};
	results = {"1","2","3"};
	Reader4.ReadRow(read);
	EXPECT_EQ(read, results);

	read = {};
	results = {""};
	Reader4.ReadRow(read);
	EXPECT_EQ(read, results);
}

TEST(DSVWriter, SimpleWritingTest) {

	auto Sink = std::make_shared< CStringDataSink > ();
    CDSVWriter Writer(Sink, '1');
    std::vector< std::string > input = {"Apples", "are", "better!"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(), "Apples1are1better!");

    auto Sink1 = std::make_shared< CStringDataSink > ();
    CDSVWriter Writer1(Sink1, ',');
    std::vector< std::string > input1 = {"Bananas", "are", "better", "than", "apples"};

    EXPECT_TRUE(Writer1.WriteRow(input1));
    EXPECT_EQ(Sink1->String(), "Bananas,are,better,than,apples");


    auto Sink2 = std::make_shared< CStringDataSink > ();
    CDSVWriter Writer2(Sink2, 'l');
    std::vector< std::string > input2 = {"Neither", "of", "them","are","good"};

    EXPECT_TRUE(Writer2.WriteRow(input2)); 
    EXPECT_EQ(Sink2->String(), "Neitherloflthemlarelgood");

    auto Sink3 = std::make_shared< CStringDataSink > ();
    CDSVWriter Writer3(Sink3, 'r');
    std::vector< std::string > input3 = {"Watermelon", "are", "superior"};

    EXPECT_TRUE(Writer3.WriteRow(input3));
    EXPECT_EQ(Sink3->String(), "\"Watermelon\"r\"are\"r\"superior\"");
}

TEST(DSVReading, SimpleReadingTest){

	auto Source = std::make_shared< CStringDataSource > ("Apples1are1better!");
    CDSVReader Reader(Source,'1');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),3);
    EXPECT_EQ(output[0],"Apples");
    EXPECT_EQ(output[1],"are");
    EXPECT_EQ(output[2],"better!");

    auto Source1 = std::make_shared< CStringDataSource > ("Bananas,are,better,than,apples");
    CDSVReader Reader1(Source1,',');
    std::vector< std::string > output1;

    EXPECT_TRUE(Reader1.ReadRow(output1));
    ASSERT_EQ(output1.size(),5);
    EXPECT_EQ(output1[0],"Bananas");
    EXPECT_EQ(output1[1],"are");
    EXPECT_EQ(output1[2],"better");
    EXPECT_EQ(output1[3],"than");
    EXPECT_EQ(output1[4],"apples");

    auto Source2 = std::make_shared< CStringDataSource > ("Neitherloflthemlarelgood");
    CDSVReader Reader2(Source2,'l');
    std::vector< std::string > output2;

    EXPECT_TRUE(Reader2.ReadRow(output2));
    ASSERT_EQ(output2.size(),5);
    EXPECT_EQ(output2[0],"Neither");
    EXPECT_EQ(output2[1],"of");
    EXPECT_EQ(output2[2],"them");
    EXPECT_EQ(output2[3],"are");
    EXPECT_EQ(output2[4],"good");

}