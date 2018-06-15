#include <tradebook.h>

#include <gtest/gtest.h>
#include <stdexcept>
#include <sstream>
#include <assert.h>

using namespace tradebook;

void setupTradebook(Tradebook* tb) {
    assert(tb);
    tb->insertTrade(Trade(52924702, "aaa", 13, 1136));
    tb->insertTrade(Trade(52924702, "aac", 20, 477));
    tb->insertTrade(Trade(52925641, "aab", 31, 907));
    tb->insertTrade(Trade(52927350, "aab", 29, 724));
    tb->insertTrade(Trade(52927783, "aac", 21, 638));
    tb->insertTrade(Trade(52930489, "aaa", 18, 1222));
    tb->insertTrade(Trade(52931654, "aaa", 9, 1077));
    tb->insertTrade(Trade(52933453, "aab", 9, 756));
    return;
}

// Basic operations
TEST(TradebookOperations, CanInsertTrade) {
    // GIVEN
    Tradebook tb;
    // EXPECT
    EXPECT_NO_THROW(tb.insertTrade(Trade(51300036398, "dag", 129, 222)));
}

// getMaxTimeGap tests
TEST(TradebookGetMaxTimeGap, NoTradesThrows) {
    // GIVEN
    Tradebook tb;
    // THEN
    EXPECT_THROW(tb.getMaxTimeGap("a"), std::invalid_argument);
}

TEST(TradebookGetMaxTimeGap, OneTradeOnlyReturnsZero) {
    // GIVEN
    Tradebook tb;
    // WHEN
    tb.insertTrade(Trade(51300036398, "dag", 129, 222));
    // THEN
    EXPECT_EQ(0, tb.getMaxTimeGap("dag").count());
}

TEST(TradebookGetMaxTimeGap, MultipleTradesReturnMaxGap) {
    // GIVEN
    Tradebook tb;
    // WHEN
    setupTradebook(&tb);
    // THEN
    EXPECT_EQ(5787, tb.getMaxTimeGap("aaa").count());
    EXPECT_EQ(6103, tb.getMaxTimeGap("aab").count());
    EXPECT_EQ(3081, tb.getMaxTimeGap("aac").count());
}

// getTotalVolumeTraded tests
TEST(TradebookGetTotalVolumeTraded, NoTradesThrows) {
    // GIVEN
    Tradebook tb;
    // THEN
    EXPECT_THROW(tb.getTotalVolumeTraded("a"), std::invalid_argument);
}

TEST(TradebookGetTotalVolumeTraded, OneTradeReturnsVolume) {
    // GIVEN
    Tradebook tb;
    // WHEN
    tb.insertTrade(Trade(51300036398, "dag", 129, 222));
    // THEN
    EXPECT_EQ(129, tb.getTotalVolumeTraded("dag"));
}

TEST(TradebookGetTotalVolumeTraded, MultipleTradesReturnTotalVolume) {
    // GIVEN
    Tradebook tb;
    // WHEN
    setupTradebook(&tb);
    // THEN
    EXPECT_EQ(40, tb.getTotalVolumeTraded("aaa"));
    EXPECT_EQ(69, tb.getTotalVolumeTraded("aab"));
    EXPECT_EQ(41, tb.getTotalVolumeTraded("aac"));
}

// getWeightedAveragePrice tests
TEST(TradebookGetWeightedAveragePrice, NoTradesThrows) {
    // GIVEN
    Tradebook tb;
    // THEN
    EXPECT_THROW(tb.getWeightedAveragePrice("a"), std::invalid_argument);
}

TEST(TradebookGetWeightedAveragePrice, OneTradeReturnsPrice) {
    // GIVEN
    Tradebook tb;
    // WHEN
    tb.insertTrade(Trade(51300036398, "dag", 129, 222));
    // THEN
    EXPECT_EQ(222, tb.getWeightedAveragePrice("dag"));
}

TEST(TradebookGetWeightedAveragePrice, MultipleTradesReturnWeightedAverage) {
    // GIVEN
    Tradebook tb;
    // WHEN
    setupTradebook(&tb);
    // THEN
    EXPECT_EQ(1161, tb.getWeightedAveragePrice("aaa"));
    EXPECT_EQ(810, tb.getWeightedAveragePrice("aab"));
    EXPECT_EQ(559, tb.getWeightedAveragePrice("aac"));
}

// getMaxTradedPrice tests
TEST(TradebookGetMaxTradedPrice, NoTradesThrows) {
    // GIVEN
    Tradebook tb;
    // THEN
    EXPECT_THROW(tb.getMaxTradedPrice("a"), std::invalid_argument);
}

TEST(TradebookGetMaxTradedPrice, OneTradeReturnsPrice) {
    // GIVEN
    Tradebook tb;
    // WHEN
    tb.insertTrade(Trade(51300036398, "dag", 129, 222));
    // THEN
    EXPECT_EQ(222, tb.getMaxTradedPrice("dag"));
}

TEST(TradebookGetMaxTradedPrice, MultipleTradesReturnTradedPrice) {
    // GIVEN
    Tradebook tb;
    // WHEN
    setupTradebook(&tb);
    // THEN
    EXPECT_EQ(1222, tb.getMaxTradedPrice("aaa"));
    EXPECT_EQ(907, tb.getMaxTradedPrice("aab"));
    EXPECT_EQ(638, tb.getMaxTradedPrice("aac"));
}

// printSummary test
TEST(TradebookPrintSummary, NoTradePrintsEmpty) {
    // GIVEN
    Tradebook tb;
    // EXPECT
    std::stringstream ss;
    tb.printSummary(ss);
    EXPECT_EQ("", ss.str());
}

TEST(TradebookPrintSummary, OneTradePrintsSummary) {
    // GIVEN
    Tradebook tb;
    // WHEN
    tb.insertTrade(Trade(51300036398, "dag", 129, 222));
    // EXPECT
    std::stringstream ss;
    tb.printSummary(ss);
    EXPECT_EQ("dag,0,129,222,222\n", ss.str());
}

TEST(TradebookPrintSummary, MultipleTradesPrintSummary) {
    // GIVEN
    Tradebook tb;
    // WHEN
    setupTradebook(&tb);
    // EXPECT
    std::stringstream ss;
    tb.printSummary(ss);
    EXPECT_EQ("aaa,5787,40,1161,1222\naab,6103,69,810,907\naac,3081,41,559,638\n",
              ss.str());
}

// Test driver
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
