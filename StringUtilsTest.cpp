#include <gtest/gtest.h>
#include "StringUtils.h"

TEST(StringUtilsTest, SliceTest){
    std::string Base = "Hello";

    EXPECT_EQ(StringUtils::Slice(Base,1,-1), "ello");
    EXPECT_EQ(StringUtils::Slice(Base,3,4), "lo");
    EXPECT_EQ(StringUtils::Slice(Base,1,2), "el");
}

TEST(StringUtilsTest, Capitalize){
    std::string Base = "hello";
    std::string Base1 = "hey world";
    std::string Base2 = "ba nan a";

    EXPECT_EQ(StringUtils::Capitalize(Base), "Hello");
    EXPECT_EQ(StringUtils::Capitalize(Base1), "Hey World");
    EXPECT_EQ(StringUtils::Capitalize(Base2), "Ba Nan A");
}

TEST(StringUtilsTest, Upper){
    std::string Base = "hello";
    std::string Base1 = "ApplE IS GOoooOd";
    std::string Base2 = "BanaNA";

    EXPECT_EQ(StringUtils::Upper(Base), "HELLO");
    EXPECT_EQ(StringUtils::Upper(Base1), "APPLE IS GOOOOOD");
    EXPECT_EQ(StringUtils::Upper(Base2), "BANANA");

}

TEST(StringUtilsTest, Lower){
    std::string Base = "HELLO";
    std::string Base1 = "BAnAna aRe BeTtEr";
    std::string Base2 = "TeaM BanAnA";

    EXPECT_EQ(StringUtils::Lower(Base), "hello");
    EXPECT_EQ(StringUtils::Lower(Base1), "banana are better");
    EXPECT_EQ(StringUtils::Lower(Base2), "team banana");

}

TEST(StringUtilsTest, LStrip){
    std::string Base = "     hello";
    std::string Base1 = "   Pineapples are good";
    std::string Base2 = " TEAM BANANAS   ";

    EXPECT_EQ(StringUtils::LStrip(Base), "hello");
    EXPECT_EQ(StringUtils::LStrip(Base1), "Pineapples are good");
    EXPECT_EQ(StringUtils::LStrip(Base2), "TEAM BANANAS   ");
}

TEST(StringUtilsTest, RStrip){
    std::string Base = "hello     ";
    std::string Base1 = "Pineapples are good   ";
    std::string Base2 = "   NOOO TEAM APPLE     ";

    EXPECT_EQ(StringUtils::RStrip(Base), "hello");
    EXPECT_EQ(StringUtils::RStrip(Base1), "Pineapples are good");
    EXPECT_EQ(StringUtils::RStrip(Base2), "   NOOO TEAM APPLE");
}

TEST(StringUtilsTest, Strip){
    std::string Base = "     hello     ";
    std::string Base1 = "   Pineapples are good   ";
    std::string Base2 = " I think pineapples are good too   ye ";


    EXPECT_EQ(StringUtils::Strip(Base), "hello");
    EXPECT_EQ(StringUtils::Strip(Base1), "Pineapples are good");
    EXPECT_EQ(StringUtils::Strip(Base2), "I think pineapples are good too   ye");
}

TEST(StringUtilsTest, Center){
    std::string Base = "Apple";
    
    EXPECT_EQ(StringUtils::Center(Base, 5, '-'), "--Apple---");
    EXPECT_EQ(StringUtils::Center(Base, 6, '*'), "***Apple***");
    EXPECT_EQ(StringUtils::Center(Base, 1, ' '), " Apple");
}

TEST(StringUtilsTest, LJust){
    std::string Base = "Banana";
    
    EXPECT_EQ(StringUtils::LJust(Base, 5, '-'), "-----Banana");
    EXPECT_EQ(StringUtils::LJust(Base, 6, '*'), "******Banana");
    EXPECT_EQ(StringUtils::LJust(Base, 1, ' '), " Banana");
}

TEST(StringUtilsTest, RJust){
    std::string Base = "Pineapples";
    
    EXPECT_EQ(StringUtils::RJust(Base, 5, '-'), "Pineapples-----");
    EXPECT_EQ(StringUtils::RJust(Base, 6, '*'), "Pineapples******");
    EXPECT_EQ(StringUtils::RJust(Base, 1, ' '), "Pineapples ");
}

TEST(StringUtilsTest, Replace){
    std::string Base = "Hello";
    std::string Base1 = "BononoRong";
    std::string Base2 = "Pea Nuts";

    EXPECT_EQ(StringUtils::Replace(Base, "o", "a"), "Hella");   
    EXPECT_EQ(StringUtils::Replace(Base1,"o", "a"), "BananaRang");
    EXPECT_EQ(StringUtils::Replace(Base2,"s", "!"), "Pea Nut!");
}

TEST(StringUtilsTest, Split){
   std::string Base = "Hello world";
   std::vector<std::string> result = {"Hello", "world"};

   std::string Base1 = "Hey Hanna Montana";
   std::vector<std::string> result1 = {"Hey", "Hanna", "Montana"};

   EXPECT_EQ(StringUtils::Split(Base, "H"), result);
   EXPECT_EQ(StringUtils::Split(Base, ""), result);
   EXPECT_EQ(StringUtils::Split(Base1, "H"), result1);
}

TEST(StringUtilsTest, Join){
    std::string Base = ", ";
    std::vector<std::string> BaseVect = {"Pencil", "Notebook", "Eraser"};
    
    std::string Base1 = " ";
    std::vector<std::string> BaseVect1 = {"Apples", "are", "better"};

    std::string Base2 = " 'lies' ";
    std::vector<std::string> BaseVect2 = {"Banana", "are", "good"};
    
    EXPECT_EQ(StringUtils::Join(Base, BaseVect), "Pencil, Notebook, Eraser");
    EXPECT_EQ(StringUtils::Join(Base1, BaseVect1), "Apples are better");
    EXPECT_EQ(StringUtils::Join(Base2, BaseVect2), "Banana 'lies' are 'lies' good");
}

TEST(StringUtilsTest, ExpandTabs){
    std::string Base = "\tHello";
    std::string Base1 = "\t\t Bananas";
    std::string Base2 = "Ba\tna\tna";
    
    EXPECT_EQ(StringUtils::ExpandTabs(Base, 4), "    Hello");
    EXPECT_EQ(StringUtils::ExpandTabs(Base1, 4), "         Bananas");    
    EXPECT_EQ(StringUtils::ExpandTabs(Base2, 4), "Ba    na    na");    
 
}

TEST(StringUtilsTest, EditDistance){
    std::string Base1 = "Hello";
    std::string Base2 = "hella";

    std::string Base3 = "Banana";
    std::string Base4 = "bonono";

    std::string Base5 = "Apples";
    std::string Base6 = "Bananas";
    
    EXPECT_EQ(StringUtils::EditDistance(Base1, Base2, true), 1);
    EXPECT_EQ(StringUtils::EditDistance(Base3, Base4, false), 4);
    EXPECT_EQ(StringUtils::EditDistance(Base5, Base6, false), 7);    
}
