#include <gtest/gtest.h>
#include "OpenStreetMap.h"
#include "StringDataSource.h"
#include "XMLReader.h"

TEST(OpenStreetMap, SingularNodeTest){
    // Example Case via Piazza
    auto InStream = std::make_shared<CStringDataSource>("<?xml version='1.0' encoding='UTF-8'?>"
                                                        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">"
                                                        "<node id=\"1\" lat=\"1.0\" lon=\"-1.0\"/>"
                                                        "</osm>");
    auto Reader = std::make_shared<CXMLReader>(InStream);
    COpenStreetMap StreetMap(Reader);
    
    EXPECT_EQ(StreetMap.NodeCount(),1);
    EXPECT_EQ(StreetMap.WayCount(),0);
    EXPECT_EQ(StreetMap.NodeByIndex(0)->ID(),1);
    EXPECT_EQ(StreetMap.NodeByIndex(1), nullptr);
    EXPECT_EQ(StreetMap.NodeByID(0), nullptr);
    EXPECT_EQ(StreetMap.NodeByID(1), StreetMap.NodeByIndex(0));
}

TEST(OpenStreetMap, MultipleNodesTest){
        //Test case Multiple Nodes
     auto InStream = std::make_shared<CStringDataSource>("<?xml version='1.0' encoding='UTF-8'?>"
                                                        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">"
                                                        "<node id=\"1\" lat=\"1.0\" lon=\"-1.0\"/>"
                                                        "<node id=\"2\" lat=\"2.0\" lon=\"-2.0\"/>"
                                                        "<node id=\"3\" lat=\"3.0\" lon=\"-3.0\"/>"
                                                        "<node id=\"4\" lat=\"4.0\" lon=\"-4.0\"/>"
                                                        "<node id=\"5\" lat=\"5.0\" lon=\"-5.0\"/>"
                                                        "<node id=\"6\" lat=\"6.0\" lon=\"-6.0\"/>"
		                                                "<tag k=\"highway\" v=\"residential\"/>"
                                                        "</osm>");
    auto Reader = std::make_shared<CXMLReader>(InStream);
    COpenStreetMap StreetMap(Reader);

    EXPECT_EQ(StreetMap.NodeCount(), 6);
    EXPECT_EQ(StreetMap.WayCount(), 0);
    EXPECT_EQ(StreetMap.NodeByIndex(0)->ID(),1);
    EXPECT_EQ(StreetMap.NodeByIndex(1)->ID(),2);
    EXPECT_EQ(StreetMap.NodeByIndex(2)->ID(),3);
    EXPECT_EQ(StreetMap.NodeByIndex(3)->ID(),4);
    EXPECT_EQ(StreetMap.NodeByIndex(4)->ID(),5);
    EXPECT_EQ(StreetMap.NodeByIndex(5)->ID(),6);
    EXPECT_EQ(StreetMap.NodeByID(1), StreetMap.NodeByIndex(0));
    EXPECT_EQ(StreetMap.NodeByID(2), StreetMap.NodeByIndex(1));
    EXPECT_EQ(StreetMap.NodeByID(3), StreetMap.NodeByIndex(2));
    EXPECT_EQ(StreetMap.NodeByID(4), StreetMap.NodeByIndex(3));
    EXPECT_EQ(StreetMap.NodeByID(5), StreetMap.NodeByIndex(4));
    EXPECT_EQ(StreetMap.NodeByID(6), StreetMap.NodeByIndex(5));
}

TEST(OpenStreetMap, SingularWayTest){
        // Test Case testing single way count
    auto InStream = std::make_shared<CStringDataSource>("<?xml version='1.0' encoding='UTF-8'?>"
                                                        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">"
                                                        "<way id=\"10747760\">"
                                                        "</osm>");
    auto Reader = std::make_shared<CXMLReader>(InStream);
    COpenStreetMap StreetMap(Reader);

    EXPECT_EQ(StreetMap.NodeCount(), 0);
    EXPECT_EQ(StreetMap.WayCount(), 1);
    EXPECT_EQ(StreetMap.WayByIndex(0)->ID(), 10747760);
    EXPECT_EQ(StreetMap.WayByID(10747760), StreetMap.WayByIndex(0));
}

TEST(OpenStreetMap, MultipleWayTest){
        // Test Case testing single way count
    auto InStream = std::make_shared<CStringDataSource>("<?xml version='1.0' encoding='UTF-8'?>"
                                                        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">"
                                                        "<way id=\"10747760\"/>"
                                                    	"<way id=\"10747764\"/>"
                                                        "<way id=\"10747766\"/>"
                                                        "<way id=\"10747768\"/>"
                                                    	"<way id=\"10747770\"/>"
                                                        "<way id=\"10747772\"/>"
                                                        "</osm>");
    auto Reader = std::make_shared<CXMLReader>(InStream);
    COpenStreetMap StreetMap(Reader);

    EXPECT_EQ(StreetMap.NodeCount(), 0);
    EXPECT_EQ(StreetMap.WayCount(), 6);
    EXPECT_EQ(StreetMap.WayByIndex(0)->ID(),10747760);
    EXPECT_EQ(StreetMap.WayByIndex(1)->ID(),10747764);
    EXPECT_EQ(StreetMap.WayByIndex(2)->ID(),10747766);
    EXPECT_EQ(StreetMap.WayByIndex(3)->ID(),10747768);
    EXPECT_EQ(StreetMap.WayByIndex(4)->ID(),10747770);
    EXPECT_EQ(StreetMap.WayByIndex(5)->ID(),10747772);
    EXPECT_EQ(StreetMap.WayByID(10747760), StreetMap.WayByIndex(0));
    EXPECT_EQ(StreetMap.WayByID(10747764), StreetMap.WayByIndex(1));
    EXPECT_EQ(StreetMap.WayByID(10747766), StreetMap.WayByIndex(2));
    EXPECT_EQ(StreetMap.WayByID(10747768), StreetMap.WayByIndex(3));
    EXPECT_EQ(StreetMap.WayByID(10747770), StreetMap.WayByIndex(4));
    EXPECT_EQ(StreetMap.WayByID(10747772), StreetMap.WayByIndex(5));
}