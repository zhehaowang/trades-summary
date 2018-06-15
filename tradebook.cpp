#include <tradebook.h>
#include <assert.h>

namespace tradebook {

void
Tradebook::insertTrade(const Trade& trade) {
    auto it = d_summary.find(trade.symbol());
    if (it == d_summary.end()) {
        auto res = d_summary.insert({trade.symbol(), TradeSummary()});
        assert(res.second);
        TradeSummary& summary = res.first->second;
        summary.d_lastTradeTimestamp   = trade.timestamp();
        summary.d_maxTimeGap           = std::chrono::duration<uint64_t>(0);
        summary.d_totalVolume          = trade.quantity();
        summary.d_weightedAveragePrice = trade.price();
        summary.d_maxPrice             = trade.price();
    } else {
        TradeSummary& summary = it->second;
        if (trade.price() > summary.d_maxPrice) {
            summary.d_maxPrice = trade.price();
        }
        summary.d_weightedAveragePrice =
            (summary.d_totalVolume * summary.d_weightedAveragePrice + trade.quantity() * trade.price()) /
            (summary.d_totalVolume + trade.quantity());
        summary.d_totalVolume += trade.quantity();
        auto gap = trade.timestamp() - summary.d_lastTradeTimestamp;
        summary.d_lastTradeTimestamp = trade.timestamp();
        if (gap > summary.d_maxTimeGap) {
            summary.d_maxTimeGap = gap;
        }
    }
}

void
Tradebook::printSummary(std::ostream& stream) const {
    for (auto it = d_summary.begin(); it != d_summary.end(); ++it) {
        stream << it->first << ","
               << std::chrono::duration_cast<std::chrono::seconds>(it->second.d_maxTimeGap).count() << ","
               << it->second.d_totalVolume << ","
               << static_cast<Trade::Price>(it->second.d_weightedAveragePrice) << ","
               << it->second.d_maxPrice << "\n";
    }
}

}