#include <gtest/gtest.h>
#include "CSVBusSystem.h"
#include "DSVReader.h"
#include "StringDataSource.h"
#include <iostream>

TEST(CSVBusSystem, SingularStopTest){
    auto InStreamStops = std::make_shared< CStringDataSource >("stop_id,node_id\n1,1001");
    auto InStreamRoutes = std::make_shared< CStringDataSource >("route,stop_id");
    auto CSVReaderStops = std::make_shared< CDSVReader >(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared< CDSVReader >(InStreamRoutes,',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    EXPECT_EQ(BusSystem.StopCount(),1);
    EXPECT_EQ(BusSystem.RouteCount(),0);
    EXPECT_EQ(BusSystem.StopByIndex(0)->ID(),1);
    EXPECT_EQ(BusSystem.StopByIndex(0)->NodeID(),1001);
    EXPECT_EQ(BusSystem.StopByIndex(1),nullptr);
    EXPECT_EQ(BusSystem.StopByID(0), nullptr);
    EXPECT_EQ(BusSystem.StopByID(1001)->ID(), 1);
    EXPECT_EQ(BusSystem.StopByID(1001)->NodeID(),1001);
}

TEST(CCSVBusSystem, MultipleStopTest){
    auto InStreamStops = std::make_shared< CStringDataSource >("stop_id,node_id\n22043,2849810514\n22358,2849805223\n22105,3954294407\n22175,5598639595\n22174,3119663186\n22177,2599137935\n22176,2607436578\n22078,1190339479");
    auto InStreamRoutes = std::make_shared< CStringDataSource >("route,stop_id");
    auto CSVReaderStops = std::make_shared< CDSVReader >(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared< CDSVReader >(InStreamRoutes,',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    EXPECT_EQ(BusSystem.StopCount(),8);
    EXPECT_EQ(BusSystem.RouteCount(),0);
    EXPECT_EQ(BusSystem.StopByIndex(0)->ID(),22043);
    EXPECT_EQ(BusSystem.StopByIndex(0)->NodeID(),2849810514);
    EXPECT_EQ(BusSystem.StopByID(2849805223)->ID(),22358);
    EXPECT_EQ(BusSystem.StopByID(5598639595)->NodeID(),5598639595);
}

TEST(CCSVBusSystem, SingularRouteTest){
    auto InStreamStops = std::make_shared< CStringDataSource >("stop_id,node_id");
    auto InStreamRoutes = std::make_shared< CStringDataSource >("route,stop_id\nA,22258\nA,22169\nA,22000\nA,22005\nA,22007\nA,22011\nA,22031\nA,22033\nA, 22020");
    auto CSVReaderStops = std::make_shared< CDSVReader >(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared< CDSVReader >(InStreamRoutes,',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    EXPECT_EQ(BusSystem.StopCount(),0);
    EXPECT_EQ(BusSystem.RouteCount(),1);
    EXPECT_EQ(BusSystem.RouteByIndex(0)->Name(), "A");
}

TEST(CCSVBusSystem, MultipleRouteTest){
    auto InStreamStops = std::make_shared< CStringDataSource >("stop_id,node_id");
    auto InStreamRoutes = std::make_shared< CStringDataSource >("route,stop_id\nA,22258\nB,22189\nD,22256");
    auto CSVReaderStops = std::make_shared< CDSVReader >(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared< CDSVReader >(InStreamRoutes,',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    EXPECT_EQ(BusSystem.StopCount(),0);
    EXPECT_EQ(BusSystem.RouteCount(),3);
    EXPECT_EQ(BusSystem.RouteByIndex(0)->Name(), "A");
    EXPECT_EQ(BusSystem.RouteByIndex(1)->Name(), "B");
    EXPECT_EQ(BusSystem.RouteByIndex(2)->Name(), "D");

}