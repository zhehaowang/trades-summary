#include <tradebook.h>

#include <gtest/gtest.h>
#include <stdexcept>

using namespace tradebook;

// Basic operations
TEST(TradebookOperations, CanInsertTrade) {
    // GIVEN
    Tradebook tb;
    // EXPECT
    EXPECT_NO_THROW(tb.insertTrade(Trade(51300036398, "dag", 129, 222)));
}

// getMaximumTimeGap tests
TEST(TradebookGetMaximumTimeGap, NoTradesThrows) {
    // GIVEN
    Tradebook tb;
    // THEN
    EXPECT_THROW(tb.getMaximumTimeGap("a"), std::invalid_argument);
}

TEST(TradebookGetMaximumTimeGap, OneTradeOnlyReturnsZero) {
    // GIVEN
    Tradebook tb;
    // WHEN
    tb.insertTrade(Trade(51300036398, "dag", 129, 222));
    // THEN
    EXPECT_EQ(0, tb.getMaximumTimeGap("dag").count());

}

TEST(TradebookGetMaximumTimeGap, MultipleTradesReturnMaximumGap) {
    // max gap is between the first two
    // max gap happens in the middle
    // max gap is between the last two
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
    EXPECT_EQ(222, tb.getTotalVolumeTraded("dag"));

}

TEST(TradebookGetWeightedAveragePrice, MultipleTradesReturnWeightedAverage) {

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
    EXPECT_EQ(222, tb.getTotalVolumeTraded("dag"));
}

TEST(TradebookGetMaxTradedPrice, MultipleTradesReturnTradedPrice) {

}

// Test driver
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
